/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author
 *
 * %ProjectName%
 *
 *
 */

#include <controlbase.h>

class %ProjectName% : public ControlBase
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


    // ----- Control Variables -----


    // ----- Variables -----
 };

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int %ProjectName%::initialize()
{


    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int %ProjectName%::start()
{


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
int %ProjectName%::doloop()
{


    return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int %ProjectName%::stop()
{


    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int %ProjectName%::terminate()
{


    return 0;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    %ProjectName% c;
    c.run( argc, argv );

    return 0;
}
