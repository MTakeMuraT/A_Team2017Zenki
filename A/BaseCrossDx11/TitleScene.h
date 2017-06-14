/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		//ビューの作成
		void CreateViewLight();
		void CreateBackGround();

		//状態
		int m_state = 0;

		//時間測る用
		float m_time = 0;

		//選択番号
		int m_selectNum = 0;

		//透明度
		float m_Alpha = 1;

		//透明
		bool m_AlphaFlg = false;
	public:
		//構築と破棄
		TitleScene() :Stage() {}
		virtual ~TitleScene();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
