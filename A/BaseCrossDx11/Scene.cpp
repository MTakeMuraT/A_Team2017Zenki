
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

			

			//最初のアクティブステージの設定
			ResetActiveStage<TitleScene>();
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
	
	}

}
//end basecross
