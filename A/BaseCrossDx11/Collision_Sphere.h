//************************************
//*		作成日：2017/04/10
//*		作成者：Abe
//*		内容：
//*		球体のアタリ判定関数、２体のプレイヤーの角度の差を計算する関数を持つ
//************************************


#pragma once
#include "stdafx.h"

namespace basecross {

	class Collision_Sphere : public GameObject
	{
	private :
		//一回前の呼び出しで当たってるかどうか
		bool m_beforeCollisionFlg = false;
		//今回の呼び出しで当たってるか
		bool m_nowCollisionFlg = false;

		//現在の状態
		//上から当たった瞬間フラグ、当たってる最中フラグ、離れた瞬間フラグ
		bool m_OnCollisionFlg = false;
		bool m_StayCollisionFlg = false;
		//bool m_ExitCollisionFlg = false;
		
	public :
		Collision_Sphere(const shared_ptr<Stage>& StagePtr):GameObject(StagePtr) {};

		//当たってるかどうか判定
		void CollisionTest(Vector3 TargetPos, Vector3 PlayerPos1, Vector3 PlayerPos2, Vector3 TargetScale, Vector3 PlayerScale);

		//フラグとれる
		bool GetOnCollisionFlg() { return m_OnCollisionFlg; };
		bool GetStayCollisionFlg() { return m_StayCollisionFlg; };
		//bool GetExitCollisionFlg() { return m_ExitCollisionFlg; };
	};
}