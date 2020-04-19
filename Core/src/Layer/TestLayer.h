#pragma once

#include "Layer.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Buffers/VertexLayout.h"

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

        //Test indices
        uint m_Indices[6];

        //Test shader.
        std::unique_ptr<Rendering::Shader> m_Shader;
        //Test Vertex Array
        uint VAO, IBO;

    public:
    };
}