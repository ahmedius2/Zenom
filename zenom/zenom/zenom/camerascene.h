#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QDialog>
#include <QTcpSocket>
#include <atomic>
#include <thread>
#include <mutex>
#include <fstream>
#include<QIODevice>


namespace Ui {
class CameraScene;
}

class CameraScene : public QDialog
{
    Q_OBJECT

public:
    explicit CameraScene(QWidget *parent = 0);

    ~CameraScene();

    void tick();

public slots:
    //QTimer aktif hale geldiğinde işletilecek slotumuz
    void processFrameAndUpdateGUI();

private slots:
    void on_start_clicked();

    void on_server_clicked();

    void on_local_clicked();


private:
    Ui::CameraScene *ui;
    std::thread cameraThread;
    std::mutex imgMutex;
    QString ipAdd;
    quint16 senderPort;
    QImage lastImage;
    std::atomic<bool> finish;
    std::ofstream cameraLog;

};

#endif // CAMERASCENE_H
