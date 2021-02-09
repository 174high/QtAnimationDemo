#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QTimer>
#include <unistd.h>
#include <iostream>   // std::cout  
#include <string> 
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black;");
//    ui->posButton_1->setStyleSheet("background-color:black;");
   
    start_line1=130 ;
    start_line2=270 ;
    stand_line=200  ;

    center_line=80 ; 
    start_line=-600 ;
    end_line= 130; 
    interval=50;     
    floor_long=71;
    floor_width=61; 

    maximum=5; 
    current_floor=0; 
    booked_num=0;
    current_booked_floors_num=0;

    booked_fixxed_line1=10;
    booked_start1_line1=80;
    booked_start1_line2=60;

    booked_fixxed_line2=20;
    booked_start2_line1=140;
    booked_start2_line2=120;


    ui->textEdit->setText("4");
    ui->textEdit->show();
 
    Size dsize;
    Mat img_up = imread("./resources/image/up.png");
    dsize = Size(80, 40);
    matData_up = Mat(dsize, CV_32S);
    cv::resize(img_up, matData_up, dsize);
    imgLabel_up = new QLabel(this);
    imgLabel_up->setGeometry(75,85,80,40);
    imgLabel_up->setStyleSheet("background-color:black;");


    Mat img_down = imread("./resources/image/down.png");
    dsize = Size(80, 40);
    matData_down = Mat(dsize, CV_32S);
    cv::resize(img_down, matData_down, dsize);
    imgLabel_down = new QLabel(this);
    imgLabel_down->setGeometry(75,380,80,40);
    imgLabel_down->setStyleSheet("background-color:black;");


    pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
    pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
    pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
    pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
    pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
    pPosAnimation_booked1 = new QPropertyAnimation(ui->posButton_11, "pos");
    pPosAnimation_booked2 = new QPropertyAnimation(ui->posButton_12, "pos");

    booked1_font.setPointSize(40);
    booked2_font.setPointSize(30);
    booked3_font.setPointSize(20);
    booked4_font.setPointSize(10);

    for(unsigned char i=0;i<maximum;i++)
    {
	booked_floors[i]=255;
    }

    ui->posButton_1->setGeometry(QRect(center_line, start_line, floor_long, floor_width));
    ui->posButton_2->setGeometry(QRect(center_line, start_line-interval*1, floor_long, floor_width));
    ui->posButton_3->setGeometry(QRect(center_line, start_line-interval*2, floor_long, floor_width));
    ui->posButton_4->setGeometry(QRect(center_line, start_line-interval*3, floor_long, floor_width));
    ui->posButton_5->setGeometry(QRect(center_line, start_line-interval*4, floor_long, floor_width));
 
    ui->currentFloorButton->setGeometry(QRect(78, 198, 80, 70));

    timer = new QTimer(this) ;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAction()));
    timer2 = new QTimer(this) ;
    connect(timer2, SIGNAL(timeout()), this, SLOT(on_startButton_4_clicked()));
    timer3 = new QTimer(this) ;
    connect(timer3, SIGNAL(timeout()), this, SLOT(bookedFloorsAction()));
    timer3->start(500);
    timer4 = new QTimer(this) ;
    connect(timer4, SIGNAL(timeout()), this, SLOT(carStatusIndicator()));
    timer4->start(200);
    timer5 = new QTimer(this) ;
    connect(timer5, SIGNAL(timeout()), this, SLOT(carStopIndicator()));

//    QFont font;
//    font.setPointSize(50);

//    ui->posButton_1->setFont(font);
    ui->pushButton_current_floor->setGeometry(QRect(240, 215, 101, 31));

    setMove();

    ui->posButton_1->raise();
    ui->posButton_2->raise();
    ui->posButton_3->raise();
    ui->posButton_4->raise();
    ui->posButton_5->raise();

    ui->posButton_1->setStyleSheet("background-color:transparent;color:white");
    ui->posButton_2->setStyleSheet("background-color:transparent;color:white");
    ui->posButton_3->setStyleSheet("background-color:transparent;color:white");
    ui->posButton_4->setStyleSheet("background-color:transparent;color:white");
    ui->posButton_5->setStyleSheet("background-color:transparent;color:white");

    ui->posButton_10->setFocus();

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();

    MainWindow::on_startButton_4_clicked();

    ui->posButton_11->raise();

    booked_floors[0]=4; 

    ui->posButton_11->setText(ui->textEdit->toPlainText());
    ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
    ui->posButton_11->setFont(booked1_font);
 
    car_status=stop; 
    ui->pushButton_stop->setStyleSheet("background-color: rgb(255, 43, 15);") ;


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
    pPosAnimation1->setEndValue(QPoint(center_line, end_line));
    pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

    pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
    pPosAnimation2->setDuration(3000);
    pPosAnimation2->setStartValue(QPoint(center_line, start_line-interval*1));
    pPosAnimation2->setEndValue(QPoint(center_line, end_line-interval*1));
    pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

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

}

void MainWindow::setMoveUp(bool up)
{
    char offset1,offset2,offset3,offset4,offset5; 

    unsigned char control_floor;

    offset1=current_floor-1 ; 

    control_floor=1;

    if(offset1==0)    
    {
    	pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
    	pPosAnimation1->setDuration(3000);

        if(up==true)
        { 
    		pPosAnimation1->setStartValue(QPoint(center_line, start_line1));
    		pPosAnimation1->setEndValue(QPoint(center_line, stand_line));
	}
	else
	{
        	pPosAnimation1->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation1->setEndValue(QPoint(center_line, start_line1));
	}

        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==1)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation1->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation1->setEndValue(QPoint(center_line, start_line2));
	}
	else
	{
		pPosAnimation1->setStartValue(QPoint(center_line, start_line2));
		pPosAnimation1->setEndValue(QPoint(center_line, stand_line));
	}

        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=2)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation1->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        	pPosAnimation1->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
	}
	else
	{
		pPosAnimation1->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
		pPosAnimation1->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
	}

        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }


    control_floor=2;

    if(offset1==0)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);

	if(up==true)
	{
	        pPosAnimation2->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
        	pPosAnimation2->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
	}
	else
	{
		pPosAnimation2->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
		pPosAnimation2->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
	}

        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    if(offset1==1)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);
	
	if(up==true)
	{
        	pPosAnimation2->setStartValue(QPoint(center_line, start_line1));
        	pPosAnimation2->setEndValue(QPoint(center_line, stand_line));
	}
	else
	{
		pPosAnimation2->setStartValue(QPoint(center_line, stand_line));
		pPosAnimation2->setEndValue(QPoint(center_line, start_line1));
	}

        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==2)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);

	if(up==true)
	{
	        pPosAnimation2->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation2->setEndValue(QPoint(center_line, start_line2));
	}
	else
	{
		pPosAnimation2->setStartValue(QPoint(center_line, start_line2));
		pPosAnimation2->setEndValue(QPoint(center_line, stand_line));
	}

        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=3)
    {
        pPosAnimation2 = new QPropertyAnimation(ui->posButton_2, "pos");
        pPosAnimation2->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation2->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        	pPosAnimation2->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
	}
	else
	{
		pPosAnimation2->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
		pPosAnimation2->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
	}	

        pPosAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    }



   control_floor=3; 
   

   if(offset1<=1)
   {
        pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
        pPosAnimation3->setDuration(3000);
	if(up==true)
	{
        	pPosAnimation3->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
        	pPosAnimation3->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
	}
	else
	{
		pPosAnimation3->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
		pPosAnimation3->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
	}

        pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
   }
   if(offset1==2)
   {
        pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
        pPosAnimation3->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation3->setStartValue(QPoint(center_line, start_line1));
        	pPosAnimation3->setEndValue(QPoint(center_line, stand_line));
	}
	else
	{
		pPosAnimation3->setStartValue(QPoint(center_line, stand_line));
		pPosAnimation3->setEndValue(QPoint(center_line, start_line1));
	}

        pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==3)
    {
        pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
        pPosAnimation3->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation3->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation3->setEndValue(QPoint(center_line, start_line2));
	}
	else
	{
		pPosAnimation3->setStartValue(QPoint(center_line, start_line2));
		pPosAnimation3->setEndValue(QPoint(center_line, stand_line));
	}

        pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=4)
    {
        pPosAnimation3 = new QPropertyAnimation(ui->posButton_3, "pos");
        pPosAnimation3->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation3->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        	pPosAnimation3->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
	}
	else
	{
		pPosAnimation3->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
		pPosAnimation3->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
	}

        pPosAnimation3->setEasingCurve(QEasingCurve::InOutQuad);
    }


   control_floor=4;

   if(offset1<=2)
   {
        pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
        pPosAnimation4->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation4->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
        	pPosAnimation4->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
	}
	else
	{
		pPosAnimation4->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
		pPosAnimation4->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
	}

        pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
   }
   if(offset1==3)
   {
        pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
        pPosAnimation4->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation4->setStartValue(QPoint(center_line, start_line1));
        	pPosAnimation4->setEndValue(QPoint(center_line, stand_line));
	}
	else
	{
		pPosAnimation4->setStartValue(QPoint(center_line, stand_line));
		pPosAnimation4->setEndValue(QPoint(center_line, start_line1));
	}

        pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==4)
    {
        pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
        pPosAnimation4->setDuration(3000);

	if(up==true)	
	{
        	pPosAnimation4->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation4->setEndValue(QPoint(center_line, start_line2));
	}
	else
	{
		pPosAnimation4->setStartValue(QPoint(center_line, start_line2));
		pPosAnimation4->setEndValue(QPoint(center_line, stand_line));
	}

        pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=5)
    {
        pPosAnimation4 = new QPropertyAnimation(ui->posButton_4, "pos");
        pPosAnimation4->setDuration(3000);
	
	if(up==true)
	{
        	pPosAnimation4->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        	pPosAnimation4->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
	}
	else
	{
		pPosAnimation4->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
		pPosAnimation4->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
	}

        pPosAnimation4->setEasingCurve(QEasingCurve::InOutQuad);
    }

   control_floor=5;

   if(offset1<=3)
   {
        pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
        pPosAnimation5->setDuration(3000);

	if(up==true) 
	{       
		pPosAnimation5->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
        	pPosAnimation5->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
	}
	else
	{
		pPosAnimation5->setStartValue(QPoint(center_line, start_line1-(control_floor-current_floor-1)*interval));
		pPosAnimation5->setEndValue(QPoint(center_line, start_line1-(control_floor-current_floor)*interval));
	}

        pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
   }
   if(offset1==4)
   {
        pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
        pPosAnimation5->setDuration(3000);
	
	if(up==true)
	{
        	pPosAnimation5->setStartValue(QPoint(center_line, start_line1));
        	pPosAnimation5->setEndValue(QPoint(center_line, stand_line));
	}
	else
	{
		pPosAnimation5->setStartValue(QPoint(center_line, stand_line));
		pPosAnimation5->setEndValue(QPoint(center_line, start_line1));
	}

        pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==5)
    {
        pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
        pPosAnimation5->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation5->setStartValue(QPoint(center_line, stand_line));
        	pPosAnimation5->setEndValue(QPoint(center_line, start_line2));
	}
	else
	{
		pPosAnimation5->setStartValue(QPoint(center_line, start_line2));
		pPosAnimation5->setEndValue(QPoint(center_line, stand_line));
	}

        pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=6)
    {
        pPosAnimation5 = new QPropertyAnimation(ui->posButton_5, "pos");
        pPosAnimation5->setDuration(3000);

	if(up==true)
	{
        	pPosAnimation5->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        	pPosAnimation5->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
	}
	else
	{
		pPosAnimation5->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
		pPosAnimation5->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
	}

        pPosAnimation5->setEasingCurve(QEasingCurve::InOutQuad);
    }

    timer->start(2000);

}

void MainWindow::updateAction()
{

//    qDebug() << "updateAction";
    

    QFont font;
    font.setPointSize(50);

    QFont font2;
    font2.setPointSize(30);

    if(current_floor==1)
    {
	
    	ui->posButton_1->setFont(font);

    }
    else
    {

	ui->posButton_1->setFont(font2);

    }

    if(current_floor==2)
    {
	ui->posButton_2->setFont(font);
    }
    else
    {
        ui->posButton_2->setFont(font2);
    }

    if(current_floor==3)
    {
        ui->posButton_3->setFont(font);
    }
    else
    {
	ui->posButton_3->setFont(font2);
    }

    if(current_floor==4)
    {
        ui->posButton_4->setFont(font);
    } 
    else
    {
        ui->posButton_4->setFont(font2);
    }


    if(current_floor==5)
    {
        ui->posButton_5->setFont(font);
    }
    else
    {
        ui->posButton_5->setFont(font2);
    }


    timer->stop();

}


void MainWindow::setMoveDown()
{
    char offset1,offset2,offset3,offset4,offset5;

    unsigned char control_floor;

    offset1=current_floor-1 ;

    control_floor=1;

    if(offset1==0)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);
	pPosAnimation1->setStartValue(QPoint(center_line, stand_line));
        pPosAnimation1->setEndValue(QPoint(center_line, start_line1));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1==1)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);
        pPosAnimation1->setStartValue(QPoint(center_line, start_line2));
        pPosAnimation1->setEndValue(QPoint(center_line, stand_line));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }
    else if(offset1>=2)
    {
        pPosAnimation1 = new QPropertyAnimation(ui->posButton_1, "pos");
        pPosAnimation1->setDuration(3000);
        pPosAnimation1->setStartValue(QPoint(center_line, start_line2+interval*(offset1-control_floor)));
        pPosAnimation1->setEndValue(QPoint(center_line, start_line2+interval*(offset1-control_floor-1)));
        pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    }

}




void MainWindow::on_startButton_clicked()
{

    start_line=-600 ;
    end_line=130;
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

void MainWindow::on_up()
{
    if(current_floor>=maximum)
    return;

    start_line=end_line;
    end_line=end_line+interval;
    current_floor++;

    setMoveUp(true);

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();

//    printf("current floor=%d",ui->textEdit->toPlainText());


//    m_group->setDirection(QAbstractAnimation::Backward);
//    m_group->setLoopCount(1);
//    m_group->start();
}

void MainWindow::on_down()
{
    if(current_floor<=0)
    return;

    start_line=end_line;

    setMoveUp(false);

    current_floor--;
//    setMoveDown();
    end_line=end_line-interval;

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();
}

void MainWindow::on_startButton_3_clicked()
{
    if(current_floor>=maximum)
    return;

    std::string s1= to_String(current_floor+1);

    ui->textEdit->setText(s1.c_str());

    on_startButton_4_clicked();
}

void MainWindow::on_startButton_2_clicked()
{
    if(current_floor<=0)
    return; 

    std::string s1= to_String(current_floor-1);

    ui->textEdit->setText(s1.c_str());

    on_startButton_4_clicked();
}

void MainWindow::on_startButton_4_clicked()
{
    int b = ui->textEdit->toPlainText().toInt();
    int offset=0; 

    qDebug() <<"add new floor:"<< b;

    next_floor=b;

    offset=next_floor-current_floor;  

    if(offset>0)
    {
	on_up();	
        timer2->start(3000);
    } 
    else if(offset<0)
    {
	on_down();
	timer2->start(3000);
    }
    else
    {
  	timer2->stop();
    }

    bool new_floor=true;       

    for(unsigned char i=0;i<maximum;i++)
    {
	if(next_floor==booked_floors[i])
	{
	    new_floor=false; 	
	}
    }

    if(new_floor==true)
    {
	qDebug() << "add floor:" << next_floor ;
	booked_floors[booked_num++]=next_floor; 
    }


}

void MainWindow::carStopIndicator()
{
	if(current_floor == next_floor)
	{
		ui->pushButton_up->setStyleSheet("background-color: rgb(255, 255, 255);") ;
        	ui->pushButton_down->setStyleSheet("background-color: rgb(255, 255, 255);") ;
        	ui->pushButton_stop->setStyleSheet("background-color: rgb(255, 43, 15);") ;

 		imgLabel_up->setPixmap(QPixmap(""));
        	imgLabel_down->setPixmap(QPixmap(""));

		car_status=stop;
	}

	timer5->stop();
}

void MainWindow::carStatusIndicator()
{

//    qDebug() << current_floor << " " << next_floor  ;

    if(current_floor < next_floor)
    {
        ui->pushButton_up->setStyleSheet("background-color: rgb(255, 43, 15);") ;
        ui->pushButton_down->setStyleSheet("background-color: rgb(255, 255, 255);") ;
        ui->pushButton_stop->setStyleSheet("background-color: rgb(255, 255, 255);") ;

    	QImage img = QImage((const unsigned char *)(matData_up.data),
                        matData_up.cols,
                        matData_up.rows,
                        static_cast<int>(matData_up.step),
                        QImage::Format_RGB888);
    	QPixmap pixmap = QPixmap(QPixmap::fromImage(img.rgbSwapped()));
    	imgLabel_up->setPixmap(pixmap);
	imgLabel_down->setPixmap(QPixmap(""));

	car_status=up; 
    }
    else if(current_floor == next_floor)
    {
	timer5->singleShot(3000, this, SLOT(carStopIndicator()));
    }
    else
    {
	ui->pushButton_up->setStyleSheet("background-color: rgb(255, 255, 255);") ;
        ui->pushButton_down->setStyleSheet("background-color: rgb(255, 43, 15);") ;
        ui->pushButton_stop->setStyleSheet("background-color: rgb(255, 255, 255);") ;

    	QImage img2 = QImage((const unsigned char *)(matData_down.data),
                        matData_down.cols,
                        matData_down.rows,
                        static_cast<int>(matData_down.step),
                        QImage::Format_RGB888);
    	QPixmap pixmap2 = QPixmap(QPixmap::fromImage(img2.rgbSwapped()));

    	imgLabel_down->setPixmap(pixmap2);
	imgLabel_up->setPixmap(QPixmap(""));
	car_status=down; 
    }

    for(unsigned char i=0;i<maximum;i++)
    {
        if(booked_floors[i]!=255)
        {
            qDebug() << "----------------" ;
            qDebug() << "booked num:" << booked_num ;  
            qDebug() << "Booked floor:" << booked_floors[i]<<"current floor:"<<current_floor ;
	    qDebug() << "----------------" ;

            if(car_status==up)
            {
                if(booked_floors[i]<current_floor)
                {
                        booked_floors[i]=255;
                        booked_num--;
                }
            }
            else if(car_status==down)
            {
                if(booked_floors[i]>current_floor)
                {
                        booked_floors[i]=255;
                        booked_num--;
                }
            }
            else if(car_status==stop)
            {
                booked_floors[i]=255;
                booked_num--;
            }
        }
    }


}

string MainWindow::to_String(int n)
{
     int m = n;
     char s[100];
     char ss[100];
     int i=0,j=0;
     if (n < 0)
     {
         m = 0 - m;
         j = 1;
         ss[0] = '-';
     }    
     while (m>0)
     {
         s[i++] = m % 10 + '0';
         m /= 10;
     }
     s[i] = '\0';
     i = i - 1;
     while (i >= 0)
     {
         ss[j++] = s[i--];
     }    
     ss[j] = '\0';    
     return ss;
}


void MainWindow::sortA1(int a[], int length){

    int i, j, temp;

    for(i = 0; i < length; ++i){

        for(j = i + 1; j < length; ++j){

            if(a[j] < a[i]){    //如果后一个元素小于前一个元素则交换

                temp = a[i];

                a[i] = a[j];

                a[j] = temp;

            }

        }
    }

}


void MainWindow::sortA2(int a[], int length){

    int i, j, temp;

    for(i = 0; i < length; ++i){

        for(j = length - 1; j > i; --j){

            if(a[j] > a[j - 1]){
                
                temp = a[j];

                a[j] = a[j - 1];

                a[j - 1] = temp;

            }
        }

    }

}



void MainWindow::bookedFloorsAction()
{
//    qDebug() << "bookedFloorsAction" ;

//    qDebug() << "floor" <<current_floor << " " << next_floor  ;

//    qDebug() << "floor number" <<current_booked_floors_num << " " << next_booked_floors_num  ;
  
    qDebug() << "bookedFloorsActioni booked num:" << booked_num << "current num:" << current_booked_floors_num ;

/*
    if(booked_num>current_booked_floors_num)
    {
 	current_booked_floors_num++;								
    }
*/
   
    
    for(unsigned char i=0;i<maximum;i++)
    {
        if(booked_floors[i]!=255)
        {
            qDebug() << "**************" ;
            qDebug() << "booked num:" << booked_num ;
            qDebug() << "Booked floor:" << booked_floors[i] << " " << i ;
	    qDebug() << "**************" ;
	}
    }

   //sortA1((int*)booked_floors,(int)maximum);   

/*

    if(booked_num==0)
    {
	ui->posButton_11->setGeometry(QRect(1000, 10, 70, 70));
	ui->posButton_12->setGeometry(QRect(1000, 10, 70, 70));
    }        
    else if(booked_num==1)
    {
        ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
        ui->posButton_11->setFont(booked1_font);

  	for(unsigned char i=0;i<maximum;i++)
    	{
        	if(booked_floors[i]!=255)
        	{
		        std::string s= to_String(booked_floors[i]);
        		ui->posButton_11->setText(s.c_str());
		}
	}

	ui->posButton_12->setGeometry(QRect(1000, 10, 70, 70));
    }
    else if(booked_num==2)
    {
	ui->posButton_11->setText(ui->textEdit->toPlainText());
        ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
        ui->posButton_11->setFont(booked1_font);

	std::string s= to_String(booked_floors[0]);

        ui->posButton_11->setText(s.c_str());

	ui->posButton_12->setGeometry(QRect(140, 20, 50, 50));

	std::string s1= to_String(booked_floors[1]);

        ui->posButton_12->setText(s1.c_str());
    }
    
*/

    if((booked_num==0)&&(last_booked_num!=0))
    {
        ui->posButton_11->setGeometry(QRect(1000, 10, 70, 70));
        ui->posButton_12->setGeometry(QRect(1000, 10, 70, 70));
	last_booked_num=0; 
    }        
    else if((booked_num==1)&&(last_booked_num!=1))
    {
        ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
        ui->posButton_11->setFont(booked1_font);

        for(unsigned char i=0;i<maximum;i++)
        {
                if(booked_floors[i]!=255)
                {
                        std::string s= to_String(booked_floors[i]);
                        ui->posButton_11->setText(s.c_str());
                }
        }

        ui->posButton_12->setGeometry(QRect(1000, 10, 70, 70));

	last_booked_num=1; 
    }
    else if((booked_num==2)&&(last_booked_num!=2))
    {
        ui->posButton_11->setText(ui->textEdit->toPlainText());
        ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
        ui->posButton_11->setFont(booked1_font);

        std::string s= to_String(booked_floors[0]);

        ui->posButton_11->setText(s.c_str());

        ui->posButton_12->setGeometry(QRect(140, 20, 50, 50));

        std::string s1= to_String(booked_floors[1]);

        ui->posButton_12->setText(s1.c_str());

  	pPosAnimation_booked1->setDuration(3000);
        pPosAnimation_booked1->setStartValue(QPoint(booked_start1_line1,booked_fixxed_line1));
        pPosAnimation_booked1->setEndValue(QPoint(booked_start1_line2,booked_fixxed_line1));
        pPosAnimation_booked1->setEasingCurve(QEasingCurve::InOutQuad);

        pPosAnimation_booked2->setDuration(3000);
        pPosAnimation_booked2->setStartValue(QPoint(booked_start2_line1,booked_fixxed_line2));
        pPosAnimation_booked2->setEndValue(QPoint(booked_start2_line2,booked_fixxed_line2));
        pPosAnimation_booked2->setEasingCurve(QEasingCurve::InOutQuad);

        pPosAnimation_booked1->start();
        pPosAnimation_booked2->start();


	last_booked_num=2; 
    }




 
/*	
 
    if(next_booked_floors_num>=current_booked_floors_num)
    {
	if((next_booked_floors_num==1)&&(current_booked_floors_num==1))
        {
                ui->posButton_11->setText(ui->textEdit->toPlainText());
                ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
                ui->posButton_11->setFont(booked1_font);
        }
    	if((next_booked_floors_num==1)&&(current_booked_floors_num==1))
    	{
    		ui->posButton_11->setText(ui->textEdit->toPlainText());
    		ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
    		ui->posButton_11->setFont(booked1_font);
    	}
    	if((next_booked_floors_num==2)&&(current_booked_floors_num==1))
    	{	
		ui->posButton_12->setGeometry(QRect(140, 20, 50, 50));
    		ui->posButton_12->setText("5");
		current_booked_floors_num=2;
    	}
    	if((next_booked_floors_num==2)&&(current_booked_floors_num==2))
    	{
    		pPosAnimation_booked1->setDuration(3000);
    		pPosAnimation_booked1->setStartValue(QPoint(booked_start1_line1,booked_fixxed_line1));
    		pPosAnimation_booked1->setEndValue(QPoint(booked_start1_line2,booked_fixxed_line1));
    		pPosAnimation_booked1->setEasingCurve(QEasingCurve::InOutQuad);

		pPosAnimation_booked2->setDuration(3000);
     		pPosAnimation_booked2->setStartValue(QPoint(booked_start2_line1,booked_fixxed_line2));
    		pPosAnimation_booked2->setEndValue(QPoint(booked_start2_line2,booked_fixxed_line2));
    		pPosAnimation_booked2->setEasingCurve(QEasingCurve::InOutQuad);

    		pPosAnimation_booked1->start();
		pPosAnimation_booked2->start();

		current_booked_floors_num=3;
    	}
    }

*/


}







