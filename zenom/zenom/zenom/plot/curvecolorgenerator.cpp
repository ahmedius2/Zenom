#include "curvecolorgenerator.h"

CurveColorGenerator::CurveColorGenerator() : mColorIndex(0)
{
    mColorVec.push_back( QColor(0, 0, 255) );
    mColorVec.push_back( QColor(0, 255, 0) );
    mColorVec.push_back( QColor(255, 0, 0) );
    mColorVec.push_back( QColor(0, 0, 44) );
    mColorVec.push_back( QColor(255, 26, 185) );
    mColorVec.push_back( QColor(255, 211, 0) );
    mColorVec.push_back( QColor(0, 88, 0) );
    mColorVec.push_back( QColor(132, 132, 255) );
    mColorVec.push_back( QColor(158, 79, 70) );
    mColorVec.push_back( QColor(0, 255, 194) );
    mColorVec.push_back( QColor(0, 132, 150) );
    mColorVec.push_back( QColor(0, 0, 123) );
    mColorVec.push_back( QColor(150, 211, 79) );
    mColorVec.push_back( QColor(247, 158, 220) );
    mColorVec.push_back( QColor(211, 17, 255) );
}

QColor CurveColorGenerator::generateColor()
{
    return mColorVec[ (++mColorIndex)%mColorVec.size()];
}


void CurveColorGenerator::increaseIndex()
{
    ++mColorIndex;
}

void CurveColorGenerator::reset()
{
    mColorIndex = 0;
}
