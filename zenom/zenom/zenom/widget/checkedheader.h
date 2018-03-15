#ifndef CHECKEDHEADER_H
#define CHECKEDHEADER_H
 
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
 
class CheckedHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit CheckedHeader(Qt::Orientation orientation, QWidget *parent = 0);
 
    bool isChecked(int index);
    void setChecked(int index, bool checked);
 
signals:
    void toggled(int index, bool checked);
 
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);

private slots:
    void sectionCountChanged(int, int newCount);
 
private:
    QRect checkBoxRect(const QRect &sourceRect) const;
    QVector<bool> mIsOn;
};
 
#endif // CHECKEDHEADER_H
