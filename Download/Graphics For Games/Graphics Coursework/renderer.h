#pragma once
#include "..\..\\nclgl\OGLRenderer.h"
#include "..\..\nclgl\Camera.h"
//#include "desert.h"
#include "..\\..\\nclgl/HeightMap.h"

#include "..\..\\nclgl\Mesh.h"
#include "..\Graphics Coursework\pyramid.h"
#include "..\Graphics Coursework\Plight.h"
#include "..\..\nclgl\MD5Mesh.h"
#include "..\..\nclgl\MD5Node.h"

#include "..//..//nclgl/scenenode.h"
#include "electric.h"


#define SHADOWSIZE 2048

class Renderer :
	public OGLRenderer
{
public:
	Renderer(Window& parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

private:
	void DrawHeightmap();
	void DrawWater();
	void DrawSkybox();
	void DrawMesh();
	void DrawFloor();
	void DrawShadowScene();
	void DrawCombinedScene();
	void Drawpyramid();
	void Drawpost();
	void Drawinverse();
	void Drawgrey();
	void Drawsharp();
	Shader* sceneShader = nullptr;
	Shader* shadowShader = nullptr;
	Shader* deShader = nullptr;
	Shader* inversion = nullptr;
	Shader* grey = nullptr;
	Shader* sharp = nullptr;
	GLuint shadowTex;
	GLuint shadowFBO;
	GLuint posttexture;
	GLuint postframe;
	GLuint rbo;

	MD5FileData* hellData;
	MD5Node* hellNode;
	Shader* lightShader = nullptr;
	Shader* reflectShader = nullptr;
	Shader* skyboxShader = nullptr;
	Shader* fanShader = nullptr;
	Shader* post = nullptr;
	pyramid* p = nullptr;
	Mesh* quad = nullptr;
	HeightMap* heightMap = nullptr;
	Camera* camera = nullptr;
	const Light* light = nullptr;
	Shader* pShader = nullptr;
	GLuint cubeMap;
	plight* Plight = nullptr;
	Mesh* floor = nullptr;
	Mesh* postquad = nullptr;
	Light* sl = nullptr;
	void DrawNode(SceneNode* n);
	Shader* people = nullptr;
	int waterheight = 100;
	SceneNode* root = nullptr;
	float time = 0.0f;
	float waterRotate;
};