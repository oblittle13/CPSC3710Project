#include "car.h"

#include <cmath>

const int numobjects = 14;

//---------------------------------------------------------------------------

//Constrcutor for car objects
Car::Car(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z, direction facing)
  :vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, theta_x{theta_x}, theta_y{theta_y}, theta_z{theta_z},
    scale_x{scale_x}, scale_y{scale_y}, scale_z{scale_z}, facing{facing}  {

        //Defining the verticies which make up the faces of the body of the car
        const GLuint face_recprism[6][4] = {
            {0,1,2,3},  // bottom
            {4,5,6,7},  // top
            {0,1,5,4},  // back bumper
            {2,3,7,6},  // front bumper
            {2,6,5,1},  // passenger side
            {0,4,7,3}   // driver side
        };

        glGenVertexArrays(numobjects, vao);
        glGenBuffers(numobjects, buffer);

        //Creating a way to store each set of vertices for rectangular objects
        const vec4 recobjs[numobjects][8] = {
            //body -- 1
            {
                vec4(-0.5, -1.0, 0.0, 1.0), vec4(0.5, -1.0, 0.0, 1.0),
                vec4(0.5, 0.75, 0.0, 1.0), vec4(-0.5, 0.75, 0.0, 1.0),
                vec4(-0.5, -1.0, 0.25, 1.0), vec4(0.5, -1.0, 0.25, 1.0),
                vec4(0.5, 0.75, 0.25, 1.0), vec4(-0.5, 0.75, 0.25, 1.0)
            }, 

            //Passenger front pillar -- 2
            {
                vec4(-0.40, 0.50, 0.25, 1.0), vec4(-0.50, 0.50, 0.25, 1.0),
                vec4(-0.50, 0.25, 0.25, 1.0), vec4(-0.40, 0.25, 0.25, 1.0),
                vec4(-0.40, 0.25, 0.50, 1.0), vec4(-0.50, 0.25, 0.50, 1.0),
                vec4(-0.40, 0.25, 0.50, 1.0), vec4(-0.50, 0.25, 0.50, 1.0), //doplicated for dummy top
            },

            //Driver front pillar -- 3
            {
                vec4(0.50, 0.50, 0.25, 1.0), vec4(0.40, 0.50, 0.25, 1.0),
                vec4(0.40, 0.25, 0.25, 1.0), vec4(0.50, 0.25, 0.25, 1.0),
                vec4(0.50, 0.25, 0.50, 1.0), vec4(0.40, 0.25, 0.50, 1.0),
                vec4(0.40, 0.25, 0.50, 1.0), vec4(0.50, 0.25, 0.50, 1.0), //duplicated for dummy top
            },

            //Roof -- 4
            {
                vec4(0.50, -0.50, 0.45, 1.0), vec4(-0.50, -0.50, 0.45, 1.0),
                vec4(-0.50, 0.25, 0.45, 1.0), vec4(0.50, 0.25, 0.45, 1.0),
                vec4(0.50, -0.50, 0.50, 1.0), vec4(-0.50, -0.50, 0.50, 1.0),
                vec4(-0.50, 0.25, 0.50, 1.0), vec4(0.50, 0.25, 0.50, 1.0),
            },

            //Passenger rear pillar -- 5
            {
                vec4(0.50, -0.50, 0.25, 1.0), vec4(0.45, -0.50, 0.25, 1.0),
                vec4(0.45, -0.45, 0.25, 1.0), vec4(0.50, -0.45, 0.25, 1.0),
                vec4(0.50, -0.50, 0.50, 1.0), vec4(0.45, -0.50, 0.50, 1.0),
                vec4(0.45, -0.45, 0.50, 1.0), vec4(0.50, -0.45, 0.50, 1.0),
            },

            //Driver rear pillar -- 6
            {
                vec4(-0.50, -0.50, 0.25, 1.0), vec4(-0.45, -0.50, 0.25, 1.0),
                vec4(-0.45, -0.45, 0.25, 1.0), vec4(-0.50, -0.45, 0.25, 1.0),
                vec4(-0.50, -0.50, 0.50, 1.0), vec4(-0.45, -0.50, 0.50, 1.0),
                vec4(-0.45, -0.45, 0.50, 1.0), vec4(-0.50, -0.45, 0.50, 1.0),
            },

            //Front windshield -- 7
            {
                vec4(-0.40, 0.50, 0.25, 1.0), vec4(0.40, 0.50, 0.25, 1.0),
                vec4(-0.40, 0.25, 0.25, 1.0), vec4(0.40, 0.25, 0.25, 1.0),
                vec4(-0.40, 0.25, 0.50, 1.0), vec4(0.40, 0.25, 0.50, 1.0),
                vec4(-0.40, 0.25, 0.50, 1.0), vec4(0.40, 0.25, 0.50, 1.0), //duplicated for dummy top
            },

            //Back windshield -- 8
            {
                vec4(-0.45, -0.50, 0.25, 1.0), vec4(0.45, -0.50, 0.25, 1.0),
                vec4(-0.45, -0.45, 0.25, 1.0), vec4(0.45, -0.45, 0.25, 1.0),
                vec4(-0.45, -0.50, 0.45, 1.0), vec4(0.45, -0.50, 0.45, 1.0),
                vec4(-0.45, -0.45, 0.45, 1.0), vec4(0.45, -0.45, 0.45, 1.0),
            },

            //Passenger window -- 9
            {
                vec4(-0.40, 0.25, 0.25, 1.0), vec4(-0.50, 0.25, 0.25, 1.0),
                vec4(-0.50, -0.45, 0.25, 1.0), vec4(-0.40, -0.45, 0.25, 1.0),
                vec4(-0.40, 0.25, 0.45, 1.0), vec4(-0.50, 0.25, 0.45, 1.0),
                vec4(-0.50, -0.45, 0.45, 1.0), vec4(-0.40, -0.45, 0.45, 1.0),
            },

            //Driver window -- 10
            {
                vec4(0.40, 0.25, 0.25, 1.0), vec4(0.50, 0.25, 0.25, 1.0),
                vec4(0.50, -0.45, 0.25, 1.0), vec4(0.40, -0.45, 0.25, 1.0),
                vec4(0.40, 0.25, 0.45, 1.0), vec4(0.50, 0.25, 0.45, 1.0),
                vec4(0.50, -0.45, 0.45, 1.0), vec4(0.40, -0.45, 0.45, 1.0),
            },

            //DriverRear Wheel -- 11
            {
                vec4(-0.625, -0.625, -0.125, 1.0), vec4(-0.375, -0.625, -0.125, 1.0),
                vec4(-0.375, -0.375, -0.125, 1.0), vec4(-0.625, -0.375, -0.125, 1.0),
                vec4(-0.625, -0.625, 0.125, 1.0), vec4(-0.375, -0.625, 0.125, 1.0),
                vec4(-0.375, -0.375, 0.125, 1.0), vec4(-0.625, -0.375, 0.125, 1.0),
            },

            //PassengerRear Wheel -- 12
            {
                vec4(0.625, -0.625, -0.125, 1.0), vec4(0.375, -0.625, -0.125, 1.0),
                vec4(0.375, -0.375, -0.125, 1.0), vec4(0.625, -0.375, -0.125, 1.0),
                vec4(0.625, -0.625, 0.125, 1.0), vec4(0.375, -0.625, 0.125, 1.0),
                vec4(0.375, -0.375, 0.125, 1.0), vec4(0.625, -0.375, 0.125, 1.0),
            },

            //DriverFront Wheel -- 12
            {
                vec4(-0.625, 0.625, -0.125, 1.0), vec4(-0.375, 0.625, -0.125, 1.0),
                vec4(-0.375, 0.375, -0.125, 1.0), vec4(-0.625, 0.375, -0.125, 1.0),
                vec4(-0.625, 0.625, 0.125, 1.0), vec4(-0.375, 0.625, 0.125, 1.0),
                vec4(-0.375, 0.375, 0.125, 1.0), vec4(-0.625, 0.375, 0.125, 1.0),
            },

            //PassengerRear Wheel -- 12
            {
                vec4(0.625, 0.625, -0.125, 1.0), vec4(0.375, 0.625, -0.125, 1.0),
                vec4(0.375, 0.375, -0.125, 1.0), vec4(0.625, 0.375, -0.125, 1.0),
                vec4(0.625, 0.625, 0.125, 1.0), vec4(0.375, 0.625, 0.125, 1.0),
                vec4(0.375, 0.375, 0.125, 1.0), vec4(0.625, 0.375, 0.125, 1.0),
            },
        };

        //Getting the center of the object
        center = pos;     

        //VAO, EBO and buffers for body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
        for (int i = 0; i < numobjects; i++) {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(recobjs[i]), recobjs[i], GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertex_loc);
            glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

            glGenBuffers(6, ebo);
            for (int index = 0; index < 6; index++) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face_recprism[index], GL_STATIC_DRAW);
            }
        }

        //Building the model for our car
        buildModel();

    }

//---------------------------------------------------------------------------

//Destructor for Car objects
Car::~Car() {
    glDeleteVertexArrays(numobjects, vao);
    glDeleteBuffers(numobjects, buffer);
    glDeleteBuffers(6, ebo);
}

//---------------------------------------------------------------------------

//Builds the model matrix
void Car::buildModel() {
    //Building the model for our car
    model = Translate(pos)
    * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
    * Scale(scale_x, scale_y, scale_z);

    center = pos;
}

//---------------------------------------------------------------------------

//Drawing the car object in the scene
void Car::draw() const {

    //Drawing the body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
    for (int i = 0; i < numobjects; i++) {
        glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

        glBindVertexArray(vao[i]);
        for(int index = 0; index < 6; index++) {
            GLfloat v = 0.75 * (index+1)/6.0;
            //If the object is part of the window group, make it black,
            //else make is varing shades of red
            if (i >= 6) {
                glUniform4fv(face_loc, 1, vec4(0,0,0,1));
            } else {
                glUniform4fv(face_loc, 1, vec4(1,v,v,1)); 
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
        }
    }
}

//---------------------------------------------------------------------------

//Update the position of the car
void Car::updatePos(float move) {
    //if we are facing south or east need to invert the move directions
    if (facing == south || facing == east) {
        move *= -1;
    } else {
        move *= 1;
    }

    //If North or South, move in Y, else move in X
    if (facing == north || facing == south) {
        vec4 temp(0, move, 0 ,0);
        pos += temp;
    } else {
        vec4 temp(move, 0, 0, 0);
        pos += temp;
    }

    buildModel();
}

//---------------------------------------------------------------------------

//Turn the car (rotation about z)
void Car::turn(float deg) {
    theta_z += deg;

    //If we are turing left ( < 0 degrees) adjust facing conter-clockwise, and vice versa
    if (facing == north) {
        if (deg < 0) {
            facing = west;
        } else {
            facing = east;
        }
    } else if (facing == east) {
        if (deg < 0) {
            facing = north;
        } else {
            facing = south;
        }
    } else if (facing == south) {
        if (deg < 0) {
            facing = east;
        } else {
            facing = west;
        }
    } else if (facing == west) {
        if (deg < 0) {
            facing = south;
        } else {
            facing = north;
        }
    }

    buildModel();
}

//---------------------------------------------------------------------------

vec4 Car::getCenter() {
    return center;
}

//---------------------------------------------------------------------------

direction Car::getFacing() {
    return facing;
}

//----------------------------------------------------------------------------

vec4* Car::getHitBox() {
    static vec4 hitbox[8] = {
        vec4(-0.5, -1.0, -0.125, 1.0), vec4(0.5, -1.0, -0.125, 1.0),
        vec4(0.5, 0.75, -0.125, 1.0), vec4(-0.5, 0.75, -0.125, 1.0),
        vec4(-0.5, -1.0, 0.5, 1.0), vec4(0.5, -1.0, 0.5, 1.0),
        vec4(0.5, 0.75, 0.5, 1.0), vec4(-0.5, 0.75, 0.5, 1.0)
    };

    //multiply the model onto the hitbox
    for (int i = 0; i < 8; i++) {
        hitbox[i] = model * hitbox[i];
    }

    return hitbox;
}

//----------------------------------------------------------------------------