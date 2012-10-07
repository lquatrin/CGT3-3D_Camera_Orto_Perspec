/*Arquivo contendo o Combo box das projeções
e a classe canvas que desenha tudo.*/

#ifndef ___CANVAS___DRAW_CG____H___
#define ___CANVAS___DRAW_CG____H___

#include <SCV/Canvas.h>
#include <SCV/Label.h>
#include <SCV/Color4f.h>
#include "Cube.hpp"
#include "Matriz_Functions.hpp"
#include "mCamera.hpp"
#include "Input.h"
#include <SCV/ComboBox.h>
#include "bSpline.hpp"
#include "Bezier.hpp"
#include "Sphere.hpp"
#include "Ellipsoid.hpp"
#include "SuperEllipsoid.hpp"

/*Combo box que seleciona o tipo de projecao que a camera vai realizar*/
class ComboBox0 : public scv::ComboBox {
   public:

      ComboBox0() : scv::ComboBox(scv::Point(50, 30), scv::Point(220, 50)) {
         addItem("Ortografica");
         addItem("Perspective(1 PF)");
         addItem("Perspectiva(2 PF)");
         addItem("Perspectiva(3 PF)");
      }
      ~ComboBox0() {}

      void onSelectionChanged (std::string address, int id)
      {
         cam->setProjecao(id);
      }

      mCamera *cam;
   protected:
   private:

};


//Classe principal do Canvas, onde é rodado
//o jogo inteiro
//contém todas as variáveis que são usadas no jogo
class CanvasDraw : public scv::Canvas {
public:
      
   CanvasDraw(ComboBox0 *cb, scv::Label *x,scv::Label *y,scv::Label *z ); 
   ~CanvasDraw() {
   }

   void onMouseClick(const scv::MouseEvent& evt);

   void setBackground(const scv::Color4f& color);

   void onMouseHold (const scv::MouseEvent& evt);

   void onMouseOver(const scv::MouseEvent& evt);

   void onMouseUp(const scv::MouseEvent& evt);

   void onKeyPressed(const scv::KeyEvent& evt);
   
   void onKeyUp(const scv::KeyEvent& evt);

   void onMouseWheel(const scv::MouseEvent& evt);

   void update(void);

   void render(void);

   void initGame();

   int _objects;

protected:

private:
   scv::Color4f bg_color;   
   Cube *_obj;
   mCamera *_mcam;
   mFunctions mat;
   Input *_input;
   scv::Label *_xC;
   scv::Label *_yC;
   scv::Label *_zC;
   BSplinePlane *bsp;
   Bezier *bzr;
   Sphere *sph;
   Ellipsoid *elp;
   SuperEllipsoid *selp;
   int upmouse;
   int rightmouse;
   
};

#endif