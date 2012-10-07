#include "CanvasDraw.h"
#include <cstdlib>
#include <cmath>
#include <sstream>
#include "Matriz.hpp"
#include "Matriz_Functions.hpp"
#include <cmath>
#include <SCV/Label.h>
#include <sstream>
#include "Cube.hpp"
#include "Input.h"
#include <sstream>
#include "bSpline.hpp"

int const WL = 800;
int const WA = 800;
int const posIni = 300;

static const float M_PI = 3.1415926535897932384626433832795f;

int   polygonMode = 1;
float rx = 0, rz = 0;

float abertura = 44.0;
float znear  = 1;
float zfar   = 20;
float aspect = 1;


CanvasDraw::CanvasDraw(ComboBox0 *cb, scv::Label *x,scv::Label *y,scv::Label *z ) 
   : scv::Canvas(scv::Point(posIni, 0),scv::Point(posIni+WL, WA)), bg_color(0.f,0.f,0.f) 
{
   _obj = new Cube();

   _mcam = new mCamera(0.f, 0.f,0.f, //ponto da camera
      150.f, 150.f, 0.f,   //ponto do centro
      0.f  , 0.f , 1.f);  //vetor up

   _xC = x;
   _yC = y;
   _zC = z;
   _input = new Input();
   cb->cam = _mcam;
   cb->setIndex(_mcam->getProjecao());
   _mcam->setSpeed(0.7f);

   bsp = new BSplinePlane();
   bzr = new Bezier();
   Matriz<4,1> p;
   p(0,0) = 50;
   p(1,0) = 50;
   p(2,0) = 30;
   p(3,0) = 1;
   sph = new Sphere(p,10);


   elp = new Ellipsoid(p,10,40,30);
   selp =  new SuperEllipsoid(p,20,10,20,5,3);
}


void CanvasDraw::setBackground(const scv::Color4f& color) 
{
   bg_color = color;
}

void CanvasDraw::onMouseClick(const scv::MouseEvent& evt)
{
   upmouse = evt.getPosition().y;
   rightmouse = evt.getPosition().x;
}

void CanvasDraw::onMouseHold (const scv::MouseEvent& evt)
{ 
   if( evt.getButton() == 0 )
   {
      _mcam->move_right((float)(rightmouse-evt.getPosition().x)/5.f);
      _mcam->move_up((float)(upmouse-evt.getPosition().y)/5.f);
   }else if( evt.getButton() == 2 )
   {
      _mcam->rotate_roll((float)(rightmouse-evt.getPosition().x)/20.f);
      _mcam->rotate_yaw((float)(upmouse-evt.getPosition().y)/20.f);
   }else if( evt.getButton() == 1 )
   {
      //_mcam->rotate_pitch((float)(rightmouse-evt.getPosition().x)/20.f);
      _mcam->rotate_pitch((float)(upmouse-evt.getPosition().y)/20.f);
   }
   upmouse = evt.getPosition().y;
   rightmouse = evt.getPosition().x;
}

void CanvasDraw::onKeyPressed (const scv::KeyEvent &evt){
   if(isVisible()) {
      auto p = _input->keyboard.find(evt.getKeyCode());
      if (p != _input->keyboard.end())
         p->second = true;
   }
}

void CanvasDraw::onKeyUp(const scv::KeyEvent &evt){
   if(isVisible()){
      auto p = _input->keyboard.find(evt.getKeyCode());
      if (p != _input->keyboard.end())
         p->second = false;
   }
}

void CanvasDraw::onMouseOver(const scv::MouseEvent& evt)
{

}

void CanvasDraw::onMouseWheel(const scv::MouseEvent& evt)
{
   if(evt.getState() == 4)
   {
      _mcam->move_forward(4);
   }else if(evt.getState() == 5)
   {
      _mcam->move_forward(-4);
   }
}

void CanvasDraw::onMouseUp(const scv::MouseEvent& evt)
{
   //_mcam->move_right((float)(evt.getPosition().x-rightmouse)/10.f);
   //_mcam->move_up((float)(evt.getPosition().y-upmouse)/10.f);
}

void CanvasDraw::update(void) 
{
   if(_input->keyboard['d'])//x++
   {
      _mcam->move_right(1);
   }
   if(_input->keyboard['a'])//x--
   {
      _mcam->move_right(-1);
   }
   if(_input->keyboard['s'])
   {
      _mcam->move_forward(-1);
   }
   if(_input->keyboard['w'])
   {
      _mcam->move_forward(1);
   }
   if(_input->keyboard['e'])//z++
   {
      _mcam->move_up(1);
   }
   if(_input->keyboard['q'])//z--
   {
      _mcam->move_up(-1);
   }

   if(_input->keyboard['u'])//Rx++
   {
      _mcam->rotate_pitch(1.f);
   }
   if(_input->keyboard['j'])//Rx--
   {
      _mcam->rotate_pitch(-1.f);
   }
   if(_input->keyboard['o'])//Ry++
   {
      _mcam->rotate_yaw(1.f);
   }
   if(_input->keyboard['l'])//Ry--
   {
      _mcam->rotate_yaw(-1.f);
   }
   if(_input->keyboard['i'])//Rz++
   {
      _mcam->rotate_roll(1.f);
   }
   if(_input->keyboard['k'])//Rz--
   {
      _mcam->rotate_roll(-1.f);
   }
   if(_input->keyboard['g'])
   {
      _mcam->print();
      _input->keyboard['g'] = false;
   }

   std::stringstream sse;
   sse << (_mcam->_p(0,0));
   _xC->setString("X: " + sse.str());
   std::stringstream sse1;
   sse1 << (_mcam->_p(1,0));
   _yC->setString("Y: " + sse1.str());
   std::stringstream sse2;
   sse2 << (_mcam->_p(2,0));
   _zC->setString("Z: " + sse2.str());
}

void desenha(Matriz<4,1> u){
   glVertex3f(u(0,0)+(WL/2), u(1,0)+(WA/2), u(2,0));
}

void CanvasDraw::render(void) 
{  
   _mcam->MatrizTransf();
   glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
   glClear(GL_COLOR_BUFFER_BIT);
   ////////////////////////////////////////////////////////
   //Eixo X,Y,Z Base
   glBegin(GL_LINES);
   Matriz<4,1> t;
   t(0,0) = 0;
   t(1,0) = 0;
   t(2,0) = 0;
   t(3,0) = 1;
   Matriz<4,1> tx;
   tx(0,0) = 0;
   tx(1,0) = 0;
   tx(2,0) = 0;
   tx(3,0) = 1;
   Matriz<4,1> ty = tx;
   ty(0,0) = 10;
   glColor3f(1.f,0.f,0.f);
   t = _mcam->projeta(t);
   ty = _mcam->projeta(ty);
   desenha(t);
   desenha(ty);
   ty = tx;
   ty(1,0) = 10;
   ty = _mcam->projeta(ty);
   glColor3f(0.f,1.f,0.f);
   desenha(t);
   desenha(ty);
   ty = tx;
   ty(2,0) = 10;
   glColor3f(0.f,0.f,1.f);
   ty = _mcam->projeta(ty);
   desenha(t);
   desenha(ty);

   glEnd();
   ////////////////////////////////////////////////////////

   if(_objects == 0){
      /////////////////////////////////////////////////////
      //Cubo
      glBegin(GL_LINES);
      glColor3f(1.f,0.f,0.f);
      Matriz<4,1> v = _mcam->projeta(_obj->_vertex[3]); 
      Matriz<4,1> vx = _mcam->projeta(_obj->_vertex[0]);  
      desenha(v);
      desenha(vx);  
      v = _mcam->projeta(_obj->_vertex[1]); 
      vx = _mcam->projeta(_obj->_vertex[0]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[2]); 
      vx = _mcam->projeta(_obj->_vertex[1]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[3]); 
      vx = _mcam->projeta(_obj->_vertex[2]);  
      desenha(v);
      desenha(vx);
      //

      //
      glColor3f(0.f,1.f,0.f);
      v = _mcam->projeta(_obj->_vertex[5]); 
      vx = _mcam->projeta(_obj->_vertex[4]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[6]); 
      vx = _mcam->projeta(_obj->_vertex[5]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[7]); 
      vx = _mcam->projeta(_obj->_vertex[6]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[7]); 
      vx = _mcam->projeta(_obj->_vertex[4]);  
      desenha(v);
      desenha(vx);
      //

      //
      glColor3f(0.f,0.f,1.f);
      v = _mcam->projeta(_obj->_vertex[0]); 
      vx = _mcam->projeta(_obj->_vertex[4]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[1]); 
      vx = _mcam->projeta(_obj->_vertex[5]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[2]); 
      vx = _mcam->projeta(_obj->_vertex[6]);  
      desenha(v);
      desenha(vx);
      v = _mcam->projeta(_obj->_vertex[7]); 
      vx = _mcam->projeta(_obj->_vertex[3]);  
      desenha(v);
      desenha(vx);
      //

      glEnd(); 
   }else if(_objects == 1){
      /////////////////////////////////////////////////////
      //B-Spline
      glBegin(GL_LINES);
      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();

      glBegin(GL_LINES);
      glColor3f(.5f,.5f,0.f);
      for(int i = 0 ; i < bsp->tami  ; i ++)
      {
         for(int j = 0 ; j < bsp->tamj -1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[i][j]));
            desenha(_mcam->projeta(bsp->vx[i][j+1]));
         }

      }

      for(int i = 0 ; i < bsp->tamj ; i ++)
      {
         for(int j = 0 ; j < bsp->tami-1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[j][i]));
            desenha(_mcam->projeta(bsp->vx[j+1][i]));
         }

      }

      glEnd();
   }else if(_objects == 2){
      /////////////////////////////////////////////////////
      //Bezier
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 

      glBegin(GL_LINES);
      glColor3f(.5f,.0f,5.f);
      for(int i = 0 ; i < bzr->tami  ; i ++)
      {
         for(int j = 0 ; j < bzr->tamj -1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[i][j]));
            desenha(_mcam->projeta(bzr->vx[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->tamj ; i ++)
      {
         for(int j = 0 ; j < bzr->tami-1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[j][i]));
            desenha(_mcam->projeta(bzr->vx[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 3){
      /////////////////////////////////////////////////////
      //B-Spline
      glBegin(GL_LINES);

      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 4){
      /////////////////////////////////////////////////////
      //Bezier

      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 
   }else if(_objects == 5){
      /////////////////////////////////////////////////////
      //Esfera
      glBegin(GL_LINES);
      glColor3f(1.f,1.f,0.f);
      float segmentos = 1.f/25.f;
      for( float s = 0.f ; s < 1.0f ; s += segmentos )
      {
         for( float t = 0.f ; t < 1.0f ; t += segmentos )
         {
            desenha(_mcam->projeta(sph->retPoint(s,t)));
            desenha(_mcam->projeta(sph->retPoint(s,t+segmentos)));

            desenha(_mcam->projeta(sph->retPoint(s,t)));
            desenha(_mcam->projeta(sph->retPoint(s+segmentos,t)));
         }
      }
      glEnd(); 
   }else if(_objects == 6){
      /////////////////////////////////////////////////////
      //Elipsóide
      glBegin(GL_LINES);
      glColor3f(1.f,0.f,1.f);
      float segmentos = 1.f/25.f;
      for( float s = 0.f ; s < 1.0f ; s += segmentos )
      {
         for( float t = 0.f ; t < 1.0f ; t += segmentos )
         {
            desenha(_mcam->projeta(elp->retPoint(s,t)));
            desenha(_mcam->projeta(elp->retPoint(s,t+segmentos)));

            desenha(_mcam->projeta(elp->retPoint(s,t)));
            desenha(_mcam->projeta(elp->retPoint(s+segmentos,t)));
         }
      }
      glEnd(); 
   }else if(_objects == 7){
      /////////////////////////////////////////////////////
      //Super Elipsóide
      glBegin(GL_LINES);
      glColor3f(0.f,.5f,1.f);
      float segmentos = 1.f/25.f;
      for( float s = 0.f ; s < 1.0f ; s += segmentos )
      {
         for( float t = 0.f ; t < 1.0f ; t += segmentos )
         {
            desenha(_mcam->projeta(selp->retPoint(s,t)));
            desenha(_mcam->projeta(selp->retPoint(s,t+segmentos)));

            desenha(_mcam->projeta(selp->retPoint(s,t)));
            desenha(_mcam->projeta(selp->retPoint(s+segmentos,t)));
         }
      }
      glEnd(); 
   }else if(_objects == 8){
      /////////////////////////////////////////////////////
      //Animação plano BSpline
      bsp->rando();
      glBegin(GL_LINES);
      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();

      glBegin(GL_LINES);
      glColor3f(.5f,.5f,0.f);
      for(int i = 0 ; i < bsp->tami  ; i ++)
      {
         for(int j = 0 ; j < bsp->tamj -1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[i][j]));
            desenha(_mcam->projeta(bsp->vx[i][j+1]));
         }

      }

      for(int i = 0 ; i < bsp->tamj ; i ++)
      {
         for(int j = 0 ; j < bsp->tami-1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[j][i]));
            desenha(_mcam->projeta(bsp->vx[j+1][i]));
         }

      }

      glEnd();

   }else if(_objects == 9){
      /////////////////////////////////////////////////////
      //Animação Plano Bezier
      bzr->rando();
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 

      glBegin(GL_LINES);
      glColor3f(.5f,.0f,5.f);
      for(int i = 0 ; i < bzr->tami  ; i ++)
      {
         for(int j = 0 ; j < bzr->tamj -1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[i][j]));
            desenha(_mcam->projeta(bzr->vx[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->tamj ; i ++)
      {
         for(int j = 0 ; j < bzr->tami-1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[j][i]));
            desenha(_mcam->projeta(bzr->vx[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 10){
      /////////////////////////////////////////////////////
      //B-Spline Animado
      bsp->rando();
      glBegin(GL_LINES);

      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 11){
      /////////////////////////////////////////////////////
      //Bezier Animado
      bzr->rando();
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 
   }else if(_objects == 12){
      /////////////////////////////////////////////////////
      //onda plano BSpline
      bsp->wave();
      glBegin(GL_LINES);
      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();

      glBegin(GL_LINES);
      glColor3f(.5f,.5f,0.f);
      for(int i = 0 ; i < bsp->tami  ; i ++)
      {
         for(int j = 0 ; j < bsp->tamj -1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[i][j]));
            desenha(_mcam->projeta(bsp->vx[i][j+1]));
         }

      }

      for(int i = 0 ; i < bsp->tamj ; i ++)
      {
         for(int j = 0 ; j < bsp->tami-1; j++)
         {

            desenha(_mcam->projeta(bsp->vx[j][i]));
            desenha(_mcam->projeta(bsp->vx[j+1][i]));
         }

      }

      glEnd();

   }else if(_objects == 13){
      /////////////////////////////////////////////////////
      //onda Plano Bezier
      bzr->wave();
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 

      glBegin(GL_LINES);
      glColor3f(.5f,.0f,5.f);
      for(int i = 0 ; i < bzr->tami  ; i ++)
      {
         for(int j = 0 ; j < bzr->tamj -1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[i][j]));
            desenha(_mcam->projeta(bzr->vx[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->tamj ; i ++)
      {
         for(int j = 0 ; j < bzr->tami-1; j++)
         {

            desenha(_mcam->projeta(bzr->vx[j][i]));
            desenha(_mcam->projeta(bzr->vx[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 14){
      /////////////////////////////////////////////////////
      //B-Spline onda
      bsp->wave();
      glBegin(GL_LINES);

      glColor3f(1.f,1.f,1.f);
      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[i][j]));
            desenha(_mcam->projeta(bsp->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bsp->vp[j][i]));
            desenha(_mcam->projeta(bsp->vp[j+1][i]));
         }

      }
      glEnd();
   }else if(_objects == 15){
      /////////////////////////////////////////////////////
      //Bezier onda
      bzr->wave();
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[i][j]));
            desenha(_mcam->projeta(bzr->vp[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(bzr->vp[j][i]));
            desenha(_mcam->projeta(bzr->vp[j+1][i]));
         }
      } 
      glEnd(); 
   }else if(_objects == 16){
      /////////////////////////////////////////////////////
      //B-Spline onda
      Matriz<4,1> mx[bsp->sizeVecBsp][bsp->sizeVecBsp];  //71 71
      glBegin(GL_LINES);
      glColor3f(1.f,1.f,1.f);
      for(int i = 0; i < bsp->sizeVecBsp ; i++)
      {
         for(int j = 0; j < bsp->sizeVecBsp; j++)
         {
            mx[i][j] = bsp->vp[i][j];
            mx[i][j](2,0) = bsp->vp[(i+bsp->desloc)%71][j](2,0);
         }
      }   

      bsp->desloc++;
      if(bsp->desloc > bsp->sizeVecBsp-1)
      {
         bsp->desloc = 0;
      }


      for(int i = 0 ; i < bsp->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(mx[i][j]));
            desenha(_mcam->projeta(mx[i][j+1]));
         }
      }

      for(int i = 0 ; i < bsp->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bsp->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(mx[j][i]));
            desenha(_mcam->projeta(mx[j+1][i]));
         }

      }
      glEnd(); 
   }else if(_objects == 17){
      /////////////////////////////////////////////////////
      //Bezier onda
      Matriz<4,1> mx[bzr->sizeVecBsp][bzr->sizeVecBsp];  //31 31
      glBegin(GL_LINES);
      glColor3f(0.f,1.f,0.f);
      for(int i = 0; i < bzr->sizeVecBsp ; i++)
      {
         for(int j = 0; j < bzr->sizeVecBsp; j++)
         {
            mx[i][j] = bzr->vp[i][j];
            mx[i][j](2,0) = bzr->vp[(i+bzr->desloc)%31][j](2,0);
         }
      }   

      bzr->desloc++;
      if(bzr->desloc > bzr->sizeVecBsp-1)
      {
         bzr->desloc = 0;
      }


      for(int i = 0 ; i < bzr->sizeVecBsp  ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp -1; j++)
         {

            desenha(_mcam->projeta(mx[i][j]));
            desenha(_mcam->projeta(mx[i][j+1]));
         }
      }

      for(int i = 0 ; i < bzr->sizeVecBsp ; i ++)
      {
         for(int j = 0 ; j < bzr->sizeVecBsp-1; j++)
         {

            desenha(_mcam->projeta(mx[j][i]));
            desenha(_mcam->projeta(mx[j+1][i]));
         }

      }
      glEnd(); 
   }

   /////////////////////////////////////////////////////
}