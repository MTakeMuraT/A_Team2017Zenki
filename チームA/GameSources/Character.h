/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{


	//--------------------------------------------------------------------------------------
	///	�Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Vector3 m_Position;
		int m_Num;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Rotation,
			const Vector3& Position,
			const int& Number
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
	};
	
	////--------------------------------------------------------------------------------------
	////	class Black : public GameObject;
	////	�p�r: �t�F�[�h�A�E�g�i���j
	////--------------------------------------------------------------------------------------
	//class BlackOut : public GameObject
	//{
	//private:
	//	float m_alpha = 1;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	BlackOut(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//�Ó]�N��
	//	void StartBlack();

	//	//�Ó]�������ǂ����擾
	//	bool GetBlackFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class White : public GameObject;
	////	�p�r: �t�F�[�h�A�E�g�i���j
	////--------------------------------------------------------------------------------------
	//class WhiteOut : public GameObject
	//{
	//private:
	//	float m_alpha = 1;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	WhiteOut(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//�Ó]�N��
	//	void StartWhite();

	//	//�Ó]�������ǂ����擾
	//	bool GetWhiteFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class BlackIN : public GameObject;
	////	�p�r: �t�F�[�h�C���i���j
	////--------------------------------------------------------------------------------------
	//class BlackIn : public GameObject
	//{
	//private:
	//	float m_alpha = 0;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	BlackIn(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//�Ó]�N��
	//	void StartBlackIn();

	//	//�Ó]�������ǂ����擾
	//	bool GetBlackInFinish();
	//};

	////--------------------------------------------------------------------------------------
	////	class WhiteIN : public GameObject;
	////	�p�r: �t�F�[�h�C���i���j
	////--------------------------------------------------------------------------------------
	//class WhiteIn : public GameObject
	//{
	//private:
	//	float m_alpha = 0;
	//	bool m_StartFlg = false;
	//	bool m_EndFlg = false;
	//public:
	//	WhiteIn(const shared_ptr<Stage>& StagePtr);
	//	void OnCreate() override;
	//	void OnUpdate() override;

	//	//�Ó]�N��
	//	void StartWhiteIn();

	//	//�Ó]�������ǂ����擾
	//	bool GetWhiteInFinish();
	//};

}
//end basecross
