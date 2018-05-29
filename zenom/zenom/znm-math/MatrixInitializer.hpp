//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: MatrixInitializer.hpp
// Interface of the class MatrixInitializer.
//========================================================================  
 

#ifndef INCLUDED_MatrixInitializer_hpp
#define INCLUDED_MatrixInitializer_hpp

#include "MathException.hpp"

//======================================================================== 
// class MatrixInitializer
// ----------------------------------------------------------------------
// \brief
// This class is used internally by the library to initialize the \c Matrix 
// and its derived class objects.
//
//========================================================================  

template<int numRows, int numColumns, class T> class Matrix;

template<class T = double>
class MatrixInitializer
{
 public:
  inline MatrixInitializer (T num, int offset, T *firstElementPointer);
   // The default constructor.

  ~MatrixInitializer (){}
   // The default destructor.

  inline MatrixInitializer<T>  operator,(const T &elementValue);
   // This function provides a method to
   // easily assign the elements of a Matrix 
   // object. A Matrix object is initialized in
   // the following manner:
   // \code Matrix<2,2> myMatrix;
   // myMatrix = 2.0, 5.0, 78.90, 20; \endcode
   
 // ========== END OF INTERFACE ==========
 
 private:
  T d_numElements;
  int d_positionCounter;
  T *d_firstElementPointer; 
};


//========================================================================
// MatrixInitializer::MatrixInitializer 
//========================================================================
template<class T>
MatrixInitializer<T>::MatrixInitializer (T totalElements, int offset, T *firstElementPointer)
{	
 d_numElements = totalElements;
 d_firstElementPointer = firstElementPointer;
 d_positionCounter = offset;
}


//========================================================================
// MatrixInitializer::operator, 
//========================================================================
template<class T>
MatrixInitializer<T>  MatrixInitializer<T>::operator,(const T &elementValue)
{
 if (d_positionCounter > (d_numElements-1))
 { 
  static MathException exception;
  exception.setErrorType(QMathException_illegalIndex);
  throw exception;
 }

 *(d_firstElementPointer + d_positionCounter) = elementValue;
 ++d_positionCounter;
 MatrixInitializer<T>  matrixInitialize(d_numElements,d_positionCounter, d_firstElementPointer);
 return matrixInitialize;
}

#endif
