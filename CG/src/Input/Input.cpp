/*Arquivo com as funções da classe input.*/
#include "Input.h"
#include <map>

Input::Input() 
{
   keyboard.insert ( std::pair<char,bool>('w',false) );
   keyboard.insert ( std::pair<char,bool>('s',false) );
   keyboard.insert ( std::pair<char,bool>('d',false) );
   keyboard.insert ( std::pair<char,bool>('a',false) );
   keyboard.insert ( std::pair<char,bool>('q',false) );
   keyboard.insert ( std::pair<char,bool>('e',false) );
   //
   keyboard.insert ( std::pair<char,bool>('o',false) );
   keyboard.insert ( std::pair<char,bool>('l',false) );
   keyboard.insert ( std::pair<char,bool>('i',false) );
   keyboard.insert ( std::pair<char,bool>('k',false) );
   keyboard.insert ( std::pair<char,bool>('u',false) );
   keyboard.insert ( std::pair<char,bool>('j',false) );
   //
}
Input::~Input() {}

void Input::reset()
{
   keyboard['w'] = false;
   keyboard['s'] = false;
   keyboard['d'] = false;
   keyboard['a'] = false;
   keyboard['q'] = false;
   keyboard['e'] = false;
   //
   keyboard['o'] = false;
   keyboard['l'] = false;
   keyboard['i'] = false;
   keyboard['k'] = false;
   keyboard['u'] = false;
   keyboard['j'] = false;
}
