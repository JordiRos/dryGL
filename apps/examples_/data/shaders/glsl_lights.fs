precision mediump float;

uniform float time;
varying vec2 vUv;


void main(void)
{    
	vec2 uPos = vUv;
	uPos.x -= 1.0;
	uPos.y -= 0.5;
	
	vec3 color = vec3(0.0);
	float vertColor = 1.0;
	for( float i = 0.0; i < 5.0; ++i )
	{
		float t = time * (0.9);
		uPos.y += sin( uPos.x*i + t+i/2.0 ) * 0.1;
		float fTemp = abs(1.0 / uPos.y / 100.0);
		vertColor += fTemp;
		color += vec3( fTemp*(10.0-i)/10.0, fTemp*i/10.0, pow(fTemp,1.5)*1.5 );
	}
	gl_FragColor = vec4(color, 1.0);
}