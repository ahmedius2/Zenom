#include "checkedheader.h"

#include <iostream>
 
CheckedHeader::CheckedHeader(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    // set clickable by default
#if QT_VERSION < 0x050000
    setClickable(true);
#else
    setSectionsClickable(true);
#endif
    connect(this, SIGNAL(sectionCountChanged(int,int)), SLOT(sectionCountChanged(int,int)));
}

bool CheckedHeader::isChecked(int index)
{
    return mIsOn[index];
}
 
void CheckedHeader::setChecked(int index, bool checked)
{
    if (isEnabled() && mIsOn[index] != checked)
    {
        mIsOn[index] = checked;
        updateSection(index);
        emit toggled(index, mIsOn[index]);
    }
}
 
void CheckedHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
	QStyleOptionHeader opt;
	initStyleOption(&opt);
	opt.rect = rect;
	opt.section = logicalIndex;
	style()->drawControl(QStyle::CE_Header, &opt, painter, this);
    painter->restore();

	QStyleOptionButton option;
	if (isEnabled())
		option.state |= QStyle::State_Enabled;
	option.rect = checkBoxRect(rect);
	if ( mIsOn[logicalIndex] )
		option.state |= QStyle::State_On;
	else
		option.state |= QStyle::State_Off;
	style()->drawControl(QStyle::CE_CheckBox, &option, painter);
}
 
void CheckedHeader::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled())
    {
        int index = logicalIndexAt(event->pos());
        mIsOn[index] = !mIsOn[index];
        updateSection( index );
        emit toggled(index, mIsOn[index]);
    }
    else
        QHeaderView::mousePressEvent(event);
}

void CheckedHeader::sectionCountChanged(int, int newCount)
{
    mIsOn.resize( newCount );
}
 
QRect CheckedHeader::checkBoxRect(const QRect &sourceRect) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect checkBoxRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator,
                                                 &checkBoxStyleOption);
    QPoint checkBoxPoint(sourceRect.x() +
                         sourceRect.width() / 2 -
                         checkBoxRect.width() / 2,
                         sourceRect.y() +
                         sourceRect.height() / 2 -
                         checkBoxRect.height() / 2);
    return QRect(checkBoxPoint, checkBoxRect.size());
}
