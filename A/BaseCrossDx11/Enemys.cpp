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

	void TackleEnemy::Search()
	{
		//�ʒu���擾
		Vector3 mypos  = GetComponent<Transform>()->GetPosition();
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

	//�Ȃ񂩂ɂԂ������瑬�x���]���Əc�ǂ��������������������ق���
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
		TransCi->SetRotation(90 * 3.14159265/180, 0, 0);

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

	void TeleportEnemy::OnUpdate()
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

	void TeleportEnemy::Search()
	{

	}

	void TeleportEnemy::Move()
	{

	}

	void TeleportEnemy::Attack()
	{

	}

	void TeleportEnemy::CoolTime()
	{

	}

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
			break;
		}

	}

	void BombEnemy::Search()
	{

	}

	void BombEnemy::Move()
	{

	}

	void BombEnemy::Attack()
	{

	}


}