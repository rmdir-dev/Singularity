#pragma once

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Managers/TextureManager.h"
#include "Managers/ShaderManager.h"

namespace Rendering
{
    class Model : public iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Model(const char* filePath, std::shared_ptr<Shader> Shader);
        Model(const char* filePath, Manager::TextureManager& textureManager, Manager::ShaderManager& shaderManager);
        ~Model();

        void Draw() override;
        void Draw(const glm::mat4& modelMatrix) override;

    private:
        void Load();
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

        void SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) override {}

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        std::string m_Path;
        std::string m_Dir;

        std::vector<std::unique_ptr<Mesh>> m_Meshes;

        glm::mat4 m_Model;

        std::shared_ptr<Shader> m_Shader;

        //Temporary !!! later this will ONLY use Managers
        bool b_UseManager;
    };
}