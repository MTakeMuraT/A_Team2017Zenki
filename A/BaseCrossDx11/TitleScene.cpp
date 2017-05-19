/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/
//プレイヤーのLookAtCameraをMyLookAtCameraに変更すれば治る
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	void TitleScene::CreateBackGround() {
		
		AddGameObject<TitleSprite>(
			Vector2(1280, 720),
			Vector2(0, 0)
			);
		AddGameObject<PressSprite>(
			Vector2(512, 512),
			Vector2(0, -155)
			);
		
		//AddGameObject<InputCSV>();
	}

	void TitleScene::OnCreate() {
		try {
			/*//検証するのに重いので一時的に消します Abe20170505
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"Title_01_BGM");
			m_AudioObjectPtr->Start(L"Title_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			*/

			//ビューとライトの作成
			CreateViewLight();
			//背景の作成
			CreateBackGround();	
			AddGameObject<DimSprite>(true,
				Vector2(1280, 720),
				Vector2(0, 0));
		}
		
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//コントローラ
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
		}
	}
	//破棄
	 TitleScene::~TitleScene() {
		 //m_AudioObjectPtr->Stop(L"Title_01_BGM");
	}

}
//end basecross
