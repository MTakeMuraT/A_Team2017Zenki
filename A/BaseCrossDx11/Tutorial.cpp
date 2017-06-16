#include "stdafx.h"
#include "Project.h"

//*******************************************
//　作成開始日 2017 / 06 / 15
//	土台作成者	Abe
//	ひとこと：ようじょぺろぺろ
//*******************************************

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	//ビューとライトの作成
	void TutorialScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定(カメラ固定)
		auto PtrCamera = PtrView->GetCamera();
		PtrCamera->SetEye(Vector3(0.0f, 5.0f, -5.0f));
		PtrCamera->SetAt(Vector3(0.0f, 0.0f, 0.0f));

		//シングルライトの作成
		auto PtrSingleLight = CreateLight<SingleLight>();
		//ライトの設定
		PtrSingleLight->GetLight().SetPositionToDirectional(-0.25f, 1.0f, -0.25f);

	}

	//地面作成
	void TutorialScene::CreateGround()
	{
		auto obj = AddGameObject<Ground_GameStage>(Vector3(75,75, 1),Vector3(0, 0, 0),wstring(L"Glass_TX"));
		obj->SetDrawLayer(0);
	}

	//プレイヤー作成
	void TutorialScene::CreatePlayer()
	{
		auto obj = AddGameObject<TutorialPlayerS>();
		SetSharedGameObject(L"TutorialPlayerS", obj);
	}

	//移動ターゲット作成
	void TutorialScene::CreateMoveTarget()
	{
		auto obj = AddGameObject<MoveTarget>();
		SetSharedGameObject(L"MoveTarget", obj);
	}

	//回転時間計測オブジェクト作成
	void TutorialScene::CreateRotCount()
	{
		auto obj = AddGameObject<TutorialRotFixed>();
		SetSharedGameObject(L"TutorialRotFixed", obj);
	}

	//スプライトを作成
	void TutorialScene::CreateSpriteS()
	{
		auto obj = AddGameObject<TutorialSpriteS>();
		SetSharedGameObject(L"TutorialSpriteS", obj);
	}

	//エネミー作成
	void TutorialScene::CreateEnemy()
	{
		for (int i = 0; i < 3; i++)
		{
			auto obj = AddGameObject<TutorialEnemy>();
			switch (i)
			{
			case 0:
				obj->SetPos(Vector3(0, -2, 10));
				break;
			case 1:
				obj->SetPos(Vector3(5, -2, -5));
				break;
			case 2:
				obj->SetPos(Vector3(-3, -2, -5));
				break;
			}
			GetSharedObjectGroup(L"TutorialEnemyGroup")->IntoGroup(obj);
		}

		//ついでに破片とかのマネージャー作っとく
		SetSharedGameObject(L"BakuSanSpawn",AddGameObject<BakuSanSpawn>());
	}

	void TutorialScene::OnCreate()
	{
		try 
		{
			//ビューとライトの作成
			CreateViewLight();
			//地面作成
			CreateGround();
			//プレイヤー作成
			CreatePlayer();
			//移動ターゲット作成
			CreateMoveTarget();
			//回転計測オブジェクト作成
			CreateRotCount();
			//スプライトたちを作成
			CreateSpriteS();

			//エネミーのグループ作成
			CreateSharedObjectGroup(L"TutorialEnemyGroup");
			//爆発エフェクトグループ
			CreateSharedObjectGroup(L"BakusanEFGroup");
			//爆散オブジェクト
			CreateSharedObjectGroup(L"BakusanObjGroup");
			
			//エネミー作成
			CreateEnemy();

			//カメラ更新
			m_CameraMoveFlg = true;

			m_EnemyFlg = false;
		}

		catch (...) {
			throw;
		}
	}

	void TutorialScene::OnUpdate()
	{
		if (m_CameraMoveFlg)
		{
			//カメラ更新
			UpdateCamera();
		}

		//デバック********************************
		//キーの入力
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();

			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTutorial");
		}

		if (m_EnemyFlg)
		{
			//エネミーの数数えていなくなったら演出起動
			int count = 0;
			for (auto obj : GetSharedObjectGroup(L"TutorialEnemyGroup")->GetGroupVector())
			{
				if (dynamic_pointer_cast<GameObject>(obj.lock())->GetDrawActive())
				{
					count++;
				}
			}
			if (count == 0 && !GetSharedGameObject<ResultS>(L"Result",false))
			{
				SetSharedGameObject(L"Result",AddGameObject<ResultS>(true));
			}
		}
	}

	//破棄
	TutorialScene::~TutorialScene() 
	{

	}

	//カメラ更新
	void TutorialScene::UpdateCamera()
	{
		auto View = GetView();
		auto CameraP = View->GetTargetCamera();
		//座標
		Vector3 Pos = CameraP->GetEye();
		//見る部分
		Vector3 At = CameraP->GetAt();


		//２体の座標もらう
		auto PlaPtr = GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS",false);
		vector<Vector3> PlayerPosS = PlaPtr->GetPlayerSPos_RETURNvectorVec3();

		//見る点をプレイヤー間の中心
		At = (PlayerPosS[0] + PlayerPosS[1]) / 2;
		//座標をちょっと手前上
		Pos = At;
		//距離を測る
		Vector3 def = PlayerPosS[1] - PlayerPosS[0];
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

	//リザルトカメラ制御
	bool TutorialScene::ResultCamera(Vector3 pos)
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

	//--------------------------------------------------------------------------------------
	//	こっから下は専用のオブジェクトだぜぇ～？
	//--------------------------------------------------------------------------------------

	//**************************************************************************************
	//**************************************************************************************

#pragma region TutorialPlayerS

	//**************************************************************************************
	//	[TutorialPlayerS]
	//	チュートリアル専用のプレイヤー、操作制限機能つき
	//	ヘッダーで値設定してもバグルのでクリエイトで設定するわ
	//	ちな、このオブジェクトは中心座標で周りのプレイヤーは見た目だけ
	//**************************************************************************************
	void TutorialPlayerS::OnCreate()
	{
		//-----------------------------
		//初期化

		//-----------------------
		//パラメータ類
		//-----------------------
		//プレイヤー同士の距離
		m_PlayerSDistance = 4.0f;
		//初期値
		m_PlayerSDistanceInit = 4.0f;
		//制限
		m_PlayerSDistanceLimit = 15.0f;
		//離れる速度
		m_DistanceSpeed = 40.0f;
		//くっつく速度
		m_KuttukuSpeed = 20.0f;
		//角度
		m_rot = 0;
		//回転速度
		m_rotSpeed = 90.0f;
		//速度
		m_Speed = 20.0f;
		//-----------------------
		//制御系
		//-----------------------
		m_moveFlg = true;
		m_rotFlg = false;
		m_AButtonFlg = false;

		m_DontMoveFlg2 = false;
		//-----------------------------

		for (int i = 0; i < 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(0, 0.5f, 0);
			Trans->SetScale(1, 1, 1);
			Trans->SetRotation(0, 3.14159265f/ 180 * 180 * (1-i), 0);

			//モデルとトランスフォームの間の差分
			Matrix4X4 PlayerMat;
			PlayerMat.DefTransformation(
				Vector3(1.0, 1.0f, 1.0f),
				Vector3(0, -90 * 3.14159265f/180, 0),
				Vector3(0.0f, 0.0f, 0.0f)
				);

			auto Draw = obj->AddComponent<PNTBoneModelDraw>();
			Draw->SetMeshResource(L"Player_Model");
			Draw->SetMeshToTransformMatrix(PlayerMat);

			//アニメーション
			Draw->AddAnimation(L"AllAnima", 0, 150, 30.0f);
			Draw->AddAnimation(L"Wait", 0, 30, true, 30.0f);
			Draw->AddAnimation(L"Damage", 30, 30, false, 30.0f);
			Draw->AddAnimation(L"LeftRot", 80, 15, false, 30.0f);
			//Draw->AddAnimation(L"LeftReturn", 95,20,false,30.0f);
			Draw->AddAnimation(L"RightRot", 120, 15, false, 30.0f);
			//Draw->AddAnimation(L"RightReturn",135,15,false,30.0f);

			//アニメーション設定
			m_NowAnimName = "None";
			m_ChangeAnimName = "Wait";

			obj->SetAlphaActive(true);
			obj->SetDrawLayer(3);

			if (i == 0)
			{
				GetStage()->SetSharedGameObject(L"GamePlayer_R", obj);

				m_Player1 = obj;

			}
			else
			{
				GetStage()->SetSharedGameObject(L"GamePlayer_L", obj);

				m_Player2 = obj;
			}
		}

		//黒幕作成-----------------------------------------
		auto blackobj = GetStage()->AddGameObject<GameObject>();
		auto TransBla = blackobj->AddComponent<Transform>();
		TransBla->SetPosition(0, 0, 0);
		TransBla->SetRotation(0, 0, 0);
		TransBla->SetScale(1280, 720, 1);

		auto DrawBla = blackobj->AddComponent<PCTSpriteDraw>();
		DrawBla->SetTextureResource(L"OVERBLACK_TX");
		DrawBla->SetDiffuse(Color4(1, 1, 1, 0));

		blackobj->SetAlphaActive(true);
		blackobj->SetDrawLayer(5);

		m_BlackSprite = blackobj;


	}

	void TutorialPlayerS::OnUpdate()
	{
		//アニメーション更新
		UpdateAnimation();

		if (m_DontMoveFlg2)
		{
			return;
		}
		//暗転中は動かせない
		if (m_DontMoveFlg)
		{
			BlackUpdate();
			return;
		}

		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//移動------------------------------------------------------------
			if (m_moveFlg)
			{
				if (abs(CntlVec[0].fThumbLX) + abs(CntlVec[0].fThumbLY) >= 0.2f)
				{
					Vector3 InputXY = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					pos += InputXY * App::GetApp()->GetElapsedTime() * m_Speed;
					GetComponent<Transform>()->SetPosition(pos);
					//慣性更新
					m_Kansei = InputXY;
				}
				else
				{
					//入力なければ完成で流す
					if (abs(m_Kansei.x) + abs(m_Kansei.z) >= 0.2f)
					{
						Vector3 pos = GetComponent<Transform>()->GetPosition();
						pos += m_Kansei * App::GetApp()->GetElapsedTime() * m_Speed;
						GetComponent<Transform>()->SetPosition(pos);
						//減衰
						m_Kansei *= 0.90f;
					}
					else if (m_Kansei.x != 0)
					{
						m_Kansei = Vector3(0, 0, 0);
					}
				}
			}
			//離れる--------------------------------------------------------
			if (m_AButtonFlg)
			{
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A)
				{
					m_PlayerSDistance += App::GetApp()->GetElapsedTime() * m_DistanceSpeed;
					if (m_PlayerSDistance > m_PlayerSDistanceLimit)
					{
						m_PlayerSDistance = m_PlayerSDistanceLimit;
					}
				}
				else if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					//移動制限
					m_moveFlg = false;
					//離れる制限
					m_AButtonFlg = false;
					//回転制限
					m_rotFlg = false;
					//くっつくON
					m_KuttukuFlg = true;
					//一応戻るOFF
					m_KuttukuAfterFlg = false;
					//くっつく速度初期化
					m_KuttukuSpeed = 20.0f;
				}
			}
			//くっつく
			else if(m_KuttukuFlg)
			{
				//くっつける
				m_PlayerSDistance += -m_KuttukuSpeed * App::GetApp()->GetElapsedTime();
				//速度上げる
				m_KuttukuSpeed *= 1.1f;

				//くっついたら
				if (m_PlayerSDistance < 1.0f)
				{
					//くっつくOFF
					m_KuttukuFlg = false;
					//戻るON
					m_KuttukuAfterFlg = true;
				}
			}
			//離す処理
			else if (m_KuttukuAfterFlg)
			{
				//離す
				m_PlayerSDistance += m_DistanceSpeed * App::GetApp()->GetElapsedTime();
				if (m_PlayerSDistance > m_PlayerSDistanceInit)
				{
					//距離を戻す
					m_PlayerSDistance = m_PlayerSDistanceInit;
					//移動解除
					m_moveFlg = true;
					//離れる解除
					m_AButtonFlg = true;
					//回転解除
					m_rotFlg = true;
					//戻る解除
					m_KuttukuAfterFlg = false;
				}
			}
			//回転--------------------------------------------------
			if (m_rotFlg)
			{
				//左回転
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					m_rot += -m_rotSpeed * App::GetApp()->GetElapsedTime();
					//一応ループさせとく
					if (m_rot < 0)
					{
						m_rot = 360;
					}
				}
				//右回転
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					m_rot += m_rotSpeed * App::GetApp()->GetElapsedTime();
					//一応ループさせとく
					if (m_rot > 360)
					{
						m_rot = 0;
					}
				}
			}
		}
		

		//プレイヤーの位置と回転更新
		PosRotUpdate();
		//ステージの外に行こうとしたら戻す
		CheckStageEnd();
		
	}

	//----------------------------------------------
	//関数
	//----------------------------------------------
	//プレイヤー位置回転更新
	void TutorialPlayerS::PosRotUpdate()
	{
		//右が0で左が1
		Vector3 posright = GetComponent<Transform>()->GetPosition();
		posright += Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player1->GetComponent<Transform>()->SetPosition(posright);

		//左位置決定
		Vector3 porleft = GetComponent<Transform>()->GetPosition();
		porleft += -Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player2->GetComponent<Transform>()->SetPosition(porleft);

		//右回転更新
		//座標取得
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		
		//差計算
		Vector3 dis1 = pos2 - pos1;
		Vector3 dis2 = pos1 - pos2;

		//角度計算
		float angle1 = atan2(dis1.z, dis1.x);
		float angle2 = atan2(dis2.z, dis2.x);

		m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
		m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
	}

	//ステージの外に行こうとしたら戻す判定
	void TutorialPlayerS::CheckStageEnd()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		if (abs(pos.x) > 30 || abs(pos.z) > 30)
		{
			m_DontMoveFlg = true;
			m_BlackAlpha = 0;
			m_BlackAlphaFlg = false;
		}
	}

	void TutorialPlayerS::BlackUpdate()
	{
		if (!m_BlackAlphaFlg)
		{
			m_BlackAlpha += App::GetApp()->GetElapsedTime();
			m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
			if (m_BlackAlpha > 1.0f)
			{
				m_BlackAlphaFlg = true;

				//座標更新
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos = Vector3(0, 0, 0);
				GetComponent<Transform>()->SetPosition(pos);
				m_rot = 0;
				m_Kansei = Vector3(0, 0, 0);
				//プレイヤーの位置と回転更新
				PosRotUpdate();

			}
		}
		else
		{
			m_BlackAlpha += -App::GetApp()->GetElapsedTime();
			m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
			if (m_BlackAlpha < 0)
			{
				m_BlackAlphaFlg = false;
				m_DontMoveFlg = false;
			}
		}
	}

	//アニメーション更新
	void TutorialPlayerS::UpdateAnimation()
	{
		if (m_NowAnimName == m_ChangeAnimName)
		{
			m_Player1->GetComponent<PNTBoneModelDraw>()->UpdateAnimation(App::GetApp()->GetElapsedTime());
			m_Player2->GetComponent<PNTBoneModelDraw>()->UpdateAnimation(App::GetApp()->GetElapsedTime());

		}
		else
		{
			if (m_ChangeAnimName == "Wait")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"Wait");
			}
			if (m_ChangeAnimName == "LeftRot")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"LeftRot");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"LeftRot");
			}
			if (m_ChangeAnimName == "RightRot")
			{
				m_Player1->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"RightRot");
				m_Player2->GetComponent<PNTBoneModelDraw>()->ChangeCurrentAnimation(L"RightRot");
			}
			m_NowAnimName = m_ChangeAnimName;
		}
	}

	//----------------------------------------------
	//その他(アクセサーとか)
	//----------------------------------------------
	//二体の座標をvectorコンテナで渡す
	vector<Vector3> TutorialPlayerS::GetPlayerSPos_RETURNvectorVec3()
	{
		vector<Vector3> vec3;
		vec3.push_back(m_Player1->GetComponent<Transform>()->GetPosition());
		vec3.push_back(m_Player2->GetComponent<Transform>()->GetPosition());
		return vec3;
	}
#pragma endregion

#pragma region MoveTarget
	//**************************************************************************************
	//	移動ターゲット
	//	物だけ
	//**************************************************************************************
	void MoveTarget::OnCreate()
	{
		auto TransTar = AddComponent<Transform>();
		TransTar->SetPosition(0, 0.2f, 10);
		TransTar->SetRotation(90 * 3.14159265f / 180, 0, 0);
		TransTar->SetScale(7, 7, 7);

		auto DrawTar = AddComponent<PNTStaticDraw>();
		DrawTar->SetMeshResource(L"DEFAULT_SQUARE");
		DrawTar->SetTextureResource(L"TUTORIALTARGET_TX");

		SetAlphaActive(true);
		SetDrawLayer(1);

		m_Alpha = 1;
		m_ActiveFlg = true;
	}

	void MoveTarget::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//透明に
			if (!m_AlphaFlg)
			{
				m_Alpha += -App::GetApp()->GetElapsedTime();
				if (m_Alpha < 0.5f)
				{
					m_Alpha = 0.5f;
					m_AlphaFlg = true;
				}
			}
			else
			{
				m_Alpha += App::GetApp()->GetElapsedTime();
				if (m_Alpha > 1.0f)
				{
					m_Alpha = 1.0f;
					m_AlphaFlg = false;
				}
			}
			GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));

			//プレイヤーがいるか判定
			Vector3 pos = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->GetComponent<Transform>()->GetPosition();
			////カメラの角度からちょっとずれてるのでその分修正
			Vector3 mypos = GetComponent<Transform>()->GetPosition();
			////mypos.x += 0.3f;
			//mypos.z += -0.8f;
			Vector3 dis = pos - mypos;

			if (abs(dis.x) + abs(dis.z) <= 1.0f)
			{
				//描画切る
				SetDrawActive(false);
				//プレイヤーの移動を制限、回転を解除
				auto pptr = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false);
				pptr->SetMoveCont(false);
				pptr->SetRotCont(true);

				//回転計測オブジェクト起動

				GetStage()->GetSharedGameObject<TutorialRotFixed>(L"TutorialRotFixed", false)->StartCount();

				//動きとめる
				m_ActiveFlg = false;
			}

		}
	}
#pragma endregion
	
#pragma region TutorialRotFixed
	//**************************************************************************************
	//	回転のみ使える状態の時
	//	ある程度回転したら解除
	//**************************************************************************************
	void TutorialRotFixed::OnCreate()
	{
		m_time = 0;
		m_LimitTime = 3.0f;
		m_StartFlg = false;
	}

	void TutorialRotFixed::OnUpdate()
	{
		if (m_StartFlg)
		{
			//コントローラ取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				//肩どっちか押されてたら計測
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER || CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_LimitTime)
					{
						//プレイヤーの移動と回転を制限、Aボタンを解除
						auto pptr = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false);
						pptr->SetMoveCont(false);
						pptr->SetRotCont(false);
						pptr->SetAbuttonCont(true);

						//エネミーを出す
						auto egv = GetStage()->GetSharedObjectGroup(L"TutorialEnemyGroup")->GetGroupVector();
						for (auto ob : egv)
						{
							auto ptr = dynamic_pointer_cast<TutorialEnemy>(ob.lock());
							if (ptr)
							{
								ptr->Up();
							}
						}
						//一応初期値に
						m_time = 0;
						m_StartFlg = false;
					}
				}
			}
		}
	}

	void TutorialRotFixed::StartCount()
	{
		m_StartFlg = true;
		//一応
		m_time = 0;
	}

#pragma endregion

#pragma region TutorialEnemy
	//**************************************************************************************
	//	的エネミー
	//	死ぬだけ
	//**************************************************************************************
	void TutorialEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0.5f, 10);
		Trans->SetScale(Vector3(1, 1, 1));
		Trans->SetRotation(0, 90*3.14159265f/180, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"TACKLE_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//アニメーション追加
		Draw->AddAnimation(L"Wait", 40, 30, true, 30);

		Draw->ChangeCurrentAnimation(L"Wait");

		//透明処理
		SetAlphaActive(true);

		//描画切っとく
		SetDrawActive(false);

		//下から出すフラグきっとく
		m_UpFlg = false;
		//挟まれる判定切っとく
		m_SandJudgeFlg = false;
	}

	void TutorialEnemy::OnUpdate()
	{
		if (m_UpFlg)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos.y += 10 * App::GetApp()->GetElapsedTime();
			if (pos.y > 0.5f)
			{
				m_UpFlg = false;
				m_SandJudgeFlg = true;
				pos.y = 0.5;
			}
			GetComponent<Transform>()->SetPosition(pos);
		}

		//挟まれる判定
		//プレイヤーが挟んだ時に呼ぶのがいいのだがアクセス系統を作るのが時間かかるので省略。そこまで重い処理にはならないはずだからとりあえずスルー
		if (m_SandJudgeFlg)
		{
			//プレイヤーに挟まれてるか
			Vector3 pos = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->GetComponent<Transform>()->GetPosition();
			Vector3 mypos = GetComponent<Transform>()->GetPosition();
			Vector3 dis = pos - mypos;

			//プレイヤー同士の距離でなんとかとる
			float pdistance = GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->GetDistance();

			//中心点の距離が自分とある程度近い　かつ　プレイヤー同士の距離が近いで判定
			if (abs(dis.x) + abs(dis.z) <= 1.0f && pdistance < 2.0f)
			{
				//描画消して判定けして位置を下にずらす
				SetDrawActive(false);
				m_SandJudgeFlg = false;
				//爆散作成
				GetStage()->GetSharedGameObject<BakuSanSpawn>(L"BakuSanSpawn", false)->CreateBakusan(rand() % 25 + 5, GetComponent<Transform>()->GetPosition());

				//爆散エフェクト作成
				for (int i = 0; i < 3; i++)
				{
					auto BakusanGroup = GetStage()->GetSharedObjectGroup(L"BakusanEFGroup")->GetGroupVector();
					bool bakuflg = false;
					for (auto obj : BakusanGroup)
					{
						auto ptr = dynamic_pointer_cast<BakusanEF>(obj.lock());
						if (!ptr->GetDrawActive())
						{
							bakuflg = true;
							ptr->SetPosScaActive(GetComponent<Transform>()->GetPosition(), GetComponent<Transform>()->GetScale());
						}
					}
					if (!bakuflg)
					{
						auto obj = GetStage()->AddGameObject<BakusanEF>();
						obj->SetPosScaActive(GetComponent<Transform>()->GetPosition(), GetComponent<Transform>()->GetScale());
						GetStage()->GetSharedObjectGroup(L"BakusanEFGroup")->IntoGroup(obj);
					}
				}

				mypos.y = -10;
				GetComponent<Transform>()->SetPosition(mypos);


				//エネミーの数数えさせる
				dynamic_pointer_cast<TutorialScene>(GetStage())->EnemyCountOn();
			}
		}
	}

	void TutorialEnemy::Up()
	{
		SetDrawActive(true);
		m_UpFlg = true;
	}

#pragma endregion

#pragma region TutorialSpriteS
	//**************************************************************************************
	//	スプライトたち
	//	状態変えて出す
	//　大体切り替えで２ステート使うのでNextState()で切り替えたときは２個進める
	//　ここもクリエイトで初期化
	//**************************************************************************************
	void TutorialSpriteS::OnCreate()
	{
		//-----------------------------
		//初期化

		//状態
		m_state = 0;
		//状態切り替え時
		m_ChangestateFlg = true;
		//時間計測用
		m_time = 0;
		//切り替え間隔
		m_IntervalTime = 1.0f;
		//-----------------------------
	}

	void TutorialSpriteS::OnUpdate()
	{
		switch (m_state)
		{
			//左スティックで移動
		case 0:
			if (true)
			{
				//初回
				if (m_ChangestateFlg)
				{

				}
			}
			break;
		case 1:
			if (true)
			{

			}
			break;

			//RB、LBで回転
		case 2:
			if (true)
			{
				//初回
				if (m_ChangestateFlg)
				{

				}

			}
			break;
		case 3:
			if (true)
			{

			}
			break;

			//Aボタンで離れる
		case 4:
			if (true)
			{
				//初回
				if (m_ChangestateFlg)
				{

				}

			}
			break;
		case 5:
			if (true)
			{

			}
			break;
		}
	}

	void TutorialSpriteS::NextSatte()
	{
		//まず偶数で計算
		int nowstate = m_state / 2;
		int nextstate = (nowstate+1) * 2;
		//------------------
		//例えば
		//0,1のループ2,3のループで設定してたら (0,1)/2 = 0 (2,3)/2 = 1
		//それに1足して2かければ (0+1)*2 = 2 (1+1)*2 = 4
		//次のループの状態にはいれるって寸法よ
		//------------------
		m_state = nextstate;

		m_ChangestateFlg = true;
	}

#pragma endregion
}