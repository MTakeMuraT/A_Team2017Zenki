#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//************************************************************************
	//	突撃エネミー
	//	追記なし？
	//************************************************************************
	TackleEnemy::TackleEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, float speed, int power, int tacklecount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Speed(speed),
		m_Power(power),
		m_TackleCount(tacklecount)
	{}

	void TackleEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"TACKLE_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);
		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_SearchCircle = circle;



		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色赤に変更
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

		//Abe20170515
		//ステージの大きさ取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515


	}

	void TackleEnemy::OnUpdate()
	{
		//生きてれば
		if (m_ActiveFlg)
		{
			//m_Debugtxt->SetText(Util::IntToWStr(m_State));

			switch (m_State)
			{
				//索敵
			case SearchS:
				Search();
				break;
				//探索
			case MoveS:
				Move();
				StageEndCheck();
				break;
				//攻撃
			case AttackS:
				Attack();
				Rot();
				StageEndCheck();
				break;
				//クールタイム
			case CoolTimeS:
				CoolTime();
				break;
			}

			//回転
			Rot();
		}
	}
	//Abe20170519
	void TackleEnemy::Rot()
	{
		//持ってる速度から角度算出
		Vector3 vel = m_Velocity;
		//マイナス反転(absは重いので使いません)
		if (vel.x < 0)
		{
			vel.x *= -1;
		}
		if (vel.z < 0)
		{
			vel.z *= -1;
		}
		//xとz足した値が0.2よりあれば
		if (vel.x + vel.z > 0.2f)
		{
			float angle = atan2(m_Velocity.z, m_Velocity.x);
			angle += 90 * 3.14159265f / 180;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}
	}
	//Abe20170519

	//Abe20170515
	//ステージの端にいったか判定して向き反転するやつ
	void TackleEnemy::StageEndCheck()
	{
		//位置[右]、[上]、[左]、[下]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x+scale.x,pos.z + scale.z,pos.x - scale.x,pos.z - scale.z);
		//ステージの端に当たってるか判定
		//右
		if (m_StageSize.x < PositionPXYMXY.x)
		{
			pos.x = m_StageSize.x - scale.x;
			m_Velocity.x *= -1;
		}
		//上
		if (m_StageSize.y < PositionPXYMXY.y)
		{
			pos.z = m_StageSize.y - scale.z;
			m_Velocity.z *= -1;
		}
		//左
		if (-m_StageSize.x > PositionPXYMXY.z)
		{
			pos.x = -m_StageSize.x + scale.x;
			m_Velocity.x *= -1;
		}
		//下
		if (-m_StageSize.y > PositionPXYMXY.w)
		{
			pos.z = -m_StageSize.y + scale.z;
			m_Velocity.z *= -1;
		}

	}
	//Abe20170515

	void TackleEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
			/*1A
			//チャージ中のぶれぶれ中心座標を記録
			//m_BurePos = GetComponent<Transform>()->GetPosition();
			*/
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//m_Debugtxt->SetText(Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)) + L"\n" + Util::FloatToWStr(distance*distance));
		//m_Debugtxt->SetText(L"dis:" + Util::FloatToWStr((dis.x*dis.x) + (dis.z*dis.z)));

		//一定時間で探索状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}
	}

	void TackleEnemy::Move()
	{
		//ランダムで2秒くらい進む
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 2)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			//なんかオブジェクトに当たった時はVelocityを反転するけどそれは別のとこでやるわ
			GetComponent<Transform>()->SetPosition(pos);
		}
		else
		{
			ToSearch();
		}
	}

	void TackleEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();
			/*1A
			//攻撃するまでぶれぶれ残り時間に応じて速さを変える
			//if (m_time < m_AttackTime)
			//{
			//	Vector3 pos = m_BurePos;
			//	//割り未満
			//	if (m_time / m_AttackTime < 0.3f)
			//	{
			//		//-0.2〜0.2の間でぶれぶれ
			//		pos += Vector3(rand() % 40 - 20, 0, rand() % 40 - 20) / 100;
			//	}
			//}
			*/
			//攻撃までのチャージが終了
			if (m_time > m_AttackTime)
			{
				m_time = 0;
				m_TackleFlg = true;
				//攻撃した回数加算
				m_AttackCount++;
				//速度計算
				//１体目に突撃
				if (m_TargetNum == 1)
				{
					Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//角度算出
					float angle = atan2(dis.z, dis.x);
					//速度入れる
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
				//２体目に突撃
				else if (m_TargetNum == 2)
				{
					Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
					//角度算出
					float angle = atan2(dis.z, dis.x);
					//速度入れる
					m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
				}
			}
		}
		//m_TackleFlgがtrue、以下突撃中の動作
		else
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();

			//攻撃時間過ぎるまで移動
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity * App::GetApp()->GetElapsedTime();
				GetComponent<Transform>()->SetPosition(pos);
			}
			//突撃時間終わったら
			else
			{
				m_time = 0;
				//攻撃フラグ解除
				m_TackleFlg = false;

				//攻撃した回数が設定された攻撃回数の上限を満たしたら
				if (m_AttackCount >= m_TackleCount)
				{
					ToCoolTime();
				}
			}
		}
	}

	void TackleEnemy::CoolTime()
	{
		//クールタイム過ぎたら索敵状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TackleEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}

	//なんかにぶつかったら速度反転、横と縦どっちがあたったかだけほしぃ
	void TackleEnemy::TurnVecolity(bool flgx, bool flgz)
	{
		if (flgx)
		{
			m_Velocity.x *= -1;
		}
		if (flgz)
		{
			m_Velocity.z *= -1;
		}
	}

	//それぞれの状態へ移行する関数------------------------------------------
	void TackleEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

	}

	void TackleEnemy::ToMove()
	{
		//計算時間初期化
		m_time = 0;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//移動ベクトル(?)計算
		//0.5〜-0.5までランダムで出してスピードかける
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 100;
		m_Velocity *= m_Speed;

		//状態変更
		m_State = MoveS;

	}

	void TackleEnemy::ToAttack(int num)
	{
		//計算時間初期化
		m_time = 0;
		//攻撃する対象を設定
		m_TargetNum = num;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//状態変更
		m_State = AttackS;
	}

	void TackleEnemy::ToCoolTime()
	{
		//計算時間初期化
		m_time = 0;

		//攻撃フラグ解除
		m_TackleFlg = false;
		//攻撃回数リセット
		m_AttackCount = 0;

		//状態変更
		m_State = CoolTimeS;
	}

	//プレイヤーへの攻撃判定
	void TackleEnemy::ToDamagePlayer()
	{
		//攻撃中なら
		if (m_TackleFlg)
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
			ToCoolTime();
		}
	}

	//攻撃受けたとき
	void TackleEnemy::DamagePlayer()
	{
		//もしHPが1以下なら
		if (m_Hp <= 1)
		{
			//タヒぬ
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

			//サークル除去
			m_SearchCircle->SetDrawActive(false);

		}
		else
		{
			m_Hp--;
		}
	}

	void TackleEnemy::Damage(int num)
	{
		//HP減らしてなくなってれば1残す
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
		}
	}

	//************************************************************************
	//	玉撃つエネミー
	//	追記なし？
	//************************************************************************

	ShotEnemy::ShotEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int power, float shotchildinterval, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_Power(power),
		m_ShotChildInterval(shotchildinterval),
		m_ShotAmount(shotamount)
	{}

	void ShotEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"MISSILE_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);	
		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_SearchCircle = circle;
	}

	void ShotEnemy::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			switch (m_State)
			{
				//索敵
			case SearchS:
				Search();
				break;
				//攻撃
			case AttackS:
				Attack();
				break;
			}
		}
	}

	//状態群----------------------------------------------------------
	void ShotEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る、どっちか入ったら状態変化
		Vector3 dis = pos1 - mypos;
		Vector3 dis2 = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance || ((dis2.x*dis.x) + (dis2.z*dis.z) < distance*distance))
		{
			ToAttack();
		}

		//一定時間ごとに停止するように
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 0.8f)
		{
			//回転
			Vector3 rot = Vector3(0, GetComponent<Transform>()->GetRotation().y, 0);
			rot.y += m_rotSpeed * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
			GetComponent<Transform>()->SetRotation(rot);
		}
		else if (m_time > 2.0f)
		{
			m_time = 0;
		}
	}

	void ShotEnemy::Attack()
	{
		float angle = 0;
		//狙ったプレイヤーに向く
		if (m_TargetPlayer == 1)
		{
			Vector3 dif = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			angle = atan2(dif.z, dif.x);
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}
		else
		{
			Vector3 dif = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			angle = atan2(dif.z, dif.x);
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}

		//ミサイル打つ処理
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			//アングル変換
			angle *= 180 / 3.14159265f;
			angle += 360;
			angle = (int)angle % 360;

			//計算用時間初期化
			m_time = 0;

			bool sflg = false;
			//起動してないのあれば再利用
			//同時発射
			for (int i = 0; i < m_ShotAmount; i++)
			{
				for (auto obj : m_MissileS)
				{
					if (!obj->GetDrawActive())
					{
						int Tangle = (int)angle % 360;
						//とりあえず10〜20、-10〜-20度の範囲で飛ばす
						if (rand() % 2 == 0)
						{
							Tangle += rand() % 11 + 10;
						}
						else
						{
							Tangle += rand() % 11 - 20;
						}
						
						float angle2 = Tangle * 3.14159265f / 180;

						//飛ばす向きを決める yは2〜6
						Vector3 tovelo = Vector3(cos(angle2) * m_ShotPower, rand() % 5 + 2, sin(angle2) * m_ShotPower);
						//頭の上から発射
						Vector3 topos = GetComponent<Transform>()->GetPosition();
						topos.y += GetComponent<Transform>()->GetScale().y / 2;
						dynamic_pointer_cast<Missile>(obj)->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);

						//撃ったフラグオン
						sflg = true;

						//狙うプレイヤーを決める
						m_TargetPlayer = rand() % 2 + 1;

						break;
					}
				}
				if (!sflg)
				{
					//作成
					auto objm = GetStage()->AddGameObject<Missile>();
					GetStage()->GetSharedObjectGroup(L"CollisionGroup")->IntoGroup(objm);

					int Tangle = (int)angle % 360;
					//とりあえず10〜20、-10〜-20度の範囲で飛ばす
					if (rand() % 2 == 0)
					{
						Tangle += rand() % 11 + 10;
					}
					else
					{
						Tangle += rand() % 11 - 20;
					}

					float angle2 = Tangle * 3.14159265f / 180;


					//飛ばす向きを決める yは2〜6
					Vector3 tovelo = Vector3(cos(angle2) * m_ShotPower, rand() % 5 + 2, sin(angle2) * m_ShotPower);
					//頭の上から発射
					Vector3 topos = GetComponent<Transform>()->GetPosition();
					topos.y += GetComponent<Transform>()->GetScale().y / 2;
					objm->SetMissileActive(topos, m_MissileScale, tovelo, true, 1);
				}
			}
		}

		//子機を打ち出す間隔になったら
		m_Childtime += App::GetApp()->GetElapsedTime();
		if(m_Childtime > m_ShotChildInterval)
		{ 
			//計算用時間初期化
			m_Childtime = 0;
			//子機はいたフラグオン
			m_ShotChild = true;
			//起動してないのあれば再利用
			bool flgg = false;
			for (auto obj : m_ChildS)
			{
				auto ptr = dynamic_pointer_cast<ShotEnemyChild>(obj);
				//死んでたら再利用
				if (ptr)
				{
					Vector3 PPOS = GetComponent<Transform>()->GetPosition();
					PPOS.y += GetComponent<Transform>()->GetScale().y / 2;
					int Tangle = (int)angle % 360;
					//とりあえず10〜20、-10〜-20度の範囲で飛ばす
					if (rand() % 2 == 0)
					{
						Tangle += rand() % 11 + 10;
					}
					else
					{
						Tangle += rand() % 11 - 20;
					}

					float angle2 = Tangle * 3.14159265f / 180;
					ptr->SetVelocity(Vector3(cos(angle2) * (float)(rand() % 3 + 1) * m_ParScale/2, rand() % 5 + 5, sin(angle2) * (float)(rand() % 3 + 1))* m_ParScale / 2);

					flgg = true;
					break;
				}
			}
			//いなかったら作る
			if (!flgg)
			{
				Vector3 PPOS = GetComponent<Transform>()->GetPosition();
				PPOS.y += GetComponent<Transform>()->GetScale().y/2;
				auto pptr = GetStage()->AddGameObject<ShotEnemyChild>(PPOS, Vector3(1, 1, 1), 2);
				int Tangle = (int)angle % 360;
				//とりあえず10〜20、-10〜-20度の範囲で飛ばす
				if (rand() % 2 == 0)
				{
					Tangle += rand() % 11 + 10;
				}
				else
				{
					Tangle += rand() % 11 - 20;
				}

				float angle2 = Tangle * 3.14159265f / 180;
				pptr->SetVelocity(Vector3(cos(angle2) * (float)(rand() % 3 + 1) * m_ParScale / 2, rand() % 5 + 5, sin(angle2) * (float)(rand() % 3 + 1))* m_ParScale / 2);
				m_ChildS.push_back(pptr);

				//グループに入れる
				GetStage()->GetSharedObjectGroup(L"CollisionGroup")->IntoGroup(pptr);
				GetStage()->GetSharedObjectGroup(L"EnemyGroup")->IntoGroup(pptr);

			}

		}

		//もしある程度離れたら
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る、索敵範囲の1.3倍以上離れたらかつ子機を吐き出してたら索敵状態へ
		Vector3 dis = pos1 - mypos;
		Vector3 dis2 = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) > distance*distance * 1.3f && ((dis2.x*dis.x) + (dis2.z*dis.z) > distance*distance * 1.3f) && m_ShotChild)
		{
			ToSearch();
		}

	}

	//状態変更群----------------------------------------------------------
	void ShotEnemy::ToSearch()
	{
		//時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//吐き出したフラグ解除
		m_ShotChild = false;

		//サークル描画
		m_SearchCircle->SetDrawActive(true);

	}

	void ShotEnemy::ToAttack()
	{
		//時間初期化
		m_time = 0;
		
		//状態変更
		m_State = AttackS;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//狙うプレイヤーを決める
		m_TargetPlayer = rand() % 2+1;
	}

	//Abe20170517
	void ShotEnemy::DamagePlayer()
	{
		//もしHPが1以下なら
		if (m_Hp <= 1)
		{
			//タヒぬ
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

			//サークル除去
			m_SearchCircle->SetDrawActive(false);

		}
		else
		{
			m_Hp--;
		}

	}

	void ShotEnemy::Damage(int num)
	{
		//HP減らしてなくなってれば1残す
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
		}

	}
	//Abe20170517


	//Abe20170508
	//************************************************************************
	//	爆弾置いてテレポートエネミー
	//	追記なし？
	//************************************************************************

	TeleportEnemy::TeleportEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float cooltime, int shotamount) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_CoolTime(cooltime),
		m_ShotAmount(shotamount)
	{}

	void TeleportEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"TELEPORT_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_SearchCircle = circle;

		//ステート初期化
		ToSearch();

		//テレポートポイントを作成
		auto TereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto TereportPtr = GetStage()->AddGameObject<TereportPoint>(posci);
		TereportPtr->SetOnEnemy(true);
		TereportGroup->IntoGroup(TereportPtr);

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色赤に変更
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

		//自分を認識させる番号を決定
		auto Group = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		int count = 0;
		for (auto obj : Group)
		{
			if (dynamic_pointer_cast<TeleportEnemy>(obj.lock()))
			{
				count++;
			}
		}
		//識別番号入れる
		m_number = count;

	}

	void TeleportEnemy::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			switch (m_State)
			{
				//索敵
			case SearchS:
				Search();
				break;
				//攻撃
			case AttackS:
				Attack();
				break;
				//クールタイム
			case CoolTimeS:
				CoolTime();
				break;
			}
		}
	}

	void TeleportEnemy::GoDrawns()
	{
		if (m_Drawns.size() == 0)
		{
			//ドローン作成
			for (int i = 0; i < m_ShotAmount; i++)
			{
				auto Drawn = GetStage()->AddGameObject<SearchDrawn>();
				m_Drawns.push_back(Drawn);
			}
		}

		float angle = 360/m_ShotAmount;
		float TarAngle = 0;
		for (auto obj : m_Drawns)
		{
			auto ptr = dynamic_pointer_cast<SearchDrawn>(obj);
			Vector3 inVel = Vector3(cos(TarAngle*3.14159265f / 180), 0, sin(TarAngle*3.14159265f / 180));
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos.y += 1;
			ptr->GoDrawn(pos, inVel,m_number);
			TarAngle += angle;
		}
	}

	void TeleportEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

	}

	void TeleportEnemy::Attack()
	{
		m_time += App::GetApp()->GetElapsedTime();
		//爆弾置く状態になるまで待機
		if (!m_BombPutFlg)
		{
			//攻撃までの時間過ぎたらテレポート
			if (m_time > m_AttackWaitTime)
			{
				//１体目攻撃
				if (m_TargetNum == 1)
				{
					Vector3 pos = m_Player1->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 50 - 25) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 50 - 25) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}
				//２体目攻撃
				else if (m_TargetNum == 2)
				{
					Vector3 pos = m_Player2->GetComponent<Transform>()->GetPosition();
					pos.x += (rand() % 50 - 25) / 10;
					pos.y = m_InitPos.y;
					pos.z += (rand() % 50 - 25) / 10;
					GetComponent<Transform>()->SetPosition(pos);
				}

				//爆弾置くフラグたてる
				m_BombPutFlg = true;

				//時間リセット
				m_time = 0;
			}
		}
		//爆弾置く
		else
		{
			//爆弾置く前
			if (!m_BombAfterFlg)
			{
				if (m_time > m_BombPutTime)
				{
					//爆弾を生成
					auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
					//置いたかどうか
					bool PutFlg = false;
					//Abe20170512
					int count = 0;
					//Abe20170512
					for (auto obj : BombGroup)
					{
						//Abe20170512
						count++;
						//Abe20170512

						auto ptr = dynamic_pointer_cast<Bomb>(obj.lock());
						if (!ptr->GetDrawActive())
						{
							Vector3 topos = GetComponent<Transform>()->GetPosition();
							topos.y = 1;
							ptr->SetActivePosition(topos);
							PutFlg = true;
							break;
						}
					}
					//使えるやつがなかったら作る
					if (!PutFlg)
					{
						GetStage()->GetSharedObjectGroup(L"BombGroup")->IntoGroup(GetStage()->AddGameObject<Bomb>(GetComponent<Transform>()->GetPosition()));
					}

					//Abe20170512
					//m_Debugtxt->SetText(Util::IntToWStr(count));
					//Abe20170512

					//爆弾置いたフラグをオン
					m_BombAfterFlg = true;

					//時間リセット
					m_time = 0;
				}
			}
			//爆弾置いた後
			else
			{
				auto Group = GetStage()->GetSharedObjectGroup(L"TereportPointGroup")->GetGroupVector();
				//中身の数を数える
				int count = 0;
				//ちょっと汚いけどまあいいべ
				vector<shared_ptr<GameObject>> Target;
				for (auto obj : Group)
				{
					auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
					//自分の足元のテレポートポインtじゃなかったら追加
					if (ptr != m_UnderTereportPoint)
					{
						Target.push_back(ptr);
						count++;
					}
					//足元のなら自分いないことにする
					else
					{
						dynamic_pointer_cast<TereportPoint>(ptr)->SetOnEnemy(false);
					}
				}
				//移動先を決定
				int randnum = rand() % count;
				//移動
				Vector3 targetpos = Target[randnum]->GetComponent<Transform>()->GetPosition();
				targetpos.y = m_InitPos.y;
				GetComponent<Transform>()->SetPosition(targetpos);
				//足元のポイント設定
				m_UnderTereportPoint = Target[randnum];
				dynamic_pointer_cast<TereportPoint>(m_UnderTereportPoint)->SetOnEnemy(true);

				//クールタイムへ
				ToCoolTime();
			}
		}

	}

	void TeleportEnemy::CoolTime()
	{
		//クールタイム過ぎたら索敵状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_CoolTime)
		{
			ToSearch();
			m_time = 0;
		}
	}

	void TeleportEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}

	void TeleportEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

		//子機放出
		GoDrawns();

	}

	void TeleportEnemy::ToAttack(int num)
	{
		m_time = 0;

		m_TargetNum = num;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		m_State = AttackS;

		//子機収納
		for (auto obj : m_Drawns)
		{
			dynamic_pointer_cast<SearchDrawn>(obj)->UpDrawns();

		}
	}


	void TeleportEnemy::ToCoolTime()
	{
		//計算時間初期化
		m_time = 0;

		//爆弾置く状態初期化
		m_BombPutFlg = false;
		//爆弾置いた状態初期化
		m_BombAfterFlg = false;

		//状態変更
		m_State = CoolTimeS;

	}
	//Abe20170508

	//Abe20170512
	//攻撃受けたとき
	void TeleportEnemy::DamagePlayer()
	{
		//もしHPが1以下なら
		if (m_Hp <= 1)
		{
			//タヒぬ
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

			//サークル除去
			m_SearchCircle->SetDrawActive(false);

		}
		else
		{
			m_Hp--;
		}
	}

	void TeleportEnemy::Damage(int num)
	{
		//HP減らしてなくなってれば1残す
		m_Hp += -num;
		if (m_Hp < 0)
		{
			m_Hp = 1;
		}
	}
	//Abe20170512

	//************************************************************************
	//	自爆エネミー
	//	追記なし？
	//************************************************************************
	BombEnemy::BombEnemy(const shared_ptr<Stage>& StagePtr, Vector3 pos, float parscale, int hp, float searchdistance, float speed, int power) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_ParScale(parscale),
		m_Hp(hp),
		m_SearchDistance(searchdistance),
		m_Speed(speed),
		m_Power(power)
	{}

	void BombEnemy::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(Vector3(m_ParScale, m_ParScale, m_ParScale));
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"BOMBENEMY_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);

		//ステート初期化
		m_State = SearchS;

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		Vector3 posci = m_InitPos;
		//足元へ移動
		posci.y = 1;
		TransCi->SetPosition(posci);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_SearchCircle = circle;

	}

	void BombEnemy::OnUpdate()
	{
		//生きてれば
		if (m_ActiveFlg)
		{
			//m_Debugtxt->SetText(Util::IntToWStr(m_State));

			switch (m_State)
			{
				//索敵
			case SearchS:
				Search();
				break;
				//探索
			case MoveS:
				Move();
				break;
				//攻撃
			case AttackS:
				Attack();
				break;
			}

			//Abe20170519
			//回転
			Rot();
			//Abe20170519

		}


	}

	//Abe20170519
	void BombEnemy::Rot()
	{
		//持ってる速度から角度算出
		Vector3 vel = m_Velocity;
		//マイナス反転(absは重いので使いません)
		if (vel.x < 0)
		{
			vel.x *= -1;
		}
		if (vel.z < 0)
		{
			vel.z *= -1;
		}
		//xとz足した値が0.2よりあれば
		if (vel.x + vel.z > 0.2f)
		{
			float angle = atan2(m_Velocity.z, m_Velocity.x);
			angle += 90 * 3.14159265f / 180;
			GetComponent<Transform>()->SetRotation(0, angle, 0);
		}
	}
	//Abe20170519

	void BombEnemy::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(1);
		
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			ToAttack(2);
		}

		//一定時間で探索状態へ
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_moveInterval)
		{
			ToMove();
		}

	}

	void BombEnemy::Move()
	{
		//ランダムで2秒くらい進む
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time < 2)
		{
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			//なんかオブジェクトに当たった時はVelocityを反転するけどそれは別のとこでやるわ
			GetComponent<Transform>()->SetPosition(pos);
		}
		else
		{
			ToSearch();
		}
	}

	void BombEnemy::Attack()
	{
		if (!m_TackleFlg)
		{
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();
			
			//攻撃までのチャージが終了
			if (m_time > m_AttackTime)
			{
				m_time = 0;
				m_TackleFlg = true;	
			}
		}
	
		
		//m_TackleFlgがtrue、以下突撃中の動作
		else
		{
			//速度計算
			//１体目に突撃
			if (m_TargetNum == 1)
			{
				Vector3 dis = m_Player1->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

				//角度算出
				float angle = atan2(dis.z, dis.x);
				//速度入れる
				m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
			}
			//２体目に突撃
			else
			{
				Vector3 dis = m_Player2->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

				//角度算出
				float angle = atan2(dis.z, dis.x);
				//速度入れる
				m_Velocity = Vector3(cos(angle), 0, sin(angle)) * m_Speed;
			}
			
			//時間加算
			m_time += App::GetApp()->GetElapsedTime();

			//攻撃時間過ぎるまで移動
			if (m_time < m_TackleTime)
			{
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity/10;
				GetComponent<Transform>()->SetPosition(pos);
			}
			//突撃時間終わったら
			else 
			{
				m_time = 0;
				//攻撃フラグ解除
				//m_TackleFlg = false;

				//突撃後、自爆の為消滅
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;
			}
		}
	}


	void BombEnemy::CircleMove()
	{
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		//足元へ移動
		pos.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);
		m_SearchCircle->SetDrawActive(true);
	}




	//それぞれの状態へ移行する関数------------------------------------------
	void BombEnemy::ToSearch()
	{
		//計算時間初期化
		m_time = 0;

		//状態変更
		m_State = SearchS;

		//サークル移動
		CircleMove();

	}

	void BombEnemy::ToMove()
	{
		//計算時間初期化
		m_time = 0;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//移動ベクトル(?)計算
		//0.5〜-0.5までランダムで出してスピードかける
		m_Velocity = Vector3(rand() % 100 - 50, 0, rand() % 100 - 50);
		m_Velocity /= 20; //100
		m_Velocity *= m_Speed;

		//状態変更
		m_State = MoveS;

	}

	void BombEnemy::ToAttack(int num)
	{
		//計算時間初期化
		m_time = 0;
		//攻撃する対象を設定
		m_TargetNum = num;

		//サークル除去
		m_SearchCircle->SetDrawActive(false);

		//状態変更
		m_State = AttackS;
	}


	//プレイヤーへの攻撃判定
	void BombEnemy::ToDamagePlayer()
	{
		//攻撃中なら
		if (m_TackleFlg)
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(3);
			PtrPlayerHP->SetHit(true);

			//自爆の為消滅
			SetDrawActive(false);
			m_Hp = 0;
			m_ActiveFlg = false;

		}

	}
		void BombEnemy::DamagePlayer()
		{	
				//タヒぬ
				SetDrawActive(false);
				m_Hp = 0;
				m_ActiveFlg = false;
		
		}

	//Abe20170508
	//======================以下子機群=======================
	//************************************************************************
	//	爆弾の爆発の部分
	//	拡縮だけでいいかな？
	//************************************************************************
	BombEffect::BombEffect(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void BombEffect::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(1, 1, 1);
		Trans->SetRotation(0, 0, 45 * 3.14159265f / 180);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(L"BOMBEFFECT_TX");
		//透明処理
		SetAlphaActive(true);
		SetDrawActive(false);
	}

	void BombEffect::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			switch (m_State)
			{
			case 0:
				//でっかくなる状態
				if (true)
				{
					Vector3 Scale = GetComponent<Transform>()->GetScale();
					if (Scale.x < 5.0f)
					{
						Scale *= 1.5f;
						GetComponent<Transform>()->SetScale(Scale);
					}
					else
					{
						m_State = 1;
					}
				}
				break;
				//ちっちゃくなる
			case 1:
				if (true)
				{
					Vector3 Scale = GetComponent<Transform>()->GetScale();
					if (Scale.x > 0.2f)
					{
						Scale *= 0.8f;
						GetComponent<Transform>()->SetScale(Scale);
					}
					else
					{
						m_State = 2;
					}
				}
				break;
				//終了処理
			case 2:
				//起動終了
				m_ActiveFlg = false;
				//状態初期化
				m_State = 0;
				SetDrawActive(false);
				break;
			}
		}
	}

	void BombEffect::SetPosActive(Vector3 pos)
	{
		m_ActiveFlg = true;
		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}

	//************************************************************************
	//	爆弾
	//	一定時間で起動
	//************************************************************************
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos, float scale, float bombdistance, float power, float explosiontime) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_Scale(Vector3(scale, scale, scale)),
		m_BombDistance(bombdistance),
		m_Power(power),
		m_ExplosionTime(explosiontime)
	{}

	//引数ポジションのみ。ていうか基本こっち使ってほしい
	Bomb::Bomb(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_InitPos(pos)
	{
		//その他決定
		m_Scale = Vector3(1, 1, 1);
		m_BombDistance = 6.0f;
		m_Power = 3.0f;
		m_ExplosionTime = 3.0f;
	}

	void Bomb::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_InitPos);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"BOMB_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);
		//透明処理
		SetAlphaActive(true);

		m_time = 0;

		m_Effect = GetStage()->AddGameObject<BombEffect>();
	}

	void Bomb::OnUpdate()
	{
		if (m_Activeflg)
		{
			m_time += App::GetApp()->GetElapsedTime();
			if (m_time > m_ExplosionTime)
			{
				BombExplosion();
			}
		}
	}

	//挟まれたら爆発
	void Bomb::BombExplosion()
	{
		//動かなく
		m_Activeflg = false;
		SetDrawActive(false);
		//爆風作成
		m_Effect->SetPosActive(GetComponent<Transform>()->GetPosition());


		//判定
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		auto Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		auto Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//プレイヤーの座標を持ってくる
		Vector3 ppos1 = Player1->GetComponent<Transform>()->GetPosition();
		Vector3 ppos2 = Player2->GetComponent<Transform>()->GetPosition();

		//距離を測る(プレイヤー同士の体の大きさは変わらないと思うので1体目を参照)
		float half = Player1->GetComponent<Transform>()->GetScale().x / 2 + m_BombDistance / 2;
		//平方根とらないように
		half *= half;
		//それぞれの差を計算
		Vector3 dist1 = GetComponent<Transform>()->GetPosition() - Player1->GetComponent<Transform>()->GetPosition();
		Vector3 dist2 = GetComponent<Transform>()->GetPosition() - Player2->GetComponent<Transform>()->GetPosition();
		dist1 = dist1 * dist1;
		dist2 = dist2 * dist2;

		//どっちか当たる
		if (half > dist1.x + dist1.z || half > dist2.x + dist2.z)
		{
			//ダメージを与える
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(m_Power);
			PtrPlayerHP->SetHit(true);
		}
	}

	//再利用
	void Bomb::SetActivePosition(Vector3 pos)
	{
		m_time = 0;
		m_Activeflg = true;

		SetDrawActive(true);

		GetComponent<Transform>()->SetPosition(pos);
	}


	//************************************************************************
	//	テレポートエネミーのテレポート先
	//	一定時間で起動
	//************************************************************************
	TereportPoint::TereportPoint(const shared_ptr<Stage>& StagePtr, Vector3 pos) :
		GameObject(StagePtr),
		m_Pos(pos)
	{}

	void TereportPoint::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Pos);
		Trans->SetScale(2, 2, 2);
		Trans->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto Draw = AddComponent<PNTStaticDraw>();
		Draw->SetTextureResource(L"TEREPORTPOINT_TX");
		Draw->SetMeshResource(L"DEFAULT_SQUARE");

		SetAlphaActive(true);

		//レイヤー設定
		SetDrawLayer(1);
	}
	//Abe20170508

	//Abe20170512
	//************************************************************************
	//	索敵ドローン
	//	プレイヤー見つけるまで探索
	//************************************************************************
	SearchDrawn::SearchDrawn(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}
	
	void SearchDrawn::OnCreate()
	{
		//座標、大きさ、回転
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0,0,0);
		Trans->SetScale(0.5f, 0.5f, 0.5f);
		Trans->SetRotation(0, 0, 0);


		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"SEARCHDRAWN_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);

		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//索敵範囲作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		TransCi->SetPosition(0,1,0);
		TransCi->SetScale(Vector3(m_SearchDistance, m_SearchDistance, m_SearchDistance));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SEARCHCIRCLE_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		circle->SetDrawActive(false);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_SearchCircle = circle;

		//Abe20170515
		//ステージの大きさ取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515

	}

	void SearchDrawn::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//プレイヤーを見つけていないとき
			if (!m_FindPlayerFlg)
			{
				//切り替え時間越えたら向き替え
				m_time += App::GetApp()->GetElapsedTime();
				if (m_time > m_ChangeTime)
				{
					m_Velocity = Vector3(rand() % 200-100, 0, rand() % 200-100) / 100;

					m_time = 0;
				}

				//移動
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos += m_Velocity * App::GetApp()->GetElapsedTime() * m_Speed;
				GetComponent<Transform>()->SetPosition(pos);

				//サークル移動
				pos.y = 1;
				m_SearchCircle->GetComponent<Transform>()->SetPosition(pos);

				//見つける判定
				Search();
				//ステージの端の判定
				StageEndCheck();
			}
			//見つけた
			else
			{
				//上に移動
				Vector3 pos = GetComponent<Transform>()->GetPosition();
				pos.y += 5*m_Speed * App::GetApp()->GetElapsedTime();
				GetComponent<Transform>()->SetPosition(pos);

				//20以上行ったら
				if (pos.y > 20)
				{
					SetDrawActive(false);
					m_ActiveFlg = false;
					m_FindPlayerFlg = false;
				}
			}
		}
	}

	void SearchDrawn::Search()
	{
		//位置情報取得
		Vector3 mypos = GetComponent<Transform>()->GetPosition();
		Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
		Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
		float distance = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + m_SearchDistance / 2;

		//距離を測る
		//１体目
		Vector3 dis = pos1 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			m_FindPlayerFlg = true;
			//自分の番号と一致するテレポートのやつを起動
			auto EnemyGrouP = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			for (auto obj : EnemyGrouP)
			{
				//テレポートエネミーにキャスト
				auto ptr = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
				if (ptr)
				{
					//自分の番号と一致
					if (ptr->GetNumber() == m_number)
					{
						ptr->ToAttack(1);
						break;
					}
				}
			}
		}
		//２体目
		dis = pos2 - mypos;
		if ((dis.x*dis.x) + (dis.z*dis.z) < distance*distance)
		{
			m_FindPlayerFlg = true;

			//自分の番号と一致するテレポートのやつを起動
			auto EnemyGrouP = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			for (auto obj : EnemyGrouP)
			{
				//テレポートエネミーにキャスト
				auto ptr = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
				if (ptr)
				{
					//自分の番号と一致
					if (ptr->GetNumber() == m_number)
					{
						ptr->ToAttack(2);
						break;
					}
				}
			}

		}

	}

	void SearchDrawn::GoDrawn(Vector3 pos,Vector3 vel, int num)
	{
		//座標移動
		Vector3 pos1 = pos;
		pos1.y += 1;
		GetComponent<Transform>()->SetPosition(pos);
		//移動力設定
		m_Velocity = vel;

		//番号
		m_number = num;

		//起動
		m_ActiveFlg = true;
		
		//可視化
		SetDrawActive(true);

		m_time = 0;
		
		//サークル描画
		m_SearchCircle->SetDrawActive(true);
		Vector3 pos2 = pos;
		pos2.y = 1;
		m_SearchCircle->GetComponent<Transform>()->SetPosition(pos2);

	}

	//Abe20170515
	//ステージの端にいったか判定して向き反転するやつ
	void SearchDrawn::StageEndCheck()
	{
		//位置[右]、[上]、[左]、[下]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x + scale.x, pos.z + scale.z, pos.x - scale.x, pos.z - scale.z);
		//ステージの端に当たってるか判定
		//右
		if (m_StageSize.x < PositionPXYMXY.x)
		{
			pos.x = m_StageSize.x - scale.x;
			m_Velocity.x *= -1;
		}
		//上
		if (m_StageSize.y < PositionPXYMXY.y)
		{
			pos.z = m_StageSize.y - scale.z;
			m_Velocity.z *= -1;
		}
		//左
		if (-m_StageSize.x > PositionPXYMXY.z)
		{
			pos.x = -m_StageSize.x + scale.x;
			m_Velocity.x *= -1;
		}
		//下
		if (-m_StageSize.y > PositionPXYMXY.w)
		{
			pos.z = -m_StageSize.y + scale.z;
			m_Velocity.z *= -1;
		}

	}
	//Abe20170515

	void SearchDrawn::UpDrawns()
	{
		m_FindPlayerFlg = true;
		//サークル消す
		m_SearchCircle->SetDrawActive(false);

	}
	//Abe20170512

	//Abe20170515
	//************************************
	//	ミサイル
	//	ステージの端に行くか物に当たるまで
	//	向いてる方向に移動
	//************************************
	Missile::Missile(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void Missile::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(0, 0, 0);
		Trans->SetRotation(0, 0, 0);

		//モデルとトランスフォームの間の差分
		Matrix4X4 Mat;
		Mat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0.0f, -90 * 3.14159265f / 180, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		//見た目
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"MISSILE_MODEL");
		//モデル大きさ調整
		Draw->SetMeshToTransformMatrix(Mat);

		//透明処理
		SetAlphaActive(true);
		SetDrawActive(false);

		//Abe20170515
		//ステージの大きさ取得
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_StageSize = ScenePtr->GetStageSize() / 2;
		//Abe20170515

		//Abe20170517
		m_Effect = GetStage()->AddGameObject<BombEffect>();
		//Abe20170517

		//Abe20170519
		//影作成
		auto circle = GetStage()->AddGameObject<GameObject>();
		auto TransCi = circle->AddComponent<Transform>();
		TransCi->SetPosition(0, 1, 0);
		TransCi->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		TransCi->SetRotation(90 * 3.14159265 / 180, 0, 0);

		auto DrawCi = circle->AddComponent<PNTStaticDraw>();
		DrawCi->SetTextureResource(L"SHOADOW_TX");
		DrawCi->SetMeshResource(L"DEFAULT_SQUARE");

		circle->SetAlphaActive(true);
		circle->SetDrawActive(false);
		//レイヤー設定
		circle->SetDrawLayer(2);

		m_Shadow = circle;
		//Abe20170519
	}

	void Missile::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//座標移動
			Vector3 pos = GetComponent<Transform>()->GetPosition();
			pos += m_Velocity * App::GetApp()->GetElapsedTime();
			GetComponent<Transform>()->SetPosition(pos);
			
			//影移動
			pos.y = 1;
			m_Shadow->GetComponent<Transform>()->SetPosition(pos);
			if (m_FallFlg)
			{
				//ちょっと遅めに落とす
				m_Velocity.y += -9.8f * App::GetApp()->GetElapsedTime() / 3;

				//床に近くなったら消す
				if (GetComponent<Transform>()->GetPosition().y <= 0.5f)
				{
					DeleteMissile();
				}
			}
			StageEndCheck();
		}
	}

	//ステージの端に行ったかを判定する
	void Missile::StageEndCheck()
	{
		//位置[右]、[上]、[左]、[下]
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		Vector3 scale = GetComponent<Transform>()->GetScale();
		Vector4 PositionPXYMXY = Vector4(pos.x + scale.x, pos.z + scale.z, pos.x - scale.x, pos.z - scale.z);
		//ステージの端に当たってるか判定
		//右
		if (m_StageSize.x < PositionPXYMXY.x ||
			m_StageSize.y < PositionPXYMXY.y ||
			-m_StageSize.x > PositionPXYMXY.z ||
			-m_StageSize.y > PositionPXYMXY.w
			)
		{
			//当たってたら消す
			DeleteMissile();
		}

	}
	void Missile::SetMissileActive(Vector3 pos, Vector3 scale, Vector3 velocity,bool falltype,int power)
	{
		//座標移動
		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(pos);
		Trans->SetScale(scale);
		
		//加速度追加
		m_Velocity = velocity;

		//起動
		m_ActiveFlg = true;

		//描画
		SetDrawActive(true);
		//影も
		m_Shadow->SetDrawActive(true);

		//落ちるフラグ設定
		m_FallFlg = falltype;

		//攻撃力設定
		m_power = power;
	}

	void Missile::DeleteMissile()
	{
		if (m_ActiveFlg)
		{
			//爆風作成
			m_Effect->SetPosActive(GetComponent<Transform>()->GetPosition());

			//終了
			m_ActiveFlg = false;

			//描画消す
			SetDrawActive(false);

			//影も
			m_Shadow->SetDrawActive(false);
		}
	}
	//Abe20170515

	//Abe20170517
	void Missile::ToDamagePleyer()
	{
		////落ちる設定にされてるときはy座標を測る
		//if (m_FallFlg)
		//{
		//	float PlayerY = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->GetComponent<Transform>()->GetPosition().y;
		//	//ちょっと上に
		//	PlayerY += GetComponent<Transform>()->GetScale().y / 2;
		//	//プレイヤーより結構上のほうにいたら判定しない
		//	if (GetComponent<Transform>()->GetPosition().y > PlayerY)
		//	{
		//		return;
		//	}
		//}

		//HPを減らす
		auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
		PtrPlayerHP->SetDamage_int(1);
		PtrPlayerHP->SetHit(true);

		//ミサイルを消去
		DeleteMissile();
	}
	//Abe20170517

	//索敵サークル
	SearchCircle::SearchCircle(const shared_ptr<Stage>& StagePtr) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + L"EF\\", L"NewAnimation.ssae", L"anime_1",true)
	{
	}
	void SearchCircle::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 2, 0);
		Trans->SetScale(5,1, 5);
		Trans->SetRotation(0, 0, 0);
		SS5ssae::OnCreate();
		SetAlphaActive(true);
		SetDrawActive(true);
		SetDrawLayer(10);
	}
	void SearchCircle::OnUpdate() {
		SetLooped(true);
	}
}
