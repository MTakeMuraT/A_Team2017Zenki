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

		//�n�ʍ쐬
		void CreateGround();

		//�v���C���[�쐬
		void CreatePlayer();

		//�ړ��^�[�Q�b�g�쐬
		void CreateMoveTarget();
	public:
		//�\�z�Ɣj��
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�J�����X�V
		void UpdateCamera();
	};

	//--------------------------------------------------------------------------------------
	//	�������牺�͐�p�̃I�u�W�F�N�g�������`�H
	//--------------------------------------------------------------------------------------

	//**************************************************************************************
	//**************************************************************************************


	//**************************************************************************************
	//	�`���[�g���A����p�̃v���C���[�A���쐧���@�\��
	//	�w�b�_�[�Œl�ݒ肵�Ă��o�O���̂ŃN���G�C�g�ō���
	//**************************************************************************************
	class TutorialPlayerS : public GameObject
	{
	private :
		//�v���C���[��̖�
		shared_ptr<GameObject> m_Player1;
		//�v���C���[��̖�
		shared_ptr<GameObject> m_Player2;
		//��̂̋���
		float m_PlayerSDistance;
		//��̂̋��������l
		float m_PlayerSDistanceInit;
		//��̂̋����ő�
		float m_PlayerSDistanceLimit;
		//����鑬�x
		float m_DistanceSpeed;
		//���������x
		float m_KuttukuSpeed;

		//��]
		float m_rot;
		//��]���x
		float m_rotSpeed;

		//����
		Vector3 m_Kansei;

		//����
		shared_ptr<GameObject> m_BlackSprite;
		//�����̓����x
		float m_BlackAlpha;
		//�����ɂȂ邩
		bool m_BlackAlphaFlg = false;

		//�A�j���[�V�����̖��O
		//�X�V�O
		string m_NowAnimName;
		//�X�V��
		string m_ChangeAnimName;

		//�S�������Ȃ�����t���O
		bool m_DontMoveFlg = false;

		//�������Ă�t���O
		bool m_KuttukuFlg = false;
		//�������Ė߂�t���O
		bool m_KuttukuAfterFlg = false;
		//-----------------------
		//�p�����[�^��
		//-----------------------
		float m_Speed;


		//-----------------------
		//�֐�
		//-----------------------
		//�v���C���[�����̍��W���X�V
		void PosRotUpdate();
		//�X�e�[�W�̊O�ɍs�����Ƃ�����߂�����
		void CheckStageEnd();
		//�Ó]����
		void BlackUpdate();
		//�A�j���[�V�����X�V
		void UpdateAnimation();
		//-----------------------
		//����n
		//-----------------------
		bool m_moveFlg;
		bool m_rotFlg;
		bool m_AButtonFlg;
	public :
		TutorialPlayerS(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//��̂̍��W��Ԃ�
		vector<Vector3> GetPlayerSPos_RETURNvectorVec3();

		//-----------------------
		//����n
		//-----------------------
		void SetMoveCont(bool flg) { m_moveFlg = flg; }
		void SetRotCont(bool flg) { m_rotFlg = flg; }
		void SetAbuttonCont(bool flg) { m_AButtonFlg = flg; }
	};

	//**************************************************************************************
	//	�ړ��^�[�Q�b�g
	//	������
	//**************************************************************************************
	class MoveTarget : public GameObject
	{
	private :
		//�����x
		float m_Alpha;
		//���
		bool m_AlphaFlg = false;
	public :
		MoveTarget(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}