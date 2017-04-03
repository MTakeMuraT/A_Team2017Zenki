/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage
	{

		//ビューの作成
		void CreateViewLight();
		// 背景
		void CreateBackGround();
		void CreatePlate();


	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}

		//初期化
		virtual void OnCreate()override;

		// 更新
		virtual void OnUpdate() override;


	};


}
//end basecross

