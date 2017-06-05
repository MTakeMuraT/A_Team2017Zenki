/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//�ނ�����
	//--------------------------------------------------------------------------------------
	///	�^�C�g���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	TextureKey	�e�N�X�`���L�[
		@param[in]	Trace	�����������邩�ǂ���
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		TitleSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TitleSprite();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override {}
	};


	//--------------------------------------------------------------------------------------
	///	�Ղꂷ���Ɂ[���[�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class PressSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;

		bool lighton = true;


	public:
		float m_alpha = 0.05;
		float Max = 2.0f;

		//--------------------------------------------------------------------------------------
		PressSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		virtual ~PressSprite();
		//--------------------------------------------------------------------------------------

		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------

		virtual void OnUpdate()override;
		virtual void OnLastUpdate() override;

	};

	//Abe20170523
	//--------------------------------------------------------------------------------------
	//	�V�[���J�ڂ̃X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	class SceneChangeSS : public SS5ssae
	{
	private :
		//������
		bool m_ActiveFlg = false;

		//��������
		float m_LimitTime = 2.0f;
		float m_time = 0;
	public :
		//�\�z�Ɣj��
		SceneChangeSS(const shared_ptr<Stage>& StagePtr);
		//������
		void OnCreate() override;
		void OnUpdate() override;

		void OnAnim();

		void SetLayer(int num) { SetDrawLayer(num); };
	};
	//Abe20170523
	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	�V�[���J�ڂ̃X�v���C�g�X�^�W�I(�A�E�g)
	//--------------------------------------------------------------------------------------
	class SceneChangeSSOut : public SS5ssae
	{
	private:
		//������
		bool m_ActiveFlg = false;
		//��������
		float m_LimitTime = 1.5f;
		float m_time = 0;
	public:
		//�\�z�Ɣj��
		SceneChangeSSOut(const shared_ptr<Stage>& StagePtr);
		//������
		void OnCreate() override;
		void OnUpdate() override;

		void OnAnim();

		void SetLayer(int num) { SetDrawLayer(num); };

	};
	//Abe20170526


	//��[��������
	//--------------------------------------------------------------------------------------
	//	class StageSelectSprite : public GameObject;
	//	�p�r: �V�[���\���n��
	//--------------------------------------------------------------------------------------
	class StageSelectSprite : public GameObject {
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		int m_Num;

	public:
		StageSelectSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos,
			const int& Number);
		virtual ~StageSelectSprite();
		virtual void OnCreate() override;

	};
	class DimSprite : public GameObject {
		bool m_Trace;
		Vector2 m_StartScale;
		Vector2 m_StartPos;
		float m_TotalTime;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionColor> m_BackupVertices;
	public:
		float dim = 0;
		bool dimon;
		DimSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
			const Vector2& StartScale, const Vector2& StartPos);
		virtual ~DimSprite();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	class TestLin : public GameObject;
	//	�p�r: �V�[���\���e�X�g�n��
	//--------------------------------------------------------------------------------------
	class TestLin : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
		int m_Type;
	public:
		//�\�z�Ɣj��
		TestLin(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position,
			const int& Type
		);
		virtual ~TestLin();
		//������
		virtual void OnCreate() override;
		//����
	};

	//--------------------------------------------------------------------------------------
	//	class FixdBox : public GameObject;
	//	�p�r: �G�l�~�[�e�X�g�p
	//--------------------------------------------------------------------------------------
	class FixdBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
		wstring m_TX_Name;
		bool Inserted = false;
		float Speed_F = 0.0f;
		Vector3 Vec_Vec3 = Vector3(0, 0, 0);
	public:
		//�\�z�Ɣj��
		FixdBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position,
			const wstring& TXName);
		virtual ~FixdBox() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnLastUpdate()override;
		void InputStick();
	};


	//--------------------------------------------------------------------------------------
	//	class Dedug : public GameObject;
	//	�p�r: �X�e�[�W�V�[���@
	//--------------------------------------------------------------------------------------
	class Dedug : public GameObject {
		

	public:
		//�\�z�Ɣj��
		Dedug(const shared_ptr<Stage>& StagePtr
		);
		virtual ~Dedug();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//����
	};

	//--------------------------------------------------------------------------------------
	//	class Enemy01 : public GameObject;
	//	�p�r: �G�l�~�[1�@
	//--------------------------------------------------------------------------------------
	//Abe20170412
	class Enemy01 : public GameObject 
	{
	private :
		//�C��t���O
		bool m_StanFlg = false;
		//���܂�Ă�t���O
		bool m_SandFlg = false;
		//�C�₵�Ă鎞��
		float m_StanTime = 0;
		//���W
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
		//��΂���
		float m_VeloPower = 100;
		//��
		Vector3 m_Vel;
	public :
		Enemy01(const shared_ptr<Stage>& StagePtr,Vector3 Pos,Vector3 Scale);
		Enemy01(const shared_ptr<Stage>& StagePtr, const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;

		//�_���[�W��Ԏ�
		void DamageState();
		//�v���C���[�����ꂽ�Ƃ�
		void Release();
		//���Ă�ꂽ���̂ق�
		void Release(Vector3 vel);
		//�_���[�W�󂯂��Ƃ�
		void Damage(float Time);
		//�v���C���[���玞�Ԏ����Ă���� Player_RGetATime�͉�
		//void Damage(){m_StanFlg = true; GetStage()->GetSharedGameObject<Player>(L"Player_R")->GetATime();}

		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;

		bool GetStanFlg() { return m_StanFlg; }


		//�e�X�g�p�̋��܂ꂽ��̏���
		void SandAfter() { SetDrawActive(false); };
	};
	//Abe20170412


	//Abe20170418
	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	�p�r: �����̃X�v���C�g
	//�@���������猅�����邲�Ƃɍ��ɂ���Ă�
	//--------------------------------------------------------------------------------------
	class NumberSprite : public GameObject
	{
	private:
		//�Ȃ񂩂���񃁃b�V���̃��X�g
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//����
		int m_digit = 0;
		//��������Ă鐔��
		int m_Constdigit = 0;
		//�\�����C���[
		int m_layer = 0;
		//�傫��
		Vector2 m_scale;
		//�ʒu
		Vector2 m_pos;
		//��������vector�z��
		vector<shared_ptr<GameObject>> m_Numbers;

		//�����p
		//�����ƕ����̊Ԋu
		float IntervalNums = 1.8f;
	public:
		NumberSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;

		/*�ȑO���삵�Ă����̂����ǎg��Ȃ����Ȃ̂ŏ����Ƃ��܂�
		//�ʒu����
		void SetPositionVec2(Vector2 pos);
		//�傫������
		void SetScaleVec2(Vector2 scale);
		*/

		//�����ݒ�
		void SetNum(int num);

		void SetNumDraw(bool flg);


		//Abe20170531
		//�ړ�
		void MoveNums(Vector3);
		//���C���[�ݒ�
		void SetLayer(int);
		//Abe20170531

	};

	//--------------------------------------------------------------------------------------
	//	class Timer : public GameObject;
	//	�p�r:�^�C�}�[
	//�@�ʒu�ݒ�A�傫���̓X�v���C�g�Ȃ̂�Vec2�Ŏg��
	//--------------------------------------------------------------------------------------

	class Timer : public GameObject
	{
	private:
		//�����ʒu
		Vector2 m_InitPos;
		//�傫��
		Vector2 m_InitScale;
		//���C���[
		int m_LayerNum;
		//��������
		int m_InitTime;
		//���ݎ���
		float m_Time;
		//���Ԏ~�߂�t���O
		bool m_TimeStopFlg = false;
		//�I�������
		bool m_FinishFlg = false;
		//����
		shared_ptr<NumberSprite> m_Numbers;
	public:
		//�������ԁA���W�A�傫���A���C���[
		Timer(const shared_ptr<Stage>& StagePtr, int Time, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

		void SetTimer(bool flg);

		bool GetTimerFlg() { return m_FinishFlg; }

		//Abe20170531
		//���W�ړ�
		void MovePos(Vector3);
		//���C���[�ݒ�
		void SetLayer(int);
		//Abe20170531

		//Abe20170601
		//���Ԏ擾
		int GetTime() { return m_Time; }
		//Abe20170601


	};

	//--------------------------------------------------------------------------------------
	//	class Player_Life : public GameObject;
	//	�p�r:�v���C���[��HP
	//--------------------------------------------------------------------------------------
	class Player_Life :public GameObject
	{
	private:
	
		bool m_DieFlg = true;
		bool dmg = false;

		//���ݒn
		int m_Life = 10;
		//�ő�l
		int m_LifeMax = 10;
		//���W
		Vector2 m_InitPos;
		//�傫��
		Vector2 m_InitScale;
		//���C���[
		int m_layer;
		//���C�t�X�v���C�g
		vector<shared_ptr<GameObject>> m_LifeSprite;
		//�t���[���E�E�E�͑��₷���ĂȂ�����ǉ����邩
		//�S��
		vector<shared_ptr<GameObject>> m_AllSpriteS;
		//�����p
		//�Ԋu
		float m_IntervalLife = 0.45f;
	public:
		Player_Life(const shared_ptr<Stage>& StagePtr, int LifeNum, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;
		void OnUpdate() override;

		//���͂����l�����C�t�������
		void LifeDown(int num);

		int GetLife() { return m_Life; }
		bool GetDieFlg() {
			return m_DieFlg;
		}
		
		//���C�t�X�v���C�g�ړ�
		void MoveSprtieS(Vector3);
		//���C���[�ύX
		void SetLayer(int num);

	};
	//Abe20170418
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	�X�v���C�g�̑傫���A�ʒu���m�F����I�u�W�F�N�g
	//************************************
	//	������@
	//	�\���L�[�F�X�P�[�� [��] +Y [��] -Y [��] +X [��] -X
	//	�X�e�B�b�N�F���W�ړ�
	//�@A,B�F����
	//�@X,Y�F����
	//************************************
	//--------------------------------------------------------------------------------------
	class SpritePosScaleChecker : public GameObject
	{
	private:
		//���W
		Vector3 m_pos;
		//�傫��
		Vector3 m_scale;
		//���C���[
		int m_layer;
		//�e�N�X�`���̖��O
		wstring m_texturename;
	public:
		SpritePosScaleChecker(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer, wstring txtname);

		void OnCreate()override;
		void OnUpdate()override;
	};
	//Abe20170421

	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	�f�o�b�O�����\������I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class DebugTxt : public GameObject 
	{
	private:
		//�傫��(�g)
		Vector2 m_Scale;
		//���W
		Vector2 m_Pos;
		//�傫��(����)
		int m_ScaleTxt;
	public :
		DebugTxt(const shared_ptr<Stage>& StagePtr);

		void OnCreate() override;
		//�����ݒ�
		void SetText(wstring txt);
		//�傫��(�g)�ݒ�
		void SetScale(Vector2);
		//���W�ݒ�
		void SetPos(Vector2);
		//�傫��(����)�ݒ�
		void SetScaleTxt(int);
		//���C���[�ݒ�
		void SetLayer(int);
		//�F�ݒ�
		void SetColor(Vector3);
	};

	//Abe20170427


	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChild : public GameObject;
	//	�p�r: �~�T�C�������q�@
	//--------------------------------------------------------------------------------------
	class ShotEnemyChild : public GameObject
	{
	private:
		Vector3 m_Scale = Vector3(0, 0, 0);
		Vector3 m_Position;
		Vector3 m_Rotation = Vector3(0, 0, 0);
		Vector3 m_ReferencePoint_Vec3 = Vector3(0, 0, 0);//�~�T�C�����˂̊�_�@
		Vector3 m_ReferencePoint2_Vec3 = Vector3(0, 0, 0);//�~�T�C�����˂̊�_�Q
		Vector3 m_CenterPoint_Vec3 = Vector3(0, 0, 0);//�Z���^�[�i�������擾���Ɏg�p
		Vector3 m_Distance = Vector3(0, 0, 0);//��]�Ŏg�p
		Vector3 m_NewReferencePoint_Vec3 = Vector3(0, 0, 0);
		Vector3 m_NewReferencePoint2_Vec3 = Vector3(0, 0, 0);
		Vector3 m_NewCenterPoint_Vec3 = Vector3(0, 0, 0);
		Quaternion m_Angle;
		Vector3 m_Direction_Vec3 = Vector3(0, 0, 0);
		float m_T_Angle = 0.0f;
		//���ˊԊu
		float m_ShotInterval = 0.0f;
		//bool m_ShotFlg = false;

		//�f�o�b�N�~�T�C�����ˏꏊ�̈ʒu�m�F�p�@�i�ʃN���X�ɒl�𑗂�p
		Vector3 m_Debug = Vector3(0, 0, 0);
		Vector3 m_getPos = Vector3(0, 0, 0);
		Vector3 m_getPos2 = Vector3(0, 0, 0);
		Vector3 m_getCenter = Vector3(0, 0, 0);
		float m_Time = 0.0f;
		int m_cout = 0;

		//���܂�Ă���
		bool m_ShotEnemyChildSandFlg = false;
		//�����ύX ����tore�@������false
		bool m_DefaultRot_F = true;

		//Abe20170517
		//�����n�߂邩�ǂ���
		bool m_ShotFlg = false;
		//�������Ă�Œ�
		void Tobu();
		//�����x
		Vector3 m_Velocity;
		//Abe20170517
	public:
		ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const float& ShotInterval);
		ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const wstring& line);
		virtual ~ShotEnemyChild() {};
		void OnCreate() override;
		void OnUpdate() override;
		void OnLastUpdate()override;
		void ShotEnemyChildRot();
		void PintNewPos();
		void DoingSandRotation();
		void Shot();
		Vector3 Direction();
		void SetShotFlg(bool m_Shot) { m_ShotFlg = m_Shot; };
		bool GetShotFlg() { return m_ShotFlg; };
		float GetAngle() { return m_T_Angle; }
		//�f�o�b�N�Q�b�^�[
		Vector3 GetPos(bool flg) {
			if (flg) {
				return m_getPos;
			}
			else {
				return m_getPos2;
			}
		}
		Vector3 InitialPos(bool flg) {
			if (flg) {
				return m_ReferencePoint_Vec3;
			}
			else {
				return m_ReferencePoint2_Vec3;
			}
		}
		Vector3 GetDirection() {
			return m_getCenter;
		}
		bool GetShotEnemyChildSandFlg() {
			return m_ShotEnemyChildSandFlg;
		}
		void SetShotEnemyChildSandFlg(bool flg) {
			m_ShotEnemyChildSandFlg = flg;
		}


		//Abe20170517
		//�����x�ݒ�
		void SetVelocity(Vector3 vel)
		{
			m_Velocity = vel;
		}
		//Abe20170517

	};
	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChildMissile : public GameObject;
	//	�p�r: �~�T�C�������q�@�i�~�T�C���j
	//--------------------------------------------------------------------------------------
	class ShotEnemyChildMissile : public GameObject {
	private:
		Vector3 m_Position;
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Direction;
		float m_Speed = 100;
		float m_AttackDamage;
		float m_DeleteTime;
		bool m_ShotActive;
	public:
		ShotEnemyChildMissile(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const Vector3& Rotation, const Vector3& Direction);
		virtual ~ShotEnemyChildMissile() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//�ړ�
		void ChildMissileMove();
		//�����鏈��
		void ObjDelete();
		//�U���͂̃A�N�Z�T
		float GetChildMissileAttackDamage() {
			return  m_AttackDamage;
		}
		//���������Ȃ���
		void SetShotActive(bool ShotTrue) {
			m_ShotActive = ShotTrue;
		}
		bool GetShotActive() {
			return m_ShotActive;
		}
	};

	//Abe20170519MukkuMargeNumberSprite�Ɠ��������������̂ł������ő�p
	/*
	//--------------------------------------------------------------------------------------
	//	class EnemyCountSprite : public GameObject;
	//	�p�r: �c�G���̃X�v���C�g�\��
	//--------------------------------------------------------------------------------------
	class EnemyCountSprite : public GameObject {
	private:
		//�Ȃ񂩂���񃁃b�V���̃��X�g
		vector<shared_ptr<MeshResource>> m_Mesh;
		int m_num = 0;
		//����
		int m_digit = 0;
		//��������Ă鐔��
		int m_Constdigit = 0;
		//�\�����C���[
		int m_layer = 0;
		//�傫��
		Vector2 m_scale;
		//�ʒu
		Vector2 m_pos;
		//��������vector�z��
		vector<shared_ptr<GameObject>> m_Numbers;

		//�����p
		//�����ƕ����̊Ԋu
		float IntervalNums = 1.8f;
	public:
		EnemyCountSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;

		/*�ȑO���삵�Ă����̂����ǎg��Ȃ����Ȃ̂ŏ����Ƃ��܂�
		//�ʒu����
		void SetPositionVec2(Vector2 pos);
		//�傫������
		void SetScaleVec2(Vector2 scale);
		*/
	/*
		//�����ݒ�
		void SetNum(int num);

		void SetNumDraw(bool flg);

	};
	*/
	//Abe20170519MukkuMargeNumberSprite�Ɠ��������������̂ł������ő�p

	////////////////////////

	class EnemyCountA : public GameObject
	{
	private:
		//�����ʒu
		Vector2 m_InitPos;
		//�傫��
		Vector2 m_InitScale;
		//���C���[
		int m_LayerNum;
		//����
		shared_ptr<NumberSprite> m_Numbers;
		//�ő吔
		shared_ptr<NumberSprite> m_MaxNumber;

		int m_EnemyCunt = 0;
		int m_EnemyMaxCount = 0;
	public:
		//���W�A�傫���A���C���[
		EnemyCountA(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

	};

	//Abe20170519MukkuMarge��ł܂Ƃ߂���̂�EnemyCountA�̂ق��ɂ܂Ƃ�
	/*
	class EnemyCountB : public GameObject
	{
	private:
		//�����ʒu
		Vector2 m_InitPos;
		//�傫��
		Vector2 m_InitScale;
		//���C���[
		int m_LayerNum;
		//���Ԏ~�߂�t���O
		bool m_TimeStopFlg = false;
		//�I�������
		bool m_FinishFlg = false;
		//����
		shared_ptr<NumberSprite> m_Numbers;

		int m_EnemyCunt = 0;

		int m_MaxCount = 0;
	public:
		//�������ԁA���W�A�傫���A���C���[
		EnemyCountB(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer);

		void OnCreate()override;
		void OnUpdate()override;

		//void SetTimer(bool flg);

		bool GetTimerFlg() { return m_FinishFlg; }
	};

	*/

 //�w�i���f��
	class BackgroundModel : public GameObject {
	private:
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scale = Vector3(0, 0, 0);
		int m_LayerNum = 0;
		float Rot = 1.0f;
		
	public:
		//�\�z�Ɣj��
		BackgroundModel(const shared_ptr<Stage>& StagePtr, const Vector3& Pos,const Vector3& Scale,const int& LayerNum);
		virtual ~BackgroundModel() {}
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

#pragma region ***�I�[�o�[:���U���g***
	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[����
	//--------------------------------------------------------------------------------------
	class GameOverS : public GameObject
	{
	private:
		//���
		int m_State = 0;

		//�Ó]��
		shared_ptr<GameObject> m_Black;
		//�����x
		float m_BlackAlpha = 0;
		//��̔�����
		shared_ptr<GameObject> m_White;

		//�v�Z�p����
		float m_time = 0;

		//�v���C���[�̖ړI���W
		Vector3 m_TargetPos1;
		Vector3 m_TargetPos2;

		//2
		//���Ƃ������p���x
		float m_Grav1;
		float m_Grav2;
		float m_BombTime = 1.0f;

		//3
		//������
		shared_ptr<MultiAudioObject> m_CreateSe;

		//4
		//�m�C�Y�摜
		shared_ptr<GameObject> m_Noise;
		//�m�C�Y�̉�
		shared_ptr<MultiAudioObject> m_NoiseSe;
		//�Ȃ�����
		bool m_NoiseSeFlg = false;
		//�N���Ó]
		shared_ptr<GameObject> m_BlackSprite;

		//6
		//�Q�[���I�[�o�[���S
		shared_ptr<GameObject> m_GameOverLogo;

		//7
		//���g���C���S
		shared_ptr<GameObject> m_OverRetryLogo;
		//�X�e�Z�����S
		shared_ptr<GameObject> m_OverStageSelectLogo;
		//�^�C�g�����S
		shared_ptr<GameObject> m_OverTitleLogo;

		//�I�����̑傫��
		Vector3 m_LogoSSize = Vector3(300, 100, 1);

		//�I��ԍ� 0 ���g���C 1 �X�e�Z�� 2 �^�C�g��
		int m_SelectNum = 0;

		//�J�[�\��
		shared_ptr<GameObject> m_Cursor;
		//�������邩
		bool m_MoveFlg = true;
		
		//�I����
		shared_ptr<MultiAudioObject> m_SelectSe;


		//8
		//�Ó]��
		shared_ptr<GameObject> m_BlackLast;
		//���艹
		shared_ptr<MultiAudioObject> m_KetteiSe;


		//�v���C���[�̃A�N�Z�T�[
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;

	public :
		GameOverS(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {};

		void OnCreate() override;
		void OnUpdate() override;
	};
	//Abe20170529

	//Abe20170530
	//--------------------------------------------------------------------------------------
	//	���U���g����
	//--------------------------------------------------------------------------------------
	class ResultS : public GameObject
	{
	private :
		//Abe20170601
		//�f�o�b�O�����\���I�u�W�F
		shared_ptr<DebugTxt> m_Debugtxt;
		//Abe20170601

		//���
		int m_State = 0;
		//�v���C���[�̃A�N�Z�T�[
		shared_ptr<GameObject> m_Player1;
		shared_ptr<GameObject> m_Player2;

		//�v�Z�p����
		float m_time = 0;

		//���˂�t���O
		bool m_HopFlg = false;

		//���˂��
		float m_HopPower = 10;
		//���˂�ҋ@����
		const float m_HopWaitTime = 0.5f;
		//���˂�v�Z�p����
		float m_HopTime = 0;
		//�L�����̒��S
		Vector3 m_centerPos;
		//�����̈ʒu
		Vector3 m_Player1TargetPos;
		//�E���̈ʒu
		Vector3 m_Player2TargetPos;

		//1 �J�������߂Â���{�L�������߂Â���
		//�n�߂̑҂���
		const float m_1WaitTime = 1.0f;

		//2 �L��������O�Ɍ�������

		//3 ���˂�

		//4 �~�b�V�����R���v���[�g����������o��
		shared_ptr<GameObject> m_MissCompLogo;

		//5 ������ƈÂ�����
		//����
		shared_ptr<GameObject> m_Black;
		//�����x
		float m_BlackAlpha = 0;

		//6 �~�b�V�����R���v���[�g���������ď�Ɉړ�

		//7 HP�X�v���C�g�ƃ^�C�������Ă���
		//HP�X�v���C�g�̍��W
		Vector3 m_HpPos = Vector3(0, 0, 0);
		//�ړI�̍��W
		Vector3 m_HpTargetPos = Vector3(30, -250, 0);
		//�^�C�����W
		Vector3 m_TimePos = Vector3(0, 0, 0);
		//�^�C���ڕW���W
		Vector3 m_TimeTargetPos = Vector3(-400, -400, 0);

		//8 ���ڂ��o��

		//9 �X�R�A���Z
		shared_ptr<GameObject> m_HpScore;
		shared_ptr<GameObject> m_TimeScore;
		//HP��Time�̒l
		int m_HpAmount;
		int m_TimeAmount;
		//HP��TIME�̃X�R�A�ő�l
		int m_HpScoreTotal = 0;
		int m_TimeScoreTotal = 0;
		//�g�[�^���X�R�A
		int m_TotalScore = 0;
		int m_TotalAmount = 0;

		//10 �g�[�^���X�R�A���Z
		shared_ptr<GameObject> m_TotalScoreSp;

		//11 �����N�\��
		shared_ptr<GameObject> m_RankSp;
		float m_RankAlpha = 0;

		//12 ���΂炭�҂�
		float m_Wait12Time = 3.0f;
		shared_ptr<GameObject> m_Black12;
		shared_ptr<GameObject> m_White12;

		//13 �����������ɂ��ă����N����Ɉړ�

		//14 �I�����o��
		//�I��ԍ� 0�@���̃X�e�[�W 1 ���g���C 2 �X�e�Z�� 3 �^�C�g��
		int m_SelectNum = 0;

		//�J�[�\��
		shared_ptr<GameObject> m_Cursor;
		//�I����
		shared_ptr<MultiAudioObject> m_SelectSe;
		//���艹
		shared_ptr<MultiAudioObject> m_KetteiSe;

		//15 �I��
		//�������邩
		bool m_MoveFlg = true;

	public :
		ResultS(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {};

		void OnCreate() override;
		void OnUpdate() override;

	};
	//Abe20170530
#pragma endregion

	//Abe20170605
	//--------------------------------------------------------------------------------------
	//	�|�[�Y
	//--------------------------------------------------------------------------------------
	class PauseMenu : public GameObject
	{
	private:
		//-----�I�u�W�F�N�g-----
		//�|�[�Y���S
		shared_ptr<GameObject> m_PauseLogo;
		//�Q�[���ɖ߂�
		shared_ptr<GameObject> m_ToGame;
		//���g���C
		shared_ptr<GameObject> m_ToRetry;
		//�X�e�Z��
		shared_ptr<GameObject> m_ToSteSele;
		//�^�C�g��
		shared_ptr<GameObject> m_ToTitle;
		//�G���
		shared_ptr<GameObject> m_EnemyS;
		//�Ó]���~��
		shared_ptr<GameObject> m_Black;

		//�G�l�~�[�̐�
		shared_ptr<GameObject> m_TackleSp;
		shared_ptr<GameObject> m_ShotSp;
		shared_ptr<GameObject> m_TerepoSp;
		shared_ptr<GameObject> m_BombSp;

		//-----�G�l�~�[�̐�-----
		//�ˌ�
		int m_TackleCount = 0;
		//��
		int m_ShotCount = 0;
		//�e���|�[�g
		int m_TereportCount = 0;
		//���e
		int m_BombCount = 0;
		//-----����n-----
		//�I������ 0:�Q�[���ɖ߂� 1:���g���C 2:���� 3:�^�C�g��
		int m_SelectNum = 0;
		//�I�����WX
		int m_SelectX = 0;
		//��I�����WX
		int m_NotSelectX = 0;
		//��������t���O
		bool m_MoveFlg = true;

		//-----�֐�-----
	public:
		PauseMenu(const shared_ptr<Stage>& StagePtr) :GameObject(StagePtr) {};

		void OnCreate() override;
		void OnUpdate() override;

		//�J��
		void Open();
		//����
		void Close();

	};
	//Abe20170605

}
