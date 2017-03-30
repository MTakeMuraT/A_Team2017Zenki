/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{


	//--------------------------------------------------------------------------------------
	///	固定のボックス
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
		int m_Num;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position,
			const int& Number
		);
		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
	};
	
	////--------------------------------------------------------------------------------------
	////	class Black : public GameObject;
	////	用途: フェードアウト（黒）
	////--------------------------------------------------------------------------------------
	//class BlackOut : public GameObject
	//{
	//private:
	//	float m_alpha = 1;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	BlackOut(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//暗転起動
	//	void StartBlack();

	//	//暗転したかどうか取得
	//	bool GetBlackFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class White : public GameObject;
	////	用途: フェードアウト（白）
	////--------------------------------------------------------------------------------------
	//class WhiteOut : public GameObject
	//{
	//private:
	//	float m_alpha = 1;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	WhiteOut(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//暗転起動
	//	void StartWhite();

	//	//暗転したかどうか取得
	//	bool GetWhiteFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class BlackIN : public GameObject;
	////	用途: フェードイン（黒）
	////--------------------------------------------------------------------------------------
	//class BlackIn : public GameObject
	//{
	//private:
	//	float m_alpha = 0;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	BlackIn(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//暗転起動
	//	void StartBlackIn();

	//	//暗転したかどうか取得
	//	bool GetBlackInFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class WhiteIN : public GameObject;
	////	用途: フェードイン（白）
	////--------------------------------------------------------------------------------------
	//class WhiteIn : public GameObject
	//{
	//private:
	//	float m_alpha = 0;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	WhiteIn(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//暗転起動
	//	void StartWhiteIn();

	//	//暗転したかどうか取得
	//	bool GetWhiteInFinish();
	//};

}
//end basecross
