#pragma once
#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QLabel;


QT_BEGIN_NAMESPACE
namespace Ui { class EngApp; }
QT_END_NAMESPACE

class EngApp : public QWidget
{
    Q_OBJECT


public:
    EngApp(QWidget *parent = nullptr, int width = 600, int height = 700);
    void setUpWindow(int&, int&);
    void addButtons();
    void connect_buttons();


private:
    QVector<QString> *WordList;
    QVector<QString> *transcriptionList;
    QPushButton* setting_button;
    QPushButton* start_button;
    QPushButton* test_button;
    QPushButton* show_button;
    QVBoxLayout* menu_layout;
    QLabel* menu_label;
    QVector<QPushButton*> butt_vec;
    int window_width;
    int window_height;
    Ui::EngApp *ui;


public slots:
    void start_option();

};





























