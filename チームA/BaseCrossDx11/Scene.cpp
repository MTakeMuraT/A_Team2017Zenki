
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
			m_GameMedia = ObjectFactory::Create<GameMedia>();

			//最初のアクティブステージの設定
			ResetActiveStage<TitleScene>();
		}
		catch (...) {
			throw;
		}
	}
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//タイトル
		if (event->m_MsgStr == L"ToTitleScene") {
			auto TitleScenePtr = dynamic_pointer_cast<TitleScene>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<TitleScene>();
			}
		}
		//ゲームステージ（仮）
		if (event->m_MsgStr == L"ToGameScene") {
			auto TitleScenePtr = dynamic_pointer_cast<GameStage>(GetActiveStage());
			if (!TitleScenePtr) {
				ResetActiveStage<GameStage>();
			}
		}

	}

}
//end basecross
