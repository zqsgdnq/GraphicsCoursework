#include "renderer.h"

Renderer::Renderer(Window& parent) : OGLRenderer(parent)
{
	electric::CreateCube();
	camera = new Camera();
	//camera = new Camera(40, 270, Vector3(1000, 1800, 2500));
	camera->SetPosition(Vector3(RAW_WIDTH * HEIGHTMAP_X / 2.0f-50.0f, 1200.0f, RAW_WIDTH * HEIGHTMAP_X+300.0f));
	p = new pyramid();
	p->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR "gold.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	pShader = new Shader(SHADERDIR"pvertex.glsl", SHADERDIR"pfrag.glsl");
	people = new Shader(SHADERDIR"skeletonvertex.glsl", SHADERDIR"skeFragment.glsl");
	quad = Mesh::GenerateQuad();
	postquad = Mesh::GenerateQuad();
	heightMap = new HeightMap(TEXTUREDIR"terrain.raw");
	light = new Light(Vector3((RAW_HEIGHT * HEIGHTMAP_X / 2.0f), 50.0f, (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f)), Vector4(1.0f, 1.0f, 1.0f, 1.0f), (RAW_WIDTH * HEIGHTMAP_X) / 2.0f);
	Plight = new plight();
	sl = new Light(Vector3(1600.0f, 2000.0f, 900.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), 5500.0f);
	hellData = new MD5FileData(MESHDIR"hellknight.md5mesh");
	hellNode = new MD5Node(*hellData);

	hellData->AddAnim(MESHDIR"idle2.md5anim");
	hellNode->PlayAnim(MESHDIR"idle2.md5anim");


	root = new SceneNode();
	root->AddChild(new electric());
	fanShader = new Shader(SHADERDIR "SceneVertex.glsl ", SHADERDIR "SceneFragment.glsl");
	sceneShader = new Shader(SHADERDIR"shadowscenevert.glsl", SHADERDIR"shadowscenefrag.glsl");
	shadowShader = new Shader(SHADERDIR"shadowVert.glsl", SHADERDIR"shadowFrag.glsl");

	reflectShader = new Shader(SHADERDIR"PerPixelVertex.glsl", SHADERDIR"reflectFragment.glsl");
	skyboxShader = new Shader(SHADERDIR"skyboxVertextest.glsl", SHADERDIR"skyboxFragmenttest.glsl");
	//lightShader = new Shader(SHADERDIR"PerPixelVertex.glsl", SHADERDIR"PerPixelFragment.glsl");
	deShader = new Shader(SHADERDIR"devertex.glsl", SHADERDIR"defrag.glsl");
	post = new Shader(SHADERDIR"postv.glsl", SHADERDIR"postf.glsl"); 
	inversion= new Shader(SHADERDIR"postv.glsl", SHADERDIR"inversef.glsl");
	grey = new Shader(SHADERDIR"postv.glsl", SHADERDIR"grey.glsl");
	sharp = new Shader(SHADERDIR"postv.glsl", SHADERDIR"sharp.glsl");
	if (!reflectShader->LinkProgram() || !skyboxShader->LinkProgram() || !pShader->LinkProgram() || !fanShader->LinkProgram()) {
		return;
	}
	if (!sceneShader->LinkProgram() || !shadowShader->LinkProgram()||!people->LinkProgram()||!deShader->LinkProgram()||
		!post->LinkProgram()|| !inversion->LinkProgram()||!grey->LinkProgram() || !sharp->LinkProgram()) {
		return;
	}

	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWSIZE, SHADOWSIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTex, 0);
	glDrawBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#pragma region postprocessing
	
	glGenTextures(1, &posttexture);
	glBindTexture(GL_TEXTURE_2D, posttexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width/2, height/2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	glGenFramebuffers(1, &postframe);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posttexture, 0);

	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#pragma endregion 


	floor = Mesh::GenerateQuad();
	floor->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"pinkground.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	floor->SetBumpMap(SOIL_load_OGL_texture(TEXTUREDIR"brickDOT3.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	postquad->SetTexture(posttexture);
	quad->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"water.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"pink.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetBumpMap(SOIL_load_OGL_texture(TEXTUREDIR"pink.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	//cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"land_lf.JPG", TEXTUREDIR"land_rt.JPG", TEXTUREDIR"land_up.JPG", TEXTUREDIR"land_dn.JPG", TEXTUREDIR"land_ft.JPG", TEXTUREDIR"land_bk.JPG", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"hangingstone_lf.tga", TEXTUREDIR"hangingstone_rt.tga", TEXTUREDIR"hangingstone_up.tga", TEXTUREDIR"hangingstone_dn.tga", TEXTUREDIR"hangingstone_ft.tga", TEXTUREDIR"hangingstone_bk.tga", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
	if (!cubeMap || !quad->GetTexture() || !heightMap->GetTexture() || !heightMap->GetBumpMap())
	{
		return;
	}

	SetTextureRepeating(quad->GetTexture(), true);
	SetTextureRepeating(heightMap->GetTexture(), true);
	SetTextureRepeating(heightMap->GetBumpMap(), true);
	SetTextureRepeating(p->GetTexture(), true);
	waterRotate = 0.0f;

	projMatrix = Matrix4::Perspective(1.0f, 20000.0f, (float)width / (float)height, 45.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	init = true;
}

Renderer ::~Renderer(void)
{
	glDeleteTextures(1, &shadowTex);
	glDeleteFramebuffers(1, &shadowFBO);
	glDeleteTextures(1, &posttexture);
	glDeleteFramebuffers(1, &postframe);
	delete camera;
	delete heightMap;
	delete quad;
	delete reflectShader;
	delete skyboxShader;
	delete lightShader;
	delete light;
	delete hellData;
	delete hellNode;
	delete floor;
	delete postquad;
	delete sceneShader;
	delete shadowShader;
	delete post;
	delete people;
	delete deShader;
	delete grey;
	currentShader = 0;
	delete root;
	electric::DeleteCube();
}

void Renderer::UpdateScene(float msec)
{
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix();
	waterRotate += msec / 1000.0f;
	waterheight = (waterheight % 100) + 100;
	waterheight += msec / 10;
	heightMap->UpdateHeight(msec);
	root->Update(msec);
	hellNode->Update(msec);
}

void Renderer::RenderScene()
{
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_P)) { Drawpost(); }
	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_I)) { Drawinverse(); }
	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_G)) { Drawgrey(); }
	else if (Window::GetKeyboard()->KeyDown(KEYBOARD_H)) { Drawsharp(); }

	else{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		DrawSkybox();
		DrawHeightmap();
		DrawWater();

		SetCurrentShader(fanShader);
		UpdateShaderMatrices();

		glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "diffuseTex"), 1);
		DrawNode(root);
		glUseProgram(0);
		Drawpyramid();
		DrawShadowScene();
		DrawCombinedScene();
		}
	SwapBuffers();
	

}

void Renderer::Drawpyramid() {
	//glEnable(GL_CULL_FACE);
	SetCurrentShader(pShader);
	glUniform1i(glGetUniformLocation(pShader->GetProgram(), "material.pydiffuse"), 0);

	glUniform3fv(glGetUniformLocation(pShader->GetProgram(), "light.position"), 1, (float*) & (Plight->Getposition()));
	glUniform3fv(glGetUniformLocation(pShader->GetProgram(), "light.ambient"), 1, (float*) & (Plight->Getambient()));
	glUniform3fv(glGetUniformLocation(pShader->GetProgram(), "light.diffuse"), 1, (float*) & (Plight->Getdiffuse()));
	glUniform3fv(glGetUniformLocation(pShader->GetProgram(), "light.specular"), 1, (float*) & (Plight->Getspecular()));
	glUniform3fv(glGetUniformLocation(pShader->GetProgram(), "viewPos"), 1, (float*) & (camera->GetPosition()));

	glUniformMatrix4fv(glGetUniformLocation(pShader->GetProgram(), "projMatrix"), 1, false, (float*)& projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(pShader->GetProgram(), "modelMatrix"), 1, false, (float*) & (p->buildmodel()));
	glUniformMatrix4fv(glGetUniformLocation(pShader->GetProgram(), "viewMatrix"), 1, false, (float*)& viewMatrix);
	glUniform1f(glGetUniformLocation(pShader->GetProgram(), "material.shininess"), 32.0f);

	p->Draw();
	//glUseProgram(0);
	//glDisable(GL_CULL_FACE);
}

void Renderer::DrawSkybox()
{
	glDepthMask(GL_FALSE);
	SetCurrentShader(skyboxShader);

	UpdateShaderMatrices();
	quad->Draw();

	glUseProgram(0);
	glDepthMask(GL_TRUE);
}

void Renderer::DrawHeightmap()
{
	SetCurrentShader(deShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "bumpTex"), 1);
	glUniform1f(glGetUniformLocation(currentShader->GetProgram(), "time"),sin(time));
	time += 0.005f;

	modelMatrix.ToIdentity();
	textureMatrix.ToIdentity();

	UpdateShaderMatrices();
	heightMap->Draw();

	glUseProgram(0);
}

void Renderer::DrawWater()
{
	SetCurrentShader(reflectShader);
	SetShaderLight(*light);

	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "cubeTex"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	float heightX = (RAW_WIDTH * HEIGHTMAP_X / 2.0f);

	float heightY = waterheight * 0.5f / 3.0f;
	float heightZ = (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f);

	modelMatrix = Matrix4::Translation(Vector3(heightX, heightY * 6, heightZ)) * Matrix4::Scale(Vector3(heightX * 10, 10, heightZ * 10)) * Matrix4::Rotation(90, Vector3(1.0f, 0.0f, 0.0f));

	textureMatrix = Matrix4::Scale(Vector3(10.0f, 10.0f, 10.0f)) * Matrix4::Rotation(waterRotate, Vector3(0.0f, 0.0f, 1.0f));

	UpdateShaderMatrices();
	quad->Draw();

	glUseProgram(0);
}

void Renderer::DrawShadowScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, SHADOWSIZE, SHADOWSIZE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	SetCurrentShader(shadowShader);

	viewMatrix = Matrix4::BuildViewMatrix(sl->GetPosition(), Vector3(2500, 200, -1000));
	textureMatrix = biasMatrix * (projMatrix * viewMatrix);
	UpdateShaderMatrices();

DrawMesh();
	
	glUseProgram(0);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glViewport(0, 0, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawCombinedScene()
{
	SetCurrentShader(sceneShader);
	glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "bumpTex"), 1);
	glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "shadowTex"), 2);

	glUniform3fv(glGetUniformLocation(sceneShader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());

	SetShaderLight(*sl);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	viewMatrix = camera->BuildViewMatrix();
	UpdateShaderMatrices();


	DrawMesh();

	DrawFloor();

	glUseProgram(0);
}

void Renderer::DrawMesh()
{
	
	//modelMatrix.ToIdentity();
	modelMatrix = Matrix4::Translation(Vector3(2500, 200, -1000)) * Matrix4::Scale(Vector3(15, 15, 15));
	Matrix4 tempMatrix = textureMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "textureMatrix"), 1, false, *&tempMatrix.values);
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, *&modelMatrix.values);

	hellNode->Draw(*this);
}

void Renderer::DrawFloor()
{

	Matrix4 modelMatrix = Matrix4::Translation(Vector3(4000, 400, -1000)) * Matrix4::Rotation(90, Vector3(1, 0, 0)) * Matrix4::Scale(Vector3(2500, 2500, 1));
	Matrix4 tempMatrix = textureMatrix * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "textureMatrix"), 1, false, tempMatrix.values);
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, modelMatrix.values);

	floor->Draw();
}
void Renderer::DrawNode(SceneNode* n) {
	if (n->GetMesh()) {
		Matrix4 transform = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		//modelMatrix = Matrix4::Translation(Vector3(1000, 5000, 5000));
		glUniformMatrix4fv(glGetUniformLocation(fanShader->GetProgram(), "modelMatrix"), 1, false, (float*)& transform);

		glUniform4fv(glGetUniformLocation(fanShader->GetProgram(), "nodeColour"), 1, (float*)& n->GetColour());

		glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "useTexture"), (int)n->GetMesh()->GetTexture());
		n->Draw(*this);

	}

	for (vector <SceneNode*>::const_iterator
		i = n->GetChildIteratorStart();
		i != n->GetChildIteratorEnd(); ++i) {
		DrawNode(*i);
	}
}

void Renderer::Drawpost() 
{
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSkybox();
	DrawHeightmap();
	DrawWater();
	Drawpyramid();
	//DrawFloor(); 
	//DrawMesh();
	SetCurrentShader(fanShader);
	//UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "diffuseTex"), 1);
	DrawNode(root);
	//glUseProgram(0);

	DrawShadowScene();

	//glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);
	glViewport(0, 0, width / 2, height / 2);
	DrawCombinedScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// glBindFramebuffer(GL_FRAMEBUFFER, 0); -- using the default fbo
	glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	SetCurrentShader(post);
	glUniform1i(glGetUniformLocation(post->GetProgram(), "texture1"), 0);
	glViewport(0, 0, width/2, height/2);
	Matrix4 modelMatrix = Matrix4::Rotation(180.0f,Vector3(0,0,1))* Matrix4::Rotation(180.0f, Vector3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(post->GetProgram(), "model"),1, false, (float*)& modelMatrix);
	postquad->Draw();
	glUseProgram(0);
		
}
void Renderer::Drawinverse()
{
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSkybox();
	DrawHeightmap();
	DrawWater();
	Drawpyramid();
	//DrawFloor(); 
	//DrawMesh();
	SetCurrentShader(fanShader);
	//UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "diffuseTex"), 1);
	DrawNode(root);
	//glUseProgram(0);

	DrawShadowScene();

	//glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);
	glViewport(0, 0, width / 2, height / 2);
	DrawCombinedScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// glBindFramebuffer(GL_FRAMEBUFFER, 0); -- using the default fbo
	glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	SetCurrentShader(inversion);
	glViewport(0, 0, width / 2, height / 2);
	glUniform1i(glGetUniformLocation(inversion->GetProgram(), "texture1"), 0);
	//glViewport(0, 0, 800, 600);
	Matrix4 modelMatrix = Matrix4::Rotation(180.0f, Vector3(0, 0, 1)) * Matrix4::Rotation(180.0f, Vector3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(inversion->GetProgram(), "model"), 1, false, (float*)& modelMatrix);
	postquad->Draw();
	glUseProgram(0);
}

void Renderer::Drawgrey()
	{
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSkybox();
	DrawHeightmap();
	DrawWater();
	Drawpyramid();
	//DrawFloor(); 
	//DrawMesh();
	SetCurrentShader(fanShader);
	//UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "diffuseTex"), 1);
	DrawNode(root);
	//glUseProgram(0);

	DrawShadowScene();

	//glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);
	glViewport(0, 0, width / 2, height / 2);
	DrawCombinedScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// glBindFramebuffer(GL_FRAMEBUFFER, 0); -- using the default fbo
	glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	SetCurrentShader(grey);
	glViewport(0, 0, width / 2, height / 2);
	glUniform1i(glGetUniformLocation(grey->GetProgram(), "texture1"), 0);
	//glViewport(0, 0, 800, 600);
	Matrix4 modelMatrix = Matrix4::Rotation(180.0f, Vector3(0, 0, 1)) * Matrix4::Rotation(180.0f, Vector3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(grey->GetProgram(), "model"), 1, false, (float*)& modelMatrix);
	postquad->Draw();
	glUseProgram(0);

	}
void Renderer::Drawsharp()
{
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSkybox();
	DrawHeightmap();
	DrawWater();
	Drawpyramid();
	//DrawFloor(); 
	//DrawMesh();
	SetCurrentShader(fanShader);
	//UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(fanShader->GetProgram(), "diffuseTex"), 1);
	DrawNode(root);
	//glUseProgram(0);

	DrawShadowScene();

	//glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, postframe);
	glViewport(0, 0, width / 2, height / 2);
	DrawCombinedScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// glBindFramebuffer(GL_FRAMEBUFFER, 0); -- using the default fbo
	glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	SetCurrentShader(sharp);
	glViewport(0, 0, width / 2, height / 2);
	glUniform1i(glGetUniformLocation(sharp->GetProgram(), "texture1"), 0);
	//glViewport(0, 0, 800, 600);
	Matrix4 modelMatrix = Matrix4::Rotation(180.0f, Vector3(0, 0, 1)) * Matrix4::Rotation(180.0f, Vector3(0, 1, 0));
	glUniformMatrix4fv(glGetUniformLocation(sharp->GetProgram(), "model"), 1, false, (float*)& modelMatrix);
	postquad->Draw();
	glUseProgram(0);
}



