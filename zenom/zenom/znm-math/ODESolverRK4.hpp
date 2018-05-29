//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Oct 28 11:08:28 GMT 2004
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: ODESolverRK4.hpp
// Interface of the class OdeSolverRK4.
//========================================================================  
 
#ifndef INCLUDED_ODESolverRK4_hpp
#define INCLUDED_ODESolverRK4_hpp

#include "Vector.hpp"
 
//======================================================================== 
// class ODESolverRK4
// ----------------------------------------------------------------------
// \brief
// Solver for ordinary differential equations using 4th order Runge Kutta 
// method.
//
// Use this class for solving differential equations of the type
// x'(t) = f(x,t). The user must provide a function that returns x'(t) 
// for any given x(t) and t. 
//
// <b>Example Program:</b>
//
// \include ODESolverRK4.t.cpp
//========================================================================  

template<class T = double>
class ODESolverRK4
{
 public:
  ODESolverRK4 ();
   // The default constructor.
   // The sampling period is set to default of 0.001 seconds
   // The initial value is set to 0.
	
  ODESolverRK4(double period, const T &init);
   // This constructor initializes the sampling period 
   // and initial Value.
   //  period 	The sampling period in seconds.
   //  init	The initial value.

  virtual ~ODESolverRK4() {};
   // The default destructor
	
  inline void setSamplingPeriod(double period) { d_samplingPeriod = period; }
   // Sets the sampling period of the solver 
 
  void setODE(T (*diffFunc) (T &, double t));
   // Set the differential equation of the form x'=f(x,t) to evaluate.  
   //  diffFunc		The differential equation

  virtual void reset(const T &init);
   // This function resets the output of the solver
   // to \a init and further integration
   // restarts from this initial value.

  inline virtual T stepSolve();
   // Find solution for the next time step.
   //  return  The integrated value for the next step

 //========== END OF INTERFACE ==========
 protected:
  double d_samplingPeriod;

 private:
  T d_previousOutput;
  T (*d_diffFunc)(T &, double);
  double d_elapsedTime;
};

//======================================================
// End of declarations.
//======================================================



//======================================================================== 
// ODESolverRK4::ODESolverRK4
//========================================================================  
template<class T>
ODESolverRK4<T>::ODESolverRK4()
{
 T resetToValue;
 resetToValue = 0.0;
 d_samplingPeriod = 0.001;
 reset(resetToValue);
}

template<class T>
ODESolverRK4<T>::ODESolverRK4(double samplingPeriod, const T &initialValue)
{
 d_samplingPeriod = samplingPeriod;
 reset(initialValue);
}


//======================================================================== 
// ODESolverRK4::reset
//========================================================================  
template<class T>
void ODESolverRK4<T>::reset(const T &resetToValue)
{
 d_previousOutput = resetToValue;
 d_elapsedTime = 0.0;
}


//======================================================================== 
// ODESolverRK4::setODE
//========================================================================  
template<class T>
void ODESolverRK4<T>::setODE(T (*diffFunc) (T &, double))
{
 d_diffFunc = diffFunc;
}


//======================================================================== 
// ODESolverRK4::integrate
//========================================================================  
template<class T>
T ODESolverRK4<T>::stepSolve()
{
 static T k1, k2, k3, k4, tmp;

 k1 = d_samplingPeriod * ((*d_diffFunc)(d_previousOutput, d_elapsedTime));
 	
 tmp = d_previousOutput + (0.5 * k1); 
 k2 = d_samplingPeriod * ((*d_diffFunc)(tmp, d_elapsedTime + (0.5 * d_samplingPeriod)));
	
 tmp = d_previousOutput + (0.5 * k2); 
 k3 = d_samplingPeriod * ((*d_diffFunc)(tmp, d_elapsedTime + (0.5 * d_samplingPeriod)));
	
 tmp = d_previousOutput + k3; 
 k4 = d_samplingPeriod * ((*d_diffFunc)(tmp, d_elapsedTime + d_samplingPeriod));

 d_elapsedTime += d_samplingPeriod;

 d_previousOutput = d_previousOutput + ((1.0/6.0) * (k1 + (2.0 * (k2+k3)) + k4));

 return (d_previousOutput);
}

#endif
