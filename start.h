#pragma once
#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;
class QTextEdit;
class QComboBox;
class QFileDialog;
class QTabWidget;
class QVBoxLayout;
class QSpinBox;
class QRadioButton;

using namespace std;

class PairHolder;

enum class Direction {fromEnglishToRussian, fromRussianToEnglish};
enum class Colors {Green, Yellow, Red};


class start : public QWidget{
    Q_OBJECT

public:
    start(QWidget *parent = 0);
    ~start();
    void cleanUp();
    void setUpWindow(QSize&);

    /////////// When in Progress /////////
    void loadWordList(QString& new_wordList_filename);
    void loadTranscriptionList(QString& new_transcriptionList_filename);

    void printWord();
    void paint_label(QLabel* label);

    void setTranscriptionIsLoaded(bool);
    bool transcriptionIsLoaded();

    void paint_top_label(Colors);

protected:
    void make_PairHolders();
    void startPage();
    void finishDialog();


private:

    Direction direction;

    QLabel *label;
    QTextEdit *wordPrintArea;
    QPushButton *enter;
    QLineEdit *lEdit; // signal editingFinished()

    int window_height;
    int window_width;


    /////////// When in Progress /////////
    QString current_string;

    QString wordList_filename;
    QString transcriptionList_filename;
    QVector<QString> wordList;
    QVector<QString> transcriptionList;
    QVector<PairHolder*> phVect;
    int nPages = 0; // amount of pages
    int page_size = 10; // size of a page
    int current_PH_Number = 0; // current page holder number
    int PageN = 0; // page number

    bool transcriptionIsPresent = false;

    QVector<QLabel*> labels;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;

public slots:
    void stringEntered();
    void setWordListPath(const QString&);
    void setTransListPath(const QString&);

    void getChosenPageNumber(const int&);
    void getPageSize(const int&);
    void getDirection(Direction);

signals:
    void sendAmountOfWords(int);


};




























class settings : public QWidget{
    Q_OBJECT

public:
    settings(QWidget* parent = 0);
    void setUpWindow(QSize& size);


private:
    Direction direction;

    QLabel* mainFileName;
    QLabel* transFileName;
    QLabel* pageNumberLabel;
    QSpinBox* pageSizeBox;
    QSpinBox* pageNumberBox;
    QPushButton* loadMainFile;
    QPushButton* loadTransFile;
    QPushButton* enter;
    QFileDialog* mainListDialog;
    QFileDialog* transListDialog;
    QRadioButton* eng_ru_button;
    QRadioButton* ru_eng_button;
    QVBoxLayout* layout;

    QString wordListPath;
    QString transListPath;

    int window_height;
    int window_width;

    int amount_of_pages = 0;
    int chosen_page = 0;

    int page_size = 10;
    int amount_of_words = 0;


public slots:
    void setWordListPath();
    void setTransListPath();
    void sendData();

    void getAmountOfWords(const int&);
    void getChosenPage(int);
    void getPageSize(int);
    void setRuEngDirection(bool);
    void setEngRuDirection(bool);

signals:
    void pageChanged(int newPage);
    void sendWordListPath(const QString&);
    void sendTransListPath(const QString&);
    void sendChosenPageNumber(const int&);
    void sendPageSize(int);
    void sendDirection(Direction);

};












class PairHolder{
public:
    PairHolder(QString&, QVector<QString>&, QString&); // should it also hold transctiption?
    int deleteRuWords(QVector<QString>&); // returns amount of ru words left;

    QString getRuWords();
    QString getEngWord();
    QString getTransWord();
    int ruWordsVectSize();

private:
    QString engWord;
    QVector<QString> ruWords;
    QString transcription;
};

















class Union : public QWidget{
    Q_OBJECT

public:
    Union(QWidget* parent = 0);

private:
    QTabWidget* tabs;
    start *start_widget;
    settings *settings_widget;
    QVBoxLayout* layout;
};































