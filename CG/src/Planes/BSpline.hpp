/*Este .hpp contém as funções da classe bSplinePlane
usada para construir e armazenar as informações sobre
os pontos do plano e os pontos de controle relacionados
ao mesmo*/

#ifndef __BSPLINE___PLANE_HPP__
#define __BSPLINE___PLANE_HPP__


#include "Matriz_Functions.hpp"
#include <cmath>
/*classe bSplinePlanes
O plano foi fixado com pontos de controle 10x10 de tamanho*/
class BSplinePlane
{
public:
   /*Coloca os pontos resultantes dos pontos de controle numa matriz*/
   void gPoints()
   {
      for(int n = 0; n <= 6 ; n++){
         for(int m = 0; m <= 6 ; m++){
            for(float i = 0.f; i < 1.1f; i +=0.1f)
            {
               for(float j = 0.f; j < 1.1f; j += 0.1f)
               {
                  vp[10*n + (int)(i*10.f)][10*m + (int)(j*10.f)] = GetPoint(i,j,n,m);

               }
            }
         }
      }
   }

   /*Empurra todos os Pontos de controle para +1 na sua posição em uma das direções*/
   void wave()
   {
      if(time == 6){
         Matriz<4,1> v[10][10];
         for(int i = 0; i < tami ; i++)
         {
            for(int j = 0; j < tamj; j++)
            {

               v[i][j] = vx[i][j];
            }
         }   


         for(int i = 0; i < tami ; i++)
         {
            for(int j = 0; j < tamj; j++)
            {

               vx[i][j](2,0) = v[(i+1)%tami][j](2,0);
            }
         }   
         gPoints();
         time = 0;
      }else
      {time++;}

   }

   /*Adiciona ou subtrai um valor pequeno do Z dos pontos de controle*/
   void rando()
   {

      for(int i = 0; i < tami ; i++)
      {
         for(int j = 0; j < tamj; j++)
         {

            vx[i][j](2,0) += ((float)(rand()%1000) - 500.f) / 900.f;
         }
      }   
      gPoints();
   }


   BSplinePlane() 
   {

      time = 0;
      tami = 10;
      tamj = 10;
      Matriz<4,1> m;
      m.setZero();
      m(3,0) = 1;
      desloc = 0;
      for(int i = 0; i < tami ; i++)
      {
         for(int j = 0; j < tamj; j++)
         {
            m(0,0) = (float)((i+1)*10);
            m(1,0) = (float)((j+1)*10);
            m(2,0) = (float)(rand()%20);
            vx[i][j] = m;
         }
      }   
      gPoints();
   }



   ~BSplinePlane() {}

   /*Blending functions*/
   float BF(int i, float t)
   {
      if(i == 3)
      {
         return ((1.f/6.f)*(t*t*t));
      }else if(i == 2)
      {
         return((1.f/6.f)*((-3.f*(t*t*t)) + (3.f*(t*t)) + (3.f*(t)) + 1));
      }else if(i == 1)
      {
         return((1.f/6.f)*((3.f*(t*t*t)) + (-6.f*(t*t)) + 4));
      }else if(i == 0)
      {
         return ((1.f/6.f)*((1-t)*(1-t)*(1-t)));
      }
      return 0.f;
   }


   Matriz<4,1> getControlPoint(int i, int j)
   {
      return vx[i][j];
   }

   /*Retorna o ponto da matriz do plano*/
   Matriz<4,1> GetPoint(float s, float t,int n1, int n2){

      Matriz<4,1> ret;
      ret.setZero();
      for(int i = 0 ; i <= 3 ; i++)
      {
         for(int j = 0 ; j <= 3 ; j++)
         {
            ret += getControlPoint(n1 + i,n2 + j)*BF(i,s)*BF(j,t);
         }
      }
      ret(3,0) = 1;
      return ret;
   }
   Matriz<4,1> vx[10][10];
   Matriz<4,1> vp[(11*7)-6][(11*7)-6];
   int tami;
   int tamj;
   int desloc;
   static const int sizeVecBsp = (11*7)-6;
private:
   int time;
};

#endif