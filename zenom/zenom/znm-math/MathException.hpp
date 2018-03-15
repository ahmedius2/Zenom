//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: MathException.hpp
// Interface of the class MathException.
//========================================================================  
 

#ifndef INCLUDED_MathException_hpp
#define INCLUDED_MathException_hpp
 
template<class T> class MatrixBase;
template<class T> class VectorBase;

//======================================================================== 
/*! \enum _QMathException 
    \brief Supported exception types */
//======================================================================== 
typedef enum _QMathException
{
 QMathException_unknown             = 0x00,  //!< Undocumented error.
 QMathException_illegalIndex        = 0x01,  //!< Illegal index.
 QMathException_singular            = 0x02,  //!< Singular matrix.
 QMathException_divideByZero        = 0x03,  //!< Division by 0.
 QMathException_incompatibleSize    = 0x04,  /*!< Operation between two 
                                                  non-conformable matrices. */
 QMathException_typeMismatch        = 0x05,  /*!< Operation between incompatible 
                                                  data types (Ex: int and double). */
 QMathException_dimensionTooLarge   = 0x06   /*!< Matrix dimensions too large for 
                                                  the library to handle (Ex:
                                                  calling inverse() on matrices 
                                                  larger than 8 x 8.) */
}QMathException_t;


static struct 
{
 QMathException_t error;
 char *errorMsg;
}QMathExceptions[] = 
{
 { QMathException_unknown,           (char*)"Math Exception : Unknown Exception"},
 { QMathException_illegalIndex,      (char*)"Math Exception : Index out of range"},
 { QMathException_singular,          (char*)"Math Exception : Singular Matrix."},
 { QMathException_divideByZero,      (char*)"Math Exception : Division by zero."},
 { QMathException_incompatibleSize,  (char*)"Math Exception : Operation between objects of incompatible sizes."},
 { QMathException_typeMismatch,      (char*)"Math Exception : Operation between objects of incompatible types."},
 { QMathException_dimensionTooLarge, (char*)"Math Exception : Matrix too large."}
};

//======================================================================== 
// class MathException
// ----------------------------------------------------------------------
// \brief
// Run-time exception handling for the math library. 
//
// The error type is internally set by the library.
//
// <b>Example Program:</b>
// \include MathException.t.cpp
//========================================================================  
class MathException
{
 public:
  inline MathException() {d_errorType = QMathException_unknown;};
  ~MathException(){}
  inline const char *getErrorMessage() const; 
  inline QMathException_t getErrorType() const;
  inline bool isErrorType(QMathException_t error);
  inline void setErrorType(QMathException_t error);
  // ========== END OF INTERFACE ==========
 private:
  QMathException_t d_errorType;
};

//==========================================================
// End of declarations.
//==========================================================


//==========================================================
// MathException::isErrorType
//==========================================================
bool MathException::isErrorType(QMathException_t error)
{
 return (d_errorType == error);
}

//==========================================================
// MathException::getErrorType
//==========================================================
QMathException_t MathException::getErrorType() const
{
 return d_errorType;
}

//==========================================================
// MathException::getErrorMessage
//==========================================================
const char *MathException::getErrorMessage() const
{
 return QMathExceptions[d_errorType].errorMsg;
}

//==========================================================
// MathException::setErrorType
//==========================================================
void MathException::setErrorType(QMathException_t error)
{
 d_errorType = error;
}

#endif

