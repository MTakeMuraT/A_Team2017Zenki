/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//A�{�^���œ��삷��A�N�V����
	enum class PlayerAction {
		Jump
	};
	
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	private:
		//������̕\��
		void DrawStrings();
		//���̓n���h���[
	//	InputHandler<Player> m_InputHandler;
		//�v���C���[��A�{�^���ɂ��s��
		PlayerAction m_PlayerAction;
		//�K�w���X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Player>>  m_StatePlayerMachine;
		Vector3 m_StartPos;
	public:
		
		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player() {}
		//�A�N�Z�T �X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Player>>& GetStateMachine() {
			return m_StatePlayerMachine;
		}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//��X�V
		virtual void OnUpdate2() override;
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;

		//�X�e�[�g�ύX
		//void ChangeStateDefault();
		void ChangeStateJump();
	
		
	};


	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerDefaultState : public ObjState<Player>
	{
		PlayerDefaultState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerDefaultState)
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	///	�W�����v�X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerJumpState : public ObjState<Player>
	{
		PlayerJumpState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerJumpState)
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


	//////////////////////////////////////////////////////////////
    //Player2
	//////////////////////////////////////////////////////////////
	class Player_Secnd : public GameObject {
		Vector3 m_StartPos;
		//������̕\��
		void DrawStrings();
		wstring DebugCharacter;
	public:
		//�\�z�Ɣj��
		Player_Secnd(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player_Secnd() {}

		
		//�K�w���X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Player_Secnd>>  m_State_PlayerSecnd_Machine;
		//�A�N�Z�T �X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Player_Secnd>>& GetStatePlayerSecndMachine() {
			return m_State_PlayerSecnd_Machine;
		}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		wstring GetStrings();
	};
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerSecndDefaultState : public ObjState<Player_Secnd>
	{
		PlayerSecndDefaultState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerSecndDefaultState)
		virtual void Enter(const shared_ptr<Player_Secnd>& Obj)override;
		virtual void Execute(const shared_ptr<Player_Secnd>& Obj)override;
		virtual void Exit(const shared_ptr<Player_Secnd>& Obj)override;
	};






}
//end basecross

