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
		

	public:

		//--------------------------------------------------------------------------------------
		PressSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		virtual ~PressSprite();
		//--------------------------------------------------------------------------------------

		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------

		virtual void OnUpdate()override {}
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
		//気絶してる時間
		float m_StanTime = 0;
		//座標
		Vector3 m_InitPos;
		//大きさ
		Vector3 m_Scale;
	public :
		Enemy01(const shared_ptr<Stage>& StagePtr,Vector3 Pos,Vector3 Scale);

		void OnCreate() override;
		void OnUpdate() override;

		//ダメージ状態時
		void DamageState();
		//ダメージ受けたとき
		void Damage(float Time) { if (!m_StanFlg) { m_StanFlg = true; m_StanTime = Time * 3; } }
		//プレイヤーから時間持ってくる版 Player_RGetATimeは仮
		//void Damage(){m_StanFlg = true; GetStage()->GetSharedGameObject<Player>(L"Player_R")->GetATime();}
	};
	//Abe20170412

}
//end basecross
