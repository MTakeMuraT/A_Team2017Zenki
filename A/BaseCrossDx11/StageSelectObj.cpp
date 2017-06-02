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

	//Abe20170525
	//--------------------------------------------------------------------------------------
	//	ロゴ
	//--------------------------------------------------------------------------------------
	SelectLogo::SelectLogo(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void SelectLogo::OnCreate()
	{
		//座標設定
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_InitScale);
		Trans->SetRotation(0, 0, 0);

		//描画設定
		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECT_LOGO_TX");

		//透明度設定
		SetAlphaActive(true);
		//レイヤー設定
		SetDrawLayer(m_layer);
	}
	//Abe20170525

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
			auto PtrDraw = PlayerPtr->AddComponent<PNTBoneModelDraw>();
			
			PtrDraw->SetMeshResource(L"Player_Model");
		//	PtrDraw->SetTextureResource(L"TRACE_TX");

			//透明処理
			SetAlphaActive(true);

			//Rigidbodyをつける
			auto PtrRedid = PlayerPtr->AddComponent<Rigidbody>();
			//衝突判定をつける
			auto PtrCol = PlayerPtr->AddComponent<CollisionSphere>();
			
			PlayerPtr->SetDrawLayer(0);

			//プレイヤーのアクセサ?
			m_Player.push_back(PlayerPtr);
			PtrDraw->AddAnimation(L"Wait", 0, 30, true, 30.0f);
			PtrDraw->AddAnimation(L"LeftRot", 80, 15, false, 30.0f);
			PtrDraw->AddAnimation(L"RightRot", 120, 15, false, 30.0f);

		}
		//デバッグ文字生成
		auto debtxt = GetStage()->AddGameObject<DebugTxt>();
		debtxt->SetLayer(10);
		//色赤に変更
		debtxt->SetColor(Vector3(1, 0, 0));
		//大きさ変更
		debtxt->SetScaleTxt(40);

		m_Debugtxt = debtxt;
		//Abe20170524
	
		

	}

	void SelectPlayer::OnUpdate()
	{
		AnimationWait();
		Model();
		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

#pragma region //*******デバッグ用*******//
		//*******デバッグ用*******//
		//auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();

		////移動
		//Vector2 InputXY = Vector2((KeylVec.m_bPushKeyTbl[VK_RIGHT] + -KeylVec.m_bPushKeyTbl[VK_LEFT]), (KeylVec.m_bPushKeyTbl[VK_UP] + -KeylVec.m_bPushKeyTbl[VK_DOWN])) * m_Speed;
		////もしステージ幅制限を越えるなら動かさない
		////１体目の座標
		//Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		////２体目の座標
		//Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
		//ppos1.x += InputXY.x * App::GetApp()->GetElapsedTime();
		//ppos1.z += InputXY.y * App::GetApp()->GetElapsedTime();
		//ppos2.x += InputXY.x * App::GetApp()->GetElapsedTime();
		//ppos2.z += InputXY.y * App::GetApp()->GetElapsedTime();
		////制限(左-20右+66上+10下-36)
		//if ((ppos1.x < MoveLimit.x || ppos2.x < MoveLimit.x) || (ppos1.x > MoveLimit.y || ppos2.x > MoveLimit.y))
		//{
		//	InputXY.x = 0;
		//}
		//if ((ppos1.z < MoveLimit.w || ppos2.z < MoveLimit.w) || (ppos1.z > MoveLimit.z || ppos2.z > MoveLimit.z))
		//{
		//	InputXY.y = 0;
		//}
		////wstring txt;
		////txt += L"1X:" + Util::FloatToWStr(ppos1.x) + L"1Z:" + Util::FloatToWStr(ppos1.z) +
		////	L"\n2X:" + Util::FloatToWStr(ppos2.x) + L"1Z:" + Util::FloatToWStr(ppos2.z);
		////dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(txt);
		//Vector3 ppos31 = (ppos1 + ppos2) / 2;

		//dynamic_pointer_cast<DebugTxt>(m_Debugtxt)->SetText(L"X:" + Util::FloatToWStr(ppos31.x) + L"Z:" + Util::FloatToWStr(ppos31.z));

		////*******デバッグ用*******//

		////移動
		//for (auto obj : m_Player)
		//{
		//	//挟んでる間は別のVelocityが入れられるのでここ更新しても動かない
		//	obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
		//}

#pragma endregion

		if (CntlVec[0].bConnected)
		{
			Vector3 ppos11 = m_Player[0]->GetComponent<Transform>()->GetPosition();
			Vector3 ppos21 = m_Player[1]->GetComponent<Transform>()->GetPosition();

			Vector3 ppos31 = (ppos11 + ppos21) / 2;

			//移動
			Vector2 InputXY = Vector2(CntlVec[0].fThumbLX, CntlVec[0].fThumbLY) * m_Speed;

			//もしステージ幅制限を越えるなら動かさない
			//制限(左-20右+66上+10下-36)
			//１体目の座標
			Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
			//２体目の座標
			Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();
			ppos1.x += InputXY.x * App::GetApp()->GetElapsedTime();
			ppos1.z += InputXY.y * App::GetApp()->GetElapsedTime();
			ppos2.x += InputXY.x * App::GetApp()->GetElapsedTime();
			ppos2.z += InputXY.y * App::GetApp()->GetElapsedTime();
			//制限(左-20右+66上+10下-36)
			if ((ppos1.x < MoveLimit.x || ppos2.x < MoveLimit.x) || (ppos1.x > MoveLimit.y || ppos2.x > MoveLimit.y))
			{
				InputXY.x = 0;
			}
			if ((ppos1.z < MoveLimit.w || ppos2.z < MoveLimit.w) || (ppos1.z > MoveLimit.z || ppos2.z > MoveLimit.z))
			{
				InputXY.y = 0;
			}

			//移動
			for (auto obj : m_Player)
			{
				//挟んでる間は別のVelocityが入れられるのでここ更新しても動かない
				obj->GetComponent<Rigidbody>()->SetVelocity(InputXY.x, 0, InputXY.y);
			}

			if (!m_SandFlg)
			{
				//回転処理
				//Rot();
				if (!m_CancelFlg)
				{
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
				}

				if (m_CancelFlg)
				{
					if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
					{
						m_CancelFlg = false;
					}
				}
				else
				{
					//Aボタン離したら
					if (CntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_A)
					{
						m_SandFlg = true;
					}
				}
			}
		}

		//もしはさむ状態になってたら
		if (m_SandFlg)
		{
			SandMove();
		}

		//高さ設定
		for (auto obj : m_Player)
		{
			Vector3 pppos = obj->GetComponent<Transform>()->GetPosition();
			pppos.y = 0.6f;
			obj->GetComponent<Transform>()->SetPosition(pppos);
		}
		//もう片方に向く
		Vector3 ppos2 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		Vector3 ppos3 = m_Player[1]->GetComponent<Transform>()->GetPosition();
		Vector3 dif = ppos3 - ppos2;
		float angle = atan2(dif.z, dif.x) * -1;
		angle += 90 * 3.14159265f / 180;
		Vector3 dif2 = ppos2 - ppos3;
		float angle2 = atan2(dif2.z, dif2.x) * -1;
		angle2 += 90 * 3.14159265f / 180;


		m_Player[0]->GetComponent<Transform>()->SetRotation(0, angle2, 0);
		m_Player[1]->GetComponent<Transform>()->SetRotation(0, angle, 0);
	}

	//回転処理
	void SelectPlayer::Rot()
	{
		
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			
			//左肩
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				m_WaitFlg = false;
				AnimationRotL();
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

				//２体目
				Vector3 dif2 = pos2 - centerpos;
				float angle2 = atan2(dif2.z, dif2.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += (int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				Vector3 vel2 = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel2;

#pragma region 押し出し処理
				//押し出し処理
				//左押し出し
				if (pos1.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//右押し出し
				if (pos1.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//上押し出し
				if (pos1.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				//下押し出し
				if (pos1.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				
#pragma endregion

				//移動
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			else {
				m_WaitFlg = true;
			}
			//右肩
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				m_WaitFlg = false;
				AnimationRotR();
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

				//２体目
				Vector3 dif2 = pos2 - centerpos;
				float angle2 = atan2(dif2.z, dif2.x) * 180 / 3.14159265f;
				angle2 += 360;
				int an2 = (int)angle2 % 360;
				an2 += -(int)(m_RotSpeedPerSec * App::GetApp()->GetElapsedTime());
				//角度から求めて中心からの距離をかける
				Vector3 vel2 = Vector3(cos(an2*3.14159265f / 180), 0, sin(an2*3.14159265f / 180)) * m_DifLength;
				pos2 = centerpos + vel2;

#pragma region 押し出し処理
				//押し出し処理
				//左押し出し
				if (pos1.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x < MoveLimit.x)
				{
					float disX = MoveLimit.x - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//右押し出し
				if (pos1.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos1.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				if (pos2.x > MoveLimit.y)
				{
					float disX = MoveLimit.y - pos2.x;
					pos1.x += disX;
					pos2.x += disX;
				}
				//上押し出し
				if (pos1.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z > MoveLimit.z)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				//下押し出し
				if (pos1.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos1.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
				if (pos2.z < MoveLimit.w)
				{
					float disZ = MoveLimit.z - pos2.z;
					pos1.z += disZ;
					pos2.z += disZ;
				}
#pragma endregion

				//移動
				m_Player[0]->GetComponent<Transform>()->SetPosition(pos1);
				m_Player[1]->GetComponent<Transform>()->SetPosition(pos2);

			}
			else {
				m_WaitFlg = true;
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

		//キャンセルしたときに動くの防止
		m_CancelFlg = true;

		//すぐバグ出るから念のため
		for (auto obj : m_Player)
		{
			obj->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
	}

	//座標移動
	void SelectPlayer::SetPos(Vector3 pos)
	{
		int count = 0;
		for (auto obj : m_Player)
		{
			obj->GetComponent<CollisionSphere>()->SetUpdateActive(false);
			Vector3 pos1 = pos;
			pos1.x += -m_DifLength + (count * m_DifLength * 2);
			obj->GetComponent<Transform>()->SetPosition(pos1);
			count++;
		}
	}

	//座標取得
	Vector3 SelectPlayer::GetPos()
	{
		Vector3 ppos1 = m_Player[0]->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = m_Player[1]->GetComponent<Transform>()->GetPosition();

		return (ppos1 + ppos2) / 2;
	}

	void SelectPlayer::ActiveMove()
	{	
		for (auto obj : m_Player)
		{
			obj->GetComponent<CollisionSphere>()->SetUpdateActive(true);
		}
	}
	//モデルの向き
	void SelectPlayer::Model() {
		if (m_Model_flg) {
			auto Player1 = m_Player[0];
			auto Player2 = m_Player[1];
			Player1->GetComponent<Transform>()->SetRotation(0, -XM_PI / 2, 0);
			Player2->GetComponent<Transform>()->SetRotation(0, XM_PI / 2, 0);

			m_Model_flg = false;
		}
	}
	//待機アニメーション
	void SelectPlayer::AnimationWait() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		if (!(PtrDraw->GetCurrentAnimation() == L"Wait") && m_WaitFlg) {
			PtrDraw->ChangeCurrentAnimation(L"Wait");
			PtrDraw2->ChangeCurrentAnimation(L"Wait");
		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//回転アニメション関数 左
	void SelectPlayer::AnimationRotL() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();


		if (PtrDraw->GetCurrentAnimation() != L"LeftRot"){
			PtrDraw->ChangeCurrentAnimation(L"LeftRot");
			PtrDraw2->ChangeCurrentAnimation(L"LeftRot");
		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//右
	void SelectPlayer::AnimationRotR() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		auto PtrDraw2 = m_Player[1]->GetComponent<PNTBoneModelDraw>();

		if (!(PtrDraw->GetCurrentAnimation() == L"RightRot")) {
			PtrDraw->ChangeCurrentAnimation(L"RightRot");
			PtrDraw2->ChangeCurrentAnimation(L"RightRot");

		}
		UpdateAnyAnimation();
		UpdateAnyAnimation2();
	}
	//アニメーション更新関数
	bool SelectPlayer::UpdateAnyAnimation() {
		auto PtrDraw = m_Player[0]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
	}
	bool SelectPlayer::UpdateAnyAnimation2() {
		auto PtrDraw = m_Player[1]->GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		return PtrDraw->UpdateAnimation(ElapsedTime);
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
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		wstring stageString = L"STAGEBOX_" + Util::IntToWStr(m_stagenumber) + L"_TX";
		PtrDraw->SetTextureResource(stageString);

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
		GetStage()->GetSharedGameObject<GoStageCheck>(L"GoStageCheck", false)->SetStageNumber(m_stagenumber);
		GetStage()->GetSharedGameObject<EnemyCount>(L"Count", false)->Count();
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
		Trans->SetPosition(0, -30, 0);
		Trans->SetScale(Vector3(840,740,1));
		Trans->SetRotation(0, 0, 0);

		//描画
		auto Draw = CheckBack->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"SELECTCHECK_FLAME_TX");
		
		//レイヤー設定
		CheckBack->SetDrawLayer(2);
		//透明度有効化
		CheckBack->SetAlphaActive(true);

		//消しとく
		CheckBack->SetDrawActive(false);

		m_CheckBack = CheckBack;
		
		//中身作成----------------------------------------
		auto CheckBackIn = GetStage()->AddGameObject<GameObject>();

		//座標
		auto CITrans = CheckBackIn->AddComponent<Transform>();
		CITrans->SetPosition(0, -32, 0);
		CITrans->SetScale(Vector3(660, 580, 1));
		CITrans->SetRotation(0, 0, 0);

		//描画
		auto CIDraw = CheckBackIn->AddComponent<PCTSpriteDraw>();
		CIDraw->SetTextureResource(L"SELECT_WINDOWIN_TX");

		//レイヤー設定
		CheckBackIn->SetDrawLayer(3);
		//透明度有効化
		CheckBackIn->SetAlphaActive(true);

		//消しとく
		CheckBackIn->SetDrawActive(false);

		m_CheckBoxIn = CheckBackIn;


		
		//カーソル作成------------------------------------
		auto CursorSprite = GetStage()->AddGameObject<GameObject>();
		//座標
		auto CTrans = CursorSprite->AddComponent<Transform>();
		CTrans->SetPosition(135, -310, 0);
		CTrans->SetScale(200, 50, 1);
		CTrans->SetRotation(0, 0, 0);

		//描画
		auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
		CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

		//レイヤー設定
		CursorSprite->SetDrawLayer(3);

		//透明度有効化
		CursorSprite->SetAlphaActive(true);

		//消しとく
		CursorSprite->SetDrawActive(false);

		m_Cursor = CursorSprite;


		//Abe20170525
		//それぞれの数字作成
		//突撃
		auto tacklenum = GetStage()->AddGameObject<NumberSprite>(0,Vector2(-25,140),Vector2(100,100),4);
		tacklenum->SetNumDraw(false);
		m_TackleNumSpr = tacklenum;
		//玉
		auto shotnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(260, 140), Vector2(100, 100), 4);
		shotnum->SetNumDraw(false);
		m_ShotNumSpr = shotnum;
		//てれ
		auto terenum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(-25, -115), Vector2(100, 100), 4);
		terenum->SetNumDraw(false);
		m_TerepoNumSpr = terenum;
		//爆
		auto bombnum = GetStage()->AddGameObject<NumberSprite>(0, Vector2(260, -115), Vector2(100, 100), 4);
		bombnum->SetNumDraw(false);
		m_BombNumSpr = bombnum;
		//Abe20170525

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
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(-185, -310, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(100, 50, 1));
				}
				//右
				else if (CntlVec[0].fThumbLX > 0.5f)
				{
					m_selectnum = 0;
					m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(135, -310, 0));
					m_Cursor->GetComponent<Transform>()->SetScale(Vector3(200, 50, 1));
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
						//ステージ番号をScene.cppに渡す
						//====================================================
						//	１～４(25,25)　５～１２(50,50)　１３～１６(75,75)
						//====================================================
						Vector2 StageSize;
						StageSize = Vector2(25, 25);
						if (m_stageNum >= 1 && m_stageNum <= 4)
						{
							StageSize = Vector2(25, 25);
						}
						else if (m_stageNum >= 5 && m_stageNum <= 12)
						{
							StageSize = Vector2(50, 50);
						}
						else if (m_stageNum >= 13 && m_stageNum <= 16)
						{
							StageSize = Vector2(75, 75);
						}

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//ステージ番号と番号にあったステージの大きさを渡す
						ScenePtr->SetStageNumAndStageSize(m_stageNum, StageSize);
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
		m_CheckBoxIn->SetDrawActive(true);
		m_Cursor->SetDrawActive(true);
		m_TackleNumSpr->SetNumDraw(true);
		m_ShotNumSpr->SetNumDraw(true);
		m_TerepoNumSpr->SetNumDraw(true);
		m_BombNumSpr->SetNumDraw(true);

	}

	//終了
	void GoStageCheck::CloseCheck()
	{
		m_Dispflg = false;
		m_CheckBack->SetDrawActive(false);
		m_CheckBoxIn->SetDrawActive(false);
		m_Cursor->SetDrawActive(false);
		m_TackleNumSpr->SetNumDraw(false);
		m_ShotNumSpr->SetNumDraw(false);
		m_TerepoNumSpr->SetNumDraw(false);
		m_BombNumSpr->SetNumDraw(false);



		//次起動するとき用に初期化
		//Noに初期化
		m_Cursor->GetComponent<Transform>()->SetPosition(Vector3(150, -300, 0));
		m_selectnum = 0;

		//プレイヤーのアップデート再開
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SetUpdateActive(true);
		//離れさせる
		GetStage()->GetSharedGameObject<SelectPlayer>(L"SelectPlayer", false)->SandFinishFlgOn();
	}
	//Abe20170421

	//Abe20170525
	void GoStageCheck::SetEnemyNum(int tackle, int shot, int terepo, int bomb)
	{
		//数字のスプライト変更
		m_TackleNumSpr->SetNum(tackle);
		m_ShotNumSpr->SetNum(shot);
		m_TerepoNumSpr->SetNum(terepo);
		m_BombNumSpr->SetNum(bomb);
	}
	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	地面
	//--------------------------------------------------------------------------------------
	SelectGroud::SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale):
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale)
	{}

	void SelectGroud::OnCreate()
	{
		//必要最低限------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"STAGESELECTGROUND_TX");
		//必要最低限------

		
	}
	//Abe20170427

	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	地面に貼るやつ
	//--------------------------------------------------------------------------------------
	SelectGroundSquare::SelectGroundSquare(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale,wstring txt,float rot) :
		GameObject(StagePtr),
		m_Pos(pos),
		m_Scale(scale),
		m_Text(txt),
		m_rot(rot)
	{}

	void SelectGroundSquare::OnCreate()
	{
		//必要最低限------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//必要最低限------

		SetDrawLayer(1);
		SetAlphaActive(true);
	}
	//Abe20170526

	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	地面に貼るやつ(SS版)
	//--------------------------------------------------------------------------------------
	SelectGroundSquareSS::SelectGroundSquareSS(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, float rot) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + txtdire, txtname, L"anime_1"),
		m_Pos(pos),
		m_Scale(scale),
		m_rot(rot)
	{}

	void SelectGroundSquareSS::OnCreate()
	{
		/*
		//必要最低限------
		auto TranP = AddComponent<Transform>();
		TranP->SetPosition(m_Pos);
		TranP->SetScale(m_Scale);
		TranP->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(m_Text);
		//必要最低限------

		SetDrawLayer(1);
		SetAlphaActive(true);
		*/
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(90 * 3.14159265f / 180, -m_rot*3.14159265f / 180, 0);

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


	void SelectGroundSquareSS::OnUpdate()
	{
		//アニメ―ション更新
		UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 4);

	}
	//Abe20170529

}