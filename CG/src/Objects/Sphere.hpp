/*Este .hpp cont�m a Classe Sphere
usado no trabalho pra desenhar uma esfera
A esfera � desenhada usando fun��es param�tricas.*/

#ifndef __SPHERE__HPP__
#define __SPHERE__HPP__

#include "Matriz_Functions.hpp"
#include "Matriz.hpp"
#include <cmath>

/*Classe da Esfera*/
class Sphere
{
public:
   Sphere(Matriz<4,1> p , float r)
   {
      _p = p;
      _r = r;
      PI = 3.1415926f;
   }
   
   ~Sphere(){}

   /*Fun��o param�trica*/
   Matriz<4,1> retPoint(float s, float t)
   {
      //s vai de -pi/2 at� pi/2
      //t vai de -pi at� pi
      Matriz<4,1> ret;
      ret(3,0) = 1.f;
      ret(0,0) = _r * cos( (-1.f * PI)/2.f + (PI * s) )  *  cos( (-1.f * PI) + (2.f * PI * t) );
      ret(1,0) = _r * cos( (-1.f * PI)/2.f + (PI * s) )  *  sin( (-1.f * PI) + (2.f * PI * t) );
      ret(2,0) = _r * sin( (-1.f * PI)/2.f + (PI * s) );
      ret = mat.Translate3D( _p(0,0), _p(1,0), _p(2,0) ) * ret;
      return ret;
   }
   
protected:
   float PI;
private:
   Matriz<4,1> _p;
   float _r;
   mFunctions mat;
   
};

#endif