#include "engapp.h"
#include <QApplication>
#include <QTextStream>
#include <QTextCodec>

#include <start.h>





void StartApp(){
    QWidget *parent = new QWidget;
    EngApp *engapp = new EngApp(parent, 600, 700); // width, height
    engapp->show();
}


//void testProgram(){
//    QString filename = "test.txt";
//    QString transFilename = "trans.txt";
//    start *start_page = new start(filename, transFilename);
//}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

   StartApp();
   // testProgram();

    return app.exec();
}






















