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
#include <boost/array.hpp>

CameraScene::CameraScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraScene),
    finish(false)
{
    ui->setupUi(this);

    ui->ipAddress->hide();

    lastImage = QImage(640,480,  QImage::Format_RGB888);// dump image
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
    ui->label_camera->setPixmap(QPixmap::fromImage(lastImage));
}


void CameraScene::processFrameAndUpdateGUI()
{

    boost::array<unsigned char,1920*1080*3>buffer;

    boost::asio::io_service ios;

    boost::asio::ip::tcp::endpoint endpoint(
                boost::asio::ip::address::from_string(
                    ipAdd.toStdString()),13333);

    boost::asio::ip::tcp::socket socket(ios);

    socket.connect(endpoint);

     while(!finish){

        //boost
        auto start = std::chrono::steady_clock::now();

        buffer[0] = 'h';

        boost::asio::write(socket, boost::asio::buffer(buffer,1));

         boost::asio::read(socket,boost::asio::buffer(buffer, 12));

        //qDebug()<<"buffer "<<buffer;


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

        qDebug()<<"width , height, layer : "<<width<<" "<<height<<" "<<layer;

        int numberOfBytes=width*height*layer;
         boost::asio::read(socket,boost::asio::buffer(buffer,numberOfBytes));
        auto end = std::chrono::steady_clock::now();
        auto taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << taken << " milliseconds"<<std::endl;



        {
            std::lock_guard<std::mutex> lock(imgMutex);
            lastImage = QImage((const uchar*)(buffer.data()),
                               width, height, width*layer, QImage::Format_RGB888).copy();
        }

    }




    //EndOfBoost




}

void CameraScene::on_start_clicked()
{

    if(ui->server->isChecked())
    {
        if(ui->start->text()=="Start")
        {
            finish=false;
            ui->start->setText("Stop");
            ipAdd=ui->ipAddress->text();
            cameraThread = std::thread(&CameraScene::processFrameAndUpdateGUI,this);
        }

       else if(ui->start->text()=="Stop")
        {
            ui->start->setText("Start");
            finish=true;
            if(cameraThread.joinable())
                cameraThread.join();

        }

    }


}


void CameraScene::on_server_clicked()
{
    ui->ipAddress->placeholderText();
    ui->ipAddress->setPlaceholderText("Enter IP Address ...");
    ui->ipAddress->show();




}

void CameraScene::on_local_clicked()
{
    ui->ipAddress->hide();


}


void CameraScene::closeEvent(QCloseEvent *event){
    finish=true;
    if(cameraThread.joinable())
        cameraThread.join();
}

