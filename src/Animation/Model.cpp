/*
** EPITECH PROJECT, 2022
** Model.cpp
** File description:
** Model
*/

#include "Model.hpp"

using namespace neo;

//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4 &from)
{
    glm::mat4 to;

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
    this->processNode(*scene->mRootNode, *scene);
}

void neo::Model::processNode(aiNode &node, const aiScene &scene)
{
    for (unsigned int i = 0; i < node.mNumMeshes; i++) {
        aiMesh *mesh = scene.mMeshes[node.mMeshes[i]];
        this->_meshes.push_back(processMesh(*mesh, scene));
    }
    for (unsigned int i = 0; i < node.mNumChildren; i++)
        this->processNode(*node.mChildren[i], scene);
}

void neo::Model::setVertexBoneDataToDefault(Vertex &vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
        vertex.BoneIDs[i] = -1;
        vertex.Weights[i] = 0.0f;
    }
}

void neo::Model::setVertexBoneData(Vertex &vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
        if (vertex.BoneIDs[i] < 0) {
            vertex.Weights[i] = weight;
            vertex.BoneIDs[i] = boneID;
            break;
        }
    }
}

void neo::Model::extractBoneWeightForVertices(std::vector<Vertex> &vertices, aiMesh &mesh, const aiScene &scene)
{
    auto &boneInfoMap = this->_boneInfoMap;
    int &boneCount = this->_boneCounter;

    for (int boneIndex = 0; boneIndex < mesh.mNumBones; ++boneIndex) {
        int boneID = -1;
        std::string boneName = mesh.mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            neo::BoneInfo newBoneInfo;
            newBoneInfo.id = boneCount;
            newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh.mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID = boneCount;
            boneCount++;
        } else {
            boneID = boneInfoMap[boneName].id;
        }
        if (boneID == -1)
            continue;
        auto weights = mesh.mBones[boneIndex]->mWeights;
        int numWeights = mesh.mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            if (vertexId <= vertices.size())
                this->setVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}

neo::Mesh neo::Model::processMesh(aiMesh &mesh, const aiScene &scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<neo::Texture> textures;

    for (unsigned int i = 0; i < mesh.mNumVertices; i++) {
        Vertex vertex;
        setVertexBoneDataToDefault(vertex);
        vertex.Position = glm::vec3(mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z);
        vertex.Normal = glm::vec3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);

        if (mesh.mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh.mTextureCoords[0][i].x;
            vec.y = mesh.mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
        aiFace face = mesh.mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *materialLoaded = scene.mMaterials[mesh.mMaterialIndex];
    aiColor3D color(0.f, 0.f, 0.f);
    float shininess;

    neo::Material material;

    materialLoaded->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    material.diffuse = glm::vec3(color.r, color.g, color.b);
    materialLoaded->Get(AI_MATKEY_COLOR_AMBIENT, color);
    material.ambient = glm::vec3(color.r, color.g, color.b);
    materialLoaded->Get(AI_MATKEY_COLOR_SPECULAR, color);
    material.specular = glm::vec3(color.r, color.g, color.b);
    materialLoaded->Get(AI_MATKEY_SHININESS, shininess);
    material.shininess = shininess;

    this->extractBoneWeightForVertices(vertices, mesh, scene);

    aiMaterial *tex = scene.mMaterials[mesh.mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(tex, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(tex, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = loadMaterialTextures(tex, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = loadMaterialTextures(tex, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    if (textures.size()) {

    }

    return neo::Mesh(vertices, indices, material, textures);
}

std::vector<neo::Texture> neo::Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<neo::Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < this->_texturesLoaded.size(); j++) {
            if (std::strcmp(this->_texturesLoaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(this->_texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            neo::Texture texture;
            texture.id = textureFromFile(str.C_Str(), "resources/textures/");
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            this->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int neo::Model::textureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;

    Image image = LoadImage(filename.c_str());
    Texture2D texture = LoadTextureFromImage(image);
    return texture.id;
}

void neo::Model::draw(neo::Shader &shader)
{
    for (unsigned int i = 0; i < this->_meshes.size(); i++)
        this->_meshes[i].draw(shader);
}

void neo::Model::setPos(glm::vec3 pos)
{
}
