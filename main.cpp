#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Models/actormodel.h"
#include "Models/mygamemap.h"
#include "Models/myquestmodel.h"
#include "Models/menumodel.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<ActorModel>("CPP", 1, 0, "ActorModel");
    qmlRegisterType<MyGameMap>("CPP",1,0,"MyGameMap");
    qmlRegisterType<MyQuestModel>("CPP",1,0,"MyQuestModel");
    qmlRegisterType<MenuModel>("CPP",1,0,"MenuModel");
   QQmlApplicationEngine engine;

    engine.addImportPath(":/qml");

    const QUrl url(QStringLiteral("qrc:/ActionSceneTest/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
