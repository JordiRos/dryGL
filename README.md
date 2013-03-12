dryGL
=====

dryGL is a lightweight OpenGL ES 2.0 framework for mobile devices, targeting iOS & Android

Current status:
- iOS project
- Texture object
- Shader object + BasicShader
- Camera + CameraPerspective + CameraOrthogonal
- FBO (not working)
- Addons/QuadBatch for simple quad drawing

Example:
- Rotating 3D cube + cameraPerspective + cameraOrthogonal

Dependencies:
- Glm
- FreeImage

Roadmap:
- VBO object
- FBO object
- Auto uniforms/attributes in shader
- Mesh object / renderer
- State manager
- Inheritable basic shader
- Debug functions (DebugDrawText, DebugDrawRectangle, etc)
- Addons: Replace FreeImage with libpng / libjpg / libdds loaders
- Addons: Scene, Object, Material, SceneRenderer
