#include "linesizecombobox.h"
#include <QIcon>

#define LINE_SIZE_COUNT 10

LineSizeComboBox::LineSizeComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillComboBox();
    connect(this, SIGNAL( currentIndexChanged(int) ), SLOT( on_SelectedSizeChanged(int) ));
}

void LineSizeComboBox::on_SelectedSizeChanged(int pIndex)
{
    emit sizeChanged(pIndex);
}

void LineSizeComboBox::fillComboBox()
{

    for (int i = 1; i < LINE_SIZE_COUNT; ++i)
    {
        QSize pixmapSize(35, i+2);
        QPixmap pixmap(pixmapSize);
        pixmap.fill(Qt::black);
        QIcon *icon = new QIcon(pixmap);

        this->addItem(*icon, "");
    }
}

void LineSizeComboBox::setSize(const int pSize)
{
    if (pSize >= 0 && pSize < LINE_SIZE_COUNT )
    {
        setCurrentIndex(pSize);
    }
}
