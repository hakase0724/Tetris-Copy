#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class TitleScene :public Scene
	{
	public:
		TitleScene() {};
		~TitleScene() {};
		virtual void Init() override;
		virtual bool IsSceneEnd() override;
	};
}

