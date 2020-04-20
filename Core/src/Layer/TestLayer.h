#pragma once

#include "Layer.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Buffers/VertexLayout.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Models/Mesh.h"

#define INIDICE_NBR 36

namespace Layer 
{
    class TestLayer : public Layer
    {
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Functions
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        TestLayer();
        ~TestLayer();

        /*
        Execute to start the layer.
        */
        void OnStart();
        /*
        Execute to shutdown the layer.
        */
        void OnShutDown();

        /*
        Execute to render the layer.
        */
        void OnRender();
        /*
        Execute to send an event to the layer.
        */
        void OnEvent(Event::Event& e);

    private:
        //EVENT MANAGEMENT
        /*
        Execute when a key event is recieved.
        */
        bool keyPressEvent(Event::KeyPressed& e);
        

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Variables
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        //Test vertices
        std::vector<Rendering::VertexLayout> m_Vertices;

        //Test Mesh
        std::unique_ptr<Rendering::Mesh> m_Mesh;

        //Test indices
        std::vector<uint> m_Indices;

        //Test shader.
        std::shared_ptr<Rendering::Shader> m_Shader;

        //Test Texture
        std::shared_ptr<Rendering::Texture> m_Texture;

        //TEST MVP matrix
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        //Rotation base
        float rotation;

        //Test Vertex Array
        uint VAO, IBO;

    public:
    };
}