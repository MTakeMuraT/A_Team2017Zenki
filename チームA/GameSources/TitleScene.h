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
	class TitleScene : public Stage {
		
		//ビューの作成
		void CreateViewLight();

	public:
		
		//構築と破棄
		TitleScene() :Stage() {}
		virtual ~TitleScene() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
