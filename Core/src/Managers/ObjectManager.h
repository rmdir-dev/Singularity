#pragma once

#include "glm/glm.hpp"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Rendering/Rendering.h"

namespace Manager
{
    struct Renderable
    {
        std::string objectName;
        glm::mat4 modelMatrix;
    };

    class ObjectManager
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        ObjectManager();
        ~ObjectManager();

        uint AddModel(const char* objectPath, const glm::mat4& modelMatrix);
        uint AddModel(const char* objectPath, const char* shaderPath, const glm::mat4& modelMatrix);

        uint AddQuad(const glm::mat4& modelMatrix);
        uint AddQuad(const glm::vec4& color, const glm::mat4& modelMatrix);
        uint AddQuad(const char* diffuse, const glm::mat4& modelMatrix);
        uint AddQuad(const char* diffuse, const char* specular, const glm::mat4& modelMatrix);
        uint AddQuad(const char* diffuse, const char* specular, const char* normal, const glm::mat4& modelMatrix);

        uint AddCube(const glm::mat4& modelMatrix);

        void Render();

    private:

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        std::unordered_map<std::string, std::unique_ptr<Rendering::iRenderable>> m_Objects;
        std::vector<Renderable> m_Renderables;
        
        ShaderManager shaderManager;
        TextureManager textureManager;
        
    };
}