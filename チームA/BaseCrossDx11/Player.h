/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//Aボタンで動作するアクション
	enum class PlayerAction {
		Jump
	};
	
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	private:
		//文字列の表示
		void DrawStrings();
		//入力ハンドラー
	//	InputHandler<Player> m_InputHandler;
		//プレイヤーのAボタンによる行動
		PlayerAction m_PlayerAction;
		//階層化ステートマシーン
		unique_ptr<LayeredStateMachine<Player>>  m_StatePlayerMachine;
		Vector3 m_StartPos;
	public:
		
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player() {}
		//アクセサ ステートマシーン
		unique_ptr<LayeredStateMachine<Player>>& GetStateMachine() {
			return m_StatePlayerMachine;
		}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//後更新
		virtual void OnUpdate2() override;
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;

		//ステート変更
		//void ChangeStateDefault();
		void ChangeStateJump();
	
		
	};


	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	class PlayerDefaultState : public ObjState<Player>
	{
		PlayerDefaultState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(PlayerDefaultState)
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	///	ジャンプステート
	//--------------------------------------------------------------------------------------
	class PlayerJumpState : public ObjState<Player>
	{
		PlayerJumpState() {}
	public:
		//ステートのインスタンス取得
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
		//文字列の表示
		void DrawStrings();
		wstring DebugCharacter;
	public:
		//構築と破棄
		Player_Secnd(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player_Secnd() {}

		
		//階層化ステートマシーン
		unique_ptr<LayeredStateMachine<Player_Secnd>>  m_State_PlayerSecnd_Machine;
		//アクセサ ステートマシーン
		unique_ptr<LayeredStateMachine<Player_Secnd>>& GetStatePlayerSecndMachine() {
			return m_State_PlayerSecnd_Machine;
		}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		wstring GetStrings();
	};
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	class PlayerSecndDefaultState : public ObjState<Player_Secnd>
	{
		PlayerSecndDefaultState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(PlayerSecndDefaultState)
		virtual void Enter(const shared_ptr<Player_Secnd>& Obj)override;
		virtual void Execute(const shared_ptr<Player_Secnd>& Obj)override;
		virtual void Exit(const shared_ptr<Player_Secnd>& Obj)override;
	};






}
//end basecross

