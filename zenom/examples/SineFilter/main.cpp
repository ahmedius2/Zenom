/**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * SineFilter
 * Generates a noisy sinus signal and filter it.
 *
 */

#include <controlbase.h>
#include <math.h>
#include <ButterworthFilter.hpp>

class SineFilter : public ControlBase
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
    double noisySignal;
    double filteredSignal;

    // ----- Control Variables -----
    double amplitude;
    double cutOffFrequency;
    double dampingRatio;

    // ----- Variables -----
    ButterworthFilter<double> filter;
};

/**
 * This function is called when the control program is loaded to zenom.
 * Use this function to register control parameters, to register log variables
 * and to initialize control parameters.
 *
 * @return Return non-zero to indicate an error.
 */
int SineFilter::initialize()
{
    // ----- Initializes log and control variables -----
    // ----- Register the log variables -----
    registerLogVariable(&sine, "sine");
    registerLogVariable(&noisySignal, "noisySignal");
    registerLogVariable(&filteredSignal, "filteredSignal");

    // ----- Register the control paramateres -----
    registerControlVariable(&amplitude, "amplitude");
    registerControlVariable(&cutOffFrequency, "cutOffFrequency");
    registerControlVariable(&dampingRatio, "dampingRatio");

    std::cout
        << "This example program generates a noisy sine wave "
        << "and uses a Butterworth filter to remove the noise." << std::endl;

    return 0;
}

/**
 * This function is called when the START button is pushed from zenom.
 *
 * @return If you return 0, the control starts and the doloop() function is
 * called periodically. If you return nonzero, the control will not start.
 */
int SineFilter::start()
{
    // ----- Initializes filter attributes -----
    filter.setSamplingTime(period());
    filter.setAutoInit();

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
int SineFilter::doloop()
{
    // ----- Sets filter attributes online.
    filter.setCutOffFrequency(cutOffFrequency);
    filter.setDampingRatio(dampingRatio);

    // ----- Geneates a noisy sine signal and uses filter -----
    double time = simTimeInSec();
    double noise = amplitude / 40 * sin(20 * time) + (rand() % 3) / 10.0;
    sine = amplitude * sin(2 * M_PI * time);

    // ----- Create a noisy signal -----
    noisySignal = sine + noise;

    // ----- Now filter it -----
    filteredSignal = filter.filter(noisySignal);

    return 0;
}


/**
 * Called when a timed run ends or the STOP button is pushed from zenom.
 *
 * @return Return non-zero to indicate an error.
 */
int SineFilter::stop()
{


    return 0;
}


/**
 * This function is called when the control is unloaded. It happens when
 * the user loads a new control program or exits.
 *
 * @return Return non-zero to indicate an error.
 */
int SineFilter::terminate()
{


    return 0;
}


/**
 * The main function starts the control program
 */
int main( int argc, char *argv[] )
{
    SineFilter c;
    c.run( argc, argv );

    return 0;
}
