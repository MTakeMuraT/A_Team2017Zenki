/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class PlayerControl : public GameObject;
	//	用途: プレイヤーコントローラー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	void PlayerControl::OnCreate()
	{
		//-----------------------------
		//初期化

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);


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
		m_rotFlg = true;
		m_AButtonFlg = true;

		m_DontMoveFlg2 = false;
		//-----------------------------

		//座標設定
		auto trans = AddComponent<Transform>();
		trans->SetPosition(0, 1.0f, 0);
		trans->SetScale(0, 0, 0);
		trans->SetRotation(0, 0, 0);

		for (int i = 0; i < 2; i++)
		{
			auto obj = GetStage()->AddGameObject<GameObject>();
			auto Trans = obj->AddComponent<Transform>();
			Trans->SetPosition(0, 1.0f, 0);
			Trans->SetScale(1, 1, 1);
			Trans->SetRotation(0, 3.14159265f / 180 * 180 * (1 - i), 0);

			//モデルとトランスフォームの間の差分
			Matrix4X4 PlayerMat;
			PlayerMat.DefTransformation(
				Vector3(1.0, 1.0f, 1.0f),
				Vector3(0, -90 * 3.14159265f / 180, 0),
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
			//ステージの大きさ
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			m_StageSize = ScenePtr->GetStageSize() / 2;


			//Abe20170626
			//ターゲットリング作成
			auto tarobj = GetStage()->AddGameObject<GameObject>();
			auto tarTra = tarobj->AddComponent<Transform>();
			tarTra->SetPosition(0, 0.9f, 0);
			tarTra->SetRotation(45*3.14159265f/180, 0, 0);
			tarTra->SetScale(3.0f, 3.0f, 3.0f);

			auto tarDra = tarobj->AddComponent<PNTStaticDraw>();
			tarDra->SetTextureResource(L"TARGETRING_TX");
			tarDra->SetMeshResource(L"DEFAULT_SQUARE");

			tarobj->SetAlphaActive(true);
			tarobj->SetDrawLayer(false);
			tarobj->SetDrawActive(false);

			m_TargetRing = tarobj;
			//Abe20170626

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

		//しーるど生成
		GetStage()->AddGameObject<PlayerShield>(Vector3(0, 0, 0),
		Vector3(2,2,2),
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L", false));
		GetStage()->AddGameObject<PlayerShield>(Vector3(0, 0, 0),
			Vector3(2,2,2),
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R", false));
	}

	void PlayerControl::OnUpdate()
	{
		//アニメーション更新
		UpdateAnimation();

		//ターゲットリング位置更新
		UpdateTargetRing();

		if (m_DontMoveFlg2)
		{
			return;
		}
		////暗転中は動かせない
		//if (m_DontMoveFlg)
		//{
		//	BlackUpdate();
		//	return;
		//}
		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{

			//移動------------------------------------------------------------
			if (m_moveFlg)
			{
				if (abs(CntlVec[0].fThumbLX) + abs(CntlVec[0].fThumbLY) >= 0.2f)
				{
					//Abe20170620
					//ブースト起動
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					Vector3 InputXY = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
					Vector3 pos = GetComponent<Transform>()->GetPosition();
					pos += InputXY * App::GetApp()->GetElapsedTime() * m_Speed;
					GetComponent<Transform>()->SetPosition(pos);
					//慣性更新
					m_Kansei = InputXY;

					//回転設定
					m_MoveRotFlg = false;

					float angle = atan2(InputXY.z, InputXY.x);
					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle, 0);
					//ステージ外の制御
				}
				else
				{
					//Abe20170620
					//ブースト切る
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
					//Abe20170620

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
					//ターゲット表示
					if (!m_TargetRing->GetDrawActive())
					{
						m_TargetRing->SetDrawActive(true);
					}

					m_PlayerSDistance += App::GetApp()->GetElapsedTime() * m_DistanceSpeed;
					if (m_PlayerSDistance > m_PlayerSDistanceLimit)
					{
						m_PlayerSDistance = m_PlayerSDistanceLimit;
					}
					else
					{
						//Abe20170620
						//ブースト強め
						GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Boost();
						GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Boost();


						//回転
						m_MoveRotFlg = false;
						//座標取得
						Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
						Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

						//差計算
						Vector3 dis1 = pos1 - pos2;
						Vector3 dis2 = pos2 - pos1;


						//角度計算
						float angle1 = atan2(dis1.z, dis1.x);
						float angle2 = atan2(dis2.z, dis2.x);

						m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
						m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
						//Abe20170620

					}
				}
				else if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					//はさむ判定有効
					GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false)->SetActive(true);

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

					//Abe20170620
					//ブースト強め
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Boost();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Boost();
					//Abe20170620

				}
			}
			//くっつく
			else if (m_KuttukuFlg)
			{
				//回転も制限
				m_MoveRotFlg = true;

				//くっつける
				m_PlayerSDistance += -m_KuttukuSpeed * App::GetApp()->GetElapsedTime();
				//速度上げる
				m_KuttukuSpeed *= 1.1f;
				SetActiveCollision(true);
				//くっついたら
				if (m_PlayerSDistance < 1.0f)
				{
					//ターゲット非表示
					if (m_TargetRing->GetDrawActive())
					{
						m_TargetRing->SetDrawActive(false);
					}

					//くっつくOFF
					m_KuttukuFlg = false;
					//戻るON
					m_KuttukuAfterFlg = true;
					SetActiveCollision(false);

					//Abe20170620
					//ブースト起動
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620
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

					//はさむ判定無効
					GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false)->SetActive(false);


					//ステージ外の制御
				}
				//ステージ外の制御
			}
			//回転--------------------------------------------------
			if (m_rotFlg)
			{
				//左回転
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
				{
					//Abe20170620
					//ブースト起動
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					m_rot += -m_rotSpeed * App::GetApp()->GetElapsedTime();
					//一応ループさせとく
					if (m_rot < 0)
					{
						m_rot = 360;
					}

					//Abe20170620
					//向き変更
					m_MoveRotFlg = false;

					//座標取得
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//差計算
					Vector3 dis1 = pos2 - pos1;
					Vector3 dis2 = pos1 - pos2;

					//角度計算
					float angle1 = atan2(dis1.z, dis1.x) + -90 * 3.14159265f / 180;
					float angle2 = atan2(dis2.z, dis2.x) + -90 * 3.14159265f / 180;

					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);

					//Abe20170620

				}
				//右回転
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
				{
					//Abe20170620
					//ブースト起動
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Normal();
					GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Normal();
					//Abe20170620

					m_rot += m_rotSpeed * App::GetApp()->GetElapsedTime();
					//一応ループさせとく
					if (m_rot > 360)
					{
						m_rot = 0;
					}

					//Abe20170620
					//向き変更
					m_MoveRotFlg = false;

					//座標取得
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//差計算
					Vector3 dis1 = pos2 - pos1;
					Vector3 dis2 = pos1 - pos2;

					//角度計算
					float angle1 = atan2(dis1.z, dis1.x) + 90 * 3.14159265f / 180;
					float angle2 = atan2(dis2.z, dis2.x) + 90 * 3.14159265f / 180;

					m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
					m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);

					//Abe20170620

				}
			}
		}
		
		//ステージ外の制御
		StintArea();
		//プレイヤーの位置と回転更新
		PosRotUpdate();
	}

	//----------------------------------------------
	//関数
	//----------------------------------------------
	//プレイヤー位置回転更新
	void PlayerControl::PosRotUpdate()
	{
		//右が0で左が1
		Vector3 posright = GetComponent<Transform>()->GetPosition();
		posright += Vector3(cos(-m_rot*3.14159265f / 180), 0, sin(-m_rot*3.14159265f / 180)) * (m_PlayerSDistance / 2);
		m_Player1->GetComponent<Transform>()->SetPosition(posright);

		//m_Debugtxt->SetText(Util::FloatToWStr(GetComponent<Transform>()->GetPosition().y));

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


		//移動してなければ向かせる
		if (m_MoveRotFlg)
		{
			//角度計算
			float angle1 = atan2(dis1.z, dis1.x);
			float angle2 = atan2(dis2.z, dis2.x);

			m_Player1->GetComponent<Transform>()->SetRotation(0, -angle1, 0);
			m_Player2->GetComponent<Transform>()->SetRotation(0, -angle2, 0);
		}

		//回転戻す
		m_MoveRotFlg = true;

	}


	//アニメーション更新
	void PlayerControl::UpdateAnimation()
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

	//ターゲットリング位置更新
	void PlayerControl::UpdateTargetRing()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		pos.y = GetComponent<Transform>()->GetPosition().y + 0.5f;
		m_TargetRing->GetComponent<Transform>()->SetPosition(pos);
	}
	//----------------------------------------------
	//その他(アクセサーとか)
	//----------------------------------------------
	//二体の座標をvectorコンテナで渡す
	vector<Vector3> PlayerControl::GetPlayerSPos_RETURNvectorVec3()
	{
		vector<Vector3> vec3;
		vec3.push_back(m_Player1->GetComponent<Transform>()->GetPosition());
		vec3.push_back(m_Player2->GetComponent<Transform>()->GetPosition());
		return vec3;
	}	//////////////////////////////////////////////////////////////
		//当たり判定の有無
	void PlayerControl::SetActiveCollision(bool flg) {
		//当たり判定
		auto PtrCollisionSand = GetStage()->GetSharedGameObject<CollisionSand>(L"CollisionSand", false);
		if (PtrCollisionSand) {
			PtrCollisionSand->SetActive(flg);
		}
		else {
			throw BaseException(
				L"エラー",
				L"スタート関数の中「SetActiveCollision」",
				L"PtrCollisionSandが存在していません"
			);
		}
	}
	//エリア制限関数
	void PlayerControl::StintArea() {
	
		auto PlayerControlTrans = GetComponent<Transform>();
		Vector3 PlayerControlPos = PlayerControlTrans->GetPosition();
		Vector3 PlayerL_Pos = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerR_Pos = m_Player2->GetComponent<Transform>()->GetPosition();
		Vector3 PlayerL_Scale = m_Player1->GetComponent<Transform>()->GetScale();
		Vector3 PlayerR_Scale = m_Player2->GetComponent<Transform>()->GetScale();
		auto Elap = App::GetApp()->GetElapsedTime();
		//右　PLayerR
		if (m_StageSize.x < PlayerR_Pos.x) {
			float n2 = m_StageSize.x - PlayerR_Pos.x;
			PlayerControlPos.x += n2;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);
		}
		//PLayerL
		if (m_StageSize.x < PlayerL_Pos.x) {
			float n2 = m_StageSize.x - PlayerL_Pos.x;
			PlayerControlPos.x += n2;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//左　PLayerL
		if (-m_StageSize.x > PlayerL_Pos.x)
		{
			float n = -m_StageSize.x + (-PlayerL_Pos.x);
			PlayerControlPos.x += n;

			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PlayerR
		if (-m_StageSize.x > PlayerR_Pos.x) {
			float n = -m_StageSize.x + (-PlayerR_Pos.x);
			PlayerControlPos.x += n;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//上　PlayerL
		if (m_StageSize.y - 1.5 < PlayerL_Pos.z) {
			float n3 = (m_StageSize.y - 1.5) - PlayerL_Pos.z;
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PLayerR
		if (m_StageSize.y - 1.5 < PlayerR_Pos.z) {
			float n3 = (m_StageSize.y - 1.5) - PlayerR_Pos.z;
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//下　PlayerL
		if (-m_StageSize.y > PlayerL_Pos.z) {
			float n3 = -m_StageSize.y + (-PlayerL_Pos.z);
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
		//PLayerR
		if (-m_StageSize.y > PlayerR_Pos.z) {
			float n3 = -m_StageSize.y + (-PlayerR_Pos.z);
			PlayerControlPos.z += n3;
			PlayerControlTrans->SetPosition(PlayerControlPos.x, PlayerControlPos.y, PlayerControlPos.z);

		}
	}
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

	//シールド
	PlayerShield::PlayerShield(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scele , shared_ptr<GameObject> PtrPlayer) :
		GameObject(StagePtr),
		m_Pos(Pos),
		m_Scele(Scele),
		m_Player(PtrPlayer)
	{}
	void PlayerShield::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetRotation(0, 0, 0);
		Trans->SetScale(m_Scele);


		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"TEST_AO_TX");
		SetAlphaActive(true);
		PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
		m_OpacityColor = 1.0f;
		SetDrawActive(false);
		SetDrawLayer(10);
	}
	void PlayerShield::OnUpdate() {
		auto PlayerLifePtr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);
		auto Pos = m_Player->GetComponent<Transform>()->GetPosition();
		auto PtrDraw = GetComponent<PNTStaticDraw>();
		GetComponent<Transform>()->SetPosition(Pos.x,Pos.y+ 0.5 ,Pos.z);
		//最初のHPの保存
		if (InitHpSaveflg) {
			m_HPSave = PlayerLifePtr->GetLife();
			InitHpSaveflg = false;
			
		}
		//前回のHPと違う場合
		if (PlayerLifePtr->GetLife() != m_HPSave) {
			//保存HPの更新
			m_HPSave = PlayerLifePtr->GetLife();
			//演出フラグをON
			m_OnShield = true;
			m_Opacity = 1.0f;
			SetDrawActive(true);
		}

		//HPが内時　シールドが赤くなり点滅する
		if (m_OnShield && PlayerLifePtr->GetLife() != 1) {
				//HPがあるとき
				m_Opacity -= 0.05;
				PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
				if (m_Opacity < 0.0f) {
					SetDrawActive(false);
					m_OnShield = false;
				}
		}
		else if(m_OnShield && PlayerLifePtr->GetLife() == 1){
			if (m_Once == true) {	
				PtrDraw->SetTextureResource(L"TEST_Red_TX");
				m_Opacity = 0.5f;
				SetUpdateActive(true);
				SetDrawActive(true);
				m_Once = false;
			}
			if (m_Opacity <= 0.0f) {
				m_OpacityColor *= -1.0f;
			}
			else if (m_Opacity >= 0.5f) {
				m_OpacityColor *= -1.0f;
			}
			m_Opacity += 0.05 * m_OpacityColor;
			PtrDraw->SetDiffuse(Color4(1, 1, 1, m_Opacity));
		}
		//HPが０になったら
		if (PlayerLifePtr->GetLife() <= 0.0f) {
		SetUpdateActive(false);
		SetDrawActive(false);
		}
		
	}

	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	用途　プレイヤーブースト
	////--------------------------------------------------------------------------------------
	PlayerBoost::PlayerBoost(const shared_ptr<Stage>& StagePtr,const Vector3& InitPos,const Vector3& scale,const wstring& TextureName,const int& DeleteTime, const int& PlusTimeSpeed):
	GameObject(StagePtr),
	m_InitPos(InitPos),
	m_scale(scale),
	m_TextureName(TextureName),
	m_DeleteTime(DeleteTime),
	m_PlusTimeSpeed(PlusTimeSpeed)
	
	{}
	void PlayerBoost::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_scale);
		Trans->SetRotation(0, 0, 0);
			//描画設定
			auto Draw = AddComponent<PNTStaticDraw>();
			Draw->SetMeshResource(L"DEFAULT_SQUARE");
			Draw->SetTextureResource(m_TextureName);
			SetAlphaActive(true);
	}
	void PlayerBoost::OnUpdate() {
		m_CuntTime += App::GetApp()->GetElapsedTime()* m_PlusTimeSpeed;
		if (m_CuntTime > m_DeleteTime) {
			SetDrawActive(false);
			SetUpdateActive(false);

		}
	}

	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	用途:プレイヤーパーティクル
	////--------------------------------------------------------------------------------------
	//PlayerParticle::PlayerParticle(const  shared_ptr<Stage>& StagePtr) :
	//GameObject(StagePtr)
	//{}

	//void PlayerParticle::OnUpdate(){
	//	//パーティクルを出しているか？
	//	if (m_NowParticleFlg)
	//	{
	//		bool CreateFlg = false;
	//		//位置更新
	//		
	//		for (auto v : m_Particle)
	//		{
	//			float m_Count = 0;
	//			//描画されてたら
	//			if (v->GetDrawActive())
	//			{
	//				while(flg == true) 
	//				{
	//					m_Count += App::GetApp()->GetElapsedTime()/2;
	//					if (m_Count > 10) {
	//						v->SetDrawActive(false);
	//						m_Count = 0;
	//						flg = false;
	//					}
	//				}
	//			}
	//			flg = true;
	//		}
	//		if (CreateFlg)
	//		{
	//			//無かったら生成
	//			CreateParticle();
	//		}
	//	}
	//	
	//}
	//void PlayerParticle::OnParticle(Vector3 InitPos, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int Layer, float deleteTime){
	//	//初期位置
	//	m_InitPos = InitPos;
	//	//大きさ設定
	//	m_Scale = scale;
	//	//テクスチャの名前設定
	//	m_TextureName = TextureName;
	//	//消滅演出設定
	//	m_DeleteFlg = DeleteFlg;
	//	//作成間隔設定
	//	m_CreateInterval = CreateInterval;
	//	//レイヤー設定
	//	m_Layer = Layer;
	//	//消滅時間
	//	m_DeleteTime = deleteTime;

	//	m_NowParticleFlg = true;

	//}
	//void PlayerParticle::CreateParticle() {
	//	//生成
	//	auto obj = GetStage()->AddGameObject<GameObject>();
	//	auto Trans = obj->AddComponent<Transform>();
	//	//生成位置調整
	//	Vector3 pos = m_InitPos;
	//	//位置設定
	//	Trans->SetPosition(pos);
	//	//大きさ設定
	//	Trans->SetScale(m_Scale);

	//	//描画設定
	//	auto Draw = obj->AddComponent<PNTStaticDraw>();
	//	Draw->SetMeshResource(L"DEFAULT_SQUARE");
	//	Draw->SetTextureResource(m_TextureName);
	//	obj->SetAlphaActive(true);
	//	obj->SetDrawLayer(m_Layer);

	//
	//	//各自の消える時間
	//	m_Particle.push_back(obj);
	//}

	
	
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
	//	PlayerブーストSP スプライトスタジオ
	//--------------------------------------------------------------------------------------
	PlayerBoostSP::PlayerBoostSP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, Vector3 Rotation) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + txtdire, txtname, L"anime_1"),
		m_Pos(pos),
		m_Scale(scale),
		m_Rotation(Rotation)
	{}

	void PlayerBoostSP::OnCreate()
	{
	
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(Vector3(m_Rotation.x * XM_2PI / 180, -m_Rotation.y*XM_2PI / 180, -m_Rotation.z*XM_2PI / 180));

		//アニメーション関連
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(1.0f, 1.0f, 1.0f),
			Vector3(0, 0, 0),
			Vector3(0, 0, 0)
		);
		SetToAnimeMatrix(mat);

		//親クラスのCreate
		SS5ssae::OnCreate();
		//秒あたりのフレーム数
		SetFps(60.0f);
		//ループ無効
		SetLooped(true);


		//透明度有効化
		SetAlphaActive(true);
		//描画
		SetDrawActive(true);
		//表示レイヤー
		SetDrawLayer(2);

	}

	void PlayerBoostSP::OnUpdate()
	{
		
		//アニメ―ション更新
		UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 4);
	}
	//Abe20170529

	
	
	//////////////////////////////////////////////////////////////
}




