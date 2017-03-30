/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{



	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}

	//初期化
	void Player::OnCreate() {

		//初期位置などの設定
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"TRACE_TX");

		//透明処理
		SetAlphaActive(true);

		//カメラを得る
		auto PtrCamera = dynamic_pointer_cast<LookAtCamera>(OnGetDrawCamera());
		if (PtrCamera) {
			//MyLookAtCameraである
			//MyLookAtCameraに注目するオブジェクト（プレイヤー）の設定
			PtrCamera->SetTargetObject(GetThis<GameObject>());
			PtrCamera->SetTargetToAt(Vector3(0, 0.25f, 0));
		}
		//最初はAボタンはジャンプ
		m_PlayerAction = PlayerAction::Jump;
		//ステートマシンの構築
		m_StatePlayerMachine.reset(new LayeredStateMachine<Player>(GetThis<Player>()));
		//最初のステートをPlayerDefaultにリセット
		m_StatePlayerMachine->Reset(PlayerDefaultState::Instance());
	}

	//更新
	void Player::OnUpdate() {
		//ステートマシン更新
		m_StatePlayerMachine->Update();
	}

	//後更新
	void Player::OnUpdate2() {
		//文字列の表示
		DrawStrings();
	}


	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		//プレイヤーが何かに当たった
		if (GetStateMachine()->GetTopState() == PlayerJumpState::Instance()) {
			//現在がジャンプステートならPlayerDefaultにリセット
			GetStateMachine()->Reset(PlayerDefaultState::Instance());
		}
	}

	void Player::ChangeStateJump() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				if (GetStateMachine()->GetTopState() == PlayerDefaultState::Instance()) {
					GetStateMachine()->Push(PlayerJumpState::Instance());
				}
			}
		}
	}

	//文字列の表示
	void Player::DrawStrings() {
		auto PtrPlayerSecnd = GetStage()->GetSharedGameObject<Player_Secnd>(L"Player_S", false)->GetStrings();


		//文字列表示
		//行動
		wstring BEHAVIOR;
		if (GetStateMachine()->GetTopState() == PlayerDefaultState::Instance()) {
			BEHAVIOR = L"デフォルト";
		}
		else {
			BEHAVIOR = L"ジャンプ";
		}
		BEHAVIOR += L"\n";

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring RididStr(L"Velocity:\t");
		auto Velocity = GetComponent<Rigidbody>()->GetVelocity();
		RididStr += L"X=" + Util::FloatToWStr(Velocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Y=" + Util::FloatToWStr(Velocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Z=" + Util::FloatToWStr(Velocity.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring HitObjectStr(L"HitObject: ");
		if (GetComponent<Collision>()->GetHitObjectVec().size() > 0) {
			for (auto&v : GetComponent<Collision>()->GetHitObjectVec()) {
				HitObjectStr += Util::UintToWStr((UINT)v.get()) + L",";
			}
			HitObjectStr += L"\n";
		}
		else {
			HitObjectStr += L"NULL\n";
		}
		wstring str = BEHAVIOR + FPS + PositionStr + RididStr + HitObjectStr + PtrPlayerSecnd;
		//文字列をつける
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}
	

	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------

	IMPLEMENT_SINGLETON_INSTANCE(PlayerDefaultState)

	void PlayerDefaultState::Enter(const shared_ptr<Player>& Obj) {
		
		//何もしない
	}

	void PlayerDefaultState::Execute(const shared_ptr<Player>& Obj) {
		auto PtrBehavior = Obj->GetBehavior<PlayerBehavior>();
		PtrBehavior->MovePlayer();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
		Obj->ChangeStateJump();
		
	}

	void PlayerDefaultState::Exit(const shared_ptr<Player>& Obj) {
		//何もしない
	}

	//--------------------------------------------------------------------------------------
	///	ジャンプステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerJumpState)

		void PlayerJumpState::Enter(const shared_ptr<Player>& Obj) {
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->StartJump(Vector3(0, 4.0f, 0));
	}

	void PlayerJumpState::Execute(const shared_ptr<Player>& Obj) {
		//ジャンプ中も方向変更可能
		auto PtrDefault = Obj->GetBehavior<PlayerBehavior>();
		PtrDefault->MovePlayer();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
	}

	void PlayerJumpState::Exit(const shared_ptr<Player>& Obj) {
		//何もしない
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//Player2
	/////////////////////////////////////////////////////////////////////////////////////

	//構築と破棄
	Player_Secnd::Player_Secnd(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}

	//初期化
	void Player_Secnd::OnCreate() {
		
		//初期位置などの設定
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();


		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"TRACE_TX");
		//ステートマシンの構築
		m_State_PlayerSecnd_Machine.reset(new LayeredStateMachine<Player_Secnd>(GetThis<Player_Secnd>()));
		//最初のステートをPlayerDefaultにリセット
		m_State_PlayerSecnd_Machine->Reset(PlayerSecndDefaultState::Instance());
	}
	
	void Player_Secnd::OnUpdate() {
		m_State_PlayerSecnd_Machine->Update();
		DrawStrings();
	}
	void Player_Secnd::DrawStrings() {

		//文字列表示
		wstring P_S = L"プレイヤー２";
		P_S += L"\n";
		//行動
		wstring BEHAVIOR;
		if (GetStatePlayerSecndMachine()->GetTopState() == PlayerSecndDefaultState::Instance()) {
			BEHAVIOR = L"デフォルト";
		}
		else {
			BEHAVIOR = L"ジャンプ";
		}
		BEHAVIOR += L"\n";


		DebugCharacter = P_S + BEHAVIOR;
	}
	wstring Player_Secnd::GetStrings() {
		return DebugCharacter;
	}
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------

	IMPLEMENT_SINGLETON_INSTANCE(PlayerSecndDefaultState)
		void PlayerSecndDefaultState::Enter(const shared_ptr<Player_Secnd>& Obj) {
		//何もしない
	}

	void PlayerSecndDefaultState::Execute(const shared_ptr<Player_Secnd>& Obj) {
		auto PtrBehavior = Obj->GetBehavior<PlayerBehavior>();
		PtrBehavior->MovePlayer_Second();
		auto PtrGrav = Obj->GetBehavior<Gravity>();
		PtrGrav->Execute();
		

	}

	void PlayerSecndDefaultState::Exit(const shared_ptr<Player_Secnd>& Obj) {
		//何もしない
	}



}
//end basecross

