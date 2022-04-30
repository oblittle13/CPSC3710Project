#include "road.h"

//---------------------------------------------------------------------------

//Constructor for the road object
Road::Road(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc) : vertex_loc{vertexLoc},
face_loc{faceLoc}, model_loc{modelLoc} {

    glGenVertexArrays(numobjects, vao);
    glGenBuffers(numobjects, buffer);

    //Defining the verticies which make up the faces of the body of the car
        const GLuint face[1][4] = {
        {0,1,2,3},  // bottom
    };

    const vec4 objects[numobjects][4] = {
       //Grid where the buildings will be held
       {
           vec4(-64, -64, 0 , 1), vec4(64, -64, 0, 1),
           vec4(64, 64, 0, 1), vec4(-64, 64, 0, 1),
       },

        //vertical road
        {
            vec4(-1, -5, 0.01 , 1), vec4(2, -5, 0.01, 1),
            vec4(2, 50, 0.01, 1), vec4(-1, 50, 0.01, 1),
        },

        //horizontal road
        {
            vec4(-20, 15, 0.01 , 1), vec4(20, 15, 0.01, 1),
            vec4(20, 20, 0.01, 1), vec4(-20, 20, 0.01, 1),
        },



/*
       //Left most - verticle
       {
           vec4(-1, -2, 0.01 , 1), vec4(-0.85, -2, 0.01, 1),
           vec4(-0.85, 30, 0.01, 1), vec4(-1, 30, 0.01, 1),
       },


       //Left most -1 - verticle
       {
           vec4(-40, -64, 0.01 , 1), vec4(-38, -64, 0.01, 1),
           vec4(-38, 64, 0.01, 1), vec4(-40, 64, 0.01, 1),
       },*/

       //Left most -2 - verticle
       {
           vec4(-27, -64, 0.01 , 1), vec4(-25, -64, 0.01, 1),
           vec4(-25, 64, 0.01, 1), vec4(-27, 64, 0.01, 1),
       },

       //Left most -3 - verticle
       {
           vec4(-14, -64, 0.01 , 1), vec4(-12, -64, 0.01, 1),
           vec4(-12, 64, 0.01, 1), vec4(-14, 64, 0.01, 1),
       },

       //Left most -4 - verticle
       {
           vec4(-1, -64, 0.01 , 1), vec4(-1, -64, 0.01, 1),
           vec4(1, 64, 0.01, 1), vec4(1, 64, 0.01, 1),
       },

       //Left most -5 - verticle
       {
           vec4(12, -64, 0.01 , 1), vec4(14, -64, 0.01, 1),
           vec4(14, 64, 0.01, 1), vec4(12, 64, 0.01, 1),
       },

       //Left most -6 - verticle
       {
           vec4(25, -64, 0.01 , 1), vec4(25, -64, 0.01, 1),
           vec4(27, 64, 0.01, 1), vec4(27, 64, 0.01, 1),
       },

       //Left most -7 - verticle
       {
           vec4(38, -64, 0.01 , 1), vec4(40, -64, 0.01, 1),
           vec4(40, 64, 0.01, 1), vec4(38, 64, 0.01, 1),
       },

       //Left most -8 - verticle
       {
           vec4(51, -64, 0.01 , 1), vec4(53, -64, 0.01, 1),
           vec4(53, 64, 0.01, 1), vec4(51, 64, 0.01, 1),
       },

       //Bottom most road - horizontal
       {
           vec4(-64, -53, 0.01, 1), vec4(64, -51, 0.01, 1),
           vec4(64, -51, 0.01, 1), vec4(-64, -53, 0.01, 1),
       },

       //Bottom most road -1 - horizontal
       {
           vec4(-64, -40, 0.01, 1), vec4(64, -40, 0.01, 1),
           vec4(64, -38, 0.01, 1), vec4(-64, -38, 0.01, 1),
       },

       //Bottom most road -2 - horizontal
       {
           vec4(-64, -27, 0.01, 1), vec4(64, -25, 0.01, 1),
           vec4(64, -25, 0.01, 1), vec4(-64, -27, 0.01, 1),
       },

       //Bottom most road -3 - horizontal
       {
           vec4(-64, -14, 0.01, 1), vec4(64, -12, 0.01, 1),
           vec4(64, -12, 0.01, 1), vec4(-64, -14, 0.01, 1),
       },

       //Bottom most road -4 - horizontal
       {
           vec4(-64, -1, 0.01, 1), vec4(64, 1, 0.01, 1),
           vec4(64, 1, 0.01, 1), vec4(-64, -1, 0.01, 1),
       },

       //Bottom most road -5 - horizontal
       {
           vec4(-64, 12, 0.01, 1), vec4(64, 14, 0.01, 1),
           vec4(64, 14, 0.01, 1), vec4(-64, 12, 0.01, 1),
       },

       //Bottom most road -6 - horizontal
       {
           vec4(-64, 25, 0.01, 1), vec4(64, 27, 0.01, 1),
           vec4(64, 27, 0.01, 1), vec4(-64, 25, 0.01, 1),
       },

       //Bottom most road -7 - horizontal
       {
           vec4(-64, 38, 0.01, 1), vec4(64, 40, 0.01, 1),
           vec4(64, 40, 0.01, 1), vec4(-64, 38, 0.01, 1),
       },

       //Bottom most road -8 - horizontal
       {
           vec4(-64, 51, 0.01, 1), vec4(64, 53, 0.01, 1),
           vec4(64, 53, 0.01, 1), vec4(-64, 51, 0.01, 1),
       },
   };
   glGenBuffers(19, ebo);

   //Adding the vertices of the roads into the roadarea vector
   for (int i = 1; i < numobjects; i++) {
       for (int i2 = 0; i2 < 4; i2++) {
           roadarea.push_back(objects[i][i2]);
       }
   }

    for (int i = 0; i < numobjects; i++) {
        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(objects[i]), objects[i], GL_STATIC_DRAW);
        glEnableVertexAttribArray(vertex_loc);
        glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
    	BUFFER_OFFSET(0));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[0], GL_STATIC_DRAW);
    }
}

//---------------------------------------------------------------------------

//Drawing the road
void Road::draw() const{

    //Drawing the body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
    glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
    for (int i = 0; i < numobjects; i++) {
        glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
        glBindVertexArray(vao[i]);
        //Grass -- green in the city blocks, black for the road
        if (i == 0) {
            glUniform4fv(face_loc, 1, vec4(0.45,0.45,0.45,1));
        } else {
            glUniform4fv(face_loc, 1, vec4(0,0,0,1));
        }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
    }
}

//---------------------------------------------------------------------------

//Destructor for road objects
Road::~Road() {
    glDeleteVertexArrays(numobjects, vao);
    glDeleteBuffers(numobjects, buffer);
    glDeleteBuffers(6, ebo);
}

//---------------------------------------------------------------------------

//Returns all verticies of the roads
vector<vec4> Road::roadmap() {
    return roadarea;
}
