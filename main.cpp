#include "resizablewindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ResizableWindow w;
    w.show();

    return a.exec();
}
