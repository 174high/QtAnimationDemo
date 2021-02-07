#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <string>

using namespace std;

enum status{up,down,runing,stop} ; 

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setMove();
    void setMoveUp(bool up);
    void updateAction();
    void setMoveDown();
    void carStopIndicator();
    void carStatusIndicator();
    void bookedFloorsAction();
    void on_startButton_clicked();
    void on_startButton_2_clicked();
    void on_startButton_3_clicked();
    void on_startButton_4_clicked();

    string to_String(int n);
    void sortA1(int a[], int length);
    void sortA2(int a[], int length);

private:
    enum status car_status; 

    int start_line1;
    int start_line2;
    int stand_line;

    int center_line; 
    int start_line;
    int end_line;
    unsigned char interval;
    unsigned int floor_long;
    unsigned int floor_width; 
    unsigned char current_floor; 
    unsigned char next_floor;
    unsigned char maximum;

    int booked_fixxed_line1;
    int booked_start1_line1;   
    int booked_start1_line2; 
    int booked_start1_line3;
    int booked_start1_line4;

    int booked_fixxed_line2;
    int booked_start2_line1;
    int booked_start2_line2;
    int booked_start2_line3;
    int booked_start2_line4;

    unsigned char booked_num;
    unsigned char next_booked_floors_num;
    unsigned char current_booked_floors_num;

    unsigned char booked_floors[30]; 

    Ui::MainWindow *ui;
    QPropertyAnimation *pPosAnimation1;
    QPropertyAnimation *pPosAnimation2;
    QPropertyAnimation *pPosAnimation3;
    QPropertyAnimation *pPosAnimation4;
    QPropertyAnimation *pPosAnimation5;
    QParallelAnimationGroup *m_group;

    QPropertyAnimation *pPosAnimation_booked1;
    QPropertyAnimation *pPosAnimation_booked2;

    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;

    QFont booked1_font;
    QFont booked2_font;
    QFont booked3_font;
    QFont booked4_font;
};

#endif // MAINWINDOW_H
