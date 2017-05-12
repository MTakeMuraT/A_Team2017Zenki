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
	//	���G�ň������������v���C���[��_���B���Ԃ񓯎��ɓ�������Q�̖ڂ�_��
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

		//�����Ă邩
		bool m_ActiveFlg = true;

		//���ԑ���p
		float m_time = 0;

		//�U���܂ł̃^������
		float m_AttackTime = 2.0f;
		//�ˌ�������
		int m_AttackCount = 0;
		//�U����(����A�U����Ԃł������ŁADamageFlg���Ă��ĂԂ���)
		bool m_TackleFlg = false;
		//�U�����Ă�Ώ�
		int m_TargetNum = 0;
		//�ˌ����Ă鎞��
		float m_TackleTime = 3.0f;


		/*�Ԃ�Ԃꂷ�邩�ǂ����킩��񂩂���u�I ����Ɋ֌W������̂�1A�ŃR�����g�A�E�g
		//�Ԃ�Ԃꂳ����p�̍��W
		Vector3 m_BurePos;
		*/

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

		//Velocity�𔽓]���� ����(x,z)��true�����Ɣ��]
		//�����ɂ��낢�날��������m���B�����d�l���킻��A���΂킩��
		void TurnVecolity(bool, bool);

		//�_���[�W�󂯂邩�ǂ����̃t���O�󂯓n���p
		bool GetDamageFlg() { return m_TackleFlg; }

		//��ԕύX
		void ToSearch();
		void ToMove();
		void ToAttack(int);		//�U������Ώ�(1�Ȃ�P�̖�2�Ȃ�Q�̖�)
		void ToCoolTime();

		//�v���C���[�ւ̍U������
		void ToDamagePlayer();

		//�������_���[�W�󂯂��Ƃ��̊֐�
		//�v���C���[����
		void DamagePlayer();
		//�~�T�C���Ƃ����e�Ƃ��v���C���[�ȊO
		void Damage(int num);
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

		//�U������Ώ�
		int m_TargetNum = 0;
		//�U��(�e���|�[�g)�܂ł̎���
		float m_AttackWaitTime = 0.5f;
		//���e�u�����
		bool m_BombPutFlg = false;
		//���e�u�������
		bool m_BombAfterFlg = false;
		//���e�u���Ă�Ԃ̎���
		float m_BombPutTime = 1;
		//�u�����㓦����܂ł̎���
		float m_TereportTime = 1;

		//�����̑����̃e���|�[�g�|�C���g
		shared_ptr<GameObject> m_UnderTereportPoint;

		//�A�N�e�B�u�t���O
		bool m_ActiveFlg = true;

		//�f�o�b�O����
		shared_ptr<DebugTxt> m_Debugtxt;

		//�q�@
		vector<shared_ptr<GameObject>> m_Drawns;
		//�q�@�ł��o������
		void GoDrawns();

		//�q�@�Ɏ�����F�������邽�߂̔ԍ�
		int m_number;

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


	public:
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A�N�[���^�C��(cooltime)�A���ː�(shotamount)
		TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�U��
		void Attack();
		//�N�[���^�C��
		void CoolTime();

		//�T�[�N���ړ�
		void CircleMove();

		//��ԕύX
		void ToSearch();
		void ToAttack(int);		//�U������Ώ�(1�Ȃ�P�̖�2�Ȃ�Q�̖�)
		void ToCoolTime();

		//�v���C���[����
		void DamagePlayer();
		//�_���[�W�󂯂�֐�
		void Damage(int);

		//�ԍ��擾
		int GetNumber() {return m_number; }
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

		
		//�T���܂ł̊Ԋu
		float m_moveInterval = 2;
		//�ړ���Velocity
		Vector3 m_Velocity;

		//�����Ă邩
		bool m_ActiveFlg = true;


		//���ԑ���p
		float m_time;

		//�U���܂ł̃^������
		float m_AttackTime = 2.0f;
		//�U����(����A�U����Ԃł������ŁADamageFlg���Ă��ĂԂ���)
		bool m_TackleFlg = false;
		//�U�����Ă�Ώ�
		int m_TargetNum = 0;
		//�ˌ����Ă鎞��
		float m_TackleTime = 3.0f;



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
		//�ˌ���
		int m_TackleCount;


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
		
		//�T�[�N���ړ�
		void CircleMove();


		//��ԕύX
		void ToSearch();
		void ToMove();
		void ToAttack(int);		//�U������Ώ�(1�Ȃ�P�̖�2�Ȃ�Q�̖�)

		//�v���C���[�ւ̍U������
		void ToDamagePlayer();

	};

	//Abe20170508
	//======================�ȉ��q�@�Q=======================
	//************************************
	//	���e�̔����̕���
	//	�g�k�����ł������ȁH
	//************************************
	class BombEffect : public GameObject
	{
	private:
		//���
		int m_State = 0;
		//�A�N�e�B�u�t���O
		bool m_ActiveFlg = false;
	public:
		BombEffect(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//�N���A�~�܂��Ă�΍ċN�������B�����͍��W
		void SetPosActive(Vector3);
	};

	//************************************
	//	���e
	//	��莞�ԂŋN��
	//************************************
	class Bomb : public GameObject
	{
	private:
		//���W
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;

		//�v�Z�p����
		float m_time = 0;
		//�����Ă邩
		bool m_Activeflg = true;

		//�ȉ��p�����[�^
		//�����͈�
		float m_BombDistance;
		//�U����
		int m_Power;
		//�����܂ł̎���
		float m_ExplosionTime = 3.0f;

		shared_ptr<BombEffect> m_Effect;
	public:
		//���W�A�傫���A�����͈́A�U���́A�����܂ł̎���
		Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos, float scale, float bombdistance, float power, float explosiontime);

		//�����|�W�V�����̂݁B�Ă�������{�������g���Ăق���
		Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos);
		void OnCreate() override;
		void OnUpdate() override;

		//���܂ꂽ�甚��
		void BombExplosion();

		//�ė��p
		void SetActivePosition(Vector3 pos);

		bool GetActive() { return m_Activeflg; }
	};

	//************************************
	//	�e���|�[�g�G�l�~�[�̃e���|�[�g��
	//	��莞�ԂŋN��
	//************************************
	class TereportPoint : public GameObject
	{
	private:
		//���W
		Vector3 m_Pos;
		//���G�l�~�[����Ă邩
		bool m_OnEnemy = false;
	public:
		TereportPoint(const shared_ptr<Stage>& StagePtr, Vector3 pos);

		void OnCreate() override;

		void SetOnEnemy(bool flg) { m_OnEnemy = flg; };
		bool GetOnEnemy() { return m_OnEnemy; };
	};
	//Abe20170508
	//Abe20170512
	//************************************
	//	���G�h���[��
	//	�v���C���[������܂ŒT��
	//************************************
	class SearchDrawn : public GameObject
	{
	private :
		//�v�Z�p����
		float m_time = 0;
		//�����؂�ւ�����
		float m_ChangeTime = 3.0f;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;
		//���G�͈͂̉摜(�X�N�G�A)
		shared_ptr<GameObject> m_SearchCircle;

		//�ړ����x
		Vector3 m_Velocity;

		//�N�����Ă邩�ǂ���
		bool m_ActiveFlg = false;
		//�v���C���[�������t���O
		bool m_FindPlayerFlg = false;

		//���ʔԍ�
		int m_number;

		//�ȉ��p�����[�^
		//���G����
		float m_SearchDistance = 2.0f;
		//�ړ����x
		float m_Speed = 5.0f;

	public :
		SearchDrawn(const shared_ptr<Stage>& StagePtr);

		void OnCreate()override;
		void OnUpdate()override;

		//�����锻��
		void Search();
		//���o
		void GoDrawn(Vector3 pos, Vector3 vel,int num);

		bool GetActiveFlg() { return m_ActiveFlg; }

		//���[
		void UpDrawns();
	};
	//Abe20170512

}