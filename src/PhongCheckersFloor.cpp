#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "PhongCheckersFloor.h"
#include "util.h"

unsigned int PhongCheckersFloor::instanceCounter = 0;

GLuint PhongCheckersFloor::vertexShaderId = 0;
GLuint PhongCheckersFloor::fragmentShaderId = 0;
GLuint PhongCheckersFloor::programObject = 0;
GLint PhongCheckersFloor::v_pos_index = 0;
GLint PhongCheckersFloor::model_matrix_index = 0;
GLint PhongCheckersFloor::view_matrix_index = 0;
GLint PhongCheckersFloor::projection_matrix_index = 0;
GLint PhongCheckersFloor::ambient_index = 0;
GLint PhongCheckersFloor::diffuse_index = 0;
GLint PhongCheckersFloor::specular_index = 0;
GLint PhongCheckersFloor::shininess_index = 0;
GLint PhongCheckersFloor::light_src_index = 0;

GLfloat PhongCheckersFloor::vertices[] = {
    // Top face
    -0.5f, 0.0f, -0.5f,
    -0.5f, 0.0f,  0.5f,
     0.5f, 0.0f, -0.5f,
     0.5f, 0.0f, -0.5f,
    -0.5f, 0.0f,  0.5f,
     0.5f, 0.0f,  0.5f,
};

PhongCheckersFloor::PhongCheckersFloor() :
    ambient{0.03f, 0.03f, 0.03f},
    specular{0.3f, 0.3f, 0.3f},
    shininess{100.0f}
{
    if (instanceCounter == 0) {
        loadShaders();
    }
    ++instanceCounter;
}

PhongCheckersFloor::~PhongCheckersFloor()
{
    --instanceCounter;
    if (instanceCounter == 0) {
        unLoadShaders();
    }
}

void PhongCheckersFloor::loadShaders() {
    char vertex_shader[] =
        "#version 100 \n"
        "uniform mat4  model_m; "
        "uniform mat4  view_m; "
        "uniform mat4  proj_m; "
        "uniform vec4  light_src;"
        "attribute vec3 v_pos; "
        "varying vec3  f_norm; "
        "varying vec3  f_light; "
        "varying vec3  f_view; "
        "varying vec2  f_pos; "
        "void main(){ "
        "   vec4 cv_pos = view_m * model_m * vec4(v_pos, 1.0); "
        "   if (light_src.w == 0.0) { "
        "      f_light = vec3(view_m * light_src); "
        "   } else { "
        "      f_light = vec3((view_m * light_src) - cv_pos); "
        "   } "
        "   f_light = vec3(view_m * light_src); "
        "   f_norm = mat3(view_m) * vec3(0.0, 1.0, 0.0); "
        "   f_view = vec3(-cv_pos); "
        "   f_pos = vec2(v_pos.x, v_pos.z); "
        "   gl_Position = proj_m * cv_pos; "
        "} ";

    char fragment_shader[] =
        "#version 100 \n"
        "precision mediump float; "
        "uniform vec3 f_ambient; "
        "uniform vec3 f_specular; "
        "uniform float f_shininess; "
        "varying vec3 f_norm; "
        "varying vec3 f_light; "
        "varying vec3 f_view; "
        "varying vec2 f_pos; "
        "void main(){ "
        "   vec2 pos = sin(f_pos*100.0) * 100.0f; "
        "   float i_dif = (pos.x * pos.y) + 0.5; "
        ""
        "   vec3 light = normalize(f_light); "
        "   vec3 normal = normalize(f_norm); "
        "   float doti = dot(light, normal); "
        "   float cos_theta = max(doti, 0.0); "
        "   vec3 i_diff = cos_theta * vec3(i_dif); "
        ""
        "   vec3 view = normalize(f_view); "
        "   vec3 refl = (2.0 * doti * normal) - light; "
        "   float cos_alpha = max(dot(refl, view), 0.0); "
        "   vec3 i_spec = pow(cos_alpha, f_shininess) * f_specular; "
        ""
        "   vec3 color = min(f_ambient + i_spec + vec3(i_diff), 1.0); "
        "   gl_FragColor = vec4(color, 1.0); "
        "} ";

    vertexShaderId = loadShader(vertex_shader, GL_VERTEX_SHADER);
    fragmentShaderId = loadShader(fragment_shader, GL_FRAGMENT_SHADER);
    programObject = linkProgram(vertexShaderId, fragmentShaderId);

    v_pos_index = glGetAttribLocation(programObject, "v_pos");
    model_matrix_index = glGetUniformLocation(programObject, "model_m");
    view_matrix_index = glGetUniformLocation(programObject, "view_m");
    projection_matrix_index = glGetUniformLocation(
        programObject, "proj_m");
    ambient_index = glGetUniformLocation(programObject, "f_ambient");
    specular_index = glGetUniformLocation(programObject, "f_specular");
    shininess_index = glGetUniformLocation(programObject, "f_shininess");
    light_src_index = glGetUniformLocation(programObject, "light_src");
}

void PhongCheckersFloor::unLoadShaders() {
    glDeleteProgram(programObject);
    programObject = 0;
    glDeleteShader(vertexShaderId);
    vertexShaderId = 0;
    glDeleteShader(fragmentShaderId);
    fragmentShaderId = 0;
}

void PhongCheckersFloor::draw() {
    glUseProgram(programObject);

    // Get and set transformation matrices
    //glm::mat4 model = glm::mat4{1.0f};//getModelMatrix();
    float scalef = 100.0f;
    glm::mat4 model = glm::scale(glm::mat4{1.0f}, {scalef, scalef, scalef});
    glm::mat4 view = Camera::getCurrentCamera()->viewMatrix();
    glm::mat4 proj = Camera::getCurrentCamera()->projMatrix();

    glUniformMatrix4fv(model_matrix_index, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(view_matrix_index, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_matrix_index, 1, GL_FALSE,
        glm::value_ptr(proj));

    // Set other uniforms
    glUniform3fv(ambient_index, 1, ambient);
    glUniform3fv(specular_index, 1, specular);
    glUniform1f(shininess_index, shininess);

    // Light as point
    //glUniform4f(light_src_index, 0.0f, 3.0f, 3.0f, 1.0f);
    // Light as direction
    glUniform4f(light_src_index, 0.0f, 0.2f, 1.0f, 0.0f);

    // Set Vertex Attributes
    glVertexAttribPointer(v_pos_index, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(v_pos_index);

    // Draw flat cube
    glDrawArrays(GL_TRIANGLES,0,6);
}
