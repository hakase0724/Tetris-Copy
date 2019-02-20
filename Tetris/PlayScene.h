#pragma once
#include "Scene.h"
#include "DXText.h"
#include "DXTexture.h"
#include "ReactiveProperty.h"
#include "FieldManager.h"
#include "TetriMinoController.h"
#include "ScoreManager.h"
#include "TetriMinoNext.h"

using namespace MyObservarPattern;

namespace MyDirectX
{
	class PlayScene :public Scene
	{
	public:
		PlayScene() {};
		~PlayScene() {};
		virtual void Init() override;
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual void SceneEnd() override;
		virtual bool IsSceneEnd() override;
	private:
		//エフェクト待機フレーム
		const int cWaitFrame = 60;
		//待機を始めたフレーム数を格納するための変数
		int mWaitStartFrame;
		//UI要素生成
		void CreateUIItem();
		//フレーム計測用
		int mFrameCount;
		//FPS表示更新フレーム数
		const int FPS_CHEACK_FRAME_COUNT = 60;
		//FPS表示テキスト
		DXText* mFPSText;
		//Tスピン時に表示するUI
		DXGameObject* mTspinUI;
		//Tスピンミニ時に表示するUI
		DXGameObject* mTspinMiniUI;
		//シーン開始時にアクティブにするオブジェクト
		std::vector<DXGameObject*> mAwakeObject;
		//フィールド管理
		std::unique_ptr<FieldManager> mFieldManager;
		//盤面操作
		std::unique_ptr<TetriMinoController> mTetriMinoController;
		//スコア管理
		std::unique_ptr<ScoreManager> mScoreManager;
		//Next表示
		std::unique_ptr<TetriMinoNext> mNext;
		//エイリアステンプレートを使って名前を短縮
		using Property = ReactiveProperty<double>;
		//FPS表示に使う変数
		std::unique_ptr<Property, Deleter> mFPSRP;
		//BGM
		DXSound* mBGM;
		//消去時の音
		DXSound* mDeleteSound;
		//今現在のプレイシーンの状態
		PlaySceneState mState = Play;
	};
}


