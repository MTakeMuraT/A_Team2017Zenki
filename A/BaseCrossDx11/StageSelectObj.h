#pragma once
#include "stdafx.h"

namespace basecross 
{
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�̃I�u�W�F�N�g
	//�@�v���C���[�����삷�镔������̂ł�����Ƒ���
	//--------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	//	�t���[���X�v���C�g
	//--------------------------------------------------------------------------------------
	class SelectFlame : public GameObject
	{
	private :
		//���W�i������Vec2����邯��SetPosition��Vec3����邵�j
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_InitScale;
		//���C���[
		int m_layer;
	public:
		SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale,int layer);

		void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�v���C���[�̒��S
	//--------------------------------------------------------------------------------------
	class SelectPlayer : public GameObject
	{
	private :
		//�������W
		Vector3 m_InitPos;
		//�����T�C�Y
		Vector3 m_InitScale;
		//���x
		float m_Speed;

		//�����ŗ���Ă鋗��
		float m_DifLength = 2;

		//��]���x
		float m_RotSpeedPerSec = 180;

		//�v���C���[�̎���
		vector<shared_ptr<GameObject>> m_Player;

		//�v���C���[�����̂����ԂɂȂ��Ă邩
		bool m_SandFlg = false;
		//������x�߂Â�����߂��Ă��Ԃ�
		bool m_SandFinishFlg = false;
		//�֐��Q
		void SandMove();
		//��]
		void Rot();

		//�L�����Z�������Ƃ��ɂ������Ȃ��悤��
		bool m_CancelFlg = false;
	public :
		SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, float speed);

		void OnCreate() override;
		void OnUpdate() override;

		//�A�b�v�f�[�g����
		void SetPlayerUpdate(bool flg);

		//�͂��ރt���O�I��
		void SandFlgOn() { m_SandFlg = true; }
		//���̈ʒu�ɖ߂�t���O�I��
		void SandFinishFlgOn() { m_SandFinishFlg = true; }
	};

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�̔�
	//--------------------------------------------------------------------------------------
	class StageBox : public GameObject
	{
	private :
		//�������W
		Vector3 m_InitPos;
		//�����T�C�Y
		Vector3 m_InitScale;
		//�X�e�[�W�ԍ�
		int m_stagenumber;
		//�v���C���[�������Ă鐔
		int m_PlayerHitNum = 0;
		//���肷��t���O
		bool m_PlayerHitFlg = false;
	public :
		StageBox(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, int num);

		void OnCreate()override;
		void OnUpdate()override;

		//�A�^������(���u)
		virtual void OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) override;

		//�X�e�[�W�ɍs�����m�F���鏈��
		void CheckGo();
	};

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�s�����m�F����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class GoStageCheck : public GameObject
	{
	private :
		//�ʒu�͌Œ肷��̂ŏ����Ȃ�
		//�傫��(�傫���ς���A�j���[�V�����g���Ȃ�)
		Vector3 m_InitScale;

		//�w�i
		shared_ptr<GameObject> m_CheckBack;
		//Yes����
		shared_ptr<GameObject> m_CheckYes;
		//No����
		shared_ptr<GameObject> m_CheckNo;
		//�m�F����
		shared_ptr<GameObject> m_CheckLogo;
		//�J�[�\��
		shared_ptr<GameObject> m_Cursor;

		//�I�����Ă�ԍ� 0��No�A1��Yes
		int m_selectnum = 0;

		//Abe20170523
		//�X�e�[�W
		int m_stageNum = 0;
		//Abe20170523

		//�\������Ă邩
		bool m_Dispflg = false;
	public :
		GoStageCheck(const shared_ptr<Stage>& StagePtr, Vector2 scale);

		void OnCreate()override;
		void OnUpdate()override;

		//�X�v���C�g�Ƃ��o��
		void OpenCheck();

		//�X�v���C�g�Ƃ�����
		void CloseCheck();

		//Abe20170523
		//�X�e�[�W�ԍ��ݒ�
		void SetStageNumber(int num) { m_stageNum = num; };
		//Abe20170523
	};
	//Abe20170421

	//Abe20170427

	//--------------------------------------------------------------------------------------
	//	�n��
	//--------------------------------------------------------------------------------------
	class SelectGroud : public GameObject
	{
	private :
		Vector3 m_Pos;
		Vector3 m_Scale;
	public :
		SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;
		void OnUpdate() override;

	};
	//Abe20170427

}