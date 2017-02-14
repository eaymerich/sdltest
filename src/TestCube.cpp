
//#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "util.h"
#include "TestCube.h"

using namespace std;

unsigned int TestCube::testCubeCounter = 0;
GLuint TestCube::vertexShaderId = 0;
GLuint TestCube::fragmentShaderId = 0;
GLuint TestCube::programObject = 0;
GLint TestCube::v_pos_index = 0;
GLint TestCube::v_color_index = 0;
GLint TestCube::mvp_matrix_index = 0;

GLfloat TestCube::vertices[] = {
        // Front face
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        // Back face
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        // Left face
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        // Right face
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        // Top face
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        // Bottom face
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
    };

GLfloat TestCube::colors[] = {
        // Front face
        0.1f, 0.9f, 0.1f,
        0.1f, 0.9f, 0.1f,
        0.1f, 0.9f, 0.1f,
        0.1f, 0.9f, 0.1f,
        0.1f, 0.9f, 0.1f,
        0.1f, 0.9f, 0.1f,
        // Back face
        0.9f, 0.9f, 0.1f,
        0.9f, 0.9f, 0.1f,
        0.9f, 0.9f, 0.1f,
        0.9f, 0.9f, 0.1f,
        0.9f, 0.9f, 0.1f,
        0.9f, 0.9f, 0.1f,
        // Left face
        0.9f, 0.1f, 0.1f,
        0.9f, 0.1f, 0.1f,
        0.9f, 0.1f, 0.1f,
        0.9f, 0.1f, 0.1f,
        0.9f, 0.1f, 0.1f,
        0.9f, 0.1f, 0.1f,
        // Right face
        0.1f, 0.1f, 0.9f,
        0.1f, 0.1f, 0.9f,
        0.1f, 0.1f, 0.9f,
        0.1f, 0.1f, 0.9f,
        0.1f, 0.1f, 0.9f,
        0.1f, 0.1f, 0.9f,
        // Top face
        0.1f, 0.9f, 0.9f,
        0.1f, 0.9f, 0.9f,
        0.1f, 0.9f, 0.9f,
        0.1f, 0.9f, 0.9f,
        0.1f, 0.9f, 0.9f,
        0.1f, 0.9f, 0.9f,
        // Bottom face
        0.9f, 0.1f, 0.9f,
        0.9f, 0.1f, 0.9f,
        0.9f, 0.1f, 0.9f,
        0.9f, 0.1f, 0.9f,
        0.9f, 0.1f, 0.9f,
        0.9f, 0.1f, 0.9f
    };

TestCube::TestCube() : angle(0.0f) {
    if(testCubeCounter==0){

        char vertex_shader[] =
            "#version 100 \n"
            "uniform mat4 mvp_matrix; "
            "attribute vec3 v_pos; "
            "attribute vec3 v_color; "
            "varying   vec3 f_color; "
            "void main(){ "
            "   gl_Position = mvp_matrix * vec4(v_pos,1.0); "
            "   f_color = v_color; "
            "} ";

        char fragment_shader[] =
            "#version 100 \n"
            "precision mediump float; "
            "varying vec3 f_color; "
            "void main(){ "
            "   gl_FragColor = vec4(f_color, 1.0); "
            "} ";

        vertexShaderId = loadShader(vertex_shader, GL_VERTEX_SHADER);
        fragmentShaderId = loadShader(fragment_shader, GL_FRAGMENT_SHADER);
        programObject = linkProgram(vertexShaderId, fragmentShaderId);

        v_pos_index = glGetAttribLocation(programObject, "v_pos");
        v_color_index = glGetAttribLocation(programObject, "v_color");
        mvp_matrix_index = glGetUniformLocation(programObject, "mvp_matrix");
    }
    testCubeCounter++;
}

TestCube::~TestCube(){
    testCubeCounter--;
    if(testCubeCounter == 0){
        glDeleteProgram(programObject);
        programObject = 0;
        glDeleteShader(vertexShaderId);
        vertexShaderId = 0;
        glDeleteShader(fragmentShaderId);
        fragmentShaderId = 0;
        v_pos_index = 0;
        v_color_index = 0;
    }
}

void TestCube::update(unsigned int timeelapsed){

    angle = PI/4.0f/1000.0f * timeelapsed;
}

void TestCube::draw(){
    glUseProgram(programObject);

    /*
    GLfloat mvp[] = {
    0.1f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    };
    glUniformMatrix4fv(mvp_matrix_index, 1, GL_FALSE, mvp);*/

    //glm::mat4 mvp = glm::rotate(glm::mat4(1.0f), Rotate.z, glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 mvp = glm::rotate(glm::mat4(1.0f), PI/4.0f, glm::normalize(glm::vec3(0.0f,1.0f,1.0f)) );
    glm::mat4 mvp = glm::rotate(glm::mat4(1.0f), angle, glm::normalize(glm::vec3(0.0f,1.0f,1.0f)) );
    glUniformMatrix4fv(mvp_matrix_index, 1, GL_FALSE, glm::value_ptr(mvp) );

    glVertexAttribPointer(v_pos_index,3,GL_FLOAT,GL_FALSE,0, vertices);
    glVertexAttribPointer(v_color_index,3,GL_FLOAT,GL_FALSE,0, colors);
    glEnableVertexAttribArray(v_pos_index);
    glEnableVertexAttribArray(v_color_index);

    glDrawArrays(GL_TRIANGLES,0,36);
}
