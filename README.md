dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current status:
- iOS project
- FreeImage loader
- Texture
- Pixels
- Shader
- BasicShader
- Camera: CameraPerspective, CameraOrthogonal
- Fbo
- Addons/QuadBatch: simple quad drawing, later on it will be a real quadbatch pipeline

Example:
Single Application with multiple sub Apps for easier sample exploration (instead of many projects)
- AppSimple: Rotating 3D cube + cameraPerspective + cameraOrthogonal + Fbo example, to be splitted in simple examples

Dependencies:
- Glm
- FreeImage

Temp:
- Move FreeImage loader to Addons/FreeImageLoader

Roadmap:
- Android project & example
- Renderer utilities (clear, viewports, renderstates, etc)
- Vbo
- Mesh
- Auto uniforms/attributes in shader object, and maybe basic auto attributes/uniforms (positions, texcoords, colors, etc)
- State/Render manager
- Inheritable basic shader
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Add libpng / libjpg / libdds loaders
- Addons: Scene, Object, Material, SceneRenderer
- Addons: Material instances
- Addons: ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Defines for debug/release, logs, etc

