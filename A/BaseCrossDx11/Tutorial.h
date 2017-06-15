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
	public:
		//構築と破棄
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//カメラ更新
		void UpdateCamera();
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
	public :
		MoveTarget(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}