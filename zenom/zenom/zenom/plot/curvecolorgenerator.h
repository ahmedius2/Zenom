#ifndef CURVECOLORGENERATOR_H
#define CURVECOLORGENERATOR_H

#include <QVector>
#include <QColor>


class CurveColorGenerator
{
public:
    CurveColorGenerator();
    QColor generateColor();
    void increaseIndex();
    void reset();

protected:
    QVector< QColor> mColorVec;
    int mColorIndex;
};

#endif // CURVECOLORGENERATOR_H
