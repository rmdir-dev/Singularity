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
        m_Indices.push_back(0);
        m_Indices.push_back(1);
        m_Indices.push_back(2);
        m_Indices.push_back(3);
        m_Indices.push_back(1);
        m_Indices.push_back(2);
        m_Indices.push_back(2);
        m_Indices.push_back(3);
        m_Indices.push_back(5);
        m_Indices.push_back(5);
        m_Indices.push_back(4);
        m_Indices.push_back(3);
        m_Indices.push_back(1);
        m_Indices.push_back(3);
        m_Indices.push_back(4);
        m_Indices.push_back(4);
        m_Indices.push_back(7);
        m_Indices.push_back(1);
        m_Indices.push_back(5);
        m_Indices.push_back(4); 
        m_Indices.push_back(7);
        m_Indices.push_back(5);
        m_Indices.push_back(6);
        m_Indices.push_back(7);
        m_Indices.push_back(5);
        m_Indices.push_back(2);
        m_Indices.push_back(0);
        m_Indices.push_back(5);
        m_Indices.push_back(6);
        m_Indices.push_back(0); 
        m_Indices.push_back(0);
        m_Indices.push_back(6);
        m_Indices.push_back(1);
        m_Indices.push_back(6);
        m_Indices.push_back(1);
        m_Indices.push_back(7);       

        m_Shader = std::make_shared<Rendering::Shader>("Assets/3DShader");
        m_Texture = std::make_shared<Rendering::Texture>("Assets/wall.jpg");

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
        m_Mesh = std::make_unique<Rendering::Mesh>(m_Vertices, m_Indices, m_Texture, m_Shader);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender() 
    {
        m_Shader->Bind();
        m_Texture->Bind();
        model = glm::rotate(model, (0.0003f) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        m_Shader->SetUniformMatrix4fv("model", model);

        m_Mesh->Draw();
        //glBindVertexArray(VAO);
        ////!!! REPLACE INDICE_NBR by indices.size() later!!!
        //glDrawElements(GL_TRIANGLES, INIDICE_NBR, GL_UNSIGNED_INT, 0);
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
