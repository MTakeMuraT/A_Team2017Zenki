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
	void StageSelectScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 30.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//テスト表示
	void StageSelectScene::CreatTestLin() {
		AddGameObject<StageSelectSprite>(
			Vector2(1280, 720),
			Vector2(0, 0),
			0
			);
	}

	//Abe20170421
	//フレーム作成
	void StageSelectScene::CreateFlame()
	{
		AddGameObject<SelectFlame>(Vector2(0, 0), Vector2(1280, 720), 1);
	}

	//プレイヤー作成
	void StageSelectScene::CreatePlayer()
	{
		SetSharedGameObject(L"SelectPlayer", AddGameObject<SelectPlayer>(Vector3(0, 0, 0), Vector3(1, 1, 1),20.0f));
	}

	//ステージボックス作成
	void StageSelectScene::CreateStageBox()
	{
		AddGameObject<StageBox>(Vector3(0,0,0),Vector3(1,1,1),1);
	}

	//ステージ行くかチェックするスプライト
	void StageSelectScene::CreateGoCheck()
	{
		SetSharedGameObject(L"GoStageCheck", AddGameObject<GoStageCheck>(Vector2(200, 200)));
	}
	//Abe20170421

	void StageSelectScene::OnCreate()
	{
		try {
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"StageSelect_01_BGM");
			m_AudioObjectPtr->Start(L"StageSelect_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);

			CreateViewLight();
			//CreatTestLin();
			//Abe20170421
			//フレーム作成
			CreateFlame();
			//プレイヤー作成
			CreatePlayer();
			//ステージボックス作成
			CreateStageBox();
			//ステージ行くかチェックするスプライト
			CreateGoCheck();
			//Abe20170421


			//デバッグ用の文字
			SetSharedGameObject(L"DebugTxt", AddGameObject<DebugTxt>());
		}
		catch (...) {

			throw;
		}
	}

	void StageSelectScene::OnUpdate() {
		//キーの入力
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
		}

		//Abe20170427
		//カメラ移動
		if (m_moveCameraFlg)
		{
			CameraMove();
		}

		/*カメラ座標確認用*/
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY);
			auto View = GetView();
			auto CameraP = View->GetTargetCamera();
			m_CameraPos = CameraP->GetEye();
			m_CameraAt = CameraP->GetAt();
			m_CameraPos += Vector3(InputXY.x,0,InputXY.y);
			m_CameraAt += Vector3(InputXY.x, 0, InputXY.y);
			CameraP->SetEye(m_CameraPos);
			CameraP->SetAt(m_CameraAt);
			
			/*
			wstring txt;
			txt += L"X:" + Util::FloatToWStr(m_CameraPos.x) + L"Z:" + Util::FloatToWStr(m_CameraPos.z);
			GetSharedGameObject<DebugTxt>(L"DebugTxt",false)->SetText(txt);
			*/
		}
		//Abe20170427
	}

	//Abe20170427
	//カメラ移動関数
	void StageSelectScene::CameraMove()
	{
		
	}

	void StageSelectScene::MoveCamera(int num)
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//ターゲット設定
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();
		//カメラ移動0：上に　1：右に　2：下に　3：左に
		switch (num)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}
	//Abe20170427

	 StageSelectScene::~StageSelectScene() {
		 m_AudioObjectPtr->Stop(L"StageSelect_01_BGM");
	}
}
//end basecross
