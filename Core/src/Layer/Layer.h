#pragma once
#include "Utils/Event/Events.h"
#include "Rendering/Rendering.h"
#include "Managers/ObjectManager.h"

namespace Layer 
{
    struct Object
    {
        uint index;
        std::shared_ptr<Rendering::Shader> shader;
        glm::mat4 model;
    };

    class Layer
    {
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Functions
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        virtual ~Layer() {}

        /*
        Execute to start the layer.
        */
        virtual void OnStart() = 0;
        /*
        Execute to shutdown the layer.
        */
        virtual void OnShutDown() = 0;

        /*
        Execute to render the layer.
        */
        virtual void OnRender(const float& deltaTime) = 0;

        /*
        Execute to send an event to the layer.
        */
        virtual void OnEvent(Event::Event& e) = 0;

        /*
        Execute on ImGUI layer 
        */
        virtual void OnImGUIRender() = 0;

    private:

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Variables
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    protected:
        std::shared_ptr<Manager::ShaderManager> m_ShaderManager;
    };
}