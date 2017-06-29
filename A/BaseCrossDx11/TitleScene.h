/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class SE :public GameObject
	{
	private:
		bool SeFlg_Decision_01 = false;
		bool SeFlg_CURSORMOVE = false;
		bool SeFlg_Pause = false;
		bool SePauseCloseSe = false;
	public:
		void ASe();
		void StickSe();
		SE(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override; 
		void SetSeFlg_CURSORMOVE(bool OnTrue) { SeFlg_CURSORMOVE = OnTrue; };
		//ポーズ
		void PauseSe();
		void PauseCloseSe();

	};

	
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

		//ロゴまで切り替える時間
		float m_logocounttime = 0;
		//選択時のスティック上下のSEの連続を断ち切る用
		bool OneSeFlg = false;

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
