#include "chess.h"
#include <QApplication>

//Probably just going to use this to start game/window.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chess w;
    w.show();

    return a.exec();
}
