#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black;");
//    ui->posButton_1->setStyleSheet("background-color:black;");

    center_line=80 ; 
    start_line=-600 ;
    end_line= 100; 
//    current_floor_line= ;
    interval=50;     
    floor_long=71;
    floor_width=61; 

    maximum=5; 
    current_floor=0; 

    ui->textEdit->setText("1");
    ui->textEdit->show();

    //scale
/*    QPropertyAnimation *pScaleAnimation1 = new QPropertyAnimation(ui->scaleButton, "geometry");
    pScaleAnimation1->setDuration(1000);
    pScaleAnimation1->setStartValue(QRect(190, 230, 0, 0));
    pScaleAnimation1->setEndValue(QRect(120, 160, 140, 140));
    pScaleAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

    QPropertyAnimation *pScaleAnimation2 = new QPropertyAnimation(ui->scaleButton, "geometry");
    pScaleAnimation2->setDuration(1000);
    pScaleAnimation2->setStartValue(QRect(120, 160, 140, 140));
    pScaleAnimation2->setEndValue(QRect(190, 230, 0, 0));
    pScaleAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

    QSequentialAnimationGroup *pScaleGroup = new QSequentialAnimationGroup(this);
    pScaleGroup->addAnimation(pScaleAnimation1);
    pScaleGroup->addAnimation(pScaleAnimation2);
*/

    ui->posButton_1->setGeometry(QRect(center_line, start_line, floor_long, floor_width));
    ui->posButton_2->setGeometry(QRect(center_line, start_line-interval*1, floor_long, floor_width));
    ui->posButton_3->setGeometry(QRect(center_line, start_line-interval*2, floor_long, floor_width));
    ui->posButton_4->setGeometry(QRect(center_line, start_line-interval*3, floor_long, floor_width));
    ui->posButton_5->setGeometry(QRect(center_line, start_line-interval*4, floor_long, floor_width));


    ui->pushButton_current_floor->setGeometry(QRect(240, 215, 101, 31));

    setMove();


    pPosAnimation1->start();
    pPosAnimation2->start();
 //   pPosAnimation3->start();
//    pPosAnimation4->start();
//    pPosAnimation5->start();

//    QPropertyAnimation *pPosAnimation2 = new QPropertyAnimation(ui->posButton, "pos");
//    pPosAnimation2->setDuration(1000);
//    pPosAnimation2->setStartValue(QPoint(360, 350));
//    pPosAnimation2->setEndValue(QPoint(360, 160));
//    pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

//    QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
//    pPosGroup->addPause(500);
//    pPosGroup->addAnimation(pPosAnimation1);


//    pPosGroup->addAnimation(pPosAnimation2);

    //opacity
/*    QGraphicsOpacityEffect *pButtonOpacity = new QGraphicsOpacityEffect(this);
    pButtonOpacity->setOpacity(1);
    ui->opasityButton->setGraphicsEffect(pButtonOpacity);

    QPropertyAnimation *pOpacityAnimation1 = new QPropertyAnimation(pButtonOpacity, "opacity");
    pOpacityAnimation1->setDuration(1000);
    pOpacityAnimation1->setStartValue(1);
    pOpacityAnimation1->setEndValue(0);

    QPropertyAnimation *pOpacityAnimation2 = new QPropertyAnimation(pButtonOpacity, "opacity");
    pOpacityAnimation2->setDuration(1000);
    pOpacityAnimation2->setStartValue(0);
    pOpacityAnimation2->setEndValue(1);

    QSequentialAnimationGroup *pOpacityGroup = new QSequentialAnimationGroup(this);
    pOpacityGroup->addPause(1000);
    pOpacityGroup->addAnimation(pOpacityAnimation1);
    pOpacityGroup->addAnimation(pOpacityAnimation2);
*/
//    m_group = new QParallelAnimationGroup(this);
//    m_group->addAnimation(pScaleGroup);
//    m_group->addAnimation(pPosGroup);
 //   m_group->addAnimation(pOpacityGroup);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMove()
{
    pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
    pPosAnimation1->setDuration(3000);
    pPosAnimation1->setStartValue(QPoint(center_line, start_line-interval*0)); 
    pPosAnimation1->setEndValue(QPoint(center_line, 100));
    pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
    pPosAnimation2->setDuration(3000);
    pPosAnimation2->setStartValue(QPoint(center_line, start_line-interval*1));
    pPosAnimation2->setEndValue(QPoint(center_line, 100-interval*1));
    pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
/*
    pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
    pPosAnimation3->setDuration(3000);
    pPosAnimation3->setStartValue(QPoint(center_line, start_line-interval*2));
    pPosAnimation3->setEndValue(QPoint(center_line, end_line-interval*2));
    pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
    pPosAnimation4->setDuration(3000);
    pPosAnimation4->setStartValue(QPoint(center_line, start_line-interval*3));
    pPosAnimation4->setEndValue(QPoint(center_line, end_line-interval*3));
    pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
    pPosAnimation5->setDuration(3000);
    pPosAnimation5->setStartValue(QPoint(center_line, start_line-interval*4));
    pPosAnimation5->setEndValue(QPoint(center_line, end_line-interval*4));
    pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
*/
}

void MainWindow::setMoveUp()
{
    char offset1,offset2,offset3,offset4,offset5; 
   
    int start_line1=100,start_line2=300,stand_line=200; 

    offset1=current_floor-1 ; 

    if(offset1==0)    
    {
    	pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
    	pPosAnimation1->setDuration(3000);
    	pPosAnimation1->setStartValue(QPoint(center_line, start_line1));
    	pPosAnimation1->setEndValue(QPoint(center_line, stand_line));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==1)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);
        pPosAnimation1->setStartValue(QPoint(center_line, stand_line));
        pPosAnimation1->setEndValue(QPoint(center_line, start_line2));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=2)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);
        pPosAnimation1->setStartValue(QPoint(center_line, start_line2+interval*(offset1-2)));
        pPosAnimation1->setEndValue(QPoint(center_line, start_line2+interval*(offset1-1)));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }


    if(offset1==0)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);
        pPosAnimation2->setStartValue(QPoint(center_line, start_line1-interval));
        pPosAnimation2->setEndValue(QPoint(center_line, start_line1));
        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    if(offset1==1)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);
        pPosAnimation2->setStartValue(QPoint(center_line, start_line1));
        pPosAnimation2->setEndValue(QPoint(center_line, stand_line));
        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==2)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);
        pPosAnimation2->setStartValue(QPoint(center_line, stand_line));
        pPosAnimation2->setEndValue(QPoint(center_line, start_line2));
        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=3)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);
        pPosAnimation2->setStartValue(QPoint(center_line, start_line2+interval*(offset1-3)));
        pPosAnimation2->setEndValue(QPoint(center_line, start_line2+interval*(offset1-2)));
        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }



/*
    pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
    pPosAnimation2->setDuration(3000);
    pPosAnimation2->setStartValue(QPoint(center_line, start_line-interval*1));
    pPosAnimation2->setEndValue(QPoint(center_line, start_line-interval*1+interval));
    pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);


    pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
    pPosAnimation3->setDuration(3000);
    pPosAnimation3->setStartValue(QPoint(center_line, start_line-interval*2));
    pPosAnimation3->setEndValue(QPoint(center_line, start_line-interval*2+interval));
    pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
    pPosAnimation4->setDuration(3000);
    pPosAnimation4->setStartValue(QPoint(center_line, start_line-interval*3));
    pPosAnimation4->setEndValue(QPoint(center_line, start_line-interval*3+interval));
    pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);


    pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
    pPosAnimation5->setDuration(3000);
    pPosAnimation5->setStartValue(QPoint(center_line, start_line-interval*4));
    pPosAnimation5->setEndValue(QPoint(center_line, start_line-interval*4+interval));
    pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);

*/

}

void MainWindow::setMoveDown()
{
    pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
    pPosAnimation1->setDuration(3000);
    pPosAnimation1->setStartValue(QPoint(center_line, start_line-interval*0));
    pPosAnimation1->setEndValue(QPoint(center_line, start_line-interval*0-interval));
    pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
    pPosAnimation2->setDuration(3000);
    pPosAnimation2->setStartValue(QPoint(center_line, start_line-interval*1));
    pPosAnimation2->setEndValue(QPoint(center_line, start_line-interval*1-interval));
    pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
    pPosAnimation3->setDuration(3000);
    pPosAnimation3->setStartValue(QPoint(center_line, start_line-interval*2));
    pPosAnimation3->setEndValue(QPoint(center_line, start_line-interval*2-interval));
    pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
    pPosAnimation4->setDuration(3000);
    pPosAnimation4->setStartValue(QPoint(center_line, start_line-interval*3));
    pPosAnimation4->setEndValue(QPoint(center_line, start_line-interval*3-interval));
    pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
    pPosAnimation5->setDuration(3000);
    pPosAnimation5->setStartValue(QPoint(center_line, start_line-interval*4));
    pPosAnimation5->setEndValue(QPoint(center_line, start_line-interval*4-interval));
    pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);

}




void MainWindow::on_startButton_clicked()
{

    start_line=-600 ;
    end_line=100;
    current_floor=0; 

    setMove();

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();

//    m_group->setDirection(QAbstractAnimation::Forward);
//    m_group->setLoopCount(1);
//    m_group->start();
}

void MainWindow::on_startButton_3_clicked()
{
    if(current_floor>=maximum)
    return;

    start_line=end_line;
    end_line=end_line+interval;
    current_floor++; 

    setMoveUp();

    pPosAnimation1->start();
    pPosAnimation2->start();
//    pPosAnimation3->start();
//    pPosAnimation4->start();
//    pPosAnimation5->start();

//    printf("current floor=%d",ui->textEdit->toPlainText());


//    m_group->setDirection(QAbstractAnimation::Backward);
//    m_group->setLoopCount(1);
//    m_group->start();
}

void MainWindow::on_startButton_2_clicked()
{
    if(current_floor<=1)
    return; 

    start_line=end_line;
    current_floor--; 

    setMoveDown();
    end_line=end_line-interval;

    pPosAnimation1->start();
 //   pPosAnimation2->start();
//    pPosAnimation3->start();
//    pPosAnimation4->start();
//    pPosAnimation5->start();


//    m_group->setDirection(QAbstractAnimation::Forward);
//    m_group->setLoopCount(-1);
//    m_group->start();
}

void MainWindow::on_startButton_4_clicked()
{
    int b = ui->textEdit->toPlainText().toInt();

    qDebug() << b;

    start_line=end_line;
    end_line=end_line-(current_floor-b)*interval;
    current_floor=b;

    setMove();

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();


//    m_group->setDirection(QAbstractAnimation::Forward);
//    m_group->setLoopCount(-1);
//    m_group->start();
}

