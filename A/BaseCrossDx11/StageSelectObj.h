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
	private:
		//���W�i������Vec2����邯��SetPosition��Vec3����邵�j
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_InitScale;
		//���C���[
		int m_layer;
	public:
		SelectFlame(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;
	};

	//Abe20170525
	//--------------------------------------------------------------------------------------
	//	���S
	//--------------------------------------------------------------------------------------
	class SelectLogo : public GameObject
	{
	private:
		//���W�i������Vec2����邯��SetPosition��Vec3����邵�j
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_InitScale;
		//���C���[
		int m_layer;
	public:
		SelectLogo(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;
	};
	//Abe20170525

	//--------------------------------------------------------------------------------------
	//	�v���C���[�̒��S
	//--------------------------------------------------------------------------------------
	class SelectPlayer : public GameObject
	{
	private:
		//�������W
		Vector3 m_InitPos;
		//�����T�C�Y
		Vector3 m_InitScale;
		//���x
		float m_Speed;

		//�����ŗ���Ă鋗��
		float m_DifLength = 2;
		//����
		float m_dist = 2;

		//�v���C���[�̎���
		vector<shared_ptr<GameObject>> m_Player;
		//�����v�����[�ʒu
		vector<Vector3> m_InitPlayerPos;
		//�v���C���[�����̂����ԂɂȂ��Ă邩
		bool m_SandFlg = false;
		//������x�߂Â�����߂��Ă��Ԃ�
		bool m_SandFinishFlg = false;

		//�L�����Z�������Ƃ��ɂ������Ȃ��悤��
		bool m_CancelFlg = false;

		//Abe20170524
		//�X�e�[�W�̕�
		//�������A�E�����A�㐧���A�������̏�
		Vector4 MoveLimit = Vector4(-20, 66, 10, -36);
		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<GameObject> m_Debugtxt;
		//Abe20170524

		bool m_InitMoveFlg = true;
		bool m_Model_flg = true;
		bool m_Animeflg = true;
		bool m_WaitFlg = true;

		//�E�̈ړ��ő�l�ƍŏ��l�Ə����ʒu�̐ݒ�
		Vector3 m_RightSandMinit = Vector3(0, 0, 0);
		Vector3 m_RightLeaveMax = Vector3(0, 0, 0);
		Vector3 m_RightInitPos = Vector3(0, 0, 0);
		//���̈ړ��ő�l�ƍŏ��l�Ə����ʒu�̐ݒ�
		Vector3 m_leftSandMinit = Vector3(0, 0, 0);
		Vector3 m_leftLeaveMax = Vector3(0, 0, 0);
		Vector3 m_leftInitPos = Vector3(0, 0, 0);
		int StateNam = 0;
		int selecflg = true;

	public:
		SelectPlayer(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, float speed);

		void OnCreate() override;
		void OnUpdate() override;

		//�A�b�v�f�[�g����
		void SetPlayerUpdate(bool flg);
		//�͂��ރt���O�I��
		void SandFlgOn() { m_SandFlg = true; }
		//���̈ʒu�ɖ߂�t���O�I��
		void SandFinishFlgOn() { m_SandFinishFlg = true; }


		//���W�ړ��֐�
		void SetPos(Vector3);
		//���W�Ƃ��
		Vector3 GetPos();
		void InitPosMove();
		void SandMove();
		void LeaveMove();
		void SetLeaveMove(bool OnTrue) { m_InitMoveFlg = OnTrue; };
		//���f���̍ŏ��̌���
		void Model();
		void AnimationWait();
		bool UpdateAnyAnimation();
		bool UpdateAnyAnimation2();
		//�X�e�[�W�I�����ɃL�����Z���������ꂽ�Ƃ��ɃX�C�b�`�̓��e������������Z�b�^�[
		void SetChangeNum(int ChangNum) { StateNam = ChangNum; };

	};
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W��Փx�ƃX�e�[�W�I��
	//--------------------------------------------------------------------------------------
	class StageModeControl :public GameObject
	{
	private:
		//��Փx
		vector<int> m_Type;
		//�X�e�[�W���
		vector<shared_ptr<GameObject>> m_Easy;
		vector<shared_ptr<GameObject>> m_Normal;
		vector<shared_ptr<GameObject>> m_Hard;
		//�e�X�e�[�W��ނ̌��E�l
		int m_AddEasy = 0;
		int m_AddNormal = 0;
		int m_AddHard = 0;
		//�X�e�[�WBOX�̊�l
		Vector3 m_EasyPosCenter = Vector3(0, 0, 0);
		Vector3 m_EasyPosUP = Vector3(0, 0, 0);
		Vector3 m_EasyPosDown = Vector3(0, 0, 0);
		Vector3 m_EasyOtherPos = Vector3(0, 0, 0);
		Vector3 m_EasyTopPos = Vector3(0, 0, 0);
		//�m�[�}��
		Vector3 m_NormalPosCenter = Vector3(0, 0, 0);
		Vector3 m_NormalPosUP = Vector3(0, 0, 0);
		Vector3 m_NormalPosDown = Vector3(0, 0, 0);
		Vector3 m_NormalOtherPos = Vector3(0, 0, 0);
		Vector3 m_NormalTopPos = Vector3(0, 0, 0);
		//�n�[�h
		Vector3 m_HardPosCenter = Vector3(0, 0, 0);
		Vector3 m_HardPosUP = Vector3(0, 0, 0);
		Vector3 m_HardPosDown = Vector3(0, 0, 0);
		Vector3 m_HardOtherPos = Vector3(0, 0, 0);
		Vector3 m_HardTopPos = Vector3(0, 0, 0);
		//�X�e�[�W�I��p
		int m_EasyStageCenter = 0;
		int m_EasyStageUP = 0;
		int m_EasyStageDown = 0;
		int m_NormalStageCenter = 0;
		int m_NormalStageUP = 0;
		int m_NormalStageDown = 0;
		int m_HardStageCenter = 0;
		int m_HardStageUP = 0;
		int m_HardStageDown = 0;
		//�z��w��p
		int m_NormalUP = 0;
		int m_NormalDown = 0;
		//��Փx�̈ړ����\��
		bool m_ModeMove = false;
		//�
		Vector3 m_CenterScalse = Vector3(2, 2, 2);
		Vector3 m_NoCenterScalse = Vector3(1, 1, 1);
		//�͂��߂�������t���O
		bool InitOneflg = true;
		//�v�f���̌��o�@�Z���^�[
		int m_ElementCenter = 0;
		int m_ElementUp = 0;
		int m_ElementDown = 0;
		int m_ElementTop = 0;
		//�ړ��X�s�[�h
		float m_MoveSpeed = 0;
		//�z�񂩂���ʒu�̕ۑ�
		Vector3 m_Center = Vector3(0, 0, 0);
		Vector3 m_Up = Vector3(0, 0, 0);
		Vector3 m_Down = Vector3(0, 0, 0);
		Vector3 m_Top = Vector3(0, 0, 0);
		bool m_Flg = false;
		bool m_ElementNumTopFlg = false;
		//�Ȃ�̃X�e�[�W���Z���^�[�ɂ���̂��H �Z���^�[:true ����ȊO:false�@StageBox�N���X�Ŏg�p�@
		int m_CenterStageNum = 0;
		//��Փx�̈ړ��I���̃t���O
		bool m_ModeMoveEnd = true;
		bool m_GetModeflg = true;
		bool m_StageMoveEnd = true;
		//�X�e�B�b�N�����ɖ߂����i0.2��菬����-0.2���傫���j
		bool m_StickDown = false;
		//�����ꑱ���Ă��Ƃ���flg
		bool m_APush = false;
		bool m_KeepApudh = false;
		//A�����������ĂȂ����false�ɂȂ艟�������Ă��錟�؂����Ȃ�
		bool m_KeepPushing = true;
	public:
		StageModeControl(const shared_ptr<Stage>& StagePtr);
		~StageModeControl() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//�C�[�W�[�̃X�e�[�WBOX�̔z�u
		void EasySelect();
		void NormalSelect();
		void HardSelect();

		//��Փx�̈ړ����ł��邩��Ԃ��Q�b�^
		bool GetModeMove() { return m_ModeMove; };

		//�ʒu�̐ݒ�
		void  StandardEasyPos();
		void StandardNormalPos();
		void StandardHardPos();
		//�ő�ƍŏ��l�𒴂��Ă��Ȃ���������֐�
		int ExceedNum(int MIni, int Max, int Num);
		//�Z���^�[���瑼�̏ꏊ�̗v�f�����o
		void ElementNum(int Mini, int Max, int CenterNum);
		//�ړ�����
		void StageMove();
		void EasyMove();
		void NormalMove();
		void EasySideMove();
		void NormalSideMove();
		void HardMove();
		void HardSideMove();
		//�g��k������
		void EasyScale();
		void NormalScale();
		void HardScale();
		//�����z�u
		void Init();
		void InitSetCenter();
		void InitSetUp();
		void InitSetDown();
		void InitSetOther();
		//��Փx�̉�]���I������Ƃ��̃t���O
		bool ModeMoveEnd() { return m_ModeMoveEnd; };
		bool StageEndMove() { return m_StageMoveEnd; };

	};

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W��Փx�̃X�v���C�g �X�e�[�W���[�h
	//--------------------------------------------------------------------------------------
	class ModeSelect : public GameObject
	{
	private:
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scale = Vector3(0, 0, 0);
		bool m_Centerflg = false;
		bool m_Liftflg = false;
		bool m_Rightflg = false;
		int m_ModeNum = 0;
		int m_NowModeNum = 0;
		int m_MoveNum = 0;
		//3�̋K��ʒu
		//���S
		Vector3 m_CenterPos = Vector3(0, 0, 0);
		//�E
		Vector3 m_RightPos = Vector3(10, 1, 0);
		//��
		Vector3 m_LeftPos = Vector3(-10, 0, 0);
		//�X�s�[�h
		float m_Speed = 3.0f;
		//��]�t���O
		bool m_Rotflg = false;
		bool m_RotCenterflg = false;
		bool m_RotRightflg = false;
		bool m_RotLeftflg = false;
		//�ړ����I����Ă��邩�H
		bool m_EndMove = true;
		//�R���g���[���̘A�����̖͂h�~
		bool m_StickDown = false;
		bool m_StickLift = false;

	public:
		ModeSelect(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scale, const int& ModeNum, const bool& Centerflg, const int& MoveNum);
		~ModeSelect() {};
		virtual void OnCreate();
		virtual void OnUpdate();
		void SetModeSelectNum(int SetModeNum) { m_NowModeNum = SetModeNum; };
		//�e��Փx�̈ʒu�ړ����I��������̃Q�b�^�[ //�I����Ă���false�@�ړ�������true
		bool GetRotCenterflg() { return m_RotCenterflg; };
		bool GetRotRightflg() { return m_RotRightflg; };
		bool GetRotLeftflg() { return m_RotLeftflg; };
		//
		int GetMoveNum() { return m_MoveNum; };
		//�Z���^�[�t���O�@�Z���^�[�Ȃ�true ����ȊO�Ȃ�false
		bool GetCenter() { return m_Centerflg; };
		bool GetLiftf() { return m_Liftflg; };
		bool GetRight() { return m_Rightflg; };
		//��Փx�̈ړ�
		void ModeSelectMove();
		//�Z���^�[�Ɉړ�
		void CenterMove();
		//���Ɉړ�
		void LiftMove();
		//�E�Ɉړ�
		void RightMove();
		//�ړ����I��������H�Q�b�^�[ �I����Ă���true �I����ĂȂ�������false
		bool EndMove() { return m_EndMove; };

	};

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�̔�
	//--------------------------------------------------------------------------------------
	class StageBox : public GameObject
	{
	private:
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
	public:
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
	private:
		//�ʒu�͌Œ肷��̂ŏ����Ȃ�
		//�傫��(�傫���ς���A�j���[�V�����g���Ȃ�)
		Vector3 m_InitScale;

		//�w�i
		shared_ptr<GameObject> m_CheckBack;
		//���g
		shared_ptr<GameObject> m_CheckBoxIn;
		//�J�[�\��
		shared_ptr<GameObject> m_Cursor;
		//Go�X�v���C�g
		shared_ptr<GameObject> m_GoSprite;
		//Back�X�v���C�g
		shared_ptr<GameObject> m_BackSprite;

		//�I�����Ă�ԍ� 0��No�A1��Yes
		int m_selectnum = 0;

		//Abe20170523
		//�X�e�[�W
		int m_stageNum = 0;
		//Abe20170523

		//�\������Ă邩
		bool m_Dispflg = false;

		//Abe20170525
		//���ꂼ��̐�
		//�ˌ�
		shared_ptr<NumberSprite> m_TackleNumSpr;
		//�ʌ���
		shared_ptr<NumberSprite> m_ShotNumSpr;
		//�e���|�[�g
		shared_ptr<NumberSprite> m_TerepoNumSpr;
		//����
		shared_ptr<NumberSprite> m_BombNumSpr;
		//Abe20170525
		bool m_Closeflg = true;
		//�����ꑱ���Ă��Ƃ���flg
		bool m_APush = false;
		bool m_KeepApudh = false;
		//A�����������ĂȂ����false�ɂȂ艟�������Ă��錟�؂����Ȃ�
		bool m_KeepPushing = true;
	public:
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
		int GetStageNumber() { return m_stageNum; };
		//Abe20170523

		//Abe20170525
		//�G�l�~�[�̐������
		void SetEnemyNum(int tackle, int shot, int terepo, int bomb);
		//Abe20170525

		bool GetCloseflg() { return m_Closeflg; };
		void SetCloseflg(bool flg) { m_Closeflg = flg; };
	};
	//Abe20170421

	//Abe20170427

	//--------------------------------------------------------------------------------------
	//	�n��
	//--------------------------------------------------------------------------------------
	class SelectGroud : public GameObject
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
	public:
		SelectGroud(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale);

		void OnCreate() override;
	};
	//Abe20170427


	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����
	//--------------------------------------------------------------------------------------
	class SelectGroundSquare : public GameObject
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		wstring m_Text;
		float m_rot;
	public:
		SelectGroundSquare(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txt, float rot);

		void OnCreate() override;
	};

	//Abe20170526

	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����(SS��)
	//--------------------------------------------------------------------------------------
	class SelectGroundSquareSS : public SS5ssae
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		float m_rot;
	public:
		SelectGroundSquareSS(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, float rot);
		~SelectGroundSquareSS() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	//Abe20170529

	class ModeSeledctNameSprite :public GameObject {
	private:
		Vector3 m_Scale;
		int m_Type;

	public:
		ModeSeledctNameSprite(const shared_ptr<Stage>& StagePtr, const Vector3& Scale, const int& Type);
		~ModeSeledctNameSprite() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	//--------------------------------------------------------------------------------------
	//	�n�ʂɓ\����
	//--------------------------------------------------------------------------------------
	class SelectModeSquare : public GameObject
	{
	private:
		int m_ModeNum = 0;
	public:
		SelectModeSquare(const shared_ptr<Stage>& StagePtr, const int& ModeNum);
		~SelectModeSquare() {};

		void OnCreate() override;
		void OnUpdate() override;
	};

	class SERECT_Background :public GameObject
	{
	private:
		Vector3 m_Scale = Vector3(0, 0, 0);
		Vector3 m_Pos = Vector3(0, 0, 0);
	public:
		SERECT_Background(const shared_ptr<Stage>& StagePtr, const Vector3& m_Scale, const Vector3& m_Pos);
		~SERECT_Background() {};
		void OnCreate() override;
	};
}