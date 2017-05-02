#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//************************************
	//	円形アタリ判定
	//	距離で判定、座標のマイナス反転して加算した分が2(プレイヤーの半径[1]*2)以下のもののみ判定
	//************************************
	CollisionManager::CollisionManager(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void CollisionManager::OnCreate()
	{

	}

	void CollisionManager::OnUpdate()
	{

	}

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