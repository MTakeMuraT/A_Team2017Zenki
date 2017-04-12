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
		shared_ptr<Collision_Sphere> m_Collision_Sphere;
		//���������I�u�W�F�N�g�擾
		shared_ptr<GameObject> m_HitObject;
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
		bool FixedPos_b = true;
		Vector3 Now_Pos_Vec3;
		
		//�e�X�g�t���O
		bool Debug_StickDown_b = false;

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
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;
		virtual void OnLastUpdate() override;

		void InputStick();

		//�s���̃X�^�[�g�֐�
		//void EnterMoveBehavior();
		void EnterToAttractBehavior();
		void EnterPinchBehavior();
		void EnterSandwichBehavior();
		//�s���̌p���֐�
		void ExecuteMoveBehavior();
		void ExecuteToAttractBehavior();
		void ExecutePinchBehavior();
		void ExecuteSandwichBehavior();
		//�s���̏I���֐�
		void ExitMoveBehabior();
		void ExitToAttractBehavior();
		void ExitPinchBehavior();
		void ExitSandwichBehavior();

		//A�{�^����������Ă邩�H�i���������X�e�[�g�Ŏg�p�j
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		void FixedPos();


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
		//	class PinchState : public ObjState<Player>;
		//	�p�r:�@����ł���X�e�[�g
		//--------------------------------------------------------------------------------------
		class PinchState : public ObjState<Player>
		{
			PinchState() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<PinchState> Instance();
			//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
			virtual void Enter(const shared_ptr<Player>& Obj)override;
			//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
			virtual void Execute(const shared_ptr<Player>& Obj)override;
			//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
			virtual void Exit(const shared_ptr<Player>& Obj)override;
		};
		//--------------------------------------------------------------------------------------
		//	class SandwichState : public ObjState<Player>;
		//	�p�r:�@����ňړ��X�e�[�g
		//--------------------------------------------------------------------------------------
		class SandwichState : public ObjState<Player>
		{
			SandwichState() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<SandwichState> Instance();
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
			bool FixedPos_b = true;
			Vector3 Now_Pos_Vec3;
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
			virtual void Player_Second::OnCollision(vector<shared_ptr<GameObject>>& OtherVec);
			void InputStick();

			//�s���̃X�^�[�g�֐�
			//void EnterMoveBehavior();
			void EnterToAttractBehavior();
			void EnterPinchBehavior();
			void EnterSandwichBehavior();
			//�s���̌p���֐�
			void ExecuteMoveBehavior();
			void ExecuteToAttractBehavior();
			void ExecutePinchBehavior();
			void ExecuteSandwichBehavior();
			//�s���̏I���֐�
			void ExitMoveBehabior();
			void ExitToAttractBehavior();
			void ExitPinchBehavior();
			void ExitSandwichBehavior();

			//A�{�^����������Ă邩�H�i���������X�e�[�g�Ŏg�p�j
			bool KeepPushed_A = true;

			Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
			void FixedPos();

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
		//--------------------------------------------------------------------------------------
		//	class PinchState_Second  : public ObjState<Player>;
		//	�p�r:�@����ł���X�e�[�g
		//--------------------------------------------------------------------------------------
		class PinchState_Second : public ObjState<Player_Second>
		{
			PinchState_Second() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<PinchState_Second > Instance();
			//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
		//--------------------------------------------------------------------------------------
		//	class SandwichState_Second : public ObjState<Player_Second>;
		//	�p�r:�@����ňړ��X�e�[�g
		//--------------------------------------------------------------------------------------
		class SandwichState_Second : public ObjState<Player_Second>
		{
			SandwichState_Second() {}
		public:
			//�X�e�[�g�̃C���X�^���X�擾
			static shared_ptr<SandwichState_Second> Instance();
			//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
		
}
//end basecross

