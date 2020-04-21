#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Utils/Log.h"
#include "Utils/KeyCodes.h"

namespace Layer
{
    TestLayer::TestLayer() 
    {
        m_Shader = std::make_shared<Rendering::Shader>("Assets/3DShader");
        m_Texture = std::make_shared<Rendering::Texture>("Assets/wall.jpg");

        //CAMERA SETUP
        cameraPos       = glm::vec3(0.0f, 0.0f,  3.0f);
        cameraFront     = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp        = glm::vec3(0.0f, 1.0f,  0.0f);
        cameraSpeed = 0.05f;
        sensitivity = 0.1f;
        m_Yaw = -84.0f;
        m_Pitch = 0.0f;

        mvt.input = 0x00;

        UpdateView(); 

        m_Shader->Bind();
        //Set the texture to the good active texture slot
        m_Shader->SetUniform1i("texture0", 0);        

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down      
        projection = glm::perspective(glm::radians(45.0f), 1900.0f / 1000.0f, 0.1f, 250.0f);

        m_Shader->SetUniformMatrix4fv("model", model);
        m_Shader->SetUniformMatrix4fv("projection", projection);

        m_Shader->Unbind();         

        rotation = 0.0f;
    }


    TestLayer::~TestLayer() 
    {
        
    }

    void TestLayer::OnStart() 
    {
        //m_Mesh = std::make_unique<Rendering::Mesh>(m_Vertices, m_Indices, m_Texture, m_Shader);
        m_Model = std::make_unique<Rendering::Model>("Assets/Nano/nanosuit.obj", m_Shader);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender(const float& deltaTime) 
    {
        UpdateMouvement(deltaTime);
        m_Shader->Bind();
        m_Texture->Bind();
        model = glm::rotate(model, (0.5f * deltaTime) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));  
        m_Shader->SetUniformMatrix4fv("model", model);

        //m_Mesh->Draw();
        m_Model->Draw();
        //glBindVertexArray(VAO);
        ////!!! REPLACE INDICE_NBR by indices.size() later!!!
        //glDrawElements(GL_TRIANGLES, INIDICE_NBR, GL_UNSIGNED_INT, 0);
        m_Shader->Unbind();

    }

    void TestLayer::UpdateView() 
    {
        m_Shader->Bind();
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        m_Shader->SetUniformMatrix4fv("view", view);
        m_Shader->Unbind();
    }

    void TestLayer::UpdateMouvement(const float& deltaTime) 
    {
        cameraSpeed = 2.5f * deltaTime;
        if(mvt.bits.w)
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if(mvt.bits.s)
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if(mvt.bits.a)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(mvt.bits.d)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(mvt.bits.q)
        {
            cameraPos -= cameraSpeed * cameraUp;
        }
        if(mvt.bits.e)
        {
            cameraPos += cameraSpeed * cameraUp;
        }
        UpdateView();
    }

    void TestLayer::OnEvent(Event::Event& e) 
    {
        Event::Dispatcher dispatcher(e);
	    dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(TestLayer::KeyPressEvent));
	    dispatcher.dispatch<Event::KeyReleased>(BIND_EVENT_FCT(TestLayer::KeyReleasedEvent));
	    dispatcher.dispatch<Event::MouseMoved>(BIND_EVENT_FCT(TestLayer::MouseMovedEvent));
	    dispatcher.dispatch<Event::WindowResize>(BIND_EVENT_FCT(TestLayer::WindowResizeEvent));
    }

    bool TestLayer::KeyPressEvent(Event::KeyPressed& e) 
    {
        switch (e.getKeyCode())
        {
        case SE_KEY_W:
            mvt.bits.w = 1;
            break;
        
        case SE_KEY_S:
            mvt.bits.s = 1;
            break;

        case SE_KEY_A:
            mvt.bits.a = 1;
            break;

        case SE_KEY_D:
            mvt.bits.d = 1;
            break;

        case SE_KEY_Q:
            mvt.bits.q = 1;
            break;

        case SE_KEY_E:
            mvt.bits.e = 1;
            break;

        default:
            break;
        }
    }

    bool TestLayer::KeyReleasedEvent(Event::KeyReleased& e) 
    {
        switch (e.getKeyCode())
        {
        case SE_KEY_W:
            mvt.bits.w = 0;
            break;
        
        case SE_KEY_S:
            mvt.bits.s = 0;
            break;

        case SE_KEY_A:
            mvt.bits.a = 0;
            break;

        case SE_KEY_D:
            mvt.bits.d = 0;
            break;

        case SE_KEY_Q:
            mvt.bits.q = 0;
            break;

        case SE_KEY_E:
            mvt.bits.e = 0;
            break;

        default:
            break;
        }
    }

    bool TestLayer::MouseMovedEvent(Event::MouseMoved& e) 
    {
        m_Yaw += e.GetMousePosition().x * sensitivity;
        m_Pitch -= e.GetMousePosition().y * sensitivity;

        if(m_Pitch > 89.0f)
            m_Pitch =  89.0f;
        if(m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        cameraFront = glm::normalize(direction);
    }

    bool TestLayer::WindowResizeEvent(Event::WindowResize& e) 
    {
        WindowSize size = e.GetWindowSize();
        m_Shader->Bind();
        projection = glm::perspective(glm::radians(45.0f), size.width / size.height, 0.1f, 250.0f);
        m_Shader->SetUniformMatrix4fv("projection", projection);
        m_Shader->Unbind();
    }
}
