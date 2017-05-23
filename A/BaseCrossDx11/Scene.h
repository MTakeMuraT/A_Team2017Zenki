/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	class GameMedia;

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//リソースを最初に呼ぶため作成
		shared_ptr<GameMedia> m_GameMedia;

		//Abe20170515
		//ステージ番号
		int m_StageNum = 0;
		//ステージの幅
		Vector2 m_StageSize = Vector2(50,50);
		//Abe20170515

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;

		virtual void OnEvent(const shared_ptr<Event>& event) override;
		
		//Abe20170515
		//ステージ番号とステージサイズを設定
		void SetStageNumAndStageSize(int stagenum, Vector2 stagesize);
		//ステージサイズアクセサー
		Vector2 GetStageSize() { return m_StageSize; }
		//ステージ番号アクセサー
		int GetStageNum() { return m_StageNum; }
		//Abe20170515

	};

}

//end basecross
