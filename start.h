#pragma once
#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;

class start : public QWidget{
    Q_OBJECT

public:
    start(QWidget *parent, QString& new_wordList_filename, QString& new_transcriptionList_filename);
    void setUpWindow(QSize&);

    /////////// When in Progress /////////
    void loadWordList();
    void loadTranscriptionList();
    QHash<QString, QVector<QString>> make_dict(const int&);

private:
    QLabel *label;
    QLabel *info_label;
    QPushButton *enter;
    QLineEdit *lEdit; // signal editingFinished()

    int window_height;
    int window_width;


    /////////// When in Progress /////////
    QHash<QString, QVector<QString>> current_page_hMap;
    QString current_string;
////
    const QString *wordList_filename;
    const QString *transcriptionList_filename ;
    QVector<QString> wordList;
    QVector<QString> transcriptionList;
    int nPages; //
    int page_size = 10;

public slots:
    void enterPressed();
    void stringEntered(const QString&);

};

/*
what if there is hMap that holds a current page;
when editingFinished() send it [signal] to slot that reads from lEdit
and compares the string with  current word which is also some private
QString; If they're equal delete that word or <key, value>pair
from current hMap; proceed until hMap is empty;
*/





































