#pragma once

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Rendering
{
    class Model
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Model(const char* filePath, std::shared_ptr<Shader> Shader);
        ~Model();

        void Draw();

    private:
        void Load();
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        std::string m_Path;
        std::string m_Dir;

        std::vector<Mesh> m_Meshes;

        glm::mat4 m_Model;

        std::shared_ptr<Shader> m_Shader;
    };
}