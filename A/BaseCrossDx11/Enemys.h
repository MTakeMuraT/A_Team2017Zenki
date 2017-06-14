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
	CoolTimeS,
	MutekiS
};

namespace basecross
{

	//Abe20170612
	//************************************
	//�@�V�[���h
	//************************************
	class EnemyShield : public GameObject
	{
	private:
		//�V�[���h�̐�
		int m_ShieldAmout = 0;
		//�V�[���h
		vector<shared_ptr<GameObject>> m_ShieldS;
		//�V�[���h�̊p�x
		vector<float> m_ShieldAngleS;
		//�V�[���h�̒��S���W
		Vector3 m_ShieldPos;
		//�V�[���h�̑傫��
		Vector3 m_ShieldScale;
		//���S����̋���
		float m_Half;

		//���݂̃V�[���h�̐�
		int m_NowShieldNum;
	public:
		EnemyShield(const shared_ptr<Stage>& StagePtr, int num, Vector3 pos, Vector3 sca, float half);

		void OnCreate() override;
		void OnUpdate() override;

		void SetPos(Vector3 pos);

		void Damage(int dam);
	};
	//Abe20170612

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

		//Abe20170515
		//�X�e�[�W�̕�
		Vector2 m_StageSize;

		//�X�e�[�W�̒[�ɍs���������肵�Č�����ς���֐�
		void StageEndCheck();
		//Abe20170515


		//Abe20170526
		//���G�t���O
		bool m_MutekiFlg = false;
		//���G����
		float m_MutekiTime = 3.0f;
		//�_�ŗp
		float m_MutekiTenmetuTime = 0;
		//Abe20170526

		//Abe20170519
		//��]
		void Rot();
		//Abe20170519

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
		

		//Abe20170526
		//�A�j���[�V�����ύX
		void ChangeAnimation(string);
		//Abe20170526

		//Abe20170612
		//�V�[���h
		shared_ptr<EnemyShield> m_Shield;
		//Abe20170612
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
		//Abe20170526
		//���G����
		void Muteki();
		//Abe20170526

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
		//Abe20170526
		void ToMuteki();
		//Abe20170526

		//�v���C���[�ւ̍U������
		void ToDamagePlayer();

		//�������_���[�W�󂯂��Ƃ��̊֐�
		//�v���C���[����
		void DamagePlayer();
		//�~�T�C���Ƃ����e�Ƃ��v���C���[�ȊO
		void Damage(int num);
		int GetPower() { return m_Power; }
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

		//��]���x
		float m_rotSpeed = 180.0f;

		//���ԑ���p
		float m_time = 0;
		float m_Childtime = 0;

		//�~�T�C��
		vector<shared_ptr<GameObject>> m_MissileS;
		//�~�T�C���̑傫��
		Vector3 m_MissileScale = Vector3(0.8f, 0.8f, 0.8f);
		//�q�@
		vector<shared_ptr<GameObject>> m_ChildS;

		//�q�@�f���o���֐�
		void ShotChild();
		//���̍��G���Ɏq�@��f���o������
		bool m_ShotChild = false;

		//Abe20170517
		//�����t���O
		bool m_ActiveFlg = true;
		//�����_���ő_���ق������߂�
		int m_TargetPlayer = 0;
		//��΂���
		float m_ShotPower = 3.0f;
		//Abe20170517

		//Abe20170526
		//�A�j���[�V�����ύX
		void ChangeAnimation(string);

		//���G�t���O
		bool m_MutekiFlg = false;
		//���G����
		float m_MutekiTime = 3.0f;
		//�_�ŗp
		float m_MutekiTenmetuTime = 0;
		//Abe20170526

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

		//Abe20170612
		//�V�[���h
		shared_ptr<EnemyShield> m_Shield;
		//Abe20170612

	public:
		//���� �ʒu(pos)�A�傫��(parscale)�AHP(hp)�A���G����(serchdistance)�A�N�[���^�C��(cooltime)�A�U����(power)�A�q�@���ˊԊu(shotchildinterval)�A���ː�(shotamount)
		ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime,int power, float shotchildinterval,int shotamount);

		void OnCreate() override;
		void OnUpdate() override;

		//���G
		void Search();
		//�U��
		void Attack();
		//Abe20170526
		//���G����
		void Muteki();
		//Abe20170526

		//��ԕύX
		void ToSearch();
		void ToAttack();		
		//Abe20170526
		void ToMuteki();
		//Abe20170526


		//�������_���[�W�󂯂��Ƃ��̊֐�
		//�v���C���[����
		void DamagePlayer();
		//�~�T�C���Ƃ����e�Ƃ�
		void Damage(int power);
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
		//�U��������
		bool m_AttackFlg = false;
		//�U�����Ă�Ώ�
		int m_TargetNum = 0;
		//�ˌ����Ă鎞��
		float m_TackleTime = 3.0f;

		void StageEndCheck();
		Vector2 m_StageSize;

		//Abe20170519
		//��]
		void Rot();
		//Abe20170519

		//�����͈�
		float m_BombDistance;

		//�U������܂ő҂ӂ炮
		bool m_Tackleflg = false;


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

		//�����G�t�F�N�g
		shared_ptr<GameObject> m_Effect;

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

		//�������_���[�W�󂯂��Ƃ��̊֐�
		//�v���C���[����
		void DamagePlayer();

		void TurnVecolity(bool, bool);
		bool GetAttack() { return m_AttackFlg; }
		int GetPower() { return m_Power; }

	};

	//Abe20170508
	//======================�ȉ��q�@�Q=======================
	//************************************
	//	���e�̔����̕���(SS�Ή���)
	//	�����͂���܁[��
	//************************************
	class BombEffect : public GameObject
	{
	private:
		//���
		//int m_State = 0;
		//�A�N�e�B�u�t���O
		bool m_ActiveFlg = false;

		//��������vector�z��
		vector<shared_ptr<MeshResource>> m_SpriteS;

		//������
		int m_SpriteNum = 0;
		//���̔ԍ�
		int m_NowSpriteNum = 0;

		//�v�Z�p����
		float m_time = 0;
		//�摜�؂�ւ��Ԋu
		const float m_IntervalTime = 0.01f;
	public:
		BombEffect(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//�N���A�~�܂��Ă�΍ċN�������B�����͍��W
		void SetPosActive(Vector3);

		//���C���[�ݒ�
		void SetLayer(int num) { SetDrawLayer(num); }
	};

	//************************************
	//	�G�̔��U�G�t�F�N�g
	//	�����Ł[�[�[�[��
	//************************************
	class BakusanEF : public GameObject
	{
	private :
		//��������vector�z��
		vector<shared_ptr<MeshResource>> m_SpriteS;

		//������
		int m_SpriteNum = 0;
		//���̔ԍ�
		int m_NowSpriteNum = 0;
		//�v�Z�p����
		float m_time = 0;
		//�摜�؂�ւ��Ԋu
		float m_IntervalTime = 0.03f;
	public :
		BakusanEF(const shared_ptr<Stage>& StagePtr): GameObject(StagePtr) {}

		void OnCreate() override;
		void OnUpdate() override;

		void SetPosScaActive(Vector3,Vector3);

		void SetLayer(int num) { SetDrawLayer(num); }
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

		//Abe20170515
		//�X�e�[�W�̕�
		Vector2 m_StageSize;

		//�X�e�[�W�̒[�ɍs���������肵�Č�����ς���֐�
		void StageEndCheck();
		//Abe20170515

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

	//Abe20170515
	//************************************
	//	�~�T�C��
	//	�X�e�[�W�̒[�ɍs�������ɓ�����܂�
	//	�����Ă�����Ɉړ�
	//************************************
	class Missile : public GameObject
	{
	private:
		//�ʒu
		Vector3 m_Pos;
		//�傫��
		Vector3 m_Scale;
		//�ړ�����
		Vector3 m_Velocity;
		//�����Ă邩
		bool m_ActiveFlg = false;

		//�����G�t�F�N�g
		shared_ptr<BombEffect> m_Effect;
		//Abe20170517
		//������t���O
		bool m_FallFlg = false;
		//Abe20170517

		//Abe20170515
		//�X�e�[�W�̕�
		Vector2 m_StageSize;

		//�X�e�[�W�̒[�ɍs���������肵�Č�����ς���֐�
		void StageEndCheck();
		//Abe20170515


		//Abe20170519
		//�����̉e
		shared_ptr<GameObject> m_Shadow;
		//Abe20170519

		//Abe20170529
		//���� 0��shot�G�l�~�[�ɂ͓�����Ȃ��A1�œ�����
		int m_Zokusei = 0;
		//Abe20170529


		//�ȉ��p�����[�^
		//�U����
		int m_power = 1;
	public :
		Missile(const shared_ptr<Stage>& StagePtr);

		void OnCreate()override;
		void OnUpdate()override;

		//�~�T�C�����N���B�Ō�̃t���O���I���ɂ���Ɨ�����悤�ɂȂ�
		void SetMissileActive(Vector3 pos, Vector3 scale, Vector3 velocity,bool falltype,int power);

		//�~�T�C������
		void DeleteMissile();

		//�v���C���[�ɍU�������ꍇ
		void ToDamagePleyer();

		int GetPower() { return m_power; DeleteMissile()}

		//�����A�N�Z�T�[
		int GetZokusei() { return m_Zokusei; }
	};
	//Abe20170515

	//Abe20170523IzumiHikitugi
	//************************************
	//	���G�T�[�N��(SS��)
	//	�X�v���C�g�X�^�W�I�ōĐ�
	//************************************
	class SearchCircle : public SS5ssae {
	private :

	public:
		//�\�z�Ɣj��
		SearchCircle(const shared_ptr<Stage>& StagePtr);
		virtual ~SearchCircle() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
	//Abe20170523IzumiHikitugi

	//Abe20170605
	//************************************
	//	���U���Ĕ�Ԃ��
	//************************************
	class BakuSanObj : public GameObject
	{
	private :
		//���x
		Vector3 m_Velocity;
		//�傫��
		Vector3 m_Scale;
		//�ʒu
		Vector3 m_Pos;

		//��](�����_���Ō��߂�)
		Vector3 m_RotPow;
	public :
		BakuSanObj(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {}

		void OnCreate() override;

		void OnUpdate() override;

		//�ʒu�A�傫���A���x�Z�b�g
		void SetPosScaleVelo(Vector3, Vector3, Vector3);
	};
	//************************************
	//	���U���Ĕ�Ԃ�𐶐�������
	//************************************
	class BakuSanSpawn : public GameObject
	{
	private :
	public :
		BakuSanSpawn(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {}

		//�Ƃ肠����
		void OnCreate() {}

		//���� �����o����
		void CreateBakusan(int num , Vector3 pos);
	};
	//Abe20170605

}