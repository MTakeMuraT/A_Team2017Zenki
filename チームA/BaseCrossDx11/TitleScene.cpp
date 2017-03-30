/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);

		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		/*auto PtrWhiteOut = AddGameObject<WhiteOut>();
		SetSharedGameObject(L"WhiteOut", PtrWhiteOut);*/
	}

	void TitleScene::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
	}
	
	void TitleScene::OnUpdate() {
	//	auto PtrWhiteIn = GetSharedGameObject<WhiteOut>(L"WhiteOut");
	//	//デバックキー
	//	//キーボードの取得
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			//		PtrWhiteIn->StartWhite();
			//	}
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//	if (PtrWhiteIn->GetWhiteFinish()) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameScene");
		}
	}

}
//end basecross
