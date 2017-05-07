//************************************
//*		�쐬���F2017/04/30
//*		�쐬�ҁFAbe
//*		���e�F
//*		�A�^������(�ʏ�~�`�Ƃ͂��ގ�)
//************************************


#pragma once
#include "stdafx.h"

namespace basecross 
{
	//************************************
	//	�~�`�A�^������
	//	�����Ŕ���A���W�̃}�C�i�X���]���ĉ��Z��������2(�v���C���[�̔��a[1]*2)�ȉ��̂��̂̂ݔ���
	//************************************
	class CollisionManager : public GameObject
	{
	private :
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;		//���H�������Ƃ��ł₢�Ă�́H
		shared_ptr<GameObject> m_Player2;		//�E�H�͂�����킩�񂾂�

		//���肷�邩�ǂ���
		bool m_ActiveFlg = true;

		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<DebugTxt> m_Debugtxt;

		//�v���C���[���Ԃ�������̏����A�����͋��񂾃I�u�W�F�N�g�Ɠ��������v���C���[�̔ԍ�
		void CollisionAfter(shared_ptr<GameObject>,int);

		//�R���W�����O���[�v�ɓ����Ă�I�u�W�F�N�g���m�̂�����A�����̓I�u�W�F�N�g�Ɗp�x
		void CollisionAfterObjs(shared_ptr<GameObject>,int, shared_ptr<GameObject>, int);

		//�v���C���[�ƃI�u�W�F�̔���
		void CollisionPlayer();

		//�A�^������O���[�v�ɓ����Ă�S���̔���
		void AllCollision();

		//�Ȃ񂩂킩�肸�炢���vector�R���e�i�ɓ˂�����
		vector<shared_ptr<GameObject>> m_ColObjs;

		//�����锻��
		bool HitTest(Vector3 pos1, float half1, Vector3 pos2, float half2);
	public :
		CollisionManager(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		void OnUpdate() override;

		//�ꉞ���肵�Ȃ��悤�ɂ���֐�������Ă���
		void SetActive(bool flg) { m_ActiveFlg = flg; }
	};

	//************************************
	//	�͂��ގ��̔���
	//	�����u���܂�锻��l�@.txt�v���Q��
	//	�������x���グ�邽�߁A�㉺(Y)���Ɋւ��Ă̔���͂��Ȃ�
	//************************************

	class CollisionSand : public GameObject 
	{
	private :
		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;

		//���肷�邩�ǂ���
		bool m_ActiveFlg = true;

		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<DebugTxt> m_Debugtxt;

		//���񂾌�̏��������͋��񂾃I�u�W�F�N�g
		void SandAfter(shared_ptr<GameObject>);
	public : 
		CollisionSand(const shared_ptr<Stage>& StagePtr);
		void OnCreate() override;
		void OnUpdate() override;

		//�N���ݒ�
		void SetActive(bool flg) { m_ActiveFlg = flg; }
	};
}