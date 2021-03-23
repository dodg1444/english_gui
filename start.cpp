#include "start.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QFile>
#include <QRandomGenerator>
#include <QTextEdit>
#include <QTabWidget>
#include <QFileDialog>
#include <QSpinBox>
#include <QMessageBox>
#include <QColorDialog>



using namespace std;


start::start(QWidget *parent) : QWidget(parent),
                                window_height(parent->height()),
                                window_width(parent->width())
{
    QSize parent_size = parent->size();
    setUpWindow(parent_size);

}


start::~start(){ // add your brooms and scoops here
    cleanUp();
}


void start::cleanUp(){ // deletes Pair Holders from heap - don' need 'em anymo'
    QVector<PairHolder*>::iterator pIter;
    for (pIter = phVect.begin(); pIter != phVect.end(); ++pIter)
        delete *pIter;
}



void start::setUpWindow(QSize& size){ // General widget look
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("Start");
    this->resize(size);


    QString nPages = "Choose wordlist";


//    label = make_unique<QLabel>("Enter page number\nPages available: " + nPages); // not how it's done
    label = new QLabel("Pages available: " + nPages);
//    label->setStyleSheet("border-image: url(C:/QtProjects/build-Eng-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/frame_image2.png) "
//                                 "0 0 0 0 stretch stretch; ");

    wordPrintArea = new QTextEdit;

//    QPalette palette = wordPrintArea->palette(); // define pallete for textEdit..
//    palette.setColor(QPalette::Base, Qt::darkRed); // set color "Red" for textedit base
//    palette.setColor(QPalette::Text, Qt::cyan); // set text color which is selected from color pallete
//    wordPrintArea->setPalette(palette);
    wordPrintArea->setReadOnly(1);
//    wordPrintArea->setText("Waiting for wordlist...");
    wordPrintArea->setHtml("<html><head/><body><p align='center'><span><br><br>  Waiting for wordlist... </span></p></body></html>");
    wordPrintArea->setAlignment(Qt::AlignCenter);
    wordPrintArea->setFont(QFont("Times New Roman", 12));

    wordPrintArea->setAutoFillBackground(true);
    wordPrintArea->setStyleSheet("border-image: url(C:/QtProjects/build-Eng-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/frame_image4.png) "
                                 "0 0 0 0 stretch stretch; ");




    lEdit = new QLineEdit;
    lEdit->setDisabled(1);

    enter = new QPushButton("Enter");
    enter->setDisabled(1);
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout* bottom_layout = new QHBoxLayout;
    QGridLayout* grid = new QGridLayout;


    labels.push_back(label_1 = new QLabel/*("10")*/);
    labels.push_back(label_2 = new QLabel/*("21")*/);
    labels.push_back(label_3 = new QLabel/*("12")*/);
    labels.push_back(label_4 = new QLabel/*("01")*/);
    labels.push_back(label_5 = new QLabel/*("00")*/);
    labels.push_back(label_6 = new QLabel/*("22")*/);
    labels.push_back(label_7 = new QLabel/*("02")*/);
    labels.push_back(label_8 = new QLabel/*("20")*/);
    label_1->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_1->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_2->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_2->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_3->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_3->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_4->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_4->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_5->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_5->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_6->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_6->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_7->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_7->setFrameStyle(QFrame::Box | QFrame::Raised);
    label_8->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label_8->setFrameStyle(QFrame::Box | QFrame::Raised);


    label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    label->setFont(QFont("Times New Roman", 12));


    grid->addWidget(wordPrintArea, 1, 1);
    grid->addWidget(label_1,1,0);
    grid->addWidget(label_4,0,1);
    grid->addWidget(label_2,2,1);
    grid->addWidget(label_3,1,2);
    grid->addWidget(label_5, 0, 0);
    grid->addWidget(label_6, 2, 2);
    grid->addWidget(label_7, 0, 2);
    grid->addWidget(label_8, 2, 0);

    grid->setColumnStretch(1, 10);
    grid->setRowStretch(0, 2);
    grid->setRowStretch(2, 2);
    grid->setColumnStretch(0, 2);
    grid->setColumnStretch(2,2);

    grid->setSpacing(0);
    grid->setMargin(0);


    layout->addWidget(label);
    layout->addLayout(grid);

    bottom_layout->addWidget(lEdit);
    bottom_layout->addWidget(enter);

    layout->addLayout(bottom_layout);

    layout->setStretch(0, 1);
    layout->setStretch(1, 5);


    this->setLayout(layout);


    /* ADD CONNECTIONS WITHIN WIDGET HERE */
    QObject::connect(enter, SIGNAL(clicked()), this, SLOT(stringEntered()));
    QObject::connect(lEdit, SIGNAL(editingFinished()), this, SLOT(stringEntered()));

}


void start::paint_label(QLabel* label){
    int r = QRandomGenerator::global()->bounded(255);
    int g = QRandomGenerator::global()->bounded(255);
    int b = QRandomGenerator::global()->bounded(255);
    QColor col(r,g,b);
    QString str = " background-color : " ;
    str += col.name();
    label->setStyleSheet(str);
};



void start::paint_top_label(Colors color){
    switch(color){
        case(Colors::Green) : {
            label->setStyleSheet(" background-color : #2bb31e");
            break;
        }
        case(Colors::Yellow) : {
            label->setStyleSheet(" background-color : #faee05");
            break;
        }
        case(Colors::Red) : {
            label->setStyleSheet(" background-color : #d41e1e");
            break;
        }
    }
}


// ATTENTION HERE
void start::stringEntered(){ // reades input from LineEdit and .. should it delete on its own or call for a special function?
    QString str = lEdit->text();
    lEdit->clear();
    for (auto label : labels)
        paint_label(label);

    qDebug() << "you entered: " + str;
    wordPrintArea->moveCursor(QTextCursor::Start);

    switch(direction){

        case(Direction::fromRussianToEnglish) : {
            if (str == current_string){
                phVect.remove(current_PH_Number);
                label->setText("Page: " + QString::number(PageN) + "\n" + "Words left: " + QString::number(phVect.size()));
                paint_top_label(Colors::Green);
                if (phVect.size())
                    printWord();
                else
                    finishDialog();
            }

            else{
                paint_top_label(Colors::Red);
                if (phVect.size())
                    printWord();
            }
            break;
        }

        case (Direction::fromEnglishToRussian) : {
            QStringList list = str.split(QString(", ")); // should probably replace vect with list in delete function
            QVector<QString> tempVect = list.toVector(); // <---

            int before_deletion_attempt = phVect[current_PH_Number]->ruWordsVectSize();
            int after_deletion_attempt = phVect[current_PH_Number]->deleteRuWords(tempVect);
            if (before_deletion_attempt == after_deletion_attempt){
                paint_top_label(Colors::Red);
                printWord();
            }
            else if (after_deletion_attempt == 0){
                phVect.remove(current_PH_Number);
                label->setText("Page: " + QString::number(PageN) + "\n" + "Words left: " + QString::number(phVect.size()));
                paint_top_label(Colors::Green);
                if (phVect.size())
                    printWord();
                else
                    finishDialog();
            }
            else if (after_deletion_attempt < before_deletion_attempt){
//                    wordPrintArea->insertPlainText("\nCorrect, but there is more!\n");
                paint_top_label(Colors::Yellow);
                printWord();
            }
            break;
        }
    }
}


void start::printWord(){ // Prints one word from Pair Handler for user;
    current_PH_Number = QRandomGenerator::global()->bounded(phVect.size());
    wordPrintArea->moveCursor(QTextCursor::Start);
    QString txt;

    switch(direction){
        case (Direction::fromRussianToEnglish) : {
            current_string = phVect[current_PH_Number]->getEngWord();
//            wordPrintArea->insertPlainText("\n"+phVect[current_PH_Number]->getRuWords());
//            wordPrintArea->setText(phVect[current_PH_Number]->getRuWords()+"\nsdfsdf");



            txt = "<html><head/><body><p align='center'><span>"\
                + phVect[current_PH_Number]->getRuWords()\
                + "</span></p></body></html>";

            qDebug() << "txt is " << txt;
            wordPrintArea->setHtml(txt);
            wordPrintArea->setAlignment(Qt::AlignCenter);
            qDebug() << "answer is: " + current_string;
            break;
        }

        case (Direction::fromEnglishToRussian) : {
            current_string = phVect[current_PH_Number]->getRuWords();
//            wordPrintArea->insertPlainText("\n"+phVect[current_PH_Number]->getEngWord());
//            wordPrintArea->setText(phVect[current_PH_Number]->getEngWord()+"\nsdfsdf");
            if (transcriptionIsLoaded())
                txt = "<html><head/><body><p align='center'><span><br><br>"\
                    + phVect[current_PH_Number]->getEngWord()\
                    + "<br>[" + phVect[current_PH_Number]->getTransWord() + "]"\
                    + "</span></p></body></html>"; // works with encodings: UTF-16 BE with BOM

            else
                txt = "<html><head/><body><p align='center'><span><br><br>"\
                    + phVect[current_PH_Number]->getEngWord()\
                    + "</span></p></body></html>";

            qDebug() << "txt is " << txt;
            wordPrintArea->setHtml(txt);
            wordPrintArea->setAlignment(Qt::AlignCenter);
            qDebug() << "answer is: " + current_string;
            break;
        }
    }



}





void start::loadWordList(QString &new_wordList_filename){ // If the name of the function doesn't say shit than i'm helpless either;
    QFile input(new_wordList_filename);
    if (!input.open(QIODevice::ReadOnly))
        qDebug() << "Couldn't open " << new_wordList_filename;
    else{
        QTextStream wordsStream(&input);
        while (!wordsStream.atEnd())
            wordList.push_back(wordsStream.readLine());
    }
}


void start::setTranscriptionIsLoaded(bool state){
    transcriptionIsPresent = state;
}

bool start::transcriptionIsLoaded(){
    return transcriptionIsPresent;
}

void start::loadTranscriptionList(QString& new_transcriptionList_filename){ // If the name of the function doesn't say shit than i'm helpless either;
//    QFile *word_list_file = new QFile(new_transcriptionList_filename); leak
    QFile input(new_transcriptionList_filename);
    setTranscriptionIsLoaded(true);
    if (!input.open(QIODevice::ReadOnly)){
        qDebug() << "Couldn't open " << new_transcriptionList_filename;
        setTranscriptionIsLoaded(false);
    }
    QTextStream wordsStream(&input);
    while (!wordsStream.atEnd()){
        QString line = wordsStream.readLine();
        transcriptionList.push_back(line);
    }
    //qDebug() << transcriptionList;
}



void start::make_PairHolders(){ // Creates vector of PairHolders with page number given;
//    QVector<PairHolder*> phVect;
    QString str;
    QVector<QString> strVect;
    QString transcription;
    phVect.clear();

    for (int i = (PageN-1)*page_size; i < PageN*page_size; ++i){
//        QVector<QString> strVect; // strVect.clear() cheaper than constructing new vector each time

        QStringList list = wordList[i].split(QString(", "));

        QStringList::iterator slIter;
        slIter = list.begin();
        str = *slIter;
        qDebug() << str;

        for (slIter = ++list.begin(); slIter != list.end(); ++slIter)
            strVect.push_back(*slIter);

        qDebug() << strVect;

        if (transcriptionIsLoaded()) {
            transcription = transcriptionList[i].split(QString(" - "))[1]; // takes string "word - trans",
            qDebug() << "transcription word is :" << transcription;
        }                                                                                        //splits is and returns transcription
        PairHolder *pair_holder = new PairHolder(str, strVect, transcription);
        phVect.push_back(pair_holder);

        strVect.clear();
    }
}


void start::setWordListPath(const QString& new_path){ // slot; sets new wordlist path to current;
    wordList_filename = new_path;
    qDebug() << "start changed wordlist path to: " << wordList_filename;
    loadWordList(wordList_filename);
    nPages = wordList.size()/page_size;
    if (wordList.size() >  0)
        emit sendAmountOfWords(wordList.size());
    label->setText("Pages available: " + QString::number(nPages));
    wordPrintArea->setText("Waiting for a page number...");

};


void start::setTransListPath(const QString& new_path){ // slot; sets new transcription list path for current;
    transcriptionList_filename = new_path;
    qDebug() << "start changed translist path to: " << transcriptionList_filename;

    loadTranscriptionList(transcriptionList_filename);
};


void start::getChosenPageNumber(const int& new_page_number){ // guess what;

    PageN = new_page_number;
    qDebug() << "START chosen page number set to: " << PageN;
};


void start::getPageSize(const int& new_page_size){
    page_size = new_page_size;
    qDebug() << "START Page size changed to: " << page_size;
};


void start::getDirection(Direction new_direction){
    direction = new_direction;
    switch(direction){
        case(Direction::fromEnglishToRussian) : qDebug() << "START direction set to: fromEnglishToRussian"; break;
        case(Direction::fromRussianToEnglish) : qDebug() << "START direction set to: fromRussianToEnglish"; break;
    }
    startPage();
    lEdit->setEnabled(1);
    enter->setEnabled(1);
    label->setText("Page: " + QString::number(PageN) + "\n" + "Words left: " + QString::number(phVect.size()));
}


void start::startPage(){
    make_PairHolders();
    wordPrintArea->clear();
    printWord();
}


void start::finishDialog(){
    lEdit->setDisabled(1);
    enter->setDisabled(1);
    QMessageBox::StandardButton resButton = QMessageBox::question( this, "app",
                                                                  tr("Finished!\nTime spent: \nStart over?\n"),
                                                                  QMessageBox::Yes | QMessageBox::Cancel);
    if (resButton == QMessageBox::Yes) {
        lEdit->setEnabled(1);
        enter->setEnabled(1);
        startPage();
        label->setText("Page: " + QString::number(PageN) + "\n" + "Words left: " + QString::number(phVect.size()));
    } else {
        wordPrintArea->setText("Waiting for wordlist...");

        wordPrintArea->setText("Waiting for wordlist...");
        label->setText("Page finished");
    }
}

































settings::settings(QWidget* parent) : QWidget(parent){
    window_height = parent->height();
    window_width = parent->width();

    QSize size = parent->size();
    setUpWindow(size);


};


// HEY! Add words separator?

void settings::setUpWindow(QSize& size){ // General widget look
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("Settings");
    this->resize(size);

    mainListDialog = new QFileDialog(this, "Choose a word list");
    mainListDialog->setFileMode(QFileDialog::AnyFile);
    mainListDialog->setViewMode(QFileDialog::Detail);

    transListDialog = new QFileDialog(this, "Choose a transcription list");
    transListDialog->setFileMode(QFileDialog::AnyFile);
    transListDialog->setViewMode(QFileDialog::Detail);

    QHBoxLayout* h_layout1 = new QHBoxLayout;
    QHBoxLayout* h_layout2 = new QHBoxLayout;
    QHBoxLayout* h_layout3 = new QHBoxLayout;
    QHBoxLayout* h_layout4 = new QHBoxLayout;
    QHBoxLayout* h_layout5 = new QHBoxLayout;

    mainFileName = new QLabel(this);
    mainFileName->setText("File not chosen");
    mainFileName->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    mainFileName->setFrameStyle(QFrame::Box | QFrame::Raised);

    transFileName = new QLabel(this);
    transFileName->setText("File not chosen");
    transFileName->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    transFileName->setFrameStyle(QFrame::Box | QFrame::Raised);


    pageSizeBox = new QSpinBox(this);
    pageSizeBox->setPrefix("Page size: ");
    pageSizeBox->setDisabled(1);

    eng_ru_button = new QRadioButton("from English - to Russian", this);
    eng_ru_button->setDisabled(1);
    ru_eng_button = new QRadioButton("from Russian - to English", this);
    ru_eng_button->setDisabled(1);

    pageNumberBox = new QSpinBox(this);
    pageNumberBox->setPrefix("Page number: ");
    pageNumberBox->setDisabled(1);

    enter = new QPushButton("Apply", this);
    enter->setDisabled(1);

    h_layout1->addWidget(mainFileName);
    h_layout1->addWidget(loadMainFile = new QPushButton("Choose a word list"));


    h_layout2->addWidget(transFileName);
    h_layout2->addWidget(loadTransFile = new QPushButton("Choose a transcription list"));

    h_layout3->addWidget(pageSizeBox);
    h_layout3->addWidget(pageNumberBox);

    h_layout4->addWidget(eng_ru_button, 0, Qt::AlignHCenter);
    h_layout4->addWidget(ru_eng_button, 0, Qt::AlignHCenter);


    h_layout5->addWidget(enter, 0, Qt::AlignRight);

// preview widget

    layout = new QVBoxLayout(this);
    layout->addLayout(h_layout1);
    layout->addLayout(h_layout2);
    layout->addLayout(h_layout3);
    layout->addLayout(h_layout4);
    layout->addLayout(h_layout5);

    setLayout(layout);


    /* ADD CONNECTIONS WITHIN WIDGET HERE */
    QObject::connect(loadMainFile, SIGNAL(clicked()), this, SLOT(setWordListPath())); // get wordlist path when chosen
    QObject::connect(loadTransFile, SIGNAL(clicked()), this, SLOT(setTransListPath())); // get translist path when chosen
    QObject::connect(pageSizeBox, SIGNAL(valueChanged(int)), this, SLOT(getPageSize(int)));
    QObject::connect(pageNumberBox, SIGNAL(valueChanged(int)), this, SLOT(getChosenPage(int))); // get page number when chosen
    QObject::connect(eng_ru_button, SIGNAL(clicked(bool)), this, SLOT(setEngRuDirection(bool)));
    QObject::connect(ru_eng_button, SIGNAL(clicked(bool)), this, SLOT(setRuEngDirection(bool)));
    // radio button1
    // radio button2
    QObject::connect(enter, SIGNAL(clicked()), this, SLOT(sendData())); // send data when files and page are chosen;


}
/*
  Plan of signal-slots actions:
1) set list(s) and send to start, get amount of pages in return;
2) set page size, count possible amount of pages;
3) set page number limit according to page size;
4) set translation direction
5) apply and send page_size and page_number to start with direction;
*/


void settings::setWordListPath(){ // slot; chooses wordlist and sends it to start widget;
    wordListPath = mainListDialog->getOpenFileName();
    (wordListPath == 0) ? mainFileName->setText("No file chosen") : mainFileName->setText(QFileInfo(wordListPath).fileName());
    emit sendWordListPath(wordListPath);
    qDebug() << "Wordlist path: " + wordListPath;
}


void settings::setTransListPath(){ // slot; chooses translist and sends it to start widget;
    transListPath = transListDialog->getOpenFileName();
    (transListPath == 0) ? transFileName->setText("No file chosen") : transFileName->setText(QFileInfo(transListPath).fileName());
    emit sendTransListPath(transListPath);
    qDebug() << "Translist path: " + transListPath;
}


void settings::sendData(){
    qDebug() << "sendData slot called";
    emit sendPageSize(page_size);
    emit sendChosenPageNumber(chosen_page);
    emit sendDirection(direction);
}


void settings::getAmountOfWords(const int& nWords){ // slot; adds option to ComboBox for each page;
    amount_of_pages = nWords/page_size;
    amount_of_words = nWords;
    pageNumberBox->setEnabled(1);
    pageSizeBox->setEnabled(1);
    enter->setEnabled(1);
    eng_ru_button->setEnabled(1);
    ru_eng_button->setEnabled(1);
    qDebug() << "SETTINGS amount of words: " << amount_of_words;
    pageNumberBox->setRange(1, amount_of_pages);
    pageSizeBox->setRange(1, nWords);
}


void settings::getChosenPage(int page){ // well, obvious
    chosen_page = page;
    qDebug() << "START chosen page changed to: " << chosen_page;
}


void settings::getPageSize(int size){
    page_size = size;
    qDebug() << "SETTINGS Page size changed to: " << page_size;
    amount_of_pages = amount_of_words/page_size;
    pageNumberBox->setRange(1, amount_of_pages);

}


void settings::setRuEngDirection(bool condition){
    if (condition){
        direction = Direction::fromRussianToEnglish;
        qDebug() << "SETTINGS direction set to Direction::fromRussianToEnglish";
    }
}


void settings::setEngRuDirection(bool condition){
    if (condition){
        direction = Direction::fromEnglishToRussian;
        qDebug() << "SETTINGS direction set to Direction::fromEnglishToRussian";
    }
}




















PairHolder::PairHolder(QString& eng_word, QVector<QString>& ru_words, QString& trans)
    : engWord(eng_word), ruWords(ru_words), transcription(trans){};


int PairHolder::deleteRuWords(QVector<QString>& words){ // searches for a match of entered word(s) and deletes it;
                                                        // return size indicates changes (considered to use bool but it seemed to be more descriptive)
    for (const QString& word : words){
        if (ruWords.removeOne(word))
            qDebug() << "Just removed " << word;
    }
    return ruWords.size();
}



QString PairHolder::getRuWords(){
    QString str = "<br><br>";
    for (const QString& x : ruWords)
        str += x + "<br>";
    return str;
}


QString PairHolder::getEngWord(){
    return engWord;
}


QString PairHolder::getTransWord(){
    return transcription;
}

int PairHolder::ruWordsVectSize(){
    return ruWords.size();
}






















Union::Union(QWidget* parent) : QWidget(parent){
    settings_widget = new settings(this);
//    QFont* settings_font = new QFont("Courier", 10, QFont::StyleNormal);
//    settings_widget->setFont(*settings_font);


    start_widget = new start(this);


    tabs = new QTabWidget(this);
    tabs->addTab(start_widget, "Test");
    tabs->addTab(settings_widget, "Settings");

    layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    setLayout(layout);
    resize(600, 700);


    /* ADD CONNECTIONS BETWEEN WIDGETS HERE */
    QObject::connect(settings_widget, SIGNAL(sendWordListPath(const QString&)), start_widget, SLOT(setWordListPath(const QString&)));
    QObject::connect(settings_widget, SIGNAL(sendTransListPath(const QString&)), start_widget, SLOT(setTransListPath(const QString&)));

    QObject::connect(start_widget, SIGNAL(sendAmountOfWords(const int&)), settings_widget, SLOT(getAmountOfWords(const int&)));
    QObject::connect(settings_widget, SIGNAL(sendPageSize(int)), start_widget, SLOT(getPageSize(int)));
    QObject::connect(settings_widget, SIGNAL(sendChosenPageNumber(const int&)), start_widget, SLOT(getChosenPageNumber(const int&)));
    QObject::connect(settings_widget, SIGNAL(sendDirection(Direction)), start_widget, SLOT(getDirection(Direction)));



};






































