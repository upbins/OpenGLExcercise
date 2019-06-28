#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../opengl/src/Shader.h"

class Material
{
private:
    /* data */
public:
    Shader* shader;
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess;
    Material(Shader* _shader,glm::vec3 _diffuse,glm::vec3 _ambient,glm::vec3 _specular,float _shininess);
    ~Material();
};
