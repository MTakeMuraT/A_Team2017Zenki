#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TutorialScene : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();

	public:
		//�\�z�Ɣj��
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}