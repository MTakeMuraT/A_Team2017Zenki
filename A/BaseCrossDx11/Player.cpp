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
	Player::Player(const shared_ptr<Stage>& StagePtr, const Vector3& StartPos, const wstring& PlayerLorPlayerR) :
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_Player_Str(PlayerLorPlayerR)
	{}
	//初期化
	void Player::OnCreate() {
		shared_ptr<CollisionSand> m_CollisionSand;
		//m_Collision_Sphere = GetStage()->AddGameObject<Collision_Sphere>();
		//初期位置などの設定
		auto Ptr = AddComponent<Transform>();
		Ptr->SetScale(1.0f, 1.0f, 1.0f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_StartPos);
		Vector3 Rot;
		if (m_Player_Str == L"PlayerL") {
			Rot = Vector3(0, -XM_PI / 2, 0);
		}
		else {
			Rot = Vector3(0, XM_PI / 2, 0);
		}

		//モデルとトランスフォームの間の差分
		Matrix4X4 PlayerMat;
		PlayerMat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(Rot),
			Vector3(0.0f, -0.61f, 0.0f)
		);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		//auto PtrCol = AddComponent<CollisionSphere>();

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFontColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"Player_Model");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"Player_Model");
		//描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"TRACE_TX");

		//透明処理
		SetAlphaActive(true);
		PtrDraw->SetMeshToTransformMatrix(PlayerMat);

	}
	void Player::OnUpdate() {
		
	}

	
	//////////////////////////////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	///	プレイヤーセンター
	//--------------------------------------------------------------------------------------
	PlayerCenter::PlayerCenter(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void PlayerCenter::OnCreate() {
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(0.0f, 0.5f, 5.0f);

		////影をつける（シャドウマップを描画する）
		//auto ShadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		////描画コンポーネントの設定
		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		////描画するメッシュを設定
		//PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		////描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"TRACE_TX");
		////透明処理
		//SetAlphaActive(true);
		auto PtrRig = AddComponent<Rigidbody>();

		//初期位置を二体のプレイヤーの真ん中に設定
		auto Trans = GetComponent<Transform>();
		auto PtrPlayerL_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		auto PtrPlayerR_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		auto PlayerHalf = (PtrPlayerL_Pos + PtrPlayerR_Pos) / 2;
		Trans->SetPosition(PlayerHalf);

	}

	void PlayerCenter::OnUpdate() {
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		auto Qt = Trans->GetQuaternion();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrPlayer_Vel = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Rigidbody>()->GetVelocity();
		Rig->SetVelocity(PtrPlayer_Vel);


		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
			Quaternion SpanQt(Vector3(0, 1, 0), -ElapsedTime * 2.0f);
			Qt *= SpanQt;
			Trans->SetQuaternion(Qt);
		}
		else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			Quaternion SpanQt(Vector3(0, 1, 0), ElapsedTime * 2.0f);
			Qt *= SpanQt;
			Trans->SetQuaternion(Qt);
		}

		auto PtrPlayerL_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		auto PtrPlayerR_Pos = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();
		auto PlayerHalf = (PtrPlayerL_Pos + PtrPlayerR_Pos) / 2;
		Trans->SetPosition(PlayerHalf);
	}
	


	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	用途: スカイスフィア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	SkySphere::SkySphere(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position)
	{
	}
	SkySphere::~SkySphere() {}

	//初期化
	void SkySphere::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_Position);


		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"Background_TX");
		SetAlphaActive(true);

	}
	//--------------------------------------------------------------------------------------
	//	class PlayerManager : public GameObject;
	//	用途: プレイヤーマネージャー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	PlayerManager::PlayerManager(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}


	//初期化
	void PlayerManager::OnCreate() {
		//初期化

		//ステートマシーン作成　初期ステート設定
		m_StateManagerMachine = make_shared<StateMachine<PlayerManager> >(GetThis<PlayerManager>());
		m_StateManagerMachine->ChangeState(GamePrepareState_Manager::Instance());

		AddComponent<Rigidbody>();
		//オーディオリソース登録
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"Collision_01_SE");


		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);



	}
	void PlayerManager::OnUpdate() {
		m_StateManagerMachine->Update();
	}
	void PlayerManager::OnLastUpdate() {


		/*wstring PosStr(L"デバック初期位置L：:\t");
		PosStr += L"X=" + Util::FloatToWStr(GetDebugPlayerL().x, 6, Util::FloatModify::Fixed) + L",\t";
		PosStr += L"Y=" + Util::FloatToWStr(GetDebugPlayerL().y, 6, Util::FloatModify::Fixed) + L",\t";
		PosStr += L"Z=" + Util::FloatToWStr(GetDebugPlayerL().z, 6, Util::FloatModify::Fixed) + L"\n";
		*/


		/*wstring  str = PosStr;
		m_Debugtxt->SetText(str)*/;
	}
	//////////////ステート以外の関数群///////////////////////////////////////////////
	//スティック入力
	void PlayerManager::InputStick() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PlayerL_Rig = PlayerL_Ptr->GetComponent<Rigidbody>();
		auto PlayerR_Rig = PlayerR_Ptr->GetComponent<Rigidbody>();
		auto Rig = GetComponent<Rigidbody>();
		auto Trans = GetComponent<Transform>();
		if (m_StateManagerMachine->GetCurrentState() == MoveState_Manager::Instance()) {
			Move_Speed = Rig->GetMaxSpeed() / 5.0f;
		}
		else {
			Move_Speed = Rig->GetMaxSpeed() / 5.0f;
		}
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		PlayerL_Rig->SetVelocity(Vec_Vec3 * Move_Speed);
		PlayerR_Rig->SetVelocity(Vec_Vec3 * Move_Speed);


	}
	//回転
	void PlayerManager::InputRotation() {
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterRot = PlayerCenterPtr->GetComponent<Transform>()->GetRotation();
		float RotY_Initialization = PlayerCenterRot.y;
		float RotY = RotY_Initialization;
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Trans = PlayerL_Ptr->GetComponent<Transform>();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Trans = PlayerR_Ptr->GetComponent<Transform>();
		if (PlayerL_Ptr) {
			RotY -= XM_PIDIV2;
		}
		auto PosL = Vector3(sin(RotY), 0, cos(RotY));
		//初期化//
		RotY = RotY_Initialization;
		//////////
		if (PlayerR_Ptr) {
			RotY += XM_PIDIV2;
		}
		auto PosR = Vector3(sin(RotY), 0, cos(RotY));

		PosL += PlayerCenterPos;
		PosR += PlayerCenterPos;
		PlayerL_Trans->SetScale(1.0, 1.0, 1.0);
		PlayerL_Trans->SetRotation(0, 0, 0);
		PlayerL_Trans->SetPosition(PosL);
		PlayerR_Trans->SetScale(1.0, 1.0, 1.0);
		PlayerR_Trans->SetRotation(0, 0, 0);
		PlayerR_Trans->SetPosition(PosR);

	}
	//初期化
	void PlayerManager::InitializationVelocity() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(0, 0, 0);
	}
	//方向
	Vector3 PlayerManager::Direction(Vector3 MyPos, Vector3 PartnerPos) {
		//反対に向いて欲しいので自分-相手
		Direction_Vec3 = MyPos - PartnerPos;
		Direction_Vec3.Normalize();
		return Direction_Vec3;
	}
	//移動
	Vector3 PlayerManager::Move_Velo(Vector3 MyPos, Vector3 PartnerPos) {
		Vector3 Default_Pos_Vec3 = PartnerPos - MyPos;
		float Angle = atan2(Default_Pos_Vec3.z, Default_Pos_Vec3.x);
		Vector3 Velo = Vector3(cos(Angle), 0, sin(Angle));
		return Velo;
	}
	//モデルのプレイヤー方向
	void PlayerManager::PlayerAngle() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter");
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = PlayerCenterPos - PlayerL_Pos;
		Vector3 Distance2_Vec3 = PlayerCenterPos - PlayerR_Pos;

		float Angl = atan2(Distance_Vec3.z, -Distance_Vec3.x);
		float Angl2 = atan2(Distance2_Vec3.z, -Distance2_Vec3.x);
		Angl += XM_PI;

		Quaternion Qt(Vector3(0, 1, 0), Angl);
		Quaternion Qt2(Vector3(0, 1, 0), Angl2);

		PlayerL_Ptr->GetComponent<Transform>()->SetQuaternion(Qt);
		PlayerR_Ptr->GetComponent<Transform>()->SetQuaternion(Qt2);
	}
	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////ステートシェンジ関数///////////////////////////////////
	void PlayerManager::StateChangeDoingInterpose() {
		//挟まれた対象からフラグをもらう
		auto PtrShotEnemyChild = GetStage()->GetSharedGameObject<ShotEnemyChild>(L"ShotEnemyChild", false);
		if (PtrShotEnemyChild->GetShotEnemyChildSandFlg()) {
			GetStateMachine_Manager()->ChangeState(DoingInterposeState_Manager::Instance());

		}
	}

	////////////////////////ステートスタート関数///////////////////////////////////
	void PlayerManager::EnterGamePrepare() {
		//処理なし
	}
	//移動
	void PlayerManager::EnterMoveBehavior() {

	}
	//離れる
	void PlayerManager::EnterLeaveBehavior() {


		////初期位置の保存
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		PlayerL_SavePos_Vec3 = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		PlayerR_SavePos_Vec3 = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();

		PlayerL_Direction_Vec3 = Direction(PlayerL_SavePos_Vec3, PlayerR_SavePos_Vec3);
		PlayerR_Direction_Vec3 = Direction(PlayerR_SavePos_Vec3, PlayerL_SavePos_Vec3);
	}
	//引き付ける
	void PlayerManager::EnterToAttractBehavior() {
		//当たり判定
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(true);
		}
		else {
			throw BaseException(
				L"エラー",
				L"スタート関数の中「EnterToAttractBehavior」",
				L"PtrCollisionSandが存在していません"
			);
		}
		////進む向き
		PlayerL_Direction_Vec3 = Move_Velo(PlayerL_SavePos_Vec3, PlayerR_SavePos_Vec3);
		PlayerR_Direction_Vec3 = Move_Velo(PlayerR_SavePos_Vec3, PlayerL_SavePos_Vec3);


	}
	//最初の位置に戻る
	void PlayerManager::EnterReturnBehavior() {
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(false);
		}
		else {
			throw BaseException(
				L"エラー",
				L"スタート関数の中「ExitLeaveBehavior」",
				L"PtrCollisionSandが存在していません"
			);
		}
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlaeyrR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		PlayerL_Velocity_Vec3 = Move_Velo(PlayerL_Pos, PlayerL_SavePos_Vec3);
		PlayerR_Velocity_Vec3 = Move_Velo(PlayerL_Pos, PlayerR_SavePos_Vec3);

	}
	//挟んでいるとき
	void PlayerManager::EneterDoingInterpose() {

	}
	////////////////////////継続式関数///////////////////////////////////
	void PlayerManager::ExecuteGamePrepare() {
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerCenterPtr = GetStage()->GetSharedGameObject<PlayerCenter>(L"PlayerCenter", false);
		auto PlayerCenterPos = PlayerCenterPtr->GetComponent<Transform>()->GetPosition();


		if (PtrCollisionSand && PlayerCenterPtr) {
			PtrCollisionSand->SetActive(false);
			//戻るときの目安
			PlayerL_Initial_Vec3 = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
			PLayerR_Initial_Vec3 = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
			PlayerL_Distance_Vec3 = PlayerL_Initial_Vec3 - PlayerCenterPos;
			PlayerR_Distance_Vec3 = PLayerR_Initial_Vec3 - PlayerCenterPos;
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}
		//		GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
	}
	//移動
	void PlayerManager::ExecuteMoveBehavior() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		InputStick();
		InputRotation();
		PlayerAngle();

		if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
			//ステート移動
			GetStateMachine_Manager()->ChangeState(LeaveState_Manager::Instance());
		}
	}
	//離れる
	void PlayerManager::ExecuteLeaveBehavior() {

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		auto Distance = PlayerL_Pos - PlayerR_Pos;

		//　離れる処理
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 10;
		auto Rig = GetComponent<Rigidbody>();

		PlayerL_Direction_Vec3.y = 0;
		PlayerR_Direction_Vec3.y = 0;
		//New_Vec = 進む方向　Speed_F = 移動スピード

		if (CntlVec[0].fThumbLX || CntlVec[0].fThumbLY) {
			InputStick();
		}
		else {
			PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerL_Direction_Vec3.x, 0, PlayerL_Direction_Vec3.z)* Speed_F * ElapsedTime_F);
			PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerR_Direction_Vec3.x, 0, PlayerR_Direction_Vec3.z)* Speed_F * ElapsedTime_F);

		}

		if (Distance.x * Distance.x + Distance.z * Distance.z > 100) {
			Speed_F = 0.0f;
		}
		else {
			Speed_F += Rig->GetMaxSpeed() / 30;
		}

		//Aが話されたら攻撃ステートに移動
		if (!(CntlVec[0].wButtons& XINPUT_GAMEPAD_A)) {
			GetStateMachine_Manager()->ChangeState(ToAttractState_Manager::Instance());
		}
	}
	//引き付ける
	void PlayerManager::ExecuteToAttractBehavior() {
		auto Rig = GetComponent<Rigidbody>();
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		Vector3 Distance_Vec3 = PlayerL_Pos - PlayerR_Pos;

		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 20;
		Speed_F += Rig->GetMaxSpeed() / 30;
		PlayerL_Direction_Vec3.y = 0;
		PlayerR_Direction_Vec3.y = 0;
		//New_Vec = 進む方向　Speed_F = 移動スピード
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerL_Direction_Vec3.x, 0, PlayerL_Direction_Vec3.z)* Speed_F * ElapsedTime_F);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(Vector3(PlayerR_Direction_Vec3.x, 0, PlayerR_Direction_Vec3.z)* Speed_F * ElapsedTime_F);

		StateChangeDoingInterpose();
		if (1.5 > abs(Distance_Vec3.x) && 1.5 > abs(Distance_Vec3.z)) {

			//SE
			auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			pMultiSoundEffect->Start(L"Collision_01_SE", 0, 0.4f);

			GetStateMachine_Manager()->ChangeState(ReturnState_Manager::Instance());
		}
	}
	//最初の位置に戻る
	void PlayerManager::ExecuteReturnBehavior() {
		auto PlayerL_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PlayerR_Ptr = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PlayerL_Pos = PlayerL_Ptr->GetComponent<Transform>()->GetPosition();
		auto PlaeyrR_Pos = PlayerR_Ptr->GetComponent<Transform>()->GetPosition();
		//　離れる処理
		float ElapsedTime_F = App::GetApp()->GetElapsedTime() * 2;
		auto Trans = GetComponent<Transform>();
		auto Rig = GetComponent<Rigidbody>();
		Vector3 Distance_L_Vec3 = PlayerL_SavePos_Vec3 - PlayerL_Pos;
		Vector3 Distance_R_Vec3 = PlayerR_SavePos_Vec3 - PlaeyrR_Pos;

		Speed_F += Rig->GetMaxSpeed() / 3;
		//New_Vec = 進む方向　Speed_F = 移動スピード
		PlayerL_Ptr->GetComponent<Rigidbody>()->SetVelocity(PlayerL_Velocity_Vec3 * Speed_F * ElapsedTime_F);
		PlayerR_Ptr->GetComponent<Rigidbody>()->SetVelocity(PlayerR_Velocity_Vec3 * Speed_F * ElapsedTime_F);

		if (abs(PlayerL_Pos.x) > abs(PlayerL_Initial_Vec3.x) && abs(PlayerL_Pos.z) > abs(PlayerL_Initial_Vec3.z)) {
			//	PlayerL_Ptr->GetComponent<Transform>()->SetPosition(PlayerL_SavePos_Vec3);
			//PlayerR_Ptr->GetComponent<Transform>()->SetPosition(PlayerR_SavePos_Vec3);
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}
	}
	//挟んでいるとき
	void PlayerManager::ExecuteDoingInterpose() {
		InputStick();
		InputRotation();
		PlayerAngle();

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wPressedButtons& XINPUT_GAMEPAD_B) {
			GetStateMachine_Manager()->ChangeState(MoveState_Manager::Instance());
		}

	}
	////////////////////////終了関数///////////////////////////////////
	void PlayerManager::ExitGamePrepare() {

	}
	void PlayerManager::ExitMoveBehabior() {
		InitializationVelocity();
	}
	void PlayerManager::ExitLeaveBehavior() {
		//処理なし
	}
	void PlayerManager::ExitToAttractBehavior() {
		InitializationVelocity();
		Speed_F = 0.0f;
	}
	void PlayerManager::ExitReturnBehavior() {
		InitializationVelocity();
	}
	void PlayerManager::ExitDoingInterpose() {
		InitializationVelocity();
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(false);
		}
		else {
			throw BaseException(
				L"エラー",
				L"スタート関数の中「ExitLeaveBehavior」",
				L"PtrCollisionSandが存在していません"
			);
		}
	}
	/////////////////////////ステート////////////////////////////////
	//ゲーム開始前のステート
	//--------------------------------------------------------------------------------------
	//	class GamePrepareState_Manager : public ObjState<MoveState_Manager>;
	//	用途:ゲーム開始前のステート
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<GamePrepareState_Manager> GamePrepareState_Manager::Instance() {
		static shared_ptr<GamePrepareState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<GamePrepareState_Manager>(new GamePrepareState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void GamePrepareState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterGamePrepare();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void GamePrepareState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteGamePrepare();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void GamePrepareState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitGamePrepare();
	}

	//移動ステート
	//--------------------------------------------------------------------------------------
	//	class MoveState_Manager : public ObjState<MoveState_Manager>;
	//	用途:移動ステート　
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<MoveState_Manager> MoveState_Manager::Instance() {
		static shared_ptr<MoveState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<MoveState_Manager>(new MoveState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void MoveState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterMoveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteMoveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void MoveState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitMoveBehabior();
	}

	//--------------------------------------------------------------------------------------
	//	class LeaveState_Manager : public ObjState<MoveState_Manager>;
	//	用途:離れるステート　
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<LeaveState_Manager> LeaveState_Manager::Instance() {
		static shared_ptr<LeaveState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<LeaveState_Manager>(new LeaveState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void LeaveState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterLeaveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void LeaveState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteLeaveBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void LeaveState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitLeaveBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class ToAttractState_Manager : public ObjState<MoveState_Manager>;
	//	用途:引き合うステート　
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<ToAttractState_Manager> ToAttractState_Manager::Instance() {
		static shared_ptr<ToAttractState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<ToAttractState_Manager>(new ToAttractState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void ToAttractState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteToAttractBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ToAttractState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitToAttractBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class ReturnState_Manager : public ObjState<MoveState_Manager>;
	//	用途:戻るステート
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<ReturnState_Manager> ReturnState_Manager::Instance() {
		static shared_ptr<ReturnState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<ReturnState_Manager>(new ReturnState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void ReturnState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EnterReturnBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ReturnState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteReturnBehavior();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void ReturnState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitReturnBehavior();
	}
	//--------------------------------------------------------------------------------------
	//	class DoingInterposeState_Manager : public ObjState<MoveState_Manager>;
	//	用途:挟んでいるときのステート
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<DoingInterposeState_Manager> DoingInterposeState_Manager::Instance() {
		static shared_ptr<DoingInterposeState_Manager> instance;
		if (!instance) {
			instance = shared_ptr<DoingInterposeState_Manager>(new DoingInterposeState_Manager);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void DoingInterposeState_Manager::Enter(const shared_ptr<PlayerManager>& Obj) {
		Obj->EneterDoingInterpose();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void DoingInterposeState_Manager::Execute(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExecuteDoingInterpose();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void DoingInterposeState_Manager::Exit(const shared_ptr<PlayerManager>& Obj) {
		Obj->ExitDoingInterpose();
	}
	//////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	用途: プレイヤーHP処理
	//--------------------------------------------------------------------------------------
	//構築と破棄
	PlayerHP::PlayerHP(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr)
	{
	}
	PlayerHP::~PlayerHP() {}

	//初期化
	void PlayerHP::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(0, 0, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(0, 0, 0);
		SetInvincible(false);
		SetHit(false);
	}
	void PlayerHP::OnUpdate() {
		if (!GetInvincible() && GetHit()) {
			GetStage()->GetSharedGameObject<Player_Life>(L"Life")->LifeDown(GetDamage_int());
			SetInvincible(true);

			if (GetDamage_int() > 0) {
				SetDamage_int(0);
			}
		}
		else if (GetInvincible()) {
			float ElapsedTime_F = App::GetApp()->GetElapsedTime();
			InvinciblecCunt += ElapsedTime_F;
			if (InvinciblecCunt > InvinciblecLimit) {
				SetInvincible(false);
				SetHit(false);
				InvinciblecCunt = 0.0f;
			}
		}
	}
}


