dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current status
==============
- iOS project
- FreeImage loader
- Texture
- Pixels
- Shader
- Camera: CameraPerspective, CameraOrthogonal
- Vbo
- Ibo
- Fbo
- Addons/QuadBatch: simple quad drawing, later on it will be a real quadbatch pipeline

Examples:
- AppSimple: Rotating 3D cube
- AppFbo:

ToDo
====
- Move FreeImage loader to Addons/FreeImageLoader

Roadmap
=======
- Android project & example
- Input manager
- Renderer utilities (viewports, renderstates, etc)
- Mesh
- State/Render manager
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Add libpng / libjpg / libdds loaders
- Addons: Scene, Object, Material, SceneRenderer
- Addons: Material instances
- Addons: ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Defines for debug/release, logs, etc

Dependencies
============
- Glm
- FreeImage
