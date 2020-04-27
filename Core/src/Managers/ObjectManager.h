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
        ObjectManager() {}
        ObjectManager(std::shared_ptr<ShaderManager> shaderManager);
        ~ObjectManager();
        
        uint AddModel(const char* objectPath, const char* shaderPath, glm::mat4* modelMatrix);
        uint AddModel(const char* objectPath, std::shared_ptr<Rendering::Shader> shader, glm::mat4* modelMatrix);

        uint AddQuad(glm::mat4* modelMatrix);
        uint AddQuad(const Material& material, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddQuad(const glm::vec4& color, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddQuad(const char* diffuse, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddQuad(const char* diffuse, const char* specular, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddQuad(const char* diffuse, const char* specular, const char* normal, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);

        uint AddCube(glm::mat4* modelMatrix);
        uint AddCube(const Material& material, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddCube(const glm::vec4& color, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddCube(const char* diffuse, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddCube(const char* diffuse, const char* specular, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);
        uint AddCube(const char* diffuse, const char* specular, const char* normal, glm::mat4* modelMatrix, std::shared_ptr<Rendering::Shader> shader);

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
        
        std::shared_ptr<ShaderManager> m_ShaderManager;
        TextureManager m_TextureManager;
        
    };
}