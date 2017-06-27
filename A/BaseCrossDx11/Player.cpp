/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class PlayerControl : public GameObject;
	//	�p�r: �v���C���[�R���g���[���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	void PlayerControl::OnCreate()
	{
		//-----------------------------
		//������

		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F���ɕύX
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);


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

		m_DontMoveFlg2 = false;
		//-----------------------------

		//���W�ݒ�
		auto trans = AddComponent<Transform>();
		trans->SetPosition(0, 1.0f, 0);
		trans->SetScale(0, 0, 0);
		trans->SetRotation(0, 0, 0);

		for (int i = 0; i < 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(0, 1.0f, 0);
			Trans->SetScale(1, 1, 1);
			Trans->SetRotation(0, 3.14159265f / 180 * 180 * (1 - i), 0);

			//���f���ƃg�����X�t�H�[���̊Ԃ̍���
			Matrix4X4 PlayerMat;
			PlayerMat.DefTransformation(
				Vector3(1.0, 1.0f, 1.0f),
				Vector3(0, -90 * 3.14159265f / 180, 0),
				Vector3(0.0f, 0.0f, 0.0f)
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
				GetStage()->SetSharedGameObject(L"GamePlayer_R", obj);

				m_Player1 = obj;

			}
			else
			{
				GetStage()->SetSharedGameObject(L"GamePlayer_L", obj);

				m_Player2 = obj;
			}
			//�X�e�[�W�̑傫��
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			m_StageSize = ScenePtr->GetStageSize() / 2;


			//Abe20170626
			//�^�[�Q�b�g�����O�쐬
			auto tarobj = GetStage()->AddGameObject<GameObject>();
			auto tarTra = tarobj->AddComponent<Transform>();
			tarTra->SetPosition(0, 0.9f, 0);
			tarTra->SetRotation(45*3.14159265f/180, 0, 0);
			tarTra->SetScale(3.0f, 3.0f, 3.0f);

			auto tarDra = tarobj->AddComponent<PNTStaticDraw>();
			tarDra->SetTextureResource(L"TARGETRING_TX");
			tarDra->SetMeshResource(L"DEFAULT_SQUARE");

			tarobj->SetAlphaActive(true);
			tarobj->SetDrawLayer(false);
			tarobj->SetDrawActive(false);

			m_TargetRing = tarobj;
			//Abe20170626

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

		//���[��ǐ���
		GetStage()->AddGameObject<PlayerShield>(Vector3(0, 0, 0),
		Vector3(2,2,2),
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L", false));
		GetStage()->AddGameObject<PlayerShield>(Vector3(0, 0, 0),
			Vector3(2,2,2),
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R", false));
	}

	void PlayerControl::OnUpdate()
	{
		//�A�j���[�V�����X�V
		UpdateAnimation();

		//�^�[�Q�b�g�����O�ʒu�X�V
		UpdateTargetRing();

		if (m_DontMoveFlg2)
		{
			return;
		}
		////�Ó]���͓������Ȃ�
		//if (m_DontMoveFlg)
		//{
		//	BlackUpdate();
		//	return;
		//}
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{

			//�ړ�------------------------------------------------------------
			if (m_moveFlg)
			{
				if (abs(CntlVec[0].fThumbLX) + abs(CntlVec[0].fThumbLY) >= 0.2f)
				{
					//Abe20170620
					//�u�[�X�g�N��
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					Vector3 InputXY = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					pos += InputXY * App::GetApp()->GetElapsedTime() * m_Speed;
					GetComponent<Transform>()->SetPosition(pos);
					//�����X�V
					m_Kansei = InputXY;

					//��]�ݒ�
					m_MoveRotFlg = false;

					float angle = atan2(InputXY.z, InputXY.x);
					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle, 0);
					//�X�e�[�W�O�̐���
				}
				else
				{
					//Abe20170620
					//�u�[�X�g�؂�
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
					//Abe20170620

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
					//�^�[�Q�b�g�\��
					if (!m_TargetRing->GetDrawActive())
					{
						m_TargetRing->SetDrawActive(true);
					}

					m_PlayerSDistance += App::GetApp()->GetElapsedTime() * m_DistanceSpeed;
					if (m_PlayerSDistance > m_PlayerSDistanceLimit)
					{
						m_PlayerSDistance = m_PlayerSDistanceLimit;
					}
					else
					{
						//Abe20170620
						//�u�[�X�g����
						GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Boost();
						GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Boost();


						//��]
						m_MoveRotFlg = false;
						//���W�擾
						Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
						Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

						//���v�Z
						Vector3 dis1 = pos1 - pos2;
						Vector3 dis2 = pos2 - pos1;


						//�p�x�v�Z
						float angle1 = atan2(dis1.z, dis1.x);
						float angle2 = atan2(dis2.z, dis2.x);

						m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
						m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
						//Abe20170620

					}
				}
				else if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					//�͂��ޔ���L��
					GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false)->SetActive(true);

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

					//Abe20170620
					//�u�[�X�g����
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Boost();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Boost();
					//Abe20170620

				}
			}
			//������
			else if (m_KuttukuFlg)
			{
				//��]������
				m_MoveRotFlg = true;

				//��������
				m_PlayerSDistance += -m_KuttukuSpeed * App::GetApp()->GetElapsedTime();
				//���x�グ��
				m_KuttukuSpeed *= 1.1f;
				SetActiveCollision(true);
				//����������
				if (m_PlayerSDistance < 1.0f)
				{
					//�^�[�Q�b�g��\��
					if (m_TargetRing->GetDrawActive())
					{
						m_TargetRing->SetDrawActive(false);
					}

					//������OFF
					m_KuttukuFlg = false;
					//�߂�ON
					m_KuttukuAfterFlg = true;
					SetActiveCollision(false);

					//Abe20170620
					//�u�[�X�g�N��
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620
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

					//�͂��ޔ��薳��
					GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false)->SetActive(false);


					//�X�e�[�W�O�̐���
				}
				//�X�e�[�W�O�̐���
			}
			//��]--------------------------------------------------
			if (m_rotFlg)
			{
				//����]
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					//Abe20170620
					//�u�[�X�g�N��
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					m_rot += -m_rotSpeed * App::GetApp()->GetElapsedTime();
					//�ꉞ���[�v�����Ƃ�
					if (m_rot < 0)
					{
						m_rot = 360;
					}

					//Abe20170620
					//�����ύX
					m_MoveRotFlg = false;

					//���W�擾
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//���v�Z
					Vector3 dis1 = pos2 - pos1;
					Vector3 dis2 = pos1 - pos2;

					//�p�x�v�Z
					float angle1 = atan2(dis1.z, dis1.x) + -90 * 3.14159265f / 180;
					float angle2 = atan2(dis2.z, dis2.x) + -90 * 3.14159265f / 180;

					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);

					//Abe20170620

				}
				//�E��]
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					//Abe20170620
					//�u�[�X�g�N��
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					m_rot += m_rotSpeed * App::GetApp()->GetElapsedTime();
					//�ꉞ���[�v�����Ƃ�
					if (m_rot > 360)
					{
						m_rot = 0;
					}

					//Abe20170620
					//�����ύX
					m_MoveRotFlg = false;

					//���W�擾
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//���v�Z
					Vector3 dis1 = pos2 - pos1;
					Vector3 dis2 = pos1 - pos2;

					//�p�x�v�Z
					float angle1 = atan2(dis1.z, dis1.x) + 90 * 3.14159265f / 180;
					float angle2 = atan2(dis2.z, dis2.x) + 90 * 3.14159265f / 180;

					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);

					//Abe20170620

				}
			}
		}
		
		//�X�e�[�W�O�̐���
		StintArea();
		//�v���C���[�̈ʒu�Ɖ�]�X�V
		PosRotUpdate();
	}

	//----------------------------------------------
	//�֐�
	//----------------------------------------------
	//�v���C���[�ʒu��]�X�V
	void PlayerControl::PosRotUpdate()
	{
		//�E��0�ō���1
		Vector3 posright = GetComponent<Transform>()->GetPosition();
		posright += Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player1->GetComponent<Transform>()->SetPosition(posright);

		//m_Debugtxt->SetText(Util::FloatToWStr(GetComponent<Transform>()->GetPosition().y));

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


		//�ړ����ĂȂ���Ό�������
		if (m_MoveRotFlg)
		{
			//�p�x�v�Z
			float angle1 = atan2(dis1.z, dis1.x);
			float angle2 = atan2(dis2.z, dis2.x);

			m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
			m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
		}

		//��]�߂�
		m_MoveRotFlg = true;

	}


	//�A�j���[�V�����X�V
	void PlayerControl::UpdateAnimation()
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

	//�^�[�Q�b�g�����O�ʒu�X�V
	void PlayerControl::UpdateTargetRing()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		pos.y = GetComponent<Transform>()->GetPosition().y + 0.5f;
		m_TargetRing->GetComponent<Transform>()->SetPosition(pos);
	}
	//----------------------------------------------
	//���̑�(�A�N�Z�T�[�Ƃ�)
	//----------------------------------------------
	//��̂̍��W��vector�R���e�i�œn��
	vector<Vector3> PlayerControl::GetPlayerSPos_RETURNvectorVec3()
	{
		vector<Vector3> vec3;
		vec3.push_back(m_Player1->GetComponent<Transform>()->GetPosition());
		vec3.push_back(m_Player2->GetComponent<Transform>()->GetPosition());
		return vec3;
	}	//////////////////////////////////////////////////////////////
		//�����蔻��̗L��
	void PlayerControl::SetActiveCollision(bool flg) {
		//�����蔻��
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(flg);
		}
		else {
			throw BaseException(
				L"�G���[",
				L"�X�^�[�g�֐��̒��uSetActiveCollision�v",
				L"PtrCollisionSand�����݂��Ă��܂���"
			);
		}
	}
	//�G���A�����֐�
	void PlayerControl::StintArea() {
	
		auto PlayerControlTrans = GetComponent<Transform>();
		Vector3 PlayerControlPos = PlayerControlTrans->GetPosition();
		Vector3 PlayerL_Pos = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerR_Pos = m_Player2->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerL_Scale = m_Player1->GetComponent<Transform>()->GetScale();
		Vector3 PlayerR_Scale = m_Player2->GetComponent<Transform>()->GetScale();
		auto Elap = App::GetApp()->GetElapsedTime();
		//�E�@PLayerR
		if (m_StageSize.x < PlayerR_Pos.x) {
			float n2 = m_StageSize.x - PlayerR_Pos.x;
			PlayerControlPos.x += n2;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);
		}
		//PLayerL
		if (m_StageSize.x < PlayerL_Pos.x) {
			float n2 = m_StageSize.x - PlayerL_Pos.x;
			PlayerControlPos.x += n2;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//���@PLayerL
		if (-m_StageSize.x > PlayerL_Pos.x)
		{
			float n = -m_StageSize.x + (-PlayerL_Pos.x);
			PlayerControlPos.x += n;

			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PlayerR
		if (-m_StageSize.x > PlayerR_Pos.x) {
			float n = -m_StageSize.x + (-PlayerR_Pos.x);
			PlayerControlPos.x += n;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//��@PlayerL
		if (m_StageSize.y - 1.5 < PlayerL_Pos.z) {
			float n3 = (m_StageSize.y - 1.5) - PlayerL_Pos.z;
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PLayerR
		if (m_StageSize.y - 1.5 < PlayerR_Pos.z) {
			float n3 = (m_StageSize.y - 1.5) - PlayerR_Pos.z;
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//���@PlayerL
		if (-m_StageSize.y > PlayerL_Pos.z) {
			float n3 = -m_StageSize.y + (-PlayerL_Pos.z);
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PLayerR
		if (-m_StageSize.y > PlayerR_Pos.z) {
			float n3 = -m_StageSize.y + (-PlayerR_Pos.z);
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
	}
	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	�p�r: �v���C���[HP����
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	PlayerHP::PlayerHP(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr)
	{
	}
	PlayerHP::~PlayerHP() {}

	//������
	void PlayerHP::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(0, 0, 0);
		SetInvincible(false);
		SetHit(false);
	}
	void PlayerHP::OnUpdate() {
		if (!GetInvincible() && GetHit()) {
			GetStage()->GetSharedGameObject<Player_Life>(L"Life")->LifeDown(GetDamage_int());
			SetInvincible(true);
			

			if (GetDamage_int() > 0) {

				SetDamage_int(0);
			}
		}
		else if (GetInvincible()) {
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			InvinciblecCunt += ElapsedTime_F;
			if (InvinciblecCunt > InvinciblecLimit) {
				SetInvincible(false);
				SetHit(false);
				InvinciblecCunt = 0.0f;
			}
		}
	}

	//�V�[���h
	PlayerShield::PlayerShield(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scele , shared_ptr<GameObject> PtrPlayer) :
		GameObject(StagePtr),
		m_Pos(Pos),
		m_Scele(Scele),
		m_Player(PtrPlayer)
	{}
	void PlayerShield::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetRotation(0, 0, 0);
		Trans->SetScale(m_Scele);


		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"TEST_AO_TX");
		SetAlphaActive(true);
		PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
		m_OpacityColor = 1.0f;
		SetDrawActive(false);
		SetDrawLayer(10);
	}
	void PlayerShield::OnUpdate() {
		auto PlayerLifePtr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);
		auto Pos = m_Player->GetComponent<Transform>()->GetPosition();
		auto PtrDraw = GetComponent<PNTStaticDraw>();
		GetComponent<Transform>()->SetPosition(Pos.x,Pos.y+ 0.5 ,Pos.z);
		//�ŏ���HP�̕ۑ�
		if (InitHpSaveflg) {
			m_HPSave = PlayerLifePtr->GetLife();
			InitHpSaveflg = false;
			
		}
		//�O���HP�ƈႤ�ꍇ
		if (PlayerLifePtr->GetLife() != m_HPSave) {
			//�ۑ�HP�̍X�V
			m_HPSave = PlayerLifePtr->GetLife();
			//���o�t���O��ON
			m_OnShield = true;
			m_Opacity = 1.0f;
			SetDrawActive(true);
		}

		//HP�������@�V�[���h���Ԃ��Ȃ�_�ł���
		if (m_OnShield && PlayerLifePtr->GetLife() != 1) {
				//HP������Ƃ�
				m_Opacity -= 0.05;
				PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
				if (m_Opacity < 0.0f) {
					SetDrawActive(false);
					m_OnShield = false;
				}
		}
		else if(m_OnShield && PlayerLifePtr->GetLife() == 1){
			if (m_Once == true) {	
				PtrDraw->SetTextureResource(L"TEST_Red_TX");
				m_Opacity = 0.5f;
				SetUpdateActive(true);
				SetDrawActive(true);
				m_Once = false;
			}
			if (m_Opacity <= 0.0f) {
				m_OpacityColor *= -1.0f;
			}
			else if (m_Opacity >= 0.5f) {
				m_OpacityColor *= -1.0f;
			}
			m_Opacity += 0.05 * m_OpacityColor;
			PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
		}
		//HP���O�ɂȂ�����
		if (PlayerLifePtr->GetLife() <= 0.0f) {
		SetUpdateActive(false);
		SetDrawActive(false);
		}
		
	}

	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	�p�r�@�v���C���[�u�[�X�g
	////--------------------------------------------------------------------------------------
	PlayerBoost::PlayerBoost(const shared_ptr<Stage>& StagePtr,const Vector3& InitPos,const Vector3& scale,const wstring& TextureName,const int& DeleteTime, const int& PlusTimeSpeed):
	GameObject(StagePtr),
	m_InitPos(InitPos),
	m_scale(scale),
	m_TextureName(TextureName),
	m_DeleteTime(DeleteTime),
	m_PlusTimeSpeed(PlusTimeSpeed)
	
	{}
	void PlayerBoost::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_scale);
		Trans->SetRotation(0, 0, 0);
			//�`��ݒ�
			auto Draw = AddComponent<PNTStaticDraw>();
			Draw->SetMeshResource(L"DEFAULT_SQUARE");
			Draw->SetTextureResource(m_TextureName);
			SetAlphaActive(true);
	}
	void PlayerBoost::OnUpdate() {
		m_CuntTime += App::GetApp()->GetElapsedTime()* m_PlusTimeSpeed;
		if (m_CuntTime > m_DeleteTime) {
			SetDrawActive(false);
			SetUpdateActive(false);

		}
	}

	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	�p�r:�v���C���[�p�[�e�B�N��
	////--------------------------------------------------------------------------------------
	//PlayerParticle::PlayerParticle(const  shared_ptr<Stage>& StagePtr) :
	//GameObject(StagePtr)
	//{}

	//void PlayerParticle::OnUpdate(){
	//	//�p�[�e�B�N�����o���Ă��邩�H
	//	if (m_NowParticleFlg)
	//	{
	//		bool CreateFlg = false;
	//		//�ʒu�X�V
	//		
	//		for (auto v : m_Particle)
	//		{
	//			float m_Count = 0;
	//			//�`�悳��Ă���
	//			if (v->GetDrawActive())
	//			{
	//				while(flg == true) 
	//				{
	//					m_Count += App::GetApp()->GetElapsedTime()/2;
	//					if (m_Count > 10) {
	//						v->SetDrawActive(false);
	//						m_Count = 0;
	//						flg = false;
	//					}
	//				}
	//			}
	//			flg = true;
	//		}
	//		if (CreateFlg)
	//		{
	//			//���������琶��
	//			CreateParticle();
	//		}
	//	}
	//	
	//}
	//void PlayerParticle::OnParticle(Vector3 InitPos, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int Layer, float deleteTime){
	//	//�����ʒu
	//	m_InitPos = InitPos;
	//	//�傫���ݒ�
	//	m_Scale = scale;
	//	//�e�N�X�`���̖��O�ݒ�
	//	m_TextureName = TextureName;
	//	//���ŉ��o�ݒ�
	//	m_DeleteFlg = DeleteFlg;
	//	//�쐬�Ԋu�ݒ�
	//	m_CreateInterval = CreateInterval;
	//	//���C���[�ݒ�
	//	m_Layer = Layer;
	//	//���Ŏ���
	//	m_DeleteTime = deleteTime;

	//	m_NowParticleFlg = true;

	//}
	//void PlayerParticle::CreateParticle() {
	//	//����
	//	auto obj = GetStage()->AddGameObject<GameObject>();
	//	auto Trans = obj->AddComponent<Transform>();
	//	//�����ʒu����
	//	Vector3 pos = m_InitPos;
	//	//�ʒu�ݒ�
	//	Trans->SetPosition(pos);
	//	//�傫���ݒ�
	//	Trans->SetScale(m_Scale);

	//	//�`��ݒ�
	//	auto Draw = obj->AddComponent<PNTStaticDraw>();
	//	Draw->SetMeshResource(L"DEFAULT_SQUARE");
	//	Draw->SetTextureResource(m_TextureName);
	//	obj->SetAlphaActive(true);
	//	obj->SetDrawLayer(m_Layer);

	//
	//	//�e���̏����鎞��
	//	m_Particle.push_back(obj);
	//}

	
	
	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	�p�r: �X�J�C�X�t�B�A
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	SkySphere::SkySphere(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SkySphere::~SkySphere() {}

	//������
	void SkySphere::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_Position);


		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"Background_TX");
		SetAlphaActive(true);

	}
	
	

	//--------------------------------------------------------------------------------------
	//	Player�u�[�X�gSP �X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	PlayerBoostSP::PlayerBoostSP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, Vector3 Rotation) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + txtdire, txtname, L"anime_1"),
		m_Pos(pos),
		m_Scale(scale),
		m_Rotation(Rotation)
	{}

	void PlayerBoostSP::OnCreate()
	{
	
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(Vector3(m_Rotation.x * XM_2PI / 180, -m_Rotation.y*XM_2PI / 180, -m_Rotation.z*XM_2PI / 180));

		//�A�j���[�V�����֘A
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
		);
		SetToAnimeMatrix(mat);

		//�e�N���X��Create
		SS5ssae::OnCreate();
		//�b������̃t���[����
		SetFps(60.0f);
		//���[�v����
		SetLooped(true);


		//�����x�L����
		SetAlphaActive(true);
		//�`��
		SetDrawActive(true);
		//�\�����C���[
		SetDrawLayer(2);

	}

	void PlayerBoostSP::OnUpdate()
	{
		
		//�A�j���\�V�����X�V
		UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 4);
	}
	//Abe20170529

	
	
	//////////////////////////////////////////////////////////////
}




