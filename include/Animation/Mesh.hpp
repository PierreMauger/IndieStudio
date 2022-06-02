/*
** EPITECH PROJECT, 2022
** Mesh.hpp
** File description:
** Mesh
*/

#ifndef MESH_HPP
    #define MESH_HPP

    #define MAX_BONE_INFLUENCE 4

    #include "includes.hpp"
    #include "Shader.hpp"

    #include <GL/glew.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>

namespace neo
{
    typedef struct {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
        int BoneIDs[MAX_BONE_INFLUENCE];
        float Weights[MAX_BONE_INFLUENCE];
    } Vertex;

    typedef struct {
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 ambient;
        float shininess;
    } Material;

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
        private:
            std::vector<Vertex> _vertices;
            std::vector<unsigned int> _indices;
            std::vector<neo::Texture> _textures;
            neo::Material _material;
            unsigned int VAO;
            unsigned int VBO;
            unsigned int EBO;

        public:
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, neo::Material material, std::vector<neo::Texture> textures);
            ~Mesh() = default;
            void setupMesh();
            void draw(neo::Shader &shader);
    };
}

#endif // MESH_HPP
