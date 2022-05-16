/*
** EPITECH PROJECT, 2022
** Bone.hpp
** File description:
** Bone
*/

#ifndef BONE_HPP
    #define BONE_HPP

    #include "includes.hpp"

    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
    #include <glm/gtx/quaternion.hpp>
    #include <assimp/scene.h>

typedef struct {
	glm::vec3 position;
	float timeStamp;
} KeyPosition;

typedef struct {
	glm::quat orientation;
	float timeStamp;
} KeyRotation;

typedef struct {
	glm::vec3 scale;
	float timeStamp;
} KeyScale;

namespace neo
{
    class Bone
    {
        private:
            std::vector<KeyPosition> _positions;
            std::vector<KeyRotation> _rotations;
            std::vector<KeyScale> _scales;
            int _numPositions;
            int _numRotations;
            int _numScalings;

            std::string _name;
            glm::mat4 _localTransform;
            int _ID;

        public:
            Bone(const std::string &name, int ID, const aiNodeAnim *channel);
            ~Bone() = default;

            void update(float animationTime);
            int getPositionIndex(float animationTime);
            int getRotationIndex(float animationTime);
            int getScaleIndex(float animationTime);

            glm::mat4 getLocalTransform();
            std::string getName() const;
            int getID();

            float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);
            glm::mat4 InterpolatePosition(float animationTime);
            glm::mat4 InterpolateRotation(float animationTime);
            glm::mat4 InterpolateScale(float animationTime);
    };
}

#endif // BONE_HPP
