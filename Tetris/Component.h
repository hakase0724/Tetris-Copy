#pragma once
#include <string>
#include "MyStructs.h"
#include "MyEnums.h"


namespace MyDirectX
{
	class DXGameObject;

	//コンポーネントクラス
	//このクラスを継承したクラスをDXGameObjectに追加していく
	class Component
	{
	public:
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) {};
		virtual void Initialize() {};
		//更新処理
		virtual void Update() {};
		virtual void LateUpdate() {};
		//描画処理
		virtual void Render() {};
		//解放処理
		virtual void Exit() {};
		virtual void OnEnable() {};
		virtual void OnDisable() {};
		std::string GetName() { return mName; }
		UINT GetID() { return mId; }
		Tag GetTag() const { return mTag; }
		void SetTag(Tag tag) { mTag = tag; }
		DXGameObject* GetGameObject() const { return mGameObject; }
		void SetEnable(bool enable) { mEnable = enable; }
		bool GetEnable() const { return mEnable; }
		virtual ~Component() {};
	protected:
		DXGameObject* mGameObject;
		std::string mName;
		UINT mId;
		Tag mTag;
		bool mEnable = true;
	};
}
