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
  glDeleteVertexArrays(5, vao);
  glDeleteBuffers(5, buffer);
  glDeleteBuffers(6, ebo);
  glDeleteBuffers(6, ebo2);
  glDeleteBuffers(6, ebo3);
  glDeleteBuffers(6, ebo4);
  glDeleteBuffers(6, ebo5);

}

void building::typeOne() {
      const vec4 point[8] =
    { vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 6.0, 1.0), vec4(1, -1, 6.0, 1.0),
      vec4(1, 1, 6.0, 1.0), vec4(-1, 1, 6.0, 1.0)
    };

  glGenVertexArrays(3, vao);
  glGenBuffers(3, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

      const vec4 windows_point[8] =
    { vec4(-1.25, 0, 4, 1.0), vec4(1.25, 0, 4, 1.0),
      vec4(1.25, -1.25, 4, 1.0), vec4(-1.25, -1.25, 4, 1.0),
      vec4(-1.25, 0, 5.5, 1.0), vec4(1.25, 0, 5.5, 1.0),
      vec4(1.25, -1.25, 5.5, 1.0), vec4(-1.25, -1.25, 5.5, 1.0)
    };

  glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(windows_point), windows_point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo2);


  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }
    const vec4 windows_point2[8] =
    { vec4(-1.25, 0, 2, 1.0), vec4(1.25, 0, 2, 1.0),
      vec4(1.25, 1.25, 2, 1.0), vec4(-1.25, 1.25, 2, 1.0),
      vec4(-1.25, 0, 3.5, 1.0), vec4(1.25, 0, 3.5, 1.0),
      vec4(1.25, 1.25, 3.5, 1.0), vec4(-1.25, 1.25, 3.5, 1.0)
    };

  glBindVertexArray(vao[2]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(windows_point2), windows_point2, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo3);


  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

}

void building::typeTwo() {

      const vec4 point[8] =
    { vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 1.0, 1.0), vec4(1, -1, 1.0, 1.0),
      vec4(1, 1, 1.0, 1.0), vec4(-1, 1, 1.0, 1.0)
    };

  glGenVertexArrays(2, vao);
  glGenBuffers(2, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

  const vec4 point2[8] = {
  vec4(-1.5, -1.5, 1, 1), vec4(1.5, -1.5, 1, 1),
  vec4(1.5, 1.5, 1, 1), vec4(-1.5, 1.5, 1, 1),
  vec4(-1.25, -0.5, 2, 1), vec4(1.25, -0.5, 2, 1),
  vec4(1.25, 0.5, 2, 1), vec4(-1.25, 0.5, 2, 1)
  };

    glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point2), point2, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo2);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }


}

void building::typeThree() {
        const vec4 point[8] =
    { vec4(-1, -1, 0.0, 1.0), vec4(1, -1, 0.0, 1.0),
      vec4(1, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 3.0, 1.0), vec4(1, -1, 3.0, 1.0),
      vec4(1, 1, 3.0, 1.0), vec4(-1, 1, 3.0, 1.0)
    };

  glGenVertexArrays(5, vao);
  glGenBuffers(5, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }
    const vec4 point2[8] = {
      vec4(-0.75, -0.75, 3.0, 1.0), vec4(0.75, -0.75, 3.0, 1.0),
      vec4(0.75, 0.75, 3.0, 1.0), vec4(-0.75, 0.75, 3.0, 1.0),
      vec4(-0.75, -0.75, 5.0, 1.0), vec4(0.75, -0.75, 5.0, 1.0),
      vec4(0.75, 0.75, 5.0, 1.0), vec4(-0.75, 0.75, 5.0, 1.0)
    };


    glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point2), point2, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo2);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

  const vec4 point3[8] = {
  vec4(-0.5, -0.5, 5, 1), vec4(0.5, -0.5, 5, 1),
  vec4(0.5, 0.5, 5, 1), vec4(-0.5, 0.5, 5, 1),
  vec4(-0.25, -0.25, 7, 1), vec4(0.25, -0.25, 7, 1),
  vec4(0.25, 0.25, 7, 1), vec4(-0.25, 0.25, 7, 1)
  };

    glBindVertexArray(vao[2]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point3), point3, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo3);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }
        const vec4 point4[8] =
    { vec4(-0.5, -1.01, 0.0, 1.0), vec4(0.5, -1.01, 0.0, 1.0),
      vec4(0.5, 1.01, 0.0, 1.0), vec4(-0.5, 1.01, 0.0, 1.0),
      vec4(-0.5, -1.01, 2.0, 1.0), vec4(0.5, -1.01, 2.0, 1.0),
      vec4(0.5, 1.01, 2.0, 1.0), vec4(-0.5, 1.01, 2.0, 1.0)
    };


    glBindVertexArray(vao[3]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point4), point4, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo4);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo4[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

          const vec4 point5[8] =
    { vec4(-1.01, -0.5, 0.0, 1.0), vec4(1.01, -0.5, 0.0, 1.0),
      vec4(1.01, 0.5, 0.0, 1.0), vec4(-1.01, 0.5, 0.0, 1.0),
      vec4(-1.01, -0.5, 2.0, 1.0), vec4(1.01, -0.5, 2.0, 1.0),
      vec4(1.01, 0.5, 2.0, 1.0), vec4(-1.01, 0.5, 2.0, 1.0)
    };

        glBindVertexArray(vao[4]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point5), point5, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo5);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo5[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }



}

void building::typeFour() {
      const vec4 point[8] =
    { vec4(-1, -1, 0.0, 1.0), vec4(2, -1, 0.0, 1.0),
      vec4(2, 1, 0.0, 1.0), vec4(-1, 1, 0.0, 1.0),
      vec4(-1, -1, 3.0, 1.0), vec4(2, -1, 3.0, 1.0),
      vec4(2, 1, 3.0, 1.0), vec4(-1, 1, 3.0, 1.0)
    };

  glGenVertexArrays(4, vao);
  glGenBuffers(4, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

  const vec4 point2[8] =
    { vec4(0, -0.5, 3.0, 1.0), vec4(1.75, -0.5, 3.0, 1.0),
      vec4(1.75, 0.5, 3.0, 1.0), vec4(0, 0.5, 3.0, 1.0),
      vec4(0, -0.5, 3.5, 1.0), vec4(1.75, -0.5, 3.5, 1.0),
      vec4(1.75, 0.5, 3.5, 1.0), vec4(0, 0.5, 3.5, 1.0)
    };
  glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point2), point2, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo2);
  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }


      const vec4 windows_point[8] =
    { vec4(-1.01, 0, 2, 1.0), vec4(1.25, 0, 2, 1.0),
      vec4(1.25, -1.01, 2, 1.0), vec4(-1.01, -1.01, 2, 1.0),
      vec4(-1.01, 0, 2.5, 1.0), vec4(1.25, 0, 2.5, 1.0),
      vec4(1.25, -1.01, 2.5, 1.0), vec4(-1.01, -1.01, 2.5, 1.0)
    };


  glBindVertexArray(vao[2]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(windows_point), windows_point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo3);


  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }


    const vec4 windows_point2[8] =
    { vec4(-1.01, 0, 1, 1.0), vec4(1.25, 0, 1, 1.0),
      vec4(1.25, -1.01, 1, 1.0), vec4(-1.01, -1.01, 1, 1.0),
      vec4(-1.01, 0, 1.5, 1.0), vec4(1.25, 0, 1.5, 1.0),
      vec4(1.25, -1.01, 1.5, 1.0), vec4(-1.01, -1.01, 1.5, 1.0)
    };

  glBindVertexArray(vao[3]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(windows_point2), windows_point2, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glGenBuffers(6, ebo4);


  for (int i = 0; i < 6; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo4[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }


}


void building::draw(vec4 colour[]) const
{

  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[0]);
  for (int i = 0; i < 6; i++) {
    glUniform4fv(face_loc, 1, colour[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }


  glBindVertexArray(vao[1]);
  for (int i = 0; i <6; i++) {
    glUniform4fv(face_loc, 1, colour[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

  }

  glBindVertexArray(vao[2]);
  for (int i = 0; i <6; i++) {
        if (TYPE == 4 ){
        glUniform4fv(face_loc, 1, vec4(0,0,0,1));
        } else {
        glUniform4fv(face_loc, 1, colour[2]);
        }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }

    glBindVertexArray(vao[3]);
  for (int i = 0; i <6; i++) {
    glUniform4fv(face_loc, 1, vec4(0,0,0,1));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }

      glBindVertexArray(vao[4]);
  for (int i = 0; i <6; i++) {
    glUniform4fv(face_loc, 1, vec4(0,0,0,1));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }

}
