//************************************
//*		�쐬���F2017/05/05
//*		�쐬�ҁFAbe
//*		���e�F
//*		�G�l�~�[�܂Ƃ�
//************************************


#pragma once
#include "stdafx.h"

enum EnemyState
{
	SearchS,
	MoveS,
	AttackS,
	CoolTimeS
};

namespace basecross
{
	//************************************
	//	�ˌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************
	class TackleEnemy : public GameObject
	{
	private :
		//�����ʒu
		Vector3 m_InitPos;
		//���݂̏��
		EnemyState m_State;
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//���G�͈͂̉摜(�X�N�G�A)
		shared_ptr<GameObject> m_SearchCircle;

		//�T���܂ł̊Ԋu
		float m_moveInterval = 2;
		//�ړ���Velocity
		Vector3 m_Velocity;

		//���ԑ���p
		float m_time;

		//�ȉ��p�����[�^
		//�傫��
		float m_ParScale;
		//HP
		int m_Hp;
		//���G����
		float m_SearchDistance;
		//�N�[���^�C��
		float m_CoolTime;
		//���x
		float m_Speed;
		//�U����
		int m_Power;
		//�ˌ���
		int m_TackleCount;

		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<DebugTxt> m_Debugtxt;

	public :
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A�N�[���^�C��(cooltime)�A���x(speed)�A�U����(power)�A�ˌ���(tacklecount)
		TackleEnemy(const shared_ptr<Stage>& StagePtr,Vector3 pos,float parscale,int hp,float searchdistance,float cooltime,float speed,int power,int tacklecount);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�T��
		void Move();
		//�U��
		void Attack();
		//�N�[���^�C��
		void CoolTime();

		//�T�[�N���ړ�
		void CircleMove();
	};

	//************************************
	//	�ʌ��G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************

	class ShotEnemy : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//���݂̏��
		EnemyState m_State;
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//���G�͈͂̉摜(�X�N�G�A)
		shared_ptr<GameObject> m_SearchCircle;

		//���ԑ���p
		float m_time;

		//�ȉ��p�����[�^
		//�傫��
		float m_ParScale;
		//HP
		int m_Hp;
		//���G����
		float m_SearchDistance;
		//�N�[���^�C��
		float m_CoolTime;
		//�U����
		int m_Power;
		//�q�@���ˊԊu
		float m_ShotChildInterval;
		//���ː�(�~�T�C��)
		int m_ShotAmount;
	public:
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A�N�[���^�C��(cooltime)�A�U����(power)�A�q�@���ˊԊu(shotchildinterval)�A���ː�(shotamount)
		ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime,int power, float shotchildinterval,int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�T��
		void Move();
		//�U��
		void Attack();
		//�N�[���^�C��
		void CoolTime();
	};

	//************************************
	//	���e�u���ăe���|�[�g�G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************

	class TeleportEnemy : public GameObject
	{
	private :
		//�����ʒu
		Vector3 m_InitPos;
		//���݂̏��
		EnemyState m_State;
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//���G�͈͂̉摜(�X�N�G�A)
		shared_ptr<GameObject> m_SearchCircle;

		//���ԑ���p
		float m_time;

		//�ȉ��p�����[�^
		//�傫��
		float m_ParScale;
		//HP
		int m_Hp;
		//���G����
		float m_SearchDistance;
		//�N�[���^�C��
		float m_CoolTime;
		//�q�@���ˊԊu
		//float m_ShotChildInterval;
		//���ː�(�q�@)
		int m_ShotAmount;

	public :
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A�N�[���^�C��(cooltime)�A���ː�(shotamount)
		TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�T��
		void Move();
		//�U��
		void Attack();
		//�N�[���^�C��
		void CoolTime();
	};

	//************************************
	//	�����G�l�~�[
	//	�ǋL�Ȃ��H
	//************************************
	class BombEnemy : public GameObject
	{
	private:
		//�����ʒu
		Vector3 m_InitPos;
		//���݂̏��
		EnemyState m_State;
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//���G�͈͂̉摜(�X�N�G�A)
		shared_ptr<GameObject> m_SearchCircle;

		//���ԑ���p
		float m_time;

		//�ȉ��p�����[�^
		//�傫��
		float m_ParScale;
		//HP
		int m_Hp;
		//���G����
		float m_SearchDistance;
		//���x
		float m_Speed;
		//�U����
		int m_Power;

	public:
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A���x(speed)�A�U����(power)
		BombEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float speed, int power);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�T��
		void Move();
		//�U��
		void Attack();
	};
}