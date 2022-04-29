#include "road.h"

const int numobjects = 14;

//---------------------------------------------------------------------------

//Constructor for the road object
Road::Road(Gluint vertexLoc, GLuint faceLoc, GLuint modelLoc) : vertex_loc{vertexLoc}, 
face_loc{faceLoc}, model_loc{modelLoc} {

    glGenVertexArrays(numobjects, vao);
    glGenBuffers(numobjects, buffer);

   const vec4 objects[1][4] = {
       //Grid where the buildings will be held
       {
           vec4(-128, -128, 0 , 1), vec4(128, -128, 0, 1),
           vec4(-128, 128, 0, 1), vec4(128, 128, 0, 1),
       },


   }
}