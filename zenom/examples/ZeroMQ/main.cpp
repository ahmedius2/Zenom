/**

 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * ZeroMQ
 * A simple example of a control program.
 * Does not require any hardware, just generates a sine signal.
 */
#include <iostream>
#include <controlbase.h>
#include <math.h>

class ZeroMQ : public ControlBase
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
    double sine;


    // ----- Control Parameters -----
    double amplitude;
    double key_a;
    double key_s;
    double key_d;
    double key_w;


    // ----- Variables -----
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int ZeroMQ::initialize()
{
    // ----- Initializes log and control variables -----
    // ----- Register the log variables -----
    registerLogVariable(&sine, "sine");

    // ----- Register the control paramateres -----
    registerControlVariable(&amplitude, "amplitude");
    amplitude = 3;
    registerControlVariable(&key_a, "key_a");
    key_a = 0;
    registerControlVariable(&key_s, "key_s");
    key_s = 0;
    registerControlVariable(&key_d, "key_d");
    key_d = 0;
    registerControlVariable(&key_w, "key_w");
    key_w = 0;

    // ----- Prints message in screen -----
    std::cout
        << "This is a simple control program that generates "
        << "a sine wave and doesn't access any hardware."
        << "Use the amplitude control parameter to change "
        << "the amplitude of the sine wave" << std::endl << std::endl;

    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int ZeroMQ::start()
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
 * nonzero, the control will abort.
 */
int ZeroMQ::doloop()
{
    // ----- Generates sine wave -----
    sine = amplitude * sin( elapsedTime() ) *key_a;
    return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int ZeroMQ::stop()
{


    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int ZeroMQ::terminate()
{


    return 0;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    ZeroMQ c;
    c.run( argc, argv );

    return 0;
}
