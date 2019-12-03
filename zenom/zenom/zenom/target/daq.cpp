#include "daq.h"
#include "ui_daq.h"

daq::daq(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::daq),
    cntrVariables(DataRepository::instance()->controlVariables()),
    logVariables(DataRepository::instance()->logVariables())
{
    ui->setupUi(this);
    tickCnt = 0;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->cbPorts->addItem(info.portName());
    }

    connect(&mSerial, SIGNAL(readyRead()), this, SLOT(on_serial_read()));
    mDeviceStatus = DAQ_NOT_CONNECTED;
}

daq::~daq()
{
    delete ui;
}


void daq::tick(){
    tickCnt++;
    if(state == RUNNING){

        //ouputs (dac)
        for(int i=0; i<ui->tblOut->rowCount(); i++){
            if(ui->tblOut->item(i,1) == nullptr) continue;
            QString varName = ui->tblOut->item(i,1)->text();
            QString channel = ui->tblOut->item(i,0)->text();
            if( varName != ""){
                for(uint j=0; j<logVariables.size(); j++){
                    if(QString::fromStdString(logVariables.at(j)->name()) == varName){
                        if(!logVariables.at(j)->isHeapValid()) break;
                        double val = logVariables.at(j)->lastHeapElement(0,0);
                        if(channel.startsWith("DAC")){
                            uint8_t chn = channel.at(3).toAscii() - '0' - 1;
                            daq_upd_dac(chn, val);
                            break;
                        }
                    }
                }
            }
        }//output for
        //inputs
        for(int i=0; i<ui->tblIn->rowCount(); i++){
            if(ui->tblIn->item(i,1) == nullptr) continue;
            QString varName = ui->tblIn->item(i,1)->text();
            QString channel = ui->tblIn->item(i,0)->text();
            if( varName != ""){
                for(uint j=0; j<cntrVariables.size(); j++){
                    if(QString::fromStdString(cntrVariables.at(j)->name()) == varName){
                        if(channel.startsWith("ADC")){
                            uint8_t chn = channel.at(3).toAscii() - '0' - 1;
                            cntrVariables[j]->setHeapElement(0, adc[chn]);
                            break;
                        }
                        if(channel.startsWith("ENC")){
                            uint8_t chn = channel.at(3).toAscii() - '0';
                            cntrVariables[j]->setHeapElement(0, enc[chn]);
                            break;
                        }
                    }
                }
            }
        }//input for
    } //running
}

void daq::sendStateRequest(StateRequest pRequest)
{
    if(pRequest == R_INIT){
        state = STOPPED;
        ui->label->setText("INIT: " + QString(tickCnt));
        init();
    } else if(pRequest == R_START){
        state = RUNNING;
        ui->label->setText("START: " + QString(tickCnt));
        daq_init();
        daq_start(1);
    } else if(pRequest == R_PAUSE){
        state = PAUSED;
        ui->label->setText("PAUSED: " + QString(tickCnt));
        daq_start(0);
    } else if(pRequest == R_RESUME){
        state = RUNNING;
        ui->label->setText("RESUMED: " + QString(tickCnt));
        daq_start(1);
    } else if(pRequest == R_STOP){
        state = STOPPED;
        ui->label->setText("STOPPED: " + QString(tickCnt));
        daq_start(0);
    } else if(pRequest == R_TERMINATE){
        state = TERMINATED;
        ui->label->setText("TERMINATED: " + QString(tickCnt));
        daq_start(0);
        daq_reset();
    }
}


void daq::init(){
    ui->tblOut->clear();
    ui->tblIn->clear();

    if(ui->tblOut->itemDelegateForColumn(1) != nullptr)
        delete ui->tblOut->itemDelegateForColumn(1);

    if(ui->tblIn->itemDelegateForColumn(1) != nullptr)
        delete ui->tblIn->itemDelegateForColumn(1);

    QStringList inputs = {"ADC1", "ADC2", "ADC3", "ADC4", "ADC5", "ADC6", "ADC7", "ADC8",
                          "ENC1", "ENC2", "ENC3", "ENC4", "ENC5", "ENC6", "ENC7", "ENC8",
                          "I1", "I2", "I3", "I4"};

    QStringList outputs = {"DAC1", "DAC2", "DAC3", "DAC4", "DAC5", "DAC6", "DAC7", "DAC8",
                           "O1", "O2", "O3", "O4"};

    ui->tblIn->setRowCount(inputs.length());
    for(int i=0; i<inputs.length(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(inputs[i]);
        ui->tblIn->setItem(i,0,item);
    }

    ui->tblOut->setRowCount(outputs.length());
    for(int i=0; i<outputs.length(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(outputs[i]);
        ui->tblOut->setItem(i,0,item);
    }

    QStringList logVarList = QStringList();
    QStringList cntVarList = QStringList();
    for(int i=0; i<logVariables.size(); i++){
        logVarList.append(QString::fromStdString(logVariables.at(i)->name()));
    }
    for(int i=0; i<cntrVariables.size(); i++){
        cntVarList.append(QString::fromStdString(cntrVariables.at(i)->name()));
    }

    ComboBoxItemDelegate *cbid = new ComboBoxItemDelegate(logVarList, ui->tblOut);
    ui->tblOut->setItemDelegateForColumn(1, cbid);

    ComboBoxItemDelegate *cbid2 = new ComboBoxItemDelegate(cntVarList, ui->tblIn);
    ui->tblIn->setItemDelegateForColumn(1, cbid2);

}


void daq::on_btnConnect_clicked()
{
    mSerial.setPortName(ui->cbPorts->currentText());
    mSerial.setBaudRate(115200);
    if(mSerial.open(QIODevice::ReadWrite)){
        ui->lblCommStatus->setText("OK");
        mDeviceStatus = DAQ_CONNECTED;
    }
}


void daq::daq_reset(){
    uint8_t cmd[] = {SOFT_RST, SOFT_RST, SOFT_RST};
    mSerial.write((const char*)cmd, sizeof (cmd));
    mDeviceStatus = DAQ_READY;
}

void daq::daq_upd_dac(uint8_t channel, double data){
    //TODO: dac mode gore heseplamayi yap. su an 0 5 kabul ettik.
    if(data < 0) data = 0;
    if(data > 5) data = 5;
    int dac = data/5.0*16284.0;
    uint8_t d1 = dac;
    uint8_t d2 = (dac >> 8);
    uint8_t cmd[] = {UPD_DAC, channel, d1, d2 };
    int ret = mSerial.write((const char*)cmd, sizeof (cmd));
    std::cout << "Dac: " << (int)channel << ", " << data << ", " << ret << std::endl;
}

void daq::setFrequency(double freq){
    mFreq = freq;
}


void daq::daq_init(){
    int sampleRate = (int)((1.0/mFreq) / 0.0002);
    ui->lblSamplingRate->setText(QString::number(sampleRate));
    uint8_t s1 = sampleRate;
    uint8_t s2 = (sampleRate >> 8);
    uint8_t s3 = (sampleRate >> 16);

    int encRate = ui->spEnc->value() - 1;
    uint8_t e1 = encRate;
    uint8_t e2 = (encRate >> 8);
    uint8_t e3 = (encRate >> 16);

    int pwmFreq = ui->spPWM->value();
    //PWM = (84000/prescaler) / period;
    //presacler = 84 => period = 1000/PWM;
    int prescaler = 84 - 1;
    int period = 1000/pwmFreq - 1;
    uint8_t p1 = period;
    uint8_t p2 = (period >> 8);
    uint8_t c1 = prescaler;
    uint8_t c2 = (prescaler >> 8);

    uint8_t cmd[] = {SOFT_RST,
                     SOFT_RST,
                     SOFT_RST,
                     SET_SAMP_RATE, s1, s2, s3,
                     RST_ENC_CNT, CH_ALL | CH_ENABLE, //reset all encoder counters
                     SET_ENC_MAX_CNT, CH_ALL, e1, e2, e3,
                     SET_ENC_VEL_PER, CH_ALL, 0, 0,
                     INIT_PWM, CH_ALL, p1, p2, c1, c2,
                     INIT_ADC, CH_ALL | CH_ENABLE, //Enable all ADC's
                     INIT_DAC, CH_ALL | DAC_0_5, s1, s2, //Enable all DAC's with 0-5v range
                     SET_TRANS_MODE, 1 //send data immediately
                     };
    int ret = mSerial.write((const char*)cmd, sizeof (cmd));
}

void daq::daq_start(uint8_t status){
    uint8_t cmd[] = {START_STOP_AQ, status};
    mSerial.write((const char*)cmd, sizeof (cmd));
}

void daq::on_serial_read(){

    mSerialBuf.append(mSerial.readAll());
    while(mSerialBuf.size() > 4){
        uint8_t signature = mSerialBuf.at(0) & 0xF0;
        uint8_t channel = mSerialBuf.at(0) & 0x0F;
        bool err = false;

        switch (signature) {
        case SIG_ANALOG_IN:
            if(channel < 8)
                adc[channel] = (mSerialBuf.at(1) + (mSerialBuf.at(2)>>8))/(16384.0)*(5.0);
            //todo: update control variables
            break;
        case SIG_ENCODER_IN:
            if(channel < 8)
                enc[channel] = mSerialBuf.at(1) + (mSerialBuf.at(2) >> 8) + (mSerialBuf.at(2) >> 16);
            //todo: update control variables
            break;
        case SIG_DIGITAL_IN:
            in[0] = mSerialBuf.at(1) & 0x01;
            in[1] = (mSerialBuf.at(1) & 0x02) >> 1;
            in[2] = (mSerialBuf.at(1) & 0x04) >> 2;
            in[3] = (mSerialBuf.at(1) & 0x08) >> 3;
            //todo: update control variables
            break;
        case SIG_DEV_STATUS:
        case SIG_EOF:
            ui->lblCommErr->setText(QString::number(mSerialBuf.at(1)));
            ui->lblUSBErr->setText(QString::number(mSerialBuf.at(2)));
            ui->lblGenericErr->setText(QString::number(mSerialBuf.at(3)));
            break;
        case SIG_TIMESTAMP:
        case SIG_SW_INFO:
            break;
        default:
            //an error occured
            //remove a char
            err = true;
            mSerialBuf.remove(0,1);
            mDeviceStatus = DAQ_ERR;
            break;
        }
        if(!err){
            //a succesfull frame gathered and processed, remove it now.
            mSerialBuf.remove(0,4);
            mDeviceStatus = DAQ_RUNNING;
        }
    }
}
