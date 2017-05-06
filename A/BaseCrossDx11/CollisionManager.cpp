#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//************************************
	//	円形アタリ判定
	//	距離で判定、座標のマイナス反転して加算した分が2(プレイヤーの半径[1]*2)以下のもののみ判定
	//************************************
	//Abe20170504
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void CollisionManager::OnCreate()
	{
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

	}

	void CollisionManager::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//プレイヤーの座標を持ってくる
			Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();

			//アタリ判定を行うオブジェクトが入ってるグループを持ってくる
			auto ColGroupVec = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();

			//オブジェクト数分ループ
			for (auto obj : ColGroupVec)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				//距離を測る(プレイヤー同士の体の大きさは変わらないと思うので1体目を参照)
				float half = m_Player1->GetComponent<Transform>()->GetScale().x / 2 + ptr->GetComponent<Transform>()->GetScale().x / 2;
				//平方根とらないように
				half *= half;
				//それぞれの差を計算
				Vector3 dist1 = ptr->GetComponent<Transform>()->GetPosition() - m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 dist2 = ptr->GetComponent<Transform>()->GetPosition() - m_Player2->GetComponent<Transform>()->GetPosition();
				dist1 = dist1 * dist1;
				//軽い計算で反転
				if (dist1.x < 0)
				{
					dist1.x *= -1;
				}
				if (dist1.z < 0)
				{
					dist1.z *= -1;
				}
				//dist2 *= dist2;		//どうやら、ないみたいだね
				dist2 = dist2 * dist2;
				if (dist2.x < 0)
				{
					dist2.x *= -1;
				}
				if (dist2.z < 0)
				{
					dist2.z *= -1;
				}

				//一体目があたる
				if (half > dist1.x + dist1.z)
				{
					CollisionAfter(ptr, 1);
				}
				//二体目があたる
				if (half > dist2.x + dist2.z)
				{
					CollisionAfter(ptr, 2);
				}
			}
		}
	}

	void CollisionManager::CollisionAfter(shared_ptr<GameObject> obj , int num)
	{
		//switch使ってもいいけどなんか見づらかったので
		//ていうか一部共通でよくね？←共通するの別で作りました
		//一体目に当たる
		if (num == 1)
		{
			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
			//	m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
			//************************************************************
			//	↑みたいな感じであたったオブジェクトごとにコードを書いてく(↑のは消してもいいよ?デバッグ用だし、確認済みだし)
			//************************************************************
		}
		//二体目に当たる
		else if (num == 2)
		{
			//==============================================
			//if (dynamic_pointer_cast<Enemy01>(obj))
			//{
				//m_Debugtxt->SetText(L"DAMAGE!!");
			//}
			//==============================================
		}
		//共通する部分---------------------------------------------------------

		//==============================================
		if (dynamic_pointer_cast<Enemy01>(obj))
		{
			//m_Debugtxt->SetText(L"DAMAGE!!");
		}
		//==============================================
		//************************************************************
		//	↑みたいな感じで(ry
		//************************************************************

		//==============================================
		//突撃エネミー(TackleEnemy)
		if (dynamic_pointer_cast<TackleEnemy>(obj))
		{
			dynamic_pointer_cast<TackleEnemy>(obj)->ToDamagePlayer();
		}
		//==============================================


		//ミサイルにあたったら
		if (dynamic_pointer_cast<ShotEnemyChildMissile>(obj))
		{
			//HPを減らす
			auto PtrPlayerHP = GetStage()->GetSharedGameObject<PlayerHP>(L"PlayerHP", false);
			PtrPlayerHP->SetDamage_int(1);
			PtrPlayerHP->SetHit(true);
		}

		//共通する部分---------------------------------------------------------

	}
	//Abe20170504

	//************************************
	//	はさむ時の判定
	//	資料「挟まれる判定考察.txt」を参照
	//************************************

	CollisionSand::CollisionSand(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void CollisionSand::OnCreate()
	{
		//プレイヤーのアクセサー的なのをはじめにもってきておく
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(0,0,0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);
	}

	void CollisionSand::OnUpdate()
	{
		if (m_ActiveFlg)
		{
			//それぞれの座標を持ってくる
			Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
			Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

			//pos1のほうに値が小さいほうをいれる
			if (pos1.x > pos2.x)
			{
				float work = pos2.x;
				pos2.x = pos1.x;
				pos1.x = work;
			}
			//Zの値
			if (pos1.z > pos2.z)
			{
				float work = pos2.z;
				pos2.z = pos1.z;
				pos1.z = work;
			}

			//プレイヤー同士の距離がある程度近ければ判定
			//距離確認用
			//wstring txt;
			//txt += L"dist : " + Util::FloatToWStr(pos2.x-pos1.x + pos2.z - pos1.z);
			//m_Debugtxt->SetText(txt);

			//大体4,4(scaleの2倍*2)でいいかな
			float dist = m_Player1->GetComponent<Transform>()->GetScale().x * 2 + m_Player2->GetComponent<Transform>()->GetScale().x * 2;
			if (pos2.x - pos1.x + pos2.z - pos1.z < dist)
			{
				//エネミーの数だけループ
				//プレイヤーの間にいなければ判定はしない
				auto EGroupVec = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
				for (auto obj : EGroupVec)
				{
					//ポインターと座標持ってくる
					auto eptr = dynamic_pointer_cast<GameObject>(obj.lock());
					Vector3 epos = eptr->GetComponent<Transform>()->GetPosition();
					//若干判定緩めるために半径タス
					Vector3 escale = eptr->GetComponent<Transform>()->GetScale() /2;
					//2体のプレイヤーの間にいるか
					if ((pos1.x-escale.x < epos.x && epos.x < pos2.x + escale.x) &&
						(pos1.z-escale.z < epos.z && epos.z < pos2.z + escale.z))
					{
						//挟んだ後の処理
						SandAfter(eptr);
						//確認用
						//m_Debugtxt->SetText(L"sand");
					}
					//座標表示
					//wstring txt2;
					//txt2 += L"pos1.x : " + Util::FloatToWStr(pos1.x) + L"\npos1.z : " + Util::FloatToWStr(pos1.z);
					//txt2 += L"\npos2.x : " + Util::FloatToWStr(pos2.x) + L"\npos2.z : " + Util::FloatToWStr(pos2.z);
					//txt2 += L"\nepos.x : " + Util::FloatToWStr(epos.x) + L"\nepos.z : " + Util::FloatToWStr(epos.z);
					//m_Debugtxt->SetText(txt2);
					//２体の間にいなかったらその回は終了
				}
			}
			//else
			//{
				//m_Debugtxt->SetText(L"NOsand");
			//}
		}
	}

	//挟んだ後
	void CollisionSand::SandAfter(shared_ptr<GameObject> obj)
	{
		if (dynamic_pointer_cast<Enemy01>(obj))
		{
			dynamic_pointer_cast<Enemy01>(obj)->SandAfter();
		}
	}
}