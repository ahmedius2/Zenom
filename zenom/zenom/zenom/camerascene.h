#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QDialog>
#include <QTcpSocket>
#include <atomic>
#include <thread>

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
    QTcpSocket *socket;
    std::thread cameraThread;
    QString ipAdd;
    quint16 senderPort;
    QImage imageOrg;
    std::atomic<bool> finish;

};

#endif // CAMERASCENE_H
