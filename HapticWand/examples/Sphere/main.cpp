/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * Sphere - Virtual Reality Example
 * When the sphere is touched, a force feedback control allows the user
 * to feel a slightly spongy sphere.
 *
 */

#include <controlbase.h>
#include <hapticwand.h>
#include <hapticwand_utils.h>
#include <ColumnVector.hpp>
#include <Euler2DigitalFilter.hpp>

using namespace std;
using namespace Hardware;

class Sphere : public ControlBase
{
public:
    
    // ----- User Functions -----
    // This functions need to be implemented by the user.
    int initialize();
    int start();
    int doloop();
    int stop();
    int terminate();
    
private:
    /**
     * Detects collision. When the sphere is touched, calculates a force feedback.
     *
     * @param center        Center of object (m)
     * @param radius        Radius of object (m)
     * @param k_stiff       Stiffness gain (N/m)
     * @param k_damp        Damping gain (N.s/m)
     * @param w_xyz         World coordinates of wand (m,rad)
     * @param w_dot         World rate of wand (m/s,rad/s)
     *
     * @return F Output force (N)
     *
     */
    ColumnVector<5, double> virtual_object( ColumnVector<3, double>& center,
        double radius, ColumnVector<5, double>& k_stiff, ColumnVector<5, double>& k_damp,
        ColumnVector<3, double>& w_xyz, ColumnVector<5, double>& w_dot );

    // ----- Log Variables -----
    double position[3];             // position of the wand (openscenegraph coordinate system)
    double rotation[4];             // rotation of the wand (openscenegraph coordinate system)
    ColumnVector<5, double> F;      // world forces in N and world torques in N-m


    // ----- Control Variables -----


    // ----- Variables -----
    HapticWand hapticWand;  // 5-DOF Haptic Wand
    Euler2DigitalFilter< ColumnVector<5> > digitalFilter;
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int Sphere::initialize()
{
    registerLogVariable( position, "position", 1, 3 );
    registerLogVariable( rotation, "rotation", 1, 4 );
    registerLogVariable( F.getElementsPointer(), "F", 1, 5 );

    hapticWand.open();                  // Open the q8 card
    hapticWand.calibrateWand();         // Calibrate the haptic wand

    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int Sphere::start()
{
    hapticWand.enableWand();

    // Filter Cutoff (rad/s)
    double wn_f = 150;

    // Filter Damping Ratio
    double zeta_f = 1;

    digitalFilter.setSamplingPeriod( period() );
    digitalFilter.setCutOffFrequencyRad( wn_f );
    digitalFilter.setDampingRatio( zeta_f );

    ColumnVector<5> first_sample;
    first_sample =
            hapticWand.firstSample()[0],
            hapticWand.firstSample()[1],
            hapticWand.firstSample()[2],
            hapticWand.firstSample()[3],
            hapticWand.firstSample()[4];
    digitalFilter.reset( first_sample );

    return 0;
}


/**
 * This function is called periodically (as specified by the control frequency).
 * The useful functions that you can call used in doloop() are listed below.
 *
 * frequency()          returns frequency of simulation.
 * period()             returns period of simulation.
 * duration()           returns duration of simulation.
 * simTicks()           returns elapsed simulation ticks.
 * simTimeInNano()      returns elapsed simulation time in nano seconds.
 * simTimeInMiliSec()   returns elapsed simulation time in miliseconds.
 * simTimeInSec()       returns elapsed simulation time in seconds.
 * overruns()           returns the count of overruns.
 *
 * @return If you return 0, the control will continue to execute. If you return
 * nonzero, the control will abort and stop() function will be called.
 */
int Sphere::doloop()
{    
    ColumnVector<5> worldCoordinates;
    double jointAngles[6];        // joint angles in radians
    hapticWand.jointAngles( jointAngles );
    hapticWand.forwardKinematics( jointAngles, worldCoordinates.getElementsPointer() );

    // transform to openscenegraph coordinate system.
    transformToOSG( worldCoordinates.getElementsPointer(), position, rotation );

    // Center of Ball (m)
     ColumnVector<3> vo_c;
     vo_c = 0, 0.124, -0.075;

     // Radius of Ball (m)
     double vo_r = 0.05;

     // Stiffness (N/m)
     ColumnVector<5> kp;
     kp = 500, 500, 500, 1, 1;

     // Damping (N.s/m, N.s/rad)
     ColumnVector<5> kd;
     kd = 5, 5, 5, 0.1, 0.1;

     // Posion of Wand
     ColumnVector<3> w_xyz;
     w_xyz = worldCoordinates(1), worldCoordinates(2), worldCoordinates(3);

     // world rate of wand (m/s,rad/s)
     ColumnVector<5> w_dot = digitalFilter.integrate( worldCoordinates );

     // World forces in N and world torques in N-mm
     F = virtual_object( vo_c, vo_r, kp, kd, w_xyz, w_dot );

     // Generate the forces and torques for the Haptic Wand
     hapticWand.generateForces( period(), jointAngles, F.getElementsPointer() );

     return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int Sphere::stop()
{
    hapticWand.disableWand();
    
    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int Sphere::terminate()
{
    hapticWand.close();
    
    return 0;
}


ColumnVector<5, double> Sphere::virtual_object( ColumnVector<3, double>& center,
    double radius, ColumnVector<5, double>& k_stiff, ColumnVector<5, double>& k_damp,
    ColumnVector<3, double>& w_xyz, ColumnVector<5, double>& w_dot )
{
    // Output Force (N)
    ColumnVector<5> F;

    // Vector from object to wand (m)
    ColumnVector<3> r = w_xyz - center;
    // Distance of r (m)
    double r_abs = r.norm();

    // Is wand inside object?
    if ( r_abs < radius )
    {
        // normalized direction vector
        ColumnVector<3> dir = r / r_abs;

        // stiffness force (N)
        ColumnVector<5> F_stiff;
        F_stiff =
                dir.getElement(1) * k_stiff.getElement(1) * (radius - r_abs),
                dir.getElement(2) * k_stiff.getElement(2) * (radius - r_abs),
                dir.getElement(3) * k_stiff.getElement(3) * (radius - r_abs),
                0,
                0;

        // damping force (N)
        ColumnVector<5, double> F_damp = elementProduct( k_damp, w_dot );
        F_damp *= -1;

        // total force
        F = F_stiff + F_damp;
    }
    else
    {
        // Wand not touching object.
        F = 0;
    }

    return F;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    Sphere c;
    c.run( argc, argv );
    
    return 0;
}

