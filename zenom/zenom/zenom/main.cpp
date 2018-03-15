#include <sys/mman.h>
#include <QtGui/QApplication>
#include "zenom.h"

#if QT_VERSION < 0x050000
#include <QGtkStyle>
#endif

int main(int argc, char *argv[])
{
    mlockall ( MCL_CURRENT | MCL_FUTURE );

    QApplication a(argc, argv);
    a.setOrganizationName( "RobotLab" );
    a.setApplicationName( "Zenom" );
	
#if QT_VERSION < 0x050000
    a.setStyle(new QGtkStyle());
#endif

    Zenom w(argc, argv);
    w.show();

    return a.exec();
}
