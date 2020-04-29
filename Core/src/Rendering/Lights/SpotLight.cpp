#include "SpotLight.h"

namespace Rendering
{
    SpotLight::SpotLight()
        : m_CutOff(glm::cos(glm::radians(12.5f))), m_OuterCutOff(glm::cos(glm::radians(17.5f))), 
        m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), Lights(),
        m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff, float outerCutOff)
        : m_CutOff(glm::cos(glm::radians(cutOff))), m_OuterCutOff(glm::cos(glm::radians(outerCutOff))), 
        m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), Lights(position),
        m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff) 
        : m_CutOff(glm::cos(glm::radians(cutOff))), m_OuterCutOff(glm::cos(glm::radians(17.5f))), 
        m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), Lights(position),
        m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction) 
        : m_CutOff(glm::cos(glm::radians(12.5f))), m_OuterCutOff(glm::cos(glm::radians(17.5f))), 
        m_Direction(direction), Lights(position),
        m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        
    }

    SpotLight::SpotLight(const glm::vec3& position) 
        : m_CutOff(glm::cos(glm::radians(12.5f))), m_OuterCutOff(glm::cos(glm::radians(17.5f))), 
        m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), Lights(position),
        m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f)
    {
        
    }

    SpotLight::~SpotLight() 
    {
        
    }
}