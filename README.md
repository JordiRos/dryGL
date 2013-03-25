dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework, currently targeting iOS (Android planned)

The main aim is to have a super simple way of creating an ES 2.0 application, plus a complete list of low level classes for rendering things to screen.
This means Vbo / Ibo buffers, Fbo, Shader / Texture loaders and utils, Cameras, etc, so then you can write your own object structures, scene renderers and custom shaders a lot easier.

On top of that, we plan to write some generic addons, like device hardware access (accelerometer, camera), a sound engine, a basic scene/object/material renderer, postprocess effects, text rendering, physics, resource manager, and many more.

Currently it is still in alpha, but things are going ok and we currently have some examples working, that work as tutorials on how to use current features.

Current features
================
- iOS version only (3.1+)
- Renderer
- Shader
- Vbo
- Ibo
- Fbo
- Cameras
- Uniform utils
- Image/Texture
- Scene/Object/Mesh/Material (WIP)
- Addons/QuadBatch / TODO: Make it a real quadbatch pipeline

Dependencies
============
- Glm

Examples
========
- AppVbo: Usage of Vbo / Ibo for rendering a cube in 3D
- AppFbo: Usage of Fbo object for rendering scene to texture
- AppQuadBatch: Usage of QuadBatch for rendering quads to screen the easy way
- AppGLSL: Screen space GLSL shader

Roadmap
=======
- Android version
- Sound engine (OpenAL?)
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Material instances (Diffuse, Lambert, etc)
- Addons: ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Addons: iOS features / accelerometer, camera, microphone, etc

License
=======

Licensed under the MIT license.
