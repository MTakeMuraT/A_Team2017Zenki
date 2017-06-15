#include "stdafx.h"
#include "Project.h"

//*******************************************
//�@�쐬�J�n�� 2017 / 06 / 15
//	�y��쐬��	Abe
//	�ЂƂ��ƁF�悤����؂�؂�
//*******************************************

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	//�r���[�ƃ��C�g�̍쐬
	void TutorialScene::CreateViewLight() {
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

	//�n�ʍ쐬
	void TutorialScene::CreateGround()
	{
		auto obj = AddGameObject<Ground_GameStage>(Vector3(75,75, 1),Vector3(0, 0, 0),wstring(L"Glass_TX"));
		obj->SetDrawLayer(0);
	}

	//�v���C���[�쐬
	void TutorialScene::CreatePlayer()
	{
		auto obj = AddGameObject<TutorialPlayerS>();
		SetSharedGameObject(L"TutorialPlayerS", obj);
	}

	//�ړ��^�[�Q�b�g�쐬
	void TutorialScene::CreateMoveTarget()
	{
		auto obj = AddGameObject<MoveTarget>();
		SetSharedGameObject(L"MoveTarget", obj);
	}

	void TutorialScene::OnCreate()
	{
		try 
		{
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�n�ʍ쐬
			CreateGround();
			//�v���C���[�쐬
			CreatePlayer();
			//�ړ��^�[�Q�b�g�쐬
			CreateMoveTarget();
		}

		catch (...) {
			throw;
		}
	}

	void TutorialScene::OnUpdate()
	{
		//�J�����X�V
		UpdateCamera();

		//�f�o�b�N********************************
		//�L�[�̓���
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTutorial");
		}

	}

	//�j��
	TutorialScene::~TutorialScene() 
	{

	}

	//�J�����X�V
	void TutorialScene::UpdateCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//���W
		Vector3 Pos = CameraP->GetEye();
		//���镔��
		Vector3 At = CameraP->GetAt();


		//�Q�̂̍��W���炤
		auto PlaPtr = GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS",false);
		vector<Vector3> PlayerPosS = PlaPtr->GetPlayerSPos_RETURNvectorVec3();

		//����_���v���C���[�Ԃ̒��S
		At = (PlayerPosS[0] + PlayerPosS[1]) / 2;
		//���W��������Ǝ�O��
		Pos = At;
		//�����𑪂�
		Vector3 def = PlayerPosS[1] - PlayerPosS[0];
		def = def*def;
		//�㏸��
		float Yup = sqrt(def.x + def.z) - 6;
		//�㏸���ɃJ�����̏���������ǉ�
		Yup += 15;
		if (Yup < 15)
		{
			Yup = 15;
		}
		Pos.y += Yup;
		//�����l��Z�ɂ�
		Pos.z += -Yup;

		//�J�����X�V
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
	}

	//--------------------------------------------------------------------------------------
	//	�������牺�͐�p�̃I�u�W�F�N�g�������`�H
	//--------------------------------------------------------------------------------------

	//**************************************************************************************
	//**************************************************************************************


	//**************************************************************************************
	//	[TutorialPlayerS]
	//	�`���[�g���A����p�̃v���C���[�A���쐧���@�\��
	//	�w�b�_�[�Œl�ݒ肵�Ă��o�O���̂ŃN���G�C�g�Őݒ肷���
	//	���ȁA���̃I�u�W�F�N�g�͒��S���W�Ŏ���̃v���C���[�͌����ڂ���
	//**************************************************************************************
	void TutorialPlayerS::OnCreate()
	{
		//-----------------------------
		//������

		//-----------------------
		//�p�����[�^��
		//-----------------------
		//�v���C���[���m�̋���
		m_PlayerSDistance = 4.0f;
		//�����l
		m_PlayerSDistanceInit = 4.0f;
		//����
		m_PlayerSDistanceLimit = 15.0f;
		//����鑬�x
		m_DistanceSpeed = 40.0f;
		//���������x
		m_KuttukuSpeed = 20.0f;
		//�p�x
		m_rot = 0;
		//��]���x
		m_rotSpeed = 90.0f;
		//���x
		m_Speed = 20.0f;
		//-----------------------
		//����n
		//-----------------------
		m_moveFlg = true;
		m_rotFlg = true;
		m_AButtonFlg = true;
		//-----------------------------

		for (int i = 0; i < 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(0, 0, 0);
			Trans->SetScale(1, 1, 1);
			Trans->SetRotation(0, 3.14159265f/ 180 * 180 * (1-i), 0);

			//���f���ƃg�����X�t�H�[���̊Ԃ̍���
			Matrix4X4 PlayerMat;
			PlayerMat.DefTransformation(
				Vector3(1.0, 1.0f, 1.0f),
				Vector3(0, -90 * 3.14159265f/180, 0),
				Vector3(0.0f, 90 * 3.14159265f/180, 0.0f)
				);

			auto Draw = obj->AddComponent<PNTBoneModelDraw>();
			Draw->SetMeshResource(L"Player_Model");
			Draw->SetMeshToTransformMatrix(PlayerMat);

			//�A�j���[�V����
			Draw->AddAnimation(L"AllAnima", 0, 150, 30.0f);
			Draw->AddAnimation(L"Wait", 0, 30, true, 30.0f);
			Draw->AddAnimation(L"Damage", 30, 30, false, 30.0f);
			Draw->AddAnimation(L"LeftRot", 80, 15, false, 30.0f);
			//Draw->AddAnimation(L"LeftReturn", 95,20,false,30.0f);
			Draw->AddAnimation(L"RightRot", 120, 15, false, 30.0f);
			//Draw->AddAnimation(L"RightReturn",135,15,false,30.0f);

			//�A�j���[�V�����ݒ�
			m_NowAnimName = "None";
			m_ChangeAnimName = "Wait";

			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);
			if (i == 0)
			{
				m_Player1 = obj;
			}
			else
			{
				m_Player2 = obj;
			}
		}

		//�����쐬-----------------------------------------
		auto blackobj = GetStage()->AddGameObject<GameObject>();
		auto TransBla = blackobj->AddComponent<Transform>();
		TransBla->SetPosition(0, 0, 0);
		TransBla->SetRotation(0, 0, 0);
		TransBla->SetScale(1280, 720, 1);

		auto DrawBla = blackobj->AddComponent<PCTSpriteDraw>();
		DrawBla->SetTextureResource(L"OVERBLACK_TX");
		DrawBla->SetDiffuse(Color4(1, 1, 1, 0));

		blackobj->SetAlphaActive(true);
		blackobj->SetDrawLayer(5);

		m_BlackSprite = blackobj;


	}

	void TutorialPlayerS::OnUpdate()
	{
		//�A�j���[�V�����X�V
		UpdateAnimation();

		//�Ó]���͓������Ȃ�
		if (m_DontMoveFlg)
		{
			BlackUpdate();
			return;
		}

		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�ړ�------------------------------------------------------------
			if (m_moveFlg)
			{
				if (abs(CntlVec[0].fThumbLX) + abs(CntlVec[0].fThumbLY) >= 0.2f)
				{
					Vector3 InputXY = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					pos += InputXY * App::GetApp()->GetElapsedTime() * m_Speed;
					GetComponent<Transform>()->SetPosition(pos);
					//�����X�V
					m_Kansei = InputXY;
				}
				else
				{
					//���͂Ȃ���Ί����ŗ���
					if (abs(m_Kansei.x) + abs(m_Kansei.z) >= 0.2f)
					{
						Vector3 pos = GetComponent<Transform>()->GetPosition();
						pos += m_Kansei * App::GetApp()->GetElapsedTime() * m_Speed;
						GetComponent<Transform>()->SetPosition(pos);
						//����
						m_Kansei *= 0.90f;
					}
					else if (m_Kansei.x != 0)
					{
						m_Kansei = Vector3(0, 0, 0);
					}
				}
			}
			//�����--------------------------------------------------------
			if (m_AButtonFlg)
			{
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A)
				{
					m_PlayerSDistance += App::GetApp()->GetElapsedTime() * m_DistanceSpeed;
					if (m_PlayerSDistance > m_PlayerSDistanceLimit)
					{
						m_PlayerSDistance = m_PlayerSDistanceLimit;
					}
				}
				else if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					//�ړ�����
					m_moveFlg = false;
					//����鐧��
					m_AButtonFlg = false;
					//��]����
					m_rotFlg = false;
					//������ON
					m_KuttukuFlg = true;
					//�ꉞ�߂�OFF
					m_KuttukuAfterFlg = false;
					//���������x������
					m_KuttukuSpeed = 20.0f;
				}
			}
			//������
			else if(m_KuttukuFlg)
			{
				//��������
				m_PlayerSDistance += -m_KuttukuSpeed * App::GetApp()->GetElapsedTime();
				//���x�グ��
				m_KuttukuSpeed *= 1.1f;

				//����������
				if (m_PlayerSDistance < 1.0f)
				{
					//������OFF
					m_KuttukuFlg = false;
					//�߂�ON
					m_KuttukuAfterFlg = true;
				}
			}
			//��������
			else if (m_KuttukuAfterFlg)
			{
				//����
				m_PlayerSDistance += m_DistanceSpeed * App::GetApp()->GetElapsedTime();
				if (m_PlayerSDistance > m_PlayerSDistanceInit)
				{
					//������߂�
					m_PlayerSDistance = m_PlayerSDistanceInit;
					//�ړ�����
					m_moveFlg = true;
					//��������
					m_AButtonFlg = true;
					//��]����
					m_rotFlg = true;
					//�߂����
					m_KuttukuAfterFlg = false;
				}
			}
			//��]--------------------------------------------------
			if (m_rotFlg)
			{
				//����]
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					m_rot += -m_rotSpeed * App::GetApp()->GetElapsedTime();
					//�ꉞ���[�v�����Ƃ�
					if (m_rot < 0)
					{
						m_rot = 360;
					}
				}
				//�E��]
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					m_rot += m_rotSpeed * App::GetApp()->GetElapsedTime();
					//�ꉞ���[�v�����Ƃ�
					if (m_rot > 360)
					{
						m_rot = 0;
					}
				}
			}
		}
		

		//�v���C���[�̈ʒu�Ɖ�]�X�V
		PosRotUpdate();
		//�X�e�[�W�̊O�ɍs�����Ƃ�����߂�
		CheckStageEnd();
		
	}

	//----------------------------------------------
	//�֐�
	//----------------------------------------------
	//�v���C���[�ʒu��]�X�V
	void TutorialPlayerS::PosRotUpdate()
	{
		//�E��0�ō���1
		Vector3 posright = GetComponent<Transform>()->GetPosition();
		posright += Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player1->GetComponent<Transform>()->SetPosition(posright);

		//���ʒu����
		Vector3 porleft = GetComponent<Transform>()->GetPosition();
		porleft += -Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player2->GetComponent<Transform>()->SetPosition(porleft);

		//�E��]�X�V
		//���W�擾
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		
		//���v�Z
		Vector3 dis1 = pos2 - pos1;
		Vector3 dis2 = pos1 - pos2;

		//�p�x�v�Z
		float angle1 = atan2(dis1.z, dis1.x);
		float angle2 = atan2(dis2.z, dis2.x);

		m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
		m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
	}

	//�X�e�[�W�̊O�ɍs�����Ƃ�����߂�����
	void TutorialPlayerS::CheckStageEnd()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		if (abs(pos.x) > 30 || abs(pos.z) > 30)
		{
			m_DontMoveFlg = true;
			m_BlackAlpha = 0;
			m_BlackAlphaFlg = false;
		}
	}

	void TutorialPlayerS::BlackUpdate()
	{
		if (!m_BlackAlphaFlg)
		{
			m_BlackAlpha += App::GetApp()->GetElapsedTime();
			m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
			if (m_BlackAlpha > 1.0f)
			{
				m_BlackAlphaFlg = true;

				//���W�X�V
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos = Vector3(0, 0, 0);
				GetComponent<Transform>()->SetPosition(pos);
				m_rot = 0;
				m_Kansei = Vector3(0, 0, 0);
				//�v���C���[�̈ʒu�Ɖ�]�X�V
				PosRotUpdate();

			}
		}
		else
		{
			m_BlackAlpha += -App::GetApp()->GetElapsedTime();
			m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
			if (m_BlackAlpha < 0)
			{
				m_BlackAlphaFlg = false;
				m_DontMoveFlg = false;
			}

		}
	}

	//�A�j���[�V�����X�V
	void TutorialPlayerS::UpdateAnimation()
	{
		if (m_NowAnimName == m_ChangeAnimName)
		{
			m_Player1->GetComponent<PNTBoneModelDraw>()->UpdateAnimation(App::GetApp()->GetElapsedTime());
			m_Player2->GetComponent<PNTBoneModelDraw>()->UpdateAnimation(App::GetApp()->GetElapsedTime());

		}
		else
		{
			if (m_ChangeAnimName == "Wait")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
			}
			if (m_ChangeAnimName == "LeftRot")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"LeftRot");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"LeftRot");
			}
			if (m_ChangeAnimName == "RightRot")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"RightRot");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"RightRot");
			}
			m_NowAnimName = m_ChangeAnimName;
		}
	}

	//----------------------------------------------
	//���̑�(�A�N�Z�T�[�Ƃ�)
	//----------------------------------------------
	//��̂̍��W��vector�R���e�i�œn��
	vector<Vector3> TutorialPlayerS::GetPlayerSPos_RETURNvectorVec3()
	{
		vector<Vector3> vec3;
		vec3.push_back(m_Player1->GetComponent<Transform>()->GetPosition());
		vec3.push_back(m_Player2->GetComponent<Transform>()->GetPosition());
		return vec3;
	}

	//**************************************************************************************
	//	�ړ��^�[�Q�b�g
	//	������
	//**************************************************************************************
	void MoveTarget::OnCreate()
	{
		auto TransTar = AddComponent<Transform>();
		TransTar->SetPosition(0, 0.5f, 10);
		TransTar->SetRotation(90 * 3.14159265f / 180, 0, 0);
		TransTar->SetScale(7, 7, 7);

		auto DrawTar = AddComponent<PNTStaticDraw>();
		DrawTar->SetMeshResource(L"DEFAULT_SQUARE");
		DrawTar->SetTextureResource(L"TUTORIALTARGET_TX");

		SetAlphaActive(true);
		SetDrawLayer(1);

		m_Alpha = 1;
	}

	void MoveTarget::OnUpdate()
	{
		//������
		if (!m_AlphaFlg)
		{
			m_Alpha += -App::GetApp()->GetElapsedTime();
			if (m_Alpha < 0.5f)
			{
				m_Alpha = 0.5f;
				m_AlphaFlg = true;
			}
		}
		else
		{
			m_Alpha += App::GetApp()->GetElapsedTime();
			if (m_Alpha > 1.0f)
			{
				m_Alpha = 1.0f;
				m_AlphaFlg = false;
			}
		}
		GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

		//�v���C���[�����邩
		Vector3 pos = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->GetComponent<Transform>()->GetPosition();
		Vector3 dis = pos - GetComponent<Transform>()->GetPosition();

		if (abs(dis.x) + abs(dis.z) <= 3.0f)
		{
			SetDrawActive(false);
		}
	}
}