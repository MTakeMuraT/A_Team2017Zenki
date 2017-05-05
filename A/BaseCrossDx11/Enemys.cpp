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
		m_Debugtxt->SetText(Util::IntToWStr(m_State));

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
		Vector3 mypos  = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;
		//�����𑪂�
		//�P�̖�
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			//�T�[�N������
			m_SearchCircle->SetDrawActive(false);
			//�U����Ԃֈڍs
			m_State = AttackS;
		}
		//�Q�̖�
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			//�T�[�N������
			m_SearchCircle->SetDrawActive(false);
			//�U����Ԃֈڍs
			m_State = AttackS;
		}

		//m_Debugtxt->SetText(Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)) + L"\n" + Util::FloatToWStr(distance*distance));
		//m_Debugtxt->SetText(L"dis:" + Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)));

		//��莞�ԂŒT����Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			m_State = MoveS;
			//�T�[�N������
			m_SearchCircle->SetDrawActive(false);
			//0.5�`-0.5�܂Ń����_���ŏo���ăX�s�[�h������
			m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
			m_Velocity /= 100;
			m_Velocity *= m_Speed;
			m_time = 0;
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
			m_time = 0;
			m_State = SearchS;
			//�T�[�N���ړ�
			CircleMove();
		}
	}

	void TackleEnemy::Attack()
	{

	}

	void TackleEnemy::CoolTime()
	{
		//�N�[���^�C���߂�������G��Ԃ�
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			m_State = SearchS;
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