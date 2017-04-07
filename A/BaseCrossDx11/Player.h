/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	private:
		//階層化ステートマシーン
		shared_ptr<StateMachine<Player>>  m_StatePlayerMachine;
		Vector3 m_StartPos;
		//移動スピード
		float Speed_F = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0, 0, 0);
		//自分の位置を取得
		Vector3 m_PlayerPos_Vec3 = Vector3(0, 0, 0);
		
		
		//自分の位置
		Vector3 My_Pos_Vec3 = Vector3(0, 0, 0);
		Vector3 New_Vec = Vector3(0, 0, 0);
		//相手の位置
		Vector3 Partner_Pos_Vec3 = Vector3(0, 0, 0);
		

		float VelocityPower = 1.0f;
		float AddVec = 10.0f;
	public:

		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
		virtual ~Player() {}
		//アクセサ ステートマシーン
		shared_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StatePlayerMachine;
		}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnLastUpdate() override;

		void InputStick();

		//行動のスタート関数
		//void EnterMoveBehavior();
		void EnterToAttractBehavior();
		//行動の継続関数
		void ExcuteMoveBehavior();
		void ExcuteToAttractBehavior();
		//行動の終了関数
		void ExitMoveBehabior();
		void ExitToAttractBehavior();

		//Aボタンが押されてるか？（引き合うステートで使用）
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);

		
	};
	
	//--------------------------------------------------------------------------------------
	//	class MoveState : public ObjState<Player>;
	//	用途:　移動
	//--------------------------------------------------------------------------------------
	class MoveState : public ObjState<Player>
	{
		MoveState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<MoveState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	
		//--------------------------------------------------------------------------------------
		//	class ToAttractState : public ObjState<Player>;
		//	用途:　引き寄せ合う
		//--------------------------------------------------------------------------------------
		class ToAttractState : public ObjState<Player>
	{
			ToAttractState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<ToAttractState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

		////////////////////////////もう一体のプレイヤー/////////////////////////////////////////////////////////////////////////////

		//--------------------------------------------------------------------------------------
		///	プレイヤー2
		//--------------------------------------------------------------------------------------
		class Player_Second : public GameObject {

		private:
			//階層化ステートマシーン
			shared_ptr<StateMachine<Player_Second>>  m_StatePlayer_SecondMachine;
			Vector3 m_StartPos;
			//移動スピード
			float Speed_F = 0.0f;
			Vector3 Vec_Vec3 = Vector3(0, 0, 0);
			//自分の位置を取得
			Vector3 m_PlayerPos_Vec3 = Vector3(0, 0, 0);


			//自分の位置
			Vector3 My_Pos_Vec3 = Vector3(0, 0, 0);
			Vector3 New_Vec = Vector3(0, 0, 0);
			//相手の位置
			Vector3 Partner_Pos_Vec3 = Vector3(0, 0, 0);


			float VelocityPower = 1.0f;
			float AddVec = 2.0f;
		public:

			//構築と破棄
			Player_Second(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos);
			virtual ~Player_Second() {}
			//アクセサ ステートマシーン
			shared_ptr<StateMachine<Player_Second>>& GetStateSecondMachine() {
				return m_StatePlayer_SecondMachine;
			}
			//初期化
			virtual void OnCreate() override;
			virtual void OnUpdate() override;

			void InputStick();

			//行動のスタート関数
			//void EnterMoveBehavior();
			void EnterToAttractBehavior();
			//行動の継続関数
			void ExcuteMoveBehavior();
			void ExcuteToAttractBehavior();
			//行動の終了関数
			void ExitMoveBehabior();
			void ExitToAttractBehavior();

			//Aボタンが押されてるか？（引き合うステートで使用）
			bool KeepPushed_A = true;

			Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);


		};

		//--------------------------------------------------------------------------------------
		//	class MoveState_Second : public ObjState<Player_Second>;
		//	用途:　移動
		//--------------------------------------------------------------------------------------
		class MoveState_Second : public ObjState<Player_Second>
		{
			MoveState_Second() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<MoveState_Second> Instance();
			//ステートに入ったときに呼ばれる関数
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//ステート実行中に毎ターン呼ばれる関数
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//ステートにから抜けるときに呼ばれる関数
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};

		//--------------------------------------------------------------------------------------
		//	class ToAttractState_Second : public ObjState<Player_Second>;
		//	用途:　引き寄せ合う
		//--------------------------------------------------------------------------------------
		class ToAttractState_Second : public ObjState<Player_Second>
		{
			ToAttractState_Second() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<ToAttractState_Second> Instance();
			//ステートに入ったときに呼ばれる関数
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//ステート実行中に毎ターン呼ばれる関数
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//ステートにから抜けるときに呼ばれる関数
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
}
//end basecross

