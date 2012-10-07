#ifndef __LABELS__CG___
#define __LABELS__CG___

#include <SCV/Label.h>

class LabelsCam : public scv::Label {
   public:

      LabelsCam() : scv::Label(scv::Point(30, 100), "Coordinates of the camera:") {

      }
      ~LabelsCam() {}

   protected:
   private:

};

class LabelXCam : public scv::Label {
   public:

      LabelXCam() : scv::Label(scv::Point(30, 115), "X: ") {

      }
      ~LabelXCam() {}

   protected:
   private:

};

class LabelColorsCam0 : public scv::Label {
   public:

      LabelColorsCam0() : scv::Label(scv::Point(30,170), "Axis Colors:") {

      }
      ~LabelColorsCam0() {}

   protected:
   private:

};


class LabelColorsCam : public scv::Label {
   public:

      LabelColorsCam() : scv::Label(scv::Point(30,185), "X: Red Y: Green Z: Blue") {

      }
      ~LabelColorsCam() {}

   protected:
   private:

};

class LabelYCam : public scv::Label {
   public:

      LabelYCam() : scv::Label(scv::Point(30, 130), "Y: ") {

      }
      ~LabelYCam() {}

   protected:
   private:

};

class LabelZCam : public scv::Label {
   public:

      LabelZCam() : scv::Label(scv::Point(30, 145), "Z: ") {

      }
      ~LabelZCam() {}

   protected:
   private:

};

class Label0 : public scv::Label {
   public:

      Label0() : scv::Label(scv::Point(50, 225), "(o, l), (i, k), (u, j) -> Rotation") {

      }
      ~Label0() {}

   protected:
   private:

};
class Label1 : public scv::Label {
   public:

      Label1() : scv::Label(scv::Point(40, 240), "(w, s), (a, d), (q, e) -> Translation") {

      }
      ~Label1() {}

   protected:
   private:

};
class Label10 : public scv::Label {
   public:

      Label10() : scv::Label(scv::Point(90, 255), "Mouse Buttons:") {

      }
      ~Label10() {}

   protected:
   private:


};

class Label12 : public scv::Label {
   public:

      Label12() : scv::Label(scv::Point(33, 270), "Left(Hold) e wheelUp/Down -> Translation") {

      }
      ~Label12() {}

   protected:
   private:


};
class Label11 : public scv::Label {
   public:

      Label11() : scv::Label(scv::Point(45, 285), "Right(Hold) e Middle(Hold) -> Rotation") {

      }
      ~Label11() {}

   protected:
   private:

};
class Label2 : public scv::Label {
   public:

      Label2() : scv::Label(scv::Point(100, 210), "Commands:") {

      }
      ~Label2() {}

   protected:
   private:

};

class Label3 : public scv::Label {
   public:

      Label3() : scv::Label(scv::Point(60, 14), "Choose Projection:") {

      }
      ~Label3() {}

   protected:
   private:

};

class Label4 : public scv::Label {
   public:

      Label4() : scv::Label(scv::Point(55, 55), "Object/Plane to draw:") {

      }
      ~Label4() {}

   protected:
   private:

};

#endif