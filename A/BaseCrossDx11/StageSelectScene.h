/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class StageSelectScene : public Stage {
		

		//ビューの作成
		void CreateViewLight();
		void CreatTestLin();
	public:
		//構築と破棄
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	

		
	};


}
//end basecross