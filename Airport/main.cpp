#include <QApplication>

#include <QDebug>

#include <QSettings>
#include <QFile>

#include "WindowStartMenu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("prop.ini");
    QString host = "";

    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
        QSettings settings("prop.ini", QSettings::IniFormat);

        settings.beginGroup("SERVER");
        settings.setValue("HOST", "http://localhost/");
        settings.endGroup();

        settings.sync();

        qDebug() << "Config file has been created!";
        exit(EXIT_FAILURE);
    }
    else
    {
        QSettings settings("prop.ini", QSettings::IniFormat);

        settings.beginGroup("SERVER");
        host = settings.value("HOST").toString();
        settings.endGroup();
    }

    WindowStartMenu winStartMenu(host);

    winStartMenu.show();

	return app.exec();
}
