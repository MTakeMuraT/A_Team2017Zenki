/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void StageSelectScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 30.0f, -0.1f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//テスト表示
	void StageSelectScene::CreatTestLin() {
		AddGameObject<StageSelectSprite>(
			Vector2(1280, 720),
			Vector2(0, 0),
			0
			);
	}

	//Abe20170421
	//フレーム作成
	void StageSelectScene::CreateFlame()
	{
		AddGameObject<SelectFlame>(Vector2(0, 0), Vector2(1280, 720), 1);
	}

	//プレイヤー作成
	void StageSelectScene::CreatePlayer()
	{
		SetSharedGameObject(L"SelectPlayer", AddGameObject<SelectPlayer>(Vector3(0, 0.6f, 0), Vector3(1, 1, 1),20.0f));
	}

	//ステージボックス作成
	void StageSelectScene::CreateStageBox()
	{
		SetSharedGameObject(L"StageModeControl", AddGameObject<StageModeControl>());

		//計算めんどいので直打ち
		//１～４
		//AddGameObject<StageBox>(Vector3(-8, 0.5f, 5), Vector3(2, 2, 2), 1);
		//AddGameObject<StageBox>(Vector3(8, 0.5f, 5), Vector3(2, 2, 2), 2);
		//AddGameObject<StageBox>(Vector3(-8, 0.5f, -5), Vector3(2, 2, 2), 3);
		//AddGameObject<StageBox>(Vector3(8, 0.5f, -5), Vector3(2, 2, 2), 4);
		//
		////５～８
		//AddGameObject<StageBox>(Vector3(-8, 0.5f, -22), Vector3(2, 2, 2), 5);
		//AddGameObject<StageBox>(Vector3(8, 0.5f, -22), Vector3(2, 2, 2), 6);
		//AddGameObject<StageBox>(Vector3(-8, 0.5f, -32), Vector3(2, 2, 2), 7);
		//AddGameObject<StageBox>(Vector3(8, 0.5f, -32), Vector3(2, 2, 2), 8);
		//
		////９～１２
		//AddGameObject<StageBox>(Vector3(36, 0.5f, -22), Vector3(2, 2, 2), 9);
		//AddGameObject<StageBox>(Vector3(56, 0.5f, -22), Vector3(2, 2, 2), 10);
		//AddGameObject<StageBox>(Vector3(36, 0.5f, -32), Vector3(2, 2, 2), 11);
		//AddGameObject<StageBox>(Vector3(56, 0.5f, -32), Vector3(2, 2, 2), 12);
		//
		////１３～１６
		//AddGameObject<StageBox>(Vector3(36, 0.5f, 5), Vector3(2, 2, 2), 13);
		//AddGameObject<StageBox>(Vector3(56, 0.5f, 5), Vector3(2, 2, 2), 14);
		//AddGameObject<StageBox>(Vector3(36, 0.5f, -5), Vector3(2, 2, 2), 15);
		//AddGameObject<StageBox>(Vector3(56, 0.5f, -5), Vector3(2, 2, 2), 16);
		
	}

	//ステージの床作成
	void StageSelectScene::CreateStageUnder()
	{
		//地面作成
		//左上
		//AddGameObject<SelectGroud>(Vector3(0, -0.5, 0), Vector3(45, 1, 25));
		//左下
		//AddGameObject<SelectGroud>(Vector3(0, -0.5, -26), Vector3(45, 1, 25));
		//右下
		//AddGameObject<SelectGroud>(Vector3(46, -0.5, -26), Vector3(45, 1, 25));
		//右上
		//AddGameObject<SelectGroud>(Vector3(46, -0.5, 0), Vector3(45, 1, 25));
	}


	//ステージ行くかチェックするスプライト
	void StageSelectScene::CreateGoCheck()
	{
		SetSharedGameObject(L"GoStageCheck", AddGameObject<GoStageCheck>(Vector2(200, 200)));
	}
	//Abe20170421

	//Abe20170525
	//ステージロゴ作成
	void StageSelectScene::CreateStageLogo()
	{
		AddGameObject<SelectLogo>(Vector2(0,300),Vector2(800,120),3);
	}
	//Abe20170525

	//Abe20170526
	void StageSelectScene::CreateGroundSquareS()
	{
		//矢印
		////左上
		//AddGameObject<SelectGroundSquare>(Vector3(0, 0.5f, -10), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 270);
		//AddGameObject<SelectGroundSquare>(Vector3(18, 0.5f, 0), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 0);
		////左下
		//AddGameObject<SelectGroundSquare>(Vector3(0, 0.5f, -18), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 90);
		//AddGameObject<SelectGroundSquare>(Vector3(18, 0.5f, -27), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 0);
		////右下
		//AddGameObject<SelectGroundSquare>(Vector3(46, 0.5f, -18), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 90);
		//AddGameObject<SelectGroundSquare>(Vector3(28, 0.5f, -27), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 180);
		////右上
		//AddGameObject<SelectGroundSquare>(Vector3(46, 0.5f, -10), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 270);
		//AddGameObject<SelectGroundSquare>(Vector3(28, 0.5f, 0), Vector3(5, 5, 5), L"YAZIRUSHI_TX", 180);

		//Easy
		//AddGameObject<SelectGroundSquare>(Vector3(0, 0.5f, 0), Vector3(15, 10, 11), L"EASY_TX", 0);
		//Abe20170529
		//SS版
		//AddGameObject<SelectGroundSquareSS>(Vector3(0, 0.5f, 0), Vector3(1,1,1), L"SS\\EASY_animation\\", L"EASY.ssae", 0);

		//Abe20170529

		//Normal
		//AddGameObject<SelectGroundSquare>(Vector3(0, 0.5, -26), Vector3(15, 10, 11), L"NORMAL_TX", 0);
	//	AddGameObject<SelectGroundSquare>(Vector3(46, 0.5f, -26), Vector3(15, 10, 11), L"NORMAL_TX", 0);
		AddGameObject<SelectGroundSquareSS>(Vector3(0, 0.5f, -27), Vector3(1, 1, 1), L"SS\\NORMAL_animation\\", L"NORMAL.ssae", 0);
		AddGameObject<SelectGroundSquareSS>(Vector3(46, 0.5f, -27), Vector3(1, 1, 1), L"SS\\NORMAL_animation\\", L"NORMAL.ssae", 0);

		//Hard
	//	AddGameObject<SelectGroundSquare>(Vector3(46, 0.5f, 0), Vector3(15, 10, 11), L"HARD_TX", 0);
    	AddGameObject<SelectGroundSquareSS>(Vector3(46, 0.5f, 0), Vector3(1, 1, 1), L"SS\\HARD_animation\\", L"HARD.ssae", 0);

	}
	//Abe20170526


	void StageSelectScene::OnCreate()
	{
		try {
			////検証するのに重いので一時的に消します Abe20170505
			/*m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"StageSelect_01_BGM");
			m_AudioObjectPtr->Start(L"StageSelect_01_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);*/
			
			CreateViewLight();
			//CreatTestLin();
			//Abe20170421
			//フレーム作成
			CreateFlame();
			//プレイヤー作成
			CreatePlayer();
			//ステージボックス作成
			CreateStageBox();
			//ステージ行くかチェックするスプライト
			CreateGoCheck();
			//Abe20170421

			//Abe20170525
			//ステージロゴ作成
			CreateStageLogo();
			//Abe20170525

			//Abe20170524
			//ステージの床作成
			CreateStageUnder();

			//デバッグ文字生成
			auto debtxt = AddGameObject<DebugTxt>();
			debtxt->SetLayer(10);
			//色赤に変更
			debtxt->SetColor(Vector3(1, 0, 0));
			//大きさ変更
			debtxt->SetScaleTxt(40);

			m_Debugtxt = debtxt;
			//Abe20170524

			//Abe20170526
			//ステージの床に貼るやつ作成
			CreateGroundSquareS();
			//Abe20170526

			//Abe20170525確認用
			//AddGameObject<SpritePosScaleChecker>(Vector2(0,0),Vector2(100,100),5,L"TRACE_TX");
			//Abe20170525確認用
			auto PtrEnemyCount = AddGameObject<EnemyCount>();
			SetSharedGameObject(L"Count", PtrEnemyCount);

			//遷移アニメーション
			AddGameObject<SceneChangeSSOut>()->OnAnim();
		}

		catch (...) {

			throw;
		}
	}

	void StageSelectScene::OnUpdate() {
		//キーの入力
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			//ステージ番号を仮で１にしておく
			ScenePtr->SetStageNumAndStageSize(1, Vector2(50, 50));
			//なんかようわからんがバグ回避
			ScenePtr->SetCsvStageNum(L"1");
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
		}

		//**********************
		//コマンド
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].wButtons & XINPUT_GAMEPAD_BACK && CntlVec[0].wButtons & XINPUT_GAMEPAD_START)
		{
			//シーンタイトル
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
		}
		//**********************



		/*
		if (KeylVec.m_bPressedKeyTbl[VK_DOWN] && m_CameraNum != 1)
		{
			MoveCamera(1);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_UP] && m_CameraNum != 0)
		{
			MoveCamera(0);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_RIGHT] && m_CameraNum != 2)
		{
			MoveCamera(2);
		}
		if (KeylVec.m_bPressedKeyTbl[VK_LEFT] && m_CameraNum != 3)
		{
			MoveCamera(3);
		}
		*/
		//Abe20170427
		//カメラ移動
		//if (m_moveCameraFlg)
		//{
		//	//CameraMove();
		//}
		//else
		//{
		//	//プレイヤー座標取得
		//	auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
		//	Vector3 ppos = pptr->GetPos();

		//	//左上に移動
		//	//範囲(X[-26~26]Y[16~-16])
		//	if ((ppos.x > -26 && ppos.x < 26) && (ppos.z > -16 && ppos.z < 16) && m_CameraNum != 0)
		//	{
		//		MoveCamera(0);
		//		m_CameraNum = 0;
		//	}
		//	//左下に移動
		//	//範囲(X[-26~26]Y[-10~-33])
		//	else if ((ppos.x > -26 && ppos.x < 26) && (ppos.z > -33 && ppos.z < -10) && m_CameraNum != 1)
		//	{
		//		MoveCamera(1);
		//		m_CameraNum = 1;
		//	}

		//	//右上に移動
		//	//範囲(X[18~63]Y[16~-16])
		//	else if ((ppos.x > 18 && ppos.x < 63) && (ppos.z > -16 && ppos.z < 16) && m_CameraNum != 2)
		//	{
		//		MoveCamera(2);
		//		m_CameraNum = 2;
		//	}

		//	//右下に移動
		//	//範囲(X[18~63]Y[-10~-33])
		//	else if ((ppos.x > 18 && ppos.x < 63) && (ppos.z > -33 && ppos.z < -10) && m_CameraNum != 3)
		//	{
		//		MoveCamera(3);
		//		m_CameraNum = 3;
		//	}

		//}

		//Abe20170524
		/*カメラ座標確認用*/
		//wstring txt;
		//txt += Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_UP]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_RIGHT]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_DOWN]) + L"," + Util::FloatToWStr(KeylVec.m_bPushKeyTbl[VK_LEFT]);
		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		//Vector2 InputXY = Vector2((KeylVec.m_bPushKeyTbl[VK_RIGHT] + -KeylVec.m_bPushKeyTbl[VK_LEFT]), (KeylVec.m_bPushKeyTbl[VK_UP] + -KeylVec.m_bPushKeyTbl[VK_DOWN]));
		//auto View = GetView();
		//auto CameraP = View->GetTargetCamera();
		//m_CameraPos = CameraP->GetEye();
		//m_CameraAt = CameraP->GetAt();
		//m_CameraPos += Vector3(InputXY.x, 0, InputXY.y);
		//m_CameraAt += Vector3(InputXY.x, 0, InputXY.y);
		//CameraP->SetEye(m_CameraPos);
		//CameraP->SetAt(m_CameraAt);
		//Abe20170524
		
		//wstring txt;
		//txt += L"X:" + Util::FloatToWStr(m_CameraPos.x) + L"Z:" + Util::FloatToWStr(m_CameraPos.z);
		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		
		//Abe20170427
	}

	//Abe20170427
	//カメラ移動関数
	void StageSelectScene::CameraMove()
	{
		//Abe20170524	
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();

		//目標地点との距離を測って近くなければ近づけてく
		Vector3 dis = m_CameraMoveTarget - m_CameraPos;
		if (abs(dis.x) + abs(dis.z) > 1.0f)
		{
			//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(Util::FloatToWStr(abs(dis.x) + abs(dis.z)));

			dis /= 15;
			m_CameraPos += dis;
			m_CameraAt += dis;
			CameraP->SetEye(m_CameraPos);
			CameraP->SetAt(m_CameraAt);
		}
		else
		{
			//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(L"end");

			//移動停止
			m_moveCameraFlg = false;
			//座標固定
			m_CameraPos = m_CameraMoveTarget;

			//プレイヤー動けるように(ていうかアタリ判定戻す)
			auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
			//pptr->ActiveMove();
			return;
		}

		//プレイヤー移動
		auto pptr = GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false);
		Vector3 ppos = pptr->GetPos();
		//移動
		Vector3 dis2 = m_CameraMovePlayerTargetPos - ppos;
		if (abs(dis2.x) + abs(dis2.z) > 1.0f)
		{
			dis2 /= 5;
			ppos += dis2;
			pptr->SetPos(ppos);
		}
		else
		{
			ppos = m_CameraMovePlayerTargetPos;
			pptr->SetPos(ppos);
		}

		//Abe20170524
	}

	void StageSelectScene::MoveCamera(int num)
	{
		//Z:26 X:46

		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//ターゲット設定
		m_CameraPos = CameraP->GetEye();
		m_CameraAt = CameraP->GetAt();
		//Abe20170524
		//カメラ移動0：左上に　1：左下に　2：右上に　3：右下に
		switch (num)
		{
		case 0:
			m_CameraMoveTarget = Vector3(0, 30, -0.1f);
			m_CameraMovePlayerTargetPos = Vector3(0, 0, 0);
			break;
		case 1:
			m_CameraMoveTarget = Vector3(0, 30, -27.1f);
			m_CameraMovePlayerTargetPos = Vector3(0, 0, -27);
			break;
		case 2:
			m_CameraMoveTarget = Vector3(46, 30, -0.1f);
			m_CameraMovePlayerTargetPos = Vector3(46, 0, 0);
			break;
		case 3:		
			m_CameraMoveTarget = Vector3(46, 30, -27.1f);
			m_CameraMovePlayerTargetPos = Vector3(46, 0, -27);
			break;
		}
		//移動フラグを立てる
		m_moveCameraFlg = true;
		//Abe20170524
	}
	//Abe20170427

	 StageSelectScene::~StageSelectScene() {
		//m_AudioObjectPtr->Stop(L"StageSelect_01_BGM");
	}
}
//end basecross
