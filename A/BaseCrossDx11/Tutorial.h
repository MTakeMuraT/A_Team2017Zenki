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

		//地面作成
		void CreateGround();

		//プレイヤー作成
		void CreatePlayer();

		//移動ターゲット作成
		void CreateMoveTarget();

		//回転時間計測オブジェクト作成
		void CreateRotCount();

		//スプライトを作成
		void CreateSpriteS();

		//エネミー作成
		void CreateEnemy();

		//カメラ動くフラグ
		bool m_CameraMoveFlg = true;

		//エネミーの数数えるフラグ
		bool m_EnemyFlg = false;
	public:
		//構築と破棄
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//カメラ更新
		void UpdateCamera();

		//カメラ移動停止
		void CameraStop() { m_CameraMoveFlg = false; }

		//リザルトカメラ処理 引数はキャラの中心
		bool ResultCamera(Vector3 pos);

		void EnemyCountOn() { m_EnemyFlg = true; }

	};

	//--------------------------------------------------------------------------------------
	//	こっから下は専用のオブジェクトだぜぇ～？
	//--------------------------------------------------------------------------------------

	//**************************************************************************************
	//**************************************************************************************


	//**************************************************************************************
	//	チュートリアル専用のプレイヤー、操作制限機能つき
	//	ヘッダーで値設定してもバグルのでクリエイトで作るわ
	//**************************************************************************************
	class TutorialPlayerS : public GameObject
	{
	private :
		//プレイヤー一体目
		shared_ptr<GameObject> m_Player1;
		//プレイヤー二体目
		shared_ptr<GameObject> m_Player2;
		//二体の距離
		float m_PlayerSDistance;
		//二体の距離初期値
		float m_PlayerSDistanceInit;
		//二体の距離最大
		float m_PlayerSDistanceLimit;
		//離れる速度
		float m_DistanceSpeed;
		//くっつく速度
		float m_KuttukuSpeed;

		//回転
		float m_rot;
		//回転速度
		float m_rotSpeed;

		//慣性
		Vector3 m_Kansei;

		//黒幕
		shared_ptr<GameObject> m_BlackSprite;
		//黒幕の透明度
		float m_BlackAlpha;
		//透明になるか
		bool m_BlackAlphaFlg = false;

		//アニメーションの名前
		//更新前
		string m_NowAnimName;
		//更新後
		string m_ChangeAnimName;

		//全部動けなくするフラグ
		bool m_DontMoveFlg = false;

		//くっついてるフラグ
		bool m_KuttukuFlg = false;
		//くっついて戻るフラグ
		bool m_KuttukuAfterFlg = false;

		//位置更新切るフラグ
		bool m_DontMoveFlg2 = false;
		//-----------------------
		//パラメータ類
		//-----------------------
		float m_Speed;


		//-----------------------
		//関数
		//-----------------------
		//プレイヤーたちの座標を更新
		void PosRotUpdate();
		//ステージの外に行こうとしたら戻す判定
		void CheckStageEnd();
		//暗転処理
		void BlackUpdate();
		//アニメーション更新
		void UpdateAnimation();
		//-----------------------
		//制御系
		//-----------------------
		bool m_moveFlg;
		bool m_rotFlg;
		bool m_AButtonFlg;
	public :
		TutorialPlayerS(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//二体の座標を返す
		vector<Vector3> GetPlayerSPos_RETURNvectorVec3();
		//距離を返す
		float GetDistance() { return m_PlayerSDistance; }
		//位置更新オフ
		void DontMove() { m_DontMoveFlg2 = true; }

		//-----------------------
		//制御系
		//-----------------------
		void SetMoveCont(bool flg) { m_moveFlg = flg; }
		void SetRotCont(bool flg) { m_rotFlg = flg; }
		void SetAbuttonCont(bool flg) { m_AButtonFlg = flg; }
	};

	//**************************************************************************************
	//	移動ターゲット
	//	物だけ
	//**************************************************************************************
	class MoveTarget : public GameObject
	{
	private :
		//透明度
		float m_Alpha;
		//状態
		bool m_AlphaFlg = false;
		//動かすか
		bool m_ActiveFlg = false;
	public :
		MoveTarget(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//**************************************************************************************
	//	回転のみ使える状態の時
	//	ある程度回転したら解除
	//**************************************************************************************
	class TutorialRotFixed :public GameObject
	{
	private :
		//計算用時間
		float m_time;
		//制限時間
		float m_LimitTime;
		//計測フラグ
		bool m_StartFlg;
	public :
		TutorialRotFixed(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//制限時間計測開始
		void StartCount();
	};

	//**************************************************************************************
	//	的エネミー
	//	死ぬだけ
	//**************************************************************************************
	class TutorialEnemy : public GameObject
	{
	private :
		//下から出すフラグ
		bool m_UpFlg = false;
		//挟まれる判定するか
		bool m_SandJudgeFlg = false;
	public:
		TutorialEnemy(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//下から出す
		void Up();

		//座標移動
		void SetPos(Vector3 pos) { GetComponent<Transform>()->SetPosition(pos); }
	};

	//**************************************************************************************
	//	スプライトたち
	//	状態変えて出す
	//　大体切り替えで２ステート使うのでNextState()で切り替えたときは２個進める
	//　ここもクリエイトで初期化
	//**************************************************************************************
	class TutorialSpriteS : public GameObject
	{
	private :
		//状態
		int m_state;
		//状態切り替え時
		bool m_ChangestateFlg;
		//時間計測用
		float m_time;
		//切り替え間隔
		float m_IntervalTime;
	public :
		TutorialSpriteS(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void NextSatte();
	};
}