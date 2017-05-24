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
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;


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

		//Abe20170524
		//ステージの床作成
		void CreateStageUnder();
		//Abe20170524

		//Abe20170427
		//カメラ移動フラグ
		bool m_moveCameraFlg = false;
		//カメラ目標座標
		Vector3 m_CameraMoveTarget;
		//カメラ座標
		Vector3 m_CameraPos;
		//注視点
		Vector3 m_CameraAt;
		//カメラ移動関数
		void CameraMove();
		//Abe20170427

		//Abe20170524
		//デバッグ文字表示オブジェ
		shared_ptr<GameObject> m_Debugtxt;
		//カメラ移動時のプレイヤー移動先
		Vector3 m_CameraMovePlayerTargetPos;
		//今のカメラの位置
		int m_CameraNum = 5;
		//Abe20170524

	public:
		//構築と破棄
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//Abe20170427
		//カメラ移動0：上に　1：右に　2：下に　3：左に
		void MoveCamera(int num);
		//Abe20170427

	};


}
//end basecross