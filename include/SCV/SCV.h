/*!
\file       SCV.h
\brief      Include all SCV dependencies and components.
\author     SCV Team.
*/

#ifndef __SCV_H__
#define __SCV_H__

/*!
\mainpage SCV Documentation

O SCV é uma API (Application Programming Interface) de facilitação na construção de interfaces de usuário (GUI - Graphic User Interface), orientada ao uso de um programador com experiência na linguagem de programação C++.
<br/><br/>
Aqui você irá encontrar a documentação de todos componentes e funcionalidades oferecidas. 
Na pasta 'scv_examples' são dados exemplos de uso da API com projetos do Microsoft Visual Studio 2010.
<br/>
\section ide IDEs Suportadas
Microsoft Visual Studio 2010 
\subsection ide_so Sistemas Operacionais
Windows
<br/><br/>
A documentação atualizada poderá ser acessada através do endereço: http://www-usr.inf.ufsm.br/~pozzer/scv
<br/>
\section home Get Started!
Para acessar a documentação do SCV presente na pasta "documentation" execute o arquivo "Documentation.bat".
<br/>
<br/>
Para visualizar vários exemplos utilizando o SCV e demonstrando suas funcionalidades execute o arquivo "SCV_Examples.bat".
<br/>
<br/>
Para acessar o InterfaceDesginer execute o "InterfaceDesigner.bat", nele o usuário pode graficamente criar sua Interface, através de DragAndDrop, e gerar o código SCV correspondente para o arquivo "interface.cpp".
*/


//|||||||||||||||||||||||||||||||||||||||||||||||

#ifdef _WIN32
   #ifdef _MSC_VER
      #pragma warning(disable:4018)
   #endif // _WIN32
#endif // _MSC_VER

//|||||||||||||||||||||||||||||||||||||||||||||||

//#include <pthread.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
/*
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <list>
#include <map>

#include <cstring>
#include <cstdio>
#include <cassert>
*/
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Kernel.h"

#include "Button.h"
#include "Canvas.h"
#include "CheckBox.h"
#include "ColorPicker.h"
#include "ComboBox.h"
#include "ContextMenu.h"
#include "FileOpen.h"
#include "GlslShader.h"
#include "Image.h"
#include "InternalFrame.h"
#include "Label.h"
#include "Mathematic.h"
#include "MenuBar.h"
#include "ProgressBar.h"
#include "RadioButton.h"
#include "ScrollPane.h"
#include "Separator.h"
#include "Singleton.h"
#include "Slider.h"
#include "StateButton.h"
#include "TabbedPane.h"
#include "Table.h"
#include "util.h"
#include "TreeView.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif // __SCV_H__
