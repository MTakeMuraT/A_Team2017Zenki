#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g��
	//--------------------------------------------------------------------------------------
	class Title : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};


}
