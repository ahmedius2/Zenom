#include "camerascene.h"
#include "ui_camerascene.h"
#include <QPixmap>
#include <QDebug>
#include <thread>
#include <chrono>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include<boost/asio/error.hpp>
#include <boost/array.hpp>
#include <zenom.h>

CameraScene::CameraScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraScene),
    finish(false),
    mWidth(240),
    mHeight(240),
    mResolution(0),
    mBottomOrUp(1)
{
    ui->setupUi(this);

    ui->ipAddress->hide();
//    ui->sixHund->hide();
//    ui->threeHund->hide();
//    ui->tenThnd->hide();


    lastImage = QImage(300,300,  QImage::Format_RGB888);// dump image
    lastImage.fill(Qt::GlobalColor::blue);
    tick();

}

CameraScene::~CameraScene()
{
    finish=true;

    if(cameraThread.joinable())
        cameraThread.join();
    delete ui;
}

void CameraScene::tick()
{
    std::lock_guard<std::mutex> lock(imgMutex);
    
    ui->label_camera->setPixmap(QPixmap::fromImage(
                                lastImage.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio)));


    ui->label_camera->setFixedWidth(mWidth);
    ui->label_camera->setFixedHeight(mHeight);
}


void CameraScene::processFrameAndUpdateGUI()
{


    boost::array<unsigned char,1920*1080*3>buffer;

    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket *socket = nullptr;

    try{
        boost::asio::ip::tcp::endpoint endpoint(
                    boost::asio::ip::address::from_string(
                        ipAdd.toStdString()),13333);

        socket = new boost::asio::ip::tcp::socket(ios);
        socket->connect(endpoint);
    }
   catch(boost::system::system_error e){

        ui->ipAddress->clear();
        ui->ipAddress->setPlaceholderText("Wrong ip address , Please try again");
        ui->ipAddress->show();
        finish=true;
        ui->start->setText("Start");

   }

    boost::array<int,2>buff;


     while(!finish){
        buffer[0] = 'h';
        buff[0]=mResolution;
        buff[1]=mBottomOrUp;

        boost::asio::write(*socket, boost::asio::buffer(buff,sizeof(int)*2));

        boost::asio::read(*socket,boost::asio::buffer(buffer, 12));



        unsigned width=0, height=0,layer=0;
        width |= ((uint)((uchar)buffer[0]))<<24;
        width |= ((uint)((uchar)buffer[1]))<<16;
        width |= ((uint)((uchar)buffer[2]))<<8;
        width |= (uint)((uchar)buffer[3]);

        height |= ((uint)((uchar)buffer[4]))<<24;
        height |= ((uint)((uchar)buffer[5]))<<16;
        height |= ((uint)((uchar)buffer[6]))<<8;
        height |= (uint)((uchar)buffer[7]);

        layer |= ((uint)((uchar)buffer[8]))<<24;
        layer |= ((uint)((uchar)buffer[9]))<<16;
        layer |= ((uint)((uchar)buffer[10]))<<8;
        layer |= (uint)((uchar)buffer[11]);


        int numberOfBytes=width*height*layer;
         boost::asio::read(*socket,boost::asio::buffer(buffer,numberOfBytes));

        {
            std::lock_guard<std::mutex> lock(imgMutex);
            lastImage = QImage((const uchar*)(buffer.data()),
                               width, height, width*layer, QImage::Format_RGB888).copy();
        }

    }

     if(socket != nullptr)
         delete socket;
}

void CameraScene::on_start_clicked()
{

    if(ui->server->isChecked())
    {
        if(ui->start->text()=="Start")
        {
            if(cameraThread.joinable()){
                cameraThread.join();
            }
            finish=false;
            ui->start->setText("Stop");
            ipAdd=ui->ipAddress->text();
            cameraThread = std::thread(&CameraScene::processFrameAndUpdateGUI,this);

        }

       else if(ui->start->text()=="Stop")
        {
            ui->start->setText("Start");
            finish=true;
            ui->start->setEnabled(false);
            if(cameraThread.joinable())
                cameraThread.join();
            ui->start->setEnabled(true);
        }

    }


}


void CameraScene::on_server_clicked()
{
    if(ui->server->isChecked()){
        ui->ipAddress->placeholderText();
        ui->ipAddress->setPlaceholderText("Enter IP Address ...");
        ui->ipAddress->show();
    }

    else{
        ui->ipAddress->hide();
    }




}

void CameraScene::on_local_clicked()
{
    ui->ipAddress->hide();


}


void CameraScene::closeEvent(QCloseEvent *event){
    event->accept();
    finish=true;
    if(cameraThread.joinable())
        cameraThread.join();
}


void CameraScene::on_tenHund_clicked()
{
    mWidth=160;
    mHeight=120;
    mResolution=0;
}

void CameraScene::on_threeHund_clicked()
{
    mWidth=320;
    mHeight=240;
    mResolution=1;
}

void CameraScene::on_sixHund_clicked()
{
    mWidth=640;
    mHeight=480;
    mResolution=2;
}

void CameraScene::on_tenThnd_clicked()
{
    mWidth=1280;
    mHeight=960;
    mResolution=3;
}

void CameraScene::on_up_clicked()
{
    mBottomOrUp=0;
}

void CameraScene::on_bottom_clicked()
{
    mBottomOrUp=1;
}
