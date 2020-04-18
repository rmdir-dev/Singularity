#pragma once

#include "Layer.h"
#include "Rendering/Shaders/Shader.h"

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
        float m_Vertices[9];
        //Test shader.
        std::unique_ptr<Rendering::Shader> m_Shader;
        //Test Vertex Array
        uint VAO;
        //Test color float
        float v1, v2, v3;

    public:
    };
}