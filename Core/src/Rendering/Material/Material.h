#pragma once

#include "glm/glm.hpp"

#define BaseMaterial    {\
                            glm::vec4(0.5),\
                            glm::vec4(0.5),\
                            glm::vec4(1.0),\
                            1.0f,\
                            16\
                        }

struct Material 
{
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float opacity;
    float shininess;
};