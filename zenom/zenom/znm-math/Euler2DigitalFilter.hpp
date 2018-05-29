 /**
 * Zenom - Hard Real-Time Simulation Enviroment
 * @author zenom
 *
 * Quanser Tunable Functions 2'nd Order Digital Input Filter.
 *
 */

#ifndef EULER_2_DIGITAL_FILTER_INTEGRATOR_H
#define EULER_2_DIGITAL_FILTER_INTEGRATOR_H

#include "Integrator.hpp"
#include <math.h>
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

/**
 *
 * Numerical integration using Forward Euler 2'nd order method.
 * Quanser Tunable Functions 2'nd Order Digital Input Filter.
 *
 */
template<class T = double>
class Euler2DigitalFilter : public Integrator<T>
{
public:
    /**
     * The default constructor.
     * The sampling period is set to default of 0.001 seconds.
     * The cut-off frequency is set to default of 1 hertz.
	 * The damping ratio is set to default of 1
	 * The initial output value is set to 0.
     */
	inline Euler2DigitalFilter();

    /**
     * The constructor with initialization for the sampling period and initial
	 * value.
     *
     * @param period	The sampling period in seconds.
	 * @param init		The initial value at the start.
     */
	inline Euler2DigitalFilter(double period, const T &init);

    /**
     * The destructor 
     */
	virtual ~Euler2DigitalFilter() {};

    /**
     * Sets the cut-off frequency of the filter in hertz. 
     *
     * @param hz	Desired the cut-off frequency of the filter
     */
	inline void setCutOffFrequencyHz(double hz);
	
    /**
     * Sets the cut-off frequency of the filter in rad/s. 
     *
     * @param rads	Desired the cut-off frequency of the filter
     */  
	inline void setCutOffFrequencyRad(double rads);

    /**
     * Gets the cut-off frequency of the filter in hertz. 
     *
     * @return	The cut-off frequency of the filter in hertz.
     */  
	inline double getCutOffFrequencyHz() const;

    /**
     * Gets the cut-off frequency of the filter in rad/s. 
     *
     * @return	The cut-off frequency of the filter in rad/s.
     */   
	inline double getCutOffFrequencyRad() const;

    /**
     * Sets the damping factor of the filter.
     *
     * @param damp	Desired damping ratio.
     */   
	inline void setDampingRatio(double damp);

    /**
     * Gets the damping factor of the filter.
     *
     * @return	The damping factor of the filter.
     */ 
	inline double getDampingRatio() const;


    /**
     * Resets the output of the Integrator to the value and further integration
	 * restarts from this initial value.
     *
     * @param init	Desired initial value.
     */  
	virtual void reset(const T &init);

    /**
     * The numerical method for integration.
     *
     * @param input	The current value of the time-varying signal to be
	 * integrated.
     */
	inline virtual T integrate(const T &input);

 private:
	  double d_cutOffFrequencyHz; 
	  double d_cutOffFrequencyRad; 
	  double d_dampingRatio;

	  T prevOutput2;
	  T prevOutput1;
};

//======================================================
// End of declarations.
//======================================================



//======================================================================== 
// Euler2DigitalFilter::Euler2DigitalFilter
//========================================================================  
template<class T>
Euler2DigitalFilter<T>::Euler2DigitalFilter():Integrator<T>()
{
	prevOutput2 = 0.0;
	prevOutput1 = 0.0;

	setDampingRatio( 1 );
	setCutOffFrequencyHz( 1 );
}

template<class T>
Euler2DigitalFilter<T>::Euler2DigitalFilter(double s, const T &i):Integrator<T>(s, i)
{
	reset(i);
	setDampingRatio( 1 );
	setCutOffFrequencyHz( 1 );
}


//============================================================
// Euler2DigitalFilter::setCutOffFrequencyHz
//============================================================
template<class T>
void Euler2DigitalFilter<T>::setCutOffFrequencyHz(double cutOffFrequencyHz)
{ 
	d_cutOffFrequencyHz = cutOffFrequencyHz; 
	d_cutOffFrequencyRad = 2 * M_PI * d_cutOffFrequencyHz;
}


//============================================================
// Euler2DigitalFilter::setCutOffFrequencyRad
//============================================================
template<class T>
void Euler2DigitalFilter<T>::setCutOffFrequencyRad(double cutOffFrequencyRad)
{ 
	d_cutOffFrequencyRad = cutOffFrequencyRad;
	d_cutOffFrequencyHz = 	d_cutOffFrequencyRad/(2 * M_PI);
}


//============================================================
// Euler2DigitalFilter::getCutOffFrequencyHz
//============================================================
template<class T>
double Euler2DigitalFilter<T>::getCutOffFrequencyHz() const
{ 
	return d_cutOffFrequencyHz;
}


//============================================================
// Euler2DigitalFilter::getCutOffFrequencyRad
//============================================================
template<class T>
double Euler2DigitalFilter<T>::getCutOffFrequencyRad() const
{ 
	return d_cutOffFrequencyRad;
}


//============================================================
// Euler2DigitalFilter::setDampingRatio
//============================================================
template<class T>
void Euler2DigitalFilter<T>::setDampingRatio(double dampingRatio)
{
	d_dampingRatio = dampingRatio;
}


//============================================================
// Euler2DigitalFilter::getDampingRatio
//============================================================
template<class T>
double Euler2DigitalFilter<T>::getDampingRatio() const
{ 
	return d_dampingRatio;
}

//======================================================================== 
// Euler2DigitalFilter::reset
//========================================================================  
template<class T>
void Euler2DigitalFilter<T>::reset(const T &resetToValue)
{
	prevOutput2 = resetToValue;
	prevOutput1 = 0.0;
}


//======================================================================== 
// Euler2DigitalFilter::integrate
//========================================================================  
template<class T>
T Euler2DigitalFilter<T>::integrate(const T &currentInput)
{
    // Quanser 5-DOF Haptic Wand
    // Matlab Quanser Tunable Functions
    // 2nd Order Digital Filter Input ICs

	T tmpPrevOutput2 = prevOutput2;
	T tmpPrevOutput1 = prevOutput1;

	T sum1 = currentInput - tmpPrevOutput2;
	T sum2 = sum1 - ( 2 * d_dampingRatio * tmpPrevOutput1 );
	T input1 = d_cutOffFrequencyRad * sum2;
	T input2 = d_cutOffFrequencyRad * tmpPrevOutput1;

	prevOutput2 = this->d_samplingPeriod * input2 + prevOutput2;
	prevOutput1 = this->d_samplingPeriod * input1 + prevOutput1;

    return input2;
}

#endif

