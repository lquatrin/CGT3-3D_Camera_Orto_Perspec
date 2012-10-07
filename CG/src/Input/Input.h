/*Arquivo com a declara��o da classe input.*/

#ifndef ____INPUT__HPP____
#define ____INPUT__HPP____

#include <map>

//classe que cont�m o "mapa" das teclas do jogo
class Input
{
public:
   /*Declara��o das teclas dispon�veis
   construtor*/
   Input();

   ~Input();

   /*Resetar todas as teclas -> setar false*/
   void reset();

   std::map<char,bool> keyboard;
private:
   std::map<char,bool>::iterator it;
   std::pair<std::map<char,bool>::iterator,bool> ret;

};

#endif