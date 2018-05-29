//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: Differentiator4O.hpp
// Interface of the class Differentiator.
//========================================================================  

#ifndef INCLUDED_Differentiator4O_hpp
#define INCLUDED_Differentiator4O_hpp

#include "Differentiator.hpp"

//====================================================================
// class Differentiator4O
// -------------------------------------------------------------------
// \brief
// Fourth order differentation followed by low-pass filtering. 
//
// <b>Example Program:</b>
// \include Differentiator4O.t.cpp
//========================================================================  
 
template<class T = double>
class Differentiator4O : public Differentiator<T>
{
 public:
  inline Differentiator4O(double period = 0.001);
   // The Constructor initializes.
   // The cut-off frequency is set to half the
   // sampling frequency and damping ratio of the
   // low-pass filter in the differentiator is set to 1. 
   //  period  The sampling period of the 
   //          differentiator in seconds.
	
  virtual ~Differentiator4O (){}
   // The default destructor.

  void reset();
   // Resets the differentiator output to zero.

  virtual T differentiate(const T &input);
   // This function implements the numerical 
   // method for differentiation.
   // The output in the first cycle is smoothened to zero.
   //  input  The present value of the 
   //         variable being differentiated.
		
 // ========== END OF INTERFACE ==========
 
 private:
  T d_oldInput[3];
};



//==============================================================
// End of declarations.
//==============================================================


//======================================================================== 
// Differentiator4O::Differentiator
//========================================================================  
template<class T>
Differentiator4O<T>::Differentiator4O(double samplingPeriod)
 : Differentiator<T>(samplingPeriod)
{
 d_oldInput[0] = 0;
 d_oldInput[1] = 0;
 d_oldInput[2] = 0;
}


//======================================================================== 
// Differentiator4O::reset
//========================================================================  
template<class T>
void Differentiator4O<T>::reset()
{
 Differentiator<T>::reset();
 d_oldInput[0] = 0;
 d_oldInput[1] = 0;
 d_oldInput[2] = 0;
}


//======================================================================== 
// Differentiator4O::differentiate
//========================================================================  
template<class T>
T Differentiator4O<T>::differentiate(const T &currentInput)
{
 static int order = 1;
 if (this->d_initialize)
 {
  this->d_previousInput = currentInput;
  d_oldInput[0] = 0;
  d_oldInput[1] = 0;
  d_oldInput[2] = 0;
  this->d_lowPassFilter.setAutoInit();
  this->d_initialize = false;
  order = 1;
 }
	
 T filteredOutput;
 switch(order)
 {
  case(1):
   this->d_currentDifferential 
    = (1.0/this->d_samplingPeriod) 
    * (currentInput - this->d_previousInput);
   ++order;
  break;
  case(2):
   this->d_currentDifferential 
    = (1.0/(2.0 * this->d_samplingPeriod)) 
    * (3.0 * currentInput - 4.0 * this->d_previousInput 
    + d_oldInput[0]);
   ++order;
  break;
  case(3):
   this->d_currentDifferential 
    = (1.0/(6.0 * this->d_samplingPeriod)) 
    * (11.0 * currentInput - 18.0 * this->d_previousInput 
    + 9.0 * d_oldInput[0] - 2.0 * d_oldInput[1]);
   ++order;
  break;
  default:
   this->d_currentDifferential 
    = (1.0/(12.0 * this->d_samplingPeriod)) 
    * (25.0 * currentInput - 48.0 * this->d_previousInput 
    + 36.0 * d_oldInput[0] - 16.0 * d_oldInput[1] + 3.0 * d_oldInput[2]);
  break;
 }
 d_oldInput[2] = d_oldInput[1];
 d_oldInput[1] = d_oldInput[0];
 d_oldInput[0] = this->d_previousInput;
 this->d_previousInput = currentInput;

 if(this->d_useFilter)
  filteredOutput = this->d_lowPassFilter.filter(
                   this->d_currentDifferential);
 else
  filteredOutput = this->d_currentDifferential;
 
 return filteredOutput;
}


#endif
