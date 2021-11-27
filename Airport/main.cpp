#include <QApplication>

#include <QDebug>

#include "WindowStartMenu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WindowStartMenu winStartMenu;

    winStartMenu.show();

	return app.exec();
}
