#version 330 core

in vec3 fragmentColor;

out vec4 color;

uniform float particleLife;

void main(){
	color = vec4(fragmentColor, particleLife);
}