#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "util.h"

#include "FlatCube.h"

unsigned int FlatCube::flatCubeCounter = 0;

/**
 * Shader IDs
 */
GLuint FlatCube::vertexShaderId = 0;
GLuint FlatCube::fragmentShaderId = 0;
GLuint FlatCube::programObject = 0;

/**
 * Shader variables indexes
 */
GLint FlatCube::v_pos_index = 0;
GLint FlatCube::v_color_index = 0;
GLint FlatCube::model_matrix_index = 0;
GLint FlatCube::view_matrix_index = 0;
GLint FlatCube::projection_matrix_index = 0;

/**
 * Flat cube vertices
 */
GLfloat FlatCube::vertices[] = {
    // Front face
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    // Back face
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    // Left face
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    // Right face
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
    // Top face
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f,  0.5f,
     0.5f, 0.5f, -0.5f,
     0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f,  0.5f,
     0.5f, 0.5f,  0.5f,
    // Bottom face
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
};

/**
 * Flat cube colors
 */
GLfloat FlatCube::colors[] = {
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

FlatCube::FlatCube() :
    angle{0.0f}
{
    if (flatCubeCounter == 0) {
        char vertex_shader[] =
            "#version 100 \n"
            "uniform mat4 model_m; "
            "uniform mat4 view_m; "
            "uniform mat4 proj_m; "
            "attribute vec3 v_pos; "
            "attribute vec3 v_color; "
            "varying   vec3 f_color; "
            "void main(){ "
            "   f_color = v_color; "
            "   gl_Position = proj_m * view_m * model_m * vec4(v_pos,1.0); "
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
        model_matrix_index = glGetUniformLocation(programObject, "model_m");
        view_matrix_index = glGetUniformLocation(programObject, "view_m");
        projection_matrix_index =
            glGetUniformLocation(programObject, "proj_m");
    }
    ++flatCubeCounter;
}

FlatCube::~FlatCube()
{
    --flatCubeCounter;
    if (flatCubeCounter == 0) {
        glDeleteProgram(programObject);
        programObject = 0;
        glDeleteShader(vertexShaderId);
        vertexShaderId = 0;
        glDeleteShader(fragmentShaderId);
        fragmentShaderId = 0;
        v_pos_index = 0;
        v_color_index = 0;
        model_matrix_index = 0;
        view_matrix_index = 0;
        projection_matrix_index = 0;
    }
}


void FlatCube::update(unsigned int timeelapsed){
    angle = PI/4.0f/1000.0f * timeelapsed;
}

void FlatCube::draw(){
    glUseProgram(programObject);

    // Get and set transformation matrices
    //glm::mat4 model(1.0f);
    glm::mat4 model = glm::rotate(
        glm::mat4(1.0f),
        angle,
        glm::normalize(glm::vec3(0.0f,1.0f,0.0f)));

    glm::mat4 view = Camera::getCurrentCamera()->viewMatrix();
    //glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(model_matrix_index, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(view_matrix_index, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_matrix_index, 1, GL_FALSE,
        glm::value_ptr(proj));

    // Set Vertex Attributes
    glVertexAttribPointer(v_pos_index, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(v_color_index, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(v_pos_index);
    glEnableVertexAttribArray(v_color_index);

    // Draw flat cube
    glDrawArrays(GL_TRIANGLES,0,36);
}
