/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * BouncingBall
 * This example simulates a bouncing ball from floor.
 *
 */

#include <controlbase.h>
#include <Integrator.hpp>

class BouncingBall : public ControlBase
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
    // ----- Log Variables -----
    double velocity;    // velocity of ball
    double position[3]; // position of ball

    // ----- Control Variables -----
    double g;       // gravity
    double cor;     // coefficient of restitution

    // ----- Variables -----
    Integrator< double > mVelocityIntegrator;   // velocity integrator
    Integrator< double > mPositionIntegrator;   // position integrator
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int BouncingBall::initialize()
{
    registerLogVariable(&velocity, "velocity");
    registerLogVariable(position, "position", 1, 3);

    registerControlVariable(&g, "g");
    registerControlVariable(&cor, "cor");

    g = -9.81;   // m/s^2
    cor = -0.8;  // coefficient of restitution

    position[0] = 0;
    position[1] = 0;

    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int BouncingBall::start()
{
    mVelocityIntegrator.setSamplingPeriod( period() );
    mVelocityIntegrator.reset( 0 );  // initial speed 0 m/s

    mPositionIntegrator.setSamplingPeriod( period() );
    mPositionIntegrator.reset( 15.0 );  // initial height 15 m

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
 * nonzero, the control will abort.
 */
int BouncingBall::doloop()
{
    double ballRadius = 1;

    velocity = mVelocityIntegrator.integrate( g );
    position[2] = mPositionIntegrator.integrate( velocity );   // position of ball

    // saturation
    if ( position[2] <= ballRadius )
    {
        position[2] = ballRadius;
    }

    // Hits the floor
    if ( position[2] == ballRadius )
    {
        mVelocityIntegrator.reset( velocity * cor );
        mPositionIntegrator.reset( ballRadius );
    }

    return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int BouncingBall::stop()
{


    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int BouncingBall::terminate()
{


    return 0;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    BouncingBall c;
    c.run( argc, argv );

    return 0;
}
