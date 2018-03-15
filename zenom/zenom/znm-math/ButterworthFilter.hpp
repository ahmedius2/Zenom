///=============================================================================
/// file   : ButterworthFilter.hpp
///-----------------------------------------------------------------------------
/// This file implements the template Filtering class. 
/// A second order Low-Pass ButterWorth Filter is implemented to filter out 
/// low frequency noise inherented form time derivative calculations,
/// measurement errors or noisy sensors.
/// 
///=============================================================================

#ifndef INCLUDED_BUTTERWORTHFILTER_HPP
#define INCLUDED_BUTTERWORTHFILTER_HPP

#ifdef MALLOC_DEBUG
#include "rmalloc.h"
#endif


template <class T>
class ButterworthFilter
{
	protected:

		//internal filter parameters
		double d_cutOffFrequency;
		double d_dampingFactor;
		double d_samplingTime;

		//Filter time parameters
		double d_numeratorParameter[3]; // filter numerator parameters
		double d_denumParameter[3];			// denumeraotr parameters

		int d_initFlag ; // initialization flag
		
		T d_previousInputX[3];   // Input related current and old values are stored in these variables
		T d_previousOutputY[3];	 // Output related variables
		
		T d_numerator;   // Auxiliary variables  for output calculations
		T d_denumerator;
            
		T d_filteredOut;// output returned to the user

		void calculateInternalParameters();
 
  public:
      ButterworthFilter(); 
      ButterworthFilter(double cutOffFrequency,
                        double dampingFactor,
                        double samplingTime ); 
	   ~ButterworthFilter(); 
      
		void setCutOffFrequency(double cutOffFrequency);
		double getCutOffFrequency();

		void setDampingRatio(double dampingRatio);
		double getDampingRatio();

		void setSamplingTime(double samplingTime);
		double getSamplingTime();

		void setAutoInit();
    void initializeFilter (T initInput, T initOutput);
    
    T filter(T input);
}; 


// ---- CREATORS

///=============================================================================
/// name   : ButterworthFilter
///-----------------------------------------------------------------------------
/// input  :
///         - natural frequency of the filter in radians,
///	        - damping factor for the filter (use values are between 0.77- 1.0 )
///					- sampling time to determine the sampling frequency 
///
/// Calculates the interparameters on the filter
/// 
///=============================================================================

template <class T>
ButterworthFilter<T>::ButterworthFilter ()     
{
	// set class parameters
	d_cutOffFrequency = 1;
	d_dampingFactor = 1;
	d_samplingTime = 1;
	
	//calculate the filter parameters
	calculateInternalParameters();
	
	d_initFlag = 1;
}


template <class T>
ButterworthFilter<T>::ButterworthFilter (double cutOffFrequency,
                                         double dampingFactor,
                                         double samplingTime)     
{
	// set class parameters
	d_cutOffFrequency = cutOffFrequency;
	d_dampingFactor = dampingFactor;
	d_samplingTime = samplingTime;
	
	//calculate the filter parameters
	calculateInternalParameters();
	
	d_initFlag = 1;
}


///=============================================================================
/// name   : ~ButterworthFilter
///-----------------------------------------------------------------------------
/// Destructor.  
///=============================================================================

template <class T>
ButterworthFilter<T>::~ButterworthFilter()
{
}
	

// ---- MANIPULATORS

///=============================================================================
/// name   :  calculateInternalParameters ()
///-----------------------------------------------------------------------------
///  calculates the internal filter parameters 
///  using the cutOfffrequency, dampingRatio and samplingTime
///
///=============================================================================
template <class T>
void ButterworthFilter<T>::calculateInternalParameters()
{
	// the filter parameter are transformed to discete domain using 
	// bilinear transformation 
	// calculate the numerator values first 
	d_numeratorParameter[0] = d_cutOffFrequency * d_cutOffFrequency;
	d_numeratorParameter[1] = 2*d_numeratorParameter[0];
	d_numeratorParameter[2] = d_numeratorParameter[0];

	// denum. parameter calculations
	d_denumParameter[0] = d_numeratorParameter[0]
                       + 4*d_cutOffFrequency*d_dampingFactor / d_samplingTime
                       + 4/(d_samplingTime * d_samplingTime);

	d_denumParameter[1] = d_numeratorParameter[1]
                       - 8/(d_samplingTime * d_samplingTime);

	d_denumParameter[2] = d_numeratorParameter[0]
                       - 4*d_cutOffFrequency*d_dampingFactor / d_samplingTime
                       + 4/(d_samplingTime * d_samplingTime) ;
}


///=============================================================================
/// name   :  initialize
///-----------------------------------------------------------------------------
///  sets the initilize falg of the class to one to reset the values of the 
///  of the filter or enable the automatic initialization section ..
/// 
///=============================================================================
template <class T>
void ButterworthFilter<T>::setAutoInit()
{
// enables the automatic initialization section of the filter
// by setting the initFlag to 1

	d_initFlag = 1;
//	return 1;
	
}


///=============================================================================
/// name   :  initializeFilter
///-----------------------------------------------------------------------------
/// input  :
/// 	- initInput, the initial values of the input signal 
///   - initOutput, the initial values for the output of the filter 
///    in most practical cases input and output values are initialized to the
///    same values
///=============================================================================
template <class T>
void ButterworthFilter<T>::initializeFilter (T initInput, T initOutput)
{
 for (int i=0; i<3; i++)
 {
	 d_previousInputX[i] = initInput;
	 d_previousOutputY[i] = initOutput;
 }
	d_initFlag = 0; // initialization is done
}


///=============================================================================
/// name   :  setCutOffFrequency(double cutOffFrequency)
///-----------------------------------------------------------------------------
///  
///=============================================================================
template <class T>
void ButterworthFilter<T>::setCutOffFrequency(double cuttOffFrequency)
{

	d_cutOffFrequency = cuttOffFrequency;
	calculateInternalParameters();

}


///=============================================================================
/// name   :  getCutOffFrequency()
///-----------------------------------------------------------------------------
///  returns the current value of filters cutOffFrequency
///=============================================================================
template <class T>
double ButterworthFilter<T>::getCutOffFrequency()
{
	return(d_cutOffFrequency);
}


///=============================================================================
/// name   :  setDampingRatio(double dampingRatio)
///-----------------------------------------------------------------------------
///  
///=============================================================================
template <class T>
void ButterworthFilter<T>::setDampingRatio(double dampingRatio)
{

	d_dampingFactor = dampingRatio;
	calculateInternalParameters();

}


///=============================================================================
/// name   :  getDampingRatio()
///-----------------------------------------------------------------------------
///  returns the current value of filters dapingRatio
///=============================================================================
template <class T>
double ButterworthFilter<T>::getDampingRatio()
{
	return(d_dampingFactor);
}


///=============================================================================
/// name   :  setSamplingFrequency(double samplingTime)
///-----------------------------------------------------------------------------
///  
///=============================================================================
template <class T>
void ButterworthFilter<T>::setSamplingTime(double samplingTime)
{

	d_samplingTime = samplingTime;
	calculateInternalParameters();

}


///=============================================================================
/// name   :  getSamplingFrequency()
///-----------------------------------------------------------------------------
///  returns the current value of filters samplingFrequency
///=============================================================================
template <class T>
double ButterworthFilter<T>::getSamplingTime()
{
	return(d_samplingTime);
}



///=============================================================================
/// name   :  filter 
///-----------------------------------------------------------------------------
/// input  :
/// 	- input, signal to be filyered 
/// returns :
///   - filtered, clean filtered signal 
///============================================================================
template <class T>
T ButterworthFilter<T>::filter (T input)
{
	
// automatic initialization 	
	if (d_initFlag ==1 )
	{
		for (int i=0; i<3; i++)
		{
			  d_previousInputX[i] = input;
			  d_previousOutputY[i] = input;
		}
	d_initFlag = 0;	
	}
	
	
	d_previousInputX[0] = input;
	// calculate the input related part and assign it to numerator
	d_numerator =   d_numeratorParameter[0] * d_previousInputX[0]
                 + d_numeratorParameter[1] * d_previousInputX[1]
                 + d_numeratorParameter[2] * d_previousInputX[2];

	d_denumerator =  d_denumParameter[1] * d_previousOutputY[1]
                  + d_denumParameter[2] * d_previousOutputY[2];

	d_previousOutputY[0] = (d_numerator - d_denumerator) / d_denumParameter[0];

	d_filteredOut = d_previousOutputY[0];
	
	// and shift the input and output values for the next cycle
	d_previousOutputY[2] =  d_previousOutputY[1] ;
	d_previousOutputY[1] =  d_previousOutputY[0] ;
	
	d_previousInputX[2] =  d_previousInputX[1] ;
	d_previousInputX[1] =  d_previousInputX[0] ;

	return (d_filteredOut);
}

#endif
