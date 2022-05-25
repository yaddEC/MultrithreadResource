#include <GameObject.h>

using namespace LowRenderer;

GameObject::GameObject(string Vname,Mesh* Vmesh, GameObject* Vparent )
{
	mesh = Vmesh;
	parent = Vparent;
	name = Vname;
}

void GameObject::AddChild(GameObject child)
{
	child.parent = this;
}