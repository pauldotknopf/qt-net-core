#include "qtnetcoreengine.h"

#include "trace.h"
#include "utils.h"
#include "pal.h"
#include "fx_ver.h"
#include "error_codes.h"
#include <QMutex>

#define LIBFXR_NAME MAKE_LIBNAME("hostfxr")

typedef void(*QtNetCoreEngine_Cancel) (int result);
typedef int(*hostfxr_main_fn) (const int argc, const pal::char_t* argv[]);

pal::string_t resolve_fxr_path(const pal::string_t& own_dir)
{
    pal::string_t fxr_dir = own_dir;
    append_path(&fxr_dir, _X("host"));
    append_path(&fxr_dir, _X("fxr"));
    if (pal::directory_exists(fxr_dir))
    {
        trace::info(_X("Reading fx resolver directory=[%s]"), fxr_dir.c_str());

        std::vector<pal::string_t> list;
        pal::readdir(fxr_dir, &list);

        fx_ver_t max_ver(-1, -1, -1);
        for (const auto& dir : list)
        {
            trace::info(_X("Considering fxr version=[%s]..."), dir.c_str());

            pal::string_t ver = get_filename(dir);

            fx_ver_t fx_ver(-1, -1, -1);
            if (fx_ver_t::parse(ver, &fx_ver, false))
            {
                max_ver = std::max(max_ver, fx_ver);
            }
        }

        pal::string_t max_ver_str = max_ver.as_str();
        append_path(&fxr_dir, max_ver_str.c_str());
        trace::info(_X("Detected latest fxr version=[%s]..."), fxr_dir.c_str());

        pal::string_t ret_path;
        if (library_exists_in_dir(fxr_dir, LIBFXR_NAME, &ret_path))
        {
            trace::info(_X("Resolved fxr [%s]..."), ret_path.c_str());
            return ret_path;
        }
    }

    pal::string_t fxr_path;
    if (library_exists_in_dir(own_dir, LIBFXR_NAME, &fxr_path))
    {
        trace::info(_X("Resolved fxr [%s]..."), fxr_path.c_str());
        return fxr_path;
    }
    return pal::string_t();
}

class QtNetCoreEnginePrivate {
public:
    QtNetCoreEnginePrivate()
    {
        test = 0;
    }

    QtNetCoreEngine_Cancel cancelCallback;
    QMutex mutex;
    int test;
};

QtNetCoreEngine::QtNetCoreEngine() : d_ptr(new QtNetCoreEnginePrivate)
{
    trace::setup();
}

QtNetCoreEngine::~QtNetCoreEngine()
{

}

int QtNetCoreEngine::Initialize(const int argc, const wchar_t* argv[])
{
    QMutexLocker lock(&d_ptr->mutex);

    if (trace::is_enabled())
    {
        trace::info(_X("--- Invoked dotnet [version: %s, commit hash: %s] main = {"), _STRINGIFY(HOST_PKG_VER), _STRINGIFY(REPO_COMMIT_HASH));
        for (int i = 0; i < argc; ++i)
        {
            trace::info(_X("%s"), argv[i]);
        }
        trace::info(_X("}"));
    }

    pal::string_t own_path;
    if (!pal::get_own_executable_path(&own_path) || !pal::realpath(&own_path))
    {
        trace::error(_X("Failed to resolve full path of the current executable [%s]"), own_path.c_str());
        return StatusCode::CoreHostCurExeFindFailure;
    }

    pal::dll_t fxr;

    pal::string_t own_dir = get_directory(own_path);

    // Load library
    pal::string_t fxr_path = resolve_fxr_path(own_dir);
    if (fxr_path.empty())
    {
        trace::error(_X("A fatal error occurred, the required library %s could not be found at %s"), LIBFXR_NAME, own_dir.c_str());
        return StatusCode::CoreHostLibMissingFailure;
    }
    if (!pal::load_library(fxr_path.c_str(), &fxr))
    {
        trace::error(_X("The library %s was found, but loading it from %s failed"), LIBFXR_NAME, fxr_path.c_str());
        trace::error(_X(" - Installing .NET Core prerequisites might help resolve this problem."));
        trace::error(_X("     %s"), DOTNET_CORE_URL);
        return StatusCode::CoreHostLibLoadFailure;
    }

    // build a new set of arguments that contain a trailing value that is a pointer to this instance.
    std::vector<const wchar_t*> newArgs;
    for(int x = 0; x < argc; x++)
    {
        newArgs.push_back(argv[x]);
    }
    wchar_t nativeEnginePointerBuffer[256];
    swprintf_s(nativeEnginePointerBuffer, L"%llu", (unsigned long long)this);
    newArgs.push_back(const_cast<wchar_t*>(&nativeEnginePointerBuffer[0]));
    std::cout << "Engine pointer: " << (unsigned long long)this << "\n";


//    QtNetCoreEngine* real = this;

//    std::cout << real << "\n";
//    unsigned long long t = (unsigned long long)real;
//    std::cout << t << "\n";
//    QtNetCoreEngine* casted = (QtNetCoreEngine*)t;
//    std::cout << casted->d_ptr->test << "\n";

    // Obtain entrypoint symbols
    hostfxr_main_fn main_fn = (hostfxr_main_fn) pal::get_symbol(fxr, "hostfxr_main");
    int code = main_fn(newArgs.size(), &newArgs[0]);
    pal::unload_library(fxr);
    return code;
}

int QtNetCoreEngine::TearDown()
{
    QMutexLocker lock(&d_ptr->mutex);



    return 0;
}

extern "C"
{
    QTNETCOREENGINESHARED_EXPORT void SetCancelDelegate(QtNetCoreEngine* engine, QtNetCoreEngine_Cancel cancelCallback)
    {
        engine->d_ptr->cancelCallback = cancelCallback;
    }
}
