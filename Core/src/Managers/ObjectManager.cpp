#include "ObjectManager.h"

namespace Manager
{
    ObjectManager::ObjectManager() 
    {
        
    }

    ObjectManager::~ObjectManager() 
    {
        
    }

    uint ObjectManager::AddModel(const char* objectPath, const glm::mat4& modelMatrix) 
    {
        std::unordered_map<std::string, std::unique_ptr<Rendering::iRenderable>>::const_iterator got = m_Objects.find(objectPath);
        if(got == m_Objects.end())
        {
            m_Objects[objectPath] = std::make_unique<Rendering::Model>(objectPath, textureManager, shaderManager);
        }
        m_Renderables.push_back({ objectPath, modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddModel(const char* objectPath, const char* shaderPath, const glm::mat4& modelMatrix) 
    {
        std::unordered_map<std::string, std::unique_ptr<Rendering::iRenderable>>::const_iterator got = m_Objects.find(objectPath);
        if(got == m_Objects.end())
        {
            m_Objects[objectPath] = std::make_unique<Rendering::Model>(objectPath, shaderManager.LoadShader(shaderPath));
        }
        m_Renderables.push_back({ objectPath, modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddQuad(const glm::mat4& modelMatrix) 
    {
        std::unordered_map<std::string, std::unique_ptr<Rendering::iRenderable>>::const_iterator got = m_Objects.find("Quad");
        if(got == m_Objects.end())
        {
            m_Objects["Quad"] = std::make_unique<Rendering::Model>("Quad", textureManager, shaderManager);
        }
        m_Renderables.push_back({ "Quad", modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddQuad(const char* diffuse, const char* specular, const char* normal, const glm::mat4& modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const char* diffuse, const char* specular, const glm::mat4& modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const char* diffuse, const glm::mat4& modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const glm::vec4& color, const glm::mat4& modelMatrix) 
    {
        std::unordered_map<std::string, std::unique_ptr<Rendering::iRenderable>>::const_iterator got = m_Objects.find("Quad");
        if(got == m_Objects.end())
        {
            m_Objects["Quad"] = std::make_unique<Rendering::Quad>(color);
        }
        m_Renderables.push_back({ "Quad", modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddCube(const glm::mat4& modelMatrix) 
    {
        
    }

    void ObjectManager::Render() 
    {
        
    }
}