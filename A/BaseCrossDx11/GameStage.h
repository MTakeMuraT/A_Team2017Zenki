/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage
	{

		//�r���[�̍쐬
		void CreateViewLight();
		// �w�i
		void CreateBackGround();
		void CreatePlate();


	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}

		//������
		virtual void OnCreate()override;

		// �X�V
		virtual void OnUpdate() override;


	};


}
//end basecross

