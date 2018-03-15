//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: VectorBase.hpp
// Interface of the class VectorBase.
//========================================================================  
 
#ifndef INCLUDED_VectorBase_hpp
#define INCLUDED_VectorBase_hpp

#include <iostream>
#include "MathException.hpp"
#include "MatrixInitializer.hpp"

//====================================================================
// class VectorBase
// -------------------------------------------------------------------
// \brief
// The pure virtual base class for \c ColumnVector, \c RowVector and 
// \c Vector classes.
//========================================================================  
 
template<class T> class MatrixBase;

template<class T = double>
class VectorBase
{
 public:
  VectorBase(){}
   // The default constructor.
  
  virtual ~VectorBase(){}
   // The default destructor.

  virtual T *getElementsPointer() const = 0;
   //  return  A pointer to the first element in a vector.

  virtual T getElement(int i) const = 0;
   //  return  The element at the index i.

  virtual void setElement(int index, T value)= 0;
   // Sets an element to a value at the specified position.
   //  index  Position of the desired element.
   //  value  The desired element is set to this value.
	
  virtual int getNumElements() const  = 0;
   //  return  The number of elements in the vector.

  inline T norm() const;
   //  return 2-norm of the vector.
	
  virtual bool isRowVector() const = 0;
   //  return  'true' if the vector instantiated is a \c RowVector.

  bool isColumnVector() const {return !isRowVector(); }
   //  return  'true' if the vector instantiated is a \c ColumnVector.

  VectorBase<T> &operator=(const VectorBase<T> &vectorBase);
   // Assignment operator between two VectorBase types.
   
  virtual MatrixInitializer<T> operator=(const T &value) = 0;
   // Initialize a vector object.
	
  void output(std::ostream &outputStream = std::cout);
   //  return  The elements in the vector to the output stream 
   //          (by default the output is to the console)

 protected:
  VectorBase(VectorBase<T> &m) {};
   // Copy constructor

   // ========== END OF INTERFACE ==========	
	
 private:
};


//=================================================================
// End of declarations.
//=================================================================

//======================================================================== 
// VectorBase::norm
//========================================================================  
template<class T>
T VectorBase<T>::norm() const
{
 T norm2 = 0;
 int size = getNumElements();
 for (int i = 1; i <= size; ++i)
 {
  norm2 += (T)(pow(getElement(i), 2.0));
 }
 return (T)sqrt(norm2);
}


//=======================================================================
// VectorBase::operator=
//=======================================================================
template<class T>
VectorBase<T> &VectorBase<T>::operator=(const VectorBase<T> &v)
{
 if(this == &v)
  return *this;

 if( v.isRowVector() != isRowVector() ) 
 {
  static MathException exception;
  exception.setErrorType(QMathException_typeMismatch);
  throw exception;
 }

 int numElements = v.getNumElements();
 if (numElements != getNumElements())
 {
  static MathException exception;
  exception.setErrorType(QMathException_incompatibleSize);
  throw exception;
 }
 
 for (int i = 1; i <= numElements; ++i)
 { 
  setElement(i, v.getElement(i));
 }
 return *this;
}


//=======================================================================
// VectorBase::output
//=======================================================================
template<class T>
void VectorBase<T>::output(std::ostream &outputStream)
{
 int numElements = getNumElements();
 bool isRow = isRowVector();
	
 for (int i = 1; i <= numElements; ++i)
 {
  outputStream << getElement(i);
  if (isRow) outputStream << " ";
  else if(i < numElements) outputStream << "\n";
 }
}


#endif // INCLUDED_VectorBase_hpp

