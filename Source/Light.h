#pragma once
#include "Vertex.h"

struct Light final{

	Light(char t = 's' , float x = 0.f, float y = 0.f, float z = 0.f, float r = 1.f, float g = 1.f, float b = 1.f, Vector3 spotDir = Vector3(0.f, 1.f, 0.f)){
		if (t=='d')
			type = LIGHT_TYPE::DIRECTIONAL;
		if (t=='s')
			type = LIGHT_TYPE::SPOT;
		if (t=='p')
			type = LIGHT_TYPE::POINT;

		position.Set(x, y, z);
		color.Set(r, g, b);
		power = 0.f;
		kC = 1.f;
		kL = .01f;
		kQ = .001f;
		cosCutoff = cos(Math::DegreeToRadian(45.f));
		cosInner = cos(Math::DegreeToRadian(30.f));
		exponent = 3.f;
		spotDirection.Set(spotDir.x, spotDir.y, spotDir.z);
	}
	enum class LIGHT_TYPE{
		POINT, DIRECTIONAL, SPOT
	};
	Color color;
	float power, kC, kL, kQ, cosCutoff, cosInner, exponent;
	LIGHT_TYPE type;
	Position position;
	Vector3 spotDirection;
};