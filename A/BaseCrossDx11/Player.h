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

		float StanTime_F = 0.0f;
		float TotalEnemyStanTime = 0.0f;
		bool m_StanEnemy_b = false;
		bool m_sandwich = false;
		bool m_sandwichMove = false;


		//�e�X�g�t���O
		bool Debug_StickDown_b = false;
		bool Debug_flg = true;
		float Debug_Rot_F = 0.0f;
		Vector3 Dubug_Vec3;
		Vector3 DeBug2_Vec3;
		Vector3 DeBug3_Vec3;
		float DebugDirection = 0.0f;
		//
		void Rot();

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


		//�s���̃X�^�[�g�֐�
		void EnterMoveBehavior();
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

		//��]
		void InputRotation();
		Vector3 def;
		Vector3 CentrPos;
		float angle;
		int angle_int;
		float RotSpeedSecond = 60.0f;
		Vector3 MovePosVec3;
		//
		void Rot();

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

	//--------------------------------------------------------------------------------------
	///	NumberSprite �X�v���C�g
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject {
		Vector2 m_StartScale;
		Vector3 m_StartPos;
		float m_RightNum;
		float m_leftNum;
		float m_Score;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;

		//
		float VertexNum = 0.0f;
	public:
		
		NumberSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const float& RightNum,const float& leftNum,const Vector2& StartScale, const Vector3& StartPos);
		
		virtual ~NumberSprite() {}
		
		void SetScore(float f) {
			m_Score = f;
		}
		
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};



	//HP�֌W
	//--------------------------------------------------------------------------------------
	///	HP �X�v���C�g
	//--------------------------------------------------------------------------------------
	class HP : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;

	public:

		HP(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);

		virtual ~HP();

		virtual void OnCreate() override;

		virtual void OnUpdate()override {}
	};
	//--------------------------------------------------------------------------------------
	///	HPBackGround �X�v���C�g
	//--------------------------------------------------------------------------------------
	class HPBackGround : public GameObject {
			Vector2 m_StartScale;
			Vector2 m_StartPos;

		public:
		
			HPBackGround(const shared_ptr<Stage>& StagePtr,
				const Vector2& StartScale, const Vector2& StartPos);
			
			virtual ~HPBackGround();
			
			virtual void OnCreate() override;
		
			virtual void OnUpdate()override {}
		};
}
//end basecross

