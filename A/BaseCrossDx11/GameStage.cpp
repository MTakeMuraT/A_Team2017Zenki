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
			Vector3(0, 1, 0)
			);
		SetSharedGameObject(L"GamePlayer", PtrPlayer_L);
		auto PtrPlayer_R = AddGameObject<Player_Second>(
			Vector3(5, 1, 0)
			);
		SetSharedGameObject(L"GamePlayer_R", PtrPlayer_R);
	}

	//実装したものをテストする時に使用
	void GameStage::CreateTestLin() {
		AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, -5),
			wstring(L"TRACE_TX")
			);
		/*AddGameObject<FixdBox>(
			Vector3(1, 1, 1),
			Vector3(0, 0, 0),
			Vector3(0, 1, 5),
			wstring(L"TRACE_TX")
			);*/
	}

	void GameStage::OnCreate()
	{
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePlate();
			CreatePlayerLin();
			CreateGround();
			CreateTestLin();
			//背景の作成
			CreateBackGround();


			//Abe20170412
			//エネミー作ってみた
			AddGameObject<Enemy01>(Vector3(0, 1, 5), Vector3(1, 1, 1));
			//Abe20170412

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
		Vector3 Player1Pos = GetSharedGameObject<Player>(L"GamePlayer", false)->GetComponent<Transform>()->GetPosition();
		Vector3 Player2Pos = GetSharedGameObject<Player_Second>(L"GamePlayer_R", false)->GetComponent<Transform>()->GetPosition();

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
		Pos.y = Yup;
		//同じ値をZにも
		Pos.z = -Yup;

		//カメラ更新
		CameraP->SetEye(Pos);
		CameraP->SetAt(At);
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
		PtrDraw->SetTextureResource(m_TX_Name);


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

	}

}
//end basecross
