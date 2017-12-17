#include "page_change.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    page_change w;

    w.show();

    return a.exec();
}
