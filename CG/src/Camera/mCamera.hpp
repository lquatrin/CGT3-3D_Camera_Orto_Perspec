/*Este .hpp contém todas as funções da camera.
É a classe principal deste programa*/

#ifndef _mCAMERA__CG__
#define _mCAMERA__CG__

#include "Matriz.hpp"
#include "Matriz_Functions.hpp"
#include <iostream>

#define DISTANCE_PERSPECTIVE 500.f

/*Classe camera*/
class mCamera
{
public:
   /*Construtor da camera*/
   mCamera(float px, float py, float pz,
      float centerx,float centery, float centerz,
      float upx, float upy, float upz) 
   {
      Matriz<4,1> _mp;
      _mp.setZero();
      _mp(0,0) = px;
      _mp(1,0) = py;
      _mp(2,0) = pz;
      _mp(3,0) = 1;
      _p = _mp;

      _V.setZero();
      _V(0,0) = upx;
      _V(1,0) = upy;
      _V(2,0) = upz;
      _V(3,0) = 1;
      _V = mat.normalizeVector3D(_V);

      _N.setZero();
      _N(0,0) = centerx - px;
      _N(1,0) = centery - py;
      _N(2,0) = centerz - pz;
      _N = mat.normalizeVector3D(_N);
      _U = mat.normalizeVector3D(mat.crossProduct3D(_V,_N));
      _V = mat.normalizeVector3D(mat.crossProduct3D(_U,_N));
      tipo_de_projecao = 1;
      graus = 0.02f;
   }

   ~mCamera() {}

   /*Guarda a matriz de translação e rotação na classe para usar nos objetos*/
   void MatrizTransf() 
   {
      Matriz<4,4> ret;
      ret.setZero();
      Matriz<4,4> trans;
      trans.setZero();
      trans = mat.Translate3D(-_p(0,0),-_p(1,0),-_p(2,0));
      Matriz<4,4> rot;
      rot.setZero();
      Matriz<4,1> n = mat.normalizeVector3D(_N);
      Matriz<4,1> u = mat.normalizeVector3D(_U);//mat.normalizeVector3D(mat.crossProduct3D(_V,_N));
      Matriz<4,1> v = mat.normalizeVector3D(_V);//mat.normalizeVector3D(mat.crossProduct3D(u,n));
      rot(0,0) = u(0,0);
      rot(0,1) = u(1,0);
      rot(0,2) = u(2,0);
      rot(1,0) = v(0,0);
      rot(1,1) = v(1,0);
      rot(1,2) = v(2,0);
      rot(2,0) = -n(0,0);
      rot(2,1) = -n(1,0);
      rot(2,2) = -n(2,0);

      rot(3,3) = 1;

      ret = rot*trans;
      _M = ret;
   }

   /*Imprimi os 3 vetores*/
   void print()
   {
      std::cout << "Forward:" <<  _N(0,0) << " " << _N(1,0) << " " << _N(2,0) << std::endl;
      std::cout << "Up:" <<_V(0,0) << " " << _V(1,0) << " " << _V(2,0) << std::endl;
      std::cout << "Right:" << _U(0,0) << " " << _U(1,0) << " " << _U(2,0) << std::endl;
   }

   Matriz<4,1> apllyOrto(Matriz<4,1> _LoL)
   {
      Matriz<4,4> t;
      t.setZero();
      t(0,0) = 1;
      t(1,1) = 1;
      t(3,3) = 1;
      return t*_LoL;
   }

   Matriz<4,1> applyPersp(Matriz<4,1> _LoL)
   {
      Matriz<4,1> t;
      float r = 1/DISTANCE_PERSPECTIVE;
      Matriz<4,4> Tp;
      Tp.setZero();
      Tp(0,0) = 1;
      Tp(1,1) = 1;
      if(tipo_de_projecao == 1){
         Tp(3,2) = -r;
      }else if(tipo_de_projecao == 2){
         Tp(3,2) = -r;
         Tp(3,1) = r;
      }else if(tipo_de_projecao == 3){
         Tp(3,1) = r;
         Tp(3,0) = r;
         Tp(3,2) = -r;
      }
      t = Tp*_LoL;
      if(t(0,0) != 0.f)
         t(0,0) = t(0,0)/t(3,0);
      if(t(1,0) != 0.f)
         t(1,0) = t(1,0)/t(3,0);
      t(2,0) = 0;
      t(3,0) = 1;
      return (t);
   }

   Matriz<4,1> projeta(Matriz<4,1> t)
   {
      Matriz<4,1> res;
      res.setZero();
      if(tipo_de_projecao == 0){ //ortrográfica
         res = apllyOrto(_M*t);
      }
      else { //perspectiva
         res = applyPersp(_M*t);
      }
      return res;
   }

   void move_forward(float forward)
   {
      _p = mat.Translate3D(_N(0,0)*getSpeed()*forward,_N(1,0)*getSpeed()*forward,_N(2,0)*getSpeed()*forward)*_p;
   }

   void move_up(float up)
   {
      _p = mat.Translate3D(_V(0,0)*getSpeed()*up,_V(1,0)*getSpeed()*up,_V(2,0)*getSpeed()*up)*_p;
   }

   void move_right(float right)
   {
      _p = mat.Translate3D(_U(0,0)*getSpeed()*right,_U(1,0)*getSpeed()*right,_U(2,0)*getSpeed()*right)*_p; 
   }

   float getSpeed()
   {
      return _speed;
   }

   void setSpeed(float sp)
   {
      _speed = sp;
   }

   void normalize_all()
   {
      _V = mat.normalizeVector3D(_V);
      _U = mat.normalizeVector3D(_U);
      _N = mat.normalizeVector3D(_N);
   }

   void rotate_pitch(float fator) //X
   {
      _V = mat.rotation3Dx(fator*graus)*_V;
      _U = mat.rotation3Dx(fator*graus)*_U;
      _N = mat.rotation3Dx(fator*graus)*_N;
      normalize_all();
   }

   void rotate_yaw(float fator) //Y
   {
      _V = mat.rotation3Dy(fator*graus)*_V;
      _U = mat.rotation3Dy(fator*graus)*_U;
      _N = mat.rotation3Dy(fator*graus)*_N;
      normalize_all();
   }

   void rotate_roll(float fator) //Z
   {
      _V = mat.rotation3Dz(fator*graus)*_V;
      _U = mat.rotation3Dz(fator*graus)*_U;
      _N = mat.rotation3Dz(fator*graus)*_N;
      normalize_all();
   }

   void setProjecao(int i)
   {
      tipo_de_projecao = i;
   }

   int getProjecao()
   {
      return tipo_de_projecao;   
   }

   Matriz<4,1> _p;

private:
   // Matriz<4,1> _p;
   Matriz<4,1> _V; //up
   Matriz<4,1> _N; //dir
   Matriz<4,1> _U; //right
   int tipo_de_projecao;
   mFunctions mat;
   float _speed;
   Matriz<4,4> _M;
   float graus;
};

#endif