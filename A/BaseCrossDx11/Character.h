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
	//	class Dedug : public GameObject;
	//	�p�r: �X�e�[�W�V�[���@�X�e�[�W�I���̎ʐ^���悹��z
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
}
//end basecross
