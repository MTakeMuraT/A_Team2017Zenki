#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	フレームスプライト
	//--------------------------------------------------------------------------------------
	SelectFlame::SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectFlame::OnCreate()
	{
		//座標設定
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//描画設定
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_FLAME_TX");

		//透明度設定
		SetAlphaActive(true);
		//レイヤー設定
		SetDrawLayer(m_layer);
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤー
	//--------------------------------------------------------------------------------------
	SelectPlayer::SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,float speed):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_Speed(speed)
	{}

	void SelectPlayer::OnCreate()
	{
		//obj作成
		for (int i = 0; i < 2; i++)
		{
			auto PlayerPtr = GetStage()->AddGameObject<GameObject>();
			//座標設定
			auto Trans = PlayerPtr->AddComponent<Transform>();
			//座標変更
			Vector3 pos = m_InitPos;
			pos.x += -m_DifLength + (i * m_DifLength*2);
			Trans->SetPosition(pos);
			Trans->SetScale(m_InitScale);
			Trans->SetRotation(0, 0, 0);

			//描画設定
			auto PtrDraw = PlayerPtr->AddComponent<PNTStaticDraw>();
			PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
			PtrDraw->SetTextureResource(L"TRACE_TX");

			//透明処理
			SetAlphaActive(true);

			//Rigidbodyをつける
			auto PtrRedid = PlayerPtr->AddComponent<Rigidbody>();
			//衝突判定をつける
			auto PtrCol = PlayerPtr->AddComponent<CollisionSphere>();
			
			//プレイヤーのアクセサ?
			m_Player.push_back(PlayerPtr);
		}

	}

	void SelectPlayer::OnUpdate()
	{
		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//移動
			Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY) * m_Speed;
			for (auto obj : m_Player)
			{
				//挟んでる間は別のVelocityが入れられるのでここ更新しても動かない
				obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
			}

			if (!m_SandFlg)
			{
				//回転処理
				Rot();
				//Aボタン押してる間離れる
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A)
				{
					//進む方向を決める
					Vector3 difpos = m_Player[0]->GetComponent<Transform>()->GetPosition() - m_Player[1]->GetComponent<Transform>()->GetPosition();
					//ある程度離れてないかを確認 半径10以下
					if (difpos.x*difpos.x + difpos.z*difpos.z < 100)
					{
						//absを使うとifで反転させるより遅くなるけどそんなに重い処理ないしおｋだよね？
						float xPlusz = abs(difpos.x) + abs(difpos.z);
						difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
						difpos *= m_Speed;

						for (auto obj : m_Player)
						{
							obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
							difpos *= -1;
						}
					}
				}

				//Aボタン離したら
				if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
				{
					m_SandFlg = true;
				}
			}
		}

		//もしはさむ状態になってたら
		if (m_SandFlg)
		{
			SandMove();
		}
	}

	//回転処理
	void SelectPlayer::Rot()
	{
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//左肩
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
				//座標取得
				Vector3 pos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
				Vector3 centerpos = (pos1 + pos2) / 2;

				//中心からの角度算出して加算して計算しなおして座標に入れる
				Vector3 dif = pos1 - centerpos;
				float angle1 = atan2(dif.z, dif.x) * 180/3.14159265f;
				angle1 += 360;
				int an1 = (int)angle1 % 360;
				an1 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				Vector3 vel = Vector3(cos(an1*3.14159265f / 180), 0, sin(an1*3.14159265f / 180)) * m_DifLength;
				pos1 = centerpos + vel;
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);

				//２体目
				dif = pos2 - centerpos;
				float angle2 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				vel = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel;
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			//右肩
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				//座標取得
				Vector3 pos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
				Vector3 centerpos = (pos1 + pos2) / 2;

				//中心からの角度算出して加算して計算しなおして座標に入れる
				Vector3 dif = pos1 - centerpos;
				float angle1 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle1 += 360;
				int an1 = (int)angle1 % 360;
				an1 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				Vector3 vel = Vector3(cos(an1*3.14159265f / 180), 0, sin(an1*3.14159265f / 180)) * m_DifLength;
				pos1 = centerpos + vel;
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);

				//２体目
				dif = pos2 - centerpos;
				float angle2 = atan2(dif.z, dif.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				vel = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel;
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
		}
	}

	//引き合う処理
	void SelectPlayer::SandMove()
	{
		//近づいてない状態
		if (!m_SandFinishFlg)
		{
			//進む方向を決める
			Vector3 difpos = m_Player[1]->GetComponent<Transform>()->GetPosition() - m_Player[0]->GetComponent<Transform>()->GetPosition();
			//ある程度 半径1.5くらい以上
			if (difpos.x*difpos.x + difpos.z*difpos.z > 4)
			{
				//absを使うとifで反転させるより遅くなるけどそんなに重い処理ないしおｋだよね？
				float xPlusz = abs(difpos.x) + abs(difpos.z);
				difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
				//正規化できてるか確認
				//GetComponent<StringSprite>()->SetText(L"x:" + Util::FloatToWStr(difpos.x) + L"z:" + Util::FloatToWStr(difpos.z));
				difpos *= m_Speed;

				for (auto obj : m_Player)
				{
					obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
					difpos *= -1;
				}
			}
			//設定した距離まで近づいた
			else
			{
				m_SandFinishFlg = true;
			}
		}
		else
		{
			//進む方向を決める
			Vector3 difpos = m_Player[0]->GetComponent<Transform>()->GetPosition() - m_Player[1]->GetComponent<Transform>()->GetPosition();
			//初期の座標の差より離れたら(距離m_difLengthは半径のため２倍*２体分)
			if (difpos.x*difpos.x + difpos.z*difpos.z < 4*(m_DifLength*m_DifLength))
			{
				//absを使うとifで反転させるより遅くなるけどそんなに重い処理ないしおｋだよね？
				float xPlusz = abs(difpos.x) + abs(difpos.z);
				difpos = Vector3(difpos.x / xPlusz, 0, difpos.z / xPlusz);
				//正規化できてるか確認
				//GetComponent<StringSprite>()->SetText(L"x:" + Util::FloatToWStr(difpos.x) + L"z:" + Util::FloatToWStr(difpos.z));
				difpos *= m_Speed;

				for (auto obj : m_Player)
				{
					obj->GetComponent<Rigidbody>()->SetVelocity(difpos);
					difpos *= -1;
				}
			}
			//初期距離より離れた
			else
			{
				m_SandFlg = false;
				m_SandFinishFlg = false;
			}
		}
	}

	void SelectPlayer::SetPlayerUpdate(bool flg)
	{
		SetUpdateActive(flg);

		//すぐバグ出るから念のため
		for (auto obj : m_Player)
		{
			obj->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
	}

	//--------------------------------------------------------------------------------------
	//	ステージの箱
	//--------------------------------------------------------------------------------------
	StageBox::StageBox(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, int num):
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_stagenumber(num)
	{}

	void StageBox::OnCreate()
	{
		//座標設定
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//描画設定
		auto PtrDraw = AddComponent<PNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		PtrDraw->SetTextureResource(L"SKY_TX");

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();

	}

	void StageBox::OnUpdate()
	{
		//プレイヤーが１体以上当たってるときのみ処理
		if (m_PlayerHitFlg)
		{
			//プレイヤーが当たってる数が２体
			if (m_PlayerHitNum == 2)
			{
				//Aボタン押されてるかの処理はいらん。Aはなされなければ引かれないしな
				CheckGo();
			}
			//なんにも当たってなければ
			else if(m_PlayerHitNum == 0)
			{
				//余計な処理しないように切っておく(本来はアップデート自体止めるのがいいんだけどバグ落ちする)
				m_PlayerHitFlg = false;
			}
			m_PlayerHitNum = 0;
		}
	}

	void StageBox::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec)
	{
		//プレイヤー以外当たるやつがないはずなのでとりあえず当たったらプレイヤーじゃ
		for (auto obj : OtherVec)
		{
			m_PlayerHitNum++;

			//プレイヤーの離れるフラグ起動
			GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFlgOn();
		}
		if (m_PlayerHitNum > 0)
		{
			m_PlayerHitFlg = true;
		}
	}

	void StageBox::CheckGo()
	{
		//元の位置に戻るフラグ起動
		//GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();

		//いったんアップデート止める
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetPlayerUpdate(false);

		//確認ウィンドウ起動
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->OpenCheck();
	}

	//--------------------------------------------------------------------------------------
	//	ステージ行くか確認するオブジェクト
	//--------------------------------------------------------------------------------------
	GoStageCheck::GoStageCheck(const shared_ptr<Stage>& StagePtr, Vector2 scale):
		GameObject(StagePtr),
		m_InitScale(scale)
	{}

	void GoStageCheck::OnCreate()
	{
		
		//背景作成------------------------------------
		auto CheckBack = GetStage()->AddGameObject<GameObject>();
		
		//座標
		auto Trans = CheckBack->AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(Vector3(660,360,1));
		Trans->SetRotation(0, 0, 0);

		//描画
		auto Draw = CheckBack->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_SIRO_TX");
		
		//レイヤー設定
		CheckBack->SetDrawLayer(2);
		//透明度有効化
		CheckBack->SetAlphaActive(true);

		//消しとく
		CheckBack->SetDrawActive(false);

		m_CheckBack = CheckBack;
		
		
		//YES文字作成---------------------------------
		auto YesSprite = GetStage()->AddGameObject<GameObject>();

		//座標
		auto YTrans = YesSprite->AddComponent<Transform>();
		YTrans->SetPosition(150, -70, 0);
		YTrans->SetScale(240, 120, 1);
		YTrans->SetRotation(0, 0, 0);

		//描画
		auto YDraw = YesSprite->AddComponent<PCTSpriteDraw>();
		YDraw->SetTextureResource(L"SELECT_YES_TX");
		
		//レイヤー設定
		YesSprite->SetDrawLayer(3);

		//透明度有効化
		YesSprite->SetAlphaActive(true);

		//消しとく
		YesSprite->SetDrawActive(false);

		m_CheckYes = YesSprite;
		
		//No文字作成------------------------------------
		auto NoSprite = GetStage()->AddGameObject<GameObject>();

		//座標
		auto NTrans = NoSprite->AddComponent<Transform>();
		NTrans->SetPosition(-150, -70, 0);
		NTrans->SetScale(240, 120, 1);
		NTrans->SetRotation(0, 0, 0);

		//描画
		auto NDraw = NoSprite->AddComponent<PCTSpriteDraw>();
		NDraw->SetTextureResource(L"SELECT_YES_TX");

		//レイヤー設定
		NoSprite->SetDrawLayer(3);

		//透明度有効化
		NoSprite->SetAlphaActive(true);

		//消しとく
		NoSprite->SetDrawActive(false);

		m_CheckNo = NoSprite;

		//確認文字作成------------------------------------
		auto CheckLogo = GetStage()->AddGameObject<GameObject>();
		//座標
		auto CLTrans = CheckLogo->AddComponent<Transform>();
		CLTrans->SetPosition(0, 80, 0);
		CLTrans->SetScale(550, 120, 1);
		CLTrans->SetRotation(0, 0, 0);

		//描画
		auto CLDraw = CheckLogo->AddComponent<PCTSpriteDraw>();
		CLDraw->SetTextureResource(L"SELECT_YES_TX");

		//レイヤー設定
		CheckLogo->SetDrawLayer(3);

		//透明度有効化
		CheckLogo->SetAlphaActive(true);

		//消しとく
		CheckLogo->SetDrawActive(false);

		m_CheckLogo = CheckLogo;

		//カーソル作成------------------------------------
		auto CursorSprite = GetStage()->AddGameObject<GameObject>();
		//座標
		auto CTrans = CursorSprite->AddComponent<Transform>();
		CTrans->SetPosition(150, -70, 0);
		CTrans->SetScale(100, 100, 1);
		CTrans->SetRotation(0, 0, 0);

		//描画
		auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
		CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

		//レイヤー設定
		CursorSprite->SetDrawLayer(4);

		//透明度有効化
		CursorSprite->SetAlphaActive(true);

		//消しとく
		CursorSprite->SetDrawActive(false);

		m_Cursor = CursorSprite;



		//文字列
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));		
	}

	void GoStageCheck::OnUpdate()
	{
		if (m_Dispflg)
		{
			//コントローラ取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				//コントローラーが左に倒されたら
				if (CntlVec[0].fThumbLX < -0.5f)
				{
					//選択項目Yes
					m_selectnum = 1;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-150, -70, 0));
				}
				//右
				else if (CntlVec[0].fThumbLX > 0.5f)
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -70, 0));
				}

				//AかBボタン押されたら
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					switch (m_selectnum)
					{
						//No
					case 0:
						CloseCheck();
						break;
						//Yes
					case 1:
						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						break;
					}
				}
			}
		}
	}

	//起動
	void GoStageCheck::OpenCheck()
	{
		m_Dispflg = true;
		m_CheckBack->SetDrawActive(true);
		m_CheckYes->SetDrawActive(true);
		m_CheckNo->SetDrawActive(true);
		m_CheckLogo->SetDrawActive(true);
		m_Cursor->SetDrawActive(true);
	}

	//終了
	void GoStageCheck::CloseCheck()
	{
		m_Dispflg = false;
		m_CheckBack->SetDrawActive(false);
		m_CheckYes->SetDrawActive(false);
		m_CheckNo->SetDrawActive(false);
		m_CheckLogo->SetDrawActive(false);
		m_Cursor->SetDrawActive(false);

		//次起動するとき用に初期化
		//Noに初期化
		m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -70, 0));
		m_selectnum = 0;

		//プレイヤーのアップデート再開
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetUpdateActive(true);
		//離れさせる
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();
	}
	//Abe20170421

}