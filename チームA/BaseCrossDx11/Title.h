#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトル
	//--------------------------------------------------------------------------------------
	class Title : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};


}
