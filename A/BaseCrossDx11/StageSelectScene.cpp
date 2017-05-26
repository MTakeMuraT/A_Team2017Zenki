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
		PtrCamera->SetEye(Vector3(0.0f, 30.0f, -0.1f));
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
		//�v�Z�߂�ǂ��̂Œ��ł�
		//�P�`�S
		AddGameObject<StageBox>(Vector3(-8, 0, 5), Vector3(2, 2, 2), 1);
		AddGameObject<StageBox>(Vector3(8, 0, 5), Vector3(2, 2, 2), 2);
		AddGameObject<StageBox>(Vector3(-8, 0, -5), Vector3(2, 2, 2), 3);
		AddGameObject<StageBox>(Vector3(8, 0, -5), Vector3(2, 2, 2), 4);
		
		//�T�`�W
		AddGameObject<StageBox>(Vector3(-8, 0, -22), Vector3(2, 2, 2), 5);
		AddGameObject<StageBox>(Vector3(8, 0, -22), Vector3(2, 2, 2), 6);
		AddGameObject<StageBox>(Vector3(-8, 0, -32), Vector3(2, 2, 2), 7);
		AddGameObject<StageBox>(Vector3(8, 0, -32), Vector3(2, 2, 2), 8);
		
		//�X�`�P�Q
		AddGameObject<StageBox>(Vector3(36, 0, -22), Vector3(2, 2, 2), 9);
		AddGameObject<StageBox>(Vector3(56, 0, -22), Vector3(2, 2, 2), 10);
		AddGameObject<StageBox>(Vector3(36, 0, -32), Vector3(2, 2, 2), 11);
		AddGameObject<StageBox>(Vector3(56, 0, -32), Vector3(2, 2, 2), 12);
		
		//�P�R�`�P�U
		AddGameObject<StageBox>(Vector3(36, 0, 5), Vector3(2, 2, 2), 13);
		AddGameObject<StageBox>(Vector3(56, 0, 5), Vector3(2, 2, 2), 14);
		AddGameObject<StageBox>(Vector3(36, 0, -5), Vector3(2, 2, 2), 15);
		AddGameObject<StageBox>(Vector3(56, 0, -5), Vector3(2, 2, 2), 16);
		
	}

	//�X�e�[�W�̏��쐬
	void StageSelectScene::CreateStageUnder()
	{
		//�n�ʍ쐬
		//����
		AddGameObject<SelectGroud>(Vector3(0, -0.5, 0), Vector3(45, 1, 25));
		//����
		AddGameObject<SelectGroud>(Vector3(0, -0.5, -26), Vector3(45, 1, 25));
		//�E��
		AddGameObject<SelectGroud>(Vector3(46, -0.5, -26), Vector3(45, 1, 25));
		//�E��
		AddGameObject<SelectGroud>(Vector3(46, -0.5, 0), Vector3(45, 1, 25));
	}


	//�X�e�[�W�s�����`�F�b�N����X�v���C�g
	void StageSelectScene::CreateGoCheck()
	{
		SetSharedGameObject(L"GoStageCheck", AddGameObject<GoStageCheck>(Vector2(200, 200)));
	}
	//Abe20170421

	//Abe20170525
	//�X�e�[�W���S�쐬
	void StageSelectScene::CreateStageLogo()
	{
		AddGameObject<SelectLogo>(Vector2(0,300),Vector2(800,120),3);
	}
	//Abe20170525

	void StageSelectScene::OnCreate()
	{
		try {
			/*//���؂���̂ɏd���̂ňꎞ�I�ɏ����܂� Abe20170505
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"StageSelect_01_BGM");
			m_AudioObjectPtr->Start(L"StageSelect_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			*/
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

			//Abe20170525
			//�X�e�[�W���S�쐬
			CreateStageLogo();
			//Abe20170525

			//Abe20170524
			//�X�e�[�W�̏��쐬
			CreateStageUnder();

			//�f�o�b�O��������
			auto debtxt = AddGameObject<DebugTxt>();
			debtxt->SetLayer(10);
			//�F�ԂɕύX
			debtxt->SetColor(Vector3(1, 0, 0));
			//�傫���ύX
			debtxt->SetScaleTxt(40);

			m_Debugtxt = debtxt;
			//Abe20170524

			//Abe20170525�m�F�p
			//AddGameObject<SpritePosScaleChecker>(Vector2(0,0),Vector2(100,100),5,L"TRACE_TX");
			//Abe20170525�m�F�p
			auto PtrEnemyCount = AddGameObject<EnemyCount>();
			SetSharedGameObject(L"Count", PtrEnemyCount);

			//�J�ڃA�j���[�V����
			AddGameObject<SceneChangeSSOut>()->OnAnim();
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




		/*
		if (KeylVec.m_bPressedKeyTbl[VK_DOWN] && m_CameraNum != 1)
		{
			MoveCamera(1);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_UP] && m_CameraNum != 0)
		{
			MoveCamera(0);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_RIGHT] && m_CameraNum != 2)
		{
			MoveCamera(2);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_LEFT] && m_CameraNum != 3)
		{
			MoveCamera(3);
		}
		*/
		//Abe20170427
		//�J�����ړ�
		if (m_moveCameraFlg)
		{
			CameraMove();
		}
		else
		{
			//�v���C���[���W�擾
			auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
			Vector3 ppos = pptr->GetPos();

			//����Ɉړ�
			//�͈�(X[-26~26]Y[16~-16])
			if ((ppos.x > -26 && ppos.x < 26) && (ppos.z > -16 && ppos.z < 16) && m_CameraNum != 0)
			{
				MoveCamera(0);
				m_CameraNum = 0;
			}
			//�����Ɉړ�
			//�͈�(X[-26~26]Y[-10~-33])
			else if ((ppos.x > -26 && ppos.x < 26) && (ppos.z > -33 && ppos.z < -10) && m_CameraNum != 1)
			{
				MoveCamera(1);
				m_CameraNum = 1;
			}

			//�E��Ɉړ�
			//�͈�(X[18~63]Y[16~-16])
			else if ((ppos.x > 18 && ppos.x < 63) && (ppos.z > -16 && ppos.z < 16) && m_CameraNum != 2)
			{
				MoveCamera(2);
				m_CameraNum = 2;
			}

			//�E���Ɉړ�
			//�͈�(X[18~63]Y[-10~-33])
			else if ((ppos.x > 18 && ppos.x < 63) && (ppos.z > -33 && ppos.z < -10) && m_CameraNum != 3)
			{
				MoveCamera(3);
				m_CameraNum = 3;
			}

		}

		//Abe20170524
		/*�J�������W�m�F�p*/
		//wstring txt;
		//txt += Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_UP]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_RIGHT]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_DOWN]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_LEFT]);
		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		//Vector2 InputXY = Vector2((KeylVec.m_bPushKeyTbl[VK_RIGHT] + -KeylVec.m_bPushKeyTbl[VK_LEFT]), (KeylVec.m_bPushKeyTbl[VK_UP] + -KeylVec.m_bPushKeyTbl[VK_DOWN]));
		//auto View = GetView();
		//auto CameraP = View->GetTargetCamera();
		//m_CameraPos = CameraP->GetEye();
		//m_CameraAt = CameraP->GetAt();
		//m_CameraPos += Vector3(InputXY.x, 0, InputXY.y);
		//m_CameraAt += Vector3(InputXY.x, 0, InputXY.y);
		//CameraP->SetEye(m_CameraPos);
		//CameraP->SetAt(m_CameraAt);
		//Abe20170524
		
		//wstring txt;
		//txt += L"X:" + Util::FloatToWStr(m_CameraPos.x) + L"Z:" + Util::FloatToWStr(m_CameraPos.z);
		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		
		//Abe20170427
	}

	//Abe20170427
	//�J�����ړ��֐�
	void StageSelectScene::CameraMove()
	{
		//Abe20170524	
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();

		//�ڕW�n�_�Ƃ̋����𑪂��ċ߂��Ȃ���΋߂Â��Ă�
		Vector3 dis = m_CameraMoveTarget - m_CameraPos;
		if (abs(dis.x) + abs(dis.z) > 1.0f)
		{
			//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(Util::FloatToWStr(abs(dis.x) + abs(dis.z)));

			dis /= 15;
			m_CameraPos += dis;
			m_CameraAt += dis;
			CameraP->SetEye(m_CameraPos);
			CameraP->SetAt(m_CameraAt);
		}
		else
		{
			//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(L"end");

			//�ړ���~
			m_moveCameraFlg = false;
			//���W�Œ�
			m_CameraPos = m_CameraMoveTarget;

			//�v���C���[������悤��(�Ă������A�^������߂�)
			auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
			pptr->ActiveMove();
			return;
		}

		//�v���C���[�ړ�
		auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
		Vector3 ppos = pptr->GetPos();
		//�ړ�
		Vector3 dis2 = m_CameraMovePlayerTargetPos - ppos;
		if (abs(dis2.x) + abs(dis2.z) > 1.0f)
		{
			dis2 /= 5;
			ppos += dis2;
			pptr->SetPos(ppos);
		}
		else
		{
			ppos = m_CameraMovePlayerTargetPos;
			pptr->SetPos(ppos);
		}

		//Abe20170524
	}

	void StageSelectScene::MoveCamera(int num)
	{
		//Z:26 X:46

		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//�^�[�Q�b�g�ݒ�
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();
		//Abe20170524
		//�J�����ړ�0�F����Ɂ@1�F�����Ɂ@2�F�E��Ɂ@3�F�E����
		switch (num)
		{
		case 0:
			m_CameraMoveTarget = Vector3(0, 30, -0.1f);
			m_CameraMovePlayerTargetPos = Vector3(0, 0, 0);
			break;
		case 1:
			m_CameraMoveTarget = Vector3(0, 30, -27.1f);
			m_CameraMovePlayerTargetPos = Vector3(0, 0, -27);
			break;
		case 2:
			m_CameraMoveTarget = Vector3(46, 30, -0.1f);
			m_CameraMovePlayerTargetPos = Vector3(46, 0, 0);
			break;
		case 3:		
			m_CameraMoveTarget = Vector3(46, 30, -27.1f);
			m_CameraMovePlayerTargetPos = Vector3(46, 0, -27);
			break;
		}
		//�ړ��t���O�𗧂Ă�
		m_moveCameraFlg = true;
		//Abe20170524
	}
	//Abe20170427

	 StageSelectScene::~StageSelectScene() {
		// m_AudioObjectPtr->Stop(L"StageSelect_01_BGM");
	}
}
//end basecross
