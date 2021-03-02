#include "start.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QFile>
#include <QHash>


start::start(QWidget *parent, QString& new_wordList_filename, QString& new_transcriptionList_filename) : QWidget(parent){
    QSize parent_size = parent->size();
    window_height = parent->height();
    window_width = parent->width();
    setUpWindow(parent_size);

    wordList_filename = &new_wordList_filename;
    transcriptionList_filename = &new_transcriptionList_filename;
    loadWordList();
    loadTranscriptionList();

}


void start::setUpWindow(QSize& size){
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("Start");
    this->resize(size);

    QString nPages = "3";
    label = new QLabel("Enter page number\nPages available: " + nPages);
    info_label = new QLabel("Waiting for commands...");
    lEdit = new QLineEdit;
    QRadioButton *eng_ru_button = new QRadioButton("English - russian", this);
    QRadioButton *ru_eng_button = new QRadioButton("Russian - english", this);
    enter = new QPushButton("Enter");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout* h_layout = new QHBoxLayout;
    QHBoxLayout* bottom_layout = new QHBoxLayout;

    connect(enter, SIGNAL(clicked()), this, SLOT(enterPressed()));

    h_layout->addWidget(eng_ru_button);
    h_layout->addWidget(ru_eng_button);
    h_layout->setSpacing(window_width/2);

    label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    label->setFont(QFont("Times New Roman", 10));

    info_label->setAlignment(Qt::AlignTop);
    info_label->setFrameStyle(QFrame::Box | QFrame::Raised);


    layout->addWidget(label);
    layout->addWidget(info_label);
    layout->addLayout(h_layout);

    bottom_layout->addWidget(lEdit);
    bottom_layout->addWidget(enter);

    layout->addLayout(bottom_layout);

    layout->setStretch(0, 1);
    layout->setStretch(1, 5);


    this->setLayout(layout);

}


void start::enterPressed(){
    QString str = lEdit->text();
    lEdit->clear();
    if(int PageN = str.toInt()){
        QHash<QString, QVector<QString>> hMap;
        QString filename = "test.txt";
        QString transFilename = "trans.txt";

        label->setBuddy(lEdit);

        current_page_hMap = this->make_dict(PageN); // take chosen page
        qDebug() << "int entered; map made";

    }
    else
        stringEntered(str);

}


void start::stringEntered(const QString& str){
    qDebug() << str;

}


void start::loadWordList(){

    QFile *word_list_file = new QFile(*wordList_filename);
    if (!word_list_file->open(QIODevice::ReadOnly))
        qDebug() << "Couldn't open " << *wordList_filename;

    QTextStream wordsStream(word_list_file);
    while (!wordsStream.atEnd()){
        QString line = wordsStream.readLine();
        wordList.push_back(line);
    }

    //qDebug() << wordList;

}


void start::loadTranscriptionList(){


    QFile *word_list_file = new QFile(*transcriptionList_filename);
    if (!word_list_file->open(QIODevice::ReadOnly))
        qDebug() << "Couldn't open " << *transcriptionList_filename;

    QTextStream wordsStream(word_list_file);
    while (!wordsStream.atEnd()){
        QString line = wordsStream.readLine();
        transcriptionList.push_back(line);
    }

    //qDebug() << transcriptionList;
}


QHash<QString, QVector<QString>> start::make_dict(const int& pageN){
    QHash<QString, QVector<QString>> hMap;

    for (int i = (pageN-1)*page_size; i < pageN*page_size; ++i){
        QVector<QString> strVect;

        QString str = wordList[i];
        QStringList list = str.split(QString(", "));

        QStringList::const_iterator constIter;
        for (constIter = ++list.begin(); constIter != list.end(); ++constIter)
            strVect.push_back(*constIter);

        hMap[list[0]] = strVect;
    }

    qDebug() << hMap;
    return hMap;
}
















































