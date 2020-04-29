#pragma once

#include "Lights.h"

namespace Rendering
{
    class SpotLight : public Lights
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        SpotLight();
        SpotLight(const glm::vec3& position);
        SpotLight(const glm::vec3& position, const glm::vec3& direction);
        SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff);
        SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff, float outerCutOff);
        ~SpotLight();

    private:

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        float m_CutOff;
        float m_OuterCutOff;
        float m_Constant;
        float m_Linear;
        float m_Quadratic;
        glm::vec3 m_Direction;


    private:

    };
}