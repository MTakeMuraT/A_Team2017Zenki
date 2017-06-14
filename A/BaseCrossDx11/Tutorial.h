#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TutorialScene : public Stage {

		//ビューの作成
		void CreateViewLight();

	public:
		//構築と破棄
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}