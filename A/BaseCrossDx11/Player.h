
/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
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
		//コンストラクタメンバ
		Vector3 m_StartPos;
		wstring m_Player_Str;
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

		float VelocityPower = 5.0f;
		float AddVec = 10.0f;
		bool FixedPos_b = true;
		Vector3 Now_Pos_Vec3;

		float StanTime_F = 0.0f;
		float TotalEnemyStanTime = 0.0f;
		bool m_StanEnemy_b = false;
		bool m_sandwich = false;
		bool m_sandwichMove = false;

		//向きを得る
		Vector3 Direction_Vec3 = Vector3(0, 0, 0);
		//LeaveStateで使用
		Vector3 SavePos_Vec3 = Vector3(0, 0, 0);


		//テストフラグ
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
		//継続式の
		//引き合うステートで使用
		Vector3 Player2Pos = Vector3(0, 0, 0);
		//攻撃前ステート

	public:

		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR);
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
		//スティック移動
		void InputStick();
		//回転
		void InputRotation();
		Vector3 def;
		Vector3 CentrPos;
		float angle;
		int angle_int;
		float RotSpeedSecond = 60.0f;
		Vector3 MovePosVec3;

		//攻撃前ステートで使用
		//限界値
		Vector3 Limit = Vector3(0, 0, 0);
		Vector3 m_Direction = Vector3(0, 0, 0);

		//行動のスタート関数
		void EnterMoveBehavior();//移動ステート
		void EnterBeforeAttractBehavior();//攻撃前
		void EnterToAttractBehavior();//引き付けるステート
		void EnterLeaveBehavior();//離れるステート
								  //行動の継続関数
		void ExecuteMoveBehavior();
		void ExecuteBeforeAttractBehavior();//攻撃前
		void ExecuteToAttractBehavior();
		void ExecuteLeaveBehavior();//離れる
									//行動の終了関数
		void ExitMoveBehabior();
		void ExitBeforeAttractBehavior();//攻撃前
		void ExitToAttractBehavior();
		void ExitLeaveBehavior();//離れる

								 //自分はPlayerなのか？
		bool MyPlayerL();
		Vector3 Partner_Pos();


		//向きだけを取る
		Vector3 Direction(Vector3 MyPos, Vector3 PartnerPos);
		//Aボタンが押されてるか？（引き合うステートで使用）
		bool KeepPushed_A = true;

		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		void FixedPos();

		//アクセサ
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
	//	class LeaveState : public ObjState<Player>;
	//	用途:　離れるステート
	//--------------------------------------------------------------------------------------
	class LeaveState : public ObjState<Player>
	{
		LeaveState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<LeaveState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class BeforeAttractState : public ObjState<Player>;
	//	用途:　攻撃準備ステート
	//--------------------------------------------------------------------------------------
	class BeforeAttractState : public ObjState<Player>
	{
		BeforeAttractState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<BeforeAttractState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


	//センターの規定ボックス
	//--------------------------------------------------------------------------------------
	///	プレイヤーセンター
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
	//	用途: スカイボックスの背景
	//--------------------------------------------------------------------------------------
	class SkySphere : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
	public:
		//構築と破棄
		SkySphere(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position
		);
		virtual ~SkySphere();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

}
//end basecross

