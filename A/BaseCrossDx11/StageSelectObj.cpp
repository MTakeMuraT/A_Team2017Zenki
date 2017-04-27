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
			auto PtrDraw = PlayerPtr->AddComponent<PNTStaticDraw>();
			PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
			PtrDraw->SetTextureResource(L"TRACE_TX");

			//��������
			SetAlphaActive(true);

			//Rigidbody������
			auto PtrRedid = PlayerPtr->AddComponent<Rigidbody>();
			//�Փ˔��������
			auto PtrCol = PlayerPtr->AddComponent<CollisionSphere>();
			
			//�v���C���[�̃A�N�Z�T?
			m_Player.push_back(PlayerPtr);
		}

	}

	void SelectPlayer::OnUpdate()
	{
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�ړ�
			Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY) * m_Speed;
			for (auto obj : m_Player)
			{
				//����ł�Ԃ͕ʂ�Velocity���������̂ł����X�V���Ă������Ȃ�
				obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
			}

			if (!m_SandFlg)
			{
				//��]����
				Rot();
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

				//A�{�^����������
				if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					m_SandFlg = true;
				}
			}
		}

		//�����͂��ޏ�ԂɂȂ��Ă���
		if (m_SandFlg)
		{
			SandMove();
		}
	}

	//��]����
	void SelectPlayer::Rot()
	{
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//����
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
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
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);

				//�Q�̖�
				dif = pos2 - centerpos;
				float angle2 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				vel = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel;
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			//�E��
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
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
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);

				//�Q�̖�
				dif = pos2 - centerpos;
				float angle2 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//�p�x���狁�߂Ē��S����̋�����������
				vel = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel;
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

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

		//�����o�O�o�邩��O�̂���
		for (auto obj : m_Player)
		{
			obj->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
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
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"SKY_TX");

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
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(Vector3(660,360,1));
		Trans->SetRotation(0, 0, 0);

		//�`��
		auto Draw = CheckBack->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_SIRO_TX");
		
		//���C���[�ݒ�
		CheckBack->SetDrawLayer(2);
		//�����x�L����
		CheckBack->SetAlphaActive(true);

		//�����Ƃ�
		CheckBack->SetDrawActive(false);

		m_CheckBack = CheckBack;
		
		
		//YES�����쐬---------------------------------
		auto YesSprite = GetStage()->AddGameObject<GameObject>();

		//���W
		auto YTrans = YesSprite->AddComponent<Transform>();
		YTrans->SetPosition(150, -70, 0);
		YTrans->SetScale(240, 120, 1);
		YTrans->SetRotation(0, 0, 0);

		//�`��
		auto YDraw = YesSprite->AddComponent<PCTSpriteDraw>();
		YDraw->SetTextureResource(L"SELECT_YES_TX");
		
		//���C���[�ݒ�
		YesSprite->SetDrawLayer(3);

		//�����x�L����
		YesSprite->SetAlphaActive(true);

		//�����Ƃ�
		YesSprite->SetDrawActive(false);

		m_CheckYes = YesSprite;
		
		//No�����쐬------------------------------------
		auto NoSprite = GetStage()->AddGameObject<GameObject>();

		//���W
		auto NTrans = NoSprite->AddComponent<Transform>();
		NTrans->SetPosition(-150, -70, 0);
		NTrans->SetScale(240, 120, 1);
		NTrans->SetRotation(0, 0, 0);

		//�`��
		auto NDraw = NoSprite->AddComponent<PCTSpriteDraw>();
		NDraw->SetTextureResource(L"SELECT_YES_TX");

		//���C���[�ݒ�
		NoSprite->SetDrawLayer(3);

		//�����x�L����
		NoSprite->SetAlphaActive(true);

		//�����Ƃ�
		NoSprite->SetDrawActive(false);

		m_CheckNo = NoSprite;

		//�m�F�����쐬------------------------------------
		auto CheckLogo = GetStage()->AddGameObject<GameObject>();
		//���W
		auto CLTrans = CheckLogo->AddComponent<Transform>();
		CLTrans->SetPosition(0, 80, 0);
		CLTrans->SetScale(550, 120, 1);
		CLTrans->SetRotation(0, 0, 0);

		//�`��
		auto CLDraw = CheckLogo->AddComponent<PCTSpriteDraw>();
		CLDraw->SetTextureResource(L"SELECT_YES_TX");

		//���C���[�ݒ�
		CheckLogo->SetDrawLayer(3);

		//�����x�L����
		CheckLogo->SetAlphaActive(true);

		//�����Ƃ�
		CheckLogo->SetDrawActive(false);

		m_CheckLogo = CheckLogo;

		//�J�[�\���쐬------------------------------------
		auto CursorSprite = GetStage()->AddGameObject<GameObject>();
		//���W
		auto CTrans = CursorSprite->AddComponent<Transform>();
		CTrans->SetPosition(150, -70, 0);
		CTrans->SetScale(100, 100, 1);
		CTrans->SetRotation(0, 0, 0);

		//�`��
		auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
		CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

		//���C���[�ݒ�
		CursorSprite->SetDrawLayer(4);

		//�����x�L����
		CursorSprite->SetAlphaActive(true);

		//�����Ƃ�
		CursorSprite->SetDrawActive(false);

		m_Cursor = CursorSprite;



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
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-150, -70, 0));
				}
				//�E
				else if (CntlVec[0].fThumbLX > 0.5f)
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -70, 0));
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
						auto ScenePtr = App::GetApp()->GetScene<Scene>();
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
		m_CheckYes->SetDrawActive(true);
		m_CheckNo->SetDrawActive(true);
		m_CheckLogo->SetDrawActive(true);
		m_Cursor->SetDrawActive(true);
	}

	//�I��
	void GoStageCheck::CloseCheck()
	{
		m_Dispflg = false;
		m_CheckBack->SetDrawActive(false);
		m_CheckYes->SetDrawActive(false);
		m_CheckNo->SetDrawActive(false);
		m_CheckLogo->SetDrawActive(false);
		m_Cursor->SetDrawActive(false);

		//���N������Ƃ��p�ɏ�����
		//No�ɏ�����
		m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -70, 0));
		m_selectnum = 0;

		//�v���C���[�̃A�b�v�f�[�g�ĊJ
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetUpdateActive(true);
		//���ꂳ����
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();
	}
	//Abe20170421

}