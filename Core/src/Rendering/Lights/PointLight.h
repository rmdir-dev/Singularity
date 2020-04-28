#pragma once

#include "Lights.h"

namespace Rendering
{
    class PointLight : public Lights
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        PointLight();
        PointLight(const glm::vec3& position);
        PointLight(float constant, float linear, float quadratic);
        PointLight(float constant, float linear, float quadratic, const glm::vec3& position);
        PointLight(float constant, float linear, float quadratic, const glm::vec3& position, float intensity);
        PointLight(float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& color, float intensity);
        ~PointLight();

    private:

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        float m_Constant;
        float m_Linear;
        float m_Quadratic;
    private:

    };
}