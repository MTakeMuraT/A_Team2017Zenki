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
			Vector3(50, 50, 50),
			Vector3(0, 0, 0),
			wstring(L"Glass_TX")
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
		AddGameObject<SkySphere>(
			Vector3(300,300,300),
			Vector3(0,0,0));
		AddGameObject<Ground_GameStage>(
			Vector3(300, 300, 300),
			Vector3(0, -50, 0),
			wstring(L"Background_TX")
			);

		//AddGameObject<Enemycount>();
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
		auto Ti = AddGameObject<Timer>(0, Vector2(50, 300), Vector2(100, 100), 5);
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

	//エネミーカウント作成--------------------------------------------
	void GameStage::CreateEnemyCounts()
	{
		AddGameObject<EnemyCountA>(Vector2(520, -250), Vector2(100, 100), 3);
	}
	//エネミーカウント作成--------------------------------------------

	
	void GameStage::OnCreate()
	{
		try {
			////検証するのに重いので一時的に消します Abe20170505
			//m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			//m_AudioObjectPtr->AddAudioResource(L"GameStage_01_BGM");
			//m_AudioObjectPtr->Start(L"GameStage_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			
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

			//Abe20170519MukkuMarge
			//エネミーの数作成
			CreateEnemyCounts();
			//Abe20170519MukkuMarge

			//アタリ判定作成
			CreateCollision();
			auto TereportGroup = CreateSharedObjectGroup(L"TereportPointGroup");
			auto BomGroup = CreateSharedObjectGroup(L"BombGroup");
			auto EnemyGroup = CreateSharedObjectGroup(L"EnemyGroup");
			auto CollisionGroup = CreateSharedObjectGroup(L"CollisionGroup");

			//2017/05/17今泉CSV//
			AddGameObject<InputCSV>();
			/////////////////////////

			//テスト(索敵サークル)
			//Abe20170523IzumiHikitugi
			//AddGameObject<SearchCircle>();
			//Abe20170523IzumiHikitugi

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
		Yup += 15;
		if (Yup < 15)
		{
			Yup = 15;
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
		else if(m_TX_Name == L"Glass_TX"){
			PtrDraw->SetTextureResource(m_TX_Name);
			SetDrawLayer(2);
		}

		
		auto PtrTrans = AddComponent<Transform>();
		Quaternion Qt;
		Qt.RotationRollPitchYawFromVector(Vector3(XM_PIDIV2, 0, 0));
		Matrix4X4 WorldMat;
		WorldMat.DefTransformation(
			Vector3(100.0f, 100.0f, 1.0f),
			Qt,
			Vector3(0.0f, -1.0f, 0.0f)
		);

		PtrTrans->SetScale(m_Scale);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(m_Positon);
		//PtrDraw->SetDrawActive(false);
		SetAlphaActive(true);
	}
}

//end basecross
