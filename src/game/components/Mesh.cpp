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

Component::Mesh::Mesh(std::vector<Renderer::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Renderer::Texture> textures) : Type(MeshType::Model)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Component::Mesh::setupMesh()
{

}

Ref<Component::Mesh> Component::Mesh::Create(MeshType type,
						PianoCore::Buffer<Renderer::Vertex>&& vertices,
						PianoCore::Buffer<uint32_t>&& indices,
						const Material& material)
{
	auto mesh = CreateRef<Mesh>(type);
	mesh->SubMeshes.Emplace(std::move(vertices), std::move(indices), 0U);
	mesh->Materials.Add(material);
	return mesh;
}

Ref<Component::Mesh> Component::Mesh::Create(MeshType type, const Material& material) {
	PianoCore::Buffer<uint32_t> indices;
	PianoCore::Buffer<Renderer::Vertex> vertices;

	switch(type) {
		case MeshType::Cube:
		{
			vertices =
			{
				{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 0.0f } },
				{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f } },
				{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f, 1.0f } },
				{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 0.0f, 1.0f } },
				{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 0.0f } },
				{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 0.0f } },
				{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f, 1.0f } },
				{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 0.0f, 1.0f } },

				{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
				{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
				{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
				{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },
				{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f } },
				{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f } },
				{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f, 1.0f } },
				{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f, 1.0f } },

				{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 0.0f } },
				{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 0.0f } },
				{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f } },
				{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 0.0f, 1.0f } },
				{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 0.0f } },
				{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 0.0f } },
				{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f, 1.0f } },
				{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f } },
			};

			indices =
			{
				0,  3,  2, // Front
				2,  1,  0,

				4,  5,  6, // Back
				6,  7,  4,

				11,  8,  9, // Left
				 9, 10, 11,

				12, 13, 14, // Right
				14, 15, 12,

				16, 17, 18, // Bottom
				18, 19, 16,

				20, 21, 22, // Top
				22, 23, 20
			};

			break;
		}

		case MeshType::Quad:
		{
			vertices =
			{
				{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
				{ {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
				{ { -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
				{ {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
			};

			indices =
			{
				0, 2, 3,
				3, 1, 0,
			};

			break;
		}
	}

	return Create(type, std::move(vertices), std::move(indices), material);
}
