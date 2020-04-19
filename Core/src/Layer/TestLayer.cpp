#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

namespace Layer
{
    TestLayer::TestLayer() 
    {
                                //POSITIONS                     COLOR                               UVs
        m_Vertices.push_back({glm::vec3(-1.0f, -1.0f,  1.0f) ,   glm::vec4(0.7f, 0.2f, 0.1f, 1.0f),  glm::vec2(0.0f, 0.0f)});   //0
        m_Vertices.push_back({glm::vec3( 1.0f, -1.0f,  1.0f)  ,   glm::vec4(0.4f, 0.7f, 0.8f, 1.0f),  glm::vec2(0.0f, 1.0f)});  //1
        m_Vertices.push_back({glm::vec3(-1.0f,  1.0f,  1.0f)  ,   glm::vec4(0.3f, 0.4f, 0.7f, 1.0f),  glm::vec2(1.0f, 0.0f)});  //2
        m_Vertices.push_back({glm::vec3( 1.0f,  1.0f,  1.0f)   ,   glm::vec4(0.1f, 0.8f, 0.5f, 1.0f),  glm::vec2(1.0f, 1.0f)}); //3
        m_Vertices.push_back({glm::vec3( 1.0f,  1.0f, -1.0f) ,   glm::vec4(0.7f, 0.2f, 0.1f, 1.0f),  glm::vec2(1.0f, 0.0f)});   //4
        m_Vertices.push_back({glm::vec3(-1.0f,  1.0f, -1.0f)  ,   glm::vec4(0.4f, 0.7f, 0.8f, 1.0f),  glm::vec2(1.0f, 1.0f)});  //5
        m_Vertices.push_back({glm::vec3(-1.0f, -1.0f, -1.0f)  ,   glm::vec4(0.3f, 0.4f, 0.7f, 1.0f),  glm::vec2(0.0f, 1.0f)});  //6
        m_Vertices.push_back({glm::vec3( 1.0f, -1.0f, -1.0f)   ,   glm::vec4(0.1f, 0.8f, 0.5f, 1.0f),  glm::vec2(0.0f, 0.0f)}); //7

        //INDICES
        m_Indices[0] =  0;
        m_Indices[1] =  1;
        m_Indices[2] =  2;

        m_Indices[3] =  3;
        m_Indices[4] =  1;
        m_Indices[5] =  2;

        m_Indices[6] =  2;
        m_Indices[7] =  3;
        m_Indices[8] =  5;

        m_Indices[9] =  5;
        m_Indices[10] = 4;
        m_Indices[11] = 3;

        m_Indices[12] = 1;
        m_Indices[13] = 3;
        m_Indices[14] = 4;

        m_Indices[15] = 4;
        m_Indices[16] = 7;
        m_Indices[17] = 1;

        m_Indices[18] = 5;
        m_Indices[19] = 4; 
        m_Indices[20] = 7;

        m_Indices[21] = 5;
        m_Indices[22] = 6;
        m_Indices[23] = 7;

        m_Indices[24] = 5;
        m_Indices[25] = 2;
        m_Indices[26] = 0;

        m_Indices[27] = 5;
        m_Indices[28] = 6;
        m_Indices[29] = 0; 

        m_Indices[30] = 0;
        m_Indices[31] = 6;
        m_Indices[32] = 1;

        m_Indices[33] = 6;
        m_Indices[34] = 1;
        m_Indices[35] = 7;       

        m_Shader = std::make_unique<Rendering::Shader>("Assets/3DShader");
        m_Texture = std::make_unique<Rendering::Texture>("Assets/wall.jpg");

        m_Shader->Bind();
        //Set the texture to the good active texture slot
        m_Shader->SetUniform1i("texture0", 0);
        

        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); 
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 250.0f);
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
        //ALL THIS CODE WILL BE COMMENTED LATER ON THEIR DEFINITIVE CLASS
        uint VBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);      

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO); 

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Rendering::VertexLayout) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * INIDICE_NBR, &m_Indices[0], GL_STATIC_DRAW);

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
        model = glm::rotate(model, (0.01f) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        m_Shader->SetUniformMatrix4fv("model", model);

        glBindVertexArray(VAO);
        //!!! REPLACE INDICE_NBR by indices.size() later!!!
        glDrawElements(GL_TRIANGLES, INIDICE_NBR, GL_UNSIGNED_INT, 0);
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
