#ifndef ZENOM_H
#define ZENOM_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif
#include <QProcess>
#include <QWaitCondition>
#include <QMutex>
#include <QTimer>

#include <datarepository.h>
#include <MessageQueueXn.h>

#include "messagelistenertask.h"
class MessageListenerTask;

#include "widget/statusbar.h"
#include "controlvariableswidget.h"
#include "logvariableswidget.h"
#include "gauge/gaugemanager.h"
#include "plot/plotmanager.h"
#include "scene/scenemanager.h"
#include "aboutdialog.h"


namespace Ui {
class Zenom;
}

class Zenom : public QMainWindow
{
    Q_OBJECT
    friend class MessageListenerTask;
    
public:
    explicit Zenom( int argc, char *argv[] );

    ~Zenom();

private slots:

    // File Menu
    /**
     * Arayuzden znm projesi acmak istenildigi zaman cagrilir.
     */
    void on_actionOpen_Project_triggered();

    /**
     * Arayuz bilgileri kayit edilir. Scene, gauge ve plot
     * pencereleri, control-variable degerleri, frekans ve zaman
     * degerleri kayit edilir.
     */
    void on_actionSave_Project_triggered();

    /**
     * En son yuklenen projenin tekrar yuklenmesini saglar.
     * Control programda sirasiyla terminate ve initialize
     * fonksiyonlari cagrilir.
     */
    void on_actionReload_triggered();

    /**
     * Arayuzden son kullanilan projelerden biri acilmak istenildigi
     * zaman cagrilir.
     */
    void openRecentFile();

    /**
     * Zenom programini kapatir. Eger calisan bir control programi
     * var ise sonlandirilir.
     */
    void on_actionExit_triggered();

    // View Menu
    /**
     * Gadget secimi yapilabilen pencereyi acar.
     */
    void on_actionWatch_triggered();

    /**
     * Grafik penceresi acar.
     */
    void on_actionPlot_triggered();

    /**
     * Sahne penceresi acar.
     */
    void on_actionScene_triggered();

    /**
     * Arayuzden start ve pause butonlarina basilinca cagrilir.
     * Log variable listesi icin gerekli hafiza alanlari alinir.
     * Control programda start fonksiyonu cagrilmasini saglar.
     */
    void on_startButton_clicked();

    /**
     * Arayuzden stop butonuna basilinca cagrilir.
     * Control programinin durdurulmasini ve stop fonsksiyonu
     * cagrilmasini saglar.
     */
    void on_stopButton_clicked();

    /**
     * Kullanici frekans degerini degistirdigi zaman cagrilir.
     */
    void on_frequency_editingFinished();

    /**
     * Kullanici süreyi degerini degistirdigi zaman cagrilir.
     */
    void on_duration_editingFinished();

    /**
     * Arayuzleri gunceller.
     * Plot, scene ve gauge arayüzlerindeki log-variable gösterimleri
     * bu fonksiyon cagrilarak guncellenir.
     */
    void doloop();

    /**
     * Control-Base process'te bir hata olustugunda cagrilir.
     * @param pError hata kodu
     */
    void controlBaseProcessError( QProcess::ProcessError pError );

    /**
     * Kullanici tarafindan girilen standart mesajlarini alir.
     * Control-Base tarafindan cout kullanilarak
     * yazilan mesajlar ele alinir.
     */
    void controlBaseReadyReadStandardOutput();

    /**
     * Kullanici tarafindan girilen hata mesajlarini alir.
     * Control-Base tarafindan cerr kullanilarak
     * yazilan mesajlar ele alinir.
     */
    void controlBaseReadyReadStandardError();

    /**
     * About penceresini gosterir.
     */
    void on_action_About_zenom_triggered();

    /**
     * Butun log degiskenlerini Matlab (.m) dosya formatina uygun
     * olarak kayit eder.
     */
    void on_actionExport_as_Matlab_triggered();

    void on_actionClear_Recent_Projects_Menu_triggered();

private:
    Ui::Zenom *ui;

    /**
     * Arayuzde yer alan status bar aracıdır.
     */
    StatusBar* mStatusBar;

    /**
     * Su an yuklu olan projenin adresini tutar.
     */
    QString mProjectPath;

    // File Menu
    /**
     * znm projesi acmak istenildigi zaman cagrilir.
     * Haberlesme (MessageQueue) baglantilari, ana heap burada olusturulur.
     *
     * @param pProjectName znm dosyasini adresi
     */
    void openProject(const QString& pProjectName);

    /**
     * znm projesine kayit edilen veriler yuklenir. Kayit edilmis scene,
     * gauge ve plot pencereleri acilir, control-variable degerleri,
     * frekans ve zaman degerleri arayuze yuklenir.
     *
     * @param pProjectName znm dosyasini adresi
     */
    void loadSettings(const QString& pProjectName);

    /**
     * znm projesini sonlandirir. Haberlesme(MessageQueue) baglantilari kapatilir,
     * ana heap, var ise log variable alanlari sisteme geri verilir. Acik olan
     * scene, gauge ve plot pencereleri kapatilir. Log-variable ve control variable
     * pencerelerindeki tablolar temizlenir.
     */
    void terminateProject();

    /**
     * Control variable degerlerinin degistirilmesini saglayan penceredir.
     */
    ControlVariablesWidget* mControlVariablesWidget;

    /**
     * Log variable frekans, süre ve baslangic zamanlarini degisterilmesini saglayan
     * penceredir.
     */
    LogVariablesWidget* mLogVariablesWidget;

    /**
     * Gadget pencerelerinin tutuldugu ve yonetildigi siniftir.
     */
    GaugeManager* mGaugeManager;

    /**
     * Plot pencerelerinin tutuldugu ve yonetildigi siniftir.
     */
    PlotManager* mPlotManager;

    /**
     * Scene pencerelerinin tutuldugu ve yonetildigi siniftir.
     */
    SceneManager* mSceneManager;

    /**
     * Control programini calistiran siniftir.
     */
    QProcess mControlBaseProcess;

    /**
     * Control programindan gelen mesajlari dinleyen siniftir.
     */
    MessageListenerTask* mMessageListenerTask;

    /**
     * Benzetim durumunu getirir.
     * @return benzetim durumunu getirir.
     */
    State simulationState();

    /**
     * Benzetim durumunu gunceller. Duruma gore arayuzdeki alanlar
     * aktif/pasif hale getilir.
     * @param pState yeni benzetim durumu
     */
    void setSimulationState( State pState );

    /**
     * Benzetim durumunu tutar.
     */
    State mSimState;

    /**
     * Ana heap, log variable ve control variable listesinin tutuldugu ana siniftir.
     */
    DataRepository* mDataRepository;

    /**
     * Frekans degerini gunceller. Frekans degeri 0'dan buyuk degil ise
     * deger guncellenmez.
     * @param pFrequency yeni frekans degeri
     */
    void setFrequency(double pFrequency);

    /**
     * Sure degerini gunceller. Sure degeri 0'dan buyuk degil ise
     * deger guncellenmez.
     * @param pDuration yeni sure degeri
     */
    void setDuration(double pDuration);

    /**
     * Arayuzlerin guncellenmesini saglayan doloop fonksiyonunu
     * periyodik olarak cagrilmasini saglayan nesnedir.
     */
    QTimer mTimer;

    // the most recent files loaded by user.
    void createRecentFileActions();
    void updateRecentFileActions();
    void insertRecentFileList( const QString& pProjectPath );
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    /**
     * About penceresidir.
     */
    AboutDialog* mAboutDialog;
};

#endif // ZENOM_H
