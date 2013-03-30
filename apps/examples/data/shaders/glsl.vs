precision mediump float;

attribute vec3 Position;
attribute vec2 TexCoord;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
varying vec2 vUv;

void main(void)
{
    gl_Position = Projection * View * Model * vec4(Position, 1.0);
    vUv = TexCoord;
}
