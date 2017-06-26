#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ロゴシーン
	//--------------------------------------------------------------------------------------
	class LogoScene : public Stage
	{
	private :
		//計算用時間
		float m_time;
		//透明度
		float m_Alpha;
		//見せてる待機時間
		float m_waitTime;
		//黒幕
		shared_ptr<GameObject> m_Black;

		//今明るいかどうか
		bool m_BlackFlg;
		//状態
		int m_state;
		//現在の画像
		int m_stateTex;
	public :

		//ビューの作成
		void CreateViewLight();

		//構築と破棄
		LogoScene() :Stage() {}
		virtual ~LogoScene();

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}