#include "ObjectManager.h"

namespace Manager
{
    ObjectManager::ObjectManager() 
    {
    }

    ObjectManager::~ObjectManager() 
    {
    }

    uint ObjectManager::AddModel(const char* objectPath, const char* shaderPath, glm::mat4* modelMatrix) 
    {
        if(SearchModel(objectPath))
        {
            m_Objects[objectPath] = std::make_shared<Rendering::Model>(objectPath, textureManager, shaderManager.LoadShader(shaderPath));
        }
        m_Renderables.push_back({ objectPath, modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddModel(const char* objectPath, std::shared_ptr<Rendering::Shader> shader, glm::mat4* modelMatrix) 
    {
        if(SearchModel(objectPath))
        {
            m_Objects[objectPath] = std::make_shared<Rendering::Model>(objectPath, textureManager, shader);
        }
        m_Renderables.push_back({ objectPath, modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddQuad(glm::mat4* modelMatrix) 
    {
        if(SearchModel("Quad"))
        {
            m_Objects["Quad"] = std::make_shared<Rendering::Quad>();
        }
        m_Renderables.push_back({ "Quad", modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddQuad(const char* diffuse, const char* specular, const char* normal, glm::mat4* modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const char* diffuse, const char* specular, glm::mat4* modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const char* diffuse, glm::mat4* modelMatrix) 
    {
        
    }

    uint ObjectManager::AddQuad(const glm::vec4& color, glm::mat4* modelMatrix) 
    {
        if(SearchModel("Quad"))
        {
            m_Objects["Quad"] = std::make_shared<Rendering::Quad>(color);
        }
        m_Renderables.push_back({ "Quad", modelMatrix });
        return m_Renderables.size() - 1;
    }

    uint ObjectManager::AddCube(glm::mat4* modelMatrix) 
    {
        
    }

    void ObjectManager::Render() 
    {
        for(uint i = 0; i < m_Renderables.size(); i++)
        {
            m_Objects[m_Renderables[i].objectName]->Draw(*(m_Renderables[i].modelMatrix));
        }
    }

    bool ObjectManager::SearchModel(const char* objectPath) 
    {
        std::unordered_map<std::string, std::shared_ptr<Rendering::iRenderable>>::const_iterator got = m_Objects.find(objectPath);
        return got == m_Objects.end();
    }
}