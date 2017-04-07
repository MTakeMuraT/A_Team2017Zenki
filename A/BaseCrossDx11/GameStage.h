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

		//ビューの作成
		void CreateViewLight();
		// 背景
		void CreateBackGround();
		void CreateGround();
		void CreatePlate();
		void CreatePlayerLin();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}

		//初期化
		virtual void OnCreate()override;

		// 更新
		virtual void OnUpdate() override;


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

