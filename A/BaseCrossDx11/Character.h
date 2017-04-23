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
	};

	//--------------------------------------------------------------------------------------
	//	class Player_Life : public GameObject;
	//	�p�r:�v���C���[��HP
	//--------------------------------------------------------------------------------------
	class Player_Life :public GameObject
	{
	private:
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

		//�����p
		//�Ԋu
		float m_IntervalLife = 0.45f;
	public:
		Player_Life(const shared_ptr<Stage>& StagePtr, int LifeNum, Vector2 pos, Vector2 scale, int layer);

		void OnCreate() override;

		//���͂����l�����C�t�������
		void LifeDown(int num);

		int GetLife() { return m_Life; }
	};
	//Abe20170418
	//Abe20170421
	//--------------------------------------------------------------------------------------
	//	�X�v���C�g�̑傫���A�ʒu���m�F����I�u�W�F�N�g
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

}
//end basecross
