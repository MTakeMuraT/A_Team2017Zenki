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

		//Abe20170421
		//フレーム作成
		void CreateFlame();
		//プレイヤー作成
		void CreatePlayer();
		//ステージボックス作成
		void CreateStageBox();
		//ステージ行くか確認するスプライト
		void CreateGoCheck();
		//Abe20170421
	public:
		//構築と破棄
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	

		
	};


}
//end basecross