#include <Angel.h>

#ifndef BUILDING_H
#define BUILDING_H

using namespace std;

class building
{
public:
  building(int type, GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc,
	vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0, GLfloat theta_z = 0,
	GLfloat scale_x = 1, GLfloat scale_y = 1, GLfloat scale_z = 1);
  ~building();

  void next_colour();
  void typeOne();
  void typeTwo();
  void typeThree();
  void typeFour();
  void draw(vec4[]) const;
  

private:
  GLuint vao[5], buffer[5], ebo[6], ebo2[6], ebo3[6], ebo4[6], ebo5[6];
  int TYPE = 1;
  mat4 model;
  int color_index;
  GLuint vertex_loc, face_loc, model_loc;
};

#endif
