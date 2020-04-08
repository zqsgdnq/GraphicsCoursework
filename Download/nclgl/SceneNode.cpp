#include "scenenode.h"


SceneNode::SceneNode(Mesh* m, Vector4 colour)
{
	boundingRadius = 1.0f;
	distanceFromCamera = 0.0f;
	this->mesh = m;
	this->colour = colour;
	parent = NULL;
	modelScale = Vector3(1, 1, 1);
	//initilizaton
}

SceneNode::~SceneNode(void) {
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void SceneNode::AddChild(SceneNode* s) {
	children.push_back(s);
	s->parent = this;
}
void SceneNode::Draw(const OGLRenderer& r) {
	if (mesh) { mesh->Draw(); };
}

void SceneNode::Update(float msec) {
	if (parent) {// This node has a parent ...
		worldTransform = parent->transform * transform;

	}
	else {
		worldTransform = transform;
	}
	for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}
