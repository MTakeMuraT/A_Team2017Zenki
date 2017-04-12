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
		

	public:

		//--------------------------------------------------------------------------------------
		PressSprite(const shared_ptr<Stage>& StagePtr,
			const Vector2& StartScale, const Vector2& StartPos);
		//--------------------------------------------------------------------------------------
		virtual ~PressSprite();
		//--------------------------------------------------------------------------------------

		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------

		virtual void OnUpdate()override {}
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
		//�C�₵�Ă鎞��
		float m_StanTime = 0;
		//���W
		Vector3 m_InitPos;
		//�傫��
		Vector3 m_Scale;
	public :
		Enemy01(const shared_ptr<Stage>& StagePtr,Vector3 Pos,Vector3 Scale);

		void OnCreate() override;
		void OnUpdate() override;

		//�_���[�W��Ԏ�
		void DamageState();
		//�_���[�W�󂯂��Ƃ�
		void Damage(float Time) { if (!m_StanFlg) { m_StanFlg = true; m_StanTime = Time * 3; } }
		//�v���C���[���玞�Ԏ����Ă���� Player_RGetATime�͉�
		//void Damage(){m_StanFlg = true; GetStage()->GetSharedGameObject<Player>(L"Player_R")->GetATime();}
	};
	//Abe20170412

}
//end basecross
