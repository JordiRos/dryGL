dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current status:
- iOS project
- FreeImage loader
- Texture
- Shader
- BasicShader example
- Camera: CameraPerspective, CameraOrthogonal
- FBO
- Addons/QuadBatch: simple quad drawing, later on it will be a real quadbatch pipeline

Example:
- Rotating 3D cube + cameraPerspective + cameraOrthogonal + FBO (not working)

Dependencies:
- Glm
- FreeImage

Roadmap:
- Renderer utilities (clear, viewports, renderstates, etc)
- VBO object
- Auto uniforms/attributes in shader
- Mesh
- State/Render manager
- Inheritable basic shader
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: Add libpng / libjpg / libdds loaders
- Addons: Scene, Object, Material, SceneRenderer
- Addons: EffectComposer, Postprocess effects / shaders
