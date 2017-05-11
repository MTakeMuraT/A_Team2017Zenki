#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void GameStage::CreateViewLight()
	{
		
		auto PtrView = CreateView<SingleView>();
		/*
		//ビューのカメラの設定
		auto PtrLookAtCamera = ObjectFactory::Create<LookAtCamera>();
		PtrView->SetCamera(PtrLookAtCamera);

		PtrLookAtCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vector3(0.0f, 5.0f, -15.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();

		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);
		*/
		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}


	//プレートの作成
	void GameStage::CreatePlate()
	{
		/*AddGameObject<TestLin>(
			Vector3(256, 256, 0),
			Vector3(0, 0, 0),
			3
			);*/
	}

	// 背景
	void GameStage::CreateBackGround()
	{


	}
	//地面
	void GameStage::CreateGround() {
		//Vector3:S・P  wstring:TX_Name
		AddGameObject<Ground_GameStage>(
			Vector3(25, 25, 25),
			Vector3(0, 0, 0),
			wstring(L"TEST_Game_TX")
			);
	}

	//プレイヤー関係
	void GameStage::CreatePlayerLin() {
		auto PtrPlayer_L = AddGameObject<Player>(
			Vector3(0, 1, 0),
			wstring(L"PlayerL")
			);
		SetSharedGameObject(L"GamePlayer_L", PtrPlayer_L);
		auto PtrPlayer_R = AddGameObject<Player>(
			Vector3(5, 1, 0),
			wstring(L"PlayerR")
			);
		auto PtrPlayerManager = AddGameObject<PlayerManager>();
		SetSharedGameObject(L"PtrPlayerManager", false);
		SetSharedGameObject(L"GamePlayer_R", PtrPlayer_R);
		auto PtrPlayerCenter = AddGameObject<PlayerCenter>();
		SetSharedGameObject(L"PlayerCenter", PtrPlayerCenter);
		auto PtrPlayerHP = AddGameObject<PlayerHP>();
		SetSharedGameObject(L"PlayerHP", PtrPlayerHP);
		////HP関係
		//AddGameObject<HP>(
		//	Vector2(512, 512),
		//	Vector2(-440, 300));
		//AddGameObject<HPBackGround>(
		//	Vector2(512, 512),
		//	Vector2(-440, 300));
	}

	void GameStage::CreateUILin() {

	}

	//実装したいものをテストする時に使用
	void GameStage::CreateTestLin() {
		AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, -5),
			wstring(L"TRACE_TX")
			);
		AddGameObject<SkySphere>(
			Vector3(300,300,300),
			Vector3(0,0,0));
		AddGameObject<Ground_GameStage>(
			Vector3(300, 300, 300),
			Vector3(0, -50, 0),
			wstring(L"Background_TX")
			);
		/*AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, 5),
			wstring(L"TRACE_TX")
			);*/

		
	}
	//タイマー作成------------------------------------------
	void GameStage::CreateTimer()
	{
		auto Ti = AddGameObject<Timer>(60, Vector2(50, 300), Vector2(100, 100), 5);
		SetSharedGameObject(L"Timer", Ti);
	}
	//タイマー作成------------------------------------------
	//ライフ作成--------------------------------------------
	void GameStage::CreateLife()
	{
		auto life = AddGameObject<Player_Life>(10, Vector2(-580, 300), Vector2(100, 100), 4);
		SetSharedGameObject(L"Life", life);
	}
	//ライフ作成--------------------------------------------

	//アタリ判定作成--------------------------------------------
	void GameStage::CreateCollision()
	{
		AddGameObject<CollisionManager>();
		auto ColSandPtr = AddGameObject<CollisionSand>();
		SetSharedGameObject(L"CollisionSand", ColSandPtr);
	}
	//アタリ判定作成--------------------------------------------
	
	//ミサイル子機
	void GameStage::CreateChildMissile() {
		auto ColGroup = GetSharedObjectGroup(L"EnemyGroup");
		auto PtrShotEnemyChild = AddGameObject<ShotEnemyChild>(
			Vector3(0, 1, 0),
			Vector3(1.0, 1.0, 1.0),
			0.0f
			);
		SetSharedGameObject(L"ShotEnemyChild", PtrShotEnemyChild);
		ColGroup->IntoGroup(PtrShotEnemyChild);
	}
	void GameStage::OnCreate()
	{
		try {
			/*//検証するのに重いので一時的に消します Abe20170505
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"GameStage_01_BGM");
			m_AudioObjectPtr->Start(L"GameStage_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			*/
			//ビューとライトの作成
			CreateViewLight();
			CreatePlate();
			CreatePlayerLin();
			CreateGround();
			CreateUILin();
			//制限時間
			CreateTimer();
			//ライフ
			CreateLife();
			//背景の作成
			CreateBackGround();
			CreateTestLin();

			//アタリ判定作成
			CreateCollision();

			

			//Abe20170412
			//エネミー作ってみた[アタリ判定とかテストするための仮のやつなのでCSVで出せるようになったら消してください]

			auto EnemyGroup = CreateSharedObjectGroup(L"EnemyGroup");

			auto Enemy_01Ptr = AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy01", Enemy_01Ptr);
			auto Enemy_02Ptr = AddGameObject<Enemy01>(Vector3(0, 1, -5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy02", Enemy_02Ptr);

			EnemyGroup->IntoGroup(Enemy_01Ptr);
			EnemyGroup->IntoGroup(Enemy_02Ptr);
			//Abe20170412

			//子機ミサイル
			CreateChildMissile();

			//Abe20170504
			//アタリ判定テスト用[とりあえずグループにだけ入れてくれればそれでおｋです]
			auto CollisionGroup = CreateSharedObjectGroup(L"CollisionGroup");
			auto Enemy_03Ptr = AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			SetSharedGameObject(L"Enemy03", Enemy_01Ptr);
			CollisionGroup->IntoGroup(Enemy_03Ptr);

			//Abe20170504

			//Abe20170505
			//エネミーテスト
			//引数 位置、大きさ、HP、索敵距離、クールタイム、速度、攻撃力、突撃回数
			auto PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(10, 1, 10), 1, 0, 3, 3, 6, 3, 2);
			CollisionGroup->IntoGroup(PtrTacklEnemy);
			EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(-10, 1, 10), 1, 0, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(10, 1, -10), 1, 1, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);
			//PtrTacklEnemy = AddGameObject<TackleEnemy>(Vector3(-10, 1, -10), 1, 1, 3, 3, 6, 3, 2);
			//CollisionGroup->IntoGroup(PtrTacklEnemy);
			//EnemyGroup->IntoGroup(PtrTacklEnemy);

			//引数 位置、大きさ、HP、索敵距離、クールタイム、攻撃力、子機発射間隔、発射数
			//AddGameObject<ShotEnemy>(Vector3(10, 1, -10),1,3,5,6,3,10,2);
			//引数 位置、大きさ、HP、索敵距離、クールタイム、発射数
			//AddGameObject<TeleportEnemy>(Vector3(-10, 1, 10),2,1,5,8,3);
			//引数 位置、大きさ、HP、索敵距離、速度、攻撃力
			//Abe20170505
			auto objbomb = AddGameObject<BombEnemy>(Vector3(20, 1, 20), 1, 1, 3, 2, 8);
			CollisionGroup->IntoGroup(objbomb);
			EnemyGroup->IntoGroup(objbomb);
			
			//Abe20170508
			//テレポート先作成
			auto TereportGroup = CreateSharedObjectGroup(L"TereportPointGroup");
			//適当に２か所作っておく
			TereportGroup->IntoGroup(AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3)));
			TereportGroup->IntoGroup(AddGameObject<TereportPoint>(Vector3(-3, 0.5f, -3)));

			//テレポートエネミー
			//引数 位置、大きさ、HP、索敵距離、クールタイム、発射数
			AddGameObject<TeleportEnemy>(Vector3(-10, 1, 10), 1, 1, 5, 1, 3);
			//爆弾グループ
			CreateSharedObjectGroup(L"BombGroup");
			//Abe20170508



		}
		catch (...) {



			throw;
		}
	}



	// 更新
	// シーン遷移
	void GameStage::OnUpdate()
	{
		//キーの入力
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
		}
		if (KeylVec.m_bPressedKeyTbl['D'])
		{
			//ライフ減らす
			GetSharedGameObject<Player_Life>(L"Life")->LifeDown(1);

		}

		//カメラ更新
		UpdateCamera();
	}

	//カメラ更新
	void GameStage::UpdateCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//座標
		Vector3 Pos = CameraP->GetEye();
		//見る部分
		Vector3 At = CameraP->GetAt();


		//２体の座標もらう
		Vector3 Player1Pos = GetSharedGameObject<Player>(L"GamePlayer_L", false)->GetComponent<Transform>()->GetPosition();
		Vector3 Player2Pos = GetSharedGameObject<Player>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();

		//見る点をプレイヤー間の中心
		At = (Player1Pos + Player2Pos) / 2;
		//座標をちょっと手前上
		Pos = At;
		//距離を測る
		Vector3 def = Player2Pos - Player1Pos;
		def = def*def;
		//上昇分
		float Yup = sqrt(def.x + def.z) - 6;
		//上昇分にカメラの初期高さを追加
		Yup += 10;
		if (Yup < 10)
		{
			Yup = 10;
		}
		Pos.y += Yup;
		//同じ値をZにも
		Pos.z += -Yup;

		//カメラ更新
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
	}
	GameStage::~GameStage() {
		//m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
	}

	//////////////////////////////////////////////////////////////////
	// class Ground_GameStage : public GameObject
	//コンストラクタ　Vector3 Scale; Vector3 Postion wstring TX_Name
	///////////////////////////////////////////////////////////////////
	Ground_GameStage::Ground_GameStage(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Postion,
		const wstring& TX_Name):
	GameObject(StagePtr),
	m_Scale(Scale),
	m_Positon(Postion),
	m_TX_Name(TX_Name)
	{}
	void Ground_GameStage::OnCreate() {
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		if (m_TX_Name == L"Background_TX") {
			PtrDraw->SetTextureResource(m_TX_Name);
		}
		else if(m_TX_Name == L"TEST_Game_TX"){
			PtrDraw->SetTextureResource(m_TX_Name);
		}


		auto PtrTrans = AddComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(100.0f, 100.0f, 1.0f),
			Qt,
			Vector3(0.0f, 0.0f, 0.0f)
		);

		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(m_Positon);
		//PtrDraw->SetDrawActive(false);
	}

}
//end basecross
