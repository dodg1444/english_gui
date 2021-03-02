#include "engapp.h"
#include "start.h"
#include "ui_engapp.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

EngApp::EngApp(QWidget *parent, int height, int width) : QWidget(parent){

    addButtons();
    setUpWindow(height, width);
    connect_buttons();
}


void EngApp::addButtons(){
    butt_vec.push_back(start_button = new QPushButton("Start", this));
    butt_vec.push_back(show_button = new QPushButton("Show Pages", this));
    butt_vec.push_back(test_button = new QPushButton("Test", this));
    butt_vec.push_back(setting_button = new QPushButton("Settings", this));
}



void EngApp::connect_buttons(){
    connect(start_button, SIGNAL(clicked()), this, SLOT(start_option()));
};


void EngApp::setUpWindow(int& height, int& width){
    window_height = height;
    window_width = width;
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("English App");
    this->resize(window_height, window_width);

    menu_layout = new QVBoxLayout;
    menu_label = new QLabel("Push a Button!", this);
    menu_label->setAlignment(Qt::AlignCenter);
    menu_label->setLineWidth(2);
    menu_label->setFixedHeight(window_height/5);
    menu_label->setFrameStyle(QFrame::Box | QFrame::Raised);
    menu_label->setFont(QFont("Times New Roman", 20, QFont::Bold));


    menu_layout->addWidget(menu_label);
    for (auto button : butt_vec){
        button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        menu_layout->addWidget(button);
    }
    menu_layout->setSpacing(10);


    this->setLayout(menu_layout);
}


void EngApp::start_option(){
    QString filename = "test.txt";
    QString transFilename = "trans.txt";
    start *start_window = new start(this, filename, transFilename);
    start_window->show();
//    this->hide();
}




































