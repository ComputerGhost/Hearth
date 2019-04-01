#pragma once

#include "../Core/Scene.hpp"

namespace Scenes
{
	class TestScene : public ::Core::Scene
	{
	public:
		TestScene();

		void initialize();

		void onAttach();
		void onUpdate(double elapsed);
	};
}
