#include "netcore.h"
#include "qtnetcoreengine.h"
#include <QDebug>

class NetCorePrivate
{
public:
    static QtNetCoreEngine* coreEngine;

    static bool CreateCorCLR(QStringList arguements)
    {
        if(coreEngine != NULL)
        {
            qWarning() << "The engine is already created.";
            return false;
        }

        std::vector<std::wstring> converted;

        for (int i = 0; i < arguements.size(); ++i)
            converted.push_back(arguements.at(i).toStdWString());

        std::vector<const wchar_t*> convertArgs;
        for(int x = 0; x < converted.size(); x++)
        {
            convertArgs.push_back(converted.at(x).c_str());
        }

        coreEngine = new QtNetCoreEngine(convertArgs.size(), &convertArgs[0]);

        return true;
    }

    static bool DestroyCoreCLR()
    {
        if(coreEngine == NULL)
        {
            qWarning() << "The engine hasn't been created.";
            return false;
        }

        delete coreEngine;
        coreEngine = NULL;

        return true;
    }
};

QtNetCoreEngine* NetCorePrivate::coreEngine = NULL;

NetCore::NetCore(QQuickItem *parent):
    d_ptr(new NetCorePrivate),
    QQuickItem(parent)
{

}

NetCore::~NetCore()
{

}

bool NetCore::CreateCoreCLR(QStringList arguements)
{
    return NetCorePrivate::CreateCorCLR(arguements);
}

bool NetCore::DestroyCoreCLR()
{
    return NetCorePrivate::DestroyCoreCLR();
}

void NetCore::invokeStatic(QString type, QString method, QVariant args, QJSValue callback)
{
    QVariantList list;
    NetCorePrivate::coreEngine->InvokeStatic(type, method, list);
}
