#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "..\nclgl\Vector3.h"
#include "..\nclgl\Vector4.h"
class plight
{
public:
	plight() {
		lightposition = Vector3(1700.0f, 2100.0f, 1000.0f);
		ambient = Vector3(0.2f, 0.2f, 0.2f);
		diffuse = Vector3(0.5f, 0.5f, 0.5f);
		specular = Vector3(0.6f, 0.6f, 0.6f);
	}
	void Setposition();
	Vector3 Getposition() { return lightposition; }

	void Setambient();
	Vector3 Getambient() { return ambient; }


	void Setdiffuse();
	Vector3 Getdiffuse() { return diffuse; };

	void Setspecular();
	Vector3 Getspecular() { return specular; };

private:
	Vector3 lightposition;

	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;




};
