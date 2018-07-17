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

    cameraLog.open("camLog.txt");

    lastImage = QImage(640,480,  QImage::Format_RGB888);// dump image
    lastImage.fill(Qt::GlobalColor::blue);
    tick();
}

CameraScene::~CameraScene()
{
    cameraLog<<"Begin ~CameraScene()"<<std::endl;
    finish=true;
    if(cameraThread.joinable())
        cameraThread.join();
    cameraLog<<"End ~CameraScene()"<<std::endl;
    cameraLog.close();
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

        int reply_length = boost::asio::read(socket,boost::asio::buffer(buffer, 12));

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
        reply_length = boost::asio::read(socket,boost::asio::buffer(buffer,numberOfBytes));
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




    /*

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


    //unsigned msWaited;
    while(!finish){
        //msWaited = 0;

        qDebug()<<"writing to socket";
        buffer[0] = 'h';
        socket->write(buffer.data(),1); // WRITE LARI VE READ LERİ WRİTEDATA READDATA YAP

        // 12 bytes are first three integers, width, height and num layers

        while(socket->bytesAvailable()<12){
            qDebug()<<"insede socket->bytesAvailable()<12 ";
            socket->waitForReadyRead();
        }
        int bytes = socket->read(buffer.data(), 12);
         qDebug()<<"bytes is after reading 12 bytes "<<bytes;
         qDebug()<<"hexadecimal : "<<buffer.left(12).toHex();



        /*int curPos = 0;
        while(curPos < 12){
            int bytes = socket->read(buffer.data() + curPos, 12-curPos); // BİR İHTİMAL
            if(bytes == 0){
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                //msWaited += 4;
            }
            else if(bytes > 0)
                curPos += bytes;
        }

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

        int numberOfbytes=width*height*layer;
        //curPos = 0;


        while(socket->bytesAvailable()<numberOfbytes){
            qDebug()<<"insede socket->bytesAvailable()<numberofbytes ";
             std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        bytes=socket->read(buffer.data(),numberOfbytes);
        qDebug()<<"bytes reading "<<bytes;


       /* while(curPos < numberOfbytes && numberOfZeroBytes<20){
           qDebug()<<"while(curPos < numberOfbytes)"<<"curpos :"<<curPos<<"numberofbyte"<<numberOfbytes;

            int bytes = socket->read(buffer.data()+ curPos,numberOfbytes-curPos);


            if(bytes==-1)
                qDebug()<<"error "<<socket->errorString();
            if(bytes == 0){
                qDebug()<<"byte 0";
                numberOfZeroBytes++;
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                //msWaited += 1;
            }
            else if(bytes > 0)
                curPos += bytes;
        }


        qDebug()<<"End of while(curPos < numberOfbytes)";

        {
            std::lock_guard<std::mutex> lock(imgMutex);
            lastImage = QImage((const uchar*)(buffer.left(numberOfbytes).data()),
                               width, height, width*layer, QImage::Format_RGB888).copy();
        }
        // This sleeping (40ms) will become variable, it will be gotten from user
        // via gui and will indicate FPS
        //std::this_thread::sleep_for(std::chrono::milliseconds(40 - msWaited));
        qDebug()<<"end of while(!finish)";

        //qDebug()<<socket->readAll().left(30);

    }
    buffer.clear();
    */
}

void CameraScene::on_start_clicked()
{

    if(ui->server->isChecked()){

        qDebug()<<"Started is clicked";
        qDebug()<<ui->ipAddress->text();

        ipAdd=ui->ipAddress->text();
        cameraThread = std::thread(&CameraScene::processFrameAndUpdateGUI,this);
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



