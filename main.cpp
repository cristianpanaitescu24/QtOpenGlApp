#include "MainWindow.h"
#include <QApplication>
#include <QImage>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w; // declaration or variable named "w" being a member of class MainWindow
    w.show();
    return app.exec();
}


