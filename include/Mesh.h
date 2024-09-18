#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "VAO.h"
#include "Camera.h"
#include "Texture.h"
#include <vector>

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        VAO VAO;

        Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);
        
        void Draw(Shader &shader, Camera &camera);
};

#endif
