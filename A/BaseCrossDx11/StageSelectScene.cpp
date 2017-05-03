/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void StageSelectScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�(�J�����Œ�)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 30.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//�V���O�����C�g�̍쐬
		auto PtrSingleLight = CreateLight<SingleLight>();
		//���C�g�̐ݒ�
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//�e�X�g�\��
	void StageSelectScene::CreatTestLin() {
		AddGameObject<StageSelectSprite>(
			Vector2(1280, 720),
			Vector2(0, 0),
			0
			);
	}

	//Abe20170421
	//�t���[���쐬
	void StageSelectScene::CreateFlame()
	{
		AddGameObject<SelectFlame>(Vector2(0, 0), Vector2(1280, 720), 1);
	}

	//�v���C���[�쐬
	void StageSelectScene::CreatePlayer()
	{
		SetSharedGameObject(L"SelectPlayer", AddGameObject<SelectPlayer>(Vector3(0, 0, 0), Vector3(1, 1, 1),20.0f));
	}

	//�X�e�[�W�{�b�N�X�쐬
	void StageSelectScene::CreateStageBox()
	{
		AddGameObject<StageBox>(Vector3(0,0,0),Vector3(1,1,1),1);
	}

	//�X�e�[�W�s�����`�F�b�N����X�v���C�g
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
			//�t���[���쐬
			CreateFlame();
			//�v���C���[�쐬
			CreatePlayer();
			//�X�e�[�W�{�b�N�X�쐬
			CreateStageBox();
			//�X�e�[�W�s�����`�F�b�N����X�v���C�g
			CreateGoCheck();
			//Abe20170421


			//�f�o�b�O�p�̕���
			SetSharedGameObject(L"DebugTxt", AddGameObject<DebugTxt>());
		}
		catch (...) {

			throw;
		}
	}

	void StageSelectScene::OnUpdate() {
		//�L�[�̓���
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
		}

		//Abe20170427
		//�J�����ړ�
		if (m_moveCameraFlg)
		{
			CameraMove();
		}

		/*�J�������W�m�F�p*/
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
	//�J�����ړ��֐�
	void StageSelectScene::CameraMove()
	{
		
	}

	void StageSelectScene::MoveCamera(int num)
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//�^�[�Q�b�g�ݒ�
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();
		//�J�����ړ�0�F��Ɂ@1�F�E�Ɂ@2�F���Ɂ@3�F����
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
