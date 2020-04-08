#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "..//..//nclgl/Mesh.h"


class pyramid :public Mesh
{
public:
	pyramid();
	~pyramid() {};
	Matrix4 buildmodel();
};