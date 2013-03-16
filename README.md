dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current status:
- iOS project
- FreeImage loader
- Texture
- Pixels
- Shader
- Camera: CameraPerspective, CameraOrthogonal
- Fbo
- Vbo
- Addons/QuadBatch: simple quad drawing, later on it will be a real quadbatch pipeline

Example:
- AppSimple: Rotating 3D cube, cameraPerspective, cameraOrthogonal, Vbo, Fbo

Dependencies:
- Glm
- FreeImage

Temp:
- Move FreeImage loader to Addons/FreeImageLoader

Roadmap:
- Android project & example
- Input manager
- Renderer utilities (clear, viewports, renderstates, etc)
- Mesh
- Auto uniforms/attributes in shader object, and maybe basic auto attributes/uniforms (positions, texcoords, colors, etc)
- State/Render manager
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: TextRendering (FreeType, Bitmap)
- Addons: Add libpng / libjpg / libdds loaders
- Addons: Scene, Object, Material, SceneRenderer
- Addons: Material instances
- Addons: ParticleSystem
- Addons: EffectComposer, Postprocess effects / shaders
- Defines for debug/release, logs, etc

