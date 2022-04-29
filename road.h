#include <Angel.h>

#ifndef ROAD_H
#define ROAD_H

using namespace std;

class Road {
    public:
    Road(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc);
    ~Road();

    void draw() const;

    private:
    GLuint vao[19], buffer[19], ebo[1];
    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
};

#endif