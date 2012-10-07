/*Arquivo contendo a classe SuperEllipsoid.
Possui a classe de uma superElipsóide
no programa.*/

#ifndef __SUPER_ELLIPSOID__HPP__
#define __SUPER_ELLIPSOID__HPP__
#include "Matriz_Functions.hpp"
#include "Matriz.hpp"
#include <cmath>


class SuperEllipsoid
{
public:
   SuperEllipsoid(Matriz<4,1> p , float rx, float ry, float rz, float s1, float s2)
   {
      _p = p;
      _rx = rx;
      _ry = ry;
      _rz = rz;
      _s1 = s1;
      _s2 = s2;
      PI = 3.1415926f;
   }
   
   ~SuperEllipsoid(){}

   /*Função paramétrica*/
   Matriz<4,1> retPoint(float s, float t)
   {
      //s vai de -pi/2 até pi/2
      //t vai de -pi até pi
      Matriz<4,1> ret;
      ret(3,0) = 1.f;
      ret(0,0) = _rx * pow(cos( (-1.f * PI)/2.f + (PI * s) ),_s1)  *  pow(cos( (-1.f * PI) + (2.f * PI * t) ),_s2);
      ret(1,0) = _ry * pow(cos( (-1.f * PI)/2.f + (PI * s) ),_s1)  *  pow(sin( (-1.f * PI) + (2.f * PI * t) ),_s2);
      ret(2,0) = _rz * pow(sin( (-1.f * PI)/2.f + (PI * s) ),_s1);
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
   float _s1;
   float _s2;
   mFunctions mat;
   
};

#endif