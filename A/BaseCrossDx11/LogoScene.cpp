#include "stdafx.h"
#include "Project.h"

//*******************************************
//　作成開始日 2017 / 06 / 26
//	土台作成者	Abe
//	ひとこと：やっとおわる、これでおわる♪
//*******************************************

namespace basecross
{

#pragma region LogoScene

	//ビューとライトの作成
	void LogoScene::CreateViewLight() {
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

	void LogoScene::OnCreate()
	{
		try
		{
			//ビューとライトの作成
			CreateViewLight();
		}

		catch (...) {
			throw;
		}
		//初期化---------------------
		m_time = 0;
		m_Alpha = 1;
		m_state = 1;
		m_stateTex = 0;
		m_waitTime = 3.0f;
		//初期化---------------------

		//関数作るまでもないと思うからここに書くは
		auto obj = AddGameObject<GameObject>();
		auto objT = obj->AddComponent<Transform>();
		objT->SetPosition(0, 0, 0);
		objT->SetRotation(0, 0, 0);
		objT->SetScale(1280, 720, 1);

		auto objD = obj->AddComponent<PCTSpriteDraw>();
		//黒幕ならなんでもいいし、ポーズのやつもらってくるか
		objD->SetTextureResource(L"PAUSE_BLACK_TX");
		objD->SetDiffuse(Color4(1, 1, 1, 1));

		obj->SetAlphaActive(true);
		obj->SetDrawLayer(10);

		m_Black = obj;

		//-------------------------------------------
		//クレジットカード
		auto objc = AddGameObject<GameObject>();
		auto objtc = objc->AddComponent<Transform>();
		objtc->SetPosition(0, 0, 0);
		objtc->SetRotation(0, 0, 0);
		objtc->SetScale(1280, 720, 1);

		auto objd = objc->AddComponent<PCTSpriteDraw>();
		objd->SetTextureResource(L"Credit_TX");

		//透明度使わないけど一応
		objc->SetAlphaActive(true);
		objc->SetDrawLayer(1);
		objc->SetDrawActive(false);

		SetSharedGameObject(L"Credit", objc);
		//-------------------------------------------
		//ロゴ１

		auto logo1 = AddGameObject<GameObject>();
		auto logoTrans = logo1->AddComponent<Transform>();
		logoTrans->SetPosition(0, 0, 0);
		logoTrans->SetRotation(0, 0, 0);
		logoTrans->SetScale(1280, 720, 1);

		auto logoDraw = logo1->AddComponent<PCTSpriteDraw>();
		logoDraw->SetTextureResource(L"LOGO1");

		logo1->SetAlphaActive(true);
		logo1->SetDrawLayer(1);
		logo1->SetDrawActive(false);

		SetSharedGameObject(L"Logo1", logo1);

		//-------------------------------------------
		//ロゴ２
		auto logo2 = AddGameObject<GameObject>();
		auto logo2Trans = logo2->AddComponent<Transform>();
		logo2Trans->SetPosition(0, 0, 0);
		logo2Trans->SetRotation(0, 0, 0);
		logo2Trans->SetScale(1280, 720, 1);

		auto logo2Draw = logo2->AddComponent<PCTSpriteDraw>();
		logo2Draw->SetTextureResource(L"LOGO2");

		logo2->SetAlphaActive(true);
		logo2->SetDrawLayer(1);
		logo2->SetDrawActive(false);

		SetSharedGameObject(L"Logo2", logo2);

		//-------------------------------------------

		//最初に移すやつ決める
		int ram = rand() % 100;
		if (ram  < 30)
		{
			GetSharedGameObject<GameObject>(L"Logo1", false)->SetDrawActive(true);
		}
		else
		{
			GetSharedGameObject<GameObject>(L"Logo2", false)->SetDrawActive(true);
		}
	}

	void LogoScene::OnUpdate()
	{
		//コントローラ
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//流れ
		//暗転→明るく→待つ→暗転→明るく→松

		switch (m_state)
		{
			//ちょっと待つ
		case 0:
			if (true)
			{
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > m_waitTime)
				{
					m_time = 0;
					//暗転
					m_state = 2;
				}

				if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
				{
					m_time = 0;
					//暗転
					m_state = 2;
				}
			}
			break;
			//明るく
		case 1:
			if (true)
			{
				m_Alpha += -App::GetApp()->GetElapsedTime();
				if (m_Alpha < 0)
				{
					m_Alpha = 0;
					//待つ状態へ
					m_state = 0;
				}
				m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

			}
			break;
			//暗転
		case 2:
			if (true)
			{
				m_Alpha += App::GetApp()->GetElapsedTime();
				if (m_Alpha > 1)
				{
					//画像入れ替え
					m_state = 3;
					m_Alpha = 1;

				}
				m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

			}
			break;
			//画像入れ替え
		case 3:
			if (true)
			{
				//明るく
				m_state = 1;

				//ここに追加
				switch (m_stateTex)
				{
				case 0:
					if (true)
					{
						//ロゴ消し
						auto ptr = GetSharedGameObject<GameObject>(L"Logo1", false);
						auto ptr2 = GetSharedGameObject<GameObject>(L"Logo2", false);

						if (ptr->GetDrawActive())
						{
							ptr->SetDrawActive(false);
						}
						if (ptr2->GetDrawActive())
						{
							ptr2->SetDrawActive(false);
						}

						//提出用
						m_state = 100;

						//クレジット
						GetSharedGameObject<GameObject>(L"Credit", false)->SetDrawActive(true);
					}
					break;
				case 1:
					if (true)
					{
						//クレジット
						GetSharedGameObject<GameObject>(L"Credit", false)->SetDrawActive(false);
						
						//展示用
						//m_state = 100;
					}
					break;
				}
				//画像進める
				m_stateTex++;
				break;
			}
			//シーン替え
		case 100:
			if (true)
			{
				//シーン切り替え
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				//タイトル
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
			}
			break;
		}
	}

	//破棄
	LogoScene::~LogoScene()
	{

	}
}
#pragma endregion
