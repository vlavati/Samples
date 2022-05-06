#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));

    return application.exec();
}
