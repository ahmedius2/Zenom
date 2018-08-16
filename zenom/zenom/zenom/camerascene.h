#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QDialog>
#include <QTcpSocket>
#include <atomic>
#include <thread>
#include <mutex>
#include <fstream>
#include<QIODevice>
#include <QCloseEvent>


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


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_start_clicked();

    void on_server_clicked();

    void on_local_clicked();


    void on_tenHund_clicked();

    void on_threeHund_clicked();

    void on_sixHund_clicked();

    void on_tenThnd_clicked();

    void on_up_clicked();

    void on_bottom_clicked();

private:
    Ui::CameraScene *ui;
    std::thread cameraThread;
    std::mutex imgMutex;
    QString ipAdd;
    quint16 senderPort;
    QImage lastImage;
    std::atomic<bool> finish;
    int mWidth;
    int mHeight;
    int mResolution;
    int mBottomOrUp;

};

#endif // CAMERASCENE_H
