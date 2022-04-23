#include <Angel.h>
#include <iostream>

#include "car.h"

using namespace std;

//----------------------------------------------------------------------------

GLfloat theta_x = 0.0, theta_y = 0.0, theta_z = 0.0;

mat4 model, rotate;

vec4 pos(0.0, 0.0, 0.0, 0.0);
vec3 scale(1.0, 1.0, 1.0);
GLint faceColourLoc, modelLoc, viewLoc, projLoc;

vec4 eye;
Car *car[1];

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

  car[0] = new Car(loc, faceColourLoc, modelLoc, vec4(0, 0, 0, 0), 0, 0, 0.125, 3, 3, 3);
  
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
    temp = vec4(0, -5, 3, 0);
  } else if (current == east) {
    temp = vec4(5, 0, 3, 0);
  } else if (current == south) {
    temp = vec4(0, 5, 3, 0);
  } else {
    temp = vec4(-5, 0, 3, 0);
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

  eye = car[0]->getCenter() + vec4(0, 0, 5, 0);
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

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (top == true) {
    topView();
  } else {
    behindView();
  }

  for (int i = 0; i < 1; i++) {
    car[i]->draw();
  }

  glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 033:
    exit( EXIT_SUCCESS );
    break;
  case 'a':
    eye.x -= 0.3;
    break;
  case 'd':
    eye.x += 0.3;
    break;
  case 'w':
    eye.y += 0.3;
    break;
  case 's':
    eye.y -= 0.3;
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
    car[0]->updatePos(0.10);
    break;

    case GLUT_KEY_DOWN:
    car[0]->updatePos(-0.10);
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
  
  glutMainLoop();

  for (int i = 0; i < 1; i++) {
    delete car[i];
  }
  return 0;
}