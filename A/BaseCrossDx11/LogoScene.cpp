#include "stdafx.h"
#include "Project.h"

//*******************************************
//�@�쐬�J�n�� 2017 / 06 / 26
//	�y��쐬��	Abe
//	�ЂƂ��ƁF����Ƃ����A����ł�����
//*******************************************

namespace basecross
{

#pragma region LogoScene

	//�r���[�ƃ��C�g�̍쐬
	void LogoScene::CreateViewLight() {
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

	void LogoScene::OnCreate()
	{
		try
		{
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}

		catch (...) {
			throw;
		}
		//������---------------------
		m_time = 0;
		m_Alpha = 1;
		m_state = 1;
		m_stateTex = 0;
		m_waitTime = 3.0f;
		//������---------------------

		//�֐����܂ł��Ȃ��Ǝv�����炱���ɏ�����
		auto obj = AddGameObject<GameObject>();
		auto objT = obj->AddComponent<Transform>();
		objT->SetPosition(0, 0, 0);
		objT->SetRotation(0, 0, 0);
		objT->SetScale(1280, 720, 1);

		auto objD = obj->AddComponent<PCTSpriteDraw>();
		//�����Ȃ�Ȃ�ł��������A�|�[�Y�̂������Ă��邩
		objD->SetTextureResource(L"PAUSE_BLACK_TX");
		objD->SetDiffuse(Color4(1, 1, 1, 1));

		obj->SetAlphaActive(true);
		obj->SetDrawLayer(10);

		m_Black = obj;

		//-------------------------------------------
		//�N���W�b�g�J�[�h
		auto objc = AddGameObject<GameObject>();
		auto objtc = objc->AddComponent<Transform>();
		objtc->SetPosition(0, 0, 0);
		objtc->SetRotation(0, 0, 0);
		objtc->SetScale(1280, 720, 1);

		auto objd = objc->AddComponent<PCTSpriteDraw>();
		objd->SetTextureResource(L"Credit_TX");

		//�����x�g��Ȃ����ǈꉞ
		objc->SetAlphaActive(true);
		objc->SetDrawLayer(1);

		SetSharedGameObject(L"Credit", objc);
		//-------------------------------------------
	}

	void LogoScene::OnUpdate()
	{
		//�R���g���[��
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//����
		//�Ó]�����邭���҂��Ó]�����邭����

		switch (m_state)
		{
			//������Ƒ҂�
		case 0:
			if (true)
			{
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > m_waitTime)
				{
					m_time = 0;
					//�Ó]
					m_state = 2;
				}

				if (KeylVec.m_bPressedKeyTbl['A'] || CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
				{
					m_time = 0;
					//�Ó]
					m_state = 2;
				}
			}
			break;
			//���邭
		case 1:
			if (true)
			{
				m_Alpha += -App::GetApp()->GetElapsedTime();
				if (m_Alpha < 0)
				{
					m_Alpha = 0;
					//�҂�Ԃ�
					m_state = 0;
				}
				m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

			}
			break;
			//�Ó]
		case 2:
			if (true)
			{
				m_Alpha += App::GetApp()->GetElapsedTime();
				if (m_Alpha > 1)
				{
					//�摜����ւ�
					m_state = 3;
					m_Alpha = 1;

				}
				m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

			}
			break;
			//�摜����ւ�
		case 3:
			if (true)
			{
				//���邭
				m_state = 1;

				//�����ɒǉ�
				switch (m_stateTex)
				{
				case 0:
					GetSharedGameObject<GameObject>(L"Credit", false)->SetDrawActive(false);
					//��Ԃ�100�ɂ���΃V�[���J��
					m_state = 100;
					break;
				}
				//�摜�i�߂�
				m_stateTex++;
			}
			break;
			//�V�[���ւ�
		case 100:
			if (true)
			{
				//�V�[���؂�ւ�
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				//�^�C�g��
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
			}
			break;
		}
	}

	//�j��
	LogoScene::~LogoScene()
	{

	}
}
#pragma endregion
