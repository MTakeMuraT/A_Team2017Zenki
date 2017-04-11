#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Collision_Sphere::CollisionTest(Vector3 TargetPos, Vector3 PlayerPos1, Vector3 PlayerPos2, Vector3 TargetScale, Vector3 PlayerScale)
	{
		//プレイヤーとの接触範囲(全部Xでとってます)
		float ColLength = TargetScale.x + PlayerScale.x;
		Vector3 def = PlayerPos1 - TargetPos;
		//１体目当たってなければ出る
		if (ColLength*ColLength < (def.x*def.x) + (def.y*def.y))
		{
			return;
		}
		
		def = PlayerPos2 - TargetPos;

		//２体目当たってなければ出る
		if (ColLength*ColLength < (def.x*def.x) + (def.y*def.y))
		{
			return;
		}

		//どっちも当たってたら判定

		//２体目の角度
		int angle2 = atan2(def.z, def.x);
		angle2 += 360;
		angle2 %= 360;

		//１体目の角度
		def = PlayerPos1 - TargetPos;
		int angle1 = atan2(def.z, def.x);
		//マイナスを反転
		angle1 += 360;
		angle1 %= 360;

		//前回の情報を更新
		m_beforeCollisionFlg = m_nowCollisionFlg;

		//離れた瞬間をリセット
		//m_ExitCollisionFlg = false;

		//プレイヤーが対角(±３０度以内)にいるか
		int angledef = abs(angle2 - angle1);
		if (angledef >= 120 && angledef <= 220)
		{
			m_nowCollisionFlg = true;
		}
		else
		{
			m_nowCollisionFlg = false;
		}

		//当たってる間
		if (m_nowCollisionFlg && m_beforeCollisionFlg)
		{
			m_StayCollisionFlg = true;
		}
		////離れた瞬間
		//if (!m_nowCollisionFlg && m_beforeCollisionFlg)
		//{
		//	m_ExitCollisionFlg = true;
		//}
	}

}