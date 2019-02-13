#pragma once
#include "DXText.h"
#include "ReactiveProperty.h"
#include "Scene.h"
using namespace MyObservarPattern;
namespace MyDirectX 
{
	class ScoreManager
	{
	public:
		ScoreManager(Scene* scene);
		~ScoreManager() {};
		void AddScore(int score) { *mScoreRP + score; }
		void Start();
	private:
		Scene* mScene;
		DXGameObject* mScoreTextObject;
		DXGameObject* mScoreTextObject2;
		DXText* mScoreText;
		DXText* mScoreText2;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mScoreRP;
	};
}


