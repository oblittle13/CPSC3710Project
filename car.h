#include <Angel.h>

#ifndef CAR_H
#define CAR_H

using namespace std;

enum direction {
    north = 0,
    east = 1,
    south = 2,
    west = 3,
};

class Car {
public:
    Car(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc,
	vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0, GLfloat theta_z = 0,
	GLfloat scale_x = 1, GLfloat scale_y = 1, GLfloat scale_z = 1, direction = north);
    ~Car();

    void draw() const;
    void updatePos(float);
    void buildModel();
    void turn(float);
    vec4 getCenter();
    direction getFacing();

private:
    GLuint vao[14], buffer[14], ebo[6];
    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    vec4 pos;
    GLfloat theta_x, theta_y, theta_z, scale_x, scale_y, scale_z;
    direction facing;
    vec4 center;
};

#endif