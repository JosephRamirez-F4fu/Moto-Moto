#version 130

in vec4 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;
out vec4 color;

uniform float time;
uniform sampler2D myImage;

void main(){
	//color = vec3(0.0,1.0,1.0);
	//color = fragmentColor;

	vec4 textureColor = texture(myImage,fragmentUV);

	color = fragmentColor + vec4(
		1.0*(cos(time)+1.0)*0.5,
		1.0*(cos(time+2.0)+1.0)*0.5,
		1.0*(sin(time+1.0)+1.0)*0.5,
		0
	) * textureColor;
}