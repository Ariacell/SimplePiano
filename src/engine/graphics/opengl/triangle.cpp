#include "triangle.h"

#include <GLES3/gl32.h>
#include <engine/graphics/IndexBuffer.h>
#include <engine/graphics/VertexArray.h>
#include <engine/graphics/VertexBuffer.h>
#include <engine/graphics/VertexBufferLayout.h>

#include <array>
#include <utility>
#include <vector>

// unsigned int OpenGlGraphics::bindRectangle(
//     std::pair<std::vector<float>, std::vector<unsigned int>> triangleData) {
//     auto triangle = triangleData;
//     unsigned int VBO, EBO, VAO;
//     // glGenVertexArrays(1, &VAO);
//     // // // bind the Vertex Array Object first, then bind and set vertex
//     buffer(s),
//     // // // and then configure vertex attributes(s).
//     // glBindVertexArray(VAO);
//     Renderer::VertexArray va;

//     Renderer::VertexBuffer rectangleVertexBuffer(
//         triangle.first.data(), sizeof(float) * triangle.first.size());
//     Renderer::IndexBuffer rectangleIndexBuffer(triangle.second.data(),
//                                                triangle.second.size());

//     Renderer::VertexBufferLayout layout;
//     // layout.Push<float>(3);
//     // layout.Push<float>(3);
//     // layout.Push<float>(2);
//     va.AddBuffer(rectangleVertexBuffer, layout);

//     // va.Bind();
//     // rectangleIndexBuffer.Bind();

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                           (void*)0);
//     glEnableVertexAttribArray(0);

//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                           (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
//                           (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(2);

//     // note that this is allowed, the call to glVertexAttribPointer
//     registered
//     // VBO as the vertex attribute's bound vertex buffer object so afterwards
//     we
//     // can safely unbind
//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     // remember: do NOT unbind the EBO while a VAO is active as the bound
//     // element buffer object IS stored in the VAO; keep the EBO bound.
//     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//     // You can unbind the VAO afterwards so other VAO calls won't
//     accidentally
//     // modify this VAO, but this rarely happens. Modifying other VAOs
//     requires a
//     // call to glBindVertexArray anyways so we generally don't unbind VAOs
//     (nor
//     // VBOs) when it's not directly necessary.
//     glBindVertexArray(0);
//     return va.GetRendererId();
//     // return va.GetRendererId();
// }

unsigned int OpenGlGraphics::bindRectangle(
    std::pair<std::vector<float>, std::vector<unsigned int>> triangleData) {
    auto triangle = triangleData;
    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    Renderer::VertexBuffer rectangleVertexBuffer(
        triangle.first.data(), sizeof(float) * triangle.first.size());
    Renderer::IndexBuffer rectangleIndexBuffer(triangle.second.data(),
                                               triangle.second.size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered
    // VBO as the vertex attribute's bound vertex buffer object so afterwards we
    // can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound
    // element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally
    // modify this VAO, but this rarely happens. Modifying other VAOs requires a
    // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
    // VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    return VAO;
}
