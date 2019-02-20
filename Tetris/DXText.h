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
		//表示テキスト更新
		void UpdateText(const wchar_t* texts);
	private:
		//テキストを表示するレンダラー達
		std::vector<TextRenderer*> mRenderers;
		//フォント
		std::wstring mFont = _T("MS P明朝");
	};
}


