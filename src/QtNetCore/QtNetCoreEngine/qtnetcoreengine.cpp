#include "qtnetcoreengine.h"

#include "trace.h"
#include "utils.h"
#include "pal.h"
#include "fx_ver.h"
#include "error_codes.h"
#include <QMutex>
#include <QThread>

#define LIBFXR_NAME MAKE_LIBNAME("hostfxr")

typedef void(*QtNetCoreEngine_Cancel) (int result);
typedef int(*hostfxr_main_fn) (const int argc, const pal::char_t* argv[]);

// This struct is passed to the CoreCLR via an arg in Program.Main.
// The .NET code should use this to fully wire everything up.
struct InteropData
{

};

class CLRThread : public QThread
{
public:
    CLRThread(InteropData* interopData) : interopData(interopData)
    {

    }
    void run() override
    {

    }
private:
    InteropData* interopData;
};

class QtNetCoreEnginePrivate
{
public:
    QtNetCoreEnginePrivate()
    {
        interopData = {};
        cancelCallback = NULL;
        clrThread = new CLRThread(&interopData);
    }
    InteropData interopData;
    QtNetCoreEngine_Cancel cancelCallback;
    QMutex mutex;
    CLRThread* clrThread;
    int argc;
    std::vector<wchar_t*> argv;
};

QtNetCoreEngine::QtNetCoreEngine() : d_ptr(new QtNetCoreEnginePrivate)
{
    trace::setup();
}

QtNetCoreEngine::~QtNetCoreEngine()
{

}

struct Test
{
    int testt;
    void* setCallback;
};

int QtNetCoreEngine::Initialize(const int argc, const wchar_t* argv[])
{
    QMutexLocker lock(&d_ptr->mutex);

    // build a new set of arguments that contain a trailing value that is a pointer to this instance.
    std::vector<const wchar_t*> newArgs;
    for(int x = 0; x < argc; x++)
    {
        newArgs.push_back(argv[x]);
    }

//    Test testt;
//    testt.testt = 3;
//    testt.setCallback = (void*)&CB;

    wchar_t nativeEnginePointerBuffer[256];
    swprintf_s(nativeEnginePointerBuffer, L"%llu", (unsigned long long)&);
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

