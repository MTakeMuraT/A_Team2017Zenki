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
		
		AddGameObject<TitleSprite>(Vector2(1280, 720),Vector2(0, 0));

		SetSharedGameObject(L"PressStart",AddGameObject<PressSprite>(Vector2(512, 512),Vector2(0, -190)));
		
		//土台作成
		auto obj = AddGameObject<GameObject>();
		auto Trans = obj->AddComponent<Transform>();
		Trans->SetPosition(0, -190, 0);
		Trans->SetScale(500, 250, 1);
		Trans->SetRotation(0, 0, 0);

		auto Draw = obj->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"TITLEDODAI_TX");

		obj->SetDrawLayer(2);
		obj->SetAlphaActive(true);

		SetSharedGameObject(L"Dodai", obj);
		SetSharedGameObject(L"TitleSE", AddGameObject<SE>());


		//AddGameObject<InputCSV>();
	}

	void TitleScene::OnCreate() {
		try {
			////検証するのに重いので一時的に消します Abe20170505
			//m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			//m_AudioObjectPtr->AddAudioResource(L"Title_01_BGM");
			//m_AudioObjectPtr->Start(L"Title_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			

			//ビューとライトの作成
			CreateViewLight();
			//背景の作成
			CreateBackGround();	
			//AddGameObject<DimSprite>(true,
			//	Vector2(1280, 720),
			//	Vector2(0, 0));

			m_time = 0;
		}
		
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//ロゴシーンに戻るカウント
		m_logocounttime += App::GetApp()->GetElapsedTime();
		if (m_logocounttime > 30)
		{
			//シーン切り替え
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//ロゴシーン
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToLogoScene");

			m_logocounttime = 0;
		}
		//コントローラ
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//**********************
		//コマンド
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK && CntlVec[0].wButtons & XINPUT_GAMEPAD_START)
		{
			//シーンリロード
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
		}
		//**********************

		switch (m_state)
		{
		case 0:
			if (true)
			{
				if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
				{
					m_state = 1;
					//ロゴカウントリセット
					m_logocounttime = 0;
				}

			}
			break;
		case 1:
			if (true)
			{
				//ちょっと待って次の状態へ
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > 1.5f)
				{
					m_state = 2;
					m_time = 0;

					//プレススタート消す
					GetSharedGameObject<GameObject>(L"PressStart", false)->SetDrawActive(false);
				}
			}
			break;
			//チュートリアルとゲーム始める作成
		case 2:
			if (true)
			{
				//上入ればもうできてるから一個だけ
				if (!GetSharedGameObject<GameObject>(L"GameStart",false))
				{
					//ゲームスタート作成
					auto obj = AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, -260, 0);
					Trans->SetScale(350, 150, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"TITLEGAMESTART_TX");

					obj->SetDrawLayer(3);
					obj->SetAlphaActive(true);

					SetSharedGameObject(L"GameStart", obj);

					//チュートリアル作成
					obj = AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, -180, 0);
					Trans->SetScale(350, 145, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"TITLETUTORIAL_TX");

					obj->SetDrawLayer(3);
					obj->SetAlphaActive(true);

					SetSharedGameObject(L"Tutorial", obj);
				}
				else
				{
					GetSharedGameObject<GameObject>(L"GameStart", false)->SetDrawActive(true);
					GetSharedGameObject<GameObject>(L"Tutorial", false)->SetDrawActive(true);

				}

				//状態変更
				m_state = 3;
			}
			break;
			//上下で選択
		case 3:
			if (true)
			{
				//上選択
				if (CntlVec[0].fThumbLY > 0.5f || KeylVec.m_bPressedKeyTbl[VK_UP])
				{
					if (OneSeFlg == true) {
						GetSharedGameObject<SE>(L"TitleSE", false)->SetSeFlg_CURSORMOVE(false);
						GetSharedGameObject<SE>(L"TitleSE", false)->StickSe();
						OneSeFlg = false;
					}
					m_selectNum = 0;
					GetSharedGameObject<GameObject>(L"Dodai", false)->GetComponent<Transform>()->SetPosition(Vector3(0, -190, 0));

					GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
					GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//消えてくフラグ
					m_AlphaFlg = false;

					//透明度再設定
					m_Alpha = 1.0f;

					//ロゴカウントリセット
					m_logocounttime = 0;
				}
				//下選択
				if (CntlVec[0].fThumbLY < -0.5f || KeylVec.m_bPressedKeyTbl[VK_DOWN])
				{
					//ここSE
					if (OneSeFlg == false) {
						GetSharedGameObject<SE>(L"TitleSE", false)->SetSeFlg_CURSORMOVE(false);
						GetSharedGameObject<SE>(L"TitleSE", false)->StickSe();
						OneSeFlg = true;
					}
					m_selectNum = 1;
					GetSharedGameObject<GameObject>(L"Dodai", false)->GetComponent<Transform>()->SetPosition(Vector3(0, -270, 0));

					GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
					GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//消えてくフラグ
					m_AlphaFlg = false;

					//透明度再設定
					m_Alpha = 1.0f;

					//ロゴカウントリセット
					m_logocounttime = 0;

				}

				//ボタン押された
				if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
				{
					GetSharedGameObject<SE>(L"TitleSE", false)->ASe();

					//ロゴカウントリセット
					m_logocounttime = 0;

					m_state = 4;
					GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
					GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//SS起動
					auto ptr = GetSharedGameObject<SceneChangeSS>(L"SceneChangeSS", false);
					if (!ptr)
					{
						auto ptr2 = AddGameObject<SceneChangeSS>();
						ptr2->OnAnim();
						ptr2->SetDrawLayer(5);
						SetSharedGameObject(L"SceneChangeSS", ptr2);
					}

					//シーン切り替え
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					//２秒待つ
					if (m_selectNum == 0)
					{
						//チュートリアル
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTutorial");
					}
					else if (m_selectNum == 1)
					{
						//ステセレ
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
					}
					return;
				}

				//戻る適当-----------------------------------------------
				if (KeylVec.m_bPressedKeyTbl['B'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_B)
				{
					m_state = 0;
					//プレススタートだす
					GetSharedGameObject<GameObject>(L"PressStart", false)->SetDrawActive(true);
					GetSharedGameObject<GameObject>(L"GameStart", false)->SetDrawActive(false);
					GetSharedGameObject<GameObject>(L"Tutorial", false)->SetDrawActive(false);

					//カーソル位置調整
					m_selectNum = 0;
					GetSharedGameObject<GameObject>(L"Dodai", false)->GetComponent<Transform>()->SetPosition(Vector3(0, -190, 0));


					//ロゴカウントリセット
					m_logocounttime = 0;

				}


				//点滅
				switch (m_selectNum)
				{
				case 0:
					if (true)
					{
						if (!m_AlphaFlg)
						{
							m_Alpha += -App::GetApp()->GetElapsedTime();
							GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha <= 0)
							{
								m_Alpha = 0;
								m_AlphaFlg = true;
							}
						}
						else
						{
							m_Alpha += App::GetApp()->GetElapsedTime() * 2;
							GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha >= 1)
							{
								m_Alpha = 1;
								m_AlphaFlg = false;
							}
						}
					}
					break;
				case 1:
					if (true)
					{
						if (!m_AlphaFlg)
						{
							m_Alpha += -App::GetApp()->GetElapsedTime();
							GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha <= 0)
							{
								m_Alpha = 0;
								m_AlphaFlg = true;
							}
						}
						else
						{
							m_Alpha += App::GetApp()->GetElapsedTime() * 2;
							GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha >= 1)
							{
								m_Alpha = 1;
								m_AlphaFlg = false;
							}
						}
					}

					break;
				}

			}
			break;
			//点滅
		case 4:
			if (true)
			{
				//点滅
				switch (m_selectNum)
				{
				case 0:
					if (true)
					{
						if (!m_AlphaFlg)
						{
							m_Alpha += -App::GetApp()->GetElapsedTime() * 3;
							GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha <= 0)
							{
								m_Alpha = 0;
								m_AlphaFlg = true;
							}
						}
						else
						{
							m_Alpha += App::GetApp()->GetElapsedTime() * 6;
							GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha >= 1)
							{
								m_Alpha = 1;
								m_AlphaFlg = false;
							}
						}
					}
					break;
				case 1:
					if (true)
					{
						if (!m_AlphaFlg)
						{
							m_Alpha += -App::GetApp()->GetElapsedTime() * 3;
							GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha <= 0)
							{
								m_Alpha = 0;
								m_AlphaFlg = true;
							}
						}
						else
						{
							m_Alpha += App::GetApp()->GetElapsedTime() * 6;
							GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

							if (m_Alpha >= 1)
							{
								m_Alpha = 1;
								m_AlphaFlg = false;
							}
						}
					}

					break;

				}
				break;
			}
		}
		//if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
		//	auto ptr = GetSharedGameObject<SceneChangeSS>(L"SceneChangeSS", false);
		//	if (!ptr)
		//	{
		//		auto ptr2 = AddGameObject<SceneChangeSS>();
		//		ptr2->OnAnim();
		//		SetSharedGameObject(L"SceneChangeSS", ptr2);
		//	}
		//	auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//	//２秒待つ
		//	PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");

		//}
	}
	//破棄
	 TitleScene::~TitleScene() {
		// m_AudioObjectPtr->Stop(L"Title_01_BGM");
	}
	 SE::SE(const shared_ptr<Stage>& StagePtr) :
		 GameObject(StagePtr)
	 {}
	 void SE::OnCreate() {
		 //SE//オーディオリソース登録
		 auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		 pMultiSoundEffect->AddAudioResource(L"Decision_01_SE");
		 pMultiSoundEffect->AddAudioResource(L"CURSORMOVE_SE");
		 pMultiSoundEffect->AddAudioResource(L"Pause_SE");

	 }
	 void SE::ASe() {
		 if (SeFlg_Decision_01 == false) {
			 auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			 pMultiSoundEffect->Start(L"Decision_01_SE", 0, 1.0f);
			 SeFlg_Decision_01 = true;
		 }
	 }
	 void SE::StickSe() {

		 if (SeFlg_CURSORMOVE == false) {
			 auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			 pMultiSoundEffect->Start(L"CURSORMOVE_SE", 0, 1.0f);
			 SeFlg_CURSORMOVE = true;
		 }
	 }
	 void SE::PauseSe() {
		 auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
		 pMultiSoundEffect->Start(L"Pause_SE", 0, 1.0f);
		 SeFlg_Pause = true;
	 }
	 void SE::PauseCloseSe() {
		 auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
		 pMultiSoundEffect->Start(L"Pause_SE", 0, 1.0f);
		 SePauseCloseSe = true;
	 }

}
//end basecross
