/*
** EPITECH PROJECT, 2022
** Model.cpp
** File description:
** Model
*/

#include "Model.hpp"

using namespace neo;

static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4 &from)
{
    glm::mat4 to;
    //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
}

neo::Model::Model(std::string const &filename)
{
    this->load(filename);
}

std::map<std::string, neo::BoneInfo> &neo::Model::getBoneInfoMap()
{
    return this->_boneInfoMap;
}

int &neo::Model::getBoneCount()
{
    return this->_boneCounter;
}

void neo::Model::load(std::string const &filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene)
        throw std::runtime_error(importer.GetErrorString());
    this->processNode(scene->mRootNode, scene);
}

void neo::Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->_meshes.push_back(processMesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
        this->processNode(node->mChildren[i], scene);
}

void neo::Model::SetVertexBoneDataToDefault(Vertex &vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
        vertex.BoneIDs[i] = -1;
        vertex.Weights[i] = 0.0f;
    }
}

void neo::Model::SetVertexBoneData(Vertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
        if (vertex.BoneIDs[i] < 0) {
            vertex.Weights[i] = weight;
            vertex.BoneIDs[i] = boneID;
            break;
        }
    }
}

void neo::Model::ExtractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh *mesh, const aiScene *scene)
{
    auto &boneInfoMap = this->_boneInfoMap;
    int &boneCount = this->_boneCounter;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            neo::BoneInfo newBoneInfo;
            newBoneInfo.id = boneCount;
            newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID = boneCount;
            boneCount++;
        } else {
            boneID = boneInfoMap[boneName].id;
        }
        if (boneID == -1)
            continue;
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            if (vertexId <= vertices.size())
                SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}

neo::Mesh neo::Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        SetVertexBoneDataToDefault(vertex);
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        // texture coordinates
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material_loaded = scene->mMaterials[mesh->mMaterialIndex];
    aiColor3D color(0.f, 0.f, 0.f);
    float shininess;

    neo::Material materialt;

    material_loaded->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    materialt.diffuse = glm::vec3(color.r, color.g, color.b);
    material_loaded->Get(AI_MATKEY_COLOR_AMBIENT, color);
    materialt.ambient = glm::vec3(color.r, color.g, color.b);
    material_loaded->Get(AI_MATKEY_COLOR_SPECULAR, color);
    materialt.specular = glm::vec3(color.r, color.g, color.b);
    material_loaded->Get(AI_MATKEY_SHININESS, shininess);
    materialt.shininess = shininess;

    ExtractBoneWeightForVertices(vertices, mesh, scene);

    return neo::Mesh(vertices, indices, materialt);
}

void neo::Model::draw(neo::Shader &shader)
{
    for(unsigned int i = 0; i < this->_meshes.size(); i++)
        this->_meshes[i].draw(shader);
}

void neo::Model::setPos(glm::vec3 pos)
{
}
