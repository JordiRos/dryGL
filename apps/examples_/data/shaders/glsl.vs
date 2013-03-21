precision mediump float;

attribute vec3 Position;
attribute vec2 TexCoord;
uniform mat4 ModelViewProjection;
varying vec2 vUv;

void main(void)
{
    gl_Position = ModelViewProjection * vec4(Position, 1.0);
    vUv = TexCoord;
}
