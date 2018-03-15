#include "hapticwand_utils.h"
#include <math.h>

void Quaternion::makeRotate( double angle, double x, double y, double z )
{
    const double epsilon = 0.0000001;

    double length = sqrt( x*x + y*y + z*z );
    if (length < epsilon)
    {
        // ~zero length axis, so reset rotation to zero.
        *this = Quaternion();
        return;
    }

    double inversenorm  = 1.0/length;
    double coshalfangle = cos( 0.5*angle );
    double sinhalfangle = sin( 0.5*angle );

    _v[0] = x * sinhalfangle * inversenorm;
    _v[1] = y * sinhalfangle * inversenorm;
    _v[2] = z * sinhalfangle * inversenorm;
    _v[3] = coshalfangle;
}

void transformToOSG( double worldCoordinates[5], double position[3], double rotation[4] )
{
    // Position
    position[0] = -worldCoordinates[0];
    position[1] = -worldCoordinates[1];
    position[2] =  worldCoordinates[2];

    // Rotation
    Quaternion q1; q1.makeRotate( -worldCoordinates[3], 1, 0, 0 );
    Quaternion q2; q2.makeRotate( -worldCoordinates[4], 0, 1, 0 );
    Quaternion q = q1 * q2;

    rotation[0] = q.x();
    rotation[1] = q.y();
    rotation[2] = q.z();
    rotation[3] = q.w();
}
