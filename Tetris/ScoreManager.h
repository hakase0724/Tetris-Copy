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
		void AddScore(int eraseLineCount, int level, bool isTspin, bool isTspinMini);
		void AddScore(int score) { *mScoreRP + score; }
		void Start();
	private:
		Scene* mScene;
		DXGameObject* mScoreTextObject;
		DXGameObject* mScoreTextObject2;
		DXText* mScoreText;
		DXText* mScoreText2;
		std::unique_ptr<ReactiveProperty<int>, Deleter> mScoreRP;
		const int cOneLine = 100;
		const int cTwoLine = 300;
		const int cThreeLine = 500;
		const int cFourLine = 800;
		const int cTspinMini = 100;
		const int cTspinSingle = 400;
		const int cTspinDouble = 700;
		const int cTspinTriple = 1100;
	};
}


