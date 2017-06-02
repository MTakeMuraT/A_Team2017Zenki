#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	�t���[���X�v���C�g
	//--------------------------------------------------------------------------------------
	SelectFlame::SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectFlame::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_FLAME_TX");

		//�����x�ݒ�
		SetAlphaActive(true);
		//���C���[�ݒ�
		SetDrawLayer(m_layer);
	}

	//Abe20170525
	//--------------------------------------------------------------------------------------
	//	���S
	//--------------------------------------------------------------------------------------
	SelectLogo::SelectLogo(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectLogo::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_LOGO_TX");

		//�����x�ݒ�
		SetAlphaActive(true);
		//���C���[�ݒ�
		SetDrawLayer(m_layer);
	}
	//Abe20170525

	//--------------------------------------------------------------------------------------
	//	�v���C���[
	//--------------------------------------------------------------------------------------
	SelectPlayer::SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,float speed):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_Speed(speed)
	{}

	void SelectPlayer::OnCreate()
	{
		//obj�쐬
		for (int i = 0; i < 2; i++)
		{
			auto PlayerPtr = GetStage()->AddGameObject<GameObject>();
			//���W�ݒ�
			auto Trans = PlayerPtr->AddComponent<Transform>();
			//���W�ύX
			Vector3 pos = m_InitPos;
			pos.x += -m_DifLength + (i * m_DifLength*2);
			Trans->SetPosition(pos);
			Trans->SetScale(m_InitScale);
			Trans->SetRotation(0, 0, 0);

			//�`��ݒ�
			auto PtrDraw = PlayerPtr->AddComponent<PNTBoneModelDraw>();
			
			PtrDraw->SetMeshResource(L"Player_Model");
		//	PtrDraw->SetTextureResource(L"TRACE_TX");

			//��������
			SetAlphaActive(true);

			//Rigidbody������
			auto PtrRedid = PlayerPtr->AddComponent<Rigidbody>();
			//�Փ˔��������
			auto PtrCol = PlayerPtr->AddComponent<CollisionSphere>();
			
			PlayerPtr->SetDrawLayer(0);

			//�v���C���[�̃A�N�Z�T?
			m_Player.push_back(PlayerPtr);
			PtrDraw->AddAnimation(L"Wait", 0, 30, true, 30.0f);
			PtrDraw->AddAnimation(L"LeftRot", 80, 15, false, 30.0f);
			PtrDraw->AddAnimation(L"RightRot", 120, 15, false, 30.0f);

		}
		//�f�o�b�O��������
		auto debtxt = GetStage()->AddGameObject<DebugTxt>();
		debtxt->SetLayer(10);
		//�F�ԂɕύX
		debtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		debtxt->SetScaleTxt(40);

		m_Debugtxt = debtxt;
		//Abe20170524
	
		

	}

	void SelectPlayer::OnUpdate()
	{
		AnimationWait();
		Model();
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

#pragma region //*******�f�o�b�O�p*******//
		//*******�f�o�b�O�p*******//
		//auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();

		////�ړ�
		//Vector2 InputXY = Vector2((KeylVec.m_bPushKeyTbl[VK_RIGHT] + -KeylVec.m_bPushKeyTbl[VK_LEFT]), (KeylVec.m_bPushKeyTbl[VK_UP] + -KeylVec.m_bPushKeyTbl[VK_DOWN])) * m_Speed;
		////�����X�e�[�W���������z����Ȃ瓮�����Ȃ�
		////�P�̖ڂ̍��W
		//Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		////�Q�̖ڂ̍��W
		//Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
		//ppos1.x += InputXY.x * App::GetApp()->GetElapsedTime();
		//ppos1.z += InputXY.y * App::GetApp()->GetElapsedTime();
		//ppos2.x += InputXY.x * App::GetApp()->GetElapsedTime();
		//ppos2.z += InputXY.y * App::GetApp()->GetElapsedTime();
		////����(��-20�E+66��+10��-36)
		//if ((ppos1.x < MoveLimit.x || ppos2.x < MoveLimit.x) || (ppos1.x > MoveLimit.y || ppos2.x > MoveLimit.y))
		//{
		//	InputXY.x = 0;
		//}
		//if ((ppos1.z < MoveLimit.w || ppos2.z < MoveLimit.w) || (ppos1.z > MoveLimit.z || ppos2.z > MoveLimit.z))
		//{
		//	InputXY.y = 0;
		//}
		////wstring txt;
		////txt += L"1X:" + Util::FloatToWStr(ppos1.x) + L"1Z:" + Util::FloatToWStr(ppos1.z) +
		////	L"\n2X:" + Util::FloatToWStr(ppos2.x) + L"1Z:" + Util::FloatToWStr(ppos2.z);
		////dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		//Vector3 ppos31 = (ppos1 + ppos2) / 2;

		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(L"X:" + Util::FloatToWStr(ppos31.x) + L"Z:" + Util::FloatToWStr(ppos31.z));

		////*******�f�o�b�O�p*******//

		////�ړ�
		//for (auto obj : m_Player)
		//{
		//	//����ł�Ԃ͕ʂ�Velocity���������̂ł����X�V���Ă������Ȃ�
		//	obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
		//}

#pragma endregion

		if (CntlVec[0].bConnected)
		{
			Vector3 ppos11 = m_Player[0]->GetComponent<Transform>()->GetPosition();
			Vector3 ppos21 = m_Player[1]->GetComponent<Transform>()->GetPosition();

			Vector3 ppos31 = (ppos11 + ppos21) / 2;

			//�ړ�
			Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY) * m_Speed;

			//�����X�e�[�W���������z����Ȃ瓮�����Ȃ�
			//����(��-20�E+66��+10��-36)
			//�P�̖ڂ̍��W
			Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
			//�Q�̖ڂ̍��W
			Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
			ppos1.x += InputXY.x * App::GetApp()->GetElapsedTime();
			ppos1.z += InputXY.y * App::GetApp()->GetElapsedTime();
			ppos2.x += InputXY.x * App::GetApp()->GetElapsedTime();
			ppos2.z += InputXY.y * App::GetApp()->GetElapsedTime();
			//����(��-20�E+66��+10��-36)
			if ((ppos1.x < MoveLimit.x || ppos2.x < MoveLimit.x) || (ppos1.x > MoveLimit.y || ppos2.x > MoveLimit.y))
			{
				InputXY.x = 0;
			}
			if ((ppos1.z < MoveLimit.w || ppos2.z < MoveLimit.w) || (ppos1.z > MoveLimit.z || ppos2.z > MoveLimit.z))
			{
				InputXY.y = 0;
			}

			//�ړ�
			for (auto obj : m_Player)
			{
				//����ł�Ԃ͕ʂ�Velocity���������̂ł����X�V���Ă������Ȃ�
				obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
			}

			if (!m_SandFlg)
			{
				//��]����
				//Rot();
				if (!m_CancelFlg)
				{
					//A�{�^�������Ă�ԗ����
					if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A)
					{
						//�i�ޕ��������߂�
						Vector3 difpos = m_Player[0]->GetComponent<Transform>()->GetPosition() - m_Player[1]->GetComponent<Transform>()->GetPosition();
						//������x����ĂȂ������m�F ���a10�ȉ�
						if (difpos.x*difpos.x + difpos.z*difpos.z < 100)
						{
							//abs���g����if�Ŕ��]��������x���Ȃ邯�ǂ���Ȃɏd�������Ȃ�����������ˁH
							float xPlusz = abs(difpos.x) + abs(difpos.z);
							difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
							difpos *= m_Speed;

							for (auto obj : m_Player)
							{
								obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
								difpos *= -1;
							}
						}
					}
				}

				if (m_CancelFlg)
				{
					if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
					{
						m_CancelFlg = false;
					}
				}
				else
				{
					//A�{�^����������
					if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
					{
						m_SandFlg = true;
					}
				}
			}
		}

		//�����͂��ޏ�ԂɂȂ��Ă���
		if (m_SandFlg)
		{
			SandMove();
		}

		//�����ݒ�
		for (auto obj : m_Player)
		{
			Vector3 pppos = obj->GetComponent<Transform>()->GetPosition();
			pppos.y = 0.6f;
			obj->GetComponent<Transform>()->SetPosition(pppos);
		}
		//�����Е��Ɍ���
		Vector3 ppos2 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		Vector3 ppos3 = m_Player[1]->GetComponent<Transform>()->GetPosition();
		Vector3 dif = ppos3 - ppos2;
		float angle = atan2(dif.z, dif.x) * -1;
		angle += 90 * 3.14159265f / 180;
		Vector3 dif2 = ppos2 - ppos3;
		float angle2 = atan2(dif2.z, dif2.x) * -1;
		angle2 += 90 * 3.14159265f / 180;


		m_Player[0]->GetComponent<Transform>()->SetRotation(0, angle2, 0);
		m_Player[1]->GetComponent<Transform>()->SetRotation(0, angle, 0);
	}

	//��]����
	void SelectPlayer::Rot()
	{
		
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			
			//����
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				m_WaitFlg = false;
				AnimationRotL();
				//���W�擾
				Vector3 pos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
				Vector3 centerpos = (pos1 + pos2) / 2;

				//���S����̊p�x�Z�o���ĉ��Z���Čv�Z���Ȃ����č��W�ɓ����
				Vector3 dif = pos1 - centerpos;
				float angle1 = atan2(dif.z, dif.x) * 180/3.14159265f;
				angle1 += 360;
				int an1 = (int)angle1 % 360;
				an1 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				Vector3 vel = Vector3(cos(an1*3.14159265f / 180), 0, sin(an1*3.14159265f / 180)) * m_DifLength;
				pos1 = centerpos + vel;

				//�Q�̖�
				Vector3 dif2 = pos2 - centerpos;
				float angle2 = atan2(dif2.z, dif2.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				Vector3 vel2 = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel2;

#pragma region �����o������
				//�����o������
				//�������o��
				if (pos1.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//�E�����o��
				if (pos1.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//�㉟���o��
				if (pos1.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				//�������o��
				if (pos1.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				
#pragma endregion

				//�ړ�
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			else {
				m_WaitFlg = true;
			}
			//�E��
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				m_WaitFlg = false;
				AnimationRotR();
				//���W�擾
				Vector3 pos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
				Vector3 centerpos = (pos1 + pos2) / 2;

				//���S����̊p�x�Z�o���ĉ��Z���Čv�Z���Ȃ����č��W�ɓ����
				Vector3 dif = pos1 - centerpos;
				float angle1 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle1 += 360;
				int an1 = (int)angle1 % 360;
				an1 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				Vector3 vel = Vector3(cos(an1*3.14159265f / 180), 0, sin(an1*3.14159265f / 180)) * m_DifLength;
				pos1 = centerpos + vel;

				//�Q�̖�
				Vector3 dif2 = pos2 - centerpos;
				float angle2 = atan2(dif2.z, dif2.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				Vector3 vel2 = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel2;

#pragma region �����o������
				//�����o������
				//�������o��
				if (pos1.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//�E�����o��
				if (pos1.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//�㉟���o��
				if (pos1.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				//�������o��
				if (pos1.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
#pragma endregion

				//�ړ�
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			else {
				m_WaitFlg = true;
			}
		}
	}

	//������������
	void SelectPlayer::SandMove()
	{
		//�߂Â��ĂȂ����
		if (!m_SandFinishFlg)
		{
			//�i�ޕ��������߂�
			Vector3 difpos = m_Player[1]->GetComponent<Transform>()->GetPosition() - m_Player[0]->GetComponent<Transform>()->GetPosition();
			//������x ���a1.5���炢�ȏ�
			if (difpos.x*difpos.x + difpos.z*difpos.z > 4)
			{
				//abs���g����if�Ŕ��]��������x���Ȃ邯�ǂ���Ȃɏd�������Ȃ�����������ˁH
				float xPlusz = abs(difpos.x) + abs(difpos.z);
				difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
				//���K���ł��Ă邩�m�F
				//GetComponent<StringSprite>()->SetText(L"x:" + Util::FloatToWStr(difpos.x) + L"z:" + Util::FloatToWStr(difpos.z));
				difpos *= m_Speed;

				for (auto obj : m_Player)
				{
					obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
					difpos *= -1;
				}
			}
			//�ݒ肵�������܂ŋ߂Â���
			else
			{
				m_SandFinishFlg = true;
			}
		}
		else
		{
			//�i�ޕ��������߂�
			Vector3 difpos = m_Player[0]->GetComponent<Transform>()->GetPosition() - m_Player[1]->GetComponent<Transform>()->GetPosition();
			//�����̍��W�̍���藣�ꂽ��(����m_difLength�͔��a�̂��߂Q�{*�Q�̕�)
			if (difpos.x*difpos.x + difpos.z*difpos.z < 4*(m_DifLength*m_DifLength))
			{
				//abs���g����if�Ŕ��]��������x���Ȃ邯�ǂ���Ȃɏd�������Ȃ�����������ˁH
				float xPlusz = abs(difpos.x) + abs(difpos.z);
				difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
				//���K���ł��Ă邩�m�F
				//GetComponent<StringSprite>()->SetText(L"x:" + Util::FloatToWStr(difpos.x) + L"z:" + Util::FloatToWStr(difpos.z));
				difpos *= m_Speed;

				for (auto obj : m_Player)
				{
					obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
					difpos *= -1;
				}
			}
			//����������藣�ꂽ
			else
			{
				m_SandFlg = false;
				m_SandFinishFlg = false;
			}
		}
	}

	void SelectPlayer::SetPlayerUpdate(bool flg)
	{
		SetUpdateActive(flg);

		//�L�����Z�������Ƃ��ɓ����̖h�~
		m_CancelFlg = true;

		//�����o�O�o�邩��O�̂���
		for (auto obj : m_Player)
		{
			obj->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
	}

	//���W�ړ�
	void SelectPlayer::SetPos(Vector3 pos)
	{
		int count = 0;
		for (auto obj : m_Player)
		{
			obj->GetComponent<CollisionSphere>()->SetUpdateActive(false);
			Vector3 pos1 = pos;
			pos1.x += -m_DifLength + (count * m_DifLength * 2);
			obj->GetComponent<Transform>()->SetPosition(pos1);
			count++;
		}
	}

	//���W�擾
	Vector3 SelectPlayer::GetPos()
	{
		Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();

		return (ppos1 + ppos2) / 2;
	}

	void SelectPlayer::ActiveMove()
	{	
		for (auto obj : m_Player)
		{
			obj->GetComponent<CollisionSphere>()->SetUpdateActive(true);
		}
	}
	//���f���̌���
	void SelectPlayer::Model() {
		if (m_Model_flg) {
			auto Player1 = m_Player[0];
			auto Player2 = m_Player[1];
			Player1->GetComponent<Transform>()->SetRotation(0, -XM_PI / 2, 0);
			Player2->GetComponent<Transform>()->SetRotation(0, XM_PI / 2, 0);

			m_Model_flg = false;
		}
	}
	//�ҋ@�A�j���[�V����
	void SelectPlayer::AnimationWait() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		if (!(PtrDraw->GetCurrentAnimation() == L"Wait") && m_WaitFlg) {
			PtrDraw->ChangeCurrentAnimation(L"Wait");
			PtrDraw2->ChangeCurrentAnimation(L"Wait");
		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//��]�A�j���V�����֐� ��
	void SelectPlayer::AnimationRotL() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();


		if (PtrDraw->GetCurrentAnimation() != L"LeftRot"){
			PtrDraw->ChangeCurrentAnimation(L"LeftRot");
			PtrDraw2->ChangeCurrentAnimation(L"LeftRot");
		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//�E
	void SelectPlayer::AnimationRotR() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();

		if (!(PtrDraw->GetCurrentAnimation() == L"RightRot")) {
			PtrDraw->ChangeCurrentAnimation(L"RightRot");
			PtrDraw2->ChangeCurrentAnimation(L"RightRot");

		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//�A�j���[�V�����X�V�֐�
	bool SelectPlayer::UpdateAnyAnimation() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
	}
	bool SelectPlayer::UpdateAnyAnimation2() {
		auto PtrDraw = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
	}

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�̔�
	//--------------------------------------------------------------------------------------
	StageBox::StageBox(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, int num):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_stagenumber(num)
	{}

	void StageBox::OnCreate()
	{
		//���W�ݒ�
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//�`��ݒ�
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		wstring stageString = L"STAGEBOX_" + Util::IntToWStr(m_stagenumber) + L"_TX";
		PtrDraw->SetTextureResource(stageString);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();

	}

	void StageBox::OnUpdate()
	{
		//�v���C���[���P�̈ȏ㓖�����Ă�Ƃ��̂ݏ���
		if (m_PlayerHitFlg)
		{
			//�v���C���[���������Ă鐔���Q��
			if (m_PlayerHitNum == 2)
			{
				//A�{�^��������Ă邩�̏����͂����BA�͂Ȃ���Ȃ���Έ�����Ȃ�����
				CheckGo();
			}
			//�Ȃ�ɂ��������ĂȂ����
			else if(m_PlayerHitNum == 0)
			{
				//�]�v�ȏ������Ȃ��悤�ɐ؂��Ă���(�{���̓A�b�v�f�[�g���̎~�߂�̂������񂾂��ǃo�O��������)
				m_PlayerHitFlg = false;
			}
			m_PlayerHitNum = 0;
		}
	}

	void StageBox::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec)
	{
		//�v���C���[�ȊO���������Ȃ��͂��Ȃ̂łƂ肠��������������v���C���[����
		for (auto obj : OtherVec)
		{
			m_PlayerHitNum++;

			//�v���C���[�̗����t���O�N��
			GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFlgOn();
		}
		if (m_PlayerHitNum > 0)
		{
			m_PlayerHitFlg = true;
		}
	}

	void StageBox::CheckGo()
	{
		//���̈ʒu�ɖ߂�t���O�N��
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();

		//��������A�b�v�f�[�g�~�߂�
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetPlayerUpdate(false);

		//�m�F�E�B���h�E�N��
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->OpenCheck();
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->SetStageNumber(m_stagenumber);
		GetStage()->GetSharedGameObject<EnemyCount>(L"Count", false)->Count();
	}

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�s�����m�F����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	GoStageCheck::GoStageCheck(const shared_ptr<Stage>& StagePtr, Vector2 scale):
		GameObject(StagePtr),
		m_InitScale(scale)
	{}

	void GoStageCheck::OnCreate()
	{
		
		//�w�i�쐬------------------------------------
		auto CheckBack = GetStage()->AddGameObject<GameObject>();
		
		//���W
		auto Trans = CheckBack->AddComponent<Transform>();
		Trans->SetPosition(0, -30, 0);
		Trans->SetScale(Vector3(840,740,1));
		Trans->SetRotation(0, 0, 0);

		//�`��
		auto Draw = CheckBack->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECTCHECK_FLAME_TX");
		
		//���C���[�ݒ�
		CheckBack->SetDrawLayer(2);
		//�����x�L����
		CheckBack->SetAlphaActive(true);

		//�����Ƃ�
		CheckBack->SetDrawActive(false);

		m_CheckBack = CheckBack;
		
		//���g�쐬----------------------------------------
		auto CheckBackIn = GetStage()->AddGameObject<GameObject>();

		//���W
		auto CITrans = CheckBackIn->AddComponent<Transform>();
		CITrans->SetPosition(0, -32, 0);
		CITrans->SetScale(Vector3(660, 580, 1));
		CITrans->SetRotation(0, 0, 0);

		//�`��
		auto CIDraw = CheckBackIn->AddComponent<PCTSpriteDraw>();
		CIDraw->SetTextureResource(L"SELECT_WINDOWIN_TX");

		//���C���[�ݒ�
		CheckBackIn->SetDrawLayer(3);
		//�����x�L����
		CheckBackIn->SetAlphaActive(true);

		//�����Ƃ�
		CheckBackIn->SetDrawActive(false);

		m_CheckBoxIn = CheckBackIn;


		
		//�J�[�\���쐬------------------------------------
		auto CursorSprite = GetStage()->AddGameObject<GameObject>();
		//���W
		auto CTrans = CursorSprite->AddComponent<Transform>();
		CTrans->SetPosition(135, -310, 0);
		CTrans->SetScale(200, 50, 1);
		CTrans->SetRotation(0, 0, 0);

		//�`��
		auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
		CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

		//���C���[�ݒ�
		CursorSprite->SetDrawLayer(3);

		//�����x�L����
		CursorSprite->SetAlphaActive(true);

		//�����Ƃ�
		CursorSprite->SetDrawActive(false);

		m_Cursor = CursorSprite;


		//Abe20170525
		//���ꂼ��̐����쐬
		//�ˌ�
		auto tacklenum = GetStage()->AddGameObject<NumberSprite>(0,Vector2(-25,140),Vector2(100,100),4);
		tacklenum->SetNumDraw(false);
		m_TackleNumSpr = tacklenum;
		//��
		auto shotnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(260, 140), Vector2(100, 100), 4);
		shotnum->SetNumDraw(false);
		m_ShotNumSpr = shotnum;
		//�Ă�
		auto terenum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(-25, -115), Vector2(100, 100), 4);
		terenum->SetNumDraw(false);
		m_TerepoNumSpr = terenum;
		//��
		auto bombnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(260, -115), Vector2(100, 100), 4);
		bombnum->SetNumDraw(false);
		m_BombNumSpr = bombnum;
		//Abe20170525

		//������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));		
	}

	void GoStageCheck::OnUpdate()
	{
		if (m_Dispflg)
		{
			//�R���g���[���擾
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				//�R���g���[���[�����ɓ|���ꂽ��
				if (CntlVec[0].fThumbLX < -0.5f)
				{
					//�I������Yes
					m_selectnum = 1;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-185, -310, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(100, 50, 1));
				}
				//�E
				else if (CntlVec[0].fThumbLX > 0.5f)
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(135, -310, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(200, 50, 1));
				}

				//A��B�{�^�������ꂽ��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					switch (m_selectnum)
					{
						//No
					case 0:
						CloseCheck();
						break;
						//Yes
					case 1:
						//�X�e�[�W�ԍ���Scene.cpp�ɓn��
						//====================================================
						//	�P�`�S(25,25)�@�T�`�P�Q(50,50)�@�P�R�`�P�U(75,75)
						//====================================================
						Vector2 StageSize;
						StageSize = Vector2(25, 25);
						if (m_stageNum >= 1 && m_stageNum <= 4)
						{
							StageSize = Vector2(25, 25);
						}
						else if (m_stageNum >= 5 && m_stageNum <= 12)
						{
							StageSize = Vector2(50, 50);
						}
						else if (m_stageNum >= 13 && m_stageNum <= 16)
						{
							StageSize = Vector2(75, 75);
						}

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//�X�e�[�W�ԍ��Ɣԍ��ɂ������X�e�[�W�̑傫����n��
						ScenePtr->SetStageNumAndStageSize(m_stageNum, StageSize);
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						break;
					}
				}
			}
		}
	}

	//�N��
	void GoStageCheck::OpenCheck()
	{
		m_Dispflg = true;
		m_CheckBack->SetDrawActive(true);
		m_CheckBoxIn->SetDrawActive(true);
		m_Cursor->SetDrawActive(true);
		m_TackleNumSpr->SetNumDraw(true);
		m_ShotNumSpr->SetNumDraw(true);
		m_TerepoNumSpr->SetNumDraw(true);
		m_BombNumSpr->SetNumDraw(true);

	}

	//�I��
	void GoStageCheck::CloseCheck()
	{
		m_Dispflg = false;
		m_CheckBack->SetDrawActive(false);
		m_CheckBoxIn->SetDrawActive(false);
		m_Cursor->SetDrawActive(false);
		m_TackleNumSpr->SetNumDraw(false);
		m_ShotNumSpr->SetNumDraw(false);
		m_TerepoNumSpr->SetNumDraw(false);
		m_BombNumSpr->SetNumDraw(false);



		//���N������Ƃ��p�ɏ�����
		//No�ɏ�����
		m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -300, 0));
		m_selectnum = 0;

		//�v���C���[�̃A�b�v�f�[�g�ĊJ
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetUpdateActive(true);
		//���ꂳ����
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();
	}
	//Abe20170421

	//Abe20170525
	void GoStageCheck::SetEnemyNum(int tackle, int shot, int terepo, int bomb)
	{
		//�����̃X�v���C�g�ύX
		m_TackleNumSpr->SetNum(tackle);
		m_ShotNumSpr->SetNum(shot);
		m_TerepoNumSpr->SetNum(terepo);
		m_BombNumSpr->SetNum(bomb);
	}
	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	�n��
	//--------------------------------------------------------------------------------------
	SelectGroud::SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale)
	{}

	void SelectGroud::OnCreate()
	{
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"STAGESELECTGROUND_TX");
		//�K�v�Œ��------

		
	}
	//Abe20170427

	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����
	//--------------------------------------------------------------------------------------
	SelectGroundSquare::SelectGroundSquare(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,wstring txt,float rot) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale),
		m_Text(txt),
		m_rot(rot)
	{}

	void SelectGroundSquare::OnCreate()
	{
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//�K�v�Œ��------

		SetDrawLayer(1);
		SetAlphaActive(true);
	}
	//Abe20170526

	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����(SS��)
	//--------------------------------------------------------------------------------------
	SelectGroundSquareSS::SelectGroundSquareSS(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, float rot) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + txtdire, txtname, L"anime_1"),
		m_Pos(pos),
		m_Scale(scale),
		m_rot(rot)
	{}

	void SelectGroundSquareSS::OnCreate()
	{
		/*
		//�K�v�Œ��------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//�K�v�Œ��------

		SetDrawLayer(1);
		SetAlphaActive(true);
		*/
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

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


	void SelectGroundSquareSS::OnUpdate()
	{
		//�A�j���\�V�����X�V
		UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 4);

	}
	//Abe20170529

}