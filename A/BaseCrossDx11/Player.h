
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
		//コンストラクタメンバ
		Vector3 m_StartPos;
		wstring m_Player_Str;
		shared_ptr<BombEffect> m_Effect;
		int m_ChangeAnimaNumber = 0;
		//アニメーションを変更できるかの判断用フラグ
		bool ChangeAnimaFlg = false;

		
	public:

		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR);
		virtual ~Player() {}
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		
		bool UpdateAnyAnimation();
		void PlayerDieEffect();
		//アニメーション関数群
		void ChangeAnima();
		void AnimationWait();
		void AnimationRotL();
		void AnimationRotR();
		void AnimationDamage();
		///////////////////////
		//アニメーションの変更セット関数
		void SetChangeAnima(int Num) {
			m_ChangeAnimaNumber = Num;
		}
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
	///	プレイヤーマネージャー
	//--------------------------------------------------------------------------------------
	class PlayerManager : public GameObject {
	private:
		//初期Pos戻るステートPlayerが戻る目安
		Vector3 PlayerL_Initial_Vec3 = Vector3(0, 0, 0);
		Vector3 PLayerR_Initial_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerL_Distance_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Distance_Vec3 = Vector3(0, 0, 0);
		//デバッグ文字表示オブジェ
		shared_ptr<DebugTxt> m_Debugtxt;
		Vector3 m_DebugL = Vector3(0, 0, 0);
		Vector3 m_DebugR = Vector3(0, 0, 0);
		//別のスピード
		float Speed_F = 0.0f;
		float AddSpeed = 0.0f;//加速時に使用
		shared_ptr<StateMachine<PlayerManager>> m_StateManagerMachine;
		//InputStick関数内の使用変数/////
		//移動スピード
		float Move_Speed = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0.0f, 0.0f, 0.0f);
		Vector3 StickVec = Vector3(0.0f, 0.0f, 0.0f);
		/////////////////////////////////
		//Direction関数内の使用変数/////
		Vector3 Direction_Vec3 = Vector3(0, 0, 0);
		/////////////////////////////////

		//ステートでの変数
		Vector3 PlayerL_SavePos_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_SavePos_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerL_Direction_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Direction_Vec3 = Vector3(0, 0, 0);
		//戻るステートでの変数
		Vector3 PlayerL_Velocity_Vec3 = Vector3(0, 0, 0);
		Vector3 PlayerR_Velocity_Vec3 = Vector3(0, 0, 0);

		//プレイヤー同士の距離
		Vector3 Distance = Vector3(0, 0, 0);
		//回転フラグ
		bool m_RotateFlg = false;
		//ローテーション可能フラグ(離れている時
		bool m_LeaveRotateFlg = false;
		//ステージのスケール
		Vector2 m_StageSize;
		//ダメージ用
		bool m_DamePower = false;
		float m_LimitTime = 0;

	public:

		PlayerManager(const shared_ptr<Stage>& StagePtr);
		virtual ~PlayerManager() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnLastUpdate() override;
		void InputStick();//コントローラでの移動
		void InputRotation();//プレイヤーの回転
		void PlayerAngle();//プレイヤーのモデルの向き
		void InitializationVelocity();//Velovituの初期化

		Vector3 Direction(Vector3 MyPos, Vector3 PartnerPos);
		Vector3 Move_Velo(Vector3 MyPos, Vector3 PartnerPos);
		//コリジョンのアクティブ
		void SetActiveCollision(bool flg);

		//アクセサ ステートマシーン
		shared_ptr<StateMachine<PlayerManager>>& GetStateMachine_Manager() {
			return m_StateManagerMachine;
		}
		//ステートチェンジ関数
		void StateChangeDoingInterpose();
		void StateChangeDie();
		//行動のスタート関数
		void EnterGamePrepare();//ゲーム前の準備ステート
		void EnterMoveBehavior();//移動ステート 
		void EnterLeaveBehavior();//離れるステート
		void EnterToAttractBehavior();//引き付けるステート
		void EnterToAttractFailureBehavior();//攻撃失敗
		void EnterReturnBehavior();//戻る
		void EneterDoingInterpose();//挟んでいるとき
		void EneterDieBehavior();

									//行動の継続関数			
		void ExecuteGamePrepare();//ゲーム前の準備
		void ExecuteMoveBehavior();
		void ExecuteLeaveBehavior();//離れる
		void ExecuteToAttractBehavior();//引き付ける
		void ExecuteToAttractFailureBehavior();//攻撃失敗
		void ExecuteReturnBehavior();//戻る
		void ExecuteDoingInterpose();//挟んでいるとき
		void ExecuteDieBehavior();

									 //行動の終了関数		
		void ExitGamePrepare();//ゲーム前の準備
		void ExitMoveBehabior();
		void ExitLeaveBehavior();//離れる
		void ExitToAttractBehavior();//引き付ける
		void ExitToAttractFailureBehavior();//攻撃失敗
		void ExitReturnBehavior();//戻る
		void ExitDoingInterpose();//挟んでいるとき
		void ExitDieBehavior();

		//エリア外への進行を防ぐ関数
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
	//	用途:　ゲーム準備
	//--------------------------------------------------------------------------------------
	class GamePrepareState_Manager : public ObjState<PlayerManager>
	{
		GamePrepareState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<GamePrepareState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class MoveState_Manager : public ObjState<PlayerManager>;
	//	用途:　移動
	//--------------------------------------------------------------------------------------
	class MoveState_Manager : public ObjState<PlayerManager>
	{
		MoveState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<MoveState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ToAttractState_Manager : public ObjState<PlayerManager>;
	//	用途:　引き合う
	//--------------------------------------------------------------------------------------
	class ToAttractState_Manager : public ObjState<PlayerManager>
	{
		ToAttractState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<ToAttractState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ToAttractAttract_F_Manager : public ObjState<PlayerManager>;
	//	用途:　攻撃失敗
	//--------------------------------------------------------------------------------------
	class ToAttractAttract_F_Manager : public ObjState<PlayerManager>
	{
		ToAttractAttract_F_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<ToAttractAttract_F_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class LeaveState_Manager : public ObjState<PlayerManager>;
	//	用途:　離れる
	//--------------------------------------------------------------------------------------
	class LeaveState_Manager : public ObjState<PlayerManager>
	{
		LeaveState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<LeaveState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class ReturnState_Manager : public ObjState<PlayerManager>;
	//	用途:　戻るステート
	//--------------------------------------------------------------------------------------
	class ReturnState_Manager : public ObjState<PlayerManager>
	{
		ReturnState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<ReturnState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DoingInterposeState_Manager : public ObjState<PlayerManager>;
	//	用途:　挟んでいるときのステート
	//--------------------------------------------------------------------------------------
	class DoingInterposeState_Manager : public ObjState<PlayerManager>
	{
		DoingInterposeState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<DoingInterposeState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DieState_Manager : public ObjState<PlayerManager>;
	//	用途:　死んだステート
	//--------------------------------------------------------------------------------------
	class DieState_Manager : public ObjState<PlayerManager>
	{
		DieState_Manager() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<DieState_Manager> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<PlayerManager>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<PlayerManager>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<PlayerManager>& Obj)override;
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

	

	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	用途: プレイヤーHPの処理
	//--------------------------------------------------------------------------------------
	class PlayerHP : public GameObject {
	private:
		//無敵用
		bool m_invincible_b = false;
		float InvinciblecCunt = 0.0f;
		float InvinciblecLimit = 3.0f;
		//敵との接触
		bool m_Hit_b = false;
		//ダメージ
		int m_Damage_int = 0;
		public:
		//構築と破棄
		PlayerHP(const shared_ptr<Stage>& StagePtr
		);
		virtual ~PlayerHP();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//操作
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
