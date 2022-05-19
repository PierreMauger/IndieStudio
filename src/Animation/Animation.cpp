/*
** EPITECH PROJECT, 2022
** Animation.cpp
** File description:
** Animation
*/

#include "Animation.hpp"

using namespace neo;

static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4 &from)
{
    glm::mat4 to;
    // the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
}

Animation::Animation(const std::string &path, neo::Model *model)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

    this->_duration = scene->mAnimations[0]->mDuration;
    this->_tickPerSecond = scene->mAnimations[0]->mTicksPerSecond;

    aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
    globalTransformation = globalTransformation.Inverse();

    this->readHierarchyData(this->_rootNode, scene->mRootNode);
    this->readMissingBones(scene->mAnimations[0], *model);
}

Bone *Animation::findBone(const std::string &name)
{
    for (auto &bone : this->_bones)
        if (bone.getName() == name)
            return &bone;
    return nullptr;
}

float Animation::getTicksPerSecond() const
{
    return this->_tickPerSecond;
}

float Animation::getDuration() const
{
    return this->_duration;
}

const AssimpNodeData &Animation::getRootNode() const
{
    return this->_rootNode;
}

const std::map<std::string, neo::BoneInfo> &Animation::getBoneInfoMap() const
{
    return this->_boneInfoMap;
}

void Animation::readMissingBones(const aiAnimation *animation, neo::Model &model)
{
    int size = animation->mNumChannels;

    auto &boneInfoMap = model.getBoneInfoMap();
    int &boneCount = model.getBoneCount();

    for (int i = 0; i < size; i++) {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        this->_bones.push_back(Bone(boneName, boneInfoMap[boneName].id, channel));
    }
    this->_boneInfoMap = boneInfoMap;
}

void Animation::readHierarchyData(AssimpNodeData &dest, const aiNode *src)
{
    dest.name = src->mName.data;
    dest.transformation = ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (unsigned int i = 0; i < src->mNumChildren; i++) {
        AssimpNodeData child;
        this->readHierarchyData(child, src->mChildren[i]);
        dest.children.push_back(child);
    }
}
