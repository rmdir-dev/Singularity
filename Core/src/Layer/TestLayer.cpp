#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"

namespace Layer
{
    TestLayer::TestLayer() 
    {
        m_Vertices[0] = -0.5f;
        m_Vertices[1] = -0.5f;
        m_Vertices[2] = 0.0f;
        m_Vertices[3] = 0.5f;
        m_Vertices[4] = -0.5f;
        m_Vertices[5] = 0.0f;
        m_Vertices[6] = 0.0f;
        m_Vertices[7] = 0.5f;
        m_Vertices[8] = 0.0f;
        v1 = v2 = v3 = 0.5f;

        m_Shader = std::make_unique<Rendering::Shader>("Assets/simpleShader");
    }


    TestLayer::~TestLayer() 
    {
        
    }

    void TestLayer::OnStart() 
    {
        uint VBO;
        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
      
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender() 
    {
        m_Shader->Bind();
        m_Shader->SetUniform3f("color", v1, v2, v3);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
            v1 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
            v2 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
            v3 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
            return true;
        }     
    }
}
