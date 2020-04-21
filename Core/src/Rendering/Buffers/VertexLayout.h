#pragma once

#include "glm/glm.hpp"
#include "Utils/Type.h"

namespace Rendering
{
    struct VertexLayout 
    {
        /*
        Positions X Y Z
        Type FLOAT
        Size 3 floats | glm::vec3
        */
        glm::vec3 position;

        /*
        Chanels Red Green Blue Alpha
        Type FLOAT
        Size 4 floats | glm::vec4
        */
        glm::vec4 color;

        /*
        Coor X Y
        Type FLOAT
        Size 2 floats | glm::vec2
        */
        glm::vec2 UVs;
        
        /*
        Normal coordinates X Y Z
        Type FLOAT
        Size 3 floats | glm::vec3
        */
        glm::vec3 normals;
    };
}