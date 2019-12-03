#ifndef DAQ_H
#define DAQ_H

#include <QDialog>
#include <datarepository.h>
#include "comboboxitemdelegate.h"
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class daq;
}

class daq : public QDialog
{
    Q_OBJECT

public:
    enum DAQ_SIG{
        SIG_ANALOG_IN = 0xC0,
        SIG_ENCODER_IN = 0x80,
        SIG_DIGITAL_IN = 0x10,
        SIG_TIMESTAMP = 0x30,
        SIG_DEV_STATUS = 0x40,
        SIG_SW_INFO = 0x60,
        SIG_EOF = 0x70
    };

    enum DAQ_CMD{
        INIT_ADC = 0x01,
        READ_SING_ALL = 0x02,
        INIT_DAC = 0x03,
        UPD_DAC = 0x04,
        LOAD_DAC_LOOKUP = 0x05,
        INIT_ENC = 0x06,
        RST_ENC_CNT = 0x08,
        SET_ENC_CNT = 0x09,
        SET_ENC_MAX_CNT = 0x0A,
        SET_ENC_VEL_PER = 0x0B,
        UPD_DIG_OUT = 0x0C,
        CONF_DIG_IO = 0x0D,
        INIT_PWM = 0x0E,
        UPD_PWM = 0x0F,
        SET_SAMP_RATE = 0x12,
        START_STOP_AQ = 0x64,
        SET_TRANS_MODE = 0x65,
        READ_STATUS = 0xFD,
        SOFT_RST = 0xFE,
        GET_SW_VER = 0xFF,
    };

    enum DAQ_Status{
        DAQ_NOT_CONNECTED,
        DAQ_CONNECTED,
        DAQ_READY,
        DAQ_RUNNING,
        DAQ_ERR
    };

    enum DAQ_Channel{
        CH1 = 0,
        CH2 = 1,
        CH3 = 2,
        CH4 = 3,
        CH5 = 4,
        CH6 = 5,
        CH7 = 6,
        CH8 = 7,
        CH_ALL = 0x20,
        CH_ENABLE = 0x80
    };

    enum DAQ_DAC_Mode{
        DAC_0_5 = 0,
        DAC_0_10 = 0x40,
        DAC_M5_5 = 0x80,
        DAC_M10_10 = 0xC0
    };

    explicit daq(QWidget *parent = nullptr);
    ~daq();

    void tick();
    void sendStateRequest(StateRequest pRequest);

    void setFrequency(double freq);

private slots:
    void on_btnConnect_clicked();
    void on_serial_read();

private:
    Ui::daq *ui;
    const ControlVariableList& cntrVariables;
    const LogVariableList& logVariables;
    State state;
    int tickCnt;
    QSerialPort mSerial;
    QByteArray mSerialBuf;
    double adc[8];
    double dac[8];
    int enc[8];
    int out[4];
    int in[4];
    DAQ_Status mDeviceStatus;
    double mFreq;

    void init();

    void daq_reset();
    void daq_init();
    void daq_start(uint8_t status);

    void daq_upd_dac(uint8_t channel, double data);
};

#endif // DAQ_H
