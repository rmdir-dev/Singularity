#include "Model.h"
#include "Utils/Log.h"


namespace Rendering
{
    Model::Model(const char* filePath, std::shared_ptr<Shader> Shader) 
        : m_Path(filePath), m_Shader(Shader)
    {
        CORE_INFO("Loading model: ", filePath);
        Load();
    }

    Model::~Model() 
    {
        
    }

    void Model::Draw() 
    {
        for(uint i = 0; i < m_Meshes.size(); i++)
        {
            m_Meshes[i].Draw();
        }
    }

    void Model::Load() 
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            CORE_ERROR("ASSIMP: ", importer.GetErrorString());
            return;
        }
        ProcessNode(scene->mRootNode, scene);
        CORE_INFO("Model loaded.");
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene) 
    {
        for(uint i  = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }
        for(uint i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) 
    {
        std::vector<VertexLayout> vertices;
        std::vector<uint> indices;
        std::shared_ptr<Rendering::Texture> Textures;

        vertices.resize(mesh->mNumVertices);

        for(uint i = 0; i < mesh->mNumVertices; i++)
        {
            VertexLayout vertex;

            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;

            vertex.position = vector;

            if(mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;

                vertex.normals = vector;
            }

            if(mesh->HasTextureCoords(0))
            {
                glm::vec2 uvs;
                uvs.x = mesh->mTextureCoords[0][i].x;
                uvs.y = mesh->mTextureCoords[0][i].y;

                vertex.UVs = uvs;
            } else
            {
                vertex.UVs = glm::vec2(0.0f);
            }

            vertices[i] = vertex;
        }

        for(uint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(uint j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (scene->mNumMaterials > 0)
        {
            std::string path = m_Path.substr(0, m_Path.find_last_of('/'));
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            aiString strDiff;
             if (material->GetTexture(aiTextureType_DIFFUSE, 0, &strDiff, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                if (strDiff.C_Str() != "")
                {
                    path = path + '/' + strDiff.C_Str();
                    Textures = std::make_shared<Texture>(path.c_str());
                }
             }
        }

        return Mesh(vertices, indices, Textures, m_Shader);
    }
}

