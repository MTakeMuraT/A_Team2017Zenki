#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g
	//--------------------------------------------------------------------------------------
	class  StageSelect: public Stage 
	{
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}