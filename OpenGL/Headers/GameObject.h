#pragma once
#include <Mesh.h>
#include <Maths.h>

namespace LowRenderer
{
	class GameObject
	{
	private:
		Mesh* mesh;

	public:
		string name;
		GameObject* parent;
		vector <GameObject> childrens;
		GameObject(string Vname, Mesh* Vmesh, GameObject* Vparent =nullptr);
		void AddChild(GameObject child);
		~GameObject() {};
	};
}