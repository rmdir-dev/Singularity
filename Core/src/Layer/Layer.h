#pragma once
#include "Utils/Event/Events.h"

namespace Layer 
{
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
        virtual void OnRender() = 0;
        /*
        Execute to send an event to the layer.
        */
        virtual void OnEvent(Event::Event& e) = 0;

    private:

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Variables
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
    public:
    };
}