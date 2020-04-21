#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Utils/Log.h"

namespace Layer
{
    TestLayer::TestLayer() 
    {
        m_Shader = std::make_shared<Rendering::Shader>("Assets/3DShader");
        m_Texture = std::make_shared<Rendering::Texture>("Assets/wall.jpg");

        m_Shader->Bind();
        //Set the texture to the good active texture slot
        m_Shader->SetUniform1i("texture0", 0);        

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); 
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 250.0f);
        m_Shader->SetUniformMatrix4fv("model", model);
        m_Shader->SetUniformMatrix4fv("projection", projection);
        m_Shader->SetUniformMatrix4fv("view", view);

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
        m_Shader->Bind();
        m_Texture->Bind();
        model = glm::rotate(model, (0.0003f) * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));  
        m_Shader->SetUniformMatrix4fv("model", model);

        //m_Mesh->Draw();
        m_Model->Draw();
        //glBindVertexArray(VAO);
        ////!!! REPLACE INDICE_NBR by indices.size() later!!!
        //glDrawElements(GL_TRIANGLES, INIDICE_NBR, GL_UNSIGNED_INT, 0);
        m_Shader->Unbind();

    }

    void TestLayer::OnEvent(Event::Event& e) 
    {
        Event::Dispatcher dispatcher(e);
	    dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(TestLayer::KeyPressEvent));
	    dispatcher.dispatch<Event::WindowResize>(BIND_EVENT_FCT(TestLayer::WindowResizeEvent));
    }

    bool TestLayer::KeyPressEvent(Event::KeyPressed& e) 
    {
        if(e.getKeyCode() == 24)
        {
            return true;
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
