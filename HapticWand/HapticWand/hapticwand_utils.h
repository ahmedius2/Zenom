#ifndef HAPTICWAND_UTILS_H
#define HAPTICWAND_UTILS_H


/**
 * A quaternion class.
 * It can be used to represent an orientation in 3D space.
 */
class Quaternion
{
public:

    inline Quaternion( double x = 0, double y = 0, double z = 0, double w = 1.0 )
    {
        _v[0]=x;
        _v[1]=y;
        _v[2]=z;
        _v[3]=w;
    }

    inline void set(double x, double y, double z, double w)
    {
        _v[0]=x;
        _v[1]=y;
        _v[2]=z;
        _v[3]=w;
    }

    inline double & x() { return _v[0]; }
    inline double & y() { return _v[1]; }
    inline double & z() { return _v[2]; }
    inline double & w() { return _v[3]; }

    void makeRotate( double angle, double x, double y, double z );

    inline const Quaternion operator*(const Quaternion& rhs) const
     {
         return Quaternion( rhs._v[3]*_v[0] + rhs._v[0]*_v[3] + rhs._v[1]*_v[2] - rhs._v[2]*_v[1],
              rhs._v[3]*_v[1] - rhs._v[0]*_v[2] + rhs._v[1]*_v[3] + rhs._v[2]*_v[0],
              rhs._v[3]*_v[2] + rhs._v[0]*_v[1] - rhs._v[1]*_v[0] + rhs._v[2]*_v[3],
              rhs._v[3]*_v[3] - rhs._v[0]*_v[0] - rhs._v[1]*_v[1] - rhs._v[2]*_v[2] );
     }

private:
    double  _v[4];
};

/**
 * Transforms from haptic wand coordinate system to OpenSceneGraph.
 *
 * @param worldCoordinates  Haptic wand coordinate system.
 * @param position (output) Openscenegraph x,y,z position.
 * @param rotation (output) Openscenegraph rotation (radians).
 */
void transformToOSG( double worldCoordinates[5], double position[3], double rotation[4] );

#endif // HAPTICWAND_UTILS_H
