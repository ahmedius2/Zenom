#ifndef LINESIZECOMBOBOX_H
#define LINESIZECOMBOBOX_H

#include <QComboBox>

class LineSizeComboBox : public QComboBox
{
    Q_OBJECT
public:
    LineSizeComboBox(QWidget *parent = 0);

    void setSize(const int);
    
signals:
    void sizeChanged(int);
    
public slots:
    void on_SelectedSizeChanged(int);

protected:
    void fillComboBox();
    
};

#endif // LINESIZECOMBOBOX_H
