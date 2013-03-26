dryGL
=====

#### OpenGL ES 2.0 engine ####

**dryGL** is a lightweight OpenGL ES 2.0 engine for mobile and ES devices, currently targeting iOS only. It is written mainly in **C++** and an Android version is currently on our roadmap.

The aim of the project is to build a framework for creating an ES 2.0 application very easy, but also providing a complete list of low and mid level classes for rendering things to screen.
This means utilities for Vbo, Fbo, Textures, Shaders, Uniforms, Attributes, Cameras, etc, so then you can write your own object structures, scene renderers and custom shaders a lot easier.

On top of that, we plan to write some generic addons, like device hardware access (accelerometer, camera), a sound engine, a basic scene/object/material renderer, postprocess effects, text rendering, physics, resource manager, and many more.

Currently we are close to a beta release, with some examples that can help understand the current features and how to use the engine.

Current features
================
- iOS version only (3.1+)
- ES 2.0 Renderer
- Vbo
- Ibo
- Fbo
- Cameras
- Images/Textures
- Shaders
- Uniform utils
- Attribute utils
- Addons/Scene: Scene,Object,Mesh,Material (WIP)
- Addons/QuadBatch: Quad drawer the simple way. TODO: Make it a real quadbatch pipeline

Dependencies
============
- Glm: [Download glm](http://glm.g-truc.net/) and copy contents to libs/glm

Examples
========
There is a single project on apps/examples where you can switch easily between example. Edit AppDelegate.mm and uncomment the desired example to run it.
This project works also as a template for new applications.
Current working examples:
- AppVbo: Usage of Vbo / Ibo for rendering a cube in 3D
- AppFbo: Usage of Fbo object for rendering scene to texture
- AppQuadBatch: Usage of QuadBatch for rendering quads to screen the easy way
- AppGLSL: Screen space GLSL shader
- AppParticles: Particle system with custom attributes

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

Contributions
=============

Once we release the first beta, you can contribute with fixes/addons/examples forking the project and pulling any request. We would be very happy!

License
=======

Licensed under the MIT license.
