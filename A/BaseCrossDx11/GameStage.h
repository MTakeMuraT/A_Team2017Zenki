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
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;


		//ビューの作成
		void CreateViewLight();
		// 背景
		void CreateBackGround();
		void CreateGround();
		void CreatePlate();
		void CreatePlayerLin();
		void CreateUILin();
		void CreateChildMissile();
		//テスト時に使用
		void CreateTestLin();

		//タイマー作成
		void CreateTimer();
		//ライフ作成
		void CreateLife();

		//カメラ更新
		void UpdateCamera();

		//アタリ判定作成
		void CreateCollision();

		//Abe20170515
		//ステージの幅
		Vector2 m_StageSize;
		//Abe20170515

		//Abe20170519MukkuMarge
		void CreateEnemyCounts();
		//Abe20170519MukkuMarge


		//Abe20170530
		bool m_CameraMoveFlg = true;
		//Abe20170530

		//Abe20170605
		//ポーズ作成
		void CreatePause();
		//Abe20170605


		//演出に移る時のBGMストップ
		bool StopBGM = true;

		//Abe20170612
		//ダメージ揺れる演出
		bool m_DamageFlg = false;
		//揺らしてる時間測る
		float m_damageTime = 0;
		//揺らす間隔
		float m_damageinterval = 0.02f;
		//揺らす回数
		int m_damageCameraCount = 0;
		//カメラ揺らす演出
		void DamageCamera();
		//Abe20170612

		//Abe20170620
		//ブースト作成
		void CreateBoost();
		//Abe20170620
		bool m_WinBgm = true;
		float m_CuntTaime = 0.0f;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage();

		//初期化
		virtual void OnCreate()override;

		// 更新
		virtual void OnUpdate() override;

		//Abe20170530
		//ゲームオーバー
		void GameOver();

		//ゲームオーバーカメラ処理
		bool GameOverCamera();

		//Abe20170531
		//リザルト
		void Result();

		//リザルトカメラ処理 引数はキャラの中心
		bool ResultCamera(Vector3 pos);
		//Abe20170531

		//Abe20170530
		//カメラ移動停止
		void CameraStop() { m_CameraMoveFlg = false; }
		//Abe20170530

		//Abe20170612
		//カメラダメージ演出起動
		void DamageCameraOn() { m_DamageFlg = true; m_damageCameraCount = 0; m_CameraMoveFlg = false; }
		//Abe20170612

	};

	//地面
	class Ground_GameStage : public GameObject
	{
	private:
		//SP
		Vector3 m_Scale;
		Vector3 m_Positon;
		wstring m_TX_Name;

	public:
		//コンストラクタ
		Ground_GameStage(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Positon ,
			const wstring& TX_Name);

		//デストラクタ
		virtual ~Ground_GameStage() {};

		virtual void OnCreate() override;

	};


}
//end basecross

