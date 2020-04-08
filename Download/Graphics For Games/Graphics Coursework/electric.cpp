#include"electric.h"

Mesh* electric::cube = NULL;



electric::electric(void) {
	// Optional , uncomment if you want a local origin marker !
		// SetMesh ( cube );
	//cube->SetTexture(SOIL_load_OGL_texture(TEXTUREDIR"desert.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	SceneNode* fan1 = new SceneNode(cube, Vector4(1, 0, 0, 1));
	fan1->SetModelScale(Vector3(20, 500, 20));
	fan1->SetTransform(Matrix4::Translation(Vector3(1800, 2500, -400)) * Matrix4::Rotation(90.0f, Vector3(0, 1, 0)) * Matrix4::Rotation(90.0f, Vector3(0, 0, 1)));
	AddChild(fan1);

	fan2 = new SceneNode(cube, Vector4(0, 1, 0, 1));
	fan2->SetModelScale(Vector3(20, 500, 20));
	fan2->SetTransform(Matrix4::Translation(Vector3(1800, 2500, -400)) * Matrix4::Rotation(180.0f, Vector3(0, 1, 0)) * Matrix4::Rotation(90.0f, Vector3(0, 0, 1)));
	AddChild(fan2);

	fan3 = new SceneNode(cube, Vector4(1, 1, 0, 1));
	fan3->SetModelScale(Vector3(20, 500, 20));
	fan3->SetTransform(Matrix4::Translation(Vector3(1800, 2500, -400)) * Matrix4::Rotation(270.0f, Vector3(0, 1, 0)) * Matrix4::Rotation(90.0f, Vector3(0, 0, 1)));
	AddChild(fan3);

	fan4 = new SceneNode(cube, Vector4(0, 0, 1, 1));
	fan4->SetModelScale(Vector3(20, 500, 20));
	fan4->SetTransform(Matrix4::Translation(Vector3(1800, 2500, -400)) * Matrix4::Rotation(360.0f, Vector3(0, 1, 0)) * Matrix4::Rotation(90.0f, Vector3(0, 0, 1)));
	AddChild(fan4);


	/*leftArm = new SceneNode(cube, Vector4(0, 0, 1, 1)); // Blue !
leftArm -> SetModelScale(Vector3(3, -18, 3));
leftArm -> SetTransform(Matrix4::Translation(Vector3(-12, 30, -1)));
 body -> AddChild(leftArm);

	 rightArm = new SceneNode(cube, Vector4(0, 0, 1, 1)); // Blue !
rightArm -> SetModelScale(Vector3(3, -18, 3));
	rightArm -> SetTransform(Matrix4::Translation(Vector3(12, 30, -1)));
	body -> AddChild(rightArm);

	SceneNode * leftLeg = new SceneNode(cube, Vector4(0, 0, 1, 1)); // Blue !
	leftLeg -> SetModelScale(Vector3(3, -17.5, 3));
 leftLeg -> SetTransform(Matrix4::Translation(Vector3(-8, 0, 0)));
	body -> AddChild(leftLeg);

		SceneNode * rightLeg = new SceneNode(cube, Vector4(0, 0, 1, 1)); // Blue !
rightLeg -> SetModelScale(Vector3(3, -17.5, 3));
	 rightLeg -> SetTransform(Matrix4::Translation(Vector3(8, 0, 0)));
 body -> AddChild(rightLeg);*/
}void electric::Update(float msec) {
	transform = transform * Matrix4::Rotation(msec / 10.0f, Vector3(0, 1, 0));
	//fan1->SetTransform(fan1->GetTransform() *Matrix4::Rotation(-msec / 10.0f, Vector3(0, 1, 0)));

	/*head -> SetTransform(head -> GetTransform() *
	Matrix4::Rotation(-msec / 10.0f, Vector3(0, 1, 0)));
	leftArm -> SetTransform(leftArm -> GetTransform() *
	 Matrix4::Rotation(-msec / 10.0f, Vector3(1, 0, 0)));

		rightArm -> SetTransform(rightArm -> GetTransform() *
			 Matrix4::Rotation(msec / 10.0f, Vector3(1, 0, 0)));*/


	SceneNode::Update(msec);
}