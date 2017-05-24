/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class StageSelectScene : public Stage {
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;


		//�r���[�̍쐬
		void CreateViewLight();
		void CreatTestLin();

		//Abe20170421
		//�t���[���쐬
		void CreateFlame();
		//�v���C���[�쐬
		void CreatePlayer();
		//�X�e�[�W�{�b�N�X�쐬
		void CreateStageBox();
		//�X�e�[�W�s�����m�F����X�v���C�g
		void CreateGoCheck();
		//Abe20170421

		//Abe20170524
		//�X�e�[�W�̏��쐬
		void CreateStageUnder();
		//Abe20170524

		//Abe20170427
		//�J�����ړ��t���O
		bool m_moveCameraFlg = false;
		//�J�����ڕW���W
		Vector3 m_CameraMoveTarget;
		//�J�������W
		Vector3 m_CameraPos;
		//�����_
		Vector3 m_CameraAt;
		//�J�����ړ��֐�
		void CameraMove();
		//Abe20170427

		//Abe20170524
		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<GameObject> m_Debugtxt;
		//�J�����ړ����̃v���C���[�ړ���
		Vector3 m_CameraMovePlayerTargetPos;
		//���̃J�����̈ʒu
		int m_CameraNum = 5;
		//Abe20170524

	public:
		//�\�z�Ɣj��
		StageSelectScene() :Stage() {}
		virtual ~StageSelectScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//Abe20170427
		//�J�����ړ�0�F��Ɂ@1�F�E�Ɂ@2�F���Ɂ@3�F����
		void MoveCamera(int num);
		//Abe20170427

	};


}
//end basecross