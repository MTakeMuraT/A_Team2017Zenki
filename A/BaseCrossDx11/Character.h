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
	};
	//Abe20170412

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

}
//end basecross
