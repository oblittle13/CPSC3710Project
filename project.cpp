#include <Angel.h>
#include <iostream>

#include "car.h"
#include "building.h"
#include "trafficLight.h"
#include "road.h"

using namespace std;

//----------------------------------------------------------------------------

GLfloat theta_x = 0.0, theta_y = 0.0, theta_z = 0.0;

mat4 model, rotate;

vec4 pos(0.0, 0.0, 0.0, 0.0);
vec3 scale(1.0, 1.0, 1.0);
GLuint faceColourLoc, modelLoc, viewLoc, projLoc;

vec4 eye;
Car *car[1];
building* builds[23];
Light* light[10];
Road *road[1];

bool top = false;

void init()
{
  // Load shaders and use the resulting shader program
  GLuint program = InitShader("vshader.glsl", "fshader.glsl");
  glUseProgram(program);
  faceColourLoc = glGetUniformLocation(program, "uFaceColour");
  modelLoc = glGetUniformLocation(program, "uModel");
  viewLoc = glGetUniformLocation(program, "uView");
  projLoc = glGetUniformLocation(program, "uProjection");

  // Initialize the vertex position attribute from the vertex shader
  GLuint loc = glGetAttribLocation( program, "vPosition" );

  car[0] = new Car(loc, faceColourLoc, modelLoc, vec4(0, 0, 0, 0), 0, 0, 0.125, 1, 1, 1);

  //south
  builds[0] = new building(3, loc, faceColourLoc, modelLoc, vec4(3, 0, 0, 0));
  builds[1] = new building(4, loc, faceColourLoc, modelLoc, vec4(-3, 0, 0, 0));
  builds[2] = new building(2, loc, faceColourLoc, modelLoc, vec4(3, 5, 0, 0));
  builds[3] = new building(1, loc, faceColourLoc, modelLoc, vec4(-3, 5, 0, 0));
  builds[4] = new building(4, loc, faceColourLoc, modelLoc, vec4(3, 10, 0, 0),0, 0, 90);
  builds[5] = new building(3, loc, faceColourLoc, modelLoc, vec4(-3, 10, 0, 0));

  //north
  builds[6] = new building(2, loc, faceColourLoc, modelLoc, vec4(-3, 15, 0, 0));
  builds[7] = new building(1, loc, faceColourLoc, modelLoc, vec4(3, 15, 0, 0));
  builds[8] = new building(4, loc, faceColourLoc, modelLoc, vec4(-3, 20, 0, 0));
  builds[9] = new building(3, loc, faceColourLoc, modelLoc, vec4(3, 20, 0, 0));
  builds[10] = new building(1, loc, faceColourLoc, modelLoc, vec4(-3, 25, 0, 0));
  builds[11] = new building(4, loc, faceColourLoc, modelLoc, vec4(3, 25, 0, 0));

  //south West - south east
  builds[12] = new building(2, loc, faceColourLoc, modelLoc, vec4(6, 10, 0, 0));
  builds[13] = new building(1, loc, faceColourLoc, modelLoc, vec4(-6, 10, 0, 0));
  builds[14] = new building(3, loc, faceColourLoc, modelLoc, vec4(9, 10, 0, 0));
  builds[15] = new building(4, loc, faceColourLoc, modelLoc, vec4(-9, 10, 0, 0));
  builds[16] = new building(1, loc, faceColourLoc, modelLoc, vec4(12, 10, 0, 0));
  builds[17] = new building(2, loc, faceColourLoc, modelLoc, vec4(-12, 10, 0, 0));

  //north west to north east
  builds[18] = new building(3, loc, faceColourLoc, modelLoc, vec4(-6, 15, 0, 0));
  builds[19] = new building(4, loc, faceColourLoc, modelLoc, vec4(6, 15, 0, 0));
  builds[20] = new building(1, loc, faceColourLoc, modelLoc, vec4(-9, 15, 0, 0));
  builds[21] = new building(2, loc, faceColourLoc, modelLoc, vec4(9, 15, 0, 0));
  builds[22] = new building(4, loc, faceColourLoc, modelLoc, vec4(-12, 15, 0, 0));
  builds[23] = new building(3, loc, faceColourLoc, modelLoc, vec4(12, 15, 0, 0));


  light[0] = new Light(loc, faceColourLoc, modelLoc, vec4(1, 0, 0, 0),
           0, 0, 90, 1, 1, 1);
  road[0] = new Road(loc, faceColourLoc, modelLoc);
  glClearColor( 0.40, 0.40, 0.40, 1.0 ); // gray background

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}

//----------------------------------------------------------------------------

vec4 getEye() {
  direction current = car[0]->getFacing();
  vec4 temp;

  if (current == north) {
    temp = vec4(0, -5, 2, 0);
  } else if (current == east) {
    temp = vec4(5, 0, 2, 0);
  } else if (current == south) {
    temp = vec4(0, 5, 2, 0);
  } else {
    temp = vec4(-5, 0, 2, 0);
  }

  return temp;
}

//----------------------------------------------------------------------------

void behindView() {
  rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  model = Translate(pos) * rotate * Scale(scale);

  eye = car[0]->getCenter() + getEye();
  vec4 up(0,0,1,0);
  mat4 view = LookAt(eye, car[0]->getCenter(), up);
  mat4 proj = Ortho(-5, 5, -5, 5, -1, 100);

  glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);
  glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
}

//---------------------------------------------------------------------------

void topView() {
  rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  model = Translate(pos) * rotate * Scale(scale);

  eye = car[0]->getCenter() + vec4(0, 0, 15, 0);
  vec4 up;
  direction current = car[0]->getFacing();
    if (current == north) {
    up = vec4(0, -1, 0, 0);
  } else if (current == east) {
    up = vec4(1, 0, 0, 0);
  } else if (current == south) {
    up= vec4(0, 1, 0, 0);
  } else {
    up = vec4(-1, 0, 0, 0);
  }

  mat4 view = LookAt(eye, car[0]->getCenter(), up);
  mat4 proj = Ortho(-5, 5, -5, 5, -1, 100);

  glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);
  glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
}

//---------------------------------------------------------------------------
void drawBuildings() {
  vec4 build1[3] =
{ vec4(0.97,0,1,1), vec4(0.5,0,0.9,1), vec4(0.75,0.25,0.35,1),};
  vec4 build2[3] =
  { vec4(1,1,1,1), vec4(00,1,1,1), vec4(0.75,0.25,0.35,1),};
  vec4 build3[3] =
  { vec4(1,0.8,0.6,1), vec4(1,0,0,1),};
  vec4 build4[4] =
  { vec4(0.87,0.8,1,1), vec4(0.85,0,0.85,1), vec4(0,0,1,1),};
  vec4 build5[4] =
  { vec4(0.2,0.8,1,1), vec4(0.15,0,0.65,1), vec4(1,0,1,1),};
  vec4 build6[4] =
  { vec4(0.3,1,0.2,1), vec4(0.5,0.1,0.25,1), vec4(1,0,1,1),};




  vec4 build[3] =
{ vec4(0.75,0.75,0.75,1), vec4(0.75,0.75,0.75,1), vec4(0.75,0.75,0.75,1),};

  builds[0]->draw(build1);
  builds[1]->draw(build2);
  builds[2]->draw(build3);
  builds[3]->draw(build4);
  builds[4]->draw(build4);
  builds[5]->draw(build5);
  builds[6]->draw(build6);

}

//---------------------------------------------------------------------------

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (top == true) {
    topView();
  } else {
    behindView();
  }
   drawBuildings();

  for (int i = 0; i < 1; i++) {
    car[i]->draw();
  }



  for (int i = 0; i < 1; i++) {
    light[i]->draw();
  }

  road[0]->draw();

  glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 033:
    exit( EXIT_SUCCESS );
    break;
  }
  glutPostRedisplay();
}

//---------------------------------------------------------------------------

//Movement function for the car and view swap
void arrow(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_LEFT:
    car[0]->turn(90);
    break;

    case GLUT_KEY_RIGHT:
    car[0]->turn(-90);
    break;

    case GLUT_KEY_UP:
    if (top == true) {
      car[0]->updatePos(-1.10);
    } else {
      car[0]->updatePos(1.10);
    }
    break;

    case GLUT_KEY_DOWN:
    if (top == true) {
      car[0]->updatePos(1.10);
    } else {
      car[0]->updatePos(-1.10);
    }
    break;

    case GLUT_KEY_F1:
    top = false;
    break;

    case GLUT_KEY_F2:
    top = true;
    break;
  }

  glutPostRedisplay();
}

//---------------------------------------------------------------------------

void timer(int val)
{
  for (int i = 0; i < 1; i++) {
    light[i]->next_colour();
  }
  glutPostRedisplay();
  glutTimerFunc(3000, timer, 0);
}

//---------------------------------------------------------------------------

int main( int argc, char **argv )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);

  // If you are using freeglut, the next two lines will check if
  // the code is truly 3.2. Otherwise, comment them out

  glutInitContextVersion(3, 2);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutCreateWindow("Car Go Vroom");

  glewInit();

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrow);
  glutTimerFunc(3000, timer, 0);

  glutMainLoop();

  for (int i = 0; i < 1; i++) {
    delete car[i];
  }
  for (int i = 0; i < 1; i++) {
    delete builds[i];
  }
  for (int i = 0; i < 1; i++) {
    delete light[i];
  }

  delete road[0];

  return 0;
  }
