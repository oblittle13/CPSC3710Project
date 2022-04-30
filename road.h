#include <Angel.h>
#include <vector>

#ifndef ROAD_H
#define ROAD_H


using namespace std;

const int numobjects = 19;

class Road {
    public:
    Road(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc);
    ~Road();

    void draw() const;
    vector<vec4> roadmap();

    private:
    GLuint vao[19], buffer[19], ebo[1];
    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    vector<vec4> roadarea;
};

#endif