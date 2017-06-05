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
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;


		//�r���[�̍쐬
		void CreateViewLight();
		// �w�i
		void CreateBackGround();
		void CreateGround();
		void CreatePlate();
		void CreatePlayerLin();
		void CreateUILin();
		void CreateChildMissile();
		//�e�X�g���Ɏg�p
		void CreateTestLin();

		//�^�C�}�[�쐬
		void CreateTimer();
		//���C�t�쐬
		void CreateLife();

		//�J�����X�V
		void UpdateCamera();

		//�A�^������쐬
		void CreateCollision();

		//Abe20170515
		//�X�e�[�W�̕�
		Vector2 m_StageSize;
		//Abe20170515

		//Abe20170519MukkuMarge
		void CreateEnemyCounts();
		//Abe20170519MukkuMarge


		//Abe20170530
		bool m_CameraMoveFlg = true;
		//Abe20170530
		//���o�Ɉڂ鎞��BGM�X�g�b�v
		bool StopBGM = true;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage();

		//������
		virtual void OnCreate()override;

		// �X�V
		virtual void OnUpdate() override;

		//Abe20170530
		//�Q�[���I�[�o�[
		void GameOver();

		//�Q�[���I�[�o�[�J��������
		bool GameOverCamera();

		//Abe20170531
		//���U���g
		void Result();

		//���U���g�J�������� �����̓L�����̒��S
		bool ResultCamera(Vector3 pos);
		//Abe20170531

		//Abe20170530
		//�J�����ړ���~
		void CameraStop() { m_CameraMoveFlg = false; }
		//Abe20170530


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

