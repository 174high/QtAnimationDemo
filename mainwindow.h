#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

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
    void on_startButton_clicked();
    void on_startButton_2_clicked();
    void on_startButton_3_clicked();
    void on_startButton_4_clicked();

private:

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
    unsigned char maximum;

    Ui::MainWindow *ui;
    QPropertyAnimation *pPosAnimation1;
    QPropertyAnimation *pPosAnimation2;
    QPropertyAnimation *pPosAnimation3;
    QPropertyAnimation *pPosAnimation4;
    QPropertyAnimation *pPosAnimation5;
    QParallelAnimationGroup *m_group;

    QTimer *timer;
    QTimer *timer2;
};

#endif // MAINWINDOW_H
