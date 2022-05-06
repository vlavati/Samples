#include <QGuiApplication>
#include <QDebug>
#include <QtQml>
#include "cproductsviewmodel.h"
#include "ceditviewmodel.h"
#include "cviewmodelfactory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<CProductsViewModel>("com.mycompany.qmlapp", 1, 0, "CProductsViewModel");
    qmlRegisterType<CEditViewModel>("com.mycompany.qmlapp", 1, 0, "CEditViewModel");

    CViewModelFactory factory;

    factory.add("products2", []() { return new CProductsViewModel(); } );
    factory.add("edit", []() { return new CEditViewModel(); } );
    engine.rootContext()->setContextProperty("g_factory", &factory);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    try {
        return app.exec();
    }
    catch (std::runtime_error &ex)
    {
        qDebug() << "Exception is raised" << ex.what();
    }
    return 1;
}
