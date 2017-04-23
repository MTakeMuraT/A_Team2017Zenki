
/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	private:
		//�K�w���X�e�[�g�}�V�[��
		shared_ptr<StateMachine<Player>>  m_StatePlayerMachine;
		shared_ptr<Collision_Sphere> m_Collision_Sphere;
		//���������I�u�W�F�N�g�擾
		shared_ptr<GameObject> m_HitObject;
		//�R���X�g���N�^�����o
		Vector3 m_StartPos;
		wstring m_Player_Str;
		//�ړ��X�s�[�h
		float Speed_F = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0, 0, 0);
		//�����̈ʒu���擾
		Vector3 m_PlayerPos_Vec3 = Vector3(0, 0, 0);

		//�����̈ʒu
		Vector3 My_Pos_Vec3 = Vector3(0, 0, 0);
		Vector3 New_Vec = Vector3(0, 0, 0);
		//����̈ʒu
		Vector3 Partner_Pos_Vec3 = Vector3(0, 0, 0);

		float VelocityPower = 5.0f;
		float AddVec = 10.0f;
		bool FixedPos_b = true;
		Vector3 Now_Pos_Vec3;

		float StanTime_F = 0.0f;
		float TotalEnemyStanTime = 0.0f;
		bool m_StanEnemy_b = false;
		bool m_sandwich = false;
		bool m_sandwichMove = false;

		//�����𓾂�
		Vector3 Direction_Vec3 = Vector3(0, 0, 0);
		//LeaveState�Ŏg�p
		Vector3 SavePos_Vec3 = Vector3(0, 0, 0);


		//�e�X�g�t���O
		bool Debug_StickDown_b = false;
		bool Debug_flg = true;
		float Debug_Rot_F = 0.0f;
		Vector3 Dubug_Vec3;
		Vector3 DeBug2_Vec3;
		Vector3 DeBug3_Vec3;
		float DebugDirection = 0.0f;
		bool Debug_R_flg = false;
		float DubugSpeed_F = 100.0f;
		//
		void Rot();
		//�p������
		//���������X�e�[�g�Ŏg�p
		Vector3 Player2Pos = Vector3(0, 0, 0);
		//�U���O�X�e�[�g

	public:

		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR);
		virtual ~Player() {}
		//�A�N�Z�T �X�e�[�g�}�V�[��
		shared_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StatePlayerMachine;
		}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;
		virtual void OnLastUpdate() override;
		//�X�e�B�b�N�ړ�
		void InputStick();
		//��]
		void InputRotation();
		Vector3 def;
		Vector3 CentrPos;
		float angle;
		int angle_int;
		float RotSpeedSecond = 60.0f;
		Vector3 MovePosVec3;

		//�U���O�X�e�[�g�Ŏg�p
		//���E�l
		Vector3 Limit = Vector3(0, 0, 0);
		Vector3 m_Direction = Vector3(0, 0, 0);

		//�s���̃X�^�[�g�֐�
		void EnterMoveBehavior();//�ړ��X�e�[�g
		void EnterBeforeAttractBehavior();//�U���O
		void EnterToAttractBehavior();//�����t����X�e�[�g
		void EnterLeaveBehavior();//�����X�e�[�g
								  //�s���̌p���֐�
		void ExecuteMoveBehavior();
		void ExecuteBeforeAttractBehavior();//�U���O
		void ExecuteToAttractBehavior();
		void ExecuteLeaveBehavior();//�����
									//�s���̏I���֐�
		void ExitMoveBehabior();
		void ExitBeforeAttractBehavior();//�U���O
		void ExitToAttractBehavior();
		void ExitLeaveBehavior();//�����

								 //������Player�Ȃ̂��H
		bool MyPlayerL();
		Vector3 Partner_Pos();


		//�������������
		Vector3 Direction(Vector3 MyPos, Vector3 PartnerPos);
		//A�{�^����������Ă邩�H�i���������X�e�[�g�Ŏg�p�j
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		void FixedPos();

		//�A�N�Z�T
		bool GetStanEnemy() {
			return m_StanEnemy_b;
		}
		void SetStanEnemy(bool Hitflg) {
			m_StanEnemy_b = Hitflg;
		}

		bool Getsandwich() {
			return m_sandwich;
		}
		bool GetsandwichMove() {
			return m_sandwichMove;
		}



	};

	//--------------------------------------------------------------------------------------
	//	class MoveState : public ObjState<Player>;
	//	�p�r:�@�ړ�
	//--------------------------------------------------------------------------------------
	class MoveState : public ObjState<Player>
	{
		MoveState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<MoveState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class ToAttractState : public ObjState<Player>;
	//	�p�r:�@�����񂹍���
	//--------------------------------------------------------------------------------------
	class ToAttractState : public ObjState<Player>
	{
		ToAttractState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<ToAttractState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class LeaveState : public ObjState<Player>;
	//	�p�r:�@�����X�e�[�g
	//--------------------------------------------------------------------------------------
	class LeaveState : public ObjState<Player>
	{
		LeaveState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<LeaveState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class BeforeAttractState : public ObjState<Player>;
	//	�p�r:�@�U�������X�e�[�g
	//--------------------------------------------------------------------------------------
	class BeforeAttractState : public ObjState<Player>
	{
		BeforeAttractState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<BeforeAttractState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


	//�Z���^�[�̋K��{�b�N�X
	//--------------------------------------------------------------------------------------
	///	�v���C���[�Z���^�[
	//--------------------------------------------------------------------------------------
	class PlayerCenter : public GameObject {
	public:

		PlayerCenter(const shared_ptr<Stage>& StagePtr);
		virtual ~PlayerCenter() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	�p�r: �X�J�C�{�b�N�X�̔w�i
	//--------------------------------------------------------------------------------------
	class SkySphere : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
	public:
		//�\�z�Ɣj��
		SkySphere(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position
		);
		virtual ~SkySphere();
		//������
		virtual void OnCreate() override;
		//����
	};

}
//end basecross

