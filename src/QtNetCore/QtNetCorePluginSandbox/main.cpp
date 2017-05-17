#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include "netcore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<NetCore>("QtNetCore", 1, 0, "NetCore");

    QQmlApplicationEngine engine;

    NetCore::CreateCoreCLR(app.arguments());

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    int result = app.exec();

    NetCore::DestroyCoreCLR();

    return result;
}
