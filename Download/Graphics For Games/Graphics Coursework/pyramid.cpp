#include "pyramid.h"

pyramid::pyramid() {

	numVertices = 12;
	
	vertices = new Vector3[numVertices];
	
	textureCoords = new Vector2[numVertices];
	normals = new Vector3[numVertices];
	

	



	vertices[0] = Vector3(0.0f, 1.0f, 0.0f);
	vertices[1] = Vector3(1.0f, 0.0f, 1.0f);
	vertices[2] = Vector3(1.0f, 0.0f, -1.0f);

	vertices[3] = Vector3(0.0f, 1.0f, 0.0f);
	vertices[4] = Vector3(-1.0f, 0.0f, 1.0f);
	vertices[5] = Vector3(1.0f, 0.0f, 1.0f);

	vertices[6] = Vector3(0.0f, 1.0f, 0.0f);
	vertices[7] = Vector3(-1.0f, 0.0f, -1.0f);
	vertices[8] = Vector3(-1.0f, 0.0f, 1.0f);

	vertices[9] = Vector3(0.0f, 1.0f, 0.0f);
	vertices[10] = Vector3(-1.0f, 0.0f, -1.0f);
	vertices[11] = Vector3(1.0f, 0.0f, -1.0f);

	textureCoords[0] = Vector2(0.5f, 1.0f);
	textureCoords[1] = Vector2(0.0f, 0.0f);
	textureCoords[2] = Vector2(1.0f, 0.0f);
	textureCoords[3] = Vector2(0.5f, 1.0f);
	textureCoords[4] = Vector2(0.0f, 0.0f);
	textureCoords[5] = Vector2(1.0f, 0.0f);
	textureCoords[6] = Vector2(0.5f, 1.0f);
	textureCoords[7] = Vector2(0.0f, 0.0f);
	textureCoords[8] = Vector2(1.0f, 0.0f);
	textureCoords[9] = Vector2(0.5f, 1.0f);
	textureCoords[10] = Vector2(0.0f, 0.0f);
	textureCoords[11] = Vector2(1.0f, 0.0f);

	normals[0] = Vector3(2, 2, 0);
	normals[1] = Vector3(2, 2, 0);
	normals[2] = Vector3(2, 2, 0);

	normals[3] = Vector3(0, 2, 2);
	normals[4] = Vector3(0, 2, 2);
	normals[5] = Vector3(0, 2, 2);

	normals[6] = Vector3(-2, 2, 0);
	normals[7] = Vector3(-2, 2, 0);
	normals[8] = Vector3(-2, 2, 0);

	normals[9] = Vector3(0, 2, -2);
	normals[10] = Vector3(0, 2, -2);
	normals[11] = Vector3(0, 2, -2);

	BufferData();
}

Matrix4 pyramid::buildmodel()
{
	return
		Matrix4::Translation(Vector3(200.0f, 500.0f, -200.0f)) *
		Matrix4::Scale(Vector3(1500.0, 2000.0, 1500.0));

}