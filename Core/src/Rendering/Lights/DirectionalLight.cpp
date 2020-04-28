#include "DirectionalLight.h"


namespace Rendering
{
    DirectionalLight::DirectionalLight()
        : m_Direction(glm::vec3(-0.2f, -1.0f, -0.3f)), Lights()
    {
        SetupLightBox();
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
        : m_Direction(direction), Lights(color, intensity)
    {
        SetupLightBox();
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, float intensity)
        : m_Direction(direction), Lights(intensity)
    {
        SetupLightBox();
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction)
        : m_Direction(direction), Lights()
    {
        SetupLightBox();
    }

    DirectionalLight::~DirectionalLight() 
    {
        
    }
}