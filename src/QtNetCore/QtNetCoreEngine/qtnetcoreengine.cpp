#include "qtnetcoreengine.h"

#include "corerunner.h"
#include "trace.h"
#include <condition_variable>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QDebug>

// this callback is called from c++ to trigger the coreclr to quit (exit wait loop)
typedef void(*QuitSignal)();

// This struct is passed to the CoreCLR via an arg in Program.Main.
// The .NET code should use this to fully wire everything up.
struct InteropData
{
    void* nativeEngine;
    void* coreCLRInitiaizedCallback;
    void* setQuitSignal;
};

class QtNetCoreEnginePrivate : public QThread
{
public:
    QtNetCoreEnginePrivate() :
        startupResult(0),
        isClrRunning(false)
    {

    }
    void coreClrInitialized(int result)
    {
        startupResult = result;
        startupHandle.wakeAll();
    }
    InteropData interopData;
    QMutex mutex;
    std::vector<std::wstring> args;
    QWaitCondition startupHandle;
    int startupResult;
    bool isClrRunning;
    QuitSignal quitSignal;
protected:
    void run() override
    {
        isClrRunning = true;

        qDebug() << "Starting the coreclr, and waiting for the finished signal back from the coreclr.";

        std::vector<const wchar_t*> newArgs;
        for(int x = 0; x < args.size(); x++)
        {
            newArgs.push_back(args.at(x).c_str());
        }

        // append the pointer to our interop structure.
        wchar_t interopPointerBuffer[256];
        swprintf_s(interopPointerBuffer, L"%llu", (unsigned long long)&interopData);
        newArgs.push_back(const_cast<wchar_t*>(&interopPointerBuffer[0]));

        std::wcout << (unsigned long long)&interopData;
        std::wcout << newArgs.at(newArgs.size() - 1) << "\n";

        int runResult = RunCoreCLR(newArgs.size(), &newArgs[0]);

        qDebug() << "Finished running the corclr with a result of " << runResult;

        isClrRunning = false;

        startupHandle.wakeAll();
    }
};

void CoreCLRInitiaizedCallback(QtNetCoreEngine* engine, int result)
{
    engine->d_ptr->coreClrInitialized(result);
}

void SetQuitSignal(QtNetCoreEngine* engine, QuitSignal signal)
{
    engine->d_ptr->quitSignal = signal;
}

QtNetCoreEngine::QtNetCoreEngine(const int argc, const wchar_t *argv[]) : d_ptr(new QtNetCoreEnginePrivate)
{
    d_ptr->mutex.lock();

    d_ptr->interopData.nativeEngine = this;
    d_ptr->interopData.coreCLRInitiaizedCallback = &CoreCLRInitiaizedCallback;
    d_ptr->interopData.setQuitSignal = &SetQuitSignal;

    for(int x = 0; x < argc; x++)
    {
        std::wstring arguement;
        arguement.append(argv[x]);
        d_ptr->args.push_back(arguement);
    }

    // wait for the clr to be initialized
    d_ptr->start();
    d_ptr->startupHandle.wait(&d_ptr->mutex);
    d_ptr->mutex.unlock();
}

QtNetCoreEngine::~QtNetCoreEngine()
{
    d_ptr->mutex.lock();

    if(d_ptr->isClrRunning)
    {
        // send cancel signal to coreclr, waiting for it to close.
        d_ptr->quitSignal();
        d_ptr->startupHandle.wait(&d_ptr->mutex);
    }

    d_ptr->mutex.unlock();
}
