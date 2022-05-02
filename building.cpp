#include "building.h"

  const GLuint face[6][4] =
    {
     {0,1,2,3},  // bot
     {4,5,6,7},  // top
     {0,1,5,4},  // back
     {2,3,7,6},  // front
     {2,6,5,1},  // left
     {0,4,7,3}   // right
    };

building::building(int type, GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc, vec4 pos,
                   GLfloat theta_x, GLfloat theta_y, GLfloat theta_z, GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : color_index{0}, vertex_loc{vertexLoc}, face_loc{faceLoc}, model_loc{modelLoc} {
    TYPE = type;
      switch (type)
      {
      case 1:
            typeOne();
            break;
      case 2:
            typeTwo();
            break;
      case 3:
            typeThree();
            break;
      case 4:
            typeFour();
            break;
        default:
            break;
      }

  model = Translate(pos)
    * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
    * Scale(scale_x, scale_y, scale_z);
}

building::~building()
{
  glDeleteVertexArrays(num, vao);
  glDeleteBuffers(num, buffer);
  glDeleteBuffers(6, ebo);

}

void building::typeOne() {
  num = 3;
      const vec4 point[num][8] = {
    //Building
    { 
      vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 6.0, 1.0), vec4(1, -1, 6.0, 1.0),
      vec4(1, 1, 6.0, 1.0), vec4(-1, 1, 6.0, 1.0)
    },

    //Window set 1
    {
      vec4(-1.25, 0, 4, 1.0), vec4(1.25, 0, 4, 1.0),
      vec4(1.25, -1.25, 4, 1.0), vec4(-1.25, -1.25, 4, 1.0),
      vec4(-1.25, 0, 5.5, 1.0), vec4(1.25, 0, 5.5, 1.0),
      vec4(1.25, -1.25, 5.5, 1.0), vec4(-1.25, -1.25, 5.5, 1.0)
    },

    //Window set 2
    { 
      vec4(-1.25, 0, 2, 1.0), vec4(1.25, 0, 2, 1.0),
      vec4(1.25, 1.25, 2, 1.0), vec4(-1.25, 1.25, 2, 1.0),
      vec4(-1.25, 0, 3.5, 1.0), vec4(1.25, 0, 3.5, 1.0),
      vec4(1.25, 1.25, 3.5, 1.0), vec4(-1.25, 1.25, 3.5, 1.0)
    },
  };

  glGenVertexArrays(num, vao);
  glGenBuffers(num, buffer);
        //VAO, EBO and buffers for body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
        for (int i = 0; i < num; i++) {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(point[i]), point[i], GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertex_loc);
            glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

            glGenBuffers(6, ebo);
            for (int index = 0; index < 6; index++) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[index], GL_STATIC_DRAW);
            }
        }

}

void building::typeTwo() {

  num = 2;
  const vec4 point[num][8] = {

    //Building Base
  {
      vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 1.0, 1.0), vec4(1, -1, 1.0, 1.0),
      vec4(1, 1, 1.0, 1.0), vec4(-1, 1, 1.0, 1.0)
    },

    //Building Top
    {
      vec4(-1.5, -1.5, 1, 1), vec4(1.5, -1.5, 1, 1),
      vec4(1.5, 1.5, 1, 1), vec4(-1.5, 1.5, 1, 1),
      vec4(-1.25, -0.5, 2, 1), vec4(1.25, -0.5, 2, 1),
      vec4(1.25, 0.5, 2, 1), vec4(-1.25, 0.5, 2, 1)
    },
  };

    glGenVertexArrays(num, vao);
  glGenBuffers(num, buffer);
        //VAO, EBO and buffers for body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
        for (int i = 0; i < num; i++) {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(point[i]), point[i], GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertex_loc);
            glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

            glGenBuffers(6, ebo);
            for (int index = 0; index < 6; index++) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[index], GL_STATIC_DRAW);
            }
        }


}

void building::typeThree() {
  num = 5;

  const vec4 point[num][8] = {

    //Building Base
    {
      vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 3.0, 1.0), vec4(1, -1, 3.0, 1.0),
      vec4(1, 1, 3.0, 1.0), vec4(-1, 1, 3.0, 1.0)
    },

    //Building Top
    {
      vec4(-0.75, -0.75, 3.0, 1.0), vec4(0.75, -0.75, 3.0, 1.0),
      vec4(0.75, 0.75, 3.0, 1.0), vec4(-0.75, 0.75, 3.0, 1.0),
      vec4(-0.75, -0.75, 5.0, 1.0), vec4(0.75, -0.75, 5.0, 1.0),
      vec4(0.75, 0.75, 5.0, 1.0), vec4(-0.75, 0.75, 5.0, 1.0)
    },

    {
      vec4(-0.5, -0.5, 5, 1), vec4(0.5, -0.5, 5, 1),
      vec4(0.5, 0.5, 5, 1), vec4(-0.5, 0.5, 5, 1),
      vec4(-0.25, -0.25, 7, 1), vec4(0.25, -0.25, 7, 1),
      vec4(0.25, 0.25, 7, 1), vec4(-0.25, 0.25, 7, 1)
    },

    {
      vec4(-0.5, -1.01, 0.0, 1.0), vec4(0.5, -1.01, 0.0, 1.0),
      vec4(0.5, 1.01, 0.0, 1.0), vec4(-0.5, 1.01, 0.0, 1.0),
      vec4(-0.5, -1.01, 2.0, 1.0), vec4(0.5, -1.01, 2.0, 1.0),
      vec4(0.5, 1.01, 2.0, 1.0), vec4(-0.5, 1.01, 2.0, 1.0)
    },

    {
      vec4(-1.01, -0.5, 0.0, 1.0), vec4(1.01, -0.5, 0.0, 1.0),
      vec4(1.01, 0.5, 0.0, 1.0), vec4(-1.01, 0.5, 0.0, 1.0),
      vec4(-1.01, -0.5, 2.0, 1.0), vec4(1.01, -0.5, 2.0, 1.0),
      vec4(1.01, 0.5, 2.0, 1.0), vec4(-1.01, 0.5, 2.0, 1.0)
    },
  };

    glGenVertexArrays(num, vao);
  glGenBuffers(num, buffer);
        //VAO, EBO and buffers for body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
        for (int i = 0; i < 5; i++) {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(point[i]), point[i], GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertex_loc);
            glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

            glGenBuffers(6, ebo);
            for (int index = 0; index < 6; index++) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[index], GL_STATIC_DRAW);
            }
        }

}

void building::typeFour() {
  num = 4;

  const vec4 point[num][8] = {

    //Building Base
    {
      vec4(-1, -1, 0.0, 1.0), vec4(2, -1, 0.0, 1.0),
      vec4(2, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 3.0, 1.0), vec4(2, -1, 3.0, 1.0),
      vec4(2, 1, 3.0, 1.0), vec4(-1, 1, 3.0, 1.0)
    },

    //Building Top
    {
      vec4(0, -0.5, 3.0, 1.0), vec4(1.75, -0.5, 3.0, 1.0),
      vec4(1.75, 0.5, 3.0, 1.0), vec4(0, 0.5, 3.0, 1.0),
      vec4(0, -0.5, 3.5, 1.0), vec4(1.75, -0.5, 3.5, 1.0),
      vec4(1.75, 0.5, 3.5, 1.0), vec4(0, 0.5, 3.5, 1.0)
    },

    {
      vec4(-1.01, 0, 2, 1.0), vec4(1.25, 0, 2, 1.0),
      vec4(1.25, -1.01, 2, 1.0), vec4(-1.01, -1.01, 2, 1.0),
      vec4(-1.01, 0, 2.5, 1.0), vec4(1.25, 0, 2.5, 1.0),
      vec4(1.25, -1.01, 2.5, 1.0), vec4(-1.01, -1.01, 2.5, 1.0)
    },

    {
      vec4(-1.01, 0, 1, 1.0), vec4(1.25, 0, 1, 1.0),
      vec4(1.25, -1.01, 1, 1.0), vec4(-1.01, -1.01, 1, 1.0),
      vec4(-1.01, 0, 1.5, 1.0), vec4(1.25, 0, 1.5, 1.0),
      vec4(1.25, -1.01, 1.5, 1.0), vec4(-1.01, -1.01, 1.5, 1.0)
    },
  };

    glGenVertexArrays(num, vao);
  glGenBuffers(num, buffer);
        //VAO, EBO and buffers for body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
        for (int i = 0; i < 5; i++) {
            glBindVertexArray(vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(point[i]), point[i], GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertex_loc);
            glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

            glGenBuffers(6, ebo);
            for (int index = 0; index < 6; index++) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[index], GL_STATIC_DRAW);
            }
        }

}


void building::draw(vec4 colour[]) const
{
    //Drawing the body, pillarPF, pillarDF, roof, pillarPR, pillarDR, and windows
    for (int i = 0; i < num; i++) {
        glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

        glBindVertexArray(vao[i]);
        for(int index = 0; index < 6; index++) {
            GLfloat v = 0.75 * (index+1)/6.0;

            //If statements to make the object a certain colour depending on which surface it is
            if (i == 1) {
              glUniform4fv(face_loc, 1, colour[0]);
            } else if (i == 1) {
              glUniform4fv(face_loc, 1, colour[1]);
            } else if (i == 2) {
              if (TYPE == 4) {
                glUniform4fv(face_loc, 1, vec4(0,0,0,1));
              } else {
                glUniform4fv(face_loc, 1, colour[2]);
              }
            } else if (i==3 || i == 4) {
              glUniform4fv(face_loc, 1, vec4(0,0,0,1));
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
        }
    }

}
