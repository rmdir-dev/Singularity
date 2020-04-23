#pragma once

#include "Layer.h"
#include "Rendering/Rendering.h"

#define INIDICE_NBR 36

namespace Layer 
{
    union MouvementInput
    {
        byte input;
        struct
        {
            byte w      : 1;  // 0x01
            byte a      : 1;  // 0x02
            byte s      : 1;  // 0x04
            byte d      : 1;  // 0x08
            byte q      : 1;  // 0x10
            byte e      : 1;  // 0x20
        }bits;
    };        
    

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
        void OnStart() override;

        /*
        Execute to shutdown the layer.
        */
        void OnShutDown() override;

        /*
        Execute to render the layer.
        */
        void OnRender(const float& deltaTime) override;

        /*
        Execute to send an event to the layer.
        */
        void OnEvent(Event::Event& e) override;

        /*
        Execute on ImGUI layer 
        */
        void OnImGUIRender() override;

    private:
        void UpdateView();

        void UpdateMouvement(const float& deltaTime);

        //EVENT MANAGEMENT
        /*
        Execute when a key event is recieved.
        */
        bool KeyPressEvent(Event::KeyPressed& e);

        /*
        Execute when a key is released.
        */
        bool KeyReleasedEvent(Event::KeyReleased& e);

        /*
        Execute when the mouse is moved.
        */
        bool MouseMovedEvent(Event::MouseMoved& e);

        /*
        Execute when the window or framebuffer is resize.
        */
        bool WindowResizeEvent(Event::WindowResize& e);
        

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Variables
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        //Test vertices
        std::vector<Rendering::VertexLayout> m_Vertices;

        //Test Mesh
        std::unique_ptr<Rendering::Mesh> m_Mesh;
        //Test Model
        std::unique_ptr<Rendering::Model> m_Model;

        //Test indices
        std::vector<uint> m_Indices;

        //Test shader.
        std::shared_ptr<Rendering::Shader> m_Shader;
        std::shared_ptr<Rendering::Shader> m_LightShader;

        //Test Texture
        std::shared_ptr<Rendering::Texture> m_Texture;

        //Test Light
        std::shared_ptr<Rendering::Lights> m_Light;

        //TEST MVP matrix
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        //TEST Camera
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        float cameraSpeed;
        MouvementInput mvt;

        float m_Yaw;
        float m_Pitch;
        float sensitivity;

        //Rotation base
        float rotation;

        //Test Vertex Array
        uint VAO, IBO;

    public:
    };
}