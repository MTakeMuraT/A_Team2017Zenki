/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//むっくん
	//--------------------------------------------------------------------------------------
	///	タイトルのスプライト
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		TitleSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TitleSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
	};


	//--------------------------------------------------------------------------------------
	///	ぷれすえにーきーのスプライト
	//--------------------------------------------------------------------------------------
	class PressSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;

		bool lighton = true;


	public:
		float m_alpha = 0.05;
		float Max = 2.0f;

		//--------------------------------------------------------------------------------------
		PressSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		virtual ~PressSprite();
		//--------------------------------------------------------------------------------------

		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------

		virtual void OnUpdate()override;
		virtual void OnLastUpdate() override;

	};


	//ゆーすけくん
	//--------------------------------------------------------------------------------------
	//	class StageSelectSprite : public GameObject;
	//	用途: シーン表示系統
	//--------------------------------------------------------------------------------------
	class StageSelectSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		int m_Num;

	public:
		StageSelectSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos,
			const int& Number);
		virtual ~StageSelectSprite();
		virtual void OnCreate() override;

	};
	class DimSprite : public GameObject {
		bool m_Trace;
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionColor> m_BackupVertices;
	public:
		float dim = 0;
		bool dimon;
		DimSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vector2& StartScale, const Vector2& StartPos);
		virtual ~DimSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	class TestLin : public GameObject;
	//	用途: シーン表示テスト系統
	//--------------------------------------------------------------------------------------
	class TestLin : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
		int m_Type;
	public:
		//構築と破棄
		TestLin(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position,
			const int& Type
		);
		virtual ~TestLin();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
	//	class FixdBox : public GameObject;
	//	用途: エネミーテスト用
	//--------------------------------------------------------------------------------------
	class FixdBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
		wstring m_TX_Name;
		bool Inserted = false;
		float Speed_F = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0, 0, 0);
	public:
		//構築と破棄
		FixdBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position,
			const wstring& TXName);
		virtual ~FixdBox() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnLastUpdate()override;
		void InputStick();
	};


	//--------------------------------------------------------------------------------------
	//	class Dedug : public GameObject;
	//	用途: ステージシーン　
	//--------------------------------------------------------------------------------------
	class Dedug : public GameObject {
		

	public:
		//構築と破棄
		Dedug(const shared_ptr<Stage>& StagePtr
		);
		virtual ~Dedug();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//操作
	};

	//--------------------------------------------------------------------------------------
	//	class Enemy01 : public GameObject;
	//	用途: エネミー1　
	//--------------------------------------------------------------------------------------
	//Abe20170412
	class Enemy01 : public GameObject 
	{
	private :
		//気絶フラグ
		bool m_StanFlg = false;
		//挟まれてるフラグ
		bool m_SandFlg = false;
		//気絶してる時間
		float m_StanTime = 0;
		//座標
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
		//飛ばす力
		float m_VeloPower = 100;
		//力
		Vector3 m_Vel;
	public :
		Enemy01(const shared_ptr<Stage>& StagePtr,Vector3 Pos,Vector3 Scale);
		Enemy01(const shared_ptr<Stage>& StagePtr, const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		//ダメージ状態時
		void DamageState();
		//プレイヤーが離れたとき
		void Release();
		//当てられた時のほう
		void Release(Vector3 vel);
		//ダメージ受けたとき
		void Damage(float Time);
		//プレイヤーから時間持ってくる版 Player_RGetATimeは仮
		//void Damage(){m_StanFlg = true; GetStage()->GetSharedGameObject<Player>(L"Player_R")->GetATime();}

		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;

		bool GetStanFlg() { return m_StanFlg; }


		//テスト用の挟まれた後の処理
		void SandAfter() { SetDrawActive(false); };
	};
	//Abe20170412

	//Abe20170519
	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	用途: ポーズ
	//--------------------------------------------------------------------------------------
	class PauseMenu : public GameObject
	{
	private:
		//ポーズ背景(暗幕)
		shared_ptr<GameObject> m_PauseBackBlack;
		//ポーズ背景(残存勢力)
		shared_ptr<GameObject> m_PauseBackEnemyS;
		//選択項目

	public:

	};
	//Abe20170519

	//Abe20170418
	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
	//　生成したら桁増えるごとに左にずれてく
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject
	{
	private:
		//なんかしらんメッシュのリスト
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//桁数
		int m_digit = 0;
		//生成されてる数字
		int m_Constdigit = 0;
		//表示レイヤー
		int m_layer = 0;
		//大きさ
		Vector2 m_scale;
		//位置
		Vector2 m_pos;
		//数字分のvector配列
		vector<shared_ptr<GameObject>> m_Numbers;

		//調整用
		//文字と文字の間隔
		float IntervalNums = 1.8f;
	public:
		NumberSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;

		/*以前試作してたものだけど使わなそうなので消しときます
		//位置調整
		void SetPositionVec2(Vector2 pos);
		//大きさ調整
		void SetScaleVec2(Vector2 scale);
		*/

		//数字設定
		void SetNum(int num);

		void SetNumDraw(bool flg);
	};

	//--------------------------------------------------------------------------------------
	//	class Timer : public GameObject;
	//	用途:タイマー
	//　位置設定、大きさはスプライトなのでVec2で使う
	//--------------------------------------------------------------------------------------

	class Timer : public GameObject
	{
	private:
		//初期位置
		Vector2 m_InitPos;
		//大きさ
		Vector2 m_InitScale;
		//レイヤー
		int m_LayerNum;
		//制限時間
		int m_InitTime;
		//現在時間
		float m_Time;
		//時間止めるフラグ
		bool m_TimeStopFlg = false;
		//終わったか
		bool m_FinishFlg = false;
		//数字
		shared_ptr<NumberSprite> m_Numbers;
	public:
		//初期時間、座標、大きさ、レイヤー
		Timer(const shared_ptr<Stage>& StagePtr, int Time, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

		void SetTimer(bool flg);

		bool GetTimerFlg() { return m_FinishFlg; }
	};

	//--------------------------------------------------------------------------------------
	//	class Player_Life : public GameObject;
	//	用途:プレイヤーのHP
	//--------------------------------------------------------------------------------------
	class Player_Life :public GameObject
	{
	private:
	
		bool m_DieFlg = true;

		//現在地
		int m_Life = 10;
		//最大値
		int m_LifeMax = 10;
		//座標
		Vector2 m_InitPos;
		//大きさ
		Vector2 m_InitScale;
		//レイヤー
		int m_layer;
		//ライフスプライト
		vector<shared_ptr<GameObject>> m_LifeSprite;
		//フレーム・・・は増やすってなったら追加するか

		//調整用
		//間隔
		float m_IntervalLife = 0.45f;
	public:
		Player_Life(const shared_ptr<Stage>& StagePtr, int LifeNum, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;

		//入力した値分ライフから引く
		void LifeDown(int num);

		int GetLife() { return m_Life; }
		bool GetDieFlg() {
			return m_DieFlg;
		}
		
		
	};
	//Abe20170418
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	スプライトの大きさ、位置を確認するオブジェクト
	//--------------------------------------------------------------------------------------
	class SpritePosScaleChecker : public GameObject
	{
	private:
		//座標
		Vector3 m_pos;
		//大きさ
		Vector3 m_scale;
		//レイヤー
		int m_layer;
		//テクスチャの名前
		wstring m_texturename;
	public:
		SpritePosScaleChecker(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer, wstring txtname);

		void OnCreate()override;
		void OnUpdate()override;
	};
	//Abe20170421

	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	デバッグ文字表示するオブジェクト
	//--------------------------------------------------------------------------------------
	class DebugTxt : public GameObject 
	{
	private:
		//大きさ(枠)
		Vector2 m_Scale;
		//座標
		Vector2 m_Pos;
		//大きさ(文字)
		int m_ScaleTxt;
	public :
		DebugTxt(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		//文字設定
		void SetText(wstring txt);
		//大きさ(枠)設定
		void SetScale(Vector2);
		//座標設定
		void SetPos(Vector2);
		//大きさ(文字)設定
		void SetScaleTxt(int);
		//レイヤー設定
		void SetLayer(int);
		//色設定
		void SetColor(Vector3);
	};

	//Abe20170427


	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChild : public GameObject;
	//	用途: ミサイルを撃つ子機
	//--------------------------------------------------------------------------------------
	class ShotEnemyChild : public GameObject
	{
	private:
		Vector3 m_Scale = Vector3(0, 0, 0);
		Vector3 m_Position;
		Vector3 m_Rotation = Vector3(0, 0, 0);
		Vector3 m_ReferencePoint_Vec3 = Vector3(0, 0, 0);//ミサイル発射の基準点　
		Vector3 m_ReferencePoint2_Vec3 = Vector3(0, 0, 0);//ミサイル発射の基準点２
		Vector3 m_CenterPoint_Vec3 = Vector3(0, 0, 0);//センター（向きを取得時に使用
		Vector3 m_Distance = Vector3(0, 0, 0);//回転で使用
		Vector3 m_NewReferencePoint_Vec3 = Vector3(0, 0, 0);
		Vector3 m_NewReferencePoint2_Vec3 = Vector3(0, 0, 0);
		Vector3 m_NewCenterPoint_Vec3 = Vector3(0, 0, 0);
		Quaternion m_Angle;
		Vector3 m_Direction_Vec3 = Vector3(0, 0, 0);
		float m_T_Angle = 0.0f;
		//発射間隔
		float m_ShotInterval = 0.0f;
		//bool m_ShotFlg = false;

		//デバックミサイル発射場所の位置確認用　（別クラスに値を送る用
		Vector3 m_Debug = Vector3(0, 0, 0);
		Vector3 m_getPos = Vector3(0, 0, 0);
		Vector3 m_getPos2 = Vector3(0, 0, 0);
		Vector3 m_getCenter = Vector3(0, 0, 0);
		float m_Time = 0.0f;
		int m_cout = 0;

		//挟まれてたら
		bool m_ShotEnemyChildSandFlg = false;
		//向き変更 完了tore　未完了false
		bool m_DefaultRot_F = true;

		//Abe20170517
		//撃ち始めるかどうか
		bool m_ShotFlg = false;
		//投げられてる最中
		void Tobu();
		//加速度
		Vector3 m_Velocity;
		//Abe20170517
	public:
		ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const float& ShotInterval);
		ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const wstring& line);
		virtual ~ShotEnemyChild() {};
		void OnCreate() override;
		void OnUpdate() override;
		void OnLastUpdate()override;
		void ShotEnemyChildRot();
		void PintNewPos();
		void DoingSandRotation();
		void Shot();
		Vector3 Direction();
		void SetShotFlg(bool m_Shot) { m_ShotFlg = m_Shot; };
		bool GetShotFlg() { return m_ShotFlg; };
		float GetAngle() { return m_T_Angle; }
		//デバックゲッター
		Vector3 GetPos(bool flg) {
			if (flg) {
				return m_getPos;
			}
			else {
				return m_getPos2;
			}
		}
		Vector3 InitialPos(bool flg) {
			if (flg) {
				return m_ReferencePoint_Vec3;
			}
			else {
				return m_ReferencePoint2_Vec3;
			}
		}
		Vector3 GetDirection() {
			return m_getCenter;
		}
		bool GetShotEnemyChildSandFlg() {
			return m_ShotEnemyChildSandFlg;
		}
		void SetShotEnemyChildSandFlg(bool flg) {
			m_ShotEnemyChildSandFlg = flg;
		}


		//Abe20170517
		//加速度設定
		void SetVelocity(Vector3 vel)
		{
			m_Velocity = vel;
		}
		//Abe20170517

	};
	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChildMissile : public GameObject;
	//	用途: ミサイルを撃つ子機（ミサイル）
	//--------------------------------------------------------------------------------------
	class ShotEnemyChildMissile : public GameObject {
	private:
		Vector3 m_Position;
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Direction;
		float m_Speed = 100;
		float m_AttackDamage;
		float m_DeleteTime;
		bool m_ShotActive;
	public:
		ShotEnemyChildMissile(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const Vector3& Rotation, const Vector3& Direction);
		virtual ~ShotEnemyChildMissile() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//移動
		void ChildMissileMove();
		//消える処理
		void ObjDelete();
		//攻撃力のアクセサ
		float GetChildMissileAttackDamage() {
			return  m_AttackDamage;
		}
		//撃つか撃たないか
		void SetShotActive(bool ShotTrue) {
			m_ShotActive = ShotTrue;
		}
		bool GetShotActive() {
			return m_ShotActive;
		}
	};

	//Abe20170519MukkuMargeNumberSpriteと同じ処理だったのでそっちで代用
	/*
	//--------------------------------------------------------------------------------------
	//	class EnemyCountSprite : public GameObject;
	//	用途: 残敵数のスプライト表示
	//--------------------------------------------------------------------------------------
	class EnemyCountSprite : public GameObject {
	private:
		//なんかしらんメッシュのリスト
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//桁数
		int m_digit = 0;
		//生成されてる数字
		int m_Constdigit = 0;
		//表示レイヤー
		int m_layer = 0;
		//大きさ
		Vector2 m_scale;
		//位置
		Vector2 m_pos;
		//数字分のvector配列
		vector<shared_ptr<GameObject>> m_Numbers;

		//調整用
		//文字と文字の間隔
		float IntervalNums = 1.8f;
	public:
		EnemyCountSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;

		/*以前試作してたものだけど使わなそうなので消しときます
		//位置調整
		void SetPositionVec2(Vector2 pos);
		//大きさ調整
		void SetScaleVec2(Vector2 scale);
		*/
	/*
		//数字設定
		void SetNum(int num);

		void SetNumDraw(bool flg);

	};
	*/
	//Abe20170519MukkuMargeNumberSpriteと同じ処理だったのでそっちで代用

	////////////////////////

	class EnemyCountA : public GameObject
	{
	private:
		//初期位置
		Vector2 m_InitPos;
		//大きさ
		Vector2 m_InitScale;
		//レイヤー
		int m_LayerNum;
		//数字
		shared_ptr<NumberSprite> m_Numbers;
		//最大数
		shared_ptr<NumberSprite> m_MaxNumber;

		int m_EnemyCunt = 0;
		int m_EnemyMaxCount = 0;
	public:
		//座標、大きさ、レイヤー
		EnemyCountA(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

	};

	//Abe20170519MukkuMarge一つでまとめられるのでEnemyCountAのほうにまとめ
	/*
	class EnemyCountB : public GameObject
	{
	private:
		//初期位置
		Vector2 m_InitPos;
		//大きさ
		Vector2 m_InitScale;
		//レイヤー
		int m_LayerNum;
		//時間止めるフラグ
		bool m_TimeStopFlg = false;
		//終わったか
		bool m_FinishFlg = false;
		//数字
		shared_ptr<NumberSprite> m_Numbers;

		int m_EnemyCunt = 0;

		int m_MaxCount = 0;
	public:
		//初期時間、座標、大きさ、レイヤー
		EnemyCountB(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

		//void SetTimer(bool flg);

		bool GetTimerFlg() { return m_FinishFlg; }
	};

	*/
}
//end basecross