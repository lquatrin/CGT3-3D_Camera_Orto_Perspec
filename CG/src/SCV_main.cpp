#include <SCV/Kernel.h>
#include <SCV/ColorScheme.h>
#include <SCV/ButtonGroup.h>
#include <SCV/ComboBox.h>
#include "CanvasDraw.h"
#include "mCamera.hpp"
#include "ComboBoxPlanes.hpp"
#include "Labels.hpp"

int const WL = 1100;
int const WA = 800;

void SCV_main(){

   using namespace scv;

   // Kernel Instance
   static Kernel *kernel = Kernel::getInstance();

   // Load ColorScheme
   static ColorScheme *scheme = ColorScheme::getInstance();
   scheme->loadScheme(ColorScheme::warcraft);

   // Set Windows Size
   kernel->setWindowSize(WL, WA);
   kernel->setWindowTitle("CG_T3");

   // Set Frame Rate
   kernel->setFramesPerSecond(55.f);

   kernel->addComponent(new Label0());

   kernel->addComponent(new Label1());

   kernel->addComponent(new Label2());

   scv::Label *LabelX = new LabelXCam();
   scv::Label *LabelY = new LabelYCam();
   scv::Label *LabelZ = new LabelZCam();
   kernel->addComponent(LabelX);
   kernel->addComponent(LabelY);
   kernel->addComponent(LabelZ);

   ComboBox0 *cb = new ComboBox0();
   
   kernel->addComponent(cb);
   kernel->addComponent(new LabelColorsCam0());
   kernel->addComponent(new LabelColorsCam());
   kernel->addComponent(new LabelsCam());
   kernel->addComponent(new Label3());
   kernel->addComponent(new Label4());
   kernel->addComponent(new Label12());
   kernel->addComponent(new Label11());
   kernel->addComponent(new Label10());

   CanvasDraw *c = new CanvasDraw(cb,LabelX, LabelY, LabelZ);

   kernel->addComponent(c);


   ComboBox1 *c1 = new ComboBox1(c);
   kernel->addComponent(c1);



   kernel->run();

}