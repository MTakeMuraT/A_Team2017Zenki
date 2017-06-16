
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------

	void Scene::OnCreate(){
		try {
			//こいつが呼ばれてからステージが呼ばれる
			m_GameMedia  = ObjectFactory::Create<GameMedia>();

			//とりあえず乱数のやつここでやるか
			srand((unsigned)time(NULL));

			//最初のアクティブステージの設定
			//ResetActiveStage<TitleScene>();
			//ResetActiveStage<StageSelectScene>();
			ResetActiveStage<TutorialScene>();

		}
		catch (...) {
			throw;
		}
	}
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		
		if (event->m_MsgStr == L"ToTitleScene") {
			auto TitleScenePtr = dynamic_pointer_cast<TitleScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<TitleScene>();
			}
		}
		
		if (event->m_MsgStr == L"ToStageSelectScene") {
			auto StafeSelectPtr = dynamic_pointer_cast<StageSelectScene>(GetActiveStage());
			if (!StafeSelectPtr) {
				ResetActiveStage<StageSelectScene>();
			}
		}
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTutorial") {
			ResetActiveStage<TutorialScene>();
		}

	}


	//ステージ番号と大きさ設定
	void Scene::SetStageNumAndStageSize(int stagenum, Vector2 stagesize)
	{
		//ステージ番号設定
		m_StageNum = stagenum;

		//ステージサイズ設定
		m_StageSize = stagesize;
	}
}
//end basecross
