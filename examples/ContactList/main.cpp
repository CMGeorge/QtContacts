#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <contactslist.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<ContactsListModel>("net.reea",0,1,"ContactsModel");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
