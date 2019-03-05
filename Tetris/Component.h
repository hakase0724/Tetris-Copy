#pragma once
#include <string>
#include "MyStructs.h"
#include "MyEnums.h"


namespace MyDirectX
{
	class DXGameObject;

	//�R���|�[�l���g�N���X
	//���̃N���X���p�������N���X��DXGameObject�ɒǉ����Ă���
	class Component
	{
	public:
		//����������
		virtual void Initialize(DXGameObject* gameObject) {};
		virtual void Initialize() {};
		//�X�V����
		virtual void Update() {};
		virtual void LateUpdate() {};
		//�`�揈��
		virtual void Render() {};
		//�������
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
