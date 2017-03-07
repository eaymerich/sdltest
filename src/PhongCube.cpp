#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/inverse_transpose.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "util.h"

#include "PhongCube.h"

unsigned int PhongCube::phongCubeCounter = 0;

/**
 * Shader IDs
 */
GLuint PhongCube::vertexShaderId = 0;
GLuint PhongCube::fragmentShaderId = 0;
GLuint PhongCube::programObject = 0;

/**
 * Shader variables indexes
 */
GLint PhongCube::v_pos_index = 0;
GLint PhongCube::v_norm_index = 0;
GLint PhongCube::model_matrix_index = 0;
GLint PhongCube::view_matrix_index = 0;
GLint PhongCube::projection_matrix_index = 0;
GLint PhongCube::normal_matrix_index = 0;
GLint PhongCube::ambient_index = 0;
GLint PhongCube::diffuse_index = 0;
GLint PhongCube::specular_index = 0;
GLint PhongCube::shininess_index = 0;
GLint PhongCube::light_src_index = 0;

GLfloat PhongCube::ambient[] = {0.03f, 0.03f, 0.03f};
GLfloat PhongCube::diffuse[] = {0.7f, 0.7f, 0.7f};
GLfloat PhongCube::specular[] = {0.3f, 0.3f, 0.3f};
GLfloat PhongCube::shininess = 100.0f;

/**
 * Flat cube vertices
 */
GLfloat PhongCube::vertices[] = {
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
 * Flat cube normals
 */
GLfloat PhongCube::normals[] = {
    // Front face
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    // Back face
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    // Left face
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // Right face
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    // Top face
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    // Bottom face
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
};

PhongCube::PhongCube() : angle{0.0f} {
    if (phongCubeCounter == 0) {
        char vertex_shader[] =
            "#version 100 \n"
            "uniform mat4  model_m; "
            "uniform mat4  view_m; "
            "uniform mat4  proj_m; "
            "uniform mat3  norm_m; "
            "uniform vec4  light_src;"
            "attribute vec3 v_pos; "
            "attribute vec3 v_norm; "
            "varying vec3  f_norm; "
            "varying vec3  f_light; "
            "varying vec3  f_view; "
            "void main(){ "
            "   vec4 cv_pos = view_m * model_m * vec4(v_pos, 1.0); "
            "   f_light = vec3(view_m * light_src); "
            "   f_norm = mat3(view_m) * norm_m * v_norm; "
            "   f_view = vec3(-cv_pos); "
            "   gl_Position = proj_m * cv_pos; "
            "} ";

        char fragment_shader[] =
            "#version 100 \n"
            "precision mediump float; "
            "uniform vec3 f_ambient; "
            "uniform vec3 f_diffuse; "
            "uniform vec3 f_specular; "
            "uniform float f_shininess; "
            "varying vec3 f_norm; "
            "varying vec3 f_light; "
            "varying vec3 f_view; "
            "void main(){ "
            "   vec3 light = normalize(f_light); "
            "   vec3 normal = normalize(f_norm); "
            "   float doti = dot(light, normal); "
            "   float cos_theta = max(doti, 0.0); "
            "   vec3 i_diff = cos_theta * f_diffuse; "
            ""
            "   vec3 view = normalize(f_view); "
            "   vec3 refl = (2.0 * doti * normal) - light; "
            "   float cos_alpha = max(dot(refl, view), 0.0); "
            "   vec3 i_spec = pow(cos_alpha, f_shininess) * f_specular; "
            ""
            "   vec3 color = min(f_ambient + i_spec + i_diff, 1.0); "
            "   gl_FragColor = vec4(color, 1.0); "
            "} ";

        vertexShaderId = loadShader(vertex_shader, GL_VERTEX_SHADER);
        fragmentShaderId = loadShader(fragment_shader, GL_FRAGMENT_SHADER);
        programObject = linkProgram(vertexShaderId, fragmentShaderId);

        v_pos_index = glGetAttribLocation(programObject, "v_pos");
        v_norm_index = glGetAttribLocation(programObject, "v_norm");
        model_matrix_index = glGetUniformLocation(programObject, "model_m");
        view_matrix_index = glGetUniformLocation(programObject, "view_m");
        projection_matrix_index =
            glGetUniformLocation(programObject, "proj_m");
        normal_matrix_index = glGetUniformLocation(programObject, "norm_m");
        ambient_index = glGetUniformLocation(programObject, "f_ambient");
        diffuse_index = glGetUniformLocation(programObject, "f_diffuse");
        specular_index = glGetUniformLocation(programObject, "f_specular");
        shininess_index = glGetUniformLocation(programObject, "f_shininess");
        light_src_index = glGetUniformLocation(programObject, "light_src");
    }
    ++phongCubeCounter;
}

PhongCube::~PhongCube() {
    --phongCubeCounter;
    if (phongCubeCounter == 0) {
        glDeleteProgram(programObject);
        programObject = 0;
        glDeleteShader(vertexShaderId);
        vertexShaderId = 0;
        glDeleteShader(fragmentShaderId);
        fragmentShaderId = 0;
        v_pos_index = 0;
        v_norm_index = 0;
        model_matrix_index = 0;
        view_matrix_index = 0;
        projection_matrix_index = 0;
        normal_matrix_index = 0;
        ambient_index = 0;
        diffuse_index = 0;
        specular_index = 0;
        shininess_index = 0;
        light_src_index = 0;
    }
}

void PhongCube::update(unsigned int timeelapsed){
    angle = PI/4.0f/1000.0f * timeelapsed;
}

void PhongCube::draw(){
    glUseProgram(programObject);

    // Get and set transformation matrices
    glm::mat4 model = glm::rotate(
        glm::mat4(1.0f),
        angle,
        glm::normalize(glm::vec3(0.0f,1.0f,0.0f)));

    glm::mat4 view = Camera::getCurrentCamera()->viewMatrix();
    glm::mat4 proj = Camera::getCurrentCamera()->projMatrix();

    //glm::mat3 normM = glm::transpose(glm::inverse(glm::mat3(view * model)));
    glm::mat3 normM = glm::transpose(glm::inverse(glm::mat3(model)));

    glUniformMatrix4fv(model_matrix_index, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(view_matrix_index, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_matrix_index, 1, GL_FALSE,
        glm::value_ptr(proj));
    glUniformMatrix3fv(normal_matrix_index, 1, GL_FALSE,
        glm::value_ptr(normM));

    // Set other uniforms
    glUniform3fv(ambient_index, 1, ambient);
    glUniform3fv(diffuse_index, 1, diffuse);
    glUniform3fv(specular_index, 1, specular);
    glUniform1f(shininess_index, shininess);
    //glUniform4f(light_src_index, 1.0f, 1.0f, 1.0f,1.0f);
    glUniform4f(light_src_index, 0.0f, 0.0f, 1.0f, 0.0f);

    // Set Vertex Attributes
    glVertexAttribPointer(v_pos_index, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(v_norm_index, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glEnableVertexAttribArray(v_pos_index);
    glEnableVertexAttribArray(v_norm_index);

    // Draw flat cube
    glDrawArrays(GL_TRIANGLES,0,36);
}
