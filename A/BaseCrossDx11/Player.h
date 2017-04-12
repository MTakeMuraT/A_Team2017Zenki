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
		shared_ptr<Collision_Sphere> m_Collision_Sphere;
		//当たったオブジェクト取得
		shared_ptr<GameObject> m_HitObject;
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
		bool FixedPos_b = true;
		Vector3 Now_Pos_Vec3;
		
		//テストフラグ
		bool Debug_StickDown_b = false;

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
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;
		virtual void OnLastUpdate() override;

		void InputStick();

		//行動のスタート関数
		//void EnterMoveBehavior();
		void EnterToAttractBehavior();
		void EnterPinchBehavior();
		void EnterSandwichBehavior();
		//行動の継続関数
		void ExecuteMoveBehavior();
		void ExecuteToAttractBehavior();
		void ExecutePinchBehavior();
		void ExecuteSandwichBehavior();
		//行動の終了関数
		void ExitMoveBehabior();
		void ExitToAttractBehavior();
		void ExitPinchBehavior();
		void ExitSandwichBehavior();

		//Aボタンが押されてるか？（引き合うステートで使用）
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		void FixedPos();


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
		//--------------------------------------------------------------------------------------
		//	class PinchState : public ObjState<Player>;
		//	用途:　挟んでいるステート
		//--------------------------------------------------------------------------------------
		class PinchState : public ObjState<Player>
		{
			PinchState() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<PinchState> Instance();
			//ステートに入ったときに呼ばれる関数
			virtual void Enter(const shared_ptr<Player>& Obj)override;
			//ステート実行中に毎ターン呼ばれる関数
			virtual void Execute(const shared_ptr<Player>& Obj)override;
			//ステートにから抜けるときに呼ばれる関数
			virtual void Exit(const shared_ptr<Player>& Obj)override;
		};
		//--------------------------------------------------------------------------------------
		//	class SandwichState : public ObjState<Player>;
		//	用途:　挟んで移動ステート
		//--------------------------------------------------------------------------------------
		class SandwichState : public ObjState<Player>
		{
			SandwichState() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<SandwichState> Instance();
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
			bool FixedPos_b = true;
			Vector3 Now_Pos_Vec3;
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
			virtual void Player_Second::OnCollision(vector<shared_ptr<GameObject>>& OtherVec);
			void InputStick();

			//行動のスタート関数
			//void EnterMoveBehavior();
			void EnterToAttractBehavior();
			void EnterPinchBehavior();
			void EnterSandwichBehavior();
			//行動の継続関数
			void ExecuteMoveBehavior();
			void ExecuteToAttractBehavior();
			void ExecutePinchBehavior();
			void ExecuteSandwichBehavior();
			//行動の終了関数
			void ExitMoveBehabior();
			void ExitToAttractBehavior();
			void ExitPinchBehavior();
			void ExitSandwichBehavior();

			//Aボタンが押されてるか？（引き合うステートで使用）
			bool KeepPushed_A = true;

			Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
			void FixedPos();

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
		//--------------------------------------------------------------------------------------
		//	class PinchState_Second  : public ObjState<Player>;
		//	用途:　挟んでいるステート
		//--------------------------------------------------------------------------------------
		class PinchState_Second : public ObjState<Player_Second>
		{
			PinchState_Second() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<PinchState_Second > Instance();
			//ステートに入ったときに呼ばれる関数
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//ステート実行中に毎ターン呼ばれる関数
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//ステートにから抜けるときに呼ばれる関数
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
		//--------------------------------------------------------------------------------------
		//	class SandwichState_Second : public ObjState<Player_Second>;
		//	用途:　挟んで移動ステート
		//--------------------------------------------------------------------------------------
		class SandwichState_Second : public ObjState<Player_Second>
		{
			SandwichState_Second() {}
		public:
			//ステートのインスタンス取得
			static shared_ptr<SandwichState_Second> Instance();
			//ステートに入ったときに呼ばれる関数
			virtual void Enter(const shared_ptr<Player_Second>& Obj)override;
			//ステート実行中に毎ターン呼ばれる関数
			virtual void Execute(const shared_ptr<Player_Second>& Obj)override;
			//ステートにから抜けるときに呼ばれる関数
			virtual void Exit(const shared_ptr<Player_Second>& Obj)override;
		};
		
}
//end basecross

