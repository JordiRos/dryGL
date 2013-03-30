// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

precision mediump float;

uniform vec3      iResolution;     // viewport resolution (in pixels)
uniform float     iGlobalTime;     // shader playback time (in seconds)
uniform samplerCube iChannel0;

vec3 sampleHemisphere(float u1, float u2, vec3 normal)
{
  vec3 u = normal;
  vec3 v = abs(u.y) < abs(u.z) ? vec3(0.0, 1.0, 0.0) : vec3(0.0, 0.0, 1.0);
  vec3 w = normalize(cross(u, v));
  v = cross(w, u);

  float r = sqrt(u1);
  float theta = 2.0 * 3.1415926535 * u2;
  float x = r * cos(theta);
  float y = r * sin(theta);
  return normalize(u * sqrt(1.0 - u1) + v * x + w * y);
}

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 intersectSphere(vec3 rpos, vec3 rdir)
{
  vec3 op = vec3(0.0, 0.0, 0.0) - rpos;
  float rad = 5.0;
  
  float eps = 1e-5;
  float b = dot(op, rdir); 
  float det = b*b - dot(op, op) + rad*rad; 
    
  if (det > 0.0)
  {
    det = sqrt(det);
    float t = b - det;
    if (t > eps)
      return vec4(normalize(rpos+rdir*t), t);
  }
  
  return vec4(0.0);
}

vec3 diffuse(vec3 n)
{ 
  vec3 col = vec3(0.0);
  for (float i = 0.0; i < 4.0; i++)
    for (float j = 0.0; j < 8.0; j++)   
    {
      vec2 s = vec2(i, j)+vec2(sin(iGlobalTime))*gl_FragCoord.xy;
      float u = (rand(n.xy+s)+i)*0.25;
      float v = (rand(n.yz+s)+j)*0.125;
      
      vec3 ns = sampleHemisphere(u*0.5, v, n);
      col += pow(textureCube(iChannel0, ns).rgb, vec3(2.2));
    }
  
  return col * 0.25 * 0.125;
}

vec3 rotate(vec3 p, float theta)
{
  return vec3(p.x * cos(theta) + p.z * sin(theta), p.y,
        p.z * cos(theta) - p.x * sin(theta));
}

vec3 trace(vec3 rayPos, vec3 rayDir)
{
  vec3 col = pow(textureCube(iChannel0, rayDir).rgb, vec3(2.2));
  
  vec4 r = intersectSphere(-rayPos, rayDir);
  
  if (r.w > 0.0)
  {
    vec3 n = r.xyz;
    vec3 diff = diffuse(n);
    vec3 spec = pow(textureCube(iChannel0, reflect(rayDir, n)).rgb, vec3(2.2));
    
    float costheta = -dot(n, rayDir);
    
    float f = 1.0 - pow(1.0 - clamp(costheta, 0.0, 1.0), 5.0);
    
    col = mix(spec, diff, f);
  }
  
  return col;
}

vec3 camera(vec2 px)
{
  vec2 rd = (px / iResolution.yy - vec2(iResolution.x/iResolution.y*0.5-0.5, 0.0)) * 2.0 - 1.0;
  
  float time = iGlobalTime * 0.2;
  vec3 rayDir = rotate(normalize(vec3(rd.x, rd.y, 1.0)), time);
  vec3 rayPos = rotate(vec3(0.0, 0.0, 10.0), time);
    
  return trace(rayPos, rayDir);
}

void main(void)
{
  /// Set to 1 to apply AA
  #if 1
  vec3 col = vec3(0.0);
  
  for (float x = 0.0; x < 1.0; x += 0.5)
    for (float y = 0.0; y < 1.0; y += 0.5)
      col += camera(gl_FragCoord.xy + vec2(x, y)) * 0.25;
  #else
  vec3 col = camera(gl_FragCoord.xy);
  #endif
    
  gl_FragColor = vec4(pow(col, vec3(0.4545)), 1.0);
}