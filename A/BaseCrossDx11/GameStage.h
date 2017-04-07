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
		void CreateGround();
		void CreatePlate();
		void CreatePlayerLin();

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}

		//������
		virtual void OnCreate()override;

		// �X�V
		virtual void OnUpdate() override;


	};

	//�n��
	class Ground_GameStage : public GameObject
	{
	private:
		//SP
		Vector3 m_Scale;
		Vector3 m_Positon;
		wstring m_TX_Name;

	public:
		//�R���X�g���N�^
		Ground_GameStage(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Positon ,
			const wstring& TX_Name);

		//�f�X�g���N�^
		virtual ~Ground_GameStage() {};

		virtual void OnCreate() override;
	};


}
//end basecross

