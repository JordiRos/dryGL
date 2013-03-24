dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current features
================
- iOS version
- Renderer
- Image
- Texture
- Shader
- Vbo
- Ibo
- Fbo
- Cameras
- Scene/Object/Mesh/Material (WIP)
- Addons/ImageLoader (iOS only)
- Addons/QuadBatch / TODO: Make it a real quadbatch pipeline

Dependencies
============
- Glm

Examples
========
- AppVbo: Usage of Vbo / Ibo for rendering a cube in 3D
- AppFbo: Usage of Fbo object for rendering to texture
- AppQuadBatch: Usage of QuadBatch for rendering quads to screen the easy way
- AppGLSL: Screen space GLSL shader

Roadmap
=======
- Android version
- Input manager
- Sound manager
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Material instances (Diffuse, Lambert, etc)
- Addons: ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Addons: iOS features / accelerometer, camera, microphone, etc
