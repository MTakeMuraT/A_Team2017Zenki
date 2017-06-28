/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/
//�v���C���[��LookAtCamera��MyLookAtCamera�ɕύX����Ύ���
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	void TitleScene::CreateBackGround() {
		
		AddGameObject<TitleSprite>(Vector2(1280, 720),Vector2(0, 0));

		SetSharedGameObject(L"PressStart",AddGameObject<PressSprite>(Vector2(512, 512),Vector2(0, -190)));
		
		//�y��쐬
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
			////���؂���̂ɏd���̂ňꎞ�I�ɏ����܂� Abe20170505
			//m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			//m_AudioObjectPtr->AddAudioResource(L"Title_01_BGM");
			//m_AudioObjectPtr->Start(L"Title_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�w�i�̍쐬
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
		//���S�V�[���ɖ߂�J�E���g
		m_logocounttime += App::GetApp()->GetElapsedTime();
		if (m_logocounttime > 30)
		{
			//�V�[���؂�ւ�
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//���S�V�[��
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToLogoScene");

			m_logocounttime = 0;
		}
		//�R���g���[��
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//**********************
		//�R�}���h
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK && CntlVec[0].wButtons & XINPUT_GAMEPAD_START)
		{
			//�V�[�������[�h
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
					//���S�J�E���g���Z�b�g
					m_logocounttime = 0;
				}

			}
			break;
		case 1:
			if (true)
			{
				//������Ƒ҂��Ď��̏�Ԃ�
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > 1.5f)
				{
					m_state = 2;
					m_time = 0;

					//�v���X�X�^�[�g����
					GetSharedGameObject<GameObject>(L"PressStart", false)->SetDrawActive(false);
				}
			}
			break;
			//�`���[�g���A���ƃQ�[���n�߂�쐬
		case 2:
			if (true)
			{
				//�����΂����ł��Ă邩������
				if (!GetSharedGameObject<GameObject>(L"GameStart",false))
				{
					//�Q�[���X�^�[�g�쐬
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

					//�`���[�g���A���쐬
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

				//��ԕύX
				m_state = 3;
			}
			break;
			//�㉺�őI��
		case 3:
			if (true)
			{
				//��I��
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

					//�����Ă��t���O
					m_AlphaFlg = false;

					//�����x�Đݒ�
					m_Alpha = 1.0f;

					//���S�J�E���g���Z�b�g
					m_logocounttime = 0;
				}
				//���I��
				if (CntlVec[0].fThumbLY < -0.5f || KeylVec.m_bPressedKeyTbl[VK_DOWN])
				{
					//����SE
					if (OneSeFlg == false) {
						GetSharedGameObject<SE>(L"TitleSE", false)->SetSeFlg_CURSORMOVE(false);
						GetSharedGameObject<SE>(L"TitleSE", false)->StickSe();
						OneSeFlg = true;
					}
					m_selectNum = 1;
					GetSharedGameObject<GameObject>(L"Dodai", false)->GetComponent<Transform>()->SetPosition(Vector3(0, -270, 0));

					GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
					GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//�����Ă��t���O
					m_AlphaFlg = false;

					//�����x�Đݒ�
					m_Alpha = 1.0f;

					//���S�J�E���g���Z�b�g
					m_logocounttime = 0;

				}

				//�{�^�������ꂽ
				if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
				{
					GetSharedGameObject<SE>(L"TitleSE", false)->ASe();

					//���S�J�E���g���Z�b�g
					m_logocounttime = 0;

					m_state = 4;
					GetSharedGameObject<GameObject>(L"GameStart", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));
					GetSharedGameObject<GameObject>(L"Tutorial", false)->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1));

					//SS�N��
					auto ptr = GetSharedGameObject<SceneChangeSS>(L"SceneChangeSS", false);
					if (!ptr)
					{
						auto ptr2 = AddGameObject<SceneChangeSS>();
						ptr2->OnAnim();
						ptr2->SetDrawLayer(5);
						SetSharedGameObject(L"SceneChangeSS", ptr2);
					}

					//�V�[���؂�ւ�
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					//�Q�b�҂�
					if (m_selectNum == 0)
					{
						//�`���[�g���A��
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTutorial");
					}
					else if (m_selectNum == 1)
					{
						//�X�e�Z��
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
					}
					return;
				}

				//�߂�K��-----------------------------------------------
				if (KeylVec.m_bPressedKeyTbl['B'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_B)
				{
					m_state = 0;
					//�v���X�X�^�[�g����
					GetSharedGameObject<GameObject>(L"PressStart", false)->SetDrawActive(true);
					GetSharedGameObject<GameObject>(L"GameStart", false)->SetDrawActive(false);
					GetSharedGameObject<GameObject>(L"Tutorial", false)->SetDrawActive(false);

					//�J�[�\���ʒu����
					m_selectNum = 0;
					GetSharedGameObject<GameObject>(L"Dodai", false)->GetComponent<Transform>()->SetPosition(Vector3(0, -190, 0));


					//���S�J�E���g���Z�b�g
					m_logocounttime = 0;

				}


				//�_��
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
			//�_��
		case 4:
			if (true)
			{
				//�_��
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
		//	//�Q�b�҂�
		//	PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");

		//}
	}
	//�j��
	 TitleScene::~TitleScene() {
		// m_AudioObjectPtr->Stop(L"Title_01_BGM");
	}
	 SE::SE(const shared_ptr<Stage>& StagePtr) :
		 GameObject(StagePtr)
	 {}
	 void SE::OnCreate() {
		 //SE//�I�[�f�B�I���\�[�X�o�^
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
