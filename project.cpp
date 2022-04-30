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
building* builds[24];
Light* light[10];
Road *road[4];

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
  builds[0] = new building(3, loc, faceColourLoc, modelLoc, vec4(3, -3, 0, 0));
  builds[1] = new building(4, loc, faceColourLoc, modelLoc, vec4(-2, 0, 0, 0)
  ,0 ,0, 90);
  builds[2] = new building(2, loc, faceColourLoc, modelLoc, vec4(3, 2, 0, 0));
  builds[3] = new building(1, loc, faceColourLoc, modelLoc, vec4(-2, 5, 0, 0));
  builds[4] = new building(4, loc, faceColourLoc, modelLoc, vec4(3, 7, 0, 0)
  ,0, 0, 90);
  builds[5] = new building(3, loc, faceColourLoc, modelLoc, vec4(-2, 10, 0, 0));

  //north
  builds[6] = new building(2, loc, faceColourLoc, modelLoc, vec4(-2, 23, 0, 0)
  , 0, 0, 90, 1, 1, 2);
  builds[7] = new building(1, loc, faceColourLoc, modelLoc, vec4(3, 23, 0, 0)
  , 0, 0, 90, 1, 0.7, 0.7);
  builds[8] = new building(4, loc, faceColourLoc, modelLoc, vec4(-2.9, 26, 0, 0)
  , 0, 0, 0, 0.8, 0.6 ,1);
  builds[9] = new building(3, loc, faceColourLoc, modelLoc, vec4(2.8, 28, 0, 0)
  , 0, 0, 0, 0.7, 1, 0.7);
  builds[10] = new building(1, loc, faceColourLoc, modelLoc, vec4(-2, 31, 0, 0)
  ,0, 0, 90, 1, 1.2, 1);
  builds[11] = new building(4, loc, faceColourLoc, modelLoc, vec4(3, 33, 0, 0));

  //south West - south east
  builds[12] = new building(2, loc, faceColourLoc, modelLoc, vec4(5, 13, 0, 0)
  ,0,0,90);
  builds[13] = new building(1, loc, faceColourLoc, modelLoc, vec4(-5, 13, 0, 0));
  builds[14] = new building(3, loc, faceColourLoc, modelLoc, vec4(9, 13, 0, 0));
  builds[15] = new building(4, loc, faceColourLoc, modelLoc, vec4(-7, 13, 0, 0));
  builds[16] = new building(1, loc, faceColourLoc, modelLoc, vec4(12, 13, 0, 0));
  builds[17] = new building(2, loc, faceColourLoc, modelLoc, vec4(-11, 13, 0, 0));

  //north west to north east
  builds[18] = new building(3, loc, faceColourLoc, modelLoc, vec4(-6, 21, 0, 0));
  builds[19] = new building(4, loc, faceColourLoc, modelLoc, vec4(5, 21, 0, 0));
  builds[20] = new building(1, loc, faceColourLoc, modelLoc, vec4(-9, 21, 0, 0));
  builds[21] = new building(2, loc, faceColourLoc, modelLoc, vec4(9, 21, 0, 0));
  builds[22] = new building(4, loc, faceColourLoc, modelLoc, vec4(-13, 21, 0, 0));
  builds[23] = new building(3, loc, faceColourLoc, modelLoc, vec4(12, 21, 0, 0));


  light[0] = new Light(loc, faceColourLoc, modelLoc, vec4(2.8, 21, 0, 0),
           0, 0, 0, 1, 1, 1);
  light[1] = new Light(loc, faceColourLoc, modelLoc, vec4(2.8, 14.5, 0, 0),
           0, 0, -90, 1, 1, 1);
  light[2] = new Light(loc, faceColourLoc, modelLoc, vec4(-1.9, 14.5, 0, 0),
           0, 0, 180, 1, 1, 1);
  light[3] = new Light(loc, faceColourLoc, modelLoc, vec4(-1.9, 21, 0, 0),
            0, 0, 90, 1, 1, 1);

  road[0] = new Road(loc, faceColourLoc, modelLoc);
  glClearColor( 0.40, 0.40, 0.40, 1.0 ); // gray background

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}

//----------------------------------------------------------------------------

bool getCollision() {
  float currentX, currentY, currentZ;
  vec4 currentarray[8];
  for (int i = 0; i < 8; i++) {
    vec4 current = *car[0]->getHitBox()[i];
    currentX = current.x;
    currentY = current.y;
    currentZ = current.z;

    for (int i2 = 0; i2 < road[0]->roadmap().size(); i2++) {
      if (currentX == road[0]->roadmap().at(i2).x) {
        std::cout << "CurrentX: " << currentX << " vs. roadX: " << road[0]->roadmap().at(i2).x << std::endl;
        return false;
      } else if ((currentY == road[0]->roadmap().at(i2).y)) {
        std::cout << "CurrentX: " << currentY << " vs. roadY: " << road[0]->roadmap().at(i2).y << std::endl;
        return false;
    } else if ((currentZ == road[0]->roadmap().at(i2).z)) {
      std::cout << "CurrentX: " << currentZ << " vs. roadZ: " << road[0]->roadmap().at(i2).z << std::endl;
      return false;
    }
    }
  }

  return true;
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

//---------------------------------------------------------------------------

mat4 get_projection(mat4 modelview) {
  GLfloat z1 = 1e10, z2 = -1e10;

  for (int i = 0; i < 8; i++) {
    auto p = modelview * *car[0]->getHitBox();
    z1 = min(z1, -p.z);
    z2 = max(z2, -p.z);
  }

  GLfloat close = z1 - 0.01, away = z2 + 10.0;

  return Perspective(90, 1.0, close, away);
}

//----------------------------------------------------------------------------

void behindView() {
  rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  model = Translate(pos) * rotate * Scale(scale);

  eye = car[0]->getCenter() + getEye();
  vec4 up(0,0,1,0);
  mat4 view = LookAt(eye, car[0]->getCenter(), up);
  mat4 modelView = model * view;
  mat4 proj = Ortho(-5, 5, -5, 5, -1, 100);
  //mat4 proj = get_projection(modelView);

  glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);
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
  mat4 modelView = model * view;
  mat4 proj = Ortho(-5, 5, -5, 5, -1, 100);
  //mat4 proj = get_projection(modelView);

  glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);
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
  { vec4(1,1,0.2,1), vec4(0.5,0.1,0.25,1), vec4(1,0,1,1),};
  vec4 build7[4] =
  { vec4(0.65,0.12,0.8,1), vec4(0.9,0.35,0.05,1), vec4(0.7,0.4,0.2,1),};
  vec4 build8[4] =
  { vec4(0.5,0.72,0.5,1), vec4(0.5,0.22,0.3,1), vec4(0.32,0.34,0.55,1),};
  vec4 build9[4] =
  { vec4(0.48,0.09,0.43,1), vec4(0.42,0.33,0.08,1), vec4(0.99,0.15,0.19,1),};
  vec4 build10[4] =
  { vec4(0.38,0.69,0.7,1), vec4(0.83,0.26,0.38,1), vec4(0.7,0.07,0.27,1),};
  vec4 build11[4] =
  { vec4(0.67,0.23,0.62,1), vec4(0.09,0.46,0.25,1), vec4(0.99,0.15,0.19,1),};
  vec4 build12[4] =
  { vec4(0.62,0.17,0.57,1), vec4(0.56,0.63,0.37,1), vec4(0.68,0.6,0.7,1),};
  vec4 build13[4] =
  { vec4(0.74,0.33,0.6,1), vec4(0.49,0.64,0.56,1), vec4(0.43,0.23,0.47,1),};
  vec4 build14[4] =
  { vec4(0.39,0.88,0.74,1), vec4(0.8,0.67,0.36,1), vec4(0.4,0.53,0.51,1),};
  vec4 build15[4] =
  { vec4(0.57,0.35,0.48,1), vec4(0.31,0.85,0.53,1), vec4(0.43,0.37,0.4,1),};
  vec4 build16[4] =
  { vec4(0.45,0.49,0.55,1), vec4(0.66,0.65,0.46,1), vec4(0.67,0.6,0.2,1),};
  vec4 build17[4] =
  { vec4(0.48,0.55,0.57,1), vec4(0.8,0.37,0.14,1), vec4(0.01,0.69,0.66,1),};
  vec4 build18[4] =
  { vec4(0.81,0.16,0.64,1), vec4(0.54,0.43,0.05,1), vec4(0.58,0.95,0.6,1),};
  vec4 build19[4] =
  { vec4(0.66,0.38,0.42,1), vec4(0.44,0.65,0.9,1), vec4(0.27,0.85,0.13,1),};
  vec4 build20[4] =
  { vec4(0.96,0.46,0.04,1), vec4(0.28,0.5,0.48,1), vec4(0.64,0.21,0.51,1),};
  vec4 build21[4] =
  { vec4(0.31,0.51,0.21,1), vec4(0.43,0.52,0.65,1), vec4(0.57,0.77,0.55,1),};
  vec4 build22[4] =
  { vec4(0.18,0.32,0.24,1), vec4(0.73,0.9,0.27,1), vec4(0.46,0.37,0.71,1),};
  vec4 build23[4] =
  { vec4(0.44,0.59,0.87,1), vec4(0.78,0.52,0.36,1), vec4(0.71,0.4,0.51,1),};


  builds[0]->draw(build1);
  builds[1]->draw(build2);
  builds[2]->draw(build3);
  builds[3]->draw(build4);
  builds[4]->draw(build4);
  builds[5]->draw(build5);
  builds[6]->draw(build6);
  builds[7]->draw(build7);
  builds[8]->draw(build8);
  builds[9]->draw(build9);
  builds[10]->draw(build10);
  builds[11]->draw(build11);
  builds[12]->draw(build12);
  builds[13]->draw(build13);
  builds[14]->draw(build14);
  builds[15]->draw(build15);
  builds[16]->draw(build16);
  builds[17]->draw(build17);
  builds[18]->draw(build18);
  builds[19]->draw(build19);
  builds[20]->draw(build20);
  builds[21]->draw(build21);
  builds[22]->draw(build22);
  builds[23]->draw(build23);
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

  for (int i = 0; i < 4; i++) {
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
  bool possible;
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
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(1.10);
      }
    } else {
      car[0]->updatePos(1.10);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(-1.10);
      }
    }
    break;

    case GLUT_KEY_DOWN:
    if (top == true) {
      car[0]->updatePos(1.10);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(-1.10);
      }
    } else {
      car[0]->updatePos(-1.10);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(1.10);
      }
    }
    break;

    case GLUT_KEY_F1:
    top = false;
    break;

    case GLUT_KEY_F2:
    top = true;
    break;
  }

  std::cout << " Poissble: " << possible << std::endl;

  glutPostRedisplay();
}

//---------------------------------------------------------------------------

void timer(int val)
{
  for (int i = 0; i < 4; i++) {
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
  for (int i = 0; i < 24; i++) {
    delete builds[i];
  }
  for (int i = 0; i < 4; i++) {
    delete light[i];
  }

  delete road[0];

  return 0;
  }
