#include "plight.h"

void plight::Setposition()
{
	lightposition = Vector3(650.0f, 750.0f, 650.0f);
}

void plight::Setambient()
{
	ambient = Vector3(0.2f, 0.2f, 0.2f);
}

void plight::Setdiffuse()
{
	diffuse = Vector3(0.5f, 0.5f, 0.5f);
}

void plight::Setspecular()
{
	specular = Vector3(0.6f, 0.6f, 0.6f);
}