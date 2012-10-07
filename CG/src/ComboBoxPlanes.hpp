/*Arquivo que contém a classe da combobox para os objetos*/

#ifndef __COMBOBOXPLANES_HPP
#define __COMBOBOXPLANES_HPP
#include "CanvasDraw.h"
#include <SCV/ComboBox.h>

class ComboBox1 : public scv::ComboBox {
   public:

      ComboBox1(CanvasDraw* cv) : scv::ComboBox(scv::Point(10, 70), scv::Point(280, 90)) {
         addItem("Cubo");
         addItem("B-Spline Plane");
         addItem("Plano Bezier");
         addItem("Plano B-Spline(sem Pontos de Controle)");
         addItem("Plano Bezier(sem Pontos de Controle)");
         addItem("Esfera");
         addItem("Elipsoide");
         addItem("Super Elipsoide");
         addItem("Tremer Plano B-Spline");
         addItem("Tremer Plano Bezier");
         addItem("Tremer Plano B-Spline(sem Pontos de Controle)");
         addItem("Tremer Plano Bezier(sem Pontos de Controle)");
         addItem("Onda Plano B-Spline");
         addItem("Onda Plano Bezier");
         addItem("Onda Plano B-Spline(sem Pontos de Controle)");
         addItem("Onda Plano Bezier(sem Pontos de Controle)");
         addItem("Onda B-Spline(sem Pontos de Controle)");
         addItem("Onda Bezier(sem Pontos de Controle)");

         _cv = cv;
         setIndex(0);
      }
      ~ComboBox1() {}

      void onSelectionChanged (std::string address, int id)
      {
         _cv->_objects = id;
      }
      
     CanvasDraw *_cv;
   protected:
   private:

};

#endif;