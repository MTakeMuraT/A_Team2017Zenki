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
	//	class Dedug : public GameObject;
	//	用途: ステージシーン　ステージ選択の写真を乗せる奴
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
}
//end basecross
