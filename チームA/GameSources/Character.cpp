/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{



	//--------------------------------------------------------------------------------------
	///	�Œ�̃{�b�N�X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Rotation,
		const Vector3& Position,
		const int& Number
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Num(Number)
	{
	}
	FixedBox::~FixedBox() {}

	//������
	void FixedBox::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//�Փ˔���
		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		PtrDraw->SetOwnShadowActive(true);
		if (m_Num == 1) {
			PtrDraw->SetTextureResource(L"SKY_TX");
		}
		if (m_Num == 2) {
			PtrDraw->SetTextureResource(L"Enemy_TX");
			//Rigidbody������
			auto PtrRedid = AddComponent<Rigidbody>();
		}
	}
	void FixedBox::OnUpdate() {
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeylVec.m_bPressedKeyTbl['A']) {
			SetDrawActive(false);
		
		}
	}

	////--------------------------------------------------------------------------------------
	////	class BlackOut : public GameObject;
	////	�p�r: �t�F�[�h�A�E�g�i���j
	////--------------------------------------------------------------------------------------
	//BlackOut::BlackOut(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr)
	//{}

	//void BlackOut::OnCreate()
	//{
	//	//�E�B���h�E�T�C�Y�擾
	//	Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

	//	auto Ptr = GetComponent<Transform>();
	//	Ptr->SetPosition(0, 0, 0);
	//	Ptr->SetScale(WindowSize.x, WindowSize.y, 1);
	//	Ptr->SetRotation(0, 0, 0);

	//	//�e�N�X�`��������
	//	auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//	PtrSprite->SetTextureResource(L"KURO_TX");

	//	//������
	//	PtrSprite->SetDiffuse(Color4(1, 1, 1, 0));

	//	//�\�����C���[10�ݒ�
	//	SetDrawLayer(10);

	//	//�����x���f
	//	SetAlphaActive(true);
	//	SetDrawActive(false);
	//}

	//void BlackOut::OnUpdate()
	//{
	//	//�N�����
	//	if (m_StartFlg)
	//	{
	//		
	//		//���̉�
	//		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//		m_alpha -= 0.03f;
	//		PtrSprite->SetDiffuse(Color4(0, 0, 0, m_alpha));

	//		if (m_alpha <= 0.0f)
	//		{
	//			m_StartFlg = false;
	//			m_EndFlg = true;

	//		}
	//	}
	//}

	//void BlackOut::StartBlack()
	//{
	//	SetDrawActive(true);
	//	m_StartFlg = true;
	//}

	//bool BlackOut::GetBlackFinish()
	//{
	//	return m_EndFlg;
	//}

	////--------------------------------------------------------------------------------------
	////	class WhiteOut : public GameObject;
	////	�p�r: �t�F�[�h�A�E�g�i���j
	////--------------------------------------------------------------------------------------
	//WhiteOut::WhiteOut(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr)
	//{}

	//void WhiteOut::OnCreate()
	//{
	//	//�E�B���h�E�T�C�Y�擾
	//	Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

	//	auto Ptr = GetComponent<Transform>();
	//	Ptr->SetPosition(0, 0, 0);
	//	Ptr->SetScale(WindowSize.x, WindowSize.y, 1);
	//	Ptr->SetRotation(0, 0, 0);

	//	//�e�N�X�`��������
	//	auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//	PtrSprite->SetTextureResource(L"SIRO_TX");

	//	//������
	//	PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));

	//	//�\�����C���[10�ݒ�
	//	SetDrawLayer(10);

	//	//�����x���f
	//	SetAlphaActive(true);
	//	SetDrawActive(false);
	//}

	//void WhiteOut::OnUpdate()
	//{
	//	//�N�����
	//	if (m_StartFlg)
	//	{
	//		
	//		//���̉�
	//		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//		m_alpha -= 0.0000003f;
	//		PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));

	//		if (m_alpha <= 0.0f){
	//			m_StartFlg = false;
	//			m_EndFlg = true;
	//		}
	//	}
	//}

	//void WhiteOut::StartWhite()
	//{
	//	SetDrawActive(true);
	//	m_StartFlg = true;
	//}

	//bool WhiteOut::GetWhiteFinish()
	//{
	//	return m_EndFlg;
	//}

	////--------------------------------------------------------------------------------------
	////	class BlackIn : public GameObject;
	////	�p�r: �t�F�[�h�C���i���j
	////--------------------------------------------------------------------------------------
	//BlackIn::BlackIn(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr)
	//{}

	//void BlackIn::OnCreate()
	//{
	//	//�E�B���h�E�T�C�Y�擾
	//	Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

	//	auto Ptr = GetComponent<Transform>();
	//	Ptr->SetPosition(0, 0, 0);
	//	Ptr->SetScale(WindowSize.x, WindowSize.y, 1);
	//	Ptr->SetRotation(0, 0, 0);

	//	//�e�N�X�`��������
	//	auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//	PtrSprite->SetTextureResource(L"KURO_TX");

	//	//������
	//	PtrSprite->SetDiffuse(Color4(0, 0, 0, 1));

	//	//�\�����C���[10�ݒ�
	//	SetDrawLayer(10);

	//	//�����x���f
	//	SetAlphaActive(true);
	//	SetDrawActive(false);
	//}

	//void BlackIn::OnUpdate()
	//{
	//	//�N�����
	//	if (m_StartFlg)
	//	{
	//		
	//		//���̉�
	//		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//		m_alpha += 0.03f;
	//		PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));

	//		if (m_alpha >= 1.0f)
	//		{
	//			m_StartFlg = false;
	//			m_EndFlg = true;
	//		}
	//	}
	//}

	//void BlackIn::StartBlackIn()
	//{
	//	SetDrawActive(true);
	//	m_StartFlg = true;
	//}

	//bool BlackIn::GetBlackInFinish()
	//{
	//	return m_EndFlg;
	//}

	////--------------------------------------------------------------------------------------
	////	class WhiteIn : public GameObject;
	////	�p�r: �t�F�[�h�C���i���j
	////--------------------------------------------------------------------------------------
	//WhiteIn::WhiteIn(const shared_ptr<Stage>& StagePtr) :
	//	GameObject(StagePtr)
	//{}

	//void WhiteIn::OnCreate()
	//{
	//	//�E�B���h�E�T�C�Y�擾
	//	Vector2 WindowSize = Vector2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());

	//	auto Ptr = GetComponent<Transform>();
	//	Ptr->SetPosition(0, 0, 0);
	//	Ptr->SetScale(WindowSize.x, WindowSize.y, 1);
	//	Ptr->SetRotation(0, 0, 0);

	//	//�e�N�X�`��������
	//	auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//	PtrSprite->SetTextureResource(L"SIRO_TX");

	//	//������
	//	PtrSprite->SetDiffuse(Color4(1, 1, 1, 0));

	//	//�\�����C���[10�ݒ�
	//	SetDrawLayer(10);

	//	//�����x���f
	//	SetAlphaActive(true);
	//	SetDrawActive(false);
	//}

	//void WhiteIn::OnUpdate()
	//{
	//	//�N�����
	//	if (m_StartFlg)
	//	{
	//		
	//		//���̉�
	//		auto PtrSprite = this->AddComponent<PCTSpriteDraw>();
	//		m_alpha += 0.03f;
	//		PtrSprite->SetDiffuse(Color4(1, 1, 1, m_alpha));

	//		if (m_alpha >= 1.0f)
	//		{
	//			m_StartFlg = false;
	//			m_EndFlg = true;
	//		}
	//	}
	//}

	//void WhiteIn::StartWhiteIn()
	//{
	//	SetDrawActive(true);
	//	m_StartFlg = true;
	//}

	//bool WhiteIn::GetWhiteInFinish()
	//{
	//	return m_EndFlg;
	//}

}
//end basecross
