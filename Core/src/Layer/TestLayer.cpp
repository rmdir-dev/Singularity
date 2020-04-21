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

        UpdateView(); 

        m_Shader->Bind();
        //Set the texture to the good active texture slot
        m_Shader->SetUniform1i("texture0", 0);        

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down      
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 250.0f);

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
        m_Mesh = std::make_unique<Rendering::Mesh>(m_Vertices, m_Indices, m_Texture, m_Shader);
        m_Model = std::make_unique<Rendering::Model>("Assets/Nano/nanosuit.obj", m_Shader);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender() 
    {
        UpdateMouvement();
        m_Shader->Bind();
        m_Texture->Bind();
        model = glm::rotate(model, (0.05f) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));  
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

    void TestLayer::UpdateMouvement() 
    {
        if(mvt.w)
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if(mvt.s)
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if(mvt.a)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(mvt.d)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        UpdateView();
    }

    void TestLayer::OnEvent(Event::Event& e) 
    {
        Event::Dispatcher dispatcher(e);
	    dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(TestLayer::KeyPressEvent));
	    dispatcher.dispatch<Event::KeyReleased>(BIND_EVENT_FCT(TestLayer::KeyReleasedEvent));
	    dispatcher.dispatch<Event::WindowResize>(BIND_EVENT_FCT(TestLayer::WindowResizeEvent));
    }

    bool TestLayer::KeyPressEvent(Event::KeyPressed& e) 
    {
        switch (e.getKeyCode())
        {
        case SE_KEY_W:
            mvt.w = 1;
            break;
        
        case SE_KEY_S:
            mvt.s = 1;
            break;

        case SE_KEY_A:
            mvt.a = 1;
            break;

        case SE_KEY_D:
            mvt.d = 1;
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
            mvt.w = 0;
            break;
        
        case SE_KEY_S:
            mvt.s = 0;
            break;

        case SE_KEY_A:
            mvt.a = 0;
            break;

        case SE_KEY_D:
            mvt.d = 0;
            break;

        default:
            break;
        }
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
