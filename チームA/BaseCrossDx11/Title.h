#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g��
	//--------------------------------------------------------------------------------------
	class Title : public Stage {
		//���\�[�X�̍쐬
		void CreateResourses();
		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�摜�쐬
		void CreateBack();
	public:
		//�\�z�Ɣj��
		Title() :Stage() {}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};


}
