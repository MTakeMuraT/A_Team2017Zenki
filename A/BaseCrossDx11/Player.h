
/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"



namespace basecross {
	

	//--------------------------------------------------------------------------------------
	///	プレイヤーコントロール
	//--------------------------------------------------------------------------------------
	class PlayerControl : public GameObject
	{
	private:
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
	public:
		PlayerControl(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//二体の座標を返す
		vector<Vector3> GetPlayerSPos_RETURNvectorVec3();
		//距離を返す
		float GetDistance() { return m_PlayerSDistance; }
		//位置更新オフ
		void DontMove() { m_DontMoveFlg2 = true; }
		//当たり判定
		void SetActiveCollision(bool flg);
		
	};

	
	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	用途: スカイボックスの背景
	//--------------------------------------------------------------------------------------
	class SkySphere : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
	public:
		//構築と破棄
		SkySphere(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position
		);
		virtual ~SkySphere();
		//初期化
		virtual void OnCreate() override;
		//操作
	};
	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	用途:プレイヤーパーティクル
	////--------------------------------------------------------------------------------------
	//class  PlayerParticle :public GameObject
	//{
	//private:
	//	//初期位置
	//	Vector3 m_InitPos = Vector3(0,0,0);
	//	//大きさ
	//	Vector3 m_Scale = Vector3(0, 0, 0);
	//	//作成する間隔
	//	float m_CreateInterval = 0.0f;
	//	//テクスチャの名前
	//	wstring m_TextureName;
	//	//消滅演出
	//	bool m_DeleteFlg = false;
	//	//現在パーティクルを出しているかどうか
	//	bool m_NowParticleFlg = false;
	//	//レイヤー
	//	int m_Layer = 0;
	//	//消える時間
	//	float m_DeleteTime = 1.0f;
	//	//float m_Count = 0.0f;
	//	//パーティクルデータ
	//	vector<shared_ptr<GameObject>> m_Particle;
	//	vector<int>m_DeleteIntvec;
	//	bool flg = true;
	//public:
	//	PlayerParticle(const shared_ptr<Stage>& StagePtr);
	//	~PlayerParticle() {};
	//	virtual void OnUpdate() override;
	//	//初期位置、大きさ、テクスチャの名前、消える時間,作成間隔、レイヤー、消える時間
	//	void OnParticle(Vector3 InitPos, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int Layer, float deleteTime);
	//	void CreateParticle();

	//};
	////--------------------------------------------------------------------------------------
	////	class PlayerShield : public GameObject;
	////	用途シールド演出
	////--------------------------------------------------------------------------------------
	class PlayerShield : public GameObject
	{
	private:
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scele = Vector3(0, 0, 0);
		float m_Opacity = 0.0f;
		shared_ptr<GameObject> m_Player;
		float m_OpacityColor = 1.0f;
		bool m_Once = true;
		bool InitHpSaveflg = true;
		bool m_OnShield = false;
		//HPの保存
		int m_HPSave = 0;
	public:
		PlayerShield(const shared_ptr<Stage>& StagePtr, const Vector3& Pos ,const Vector3& Scele, shared_ptr<GameObject> Player);
		~PlayerShield() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};



	
	////--------------------------------------------------------------------------------------
	////	class PlayerBoost : public GameObject;
	////	用途:プレイヤーブースト
	////--------------------------------------------------------------------------------------
	class  PlayerBoost :public GameObject
	{
	 private:
		Vector3 m_InitPos = Vector3(0, 0, 0);
		Vector3 m_scale = Vector3(0, 0, 0);
		wstring m_TextureName;

		float m_DeleteTime = 0.0f;
		float m_CuntTime = 0.0f;
		int m_PlusTimeSpeed = 0;
		 public:
			 PlayerBoost(const shared_ptr<Stage>& StagePtr,const Vector3& InitPos,const Vector3& scale,const wstring& TextureName,const int& DeleteTime, const int& PlusTimeSpeed);
		 	~PlayerBoost() {};
			virtual void OnCreate() override;
		 	virtual void OnUpdate() override;
	};


	

	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	用途: プレイヤーHPの処理
	//--------------------------------------------------------------------------------------
	class PlayerHP : public GameObject {
	private:
		//無敵用
		bool m_invincible_b = false;
		float InvinciblecCunt = 0.0f;
		float InvinciblecLimit = 3.0f;
		//敵との接触
		bool m_Hit_b = false;
		//ダメージ
		int m_Damage_int = 0;
		public:
		//構築と破棄
		PlayerHP(const shared_ptr<Stage>& StagePtr
		);
		virtual ~PlayerHP();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
		bool GetInvincible() {
			return m_invincible_b;
		}
		void SetInvincible(bool Hit_flg) {
			m_invincible_b = Hit_flg;
		}
		bool GetHit() {
			return m_Hit_b;
		}
		void SetHit(bool Hit) {
			m_Hit_b = Hit;
		}
		int  GetDamage_int() {
			return m_Damage_int;
		}
		void SetDamage_int(int Damage) {
			m_Damage_int = Damage;
		}
	};
	
	//--------------------------------------------------------------------------------------
	//	PlayerブーストSP スプライトスタジオ
	//--------------------------------------------------------------------------------------
	class PlayerBoostSP : public SS5ssae
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		Vector3 m_Rotation;
	public:
		PlayerBoostSP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, Vector3 Rotation);
		~PlayerBoostSP() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	
}
//end basecross
