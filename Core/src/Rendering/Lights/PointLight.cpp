#include "PointLight.h"

namespace Rendering
{
    PointLight::PointLight() 
        : m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f), Lights()
    {
        
    }

    PointLight::PointLight(const glm::vec3& position)
        : m_Constant(1.0f), m_Linear(0.09f), m_Quadratic(0.032f), Lights(position) 
    {
        
    }

    PointLight::PointLight(float constant, float linear, float quadratic, const glm::vec3& position, const glm::vec3& color, float intensity)
        : m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic), Lights(position, color, intensity)
    {
        
    }

    PointLight::PointLight(float constant, float linear, float quadratic, const glm::vec3& position, float intensity)
        : m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic), Lights(position, intensity)
    {
        
    }

    PointLight::PointLight(float constant, float linear, float quadratic, const glm::vec3& position)
        : m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic), Lights(position)
    {
        
    }

    PointLight::PointLight(float constant, float linear, float quadratic)
        : m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic), Lights()
    {
        
    }

    PointLight::~PointLight() 
    {
        
    }    
}