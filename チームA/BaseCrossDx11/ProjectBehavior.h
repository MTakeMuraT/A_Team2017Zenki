/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	プレイヤーの行動クラス
	//--------------------------------------------------------------------------------------
	class PlayerBehavior : public Behavior {
		//最高速度
		float m_MaxSpeed;
		//減速率
		float m_Decel;
		//質量
		float m_Mass;
		
		Vector3 GetMoveVector() const;
	    Vector3	GetMoveVector_Second() const;
	public:
		
		PlayerBehavior(const shared_ptr<GameObject>& GameObjectPtr) :
			Behavior(GameObjectPtr),
			m_MaxSpeed(10.0f),	//最高速度
			m_Decel(0.95f),	//減速値
			m_Mass(0.5f)	//質量
		{}
		virtual ~PlayerBehavior() {}
		float GetMaxSpeed() const {
			return m_MaxSpeed;
		}

		float GetDecel() const {
			return m_Decel;
		}

		float GetMass() const {
			return m_Mass;
		}

		void MovePlayer();
		void MovePlayer_Second();
		
	};



}

//end basecross

