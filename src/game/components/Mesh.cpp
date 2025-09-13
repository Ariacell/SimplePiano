#include "Mesh.h"

Component::Mesh1::Mesh1(Renderer::VertexArray* va,
                        Renderer::VertexBufferData vertexBufferData,
                        Renderer::IndexBufferData indexBufferData,
                        Renderer::VertexBufferLayout layout)
    : vertexBuffer(vertexBufferData),
      indexBuffer(indexBufferData),
      layout(layout) {
    vertexArray = va;
    va->Bind();
    std::cout << "Bound VAO ID: " << va->GetRendererId() << std::endl;
    va->AddBuffer(vertexBuffer, layout);
    indexBuffer.Bind();
    std::cout << "Bound mesh to VAO ID: " << va->GetRendererId() << std::endl;
}

Renderer::VertexArray* Component::Mesh1::GetVertexArray() {
    return vertexArray;
}

Renderer::VertexBuffer* Component::Mesh1::GetVertexBuffer() {
    return &vertexBuffer;
}
Renderer::IndexBuffer* Component::Mesh1::GetIndexBuffer() {
    return &indexBuffer;
}
Renderer::VertexBufferLayout* Component::Mesh1::GetBufferLayout() {
    return &layout;
}

Component::Mesh::Mesh(std::vector<Renderer::Vertex> vertices,
                      std::vector<unsigned int> indices,
                      std::vector<Renderer::Texture> textures)
    : Type(MeshType::Model) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Component::Mesh::Draw(const std::shared_ptr<Shaders::IShader>& shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to string

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.get()->ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        
        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

void Component::Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Renderer::Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Renderer::Vertex),
                          (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Renderer::Vertex),
                          (void*)offsetof(Renderer::Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Renderer::Vertex),
                          (void*)offsetof(Renderer::Vertex, TexCoords));

    glBindVertexArray(0);
}

Ref<Component::Mesh> Component::Mesh::Create(
    MeshType type, PianoCore::Buffer<Renderer::Vertex>&& vertices,
    PianoCore::Buffer<uint32_t>&& indices, const Material& material) {
    auto mesh = CreateRef<Mesh>(type);
    mesh->SubMeshes.Emplace(std::move(vertices), std::move(indices), 0U);
    mesh->Materials.Add(material);
    return mesh;
}

Ref<Component::Mesh> Component::Mesh::Create(MeshType type,
                                             const Material& material) {
    PianoCore::Buffer<uint32_t> indices;
    PianoCore::Buffer<Renderer::Vertex> vertices;

    switch (type) {
        case MeshType::Cube: {
            vertices = {
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
                {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
                {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
                {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
                {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

                {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
                {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
                {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
                {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

                {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
                {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
                {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
                {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
                {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
                {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
            };

            indices = {0,  3,  2,  // Front
                       2,  1,  0,

                       4,  5,  6,  // Back
                       6,  7,  4,

                       11, 8,  9,  // Left
                       9,  10, 11,

                       12, 13, 14,  // Right
                       14, 15, 12,

                       16, 17, 18,  // Bottom
                       18, 19, 16,

                       20, 21, 22,  // Top
                       22, 23, 20};

            break;
        }

        case MeshType::Quad: {
            vertices = {
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            };

            indices = {
                0, 2, 3, 3, 1, 0,
            };

            break;
        }
    }

    return Create(type, std::move(vertices), std::move(indices), material);
}
