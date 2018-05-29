//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: Vector.hpp
// Interface of the class Vector.
//========================================================================  
 

#ifndef INCLUDED_Vector_hpp
#define INCLUDED_Vector_hpp
 
#include "ColumnVector.hpp" 
 
//======================================================================== 
// class Vector
// ----------------------------------------------------------------------
// \brief
// The class \c Vector provides is equivalent to a \c ColumnVector object.
//
// <b>Example Program:</b> See the Example program for class ColumnVector.
//========================================================================  
 
template<int size, class T> class ColumnVector;

template<int size, class T = double>
class Vector : public ColumnVector<size, T>
{
 public:
  inline Vector ()  : ColumnVector<size,T>() {}
   // The default constructor. No element initializations.

  inline Vector(const Vector<size, T> &vector);
   // Copy Constructor. 

  ~Vector () {}
   // The default Destructor.
		
  inline Vector(const Matrix<size,1,T> &matrix);
   // The conversion constructor for conversion
   // of a \c Matrix type of single column into
   // type \c Vector.
			 	
  inline Vector<size, T> &operator=(const VectorBase<T> &vectorBase);
   // Assign a \c VectorBase type to a \c Vector type. Both objects 
   // must have the same dimensions.
		
  MatrixInitializer<T> operator=(const T &value);
   // Initialize a vector object.
   //  value  The value to which all elements in the vector are initialized.
   // The initialization of the vector object can also
   // be done as a comma seperated list. For example:
   // \code 
   // ColumnVector<3> myVector;
   // myVector = 67.88, 45.89, 90; 
   // \endcode

  // ========== END OF INTERFACE ==========
 private:
};



//======================================================================== 
// Vector::Vector
//========================================================================  
template<int size, class T>
Vector<size, T>::Vector(const Vector<size, T> &v)
 : ColumnVector<size,T>(v)
{
}

template<int size, class T>
Vector<size, T>::Vector(const Matrix<size,1,T> &m)
 : ColumnVector<size,T>(m)
{
}


//======================================================================== 
// Vector::operator=
//========================================================================  
template<int size, class T>
Vector<size, T> &Vector<size, T>::operator=(const VectorBase<T> &v)
{
 if(this != &v)
  this->VectorBase<T>::operator=(v);
 return *this;
}

template<int size, class T>
MatrixInitializer<T>Vector<size, T>::operator=(const T &value)
{
 return this->ColumnVector<size, T>::operator=(value);
}


#endif

