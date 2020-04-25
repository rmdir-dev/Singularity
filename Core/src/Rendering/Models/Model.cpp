#include "Model.h"
#include "Utils/Log.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Rendering
{
    Model::Model(const char* filePath, std::shared_ptr<Shader> Shader) 
        : m_Path(filePath), m_Shader(Shader)
    {
        b_UseManager = false;
        CORE_INFO("Loading model: ", filePath);
        Load();
    }

    Model::Model(const char* filePath, Manager::TextureManager& textureManager, Manager::ShaderManager& shaderManager) 
        : m_Path(filePath), iRenderable(textureManager, shaderManager)
    {
        CORE_INFO("Loading model: ", filePath);
        b_UseManager = true; 
        Load();
    }

    Model::~Model() 
    {
        
    }

    void Model::Draw() 
    {
        for(uint i = 0; i < m_Meshes.size(); i++)
        {
            m_Meshes[i]->Draw();
        }
    }

    void Model::Draw(const glm::mat4& modelMatrix) 
    {
        for(uint i = 0; i < m_Meshes.size(); i++)
        {
            m_Meshes[i]->Draw(modelMatrix);
        }
    }

    void Model::Load() 
    {
        m_Dir = m_Path.substr(0, m_Path.find_last_of('/'));
        m_Dir = m_Dir + '/';

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

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

    std::unique_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) 
    {
        std::vector<VertexLayout> vertices;
        std::vector<uint> indices;
        std::shared_ptr<Rendering::Texture> Diffuse;
        std::shared_ptr<Rendering::Texture> Specular;
        std::shared_ptr<Rendering::Texture> Normal;

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
            
            if(mesh->HasTangentsAndBitangents())
            {
                glm::vec3 tan;
                glm::vec3 bitan;
                tan.x = mesh->mTangents[i].x;
                tan.y = mesh->mTangents[i].y;
                tan.z = mesh->mTangents[i].z;

                bitan.x = mesh->mBitangents[i].x;
                bitan.y = mesh->mBitangents[i].y;
                bitan.z = mesh->mBitangents[i].z;

                vertex.bitangent = bitan;
                vertex.tangent = tan;
            } else if(((i + 1) % 3) == 0)
            {
                glm::vec3 edge1 = vertices[i - 1].position - vertices[i - 2].position;
                glm::vec3 edge2 = vertices[i].position - vertices[i - 2].position;
                glm::vec2 deltaUV1 = vertices[i - 1].UVs - vertices[i - 2].UVs;
                glm::vec2 deltaUV2 = vertices[i].UVs - vertices[i - 2].UVs; 

                float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

                glm::vec3 tangent;
                tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                tangent = glm::normalize(tangent);

                glm::vec3 bitangent;
                bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
                bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
                bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
                bitangent = glm::normalize(bitangent);

                vertices[i].tangent = tangent;
                vertices[i - 1].tangent = tangent;
                vertices[i - 2].tangent = tangent;
                vertices[i].bitangent = bitangent;
                vertices[i - 1].bitangent = bitangent;
                vertices[i - 2].bitangent = bitangent;
            }
        }

        for(uint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(uint j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        Material outMaterial;

        if (scene->mNumMaterials > 0)
        {
            
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiColor4D color;
            material->Get(AI_MATKEY_COLOR_AMBIENT, color);
            outMaterial.ambient = glm::make_vec4(&color.r) + glm::vec4(0.1f);
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            outMaterial.diffuse = glm::make_vec4(&color.r);
            material->Get(AI_MATKEY_COLOR_SPECULAR, color);
            outMaterial.specular = glm::make_vec4(&color.r);
            material->Get(AI_MATKEY_OPACITY, outMaterial.opacity);
            material->Get(AI_MATKEY_SHININESS, outMaterial.shininess);

            aiString strDiff, strNorm, strSpec;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &strDiff);
            material->GetTexture(aiTextureType_HEIGHT, 0, &strNorm);
            material->GetTexture(aiTextureType_SPECULAR, 0, &strSpec);
            if (strDiff.C_Str() != "")
            {
                if(b_UseManager)
                {
                    std::string path = m_Dir + strDiff.C_Str();
                    Diffuse = m_TexMan->LoadTexture(path.c_str());
                    path = m_Dir + strSpec.C_Str();
                    Specular = m_TexMan->LoadTexture(path.c_str());
                    path = m_Dir + strNorm.C_Str();
                    Normal = m_TexMan->LoadTexture(path.c_str());
                    return std::make_unique<Mesh>(vertices, indices, Diffuse, Specular, Normal, m_Shader, outMaterial);
                }
                std::string path = m_Dir + strDiff.C_Str();
                Diffuse = std::make_shared<Texture>(path.c_str());
                path = m_Dir + strSpec.C_Str();
                Specular = std::make_shared<Texture>(path.c_str());
                path = m_Dir + strNorm.C_Str();
                Normal = std::make_shared<Texture>(path.c_str());
                return std::make_unique<Mesh>(vertices, indices, Diffuse, Specular, Normal, m_Shader, outMaterial);
            }
        }
        return std::make_unique<Mesh>(vertices, indices, m_Shader, outMaterial);
    }
}



