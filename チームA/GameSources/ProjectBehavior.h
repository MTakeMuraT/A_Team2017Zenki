/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	///	�v���C���[�̍s���N���X
	//--------------------------------------------------------------------------------------
	class PlayerBehavior : public Behavior {
		//�ō����x
		float m_MaxSpeed;
		//������
		float m_Decel;
		//����
		float m_Mass;
		
		Vector3 GetMoveVector() const;
	    Vector3	GetMoveVector_Second() const;
	public:
		
		PlayerBehavior(const shared_ptr<GameObject>& GameObjectPtr) :
			Behavior(GameObjectPtr),
			m_MaxSpeed(10.0f),	//�ō����x
			m_Decel(0.95f),	//�����l
			m_Mass(0.5f)	//����
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

