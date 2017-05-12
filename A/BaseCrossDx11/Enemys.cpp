#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	//************************************
	//	�ˌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************
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

		//������
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;



		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F�ԂɕύX
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);

	}

	void TackleEnemy::OnUpdate()
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
				break;
				//�T��
			case MoveS:
				Move();
				break;
				//�U��
			case AttackS:
				Attack();
				break;
				//�N�[���^�C��
			case CoolTimeS:
				CoolTime();
				break;
			}
		}
	}

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

	void TackleEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//�����ֈړ�
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
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

	}

	void TackleEnemy::ToMove()
	{
		//�v�Z���ԏ�����
		m_time = 0;

		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

		//�ړ��x�N�g��(?)�v�Z
		//0.5�`-0.5�܂Ń����_���ŏo���ăX�s�[�h������
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 100;
		m_Velocity *= m_Speed;

		//��ԕύX
		m_State = MoveS;

	}

	void TackleEnemy::ToAttack(int num)
	{
		//�v�Z���ԏ�����
		m_time = 0;
		//�U������Ώۂ�ݒ�
		m_TargetNum = num;

		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

		//��ԕύX
		m_State = AttackS;
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
	}

	//�v���C���[�ւ̍U������
	void TackleEnemy::ToDamagePlayer()
	{
		//�U�����Ȃ�
		if (m_TackleFlg)
		{
			//HP�����炷
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
			ToCoolTime();
		}
	}

	//�U���󂯂��Ƃ�
	void TackleEnemy::DamagePlayer()
	{
		//����HP��1�ȉ��Ȃ�
		if (m_Hp <= 1)
		{
			//�^�q��
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;
		}
		else
		{
			m_Hp--;
		}
	}

	void TackleEnemy::Damage(int num)
	{
		//HP���炵�ĂȂ��Ȃ��Ă��1�c��
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
		}
	}

	//************************************
	//	�ʌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************

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

		//������
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;
	}

	void ShotEnemy::OnUpdate()
	{
		switch (m_State)
		{
			//���G
		case SearchS:
			Search();
			break;
			//�T��
		case MoveS:
			Move();
			break;
			//�U��
		case AttackS:
			Attack();
			break;
			//�N�[���^�C��
		case CoolTimeS:
			CoolTime();
			break;
		}
	}

	void ShotEnemy::Search()
	{

	}

	void ShotEnemy::Move()
	{

	}

	void ShotEnemy::Attack()
	{

	}

	void ShotEnemy::CoolTime()
	{

	}

	//Abe20170508
	//************************************
	//	���e�u���ăe���|�[�g�G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************

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
		Trans->SetRotation(0, 0, 0);

		//������
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;

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
				break;
				//�U��
			case AttackS:
				Attack();
				break;
				//�N�[���^�C��
			case CoolTimeS:
				CoolTime();
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
						}
					}
					//�g�������Ȃ���������
					if (!PutFlg)
					{
						GetStage()->AddGameObject<Bomb>(GetComponent<Transform>()->GetPosition());
					}

					//Abe20170512
					m_Debugtxt->SetText(Util::IntToWStr(count));
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
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
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

		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

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
		//����HP��1�ȉ��Ȃ�
		if (m_Hp <= 1)
		{
			//�^�q��
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;
		}
		else
		{
			m_Hp--;
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

	//************************************
	//	�����G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************
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

		//������
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		//�X�e�[�g������
		m_State = SearchS;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//�����ֈړ�
		posci.y += -m_ParScale / 2;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		m_SearchCircle = circle;

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
				break;
				//�T��
			case MoveS:
				Move();
				break;
				//�U��
			case AttackS:
				Attack();
				break;
			}
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
		pos.y += -m_ParScale / 2;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
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

		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

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

		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

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
			PtrPlayerHP->SetDamage_int(3);
			PtrPlayerHP->SetHit(true);

			//�����̈׏���
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

		}

	}
		void BombEnemy::DamagePlayer()
		{	
				//�^�q��
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;
		
		}

	//Abe20170508
	//======================�ȉ��q�@�Q=======================
	//************************************
	//	���e�̔����̕���
	//	�g�k�����ł������ȁH
	//************************************
	BombEffect::BombEffect(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void BombEffect::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(1, 1, 1);
		Trans->SetRotation(0, 0, 45 * 3.14159265f / 180);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(L"BOMBEFFECT_TX");

		SetAlphaActive(true);
	}

	void BombEffect::OnUpdate()
	{
		if (m_ActiveFlg)
		{
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
			}
		}
	}

	void BombEffect::SetPosActive(Vector3 pos)
	{
		m_ActiveFlg = true;
		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}

	//************************************
	//	���e
	//	��莞�ԂŋN��
	//************************************
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

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"BOMB_TX");
		Draw->SetMeshResource(L"DEFAULT_SPHERE");

		//�����x�L��
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


	//************************************
	//	�e���|�[�g�G�l�~�[�̃e���|�[�g��
	//	��莞�ԂŋN��
	//************************************
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

	}
	//Abe20170508

	//Abe20170512
	//************************************
	//	���G�h���[��
	//	�v���C���[������܂ŒT��
	//************************************
	SearchDrawn::SearchDrawn(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}
	
	void SearchDrawn::OnCreate()
	{
		//���W�A�傫���A��]
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(0.25f, 0.25f, 0.25f);
		Trans->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"TEREPORTPOINT_TX");
		Draw->SetMeshResource(L"DEFAULT_SPHERE");

		SetAlphaActive(true);

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ̂��͂��߂ɂ����Ă��Ă���
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//���G�͈͍쐬
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		TransCi->SetPosition(0,0,0);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		circle->SetDrawActive(false);
		m_SearchCircle = circle;


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

	void SearchDrawn::UpDrawns()
	{
		m_FindPlayerFlg = true;
		//�T�[�N������
		m_SearchCircle->SetDrawActive(false);

	}
	//Abe20170512
}
