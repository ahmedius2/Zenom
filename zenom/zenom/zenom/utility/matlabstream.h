#ifndef MATLABSTREAM_H
#define MATLABSTREAM_H

#include <QTextStream>
#include <logvariable.h>
#include "widget/logvariableitem.h"

class MatlabStream : public QTextStream
{
public:
    MatlabStream(QIODevice * pDevice);

    /**
     * Verilen log variable ait degerler matlab formatina uygun
     * olarak stream'e yazilir.
     * @param pLogVariable stream'e yazilacak kayit degiskeni
     */
    void writeLogVariable( LogVariable* pLogVariable );

    /**
     * Verilen satir ve sutundaki log variable ait degerler matlab formatina uygun
     * olarak stream'e yazilir.
     * @param pLogVariable stream'e yazilacak kayit degiskeni
     * @param pRow stream'e yazilacak kayit degiskeninin satiri
     * @param pColumn stream'e yazilacak kayit degiskeninin sutunu
     */
    void writeLogVariableItem( LogVariable* pLogVariable, unsigned int pRow, unsigned int pColumn );

    /**
     * Verilen log variable ait zaman etiketleri matlab formatina uygun
     * olarak stream'e yazilir.
     * @param pLogVariable stream'e yazilacak kayit degiskeni
     */
    void writeLogVariableTime( LogVariable* pLogVariable );

private:
    /**
     * Verilen satir ve sutundaki log variable ait degerler matlab formatina uygun
     * olarak stream'e yazilir.
     * @param pLogVariable stream'e yazilacak kayit degiskeni
     * @param pRow stream'e yazilacak kayit degiskeninin satiri
     * @param pColumn stream'e yazilacak kayit degiskeninin sutunu
     */
    void writeLogVariable( LogVariable* pLogVariable, unsigned int pRow, unsigned int pColumn );
};

#endif // MATLABSTREAM_H
