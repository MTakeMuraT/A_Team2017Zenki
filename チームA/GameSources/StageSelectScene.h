#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g
	//--------------------------------------------------------------------------------------
	class StageSelectScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

	public:
		//�\�z�Ɣj��
		StageSelectScene() :Stage() {}
		//������
		virtual void OnCreate()override;
	};


}
