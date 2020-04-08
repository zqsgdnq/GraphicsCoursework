#pragma once


#include <string>
#include <iostream>
#include <fstream>
#include "..\nclgl\mesh.h"




class object : public Mesh {
public:
	object();
	~object() {};
protected:
	void BufferData();
	unsigned int objindices[18];
};