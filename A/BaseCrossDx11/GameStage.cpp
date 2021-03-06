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
		//Abe20170525
		//ステージの大きさ取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize();
		//Abe20170525

		//Vector3:S・P  wstring:TX_Name
		AddGameObject<Ground_GameStage>(
			Vector3(m_StageSize.x, m_StageSize.y, 1),
			Vector3(0, 0, 0),
			wstring(L"Glass_TX")
			);
	}

	//プレイヤー関係
	void GameStage::CreatePlayerLin() {
	
		auto PtrPlayerControl = AddGameObject<PlayerControl>();
		SetSharedGameObject(L"PlayerControl", PtrPlayerControl);
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
			Vector3(500,500,500),
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
		auto Ti = AddGameObject<Timer>(0, Vector2(35, 300), Vector2(70, 70), 5);
		SetSharedGameObject(L"Timer", Ti);

		//動くグループに追加
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(Ti);
	}
	//タイマー作成------------------------------------------
	//ライフ作成--------------------------------------------
	void GameStage::CreateLife()
	{
		auto life = AddGameObject<Player_Life>(10, Vector2(-580, 300), Vector2(100, 100), 4);
		SetSharedGameObject(L"Life", life);

		//動くグループに追加
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(life);

	}
	//ライフ作成--------------------------------------------

	//アタリ判定作成--------------------------------------------
	void GameStage::CreateCollision()
	{
		auto ColMan = AddGameObject<CollisionManager>();
		auto ColSandPtr = AddGameObject<CollisionSand>();
		SetSharedGameObject(L"CollisionSand", ColSandPtr);

		//動くグループに追加
		//GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(ColMan);
		SetSharedGameObject(L"CollisionManager", false);
		GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(ColSandPtr);

	}
	//アタリ判定作成--------------------------------------------

	//エネミーカウント作成--------------------------------------------
	void GameStage::CreateEnemyCounts()
	{
		AddGameObject<EnemyCountA>(Vector2(520, -250), Vector2(100, 100), 3);
	}
	//エネミーカウント作成--------------------------------------------

	//Abe20170605
	//ポーズ作成--------------------------------------------
	void GameStage::CreatePause()
	{
		SetSharedGameObject(L"PauseMenu",AddGameObject<PauseMenu>());
		SetSharedGameObject(L"TitleSE", AddGameObject<SE>());

	}
	//ポーズ作成--------------------------------------------
	//Abe20170605

	//Abe20170620
	//ブースト作成--------------------------------------------
	void GameStage::CreateBoost()
	{
		auto obj = AddGameObject<KetsuHunsya>();
		obj->SetTargetSharedName(L"GamePlayer_L");
		obj->Normal();
		SetSharedGameObject(L"Ketu_L", obj);

		
		auto obj2 = AddGameObject<KetsuHunsya>();
		obj2->SetTargetSharedName(L"GamePlayer_R");
		obj2->Normal();
		SetSharedGameObject(L"Ketu_R", obj2);

	}
	//ブースト作成--------------------------------------------
	//Abe20170620

	void GameStage::OnCreate()
	{
		try {
			////検証するのに重いので一時的に消します Abe20170505
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"GameStage_01_BGM");
			m_AudioObjectPtr->Start(L"GameStage_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			m_AudioObjectPtr->AddAudioResource(L"Win_SE");
			m_AudioObjectPtr->AddAudioResource(L"WinBgm_BGM");

			//グループ類作成
			auto TereportGroup = CreateSharedObjectGroup(L"TereportPointGroup");
			auto BomGroup = CreateSharedObjectGroup(L"BombGroup");
			auto EnemyGroup = CreateSharedObjectGroup(L"EnemyGroup");
			auto CollisionGroup = CreateSharedObjectGroup(L"CollisionGroup");
			//Abe20170529
			//子機グループ
			CreateSharedObjectGroup(L"SearchChildGroup");
			CreateSharedObjectGroup(L"UgokuGroup");
			//Abe20170529
			//Abe20170605
			//爆散するオブジェクトのグループ
			CreateSharedObjectGroup(L"BakusanObjGroup");
			//爆散するオブジェクトを生成するオブジェクト
			SetSharedGameObject(L"BakuSanSpawn",AddGameObject<BakuSanSpawn>());
			//Abe20170605
			//Abe20170606
			CreateSharedObjectGroup(L"BakusanEFGroup");
			//Abe20170606

			//Abe20170609
			//ぶつかったエフェクトグループ
			CreateSharedObjectGroup(L"ButukariEFGroup");
			//Abe20170609


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

			//Abe20170605
			//ポーズ作成
			CreatePause();
			//Abe20170605

			//Abe20170620
			//ブースト作成
			CreateBoost();
			//Abe20170620

			//2017/05/17今泉CSV//
			AddGameObject<InputCSV>();
			/////////////////////////

			//テスト(索敵サークル)
			//Abe20170523IzumiHikitugi
			//AddGameObject<SearchCircle>();
			//Abe20170523IzumiHikitugi

			//Abe20170602
			//auto ob = AddGameObject<BombEffect>();
			//ob->SetPosActive(Vector3(0, 5, 0));
			//ob->SetDrawLayer(10);
			//Abe20170602

			//Abe20170605
			//****でバック
			//AddGameObject<BakuSanObj>()->SetPosScaleVelo(Vector3(0, 5, 0), Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 10, 5));
			//Abe20170605

			//Abe20170606
			//*****デバック
			//AddGameObject<BakusanEF>()->SetPosScaActive(Vector3(0, 1, 0), Vector3(100, 100, 100));
			//Abe20170606

			//Abe20170609
			//*****デバック
			//AddGameObject<ShotEnemyChildMissile>(Vector3(0, 1, 0), Vector3(1, 1, 1), Vector3(0, 0, 0), Vector3(0, 0, 0));
			//AddGameObject<ButukariEf>()->SetPosScaActive(Vector3(0,5,0),Vector3(1,1,1));
			//Abe20170609

			//Abe20170612
			//シールド
			//SetSharedGameObject(L"Shield",AddGameObject<EnemyShield>(3, Vector3(0, 1, 0), Vector3(1, 1, 1), 1));
			//Abe20170612


			//Abe20170622
			//デバッグ文字生成
			auto obj = AddGameObject<DebugTxt>();
			obj->SetLayer(10);
			//色黒に変更
			obj->SetColor(Vector3(0, 0, 0));
			//大きさ変更
			obj->SetScaleTxt(40);
			SetSharedGameObject(L"DebugTxt", obj);
			//Abe20170622


			//Abe20170627
			//コンボ
			auto combop = AddGameObject<ComboBonus>();
			GetSharedObjectGroup(L"UgokuGroup")->IntoGroup(combop);
			SetSharedGameObject(L"ComboBonus",combop);
			//Abe20170627


			//展示用、放置するとタイトルに戻るやつ
			AddGameObject<TenziTitle>();
		}
		catch (...) {



			throw;
		}
		m_WinBgm = true;
	}



	// 更新
	// シーン遷移
	void GameStage::OnUpdate()
	{
		if (m_WinBgm == false) {
			m_CuntTaime += App::GetApp()->GetElapsedTime();
			if (m_CuntTaime > 7) {
				m_AudioObjectPtr->Start(L"WinBgm_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
				m_CuntTaime = 0.0f;
				m_WinBgm = true;
			}
		}

		//Abe20170622
		//ショットエネミーのクールタイム一覧
		/*
		wstring txtes;
		for (auto obj : GetSharedObjectGroup(L"EnemyGroup", false)->GetGroupVector())
		{
			auto ptr = dynamic_pointer_cast<ShotEnemy>(obj.lock());
			if (ptr)
			{
				txtes += L"CT:" + Util::FloatToWStr(ptr->GetCoolTime()) + L"\n";
			}
		}
		GetSharedGameObject<DebugTxt>(L"DebugTxt", false)->SetText(txtes);
		*/
		//Abe20170622

		//Abe20170609
		//始まり演出
		if (!GetSharedGameObject<StartState>(L"StartState", false))
		{
			SetSharedGameObject(L"StartState",AddGameObject<StartState>());
			return;
		}
		//Abe20170609


		auto PlayerLifePtr = GetSharedGameObject<Player_Life>(L"Life", false);
		if (PlayerLifePtr) {
			if (PlayerLifePtr->GetDieFlg() == false) {
				if (StopBGM == true) {
					m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
					StopBGM = false;
				}
			}
		}

		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//**********************
			//コマンド
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK && CntlVec[0].wButtons & XINPUT_GAMEPAD_START)
			{
				//シーンタイトル
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
			}
			//**********************

			//STARTボタンでポーズ
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && !GetSharedGameObject<GameObject>(L"ResultS", false)
				&& !GetSharedGameObject<GameObject>(L"GameOverS", false)
				&& GetSharedGameObject<StartState>(L"StartState",false)->GetFinish())
			{
				if (GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->GetPushFlg())
				{
					GetSharedGameObject<SE>(L"TitleSE", false)->PauseSe();

					//ポーズ表示
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Open();

					//バグ回避用
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->SetPushFlg(false);
				}
				else
				{
					GetSharedGameObject<SE>(L"TitleSE", false)->PauseSe();

					//ポーズ表示
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Close();

					//バグ回避用
					GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->SetPushFlg(true);

				}
			}
		}

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

			//Abe2010612
			//デバッグシールド減らす
			//GetSharedGameObject<EnemyShield>(L"Shield")->Damage(10);
			//Abe2010612
			//破片
			//GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(20, Vector3(0, 0.5f, -3));

			//ポーズ表示
		//	GetSharedGameObject<PauseMenu>(L"PauseMenu", false)->Open();
		}

		//Abe20170531
		//仮でリザルト表示**********デバッグ*********
		if (KeylVec.m_bPressedKeyTbl['B'])
		{
			Result();
		}
		//仮でリザルト表示**********デバッグ*********

		//Abe20170627
		if (KeylVec.m_bPressedKeyTbl[VK_UP])
		{
			GetSharedGameObject<ComboBonus>(L"ComboBonus", false)->CountUp();
		}
		//Abe20170627


		//Abe20170531

		if (m_CameraMoveFlg)
		{
			//カメラ更新
			UpdateCamera();
		}
		//ダメージ受けてるとき
		if (m_DamageFlg)
		{
			//ダメージカメラ
			DamageCamera();
		}
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
		auto  Player = GetSharedGameObject<PlayerControl>(L"PlayerControl", false);
		
		vector<Vector3> PlayerPos = Player->GetPlayerSPos_RETURNvectorVec3();
		//見る点をプレイヤー間の中心
		At = (PlayerPos[0] + PlayerPos[1]) / 2;
		//座標をちょっと手前上
		Pos = At;
		//距離を測る
		Vector3 def = PlayerPos[0] - PlayerPos[1];
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
		if (StopBGM == true) {
			m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
		}
		if (m_WinBgm == true) {
			m_AudioObjectPtr->Stop(L"WinBgm_BGM");

		}
	}

	//Abe20170529
	//ゲームオーバー処理
	void GameStage::GameOver()
	{
		auto ptr = GetSharedGameObject<GameObject>(L"ResultS", false);
		auto ptr2 = GetSharedGameObject<GameObject>(L"GameOverS", false);
		if (!ptr && !ptr2)
		{
			SetSharedGameObject(L"GameOverS",AddGameObject<GameOverS>());

			GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
			GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
		
			
		}
	}
	//Abe20170529

	//Abe20170530
	//ゲームオーバー処理カメラ
	bool GameStage::GameOverCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//座標
		Vector3 Pos = CameraP->GetEye();
		//見る部分
		Vector3 At = CameraP->GetAt();

		//移動
		Vector3 targetpos = Vector3(0, 15, -5);
		Vector3 dis = targetpos - Pos;
		dis /= 10;
		Pos += dis;

		At = Pos + Vector3(0, -5, 5);

		//カメラ移動
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);

		if (abs(targetpos.x - Pos.x) + abs(targetpos.y - Pos.y) + abs(targetpos.z - Pos.z) < 0.1f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//Abe20170530

	//Abe20170531
	//リザルト処理
	void GameStage::Result()
	{
		auto ptr = GetSharedGameObject<GameObject>(L"ResultS", false);
		auto ptr2 = GetSharedGameObject<GameObject>(L"GameOverS", false);
		if (!ptr && !ptr2)
		{
			SetSharedGameObject(L"ResultS", AddGameObject<ResultS>());

			GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
			GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
			m_AudioObjectPtr->Stop(L"GameStage_01_BGM");
			m_AudioObjectPtr->Start(L"Win_SE", 0, 0.5f);
			m_WinBgm = false;
		}
		
	}
	
	//リザルトカメラ制御
	bool GameStage::ResultCamera(Vector3 pos)
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//座標
		Vector3 Pos = CameraP->GetEye();
		//見る部分
		Vector3 At = CameraP->GetAt();

		//移動
		Vector3 targetpos = pos;
		//ちょっと後ろ上にずらす
		targetpos += Vector3(0, 2, -8);
		Vector3 dis = targetpos - Pos;
		dis /= 10;
		Pos += dis;

		//Atも移動、移動先は(プレイヤーの中心)
		Vector3 targetAt = pos;
		//ちょっとずらす
		targetAt += Vector3(0, 1, 0);
		Vector3 disAt = targetAt - At;
		disAt /= 10;
		At += disAt;

		//目標地点に近ければtrueを返して遠ければカメラを移動してfalseを返す
		if (abs(targetpos.x - Pos.x) + abs(targetpos.y - Pos.y) + abs(targetpos.z - Pos.z) < 0.1f)
		{
			return true;
		}
		else
		{
			//カメラ移動
			CameraP->SetEye(Pos);
			CameraP->SetAt(At);

			return false;
		}

	}
	//Abe20170531

	//Abe20170612
	//ダメージカメラ演出
	void GameStage::DamageCamera()
	{
		m_CameraMoveFlg = false;

		m_damageTime += App::GetApp()->GetElapsedTime();
		if (m_damageTime > m_damageinterval)
		{
			//計算用時間
			m_damageTime = 0;

			//揺らすカウント
			m_damageCameraCount++;

			//カメラ揺らす
			auto View = GetView();
			auto CameraP = View->GetTargetCamera();
			//座標
			Vector3 pos = CameraP->GetEye();
			Vector3 at = CameraP->GetAt();

			Vector3 randvec3 = Vector3((rand() % 30 - 15) / 10, 0, (rand() % 30 - 15) / 10);
			pos += randvec3;
			at += randvec3;

			//カメラ移動
			CameraP->SetEye(pos);
			CameraP->SetAt(at);

			//指定回数分回ったら
			if (m_damageCameraCount >= 5)
			{
				m_DamageFlg = false;
				m_damageCameraCount = 0;
				m_CameraMoveFlg = true;

			}
		}
		else if (m_damageTime > m_damageinterval/2)
		{
			m_CameraMoveFlg = true;
		}
	}
	//Abe20170612

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
		PtrDraw->SetDepthStencilState(DepthStencilState::Read);
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		if (m_TX_Name == L"Background_TX") {
			PtrDraw->SetTextureResource(m_TX_Name);
			PtrDraw->SetDiffuse(Color4(1, 1, 1, 0.7));
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
		//SetDrawLayer(10);
	}
}

//end basecross
