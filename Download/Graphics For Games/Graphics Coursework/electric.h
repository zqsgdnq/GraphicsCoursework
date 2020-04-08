#pragma once
#include "..\..\\nclgl\scenenode.h"
#include "..\..\\nclgl\OBJMesh.h"

class electric : public SceneNode {
public:
	electric(void);
	~electric(void) {};
	virtual void Update(float msec);

	static void CreateCube() {
		OBJMesh* m = new OBJMesh();
		m->LoadOBJMesh(MESHDIR"cube.obj");
		cube = m;

	}

	static void DeleteCube() { delete cube; }

protected:
	static Mesh* cube;
	SceneNode* fan1;
	SceneNode* fan2;
	SceneNode* fan3;
	SceneNode* fan4;
};