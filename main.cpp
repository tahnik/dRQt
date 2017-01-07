#include "resizablewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ResizableWindow w;
    w.show();

    return a.exec();
}
