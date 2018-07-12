#include "camerascene.h"
#include "ui_camerascene.h"
#include <QPixmap>
#include <QDebug>
#include <thread>
#include <chrono>

CameraScene::CameraScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraScene),
    finish(false)
{
    ui->setupUi(this);
    ui->ipAddress->hide();

    socket = new QTcpSocket(this);
    imageOrg = QImage(640,480,QImage::Format_RGB888);// dump image
    imageOrg.fill(Qt::GlobalColor::blue);
}

CameraScene::~CameraScene()
{
    socket->close();
    finish = true;
    if(cameraThread.joinable())
        cameraThread.join();
    delete ui;
}

void CameraScene::tick()
{
    ui->label_camera->setPixmap(QPixmap::fromImage(imageOrg));
}


void CameraScene::processFrameAndUpdateGUI()
{
    QByteArray buffer;
    buffer.resize(); // NAO DOC A GIT
    while(!finish){
        buffer[0] = 'h';
        socket->write(buffer,1);

        unsigned width=0,height=0,layer=0;

        // 12 bytes are first three integers, width, height and num layers
        buffer.resize(12);
        int curPos = 0;
        while(curPos < 12){
            int bytes = socket->read(buffer.data() + curPos, 12-curPos);
            if(bytes == 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            else
                curPos += bytes;
        }

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

        buffer.resize(numberOfbytes);
        curPos = 0;
        while(curPos < numberOfbytes){
            int bytes = socket->read(buffer.data()+curPos,numberOfbytes-curPos);
            if(bytes == 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            else
                curPos += bytes;
        }

        qDebug() << "Got the image, buffer size is "<<buffer.size();

        // actually there is mutex needed here but it will work
        // without it, maybe some pixels will be corrupted
        imageOrg=QImage((uchar*)buffer.data(), width, height,layer,
                        QImage::Format_RGB888);

    }
}

void CameraScene::on_start_clicked()
{


    if(ui->server->isChecked()){

        qDebug()<<"Started is clicked";
        qDebug()<<ui->ipAddress->text();

        ipAdd=ui->ipAddress->text();
        socket->connectToHost(ipAdd, 12345);
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
