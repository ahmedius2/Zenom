#include "matlabstream.h"

MatlabStream::MatlabStream(QIODevice * pDevice)
    : QTextStream( pDevice )
{

}

void MatlabStream::writeLogVariable( LogVariable* pLogVariable )
{
    // Log variable degerleri yazilir.
    for ( unsigned int i = 0; i < pLogVariable->row(); ++i )
    {
        for ( unsigned int j = 0; j < pLogVariable->col(); ++j )
        {
            writeLogVariable( pLogVariable, i, j );
        }
    }

    // Log variable zaman degerleri yazilir.
    writeLogVariableTime( pLogVariable );
}

void MatlabStream::writeLogVariable( LogVariable* pLogVariable, unsigned int pRow, unsigned int pColumn )
{
    if ( !pLogVariable->isHeapValid() )
        return;

    // Degiskenin tek veya iki boyut olmasina gore yazilir.
    if ( pLogVariable->row() == 1 && pLogVariable->col() == 1 ) // Variable
    {
        (*this) << QString("%1 = [ ").arg( QString::fromStdString(pLogVariable->name()) );
    }
    else if ( pLogVariable->row() == 1 || pLogVariable->col() == 1 ) // Vector
    {
        (*this) << QString("%1(:,%2) = [ ").arg( QString::fromStdString(pLogVariable->name()) ).arg( pLogVariable->row() == 1 ? pColumn+1 : pRow+1);
    }
    else    // Matrices
    {
        (*this) << QString("%1(:,%2,%3) = [ ").arg( QString::fromStdString(pLogVariable->name()) ).arg(pRow+1).arg(pColumn+1);
    }

    // Degerler stream'e yazilir.
    for ( int i = 0; i < pLogVariable->heapSize(); ++i )
    {
        (*this) << pLogVariable->heapElement( i, pRow, pColumn ) << "; ";
    }

    (*this) << QString("];") << endl;
}

void MatlabStream::writeLogVariableItem( LogVariable* pLogVariable, unsigned int pRow, unsigned int pColumn )
{
    if ( !pLogVariable->isHeapValid() )
        return;

    // Degiskenin tek veya iki boyut olmasina gore yazilir.
    if ( pLogVariable->row() == 1 && pLogVariable->col() == 1 ) // Variable
    {
        (*this) << QString("%1 = [ ").arg( QString::fromStdString(pLogVariable->name()) );
    }
    else if ( pLogVariable->row() == 1 || pLogVariable->col() == 1 ) // Vector
    {
        (*this) << QString("%1_%2 = [ ").arg( QString::fromStdString(pLogVariable->name()) ).arg( pLogVariable->row() == 1 ? pColumn+1 : pRow+1);
    }
    else    // Matrices
    {
        (*this) << QString("%1_%2_%3) = [ ").arg( QString::fromStdString(pLogVariable->name()) ).arg(pRow+1).arg(pColumn+1);
    }

    // Degerler stream'e yazilir.
    for ( int i = 0; i < pLogVariable->heapSize(); ++i )
    {
        (*this) << pLogVariable->heapElement( i, pRow, pColumn ) << "; ";
    }

    (*this) << QString("];") << endl;
}

void MatlabStream::writeLogVariableTime( LogVariable* pLogVariable )
{
    if ( !pLogVariable->isHeapValid() )
        return;

    // Degisken ismi log variable ismine _t eklenerek olusturulur.
    (*this) << QString("%1_t = [ ").arg( QString::fromStdString(pLogVariable->name()) );

    // Zaman degerleri stream'e yazilir.
    for ( int i = 0; i < pLogVariable->heapSize(); ++i )
    {
        (*this) << pLogVariable->heapElement( i, pLogVariable->size() ) << "; ";
    }

    (*this) << QString("];") << endl;
}
