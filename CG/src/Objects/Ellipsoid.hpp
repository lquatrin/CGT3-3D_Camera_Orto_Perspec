/*Arquivo contendo a classe Ellipsoid.
Possui a classe de uma Elipsóide
no programa.*/

#ifndef __ELLIPSOID__HPP__
#define __ELLIPSOID__HPP__

#include "Matriz_Functions.hpp"
#include "Matriz.hpp"
#include <cmath>

class Ellipsoid
{
public:
   Ellipsoid(Matriz<4,1> p , float rx, float ry, float rz)
   {
      _p = p;
      _rx = rx;
      _ry = ry;
      _rz = rz;
      PI = 3.1415926f;
   }
   
   ~Ellipsoid(){}

   /*Função paramétrica*/
   Matriz<4,1> retPoint(float s, float t)
   {
      //s vai de -pi/2 até pi/2
      //t vai de -pi até pi
      Matriz<4,1> ret;
      ret(3,0) = 1.f;
      ret(0,0) = _rx * cos( (-1.f * PI)/2.f + (PI * s) )  *  cos( (-1.f * PI) + (2.f * PI * t) );
      ret(1,0) = _ry * cos( (-1.f * PI)/2.f + (PI * s) )  *  sin( (-1.f * PI) + (2.f * PI * t) );
      ret(2,0) = _rz * sin( (-1.f * PI)/2.f + (PI * s) );
      ret = mat.Translate3D( _p(0,0), _p(1,0), _p(2,0) ) * ret;
      return ret;
   }
protected:
   float PI;
private:
   Matriz<4,1> _p;
   float _rx;
   float _ry;
   float _rz;
   mFunctions mat;
   
};

#endif