#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクト
	//--------------------------------------------------------------------------------------
	class StageSelectScene : public Stage {
		//ビューの作成
		void CreateViewLight();

	public:
		//構築と破棄
		StageSelectScene() :Stage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
