/*Arquivo contendo a classe cube.
Possui os vértices do cubo desenhado
no programa.*/
#ifndef ___CUBE__CG____
#define ___CUBE__CG____

#include "Matriz.hpp"
#include <vector>

/*Classe relacionada ao cubo*/
class Cube
{
public:
   Cube() 
   {
      _p(0,0) = 20;
      _p(1,0) = 20;
      _p(2,0) = 20;
      _p(3,0) = 1;

      Matriz<4,1> t;
      t.setZero();
      t(3,0) = 1;
      t(2,0) = 10;
      t(0,0) = 10;
      t(1,0) = 10;
      _vertex.push_back(t);
      t(0,0) = 30;
      t(1,0) = 10;
      _vertex.push_back(t);
      t(0,0) = 30;
      t(1,0) = 30;
      _vertex.push_back(t);
      t(0,0) = 10;
      t(1,0) = 30;
      _vertex.push_back(t);
      

      t(2,0) = 30;
      t(0,0) = 10;
      t(1,0) = 10;
      _vertex.push_back(t);
      t(0,0) = 30;
      t(1,0) = 10;
      _vertex.push_back(t);
      t(0,0) = 30;
      t(1,0) = 30;
      _vertex.push_back(t);
      t(0,0) = 10;
      t(1,0) = 30;
      _vertex.push_back(t);  
   }

   ~Cube() {}

   std::vector<Matriz<4,1>> _vertex;
   Matriz<4,1> _p;

private:

};

#endif