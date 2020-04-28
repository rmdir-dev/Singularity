#include "DirectionalLight.h"


namespace Rendering
{
    DirectionalLight::DirectionalLight()
        : m_Direction(glm::vec3(-0.2f, -1.0f, -0.3f)), Lights()
    {
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
        : m_Direction(direction), Lights(color, intensity)
    {
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, float intensity)
        : m_Direction(direction), Lights(intensity)
    {
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction)
        : m_Direction(direction), Lights()
    {
    }

    DirectionalLight::~DirectionalLight() 
    {
        
    }
}