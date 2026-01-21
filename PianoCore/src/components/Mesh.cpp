#include "components/Mesh.h"

Component::Mesh1::Mesh1(PianoCore::VertexArray* vertexArray,
                        PianoCore::VertexBufferData vertexBufferData,
                        PianoCore::IndexBufferData indexBufferData,
                        PianoCore::VertexBufferLayout layout)
    : vertexBuffer(vertexBufferData),
      indexBuffer(indexBufferData),
      layout(layout) {
    vertexArray = vertexArray;
    vertexArray->Bind();
    std::cout << "Bound VAO ID: " << vertexArray->GetRendererId() << std::endl;
    vertexArray->AddBuffer(vertexBuffer, layout);
    indexBuffer.Bind();
    std::cout << "Bound mesh to VAO ID: " << vertexArray->GetRendererId()
              << std::endl;
}

PianoCore::VertexArray* Component::Mesh1::GetVertexArray() {
    return vertexArray;
}

PianoCore::VertexBuffer* Component::Mesh1::GetVertexBuffer() {
    return &vertexBuffer;
}
PianoCore::IndexBuffer* Component::Mesh1::GetIndexBuffer() {
    return &indexBuffer;
}
PianoCore::VertexBufferLayout* Component::Mesh1::GetBufferLayout() {
    return &layout;
}

Component::Mesh::Mesh(std::vector<PianoCore::Vertex> vertices,
                      std::vector<unsigned int> indices,
                      std::vector<PianoCore::Texture> textures)
    : Type(MeshType::Model) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Component::Mesh::Draw(const std::shared_ptr<Shaders::IShader>& shader) {
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 +
                        i);  // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(
                specularNr++);  // transfer unsigned int to string
        } else if (name == "texture_normal") {
            number =
                std::to_string(normalNr++);  // transfer unsigned int to string
        } else if (name == "texture_height") {
            number =
                std::to_string(heightNr++);  // transfer unsigned int to string
        }

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()),
                    i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()),
                   GL_UNSIGNED_INT, 0);
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

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PianoCore::Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PianoCore::Vertex),
                          (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PianoCore::Vertex),
                          (void*)offsetof(PianoCore::Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PianoCore::Vertex),
                          (void*)offsetof(PianoCore::Vertex, TexCoords));

    glBindVertexArray(0);
}
