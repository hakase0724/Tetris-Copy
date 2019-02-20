#pragma once
#include "Component.h"
#include "TextRenderer.h"

namespace MyDirectX
{
	class DXText :public Component
	{
	public:
		DXText() {};
		~DXText() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		//�\���e�L�X�g�X�V
		void UpdateText(const wchar_t* texts);
	private:
		//�e�L�X�g��\�����郌���_���[�B
		std::vector<TextRenderer*> mRenderers;
		//�t�H���g
		std::wstring mFont = _T("MS P����");
	};
}


