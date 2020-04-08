#include "object.h"

object::object()
{
	numVertices = 5;
	numIndices = 18;
	vertices = new Vector3[numVertices];
	indices = new GLuint[numIndices];
	colours=new Vector4[numVertices];

	vertices[0] = Vector3(0.0f,0.0f,0.0f);
	vertices[1] = Vector3(0.0f, 0.0f, 20.0f);
	vertices[2] = Vector3(20.0f, 0.0f, 20.0f);
	vertices[3] = Vector3(20.0f, 0.0f, 0.0f);
	vertices[4] = Vector3(10.0f, 15.0f, 10.0f);

	colours[0]= Vector4(1.0f,0.0f, 0.0f, 1.0f);
	colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	colours[3] = Vector4(1.0f, 0.5f, 0.5f, 1.0f);
	colours[4] = Vector4(0.8f, 0.3f, 1.0f, 1.0f);


	unsigned int objindices[] = {
    0,1,2,
	2,3,0,
	1,4,0,
	0,4,3,
	2,3,4,
	1,2,4
};
	this->BufferData();
}
	void object::BufferData()
	{
		glBindVertexArray(arrayObject);
		glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(VERTEX_BUFFER);

		if (textureCoords)
		{
			glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
			glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
			glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(TEXTURE_BUFFER);

		}

		if (colours)
		{
			glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
			glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector4), colours, GL_STATIC_DRAW);
			glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(COLOUR_BUFFER);

		}

		
			glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
				bufferObject[INDEX_BUFFER]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint),
				objindices, GL_STATIC_DRAW);
		
		glBindVertexArray(0);

	}
