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
        glm::mat4* modelMatrix;
    };

    class ObjectManager
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        ObjectManager();
        ~ObjectManager();
        
        uint AddModel(const char* objectPath, const char* shaderPath, glm::mat4* modelMatrix);
        uint AddModel(const char* objectPath, std::shared_ptr<Rendering::Shader> shader, glm::mat4* modelMatrix);

        uint AddQuad(glm::mat4* modelMatrix);
        uint AddQuad(const glm::vec4& color, glm::mat4* modelMatrix);
        uint AddQuad(const char* diffuse, glm::mat4* modelMatrix);
        uint AddQuad(const char* diffuse, const char* specular, glm::mat4* modelMatrix);
        uint AddQuad(const char* diffuse, const char* specular, const char* normal, glm::mat4* modelMatrix);

        uint AddCube(glm::mat4* modelMatrix);

        void SetView(const glm::mat4& view);
        void SetProjection(const glm::mat4& projection);

        void Render();

    private:
        bool SearchModel(const char* objectPath);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        std::unordered_map<std::string, std::shared_ptr<Rendering::iRenderable>> m_Objects;
        std::vector<Renderable> m_Renderables;
        
        ShaderManager shaderManager;
        TextureManager textureManager;
        
    };
}