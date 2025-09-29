
# Windows and rendering

The aim is to use this project as a playground to bring my experience designing systems in higher level languages to c++.
One aspect of this is aiming for abstracted windowing and rendering layers so I can quickly experiment with implementing the same graphics programming features in different underlying APIs, whether that be GLFW for windowing, or DirectX/OpenGL/Vulkan for rendering. This should force me to have a solid understanding of how to use c++ syntax to implement familiar design patterns from domain driven design/hexagonal architecture.

The window abstraction can be visualised as

+--------------------+
|  IWindow           | ← 
defines my window interface
+--------------------+
        |
        v
+--------------------+
|  GLFWwindow        | ← 
implements the GLFW variant of the IWindow interface
+--------------------+
        ^
        |
+--------------------+
| InputManager       | ← 
currently binds itself to the window and requries GLFW, but will become window implementation agnostic
+--------------------+
        |
        v
+--------------------+
| Application   | ← 
calls input.IsPressed("Action") to confirm status of various inputs to avoid coupling the application logic to a specific window implementation
+--------------------+

The rendering abstraction functions similarly, with the goal of having hotswappable rendering libraries. The IRenderer abstracts away the responsibilities of the rendering library such as clearing each frame and drawing the scene (currently this is just "drawRectangle" as a standin), and the implementations should be responsible for taking the vertex and shader information and actually presenting that to the screen in the designated window.

# ECS and scene management

I really like this article by Austin Morlan on their simple entity component system implementation via a top level coordinator and a bit-based signature system for components. I'm sure there are some drawbacks (out of the gate I'm not sure how much I like the expliciteness of "registering" components up front, but we'll see). https://austinmorlan.com/posts/entity_component_system/
