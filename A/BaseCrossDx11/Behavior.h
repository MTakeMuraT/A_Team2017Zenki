#pragma once
#include "stdafx.h"

namespace basecross
{
	//テンプレートによる行動関数の実装
	//--------------------------------------------------------------------------------------
	//	待機行動クラス
	//--------------------------------------------------------------------------------------
	template<typename T>
	class WaitBehavior_calse {
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"Wait");
		}
		void Excute(const shared_ptr<T>& Obj) {
			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

	//--------------------------------------------------------------------------------------
	//	移動行動クラス
	//--------------------------------------------------------------------------------------
	template<typename T>
	class WalkBehavior_calse {
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"walk");
		}
		void Excute(const shared_ptr<T>& Obj) {
			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

	//--------------------------------------------------------------------------------------
	//	ダメージ行動クラス
	//--------------------------------------------------------------------------------------
	template<typename T>
	class DamageBehavior_calse {
		int m_Count;
		float m_MixCunt;
	public:
		void Enter(const shared_ptr<T>& Obj) {
			auto PtrDraw = Obj->GetComponent<PNTBoneModelDraw>();
			PtrDraw->ChangeCurrentAnimation(L"Damage");
			auto ElapsedTime = App::GetApp()->GetElapsedTime();
			m_Count = 0;
			m_MixCunt = 5.0f;
		}
		void Excute(const shared_ptr<T>& Obj) {
			
			if (m_Count > m_MixCunt) {
				m_Count = 0;
				//ステート移動
				Obj->ChangeWaitState();
			}

			Obj->UpdateAnyAnimation();
		}
		void Exit(const shared_ptr<T>& Obj) {

		}
	};

}