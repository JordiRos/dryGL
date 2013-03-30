dryGL
=====

#### C++ OpenGL ES 2.0 framework ####

**dryGL** is a lightweight OpenGL ES 2.0 engine for mobile and ES devices. It is now available only for **iOS**, but we intend to be it cross-platform and an **Android** version is currently on our roadmap (maybe more in the future? Raspberry-Pi, Ouya, Windows Embedded...)

The aim of the project is to have a framework for creating an ES 2.0 application very easy, but also providing a complete list of low and mid level classes for rendering things to screen.
This means utilities for Vbo, Fbo, Textures, Shaders, Uniforms, Attributes, Cameras, etc, so you can write your own object structures, scene renderers and custom shaders a lot easier.

On top of that, we plan to write some generic addons, like a basic scene renderer, geometry/material instances, resource managers, textr rendering, postprocess effects, device hardware access (accelerometer, camera, extern display), a sound engine, physics, and many more.

Currently we are close to a beta release, with some examples that can help understand how to setup an application and use the current features.

Features
========
- ES 2.0 Renderer
- Math (using glm)
- Image/Texture2D/TextureCube
- Fbo
- Shaders
- Vbo
- Ibo
- Uniform
- Attribute
- Material
- Cameras
- iOS version (3.1+)

Addons
======
- Scene: Scene,Object,Mesh,Renderer,Materials (WIP)
- QuadBatch: Quad drawer the simple way. TODO: Make it a real quadbatch pipeline

Examples
========
There is a single project on apps/examples where you can switch easily between examples. Edit AppDelegate.mm and instance desired App from the list.
Current working examples:
- AppVbo: Usage of Vbo / Ibo for rendering a cube in 3D
- AppFbo: Usage of Fbo object for rendering scene to texture
- AppQuadBatch: Usage of QuadBatch for rendering quads to screen the easy way
- AppParticles: Particle system with custom attributes
- AppPostprocess: Usage of Fbo + Shaders for postprocessing
- AppShaderToy: Screen space GLSL shader for loading ShaderToy awesome examples

Roadmap
=======
- Debug functions (DebugDrawText, DebugDrawRectangle, DrawAxis, etc)
- Android version
- Sound engine (OpenAL?)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Material instances (Diffuse, Lambert, etc)
- Addons: Generic ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Addons: iOS features / accelerometer, camera, microphone, etc

Dependencies
============
- Glm: [Download glm](http://glm.g-truc.net/) and copy contents to libs/glm

Contributions
=============

Once we release the first beta, we will create a dev branch were you should be able to contribute with fixes/addons/examples forking the project and pulling any request. We would be very happy!

License
=======

Licensed under the MIT license.
