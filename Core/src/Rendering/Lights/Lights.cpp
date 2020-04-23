#include "Lights.h"
#include "glad/glad.h"
#include "Utils/Log.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Rendering
{
    Lights::Lights(const glm::vec3& position)
        : m_Position(position), m_Color(glm::vec3(1.0f)), m_Intensity(1.0f)
    {
        SetupLightBox();
    }

    Lights::Lights(const glm::vec3& position, const glm::vec3& color, float intensity)
        : m_Position(position), m_Color(color), m_Intensity(intensity)
    {
        SetupLightBox();
    }

    Lights::Lights(const glm::vec3& position, const glm::vec3& color) 
        : m_Position(position), m_Color(color), m_Intensity(1.0f)
    {
        SetupLightBox();
    }

    Lights::Lights(const glm::vec3& position, float intensity) 
        : m_Position(position), m_Color(glm::vec3(1.0f)), m_Intensity(intensity)
    {
        SetupLightBox();
    }

    Lights::~Lights() 
    {
        
    }

    void Lights::SetLightSettings(byte settings) 
    {
        m_Settings.Settings = settings;
    }


    void Lights::SetLightType(byte types) 
    {
        m_Type.Types = types;
    }

    void Lights::SetShader(const std::shared_ptr<Shader> shader) 
    {
        m_Shader = shader;
    }

    void Lights::Draw() 
    {
        if(m_Settings.Settings & VISIBLE_LIGHT_BOX)
        {
            if(!m_Shader)
            {
                CORE_ERROR("Light rendering not possible, NO SHADER SET!");
                return;
            }
            m_Shader->Bind();
            m_Shader->SetUniformMatrix4fv("model", m_Model);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            m_Shader->Unbind();
        }
    }

    void Lights::SetupLightBox() 
    {
        //TODO Add Object Manager to manage the loading/unloading of different object.
        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f, -0.5f,  0.5f, 
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f, -0.5f,  0.5f, 

            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f, -0.5f, 
            -0.5f, -0.5f,  0.5f, 
            -0.5f,  0.5f,  0.5f, 

            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  

            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f,  0.5f, 
            -0.5f, -0.5f, -0.5f, 

            -0.5f,  0.5f, -0.5f, 
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f, 
            -0.5f,  0.5f, -0.5f, 
        };

        uint VBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);

        // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        m_Model = glm::mat4(1.0f);
        m_Model = glm::translate(m_Model, m_Position);
        m_Model = glm::scale(m_Model, glm::vec3(0.2f));
    }
}