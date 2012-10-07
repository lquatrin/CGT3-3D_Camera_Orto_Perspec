/*Este .hpp contém as funções da classe Bezier
usada para construir e armazenar as informações sobre
os pontos do plano e os pontos de controle relacionados
ao mesmo*/

#ifndef ___BEZIER__HPP___
#define ___BEZIER__HPP___

#include "Matriz_Functions.hpp"
#include <cmath>

/*classe Bezier
O plano foi fixado com pontos de controle 10x10 de tamanho*/
class Bezier
{
public:
   /*Coloca os pontos resultantes dos pontos de controle numa matriz*/
   void gPoints()
   {
      for(int n = 0; n <= 2 ; n++){
         for(int m = 0; m <= 2 ; m++){
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

   Bezier() 
   {
      time = 0;
      grau = 3;
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
            m(2,0) = (float)(rand()%30);
            vx[i][j] = m;

         }
      }   
      gPoints();
   }

   ~Bezier() {}

   float fatorial(int n)
   {
      float res = 1.f;
      while( n > 0 )
      {
         res *= (float)n;
         n--;
      }
      return res;
   }

   /*Blending functions*/
   float BF(int n, int i, float t)
   {
      return ( (fatorial(n)/(fatorial(i)*fatorial(n-i)))*(float)pow(t,i)*(float)pow(1-t,n-i) );
   }


   Matriz<4,1> getControlPoint(int i, int j)
   {
      return vx[i][j];
   }

   /*Retorna o ponto da matriz do plano*/
   Matriz<4,1> GetPoint(float s, float t,int n1, int n2){

      Matriz<4,1> ret;
      ret.setZero();
      for(int i = 0 ; i <= grau ; i++)
      {
         for(int j = 0 ; j <= grau ; j++)
         {

            ret += getControlPoint(n1*3 + i,n2*3 + j)*BF(grau,i,s)*BF(grau,j,t);
         }
      }
      ret(3,0) = 1;
      return ret;
   }
   Matriz<4,1> vx[10][10];
   Matriz<4,1> vp[(11*3)-2][(11*3)-2];
   int tami;
   int tamj;
   int desloc;
   static const int sizeVecBsp = (11*3)-2;
private:
   int grau;
   int time;

};
#endif