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
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual bool IsSceneEnd() override;
	private:
		DXSound* mBGM;
		DXGameObject* line;
	};
}

