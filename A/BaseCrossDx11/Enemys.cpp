#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//************************************************************************
	//	�ˌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************************************************
	TackleEnemy::TackleEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, float speed, int power, int tacklecount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Speed(speed),
		m_Power(power),
		m_TackleCount(tacklecount)
	{}

	void TackleEnemy::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"TACKLE_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//Abe20170526
		//�A�j���[�V�����ǉ�
		Draw->AddAnimation(L"Walk", 0, 30, true, 30);
		Draw->AddAnimation(L"Wait", 40, 30, true, 30);
		Draw->AddAnimation(L"AttackWait", 80, 10, false, 30);
		Draw->AddAnimation(L"AttackNow", 90, 20, true, 30);
		Draw->AddAnimation(L"Damage", 120, 30, false, 30);

		Draw->ChangeCurrentAnimation(L"Wait");
		//Abe20170526

		//��������
		SetAlphaActive(true);
		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");
		
		//Abe20170523
		//���G�͈͍쐬
		//auto circle = GetStage()->AddGameObject<GameObject>();
		auto circle = GetStage()->AddGameObject<SearchCircle>();
		auto TransCi = circle->GetComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		/*
		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		//���C���[�ݒ�
		circle->SetDrawLayer(2);
		*/
		m_SearchCircle = circle;
		//Abe20170523



		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F�ԂɕύX
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);

		//Abe20170515
		//�X�e�[�W�̑傫���擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515


	}

	void TackleEnemy::OnUpdate()
	{
		//Vector3 rot = GetComponent<Transform>()->GetRotation();
		//rot.x = 0;
		//rot.y += 0.01f;
		//rot.z = 0;
		//GetComponent<Transform>()->SetRotation(rot);

		//m_Debugtxt->SetText(L"X:" + Util::FloatToWStr(rot.x) + L"\nY:" + Util::FloatToWStr(rot.y) + L"\nZ:" + Util::FloatToWStr(rot.z));
		
		//�����Ă��
		if (m_ActiveFlg)
		{
			//m_Debugtxt->SetText(Util::IntToWStr(m_State));

			switch (m_State)
			{
				//���G
			case SearchS:
				Search();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				CircleMove();
				break;
				//�T��
			case MoveS:
				Move();
				StageEndCheck();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				CircleMove();
				break;
				//�U��
			case AttackS:
				Attack();
				Rot();
				StageEndCheck();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
				//�N�[���^�C��
			case CoolTimeS:
				CoolTime();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
				//���G
			case MutekiS:
				Muteki();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
			}

			//��]
			Rot();

			//�A�j���[�V�����X�V
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);

		}
	}

	//Abe20170526
	//�A�j���[�V�����ύX
	void TackleEnemy::ChangeAnimation(string txt)
	{
		if (txt == "Walk")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Walk");
		}
		if (txt == "Wait")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
		}
		if (txt == "AttackWait")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"AttackWait");
		}
		if (txt == "AttackNow")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"AttackNow");
		}
		if (txt == "Damage")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Damage");
		}
			/*
			Draw->AddAnimation(L"Walk", 0, 30, true, 30);
		Draw->AddAnimation(L"Wait", 40, 70, true, 30);
		Draw->AddAnimation(L"AttackWait", 80, 90, false, 30);
		Draw->AddAnimation(L"AttackNow", 90, 110, true, 30);
		Draw->AddAnimation(L"Damage", 120, 150, false, 30);
		*/
	}

	//Abe20170526


	//Abe20170519
	void TackleEnemy::Rot()
	{
		//�����Ă鑬�x����p�x�Z�o
		Vector3 vel = m_Velocity;
		//�}�C�i�X���](abs�͏d���̂Ŏg���܂���)
		if (vel.x < 0)
		{
			vel.x *= -1;
		}
		if (vel.z < 0)
		{
			vel.z *= -1;
		}
		//x��z�������l��0.2��肠���
		if (vel.x + vel.z > 0.2f)
		{
			float angle = atan2(m_Velocity.z, m_Velocity.x);
			angle *= -1;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}

		if (!m_TackleFlg && m_State == AttackS)
		{
			//��]
			//�P�̖ڂɓˌ�
			if (m_TargetNum == 1)
			{
				Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
				//�p�x�Z�o
				float angle = atan2(dis.z, dis.x);
				//��]
				angle *= -1;
				GetComponent<Transform>()->SetRotation(0, angle, 0);
			}
			//�Q�̖ڂɓˌ�
			else if (m_TargetNum == 2)
			{
				Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
				//�p�x�Z�o
				float angle = atan2(dis.z, dis.x);
				//��]
				angle *= -1;
				GetComponent<Transform>()->SetRotation(0, angle, 0);
			}

		}
	}
	//Abe20170519

	//Abe20170515
	//�X�e�[�W�̒[�ɂ����������肵�Č������]������
	void TackleEnemy::StageEndCheck()
	{
		//�ʒu[�E]�A[��]�A[��]�A[��]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x+scale.x,pos.z + scale.z,pos.x - scale.x,pos.z - scale.z);
		//�X�e�[�W�̒[�ɓ������Ă邩����
		//�E
		if (m_StageSize.x < PositionPXYMXY.x)
		{
			pos.x = m_StageSize.x - scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (m_StageSize.y < PositionPXYMXY.y)
		{
			pos.z = m_StageSize.y - scale.z;
			m_Velocity.z *= -1;
		}
		//��
		if (-m_StageSize.x > PositionPXYMXY.z)
		{
			pos.x = -m_StageSize.x + scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (-m_StageSize.y > PositionPXYMXY.w)
		{
			pos.z = -m_StageSize.y + scale.z;
			m_Velocity.z *= -1;
		}

	}
	//Abe20170515

	void TackleEnemy::Search()
	{
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�
		//�P�̖�
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
			/*1A
			//�`���[�W���̂Ԃ�Ԃꒆ�S���W���L�^
			//m_BurePos = GetComponent<Transform>()->GetPosition();
			*/
		}
		//�Q�̖�
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//m_Debugtxt->SetText(Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)) + L"\n" + Util::FloatToWStr(distance*distance));
		//m_Debugtxt->SetText(L"dis:" + Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)));

		//��莞�ԂŒT����Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}
	}

	void TackleEnemy::Move()
	{
		//�����_����2�b���炢�i��
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 2)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			//�Ȃ񂩃I�u�W�F�N�g�ɓ�����������Velocity�𔽓]���邯�ǂ���͕ʂ̂Ƃ��ł���
			GetComponent<Transform>()->SetPosition(pos);


			//���G--------------------------------
			//�ʒu���擾
			Vector3 mypos = GetComponent<Transform>()->GetPosition();
			Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
			float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

			//�����𑪂�
			//�P�̖�
			Vector3 dis = pos1 - mypos;
			if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
			{
				ToAttack(1);
				/*1A
				//�`���[�W���̂Ԃ�Ԃꒆ�S���W���L�^
				//m_BurePos = GetComponent<Transform>()->GetPosition();
				*/
			}
			//�Q�̖�
			dis = pos2 - mypos;
			if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
			{
				ToAttack(2);
			}
			//���G--------------------------------

		}
		else
		{
			ToSearch();
		}
	}

	void TackleEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//���ԉ��Z
			m_time += App::GetApp()->GetElapsedTime();
			/*1A
			//�U������܂łԂ�Ԃ�c�莞�Ԃɉ����đ�����ς���
			//if (m_time < m_AttackTime)
			//{
			//	Vector3 pos = m_BurePos;
			//	//���薢��
			//	if (m_time / m_AttackTime < 0.3f)
			//	{
			//		//-0.2�`0.2�̊ԂłԂ�Ԃ�
			//		pos += Vector3(rand() % 40 - 20, 0, rand() % 40 - 20) / 100;
			//	}
			//}
			*/

			//�U���܂ł̃`���[�W���I��
			if (m_time > m_AttackTime)
			{
				//�A�j���[�V�����ύX
				ChangeAnimation("AttackNow");

				m_time = 0;
				m_TackleFlg = true;
				//�U�������񐔉��Z
				m_AttackCount++;
				//���x�v�Z
				//�P�̖ڂɓˌ�
				if (m_TargetNum == 1)
				{
					Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//�p�x�Z�o
					float angle = atan2(dis.z, dis.x);
					//���x�����
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
				//�Q�̖ڂɓˌ�
				else if (m_TargetNum == 2)
				{
					Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//�p�x�Z�o
					float angle = atan2(dis.z, dis.x);
					//���x�����
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
			}
		}
		//m_TackleFlg��true�A�ȉ��ˌ����̓���
		else
		{
			//���ԉ��Z
			m_time += App::GetApp()->GetElapsedTime();

			//�U�����ԉ߂���܂ňړ�
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity * App::GetApp()->GetElapsedTime();
				GetComponent<Transform>()->SetPosition(pos);
			}
			//�ˌ����ԏI�������
			else
			{
				m_time = 0;
				//�U���t���O����
				m_TackleFlg = false;

				//�U�������񐔂��ݒ肳�ꂽ�U���񐔂̏���𖞂�������
				if (m_AttackCount >= m_TackleCount)
				{
					ToCoolTime();
				}
			}
		}
	}

	void TackleEnemy::CoolTime()
	{
		//�N�[���^�C���߂�������G��Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TackleEnemy::Muteki()
	{
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_MutekiTime)
		{
			Vector3 sca = Vector3(m_ParScale, m_ParScale, m_ParScale);
			GetComponent<Transform>()->SetScale(sca);

			m_MutekiFlg = false;
			ToSearch();
		}
		else
		{
			m_MutekiTenmetuTime += App::GetApp()->GetElapsedTime();
			if (m_MutekiTenmetuTime > 0.05f)
			{
				m_MutekiTenmetuTime = 0;
				Vector3 sca = GetComponent<Transform>()->GetScale();
				if (sca.x < m_ParScale)
				{
					sca = Vector3(m_ParScale, m_ParScale, m_ParScale);
				}
				else
				{
					sca = Vector3(m_ParScale / 2, m_ParScale / 2, m_ParScale / 2);
				}
				//�傫���ύX
				GetComponent<Transform>()->SetScale(sca);
			}
		}
	}

	void TackleEnemy::CircleMove()
	{

		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//�����ֈړ�
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
	}

	//�Ȃ񂩂ɂԂ������瑬�x���]�A���Əc�ǂ��������������������ق���
	void TackleEnemy::TurnVecolity(bool flgx, bool flgz)
	{
		if (flgx)
		{
			m_Velocity.x *= -1;
		}
		if (flgz)
		{
			m_Velocity.z *= -1;
		}
	}

	//���ꂼ��̏�Ԃֈڍs����֐�------------------------------------------
	void TackleEnemy::ToSearch()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//��ԕύX
		m_State = SearchS;

		//�T�[�N���ړ�
		CircleMove();

		//�A�j���[�V�����ύX
		ChangeAnimation("Wait");
	}

	void TackleEnemy::ToMove()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//�ړ��x�N�g��(?)�v�Z
		//0.5�`-0.5�܂Ń����_���ŏo���ăX�s�[�h������
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 100;
		m_Velocity *= m_Speed;

		//��ԕύX
		m_State = MoveS;

		//�A�j���[�V�����ύX
		ChangeAnimation("Walk");

	}

	void TackleEnemy::ToAttack(int num)
	{
		//�v�Z���ԏ�����
		m_time = 0;
		//�U������Ώۂ�ݒ�
		m_TargetNum = num;

		//��ԕύX
		m_State = AttackS;

		//�A�j���[�V�����ύX
		ChangeAnimation("AttackWait");

	}

	void TackleEnemy::ToCoolTime()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//�U���t���O����
		m_TackleFlg = false;
		//�U���񐔃��Z�b�g
		m_AttackCount = 0;

		//��ԕύX
		m_State = CoolTimeS;

		//�A�j���[�V�����ύX
		ChangeAnimation("Wait");

	}

	void TackleEnemy::ToMuteki()
	{
		//��ԕύX
		m_State = MutekiS;

		//�t���O�I��
		m_MutekiFlg = true;

		//�U���t���O����
		m_TackleFlg = false;
		//�U���񐔃��Z�b�g
		m_AttackCount = 0;

		//���ԏ�����
		m_time = 0;

		//�A�j���[�V�����ύX
		ChangeAnimation("Damage");

	}

	//�v���C���[�ւ̍U������
	void TackleEnemy::ToDamagePlayer()
	{
		//�U�����Ȃ�
		if (m_TackleFlg)
		{
			//HP�����炷
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(m_Power);
			PtrPlayerHP->SetHit(true);
			ToCoolTime();
		}
	}

	//�U���󂯂��Ƃ�
	void TackleEnemy::DamagePlayer()
	{
		if (m_ActiveFlg)
		{
			if (!m_MutekiFlg)
			{
				//����HP��1�ȉ��Ȃ�
				if (m_Hp <= 1)
				{
					//�^�q��
					SetDrawActive(false);
					m_Hp = 0;
					m_ActiveFlg = false;
					//Abe20170605
					//���G�T�[�N������
					m_SearchCircle->SetDrawActive(false);
					//�j�А���
					GetStage()->GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(rand() % 25 + 5, GetComponent<Transform>()->GetPosition());
					//Abe20170605
				}
				else
				{
					m_Hp--;
					ToMuteki();
				}
			}
		}
	}

	void TackleEnemy::Damage(int num)
	{
		if (!m_MutekiFlg)
		{
			//HP���炵�ĂȂ��Ȃ��Ă��1�c��
			m_Hp += -num;
			if (m_Hp < 0)
			{
				m_Hp = 1;
			}

			ToMuteki();
		}
	}

	//************************************************************************
	//	�ʌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************************************************

	ShotEnemy::ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int power, float shotchildinterval, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Power(power),
		m_ShotChildInterval(shotchildinterval),
		m_ShotAmount(shotamount)
	{}

	void ShotEnemy::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"MISSILE_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//Abe20170526
		//�A�j���[�V�����ǉ�
		Draw->AddAnimation(L"Wait", 0, 30, true, 30);
		Draw->AddAnimation(L"Attack", 30, 50, false, 30);
		Draw->AddAnimation(L"Damage", 80, 30, false, 30);
		Draw->AddAnimation(L"ChildSpawn", 120, 30, false, 30);
		//Abe20170526

		Draw->ChangeCurrentAnimation(L"Wait");
		//��������
		SetAlphaActive(true);	
		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		////���G�͈͍쐬
		//auto circle = GetStage()->AddGameObject<GameObject>();
		//auto TransCi = circle->AddComponent<Transform>();
		//Vector3 posci = m_InitPos;
		////�����ֈړ�
		//posci.y = 1;
		//TransCi->SetPosition(posci);
		//TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		//TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		//auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		//DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		//DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		//circle->SetAlphaActive(true);
		////���C���[�ݒ�
		//circle->SetDrawLayer(2);

		//m_SearchCircle = circle;

		//Abe20170523
		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<SearchCircle>();
		auto TransCi = circle->GetComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		m_SearchCircle = circle;
		//Abe20170523

	}

	void ShotEnemy::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			switch (m_State)
			{
				//���G
			case SearchS:
				Search();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				break;
				//�U��
			case AttackS:
				Attack();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
				//���G
			case MutekiS:
				Muteki();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
			}

			//�A�j���[�V�����X�V
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);

		}
	}

	//Abe20170526
	//�A�j���[�V�����ύX
	void ShotEnemy::ChangeAnimation(string txt)
	{
		
		if (txt == "Wait")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
		}
		if (txt == "Attack")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Attack");
		}
		if (txt == "Damage")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Damage");
		}
		if (txt == "ChildSpawn")
		{
			GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"ChildSpawn");
		}
		
		/*
		Draw->AddAnimation(L"Wait", 0, 30, true, 30);
		Draw->AddAnimation(L"AttackWait", 40, 10, false, 30);
		Draw->AddAnimation(L"AttackNow", 50, 20, true, 30);
		Draw->AddAnimation(L"Damage", 80, 30, false, 30);
		Draw->AddAnimation(L"ChildSpawnOpen", 120, 10, false, 30);
		Draw->AddAnimation(L"ChildSpawnClose", 130, 20, false, 30);
		*/
	}
	//Abe20170526



	//��ԌQ----------------------------------------------------------
	void ShotEnemy::Search()
	{
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�A�ǂ��������������ԕω�
		Vector3 dis = pos1 - mypos;
		Vector3 dis2 = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance || ((dis2.x*dis.x) + (dis2.z*dis.z) < distance*distance))
		{
			ToAttack();
		}

		//��莞�Ԃ��Ƃɒ�~����悤��
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 0.8f)
		{
			//��]
			Vector3 rot = Vector3(0, GetComponent<Transform>()->GetRotation().y, 0);
			rot.y += m_rotSpeed * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
			GetComponent<Transform>()->SetRotation(rot);
		}
		else if (m_time > 2.0f)
		{
			m_time = 0;
		}
	}

	void ShotEnemy::Attack()
	{
		float angle = 0;
		//�_�����v���C���[�Ɍ���
		if (m_TargetPlayer == 1)
		{
			Vector3 dif = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			angle = atan2(dif.z, dif.x);
			angle *= -1;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
			//���ۂ̉�]�͋t�Ȃ�ŋt�ɂ���
			angle *= -1;
		}
		else
		{
			Vector3 dif = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			angle = atan2(dif.z, dif.x);
			angle *= -1;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
			angle *= -1;
		}

		//�~�T�C���ł���
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{

			//�A�j���[�V�����ύX
			ChangeAnimation("Attack");

			//�A���O���ϊ�
			angle *= 180 / 3.14159265f;
			angle += 360;
			angle = (int)angle % 360;

			//�v�Z�p���ԏ�����
			m_time = 0;

			bool sflg = false;
			//�N�����ĂȂ��̂���΍ė��p
			//��������
			for (int i = 0; i < m_ShotAmount; i++)
			{
				for (auto obj : m_MissileS)
				{
					if (!obj->GetDrawActive())
					{
						int Tangle = (int)angle % 360;
						//�Ƃ肠����10�`20�A-10�`-20�x�͈̔͂Ŕ�΂�
						if (rand() % 2 == 0)
						{
							Tangle += rand() % 11 + 10;
						}
						else
						{
							Tangle += rand() % 11 - 20;
						}
						
						float angle2 = Tangle * 3.14159265f / 180;

						//��΂����������߂� y��2�`6
						Vector3 tovelo = Vector3(cos(angle2) * m_ShotPower, rand() % 5 + 2, sin(angle2) * m_ShotPower);
						////���̏ォ�甭��
						//Vector3 topos = GetComponent<Transform>()->GetPosition();
						//topos.y += GetComponent<Transform>()->GetScale().y / 2;
						//dynamic_pointer_cast<Missile>(obj)->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);

						//Abe20170526
						//�̂̉����甭��
						Vector3 topos = GetComponent<Transform>()->GetPosition();
						float toanglem = angle;
						//���[�v�������̎�
						if (i % 2 == 0)
						{
							toanglem += 90;
						}
						else
						{
							toanglem += -90;
						}
						toanglem *= 3.14159265f / 180;
						float ShEnHalf = GetComponent<Transform>()->GetScale().x / 2;
						topos += Vector3(cos(toanglem)*ShEnHalf, ShEnHalf, sin(toanglem)*ShEnHalf);
						dynamic_pointer_cast<Missile>(obj)->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);

						//Abe20170526
						//�������t���O�I��
						sflg = true;

						//�_���v���C���[�����߂�
						m_TargetPlayer = rand() % 2 + 1;

						break;
					}
				}
				if (!sflg)
				{
					//�쐬
					auto objm = GetStage()->AddGameObject<Missile>();
					GetStage()->GetSharedObjectGroup(L"CollisionGroup")->IntoGroup(objm);

					int Tangle = (int)angle % 360;
					//�Ƃ肠����10�`20�A-10�`-20�x�͈̔͂Ŕ�΂�
					if (rand() % 2 == 0)
					{
						Tangle += rand() % 11 + 10;
					}
					else
					{
						Tangle += rand() % 11 - 20;
					}

					float angle2 = Tangle * 3.14159265f / 180;


					//��΂����������߂� y��2�`6
					Vector3 tovelo = Vector3(cos(angle2) * m_ShotPower, rand() % 5 + 2, sin(angle2) * m_ShotPower);
					//���̏ォ�甭��
					//Vector3 topos = GetComponent<Transform>()->GetPosition();
					//topos.y += GetComponent<Transform>()->GetScale().y / 2;
					//objm->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);

					//Abe20170526
					//�̂̉����甭��
					Vector3 topos = GetComponent<Transform>()->GetPosition();
					float toanglem = angle;
					//���[�v�������̎�
					if (i % 2 == 0)
					{
						toanglem += 90;
					}
					else
					{
						toanglem += -90;
					}
					toanglem *= 3.14159265f / 180;
					float ShEnHalf = GetComponent<Transform>()->GetScale().x / 2;
					topos += Vector3(cos(toanglem)*ShEnHalf, ShEnHalf, sin(toanglem)*ShEnHalf);
					objm->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);
					m_MissileS.push_back(objm);
					//Abe20170526

				}
			}
		}

		//�q�@��ł��o���Ԋu�ɂȂ�����
		m_Childtime += App::GetApp()->GetElapsedTime();
		if(m_Childtime > m_ShotChildInterval)
		{ 
			//�A�j���[�V�����ύX
			//ChangeAnimation("ChildSpawn");

			//�v�Z�p���ԏ�����
			m_Childtime = 0;
			//�q�@�͂����t���O�I��
			m_ShotChild = true;
			//�N�����ĂȂ��̂���΍ė��p
			bool flgg = false;

			int count = 0;
			for (auto obj : m_ChildS)
			{
				auto ptr = dynamic_pointer_cast<ShotEnemyChild>(obj);
				if (ptr->GetDrawActive())
				{
					count++;
				}
			}
			if (count < 2)
			{
				for (auto obj : m_ChildS)
				{
					auto ptr = dynamic_pointer_cast<ShotEnemyChild>(obj);
					//����ł���ė��p
					if (ptr)
					{
						if (!ptr->GetDrawActive())
						{
							Vector3 PPOS = GetComponent<Transform>()->GetPosition();
							PPOS.y += GetComponent<Transform>()->GetScale().y;
							int Tangle = (int)angle % 360;
							//�Ƃ肠����10�`20�A-10�`-20�x�͈̔͂Ŕ�΂�
							if (rand() % 2 == 0)
							{
								Tangle += rand() % 11 + 10;
							}
							else
							{
								Tangle += rand() % 11 - 20;
							}

							float angle2 = Tangle * 3.14159265f / 180;
							ptr->SetVelocity(Vector3(cos(angle2) * (float)(rand() % 3 + 1) * m_ParScale / 2, rand() % 5 + 5, sin(angle2) * (float)(rand() % 3 + 1))* m_ParScale / 2);

							flgg = true;
							break;
						}
					}
				}
				//���Ȃ���������
				if (!flgg)
				{
					Vector3 PPOS = GetComponent<Transform>()->GetPosition();
					PPOS.y += GetComponent<Transform>()->GetScale().y;
					auto pptr = GetStage()->AddGameObject<ShotEnemyChild>(PPOS, Vector3(1, 1, 1), 2);
					int Tangle = (int)angle % 360;
					//�Ƃ肠����10�`20�A-10�`-20�x�͈̔͂Ŕ�΂�
					if (rand() % 2 == 0)
					{
						Tangle += rand() % 11 + 10;
					}
					else
					{
						Tangle += rand() % 11 - 20;
					}

					float angle2 = Tangle * 3.14159265f / 180;
					pptr->SetVelocity(Vector3(cos(angle2) * (float)(rand() % 3 + 1) * m_ParScale / 2, rand() % 5 + 5, sin(angle2) * (float)(rand() % 3 + 1))* m_ParScale / 2);
					m_ChildS.push_back(pptr);

					//�O���[�v�ɓ����
					GetStage()->GetSharedObjectGroup(L"CollisionGroup")->IntoGroup(pptr);
					GetStage()->GetSharedObjectGroup(L"EnemyGroup")->IntoGroup(pptr);

				}
			}
		}

		//����������x���ꂽ��
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�A���G�͈͂�1.3�{�ȏ㗣�ꂽ�炩�q�@��f���o���Ă�����G��Ԃ�
		Vector3 dis = pos1 - mypos;
		Vector3 dis2 = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) > distance*distance * 1.3f && ((dis2.x*dis.x) + (dis2.z*dis.z) > distance*distance * 1.3f) && m_ShotChild)
		{
			ToSearch();
		}

	}

	void ShotEnemy::Muteki()
	{
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_MutekiTime)
		{
			Vector3 sca = Vector3(m_ParScale, m_ParScale, m_ParScale);
			GetComponent<Transform>()->SetScale(sca);

			m_MutekiFlg = false;
			ToSearch();
		}
		else
		{
			m_MutekiTenmetuTime += App::GetApp()->GetElapsedTime();
			if (m_MutekiTenmetuTime > 0.05f)
			{
				m_MutekiTenmetuTime = 0;
				Vector3 sca = GetComponent<Transform>()->GetScale();
				if (sca.x < m_ParScale)
				{
					sca = Vector3(m_ParScale, m_ParScale, m_ParScale);
				}
				else
				{
					sca = Vector3(m_ParScale / 2, m_ParScale / 2, m_ParScale / 2);
				}
				//�傫���ύX
				GetComponent<Transform>()->SetScale(sca);
			}
		}
	}

	//��ԕύX�Q----------------------------------------------------------
	void ShotEnemy::ToSearch()
	{
		//���ԏ�����
		m_time = 0;

		//��ԕύX
		m_State = SearchS;

		//�f���o�����t���O����
		m_ShotChild = false;

		//�A�j���[�V�����ύX
		ChangeAnimation("Wait");
	}

	void ShotEnemy::ToAttack()
	{
		//���ԏ�����
		m_time = 0;
		
		//��ԕύX
		m_State = AttackS;

		//�_���v���C���[�����߂�
		m_TargetPlayer = rand() % 2+1;

		//�A�j���[�V�����ύX
		ChangeAnimation("Wait");
	}

	//Abe20170526
	void ShotEnemy::ToMuteki()
	{
		//��ԕύX
		m_State = MutekiS;

		//�t���O�I��
		m_MutekiFlg = true;

		//���ԏ�����
		m_time = 0;

		//�A�j���[�V�����ύX
		ChangeAnimation("Damage");

	}

	//Abe20170526
	//Abe20170517
	void ShotEnemy::DamagePlayer()
	{
		if (m_ActiveFlg)
		{ 
			if (!m_MutekiFlg)
			{
				//����HP��1�ȉ��Ȃ�
				if (m_Hp <= 1)
				{
					//�^�q��
					SetDrawActive(false);
					m_Hp = 0;
					m_ActiveFlg = false;

					//Abe20170605
					//���G�T�[�N������
					m_SearchCircle->SetDrawActive(false);
					//�j�А���
					GetStage()->GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(rand() % 25 + 5, GetComponent<Transform>()->GetPosition());
					//Abe20170605

				}
				else
				{
					m_Hp--;
					ToMuteki();

				}
			}
		}
	}

	void ShotEnemy::Damage(int num)
	{
		if (!m_MutekiFlg)
		{
			//HP���炵�ĂȂ��Ȃ��Ă��1�c��
			m_Hp += -num;
			if (m_Hp < 0)
			{
				m_Hp = 1;
			}

			ToMuteki();
		}
	}
	//Abe20170517



	//Abe20170508
	//************************************************************************
	//	���e�u���ăe���|�[�g�G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************************************************

	TeleportEnemy::TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_ShotAmount(shotamount)
	{}

	void TeleportEnemy::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, -90 * 3.14159265f / 180, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"TELEPORT_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//��������
		SetAlphaActive(true);

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		//auto circle = GetStage()->AddGameObject<GameObject>();
		//auto TransCi = circle->AddComponent<Transform>();
		//Vector3 posci = m_InitPos;
		////�����ֈړ�
		//posci.y = 1;
		//TransCi->SetPosition(posci);
		//TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		//TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		//auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		//DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		//DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		//circle->SetAlphaActive(true);
		////���C���[�ݒ�
		//circle->SetDrawLayer(2);

		//m_SearchCircle = circle;

		//Abe20170523
		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<SearchCircle>();
		auto TransCi = circle->GetComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		m_SearchCircle = circle;
		//Abe20170523

		//�X�e�[�g������
		ToSearch();

		//�e���|�[�g�|�C���g���쐬
		auto TereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto TereportPtr = GetStage()->AddGameObject<TereportPoint>(posci);
		TereportPtr->SetOnEnemy(true);
		TereportGroup->IntoGroup(TereportPtr);

		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F�ԂɕύX
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);

		//������F��������ԍ�������
		auto Group = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		int count = 0;
		for (auto obj : Group)
		{
			if (dynamic_pointer_cast<TeleportEnemy>(obj.lock()))
			{
				count++;
			}
		}
		//���ʔԍ������
		m_number = count;

	}

	void TeleportEnemy::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			switch (m_State)
			{
				//���G
			case SearchS:
				Search();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				break;
				//�U��
			case AttackS:
				Attack();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
				//�N�[���^�C��
			case CoolTimeS:
				CoolTime();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
			}
		}
	}

	void TeleportEnemy::GoDrawns()
	{
		if (m_Drawns.size() == 0)
		{
			//�h���[���쐬
			for (int i = 0; i < m_ShotAmount; i++)
			{
				auto Drawn = GetStage()->AddGameObject<SearchDrawn>();
				m_Drawns.push_back(Drawn);

				GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->IntoGroup(Drawn);
			}
		}

		float angle = 360/m_ShotAmount;
		float TarAngle = 0;
		for (auto obj : m_Drawns)
		{
			auto ptr = dynamic_pointer_cast<SearchDrawn>(obj);
			Vector3 inVel = Vector3(cos(TarAngle*3.14159265f / 180), 0, sin(TarAngle*3.14159265f / 180));
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos.y += 1;
			ptr->GoDrawn(pos, inVel,m_number);
			TarAngle += angle;
		}
	}

	void TeleportEnemy::Search()
	{
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�
		//�P�̖�
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		}
		//�Q�̖�
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

	}

	void TeleportEnemy::Attack()
	{
		m_time += App::GetApp()->GetElapsedTime();
		//���e�u����ԂɂȂ�܂őҋ@
		if (!m_BombPutFlg)
		{
			//�U���܂ł̎��ԉ߂�����e���|�[�g
			if (m_time > m_AttackWaitTime)
			{
				//�P�̖ڍU��
				if (m_TargetNum == 1)
				{
					Vector3 pos = m_Player1->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 50 - 25) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 50 - 25) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}
				//�Q�̖ڍU��
				else if (m_TargetNum == 2)
				{
					Vector3 pos = m_Player2->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 50 - 25) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 50 - 25) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}

				//���e�u���t���O���Ă�
				m_BombPutFlg = true;

				//���ԃ��Z�b�g
				m_time = 0;
			}
		}
		//���e�u��
		else
		{
			//���e�u���O
			if (!m_BombAfterFlg)
			{
				if (m_time > m_BombPutTime)
				{
					//���e�𐶐�
					auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
					//�u�������ǂ���
					bool PutFlg = false;
					//Abe20170512
					int count = 0;
					//Abe20170512
					for (auto obj : BombGroup)
					{
						//Abe20170512
						count++;
						//Abe20170512

						auto ptr = dynamic_pointer_cast<Bomb>(obj.lock());
						if (!ptr->GetDrawActive())
						{
							Vector3 topos = GetComponent<Transform>()->GetPosition();
							topos.y = 1;
							ptr->SetActivePosition(topos);
							PutFlg = true;
							break;
						}
					}
					//�g�������Ȃ���������
					if (!PutFlg)
					{
						GetStage()->GetSharedObjectGroup(L"BombGroup")->IntoGroup(GetStage()->AddGameObject<Bomb>(GetComponent<Transform>()->GetPosition()));
					}

					//Abe20170512
					//m_Debugtxt->SetText(Util::IntToWStr(count));
					//Abe20170512

					//���e�u�����t���O���I��
					m_BombAfterFlg = true;

					//���ԃ��Z�b�g
					m_time = 0;
				}
			}
			//���e�u������
			else
			{
				auto Group = GetStage()->GetSharedObjectGroup(L"TereportPointGroup")->GetGroupVector();
				//���g�̐��𐔂���
				int count = 0;
				//������Ɖ������ǂ܂�������
				vector<shared_ptr<GameObject>> Target;
				for (auto obj : Group)
				{
					auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
					//�����̑����̃e���|�[�g�|�C��t����Ȃ�������ǉ�
					if (ptr != m_UnderTereportPoint)
					{
						Target.push_back(ptr);
						count++;
					}
					//�����̂Ȃ玩�����Ȃ����Ƃɂ���
					else
					{
						dynamic_pointer_cast<TereportPoint>(ptr)->SetOnEnemy(false);
					}
				}
				//�ړ��������
				int randnum = rand() % count;
				//�ړ�
				Vector3 targetpos = Target[randnum]->GetComponent<Transform>()->GetPosition();
				targetpos.y = m_InitPos.y;
				GetComponent<Transform>()->SetPosition(targetpos);
				//�����̃|�C���g�ݒ�
				m_UnderTereportPoint = Target[randnum];
				dynamic_pointer_cast<TereportPoint>(m_UnderTereportPoint)->SetOnEnemy(true);

				//�N�[���^�C����
				ToCoolTime();
			}
		}

	}

	void TeleportEnemy::CoolTime()
	{
		//�N�[���^�C���߂�������G��Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TeleportEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//�����ֈړ�
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
	}

	void TeleportEnemy::ToSearch()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//��ԕύX
		m_State = SearchS;

		//�T�[�N���ړ�
		CircleMove();

		//�q�@���o
		GoDrawns();

	}

	void TeleportEnemy::ToAttack(int num)
	{
		m_time = 0;

		m_TargetNum = num;

		m_State = AttackS;

		//�q�@���[
		for (auto obj : m_Drawns)
		{
			dynamic_pointer_cast<SearchDrawn>(obj)->UpDrawns();

		}
	}


	void TeleportEnemy::ToCoolTime()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//���e�u����ԏ�����
		m_BombPutFlg = false;
		//���e�u������ԏ�����
		m_BombAfterFlg = false;

		//��ԕύX
		m_State = CoolTimeS;

	}
	//Abe20170508

	//Abe20170512
	//�U���󂯂��Ƃ�
	void TeleportEnemy::DamagePlayer()
	{
		if (GetDrawActive())
		{
			//����HP��1�ȉ��Ȃ�
			if (m_Hp <= 1)
			{
				//�^�q��
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;

				//Abe20170605
				//���G�T�[�N������
				m_SearchCircle->SetDrawActive(false);
				//�j�А���
				GetStage()->GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(rand() % 25 + 5, GetComponent<Transform>()->GetPosition());
				//Abe20170605

				//�q�@���[
				for (auto obj : m_Drawns)
				{
					dynamic_pointer_cast<SearchDrawn>(obj)->UpDrawns();

				}

			}
			else
			{
				m_Hp--;
			}
		}
	}

	void TeleportEnemy::Damage(int num)
	{
		//HP���炵�ĂȂ��Ȃ��Ă��1�c��
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
		}
	}
	//Abe20170512

	//************************************************************************
	//	�����G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************************************************
	BombEnemy::BombEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float speed, int power) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_Speed(speed),
		m_Power(power)
	{}

	void BombEnemy::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"BOMBENEMY_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//��������
		SetAlphaActive(true);

		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		//auto circle = GetStage()->AddGameObject<GameObject>();
		//auto TransCi = circle->AddComponent<Transform>();
		//Vector3 posci = m_InitPos;
		////�����ֈړ�
		//posci.y = 1;
		//TransCi->SetPosition(posci);
		//TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		//TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		//auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		//DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		//DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		//circle->SetAlphaActive(true);
		////���C���[�ݒ�
		//circle->SetDrawLayer(2);

		//m_SearchCircle = circle;

		//Abe20170523
		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<SearchCircle>();
		auto TransCi = circle->GetComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		m_SearchCircle = circle;
		//Abe20170523

		//�X�e�[�W�̑傫���擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;


	}

	void BombEnemy::OnUpdate()
	{
		//�����Ă��
		if (m_ActiveFlg)
		{
			//m_Debugtxt->SetText(Util::IntToWStr(m_State));

			switch (m_State)
			{
				//���G
			case SearchS:
				Search();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				CircleMove();
				break;
				//�T��
			case MoveS:
				Move();
				StageEndCheck();
				if (!m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(true);
				}
				CircleMove();
				break;
				//�U��
			case AttackS:
				Attack();
				Rot();
				StageEndCheck();
				if (m_SearchCircle->GetDrawActive())
				{
					m_SearchCircle->SetDrawActive(false);
				}
				break;
			}

			//Abe20170519
			//��]
			Rot();
			//Abe20170519

		}


	}

	//Abe20170519
	void BombEnemy::Rot()
	{
		//�����Ă鑬�x����p�x�Z�o
		Vector3 vel = m_Velocity;
		//�}�C�i�X���](abs�͏d���̂Ŏg���܂���)
		if (vel.x < 0)
		{
			vel.x *= -1;
		}
		if (vel.z < 0)
		{
			vel.z *= -1;
		}
		//x��z�������l��0.2��肠���
		if (vel.x + vel.z > 0.2f)
		{
			float angle = atan2(m_Velocity.z, m_Velocity.x);
			angle *= -1;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}
	}
	//Abe20170519

	void BombEnemy::StageEndCheck()
	{
		//�ʒu[�E]�A[��]�A[��]�A[��]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x + scale.x, pos.z + scale.z, pos.x - scale.x, pos.z - scale.z);
		//�X�e�[�W�̒[�ɓ������Ă邩����
		//�E
		if (m_StageSize.x < PositionPXYMXY.x)
		{
			pos.x = m_StageSize.x - scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (m_StageSize.y < PositionPXYMXY.y)
		{
			pos.z = m_StageSize.y - scale.z;
			m_Velocity.z *= -1;
		}
		//��
		if (-m_StageSize.x > PositionPXYMXY.z)
		{
			pos.x = -m_StageSize.x + scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (-m_StageSize.y > PositionPXYMXY.w)
		{
			pos.z = -m_StageSize.y + scale.z;
			m_Velocity.z *= -1;
		}

	}

	//�Ȃ񂩂ɂԂ������瑬�x���]�A���Əc�ǂ��������������������ق���
	void BombEnemy::TurnVecolity(bool flgx, bool flgz)
	{
		if (flgx)
		{
			m_Velocity.x *= -1;
		}
		if (flgz)
		{
			m_Velocity.z *= -1;
		}
	}

	void BombEnemy::Search()
	{
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�
		//�P�̖�
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		
		}
		//�Q�̖�
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//��莞�ԂŒT����Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}

	}

	void BombEnemy::Move()
	{
		//�����_����2�b���炢�i��
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 2)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			//�Ȃ񂩃I�u�W�F�N�g�ɓ�����������Velocity�𔽓]���邯�ǂ���͕ʂ̂Ƃ��ł���
			GetComponent<Transform>()->SetPosition(pos);

			//�ʒu���擾
			Vector3 mypos = GetComponent<Transform>()->GetPosition();
			Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
			float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

			//���G------------------------------
			//�����𑪂�
			//�P�̖�
			Vector3 dis = pos1 - mypos;
			if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
			{
				ToAttack(1);

			}
			//�Q�̖�
			dis = pos2 - mypos;
			if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
			{
				ToAttack(2);
			}
			//���G------------------------------

		}
		else
		{
			ToSearch();
		}
	}

	void BombEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//���ԉ��Z
			m_time += App::GetApp()->GetElapsedTime();
			
			//�U���܂ł̃`���[�W���I��
			if (m_time > m_AttackTime)
			{
				m_time = 0;
				m_TackleFlg = true;	
			}
		}
	
		
		//m_TackleFlg��true�A�ȉ��ˌ����̓���
		else
		{
			//���x�v�Z
			//�P�̖ڂɓˌ�
			if (m_TargetNum == 1)
			{
				Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

				//�p�x�Z�o
				float angle = atan2(dis.z, dis.x);
				//���x�����
				m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
			}
			//�Q�̖ڂɓˌ�
			else
			{
				Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

				//�p�x�Z�o
				float angle = atan2(dis.z, dis.x);
				//���x�����
				m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
			}
			
			//���ԉ��Z
			m_time += App::GetApp()->GetElapsedTime();

			//�U�����ԉ߂���܂ňړ�
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity/10;
				GetComponent<Transform>()->SetPosition(pos);
			}
			//�ˌ����ԏI�������
			else 
			{
				m_time = 0;
				//�U���t���O����
				//m_TackleFlg = false;

				//�ˌ���A�����̈׏���
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;
			}
		}
	}


	void BombEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//�����ֈړ�
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
	}




	//���ꂼ��̏�Ԃֈڍs����֐�------------------------------------------
	void BombEnemy::ToSearch()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//��ԕύX
		m_State = SearchS;

		//�T�[�N���ړ�
		CircleMove();

	}

	void BombEnemy::ToMove()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//�ړ��x�N�g��(?)�v�Z
		//0.5�`-0.5�܂Ń����_���ŏo���ăX�s�[�h������
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 20; //100
		m_Velocity *= m_Speed;

		//��ԕύX
		m_State = MoveS;

	}

	void BombEnemy::ToAttack(int num)
	{
		//�v�Z���ԏ�����
		m_time = 0;
		//�U������Ώۂ�ݒ�
		m_TargetNum = num;

		//��ԕύX
		m_State = AttackS;
	}


	//�v���C���[�ւ̍U������
	void BombEnemy::ToDamagePlayer()
	{
			//�U�����Ȃ�
			if (m_TackleFlg)
			{
				//HP�����炷
				auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
				PtrPlayerHP->SetDamage_int(m_Power);
				PtrPlayerHP->SetHit(true);

				//�����̈׏���
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;

				//Abe20170605
				//���G�T�[�N������
				m_SearchCircle->SetDrawActive(false);
				//Abe20170605

			}
		
	}
	void BombEnemy::DamagePlayer()
	{
		if (GetDrawActive())
		{
			//�^�q��
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;
			//�j�А���
			//GetStage()->GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(rand() % 20, GetComponent<Transform>()->GetPosition());
			//Abe20170605
			//���G�T�[�N������
			m_SearchCircle->SetDrawActive(false);
			//Abe20170605
		}
	}

	//Abe20170508
	//======================�ȉ��q�@�Q=======================
	//************************************************************************
	//	���e�̔����̕���
	//	�����͂���܁[��
	//************************************************************************
	BombEffect::BombEffect(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void BombEffect::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(3, 3, 3);
		Trans->SetRotation(45*3.14159265f/180, 0, 0);

		auto Draw = AddComponent<PCTStaticDraw>();
		//Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(L"BOMBEFFECT_TX");
		
		//��������
		SetAlphaActive(true);
		SetDrawActive(false);

		//�摜����

		//�X�v���C�g�̐����Z�b�g
		m_SpriteNum = -1;
		//6x5
		//�摜�쐬-------------------------
		for (int i = 0; i < 30; i++)
		{
			m_SpriteNum++;
			//���_�z��
			vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV�l�̕ύX
			float fromX = (i % 6) / 6.0f;
			float toX = fromX + (1.0f / 6.0f);
			float fromY = (i / 6) / 5.0f;
			float toY = fromY + (1.0f / 5.0f);
			//���㒸�_
			vertices[0].textureCoordinate = Vector2(fromX, fromY);
			//�E�㒸�_
			vertices[1].textureCoordinate = Vector2(toX, fromY);
			//�������_
			vertices[2].textureCoordinate = Vector2(fromX, toY);
			//�E�����_
			vertices[3].textureCoordinate = Vector2(toX, toY);
			//���_�̌^��ς����V�������_���쐬
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//���b�V���쐬
			m_SpriteS.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//�摜�쐬-------------------------
		Draw->SetMeshResource(m_SpriteS[0]);
	}

	void BombEffect::OnUpdate()
	{
		if (m_ActiveFlg)
		{

			//�摜�J��
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_IntervalTime)
			{
				m_time = 0;
				GetComponent<PCTStaticDraw>()->SetMeshResource(m_SpriteS[m_NowSpriteNum++]);

				//������������葽��������
				if (m_NowSpriteNum > m_SpriteNum)
				{
					m_NowSpriteNum = 0;
					m_ActiveFlg = false;
				}
			}
			/*
			switch (m_State)
			{
			case 0:
				//�ł������Ȃ���
				if (true)
				{
					Vector3 Scale = GetComponent<Transform>()->GetScale();
					if (Scale.x < 5.0f)
					{
						Scale *= 1.5f;
						GetComponent<Transform>()->SetScale(Scale);
					}
					else
					{
						m_State = 1;
					}
				}
				break;
				//�������Ⴍ�Ȃ�
			case 1:
				if (true)
				{
					Vector3 Scale = GetComponent<Transform>()->GetScale();
					if (Scale.x > 0.2f)
					{
						Scale *= 0.8f;
						GetComponent<Transform>()->SetScale(Scale);
					}
					else
					{
						m_State = 2;
					}
				}
				break;
				//�I������
			case 2:
				//�N���I��
				m_ActiveFlg = false;
				//��ԏ�����
				m_State = 0;
				SetDrawActive(false);
				break;
			}*/
		}
	}

	void BombEffect::SetPosActive(Vector3 pos)
	{
		m_ActiveFlg = true;
		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}

	//************************************************************************
	//	���e
	//	��莞�ԂŋN��
	//************************************************************************
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos, float scale, float bombdistance, float power, float explosiontime) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(Vector3(scale, scale, scale)),
		m_BombDistance(bombdistance),
		m_Power(power),
		m_ExplosionTime(explosiontime)
	{}

	//�����|�W�V�����̂݁B�Ă�������{�������g���Ăق���
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_InitPos(pos)
	{
		//���̑�����
		m_Scale = Vector3(1, 1, 1);
		m_BombDistance = 6.0f;
		m_Power = 3.0f;
		m_ExplosionTime = 3.0f;
	}

	void Bomb::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"BOMB_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);
		//��������
		SetAlphaActive(true);

		m_time = 0;

		m_Effect = GetStage()->AddGameObject<BombEffect>();
	}

	void Bomb::OnUpdate()
	{
		if (m_Activeflg)
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_ExplosionTime)
			{
				BombExplosion();
			}
		}
	}

	//���܂ꂽ�甚��
	void Bomb::BombExplosion()
	{
		//�����Ȃ�
		m_Activeflg = false;
		SetDrawActive(false);
		//�����쐬
		m_Effect->SetPosActive(GetComponent<Transform>()->GetPosition());


		//����
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		auto Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		auto Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//�v���C���[�̍��W�������Ă���
		Vector3 ppos1 = Player1->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = Player2->GetComponent<Transform>()->GetPosition();

		//�����𑪂�(�v���C���[���m�̑̂̑傫���͕ς��Ȃ��Ǝv���̂�1�̖ڂ��Q��)
		float half = Player1->GetComponent<Transform>()->GetScale().x / 2 + m_BombDistance / 2;
		//�������Ƃ�Ȃ��悤��
		half *= half;
		//���ꂼ��̍����v�Z
		Vector3 dist1 = GetComponent<Transform>()->GetPosition() - Player1->GetComponent<Transform>()->GetPosition();
		Vector3 dist2 = GetComponent<Transform>()->GetPosition() - Player2->GetComponent<Transform>()->GetPosition();
		dist1 = dist1 * dist1;
		dist2 = dist2 * dist2;

		//�ǂ�����������
		if (half > dist1.x + dist1.z || half > dist2.x + dist2.z)
		{
			//�_���[�W��^����
			//HP�����炷
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(m_Power);
			PtrPlayerHP->SetHit(true);
		}
	}

	//�ė��p
	void Bomb::SetActivePosition(Vector3 pos)
	{
		m_time = 0;
		m_Activeflg = true;

		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}


	//************************************************************************
	//	�e���|�[�g�G�l�~�[�̃e���|�[�g��
	//	��莞�ԂŋN��
	//************************************************************************
	TereportPoint::TereportPoint(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_Pos(pos)
	{}

	void TereportPoint::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(2, 2, 2);
		Trans->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"TEREPORTPOINT_TX");
		Draw->SetMeshResource(L"DEFAULT_SQUARE");

		SetAlphaActive(true);

		//���C���[�ݒ�
		SetDrawLayer(1);
	}
	//Abe20170508

	//Abe20170512
	//************************************************************************
	//	���G�h���[��
	//	�v���C���[������܂ŒT��
	//************************************************************************
	SearchDrawn::SearchDrawn(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}
	
	void SearchDrawn::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(0.5f, 0.5f, 0.5f);
		Trans->SetRotation(0, 0, 0);


		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"SEARCHDRAWN_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//��������
		SetAlphaActive(true);

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		//auto circle = GetStage()->AddGameObject<GameObject>();
		//auto TransCi = circle->AddComponent<Transform>();
		//TransCi->SetPosition(0,1,0);
		//TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		//TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		//auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		//DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		//DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		//circle->SetAlphaActive(true);
		//circle->SetDrawActive(false);
		////���C���[�ݒ�
		//circle->SetDrawLayer(2);

		//m_SearchCircle = circle;
		
		//Abe20170523
		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<SearchCircle>();
		auto TransCi = circle->GetComponent<Transform>();
		TransCi->SetPosition(0, 0, 0);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		m_SearchCircle = circle;
		//Abe20170523
		//Abe20170515
		//�X�e�[�W�̑傫���擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515

	}

	void SearchDrawn::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//�v���C���[�������Ă��Ȃ��Ƃ�
			if (!m_FindPlayerFlg)
			{
				//�؂�ւ����ԉz����������ւ�
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > m_ChangeTime)
				{
					m_Velocity = Vector3(rand() % 200-100, 0, rand() % 200-100) / 100;

					m_time = 0;
				}

				//�ړ�
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity * App::GetApp()->GetElapsedTime() * m_Speed;
				GetComponent<Transform>()->SetPosition(pos);

				//�T�[�N���ړ�
				pos.y = 1;
				m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);

				//�����锻��
				Search();
				//�X�e�[�W�̒[�̔���
				StageEndCheck();
			}
			//������
			else
			{
				//��Ɉړ�
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos.y += 5*m_Speed * App::GetApp()->GetElapsedTime();
				GetComponent<Transform>()->SetPosition(pos);

				//20�ȏ�s������
				if (pos.y > 20)
				{
					SetDrawActive(false);
					m_ActiveFlg = false;
					m_FindPlayerFlg = false;
				}
			}
		}
	}

	void SearchDrawn::Search()
	{
		//�ʒu���擾
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//�����𑪂�
		//�P�̖�
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			m_FindPlayerFlg = true;
			//�����̔ԍ��ƈ�v����e���|�[�g�̂���N��
			auto EnemyGrouP = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			for (auto obj : EnemyGrouP)
			{
				//�e���|�[�g�G�l�~�[�ɃL���X�g
				auto ptr = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
				if (ptr)
				{
					//�����̔ԍ��ƈ�v
					if (ptr->GetNumber() == m_number)
					{
						ptr->ToAttack(1);
						break;
					}
				}
			}
		}
		//�Q�̖�
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			m_FindPlayerFlg = true;

			//�����̔ԍ��ƈ�v����e���|�[�g�̂���N��
			auto EnemyGrouP = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			for (auto obj : EnemyGrouP)
			{
				//�e���|�[�g�G�l�~�[�ɃL���X�g
				auto ptr = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
				if (ptr)
				{
					//�����̔ԍ��ƈ�v
					if (ptr->GetNumber() == m_number)
					{
						ptr->ToAttack(2);
						break;
					}
				}
			}

		}

	}

	void SearchDrawn::GoDrawn(Vector3 pos,Vector3 vel, int num)
	{
		//���W�ړ�
		Vector3 pos1 = pos;
		pos1.y += 1;
		GetComponent<Transform>()->SetPosition(pos);
		//�ړ��͐ݒ�
		m_Velocity = vel;

		//�ԍ�
		m_number = num;

		//�N��
		m_ActiveFlg = true;
		
		//����
		SetDrawActive(true);

		m_time = 0;
		
		//�T�[�N���`��
		m_SearchCircle->SetDrawActive(true);
		Vector3 pos2 = pos;
		pos2.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos2);

	}

	//Abe20170515
	//�X�e�[�W�̒[�ɂ����������肵�Č������]������
	void SearchDrawn::StageEndCheck()
	{
		//�ʒu[�E]�A[��]�A[��]�A[��]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x + scale.x, pos.z + scale.z, pos.x - scale.x, pos.z - scale.z);
		//�X�e�[�W�̒[�ɓ������Ă邩����
		//�E
		if (m_StageSize.x < PositionPXYMXY.x)
		{
			pos.x = m_StageSize.x - scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (m_StageSize.y < PositionPXYMXY.y)
		{
			pos.z = m_StageSize.y - scale.z;
			m_Velocity.z *= -1;
		}
		//��
		if (-m_StageSize.x > PositionPXYMXY.z)
		{
			pos.x = -m_StageSize.x + scale.x;
			m_Velocity.x *= -1;
		}
		//��
		if (-m_StageSize.y > PositionPXYMXY.w)
		{
			pos.z = -m_StageSize.y + scale.z;
			m_Velocity.z *= -1;
		}

	}
	//Abe20170515

	void SearchDrawn::UpDrawns()
	{
		m_FindPlayerFlg = true;
		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

	}
	//Abe20170512

	//Abe20170515
	//************************************
	//	�~�T�C��
	//	�X�e�[�W�̒[�ɍs�������ɓ�����܂�
	//	�����Ă�����Ɉړ�
	//************************************
	Missile::Missile(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void Missile::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(0, 0, 0);
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"MISSILE_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//��������
		SetAlphaActive(true);
		SetDrawActive(false);

		//Abe20170515
		//�X�e�[�W�̑傫���擾
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515

		//Abe20170517
		m_Effect = GetStage()->AddGameObject<BombEffect>();
		//Abe20170517

		//Abe20170519
		//�e�쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		TransCi->SetPosition(0, 1, 0);
		TransCi->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SHOADOW_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		circle->SetDrawActive(false);
		//���C���[�ݒ�
		circle->SetDrawLayer(2);

		m_Shadow = circle;
		//Abe20170519
	}

	void Missile::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//���W�ړ�
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			GetComponent<Transform>()->SetPosition(pos);
			
			//�e�ړ�
			pos.y = 1;
			m_Shadow->GetComponent<Transform>()->SetPosition(pos);
			if (m_FallFlg)
			{
				//������ƒx�߂ɗ��Ƃ�
				m_Velocity.y += -9.8f * App::GetApp()->GetElapsedTime() / 3;

				//���ɋ߂��Ȃ��������
				if (GetComponent<Transform>()->GetPosition().y <= 0.5f)
				{
					DeleteMissile();
				}
			}
			StageEndCheck();
		}
	}

	//�X�e�[�W�̒[�ɍs�������𔻒肷��
	void Missile::StageEndCheck()
	{
		//�ʒu[�E]�A[��]�A[��]�A[��]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x + scale.x, pos.z + scale.z, pos.x - scale.x, pos.z - scale.z);
		//�X�e�[�W�̒[�ɓ������Ă邩����
		//�E
		if (m_StageSize.x < PositionPXYMXY.x ||
			m_StageSize.y < PositionPXYMXY.y ||
			-m_StageSize.x > PositionPXYMXY.z ||
			-m_StageSize.y > PositionPXYMXY.w
			)
		{
			//�������Ă������
			DeleteMissile();
		}

	}
	void Missile::SetMissileActive(Vector3 pos, Vector3 scale, Vector3 velocity,bool falltype,int power)
	{
		//���W�ړ�
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(pos);
		Trans->SetScale(scale);
		
		//�����x�ǉ�
		m_Velocity = velocity;

		//�N��
		m_ActiveFlg = true;

		//�`��
		SetDrawActive(true);
		//�e��
		m_Shadow->SetDrawActive(true);

		//������t���O�ݒ�
		m_FallFlg = falltype;

		//�U���͐ݒ�
		m_power = power;

		if (!falltype)
		{
			m_Zokusei = 1;
		}
		else
		{
			m_Zokusei = 0;
		}
	}

	void Missile::DeleteMissile()
	{
		if (m_ActiveFlg)
		{
			//�����쐬
			m_Effect->SetPosActive(GetComponent<Transform>()->GetPosition());

			//�I��
			m_ActiveFlg = false;

			//�`�����
			SetDrawActive(false);

			//�e��
			m_Shadow->SetDrawActive(false);
		}
	}
	//Abe20170515

	//Abe20170517
	void Missile::ToDamagePleyer()
	{
		////������ݒ�ɂ���Ă�Ƃ���y���W�𑪂�
		//if (m_FallFlg)
		//{
		//	float PlayerY = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->GetComponent<Transform>()->GetPosition().y;
		//	//������Ə��
		//	PlayerY += GetComponent<Transform>()->GetScale().y / 2;
		//	//�v���C���[��茋�\��̂ق��ɂ����画�肵�Ȃ�
		//	if (GetComponent<Transform>()->GetPosition().y > PlayerY)
		//	{
		//		return;
		//	}
		//}

		//HP�����炷
		auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
		PtrPlayerHP->SetDamage_int(1);
		PtrPlayerHP->SetHit(true);

		//�~�T�C��������
		DeleteMissile();
	}
	//Abe20170517

	//Abe20170523IzumiHikitugi
	//************************************
	//	���G�T�[�N��(SS��)
	//	�X�v���C�g�X�^�W�I�ōĐ�
	//************************************
	SearchCircle::SearchCircle(const shared_ptr<Stage>& StagePtr) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + L"EF\\", L"NewAnimation.ssae", L"anime_1")
	{
	}
	void SearchCircle::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 1, 0);
		Trans->SetScale(5, 5, 5);
		Trans->SetRotation(0, 0, 0);

		//�A�j���[�V�����֘A
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(0.07f, 0.07f, 0.07f),
			Vector3(0, 0, 0),
			Vector3(0.0f, 0.0f, 0.0f)
			);
		SetToAnimeMatrix(mat);

		//�e�N���X��Create
		SS5ssae::OnCreate();
		//�b������̃t���[����
		SetFps(60.0f);
		//���[�v�L��
		SetLooped(true);


		//�����x�L����
		SetAlphaActive(true);
		//�`��
		SetDrawActive(true);
		//�\�����C���[
		SetDrawLayer(2);
	}
	void SearchCircle::OnUpdate() {
		//�A�j���\�V�����X�V
		UpdateAnimeTime(App::GetApp()->GetElapsedTime()/2);
	}
	//Abe20170523IzumiHikitugi

	//Abe20170605
	//************************************
	//	���U���Ĕ�Ԃ��
	//************************************
	void BakuSanObj::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(1, 1, 1);
		Trans->SetRotation(0, 0, 0);

		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//������
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"PARTS1_MODEL");
		//���f���傫������
		Draw->SetMeshToTransformMatrix(Mat);

		//��������
		SetAlphaActive(true);
		SetDrawActive(false);
		SetUpdateActive(false);
	}

	void BakuSanObj::OnUpdate()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();

		//�ݒ肵���͂œ�����
		pos += m_Velocity * App::GetApp()->GetElapsedTime();
		GetComponent<Transform>()->SetPosition(pos);

		//�d��
		m_Velocity.y += -9.8f * App::GetApp()->GetElapsedTime();

		//�K���ɉ�]
		Vector3 rot = GetComponent<Transform>()->GetRotation();
		rot += m_RotPow * App::GetApp()->GetElapsedTime();
		GetComponent<Transform>()->SetRotation(rot);

		//�n�ʂɂ������������
		if (pos.y < 0)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void BakuSanObj::SetPosScaleVelo(Vector3 pos, Vector3 sca, Vector3 vel)
	{
		//�`�悵�ăA�b�v�f�[�g�N��
		SetDrawActive(true);
		SetUpdateActive(true);

		//�ʒu�Ƒ傫���Ƒ��x�ݒ�
		GetComponent<Transform>()->SetPosition(pos);
		GetComponent<Transform>()->SetScale(sca);
		m_Velocity = vel;

		//��]�͂�ݒ�
		m_RotPow = Vector3(((rand() % 30) / 10), ((rand() % 30) / 10), ((rand() % 30) / 10));

		//���b�V���ύX1�`100
		int random = rand() % 100+1;
		int meshnum = 0;
		if (1 <= random && random <= 29)
		{
			meshnum = 0;
		}
		else if (30 <= random && random <= 49)
		{
			meshnum = 1;
		}
		else if (50 <= random && random <= 68)
		{
			meshnum = 2;
		}
		else if (69 <= random && random <= 79)
		{
			meshnum = 3;
		}
		else if (80 <= random && random <= 87)
		{
			meshnum = 4;
		}
		else if (88 <= random && random <= 95)
		{
			meshnum = 5;
		}
		else if (96 <= random && random <= 100)
		{
			meshnum = 6;
		}

		switch (meshnum)
		{
		case 0:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS1_MODEL");
			break;
		case 1:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS2_MODEL");
			break;
		case 2:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS3_MODEL");
			break;
		case 3:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS4_MODEL");
			break;
		case 4:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS5_MODEL");
			break;
		case 5:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS6_MODEL");
			break;
		case 6:
			GetComponent<PNTStaticModelDraw>()->SetMeshResource(L"PARTS7_MODEL");
			break;

		}
	}

	//************************************
	//	���U���Ĕ�Ԃ�Ǘ�������
	//************************************
	void BakuSanSpawn::CreateBakusan(int num,Vector3 pos)
	{
		for (int i = 0; i < num; i++)
		{
			//�`�悳��ĂȂ�����ė��p
			auto BakuGroup = GetStage()->GetSharedObjectGroup(L"BakusanObjGroup")->GetGroupVector();
			//�`�悳��ĂȂ��t���O
			bool DrawFlg = false;
			for (auto obj : BakuGroup)
			{
				auto ptr = dynamic_pointer_cast<BakuSanObj>(obj.lock());
				if (!ptr->GetDrawActive())
				{
					DrawFlg = true;

					//�ݒ�
					//�ʒu�͂��̂܂�
					//�傫�������_�� 0.5�`0.1
					Vector3 ransca = Vector3((rand() % 5) / 10.0f + 0.1f, (rand() % 5) / 10.0f + 0.1f, (rand() % 5) / 10.0f + 0.1f);
					//���x�����_�� 10�`-10
					Vector3 ranvel = Vector3(((rand() % 200) - 100) / 10.0f, (rand() % 100) / 10.0f + 2.0f, ((rand() % 200) - 100) / 10.0f);
					ptr->SetPosScaleVelo(pos, ransca, ranvel);
					break;
				}
			}

			//�ǂ���g���Ȃ���΍��
			if (!DrawFlg)
			{
				auto obj = GetStage()->AddGameObject<BakuSanObj>();
				GetStage()->GetSharedObjectGroup(L"BakusanObjGroup")->IntoGroup(obj);

				//�ݒ�
				//�ʒu�͂��̂܂�
				//�傫�������_�� 0.5�`0.1
				Vector3 ransca = Vector3((rand() % 5) / 10.0f + 0.1f, (rand() % 5) / 10.0f + 0.1f, (rand() % 5) / 10.0f + 0.1f);
				//���x�����_�� 10�`-10
				Vector3 ranvel = Vector3(((rand() % 200) - 100) / 10.0f, (rand() % 100) / 10.0f + 2.0f, ((rand() % 200) - 100) / 10.0f);
				obj->SetPosScaleVelo(pos, ransca, ranvel);

			}
		}
	}
	//Abe20170605

}
