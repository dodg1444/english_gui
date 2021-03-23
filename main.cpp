#include "engapp.h"
#include <QApplication>
#include <start.h>








int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EngApp engapp;
    engapp.show();


    return app.exec();
}






















