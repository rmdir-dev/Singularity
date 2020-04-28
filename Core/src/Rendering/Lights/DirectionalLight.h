#pragma once
#include "Lights.h"

namespace Rendering
{
    class DirectionalLight : public Lights
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        DirectionalLight();
        DirectionalLight(const glm::vec3& direction);
        DirectionalLight(const glm::vec3& direction, float intensity);
        DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity);
        ~DirectionalLight();

    private:

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        glm::vec3 m_Direction;
        
    private:
    };
}