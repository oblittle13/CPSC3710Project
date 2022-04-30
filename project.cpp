#include <Angel.h>
#include <iostream>
#include <random>

#include "car.h"
#include "building.h"
#include "trafficLight.h"
#include "road.h"

using namespace std;

//----------------------------------------------------------------------------

//Global variables

GLfloat theta_x = 0.0, theta_y = 0.0, theta_z = 0.0;

mat4 model, rotate;

vec4 pos(0.0, 0.0, 0.0, 0.0);
vec3 scale(1.0, 1.0, 1.0);
GLuint faceColourLoc, modelLoc, viewLoc, projLoc;
float build_colour[484*3];

vec4 eye;
Car *car[1];
building* builds[484];
Light* light[324];
Road *road[4];

int count;

bool top = false;
bool first_display = true;

//----------------------------------------------------------------------------

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

  //Creating the car
  car[0] = new Car(loc, faceColourLoc, modelLoc, vec4(0, 0, 0, 0), 0, 0, 0.125, 1, 1, 1);


  //This "algorith" creates the buildings with different coordinates, but makes sure that they don't end up on the road or out of bounds
  // Alternates types (1 of 4), and move each building to be centered 6.5 units away (a block is 13 units wide including 1 road)
  int type = -1;
  double Xchange = -61.5;
  double Ychange = 61.5;
  bool first = true;
  for (int i = 0; i < 484; i++) {
    type++;

    if (first) {
      Ychange -= 6.5;
    } else {
      Ychange -= 6.5;
    }

    if (Xchange > 64) {
      break;
    }

    if(first) {
      first = false;
    } else {
      first = true;
    }

    builds[i] = new building(type * 3 % 4, loc, faceColourLoc, modelLoc, vec4(Xchange, Ychange, 0, 0), 0, 0 ,0, 1, 1, 1);

    if (Ychange < -55) {
      Ychange = 61.5;
      Xchange += 6.5;
    }

    count++;

  }

  //Using the "algorithm" to place the lights, a road is 2 units wide, so we move the other 4 traffic lights to each 3 units away from eachother
  //This makes it so all the traffic lights are on the corner of the block
  double positionX = -53.5;
  double positionY = 53.5;
  for (int i = 0; i < 81; i++) {
    light[0 + 4 * i] = new Light(loc, faceColourLoc, modelLoc, vec4(positionX, positionY, 0, 0), 0, 0, -90, 1, 1, 1);
    light[1 + 4 * i] = new Light(loc, faceColourLoc, modelLoc, vec4(positionX, positionY -3, 0, 0), 0, 0, 0, 1, 1, 1);
    light[2 + 4 * i] = new Light(loc, faceColourLoc, modelLoc, vec4(positionX + 3, positionY, 0, 0), 0, 0, 180, 1, 1, 1);
    light[3 + 4 * i] = new Light(loc, faceColourLoc, modelLoc, vec4(positionX + 3, positionY -3, 0, 0), 0, 0, 90, 1, 1, 1);

    positionX += 13;

    if (i % 9 == 0 && i != 0) {
      positionX = -53.5;
      positionY -= 13;
    }
  }

  //Creating the road (this includes the blocks and roads)
  road[0] = new Road(loc, faceColourLoc, modelLoc);


  glClearColor( 0.40, 0.40, 0.40, 1.0 ); // gray background

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}

//----------------------------------------------------------------------------

//This as of now is incomplete
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

//Gets the position of the eye, as well as what direction it is facing
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

//Calculation of perspective viewing
mat4 get_projection(mat4 modelview) {
  GLfloat z1 = 1e10, z2 = -1e10;

  for (int i = 0; i < 8; i++) {
    auto p = *car[0]->getHitBox();
    z1 = min(z1, -p.z);
    z2 = max(z2, -p.z);
  }

  GLfloat close = z1 - 0.01, away = z2 + 30;

  return Perspective(90, 1.0, close, away);
}

//----------------------------------------------------------------------------

//This gives us our model and view for when we are behind the car. It is a few units up and behind
void behindView() {
  rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  model = Translate(pos) * rotate * Scale(scale);

  eye = car[0]->getCenter() + getEye();
  vec4 up(0,0,1,0);
  mat4 view = LookAt(eye, car[0]->getCenter(), up);
  mat4 modelView = model * view;
  mat4 proj = get_projection(modelView);

  glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);
  glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);
  glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
}

//---------------------------------------------------------------------------

//This gives us the model and view when we are above the car, its just units straight above the car
void topView() {
  rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  model = Translate(pos) * rotate * Scale(scale);

  eye = car[0]->getCenter() + vec4(0, 0, 20, 0);
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
  mat4 proj = get_projection(modelView);

  glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);
  glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);
  glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
}

//---------------------------------------------------------------------------

//This functions draws the buildings, takes in the colours from a different functions
void drawBuildings() {
  for (int i = 0; i < count; i++) {
    //You may be asking yourself, what on earth is this? Well its the random numbers of array indices
    //my computer just doesnt like at all, so we skip them -- O'Brien Little
    if (i == 9 || i == 10 || i == 24 || i == 54 || i == 111 || i == 113 || i == 114
    || i == 230 || i == 232 || i == 234 || i == 264 || i == 360 || i == 361 || i == 362 || i == 392 || i == 406 || i == 464
    || i == 466 || i == 468 || i == 470 || i == 472) {
      continue;
    }

    float a = build_colour[0 + i*3];
    float b = build_colour[2 + i*3];
    float c = build_colour[3 + i*3];
    vec4 colour[3] = {
      vec4(a,b,c,1), vec4(c, a, b, 1), vec4(b, c, a, 1)
    };
    builds[i]->draw(colour);
  }

}
//---------------------------------------------------------------------------

//This functions generates random colours using srand and time. The random generator from 0 to 1 was found on:
// stackexcahnge, if i can find the post again, ill add it in here, but just know i didnt come up with it
void genColours() {
  //Im using a random number generator from 0 - 1 here, in order to randomize the colours,
// much easier than creating 484 * 3 vec4s...
  constexpr int FLOAT_MIN = 0;
  constexpr int FLOAT_MAX = 1;

  srand(time(nullptr));
    for (int i = 0; i < count; i++) {
    //You may be asking yourself, what on earth is this? Well its the random numbers of array indices
    //my computer just doesnt like at all, so we skip them -- O'Brien Little
    if (i == 9 || i == 10 || i == 24 || i == 54 || i == 111 || i == 113 || i == 114
    || i == 230 || i == 232 || i == 234 || i == 264 || i == 392 || i == 406 || i == 464
    || i == 466 || i == 468 || i == 470 || i == 472) {
      continue;
    }

    build_colour[0 + i*3] = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
    build_colour[1 + i*3] = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
    build_colour[2 + i*3] = FLOAT_MIN + (float)(rand()) / ((float)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));



  }
}

//---------------------------------------------------------------------------

//This functions displays all elements of the scene
void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (top == true) {
    topView();
  } else {
    behindView();
  }

  //This is so the buildings don't change colours every redisplay
  if (first_display) {
    genColours();
    first_display = false;
  }

  drawBuildings();

  for (int i = 0; i < 1; i++) {
    car[i]->draw();
  }

  for (int i = 0; i < 324; i++) {
    light[i]->draw();
  }

  road[0]->draw();

  glutSwapBuffers();
}

//----------------------------------------------------------------------------

//Processes keyboard inputs
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
      car[0]->updatePos(-1);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(1);
      }
    } else {
      car[0]->updatePos(1);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(-1);
      }
    }
    break;

    case GLUT_KEY_DOWN:
    if (top == true) {
      car[0]->updatePos(1);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(-1);
      }
    } else {
      car[0]->updatePos(-1);
      possible = getCollision();
      if (possible == false) {
        car[0]->updatePos(1);
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

  glutPostRedisplay();
}

//---------------------------------------------------------------------------

//Timer which changes the colours of the traffic lights
void timer(int val)
{
  for (int i = 0; i < 324; i++) {
    light[i]->next_colour();
  }
  glutPostRedisplay();
  glutTimerFunc(3000, timer, 0);
}

//---------------------------------------------------------------------------

//Main
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
