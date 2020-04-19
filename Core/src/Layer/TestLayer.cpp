#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>

namespace Layer
{
    TestLayer::TestLayer() 
    {
                                //POSITIONS                     COLOR                               UVs
        m_Vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.0f) ,   glm::vec4(0.7f, 0.2f, 0.1f, 1.0f),  glm::vec2(0.0f, 0.0f)});
        m_Vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.0f)  ,   glm::vec4(0.4f, 0.7f, 0.8f, 1.0f),  glm::vec2(1.0f, 0.0f)});
        m_Vertices.push_back({glm::vec3(0.5f, -0.5f, 0.0f)  ,   glm::vec4(0.3f, 0.4f, 0.7f, 1.0f),  glm::vec2(0.0f, 1.0f)});
        m_Vertices.push_back({glm::vec3(0.5f, 0.5f, 0.0f)   ,   glm::vec4(0.1f, 0.8f, 0.5f, 1.0f),  glm::vec2(1.0f, 1.0f)});

        //INDICES
        m_Indices[0] = 0;
        m_Indices[1] = 1;
        m_Indices[2] = 2;
        m_Indices[3] = 3;
        m_Indices[4] = 1;
        m_Indices[5] = 2;
        

        m_Shader = std::make_unique<Rendering::Shader>("Assets/simpleShader");
        m_Texture = std::make_unique<Rendering::Texture>("Assets/wall.jpg");
        m_Texture2 = std::make_unique<Rendering::Texture>("Assets/chalet.jpg", 1);
        m_Shader->Bind();
        //Set the texture to the good active texture slot
        m_Shader->SetUniform1i("texture0", 0);
        m_Shader->SetUniform1i("texture1", 1);
        m_Shader->Unbind();
    }


    TestLayer::~TestLayer() 
    {
        
    }

    void TestLayer::OnStart() 
    {
        //ALL THIS CODE WILL BE COMMENTED LATER ON THEIR DEFINITIVE CLASS
        uint VBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);      

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO); 

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Rendering::VertexLayout) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6, &m_Indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::color)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::UVs)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender() 
    {
        m_Shader->Bind();
        m_Texture->Bind();
        m_Texture2->Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        m_Shader->Unbind();
    }

    void TestLayer::OnEvent(Event::Event& e) 
    {
        Event::Dispatcher dispatcher(e);
	    dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(TestLayer::keyPressEvent));
    }


    bool TestLayer::keyPressEvent(Event::KeyPressed& e) 
    {
        if(e.getKeyCode() == 24)
        {
            return true;
        }     
    }
}
