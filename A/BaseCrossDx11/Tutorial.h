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

		//��]���Ԍv���I�u�W�F�N�g�쐬
		void CreateRotCount();

		//�X�v���C�g���쐬
		void CreateSpriteS();

		//�G�l�~�[�쐬
		void CreateEnemy();

		//�J���������t���O
		bool m_CameraMoveFlg = true;

		//�G�l�~�[�̐�������t���O
		bool m_EnemyFlg = false;
	public:
		//�\�z�Ɣj��
		TutorialScene() :Stage() {}
		virtual ~TutorialScene();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�J�����X�V
		void UpdateCamera();

		//�J�����ړ���~
		void CameraStop() { m_CameraMoveFlg = false; }

		//���U���g�J�������� �����̓L�����̒��S
		bool ResultCamera(Vector3 pos);

		void EnemyCountOn() { m_EnemyFlg = true; }

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

		//�ʒu�X�V�؂�t���O
		bool m_DontMoveFlg2 = false;
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
		//������Ԃ�
		float GetDistance() { return m_PlayerSDistance; }
		//�ʒu�X�V�I�t
		void DontMove() { m_DontMoveFlg2 = true; }

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
		//��������
		bool m_ActiveFlg = false;
	public :
		MoveTarget(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//**************************************************************************************
	//	��]�̂ݎg�����Ԃ̎�
	//	������x��]���������
	//**************************************************************************************
	class TutorialRotFixed :public GameObject
	{
	private :
		//�v�Z�p����
		float m_time;
		//��������
		float m_LimitTime;
		//�v���t���O
		bool m_StartFlg;
	public :
		TutorialRotFixed(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�������Ԍv���J�n
		void StartCount();
	};

	//**************************************************************************************
	//	�I�G�l�~�[
	//	���ʂ���
	//**************************************************************************************
	class TutorialEnemy : public GameObject
	{
	private :
		//������o���t���O
		bool m_UpFlg = false;
		//���܂�锻�肷�邩
		bool m_SandJudgeFlg = false;
	public:
		TutorialEnemy(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//������o��
		void Up();

		//���W�ړ�
		void SetPos(Vector3 pos) { GetComponent<Transform>()->SetPosition(pos); }
	};

	//**************************************************************************************
	//	�X�v���C�g����
	//	��ԕς��ďo��
	//�@��̐؂�ւ��łQ�X�e�[�g�g���̂�NextState()�Ő؂�ւ����Ƃ��͂Q�i�߂�
	//�@�������N���G�C�g�ŏ�����
	//**************************************************************************************
	class TutorialSpriteS : public GameObject
	{
	private :
		//���
		int m_state;
		//��Ԑ؂�ւ���
		bool m_ChangestateFlg;
		//���Ԍv���p
		float m_time;
		//�؂�ւ��Ԋu
		float m_IntervalTime;
	public :
		TutorialSpriteS(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void NextSatte();
	};
}