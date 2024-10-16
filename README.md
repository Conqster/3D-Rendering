# Conqster Realtime Rendering Technology (CRRT)

CRRT is personal learning project focused on real-time 3D rendering using OpenGL. Designed to explore, implement various rendering techniques and features. 

|<a href="https://www.youtube.com/watch?v=9skO5a-XUGg"><img src = "Docs/milestone_light_shadow.png"/>|
|:-|
|<p align = "center"> *A Youtube video of current Milestone with light rendering simulation.* </p>|


## Goals
The primary aim of this project is to deepen my understanding of: 
-  3D Rendering techniques.
- Advance my C++ knowledge.
- Algorithms and data strutures relevant to game technologies (rendering).
- Memory management and optimization.

## Current Features
### Rendering Techniques
- Environment Mapping (Skybox)
- Debug Gizmos Primitive
- Light Source (Directional, Point & Spot)
- Omnidirectional Shadow mapping for Point Lights
- Directional Light Shadow mapping
- Multisample Anti-alising (MSAA)
- Object Instancing
- Screen Space Post Processing (Grayscale, Blurring, Edge detection)
- Scene property debugging (Model-World-Space Normals, Model Space Normal debugging)
- Mesh Primitive Construction
- Naive Gamma Correction

### Utilities
- Multiscene management
- Model Loading via Assimp
- Image Loading via stb_image
- Editing UI via ImGui


## Quick Render Samples
#### Omnidirectional Shadow (Point Lights)
|<img src = "Docs/Dynamic_omnidirectional_shadow.gif"/>|
|:-|
|<p align = "center"> *Omnidirectional Shadow, Point Light Shadows.* </p>|

#### Directional Shadow (Directional Light)
|<img src = "Docs/Dynamic_directional_shadow.gif"/>|
|:-|
|<p align = "center"> *Directional Shadow, Directional Light Shadows.* </p>|

#### Skybox, Framebuffer
|<img src = "Docs/Skybox, Framebuffer, Depthtest.png"/>|
|:-|
|<p align = "center"> *Skybox, Framebuffer (renderpass), Depth test.* </p>|

#### MSAA (Post Process)
|<img src = "Docs/MSAA 1x-8x.gif"/>|
|:-|
|<p align = "center"> *Multisample Anti-alising 1x-8x, Post Processing.* </p>|

### Debugging 
#### Scene Objects Debugging
|<img src = "Docs/debugging_scene.gif"/>|
|:-|
|<p align = "center"> *Debugging, Normals (Model Space, World Space).* </p>|

#### Model Normals (Geometry Shaders)
|<img src = "Docs/sphere_normals.png"/>|
|:-|
|<p align = "center"> *Debugging, Model Normals (Geometry Shaders).* </p>|


## Documentation 
- [Quick Start.](Docs/QuickStart.md)
- [Development Issues.](Docs/DevelopmentIssues.md).

For more detailed information, please refer to the [Detailed Documentation.](Docs/Documentation.md)

## Dependencies
Current libaries in use: GLM, GLEW, GLFW, stb-image, Assimp.

## Learning Resources
- [learnopengl.com.](https://learnopengl.com/Getting-started)
- [The Cherno C++ videos.](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb)
- OpenGl Programming Guide 9th Edition (Red Book).
- Mathematics for 3D Game Programming and Computer Graphics - Eric Lengyel.
- Foundations of Game Engine Development (Volume 2 - Rendering) Eric Lengyel.
- [Forward and Deferred Rendering - Cambridge Computer Science Talks.](https://youtu.be/n5OiqJP2f7w?si=QQGg5Mj2bPoBzMiu)
- Core Techniques and Algorithms in Game Programming.
