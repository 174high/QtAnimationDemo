#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black;");
//    ui->posButton_1->setStyleSheet("background-color:black;");
 
    car_status=stop ; 
 
    start_line1=130 ;
    start_line2=270 ;
    stand_line=200  ;

    center_line=80 ; 
    start_line=-600 ;
    end_line= 130; 
//    current_floor_line= ;
    interval=50;     
    floor_long=71;
    floor_width=61; 

    maximum=5; 
    current_floor=0; 

    booked_fixxed_line1=10;
    booked_start1_line1=80;
    booked_start1_line2=60;

    booked_fixxed_line2=20;
    booked_start2_line1=140;
    booked_start2_line2=120;


    ui->textEdit->setText("2");
    ui->textEdit->show();

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
 
    ui->currentFloorButton->setGeometry(QRect(78, 198, 80, 70));

    timer = new QTimer(this) ;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAction()));

    timer2 = new QTimer(this) ;
    connect(timer2, SIGNAL(timeout()), this, SLOT(on_startButton_4_clicked()));

    timer3 = new QTimer(this) ;
    connect(timer2, SIGNAL(timeout()), this, SLOT(bookedFloorsAction()));

    timer3->start(500);

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

    booked_floors[0]=2; 

    for(unsigned char i=0;i<maximum;i++)
    {
        if(booked_floors[i]!=255)
        {
		current_booked_floors_num=1;
    		next_booked_floors_num=1;
	}

    }
    ui->posButton_11->setText(ui->textEdit->toPlainText());
    ui->posButton_11->setGeometry(QRect(80, 10, 70, 70));
    ui->posButton_11->setFont(booked1_font);
 


//    ui->posButton_12->setText("7");
//    ui->posButton_12->setFont(booked2_font);


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

    qDebug() << "updateAction";
    

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

void MainWindow::on_startButton_3_clicked()
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

void MainWindow::on_startButton_2_clicked()
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


//    m_group->setDirection(QAbstractAnimation::Forward);
//    m_group->setLoopCount(-1);
//    m_group->start();
}

void MainWindow::on_startButton_4_clicked()
{
    int b = ui->textEdit->toPlainText().toInt();
    int offset=0; 
    int next_floor;

    qDebug() << b;
/*
    start_line=end_line;
    end_line=end_line-(current_floor-b)*interval;
    current_floor=b;

    setMove();

    pPosAnimation1->start();
    pPosAnimation2->start();
    pPosAnimation3->start();
    pPosAnimation4->start();
    pPosAnimation5->start();
*/

    next_floor=b;

    offset=next_floor-current_floor;  

    if(offset>0)
    {
	on_startButton_3_clicked();	
 	timer2->start(3000);
    } 
    else if(offset<0)
    {
	on_startButton_2_clicked();
	timer2->start(3000);
    }
    else
    {
  	timer2->stop();
    }


    for(unsigned char i=0;i<maximum;i++)
    {

        if(booked_floors[i]!=255)
        {
	 	if(next_floor!=booked_floors[i])
		{
			next_booked_floors_num=2;
		}
        }

    }

//    m_group->setDirection(QAbstractAnimation::Forward);
//    m_group->setLoopCount(-1);
//    m_group->start();
}


void MainWindow::bookedFloorsAction()
{
    qDebug() << "bookedFloorsAction" ;
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
    


/*
    pPosAnimation_booked2->setDuration(3000);
    pPosAnimation_booked2->setStartValue(QPoint(booked_start2_line1,booked_fixxed_line2));
    pPosAnimation_booked2->setEndValue(QPoint(booked_start2_line2,booked_fixxed_line2));
    pPosAnimation_booked2->setEasingCurve(QEasingCurve::InOutQuad);
*/


  //  pPosAnimation_booked1->start();

  //  pPosAnimation_booked2->start();

}







