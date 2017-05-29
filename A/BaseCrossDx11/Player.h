
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
		//�R���X�g���N�^�����o
		Vector3 m_StartPos;
		wstring m_Player_Str;
		shared_ptr<BombEffect> m_Effect;
		int m_ChangeAnimaNumber = 0;
		//�A�j���[�V������ύX�ł��邩�̔��f�p�t���O
		bool ChangeAnimaFlg = false;

		
	public:

		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR);
		virtual ~Player() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		
		bool UpdateAnyAnimation();
		void PlayerDieEffect();
		//�A�j���[�V�����֐��Q
		void ChangeAnima();
		void AnimationWait();
		void AnimationRotL();
		void AnimationRotR();
		void AnimationDamage();
		///////////////////////
		//�A�j���[�V�����̕ύX�Z�b�g�֐�
		void SetChangeAnima(int Num) {
			m_ChangeAnimaNumber = Num;
		}
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
	///	�v���C���[�}�l�[�W���[
	//--------------------------------------------------------------------------------------
	class PlayerManager : public GameObject {
	private:
		//����Pos�߂�X�e�[�gPlayer���߂�ڈ�
		Vector3 PlayerL_Initial_Vec3 = Vector3(0, 0, 0);
		Vector3 PLayerR_Initial_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerL_Distance_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Distance_Vec3 = Vector3(0, 0, 0);
		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<DebugTxt> m_Debugtxt;
		Vector3 m_DebugL = Vector3(0, 0, 0);
		Vector3 m_DebugR = Vector3(0, 0, 0);
		//�ʂ̃X�s�[�h
		float Speed_F = 0.0f;
		float AddSpeed = 0.0f;//�������Ɏg�p
		shared_ptr<StateMachine<PlayerManager>> m_StateManagerMachine;
		//InputStick�֐����̎g�p�ϐ�/////
		//�ړ��X�s�[�h
		float Move_Speed = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 StickVec = Vector3(0.0f, 0.0f, 0.0f);
		/////////////////////////////////
		//Direction�֐����̎g�p�ϐ�/////
		Vector3 Direction_Vec3 = Vector3(0, 0, 0);
		/////////////////////////////////

		//�X�e�[�g�ł̕ϐ�
		Vector3 PlayerL_SavePos_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_SavePos_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerL_Direction_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Direction_Vec3 = Vector3(0, 0, 0);
		//�߂�X�e�[�g�ł̕ϐ�
		Vector3 PlayerL_Velocity_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Velocity_Vec3 = Vector3(0, 0, 0);

		//�v���C���[���m�̋���
		Vector3 Distance = Vector3(0, 0, 0);
		//��]�t���O
		bool m_RotateFlg = false;
		//���[�e�[�V�����\�t���O(����Ă��鎞
		bool m_LeaveRotateFlg = false;
		//�X�e�[�W�̃X�P�[��
		Vector2 m_StageSize;
		//�_���[�W�p
		bool m_DamePower = false;
		float m_LimitTime = 0;

	public:

		PlayerManager(const shared_ptr<Stage>& StagePtr);
		virtual ~PlayerManager() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnLastUpdate() override;
		void InputStick();//�R���g���[���ł̈ړ�
		void InputRotation();//�v���C���[�̉�]
		void PlayerAngle();//�v���C���[�̃��f���̌���
		void InitializationVelocity();//Velovitu�̏�����

		Vector3 Direction(Vector3 MyPos, Vector3 PartnerPos);
		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		//�R���W�����̃A�N�e�B�u
		void SetActiveCollision(bool flg);

		//�A�N�Z�T �X�e�[�g�}�V�[��
		shared_ptr<StateMachine<PlayerManager>>& GetStateMachine_Manager() {
			return m_StateManagerMachine;
		}
		//�X�e�[�g�`�F���W�֐�
		void StateChangeDoingInterpose();
		void StateChangeDie();
		//�s���̃X�^�[�g�֐�
		void EnterGamePrepare();//�Q�[���O�̏����X�e�[�g
		void EnterMoveBehavior();//�ړ��X�e�[�g 
		void EnterLeaveBehavior();//�����X�e�[�g
		void EnterToAttractBehavior();//�����t����X�e�[�g
		void EnterToAttractFailureBehavior();//�U�����s
		void EnterReturnBehavior();//�߂�
		void EneterDoingInterpose();//����ł���Ƃ�
		void EneterDieBehavior();

									//�s���̌p���֐�			
		void ExecuteGamePrepare();//�Q�[���O�̏���
		void ExecuteMoveBehavior();
		void ExecuteLeaveBehavior();//�����
		void ExecuteToAttractBehavior();//�����t����
		void ExecuteToAttractFailureBehavior();//�U�����s
		void ExecuteReturnBehavior();//�߂�
		void ExecuteDoingInterpose();//����ł���Ƃ�
		void ExecuteDieBehavior();

									 //�s���̏I���֐�		
		void ExitGamePrepare();//�Q�[���O�̏���
		void ExitMoveBehabior();
		void ExitLeaveBehavior();//�����
		void ExitToAttractBehavior();//�����t����
		void ExitToAttractFailureBehavior();//�U�����s
		void ExitReturnBehavior();//�߂�
		void ExitDoingInterpose();//����ł���Ƃ�
		void ExitDieBehavior();

		//�G���A�O�ւ̐i�s��h���֐�
		void StintArea();

		bool GetRotateFlg() {
			return m_RotateFlg;
		}
		void SetRotateFlg(bool flg) {
			m_RotateFlg = flg;
		}
		

	};
	//--------------------------------------------------------------------------------------
	//	class GamePrepareState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@�Q�[������
	//--------------------------------------------------------------------------------------
	class GamePrepareState_Manager : public ObjState<PlayerManager>
	{
		GamePrepareState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<GamePrepareState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class MoveState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@�ړ�
	//--------------------------------------------------------------------------------------
	class MoveState_Manager : public ObjState<PlayerManager>
	{
		MoveState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<MoveState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ToAttractState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@��������
	//--------------------------------------------------------------------------------------
	class ToAttractState_Manager : public ObjState<PlayerManager>
	{
		ToAttractState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<ToAttractState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ToAttractAttract_F_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@�U�����s
	//--------------------------------------------------------------------------------------
	class ToAttractAttract_F_Manager : public ObjState<PlayerManager>
	{
		ToAttractAttract_F_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<ToAttractAttract_F_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class LeaveState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@�����
	//--------------------------------------------------------------------------------------
	class LeaveState_Manager : public ObjState<PlayerManager>
	{
		LeaveState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<LeaveState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ReturnState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@�߂�X�e�[�g
	//--------------------------------------------------------------------------------------
	class ReturnState_Manager : public ObjState<PlayerManager>
	{
		ReturnState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<ReturnState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DoingInterposeState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@����ł���Ƃ��̃X�e�[�g
	//--------------------------------------------------------------------------------------
	class DoingInterposeState_Manager : public ObjState<PlayerManager>
	{
		DoingInterposeState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<DoingInterposeState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DieState_Manager : public ObjState<PlayerManager>;
	//	�p�r:�@���񂾃X�e�[�g
	//--------------------------------------------------------------------------------------
	class DieState_Manager : public ObjState<PlayerManager>
	{
		DieState_Manager() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<DieState_Manager> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
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
	//	class PlayerHP : public GameObject;
	//	�p�r: �v���C���[HP�̏���
	//--------------------------------------------------------------------------------------
	class PlayerHP : public GameObject {
	private:
		//���G�p
		bool m_invincible_b = false;
		float InvinciblecCunt = 0.0f;
		float InvinciblecLimit = 3.0f;
		//�G�Ƃ̐ڐG
		bool m_Hit_b = false;
		//�_���[�W
		int m_Damage_int = 0;
		public:
		//�\�z�Ɣj��
		PlayerHP(const shared_ptr<Stage>& StagePtr
		);
		virtual ~PlayerHP();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		bool GetInvincible() {
			return m_invincible_b;
		}
		void SetInvincible(bool Hit_flg) {
			m_invincible_b = Hit_flg;
		}
		bool GetHit() {
			return m_Hit_b;
		}
		void SetHit(bool Hit) {
			m_Hit_b = Hit;
		}
		int  GetDamage_int() {
			return m_Damage_int;
		}
		void SetDamage_int(int Damage) {
			m_Damage_int = Damage;
		}
	};
	
}
//end basecross
