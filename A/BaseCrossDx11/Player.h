/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	private:
		//�K�w���X�e�[�g�}�V�[��
		shared_ptr<StateMachine<Player>>  m_StatePlayerMachine;
		Vector3 m_StartPos;
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
		

		float VelocityPower = 1.0f;
		float AddVec = 10.0f;
	public:

		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player() {}
		//�A�N�Z�T �X�e�[�g�}�V�[��
		shared_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StatePlayerMachine;
		}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnLastUpdate() override;

		void InputStick();

		//�s���̃X�^�[�g�֐�
		//void EnterMoveBehavior();
		void EnterToAttractBehavior();
		//�s���̌p���֐�
		void ExcuteMoveBehavior();
		void ExcuteToAttractBehavior();
		//�s���̏I���֐�
		void ExitMoveBehabior();
		void ExitToAttractBehavior();

		//A�{�^����������Ă邩�H�i���������X�e�[�g�Ŏg�p�j
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);

		
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

		////////////////////////////������̂̃v���C���[/////////////////////////////////////////////////////////////////////////////

		//--------------------------------------------------------------------------------------
		///	�v���C���[2
		//--------------------------------------------------------------------------------------
		class Player_Second : public GameObject {

		private:
			//�K�w���X�e�[�g�}�V�[��
			shared_ptr<StateMachine<Player_Second>>  m_StatePlayer_SecondMachine;
			Vector3 m_StartPos;
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


			float VelocityPower = 1.0f;
			float AddVec = 2.0f;
		public:

			//�\�z�Ɣj��
			Player_Second(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
			virtual ~Player_Second() {}
			//�A�N�Z�T �X�e�[�g�}�V�[��
			shared_ptr<StateMachine<Player_Second>>& GetStateSecondMachine() {
				return m_StatePlayer_SecondMachine;
			}
			//������
			virtual void OnCreate() override;
			virtual void OnUpdate() override;

			void InputStick();

			//�s���̃X�^�[�g�֐�
			//void EnterMoveBehavior();
			void EnterToAttractBehavior();
			//�s���̌p���֐�
			void ExcuteMoveBehavior();
			void ExcuteToAttractBehavior();
			//�s���̏I���֐�
			void ExitMoveBehabior();
			void ExitToAttractBehavior();

			//A�{�^����������Ă邩�H�i���������X�e�[�g�Ŏg�p�j
			bool KeepPushed_A = true;

			Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);


		};

		//--------------------------------------------------------------------------------------
		//	class MoveState_Second : public ObjState<Player_Second>;
		//	�p�r:�@�ړ�
		//--------------------------------------------------------------------------------------
		class MoveState_Second : public ObjState<Player_Second>
		{
			MoveState_Second() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<MoveState_Second> Instance();
			//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};

		//--------------------------------------------------------------------------------------
		//	class ToAttractState_Second : public ObjState<Player_Second>;
		//	�p�r:�@�����񂹍���
		//--------------------------------------------------------------------------------------
		class ToAttractState_Second : public ObjState<Player_Second>
		{
			ToAttractState_Second() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<ToAttractState_Second> Instance();
			//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
}
//end basecross

