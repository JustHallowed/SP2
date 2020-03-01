#version 330 core

//Interpolated values from vertex shader
in vec2 texCoord;
in vec3 vertexPosition_cameraspace, fragmentColor, vertexNormal_cameraspace;

//Ouput data
out vec4 color;

struct Light{
	float power, kC, kL, kQ, cosCutoff, cosInner, exponent;
	int type;
	vec3 color, position_cameraspace, spotDirection;
};

struct Material{
	float kShininess;
	vec3 kAmbient, kDiffuse, kSpecular;
};

float getAttenuation(Light light, float dist){
	return 1 / (light.type == 1 ? 1 : max(1, light.kC + light.kL * dist + light.kQ * dist * dist));
}

float getSpotlightEffect(Light light, vec3 lightDirection){
	vec3 L = normalize(lightDirection), S = normalize(light.spotDirection);
	float cosDirection = dot(L, S);
	//return smoothstep(light.cosCutoff, light.cosInner, cosDirection);
	return float(cosDirection >= light.cosCutoff); //pow(cosDirection, light.exponent);
}

const int MAX_LIGHTS = 8;

//Values that stay constant for the whole mesh
uniform bool colorTextureEnabled, lightEnabled, textEnabled;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform sampler2D colorTexture;
uniform vec3 textColor;
uniform float alpha;

void main(){
	vec4 materialColor = (colorTextureEnabled ? texture2D(colorTexture, texCoord) : vec4(fragmentColor, 1.f));
	if(lightEnabled){
		vec3 eyeDirection_cameraspace = -vertexPosition_cameraspace, E = normalize(eyeDirection_cameraspace), N = normalize(vertexNormal_cameraspace);
		color = materialColor * vec4(material.kAmbient, 1); //Ambient (simulates indirect lighting)
		for(int i = 0; i < numLights; ++i){
			vec3 lightDirection_cameraspace = lights[i].position_cameraspace - vertexPosition_cameraspace * (~lights[i].type & 1);
			float spotlightEffect = (lights[i].type == 2 ? getSpotlightEffect(lights[i], lightDirection_cameraspace) : 1.f);
			vec3 L = normalize(lightDirection_cameraspace), R = reflect(-L, N);
			float distToLight = length(lightDirection_cameraspace), attenuationFactor = getAttenuation(lights[i], distToLight), cosTheta = clamp(dot(N, L), 0, 1), cosAlpha = clamp(dot(E, R), 0, 1);
			vec4 diffuse = materialColor * vec4(material.kDiffuse, 1) * vec4(lights[i].color, 1) * lights[i].power * cosTheta * attenuationFactor * spotlightEffect; //"colour" of obj
			vec4 specular = vec4(material.kSpecular, materialColor.a) * vec4(lights[i].color, 1) * lights[i].power * pow(cosAlpha, material.kShininess) * attenuationFactor * spotlightEffect; //reflective highlight of obj
			color += diffuse + specular;
		}
	} else{
		color = materialColor;
		if(color.a >= 0.05f && color.a < 1.f){
			color.a = alpha;
		}
	}
	if(textEnabled){
		color *= vec4(textColor, 1);
	}
}