#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "../QtNetCorePlugin/netcore.h"

int wmain(int argc, wchar_t *argv[])
{
    NetCore::initializeCoreEngine(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
