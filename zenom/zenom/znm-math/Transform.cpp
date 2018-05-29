//======================================================================== 
// Package		: The Math Library - Ex
// Authors		: Vilas Kumar Chitrakaran
// Start Date		: Wed Dec 20 11:08:28 GMT 2000
// Compiler		: GNU C++ 2.95.3 and above
// ----------------------------------------------------------------------  
// File: Transform.cpp
// Implementation of the class Transform.
// See Transform.hpp for more details.
//========================================================================  
 
// ----- Project Includes -----
#include "Transform.hpp"

//============================================================= 
// xRotation
//=============================================================  
Transform xRotation(double theta)
{
 Transform xRotation;
 xRotation(1,1) = 1;
 xRotation(2,2) = cos(theta);
 xRotation(2,3) = -sin(theta);
 xRotation(3,2) = -xRotation(2,3);
 xRotation(3,3) = xRotation(2,2);
 return xRotation;
}


//============================================================= 
// yRotation
//=============================================================  
Transform yRotation(double theta)
{
 Transform yRotation;
 yRotation(1,1) = cos(theta);
 yRotation(1,3) = sin(theta);
 yRotation(2,2) = 1;
 yRotation(3,1) = -yRotation(1,3);
 yRotation(3,3) = yRotation(1,1);
 return yRotation;
}


//============================================================= 
// zRotation
//=============================================================  
Transform zRotation(double theta)
{
 Transform zRotation;
 zRotation(1,1) = cos(theta);
 zRotation(1,2) = -sin(theta);
 zRotation(2,1) = -zRotation(1,2);
 zRotation(2,2) = zRotation(1,1);
 zRotation(3,3) = 1;
 return zRotation;
}


//============================================================= 
// vectorRotation
//=============================================================  
Transform vectorRotation(const ColumnVector<3, double> &u, double theta)
{
 Transform t;
 double c = cos(theta);
 double s = sin(theta);
 Matrix<3, 3, double> r;
 r(1,1) = 0;
 r(1,2) = -u(3)*s;
 r(1,3) = u(2)*s;
 r(2,1) = -r(1,2);
 r(2,2) = r(1,1);
 r(2,3) = -u(1)*s;
 r(3,1) = -r(1,3);
 r(3,2) = -r(2,3);
 r(3,3) = r(1,1);
 r += u*transpose(u)*(1-c);
 r(1,1) += c;
 r(2,2) += c; 
 r(3,3) += c;
 t.setSubMatrix(1, 1, r);
 return t;
}


