/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

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

		m_Collision_Sphere = GetStage()->AddGameObject<Collision_Sphere>();

		//初期位置などの設定
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"TRACE_TX");

		//透明処理
		SetAlphaActive(true);

		m_StatePlayerMachine = make_shared<StateMachine<Player> >(GetThis<Player>());
		m_StatePlayerMachine->ChangeState(MoveState::Instance());
	}
	void Player::OnUpdate() {
		m_StatePlayerMachine->Update();
		
		
	}
	void Player::OnLastUpdate() {
		//文字列表示
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\n";

		wstring VelocityPowerStr(L"VelocityPower:");
		VelocityPowerStr += Util::FloatToWStr(VelocityPower);
		VelocityPowerStr += L"\n";

		auto Pos = GetComponent<Transform>()->GetWorldMatrix().PosInMatrix();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring m_FixedPos_b(L"位置固定フラグ:\t");
		if (FixedPos_b) {
			m_FixedPos_b += L"true\n";
		}
		else {
			m_FixedPos_b += L"false\n";
		}
		
		wstring m_Debug_StickDown_b(L"挟んでいる時の移動Flg:");
		if (Debug_StickDown_b) {
			m_Debug_StickDown_b += L"true";
		}
		else {
			m_Debug_StickDown_b += L"false";
		}

		//ステート
		wstring State(L"ステート状態：");
		if (m_StatePlayerMachine->GetCurrentState() == MoveState::Instance()) {

			State += L"移動";
			State += L"\n";
		}
		else if (m_StatePlayerMachine->GetCurrentState() == ToAttractState::Instance()) {

			State += L"引き寄せあう";
			State += L"\n";
		}
		else if (m_StatePlayerMachine->GetCurrentState() == PinchState::Instance()) {

			State += L"挟んでいるステート";
			State += L"\n";
		}
		else {
			State += L"該当なし";
			State += L"\n";
		}
		

		wstring ObjStr(L"\nPosition:\t");
		if (m_HitObject != NULL) {
			auto Obj = m_HitObject->GetComponent<Transform>()->GetPosition();
			
			ObjStr += L"X=" + Util::FloatToWStr(Obj.x, 6, Util::FloatModify::Fixed) + L",\t";
			ObjStr += L"Y=" + Util::FloatToWStr(Obj.y, 6, Util::FloatModify::Fixed) + L",\t";
			ObjStr += L"Z=" + Util::FloatToWStr(Obj.z, 6, Util::FloatModify::Fixed) + L"\n";
		}

		wstring  str = FPS + State + m_FixedPos_b + m_Debug_StickDown_b;
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto A : OtherVec) {
			auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
			if (Fixd_Box) {
				m_HitObject = dynamic_pointer_cast<GameObject>(A);
				//処理
				GetStateMachine()->ChangeState(PinchState::Instance());
			}
		}
	}
	
	
	
	//スティック入力
	void Player::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}


	
	
	////////////////////////ステートスタート関数///////////////////////////////////
	//挟む
	void Player::EnterToAttractBehavior() {
		//Aボタンが押されてるか？
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
		//	KeepPushed_A = true;
			
		}
	}
	//挟んでいる時
	void Player::EnterPinchBehavior() {
		if (FixedPos_b == false) {
			FixedPos_b = true;
		}
	}

	////////////////////////ステート継続関数///////////////////////////////////////
	//ステートマシーンで使う関数
	void Player::ExcuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//ステート移動
			GetStateMachine()->ChangeState(ToAttractState::Instance());
		}
	}

	//引き寄せ合うステート
	void Player::ExcuteToAttractBehavior() {
		if (KeepPushed_A == true) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//自分の位置
				My_Pos_Vec3 = Trans->GetPosition();
				//もう一つのプレイヤーの位置
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_F * Speed_F * VelocityPower));
				
			}
			else
			{
				VelocityPower = 1.0f;
				GetStateMachine()->ChangeState(MoveState::Instance());
			}
			VelocityPower += AddVec;
		}

	}

	//挟んでいるとき
	void Player::ExcutePinchBehavior() {
		//コントローラ取得
		//自分
		auto Player_L_Trans = GetComponent<Transform>();
		Vector3 Player_L_Pos_Vec3 = Player_L_Trans->GetPosition();
		//PlayerL/Rは大きさが同じ
		Vector3 Player_Scale = Player_L_Trans->GetScale();

		//もう一体
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Player_R_Ptr = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false);
		auto Player_R_Trans = Player_R_Ptr->GetComponent<Transform>();
		Vector3 Player_R_Pos_Vec3 = Player_R_Trans->GetPosition();
		//対象のオブジェクト
		auto HitObj_Trans = m_HitObject->GetComponent<Transform>();
		Vector3 HitObj_Pos_Vec3 = HitObj_Trans->GetPosition();
		Vector3 HitObj_Scale = HitObj_Trans->GetScale();
		//挟んでいる物の位置、自分の位置、もう一体の位置、挟んでいる物の大きさ、自分の大きさ
		m_Collision_Sphere->CollisionTest(HitObj_Pos_Vec3, Player_L_Pos_Vec3,Player_R_Pos_Vec3, HitObj_Scale, Player_Scale);

		//Aが押されていたらその場所の位置を固定させる
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			FixedPos();
		}
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_B) {
			GetStateMachine()->ChangeState(MoveState::Instance());
		}
		//コントローラのLスティックの入力があれば挟んで移動ステートに移動
		if (CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			Debug_StickDown_b = true;
		}
		else {
			Debug_StickDown_b = false;
		}
	}


	/////////////////////////ステート終了関数/////////////////////////////////////////
	void Player::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0,0,0);
	}
	void Player::ExitToAttractBehavior() {
		

	}
	//挟んでいるとき
	void Player::ExitPinchBehavior() {
		FixedPos_b = false;
		
	}
	//関数群
	Vector3 Player::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	//位置固定
	void Player::FixedPos() {
		if (FixedPos_b) {
			 Now_Pos_Vec3 = GetComponent<Transform>()->GetPosition();
			 GetComponent<Transform>()->SetPosition(Now_Pos_Vec3);
			 GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		}
		FixedPos_b = false;
		
	}

	//移動ステート
	//--------------------------------------------------------------------------------------
	//	class MoveState : public ObjState<Player>;
	//	用途:移動ステート　
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<MoveState> MoveState::Instance() {
		static shared_ptr<MoveState> instance;
		if (!instance) {
			instance = shared_ptr<MoveState>(new MoveState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void MoveState::Enter(const shared_ptr<Player>& Obj) {
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExcuteMoveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitMoveBehabior();
	}

	//移動ステート
	//--------------------------------------------------------------------------------------
	//	class ToAttractState : public ObjState<Player>;
	//	用途:引き寄せ合う
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<ToAttractState> ToAttractState::Instance() {
		static shared_ptr<ToAttractState> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState>(new ToAttractState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void ToAttractState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExcuteToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitToAttractBehavior();
	}
	//挟んでいるステート
	//--------------------------------------------------------------------------------------
	//	class PinchState : public ObjState<Player>;
	//	用途:挟んでいるステート
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<PinchState> PinchState::Instance() {
		static shared_ptr<PinchState> instance;
		if (!instance) {
			instance = shared_ptr<PinchState>(new PinchState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void PinchState::Enter(const shared_ptr<Player>& Obj) {
		Obj->EnterPinchBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void PinchState::Execute(const shared_ptr<Player>& Obj) {
		Obj->ExcutePinchBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void PinchState::Exit(const shared_ptr<Player>& Obj) {
		Obj->ExitPinchBehavior();
	}

	////////////////////////////もう一体のプレイヤー////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	//	class Player_Second : public Player;
	//	用途: プレイヤー2
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Player_Second::Player_Second(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{}
	//初期化
	void Player_Second::OnCreate() {

		//初期位置などの設定
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		

		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"TRACE_TX");

		//透明処理
		SetAlphaActive(true);

		m_StatePlayer_SecondMachine = make_shared<StateMachine<Player_Second> >(GetThis<Player_Second>());
		m_StatePlayer_SecondMachine->ChangeState(MoveState_Second::Instance());
	}
	void Player_Second::OnUpdate() {
		m_StatePlayer_SecondMachine->Update();
	}
	void Player_Second::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto A : OtherVec) {
			auto Fixd_Box = dynamic_pointer_cast<FixdBox>(A);
			if (Fixd_Box) {
				//処理
				GetStateSecondMachine()->ChangeState(PinchState_Second::Instance());
			}
		}
	}


	//スティック入力
	void Player_Second::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbRX, 0, CntlVec[0].fThumbRY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}




	////////////////////////ステートスタート関数///////////////////////////////////
	//挟む
	void Player_Second::EnterToAttractBehavior() {
		//Aボタンが押されてるか？
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
			//KeepPushed_A = true;

		}
	}
	//挟んでいる時
	void Player_Second::EnterPinchBehavior() {
		if (FixedPos_b == false) {
			FixedPos_b = true;
		}
	}
	////////////////////////ステート継続関数///////////////////////////////////////
	//ステートマシーンで使う関数
	void Player_Second::ExcuteMoveBehavior() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//ステート移動
			GetStateSecondMachine()->ChangeState(ToAttractState_Second::Instance());
			
		}
	}
	//挟むステート
	void Player_Second::ExcuteToAttractBehavior() {
		if (KeepPushed_A == true) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				//自分の位置
				My_Pos_Vec3 = Trans->GetPosition();
				//もう一つのプレイヤーの位置
				Partner_Pos_Vec3 = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
				New_Vec = Move_Velo(My_Pos_Vec3, Partner_Pos_Vec3);
				Rig->SetVelocity(Vector3(New_Vec * ElapsedTime_F * Speed_F * VelocityPower));
				
			}
			else {
				VelocityPower = 1.0f;
				GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
			}
			VelocityPower += AddVec;
		}
	}

	//挟んでいるとき
	void Player_Second::ExcutePinchBehavior() {
		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//Aが押されていたらその場所の位置を固定させる
		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			FixedPos();
		}
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_B) {
			GetStateSecondMachine()->ChangeState(MoveState_Second::Instance());
		}
		//コントローラのLスティックの入力があれば挟んで移動ステートに移動
		if (CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			//Debug_StickDown_b = true;
		}
		else {
			//Debug_StickDown_b = false;
		}
	}

	Vector3 Player_Second::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	

	/////////////////////////ステート終了関数/////////////////////////////////////////
	void Player_Second::ExitMoveBehabior() {
		auto Rig = GetComponent<Rigidbody>();
		Rig->SetVelocity(0, 0, 0);
	}
	void Player_Second::ExitToAttractBehavior() {
		

	}
	//挟んでいるとき
	void Player_Second::ExitPinchBehavior() {
		FixedPos_b = false;

	}
	//位置固定
	void Player_Second::FixedPos() {
		if (FixedPos_b) {
			Now_Pos_Vec3 = GetComponent<Transform>()->GetPosition();
			GetComponent<Transform>()->SetPosition(Now_Pos_Vec3);
			GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		}
		FixedPos_b = false;

	}

	////移動ステート
	////--------------------------------------------------------------------------------------
	////	class MoveState_Second : public ObjState<Player_Second>;
	////	用途:移動ステート　
	////--------------------------------------------------------------------------------------
	////ステートのインスタンス取得
	shared_ptr<MoveState_Second> MoveState_Second::Instance() {
		static shared_ptr<MoveState_Second> instance;
		if (!instance) {
			instance = shared_ptr<MoveState_Second>(new MoveState_Second);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void MoveState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExcuteMoveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitMoveBehabior();
	}

	////移動ステート
	////--------------------------------------------------------------------------------------
	////	class ToAttractState_Second : public ObjState<Player_Second>;
	////	用途:引き寄せ合う
	////--------------------------------------------------------------------------------------
	////ステートのインスタンス取得
	shared_ptr<ToAttractState_Second> ToAttractState_Second::Instance() {
		static shared_ptr<ToAttractState_Second> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState_Second>(new ToAttractState_Second);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void ToAttractState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExcuteToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitToAttractBehavior();
	}
	//挟んでいるステート
	//--------------------------------------------------------------------------------------
	//	class PinchState_Second : public ObjState<Player_Second>;
	//	用途:挟んでいるステート
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<PinchState_Second> PinchState_Second::Instance() {
		static shared_ptr<PinchState_Second> instance;
		if (!instance) {
			instance = shared_ptr<PinchState_Second>(new PinchState_Second);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void PinchState_Second::Enter(const shared_ptr<Player_Second>& Obj) {
		Obj->EnterPinchBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void PinchState_Second::Execute(const shared_ptr<Player_Second>& Obj) {
		Obj->ExcutePinchBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void PinchState_Second::Exit(const shared_ptr<Player_Second>& Obj) {
		Obj->ExitPinchBehavior();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	




}
//end basecross

