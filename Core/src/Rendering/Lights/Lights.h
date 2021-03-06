#pragma once

#include <glm/glm.hpp>
#include "Utils/pch.h"
#include "Rendering/Shaders/Shader.h"

//LIGHT TYPES
#define OMNI_LIGHT          0x01
#define DIRECTIONAL_LIGHT   0x02
#define SPOT_LIGHT          0x04
#define AERA_LIGHT          0x08
#define VOLUME_LIGHT        0x10
#define AMBIANT_LIGHT       0x20

//LIGHT SETTINGS
#define ACTIVATE_LIGHT      0x01 // 0000 0001
#define VISIBLE_LIGHT_BOX   0x02 // 0000 0010
//Must active BOTH visible and wireframe
#define WIRE_FRAME_BOX      0x06 // 0000 0110

namespace Rendering
{
    union LightTypes 
    {
        byte Types;
        struct 
        {
            byte omni           : 1; // 0000 0001
            byte directional    : 1; // 0000 0010
            byte spot           : 1; // 0000 0100
            byte aera           : 1; // 0000 1000
            byte volume         : 1; // 0001 0000
            byte ambiant        : 1; // 0010 0000
        } lights;
    };

    union LightSettings 
    {
        byte Settings;
        struct
        {
            byte active         : 1; // 0000 0001
            byte visible        : 1; // 0000 0010
            byte wireframe      : 1; // 0000 0100
        }lights;
    };

    class Lights
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Lights();
        Lights(const glm::vec3& position);
        Lights(float intensity);
        Lights(float intensity, const glm::vec3& color);
        Lights(const glm::vec3& position, float intensity);
        Lights(const glm::vec3& position, const glm::vec3& color);
        Lights(const glm::vec3& position, const glm::vec3& color, float intensity);
        virtual ~Lights();

        void SetLightSettings(byte settings);
        void SetLightType(byte types);

        void SetShader(const std::shared_ptr<Shader> shader);

        /**/
        void SetAmbiant();
        void SetAmbiant(const float intensity);
        /**/
        void SetSpecular();
        void SetSpecular(const float intensity);
        /**/
        void SetDiffuse();
        void SetDiffuse(const float intensity);

        /*
        return if the light is on or off.
        */
        uint GetOnOrOff();

        void Draw();

        void Translate(const glm::vec3& translation);

    protected:
        void SetupLightBox();

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        glm::vec3 m_Position;
        glm::vec3 m_Color;
        float m_Intensity;
        float m_AmbiantIntensity    = 0.1f;
        float m_DiffuseIntensity    = 0.5f;
        float m_SpecularIntensity   = 1.0f;
        glm::vec3 m_Ambiant;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;

    protected:
        LightSettings m_Settings;
        LightTypes m_Type;

        uint VAO;

        std::shared_ptr<Shader> m_Shader;

        //TEST Model matrix
        glm::mat4 m_Model;

    };
}