/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class TestLin : public GameObject;
	//	�p�r: �V�[���\���e�X�g�n��
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	TestLin::TestLin(const shared_ptr<Stage>& StagePtr,
		const Vector3& Scale,
		const Vector3& Position,
		const int& Type
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Position(Position),
		m_Type(Type)
	{
	}
	TestLin::~TestLin() {}

	//������
	void TestLin::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_Position);

		auto PtrDraw = AddComponent<PCTSpriteDraw>();

		if (m_Type == 1) {
			PtrDraw->SetTextureResource(L"TEST_Taitoru_TX");
		}
		else if (m_Type == 2) {
			PtrDraw->SetTextureResource(L"TEST_Serekuto_TX");
		}
		else if (m_Type == 3) {
			PtrDraw->SetTextureResource(L"TEST_Game_TX");
		}
		SetAlphaActive(true);
	}

	//�ނ�����
	//--------------------------------------------------------------------------------------
	///	�^�C�g���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	TitleSprite::TitleSprite(const shared_ptr<Stage>& StagePtr,const Vector2& StartScale, const Vector2& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	TitleSprite::~TitleSprite() {}
	void TitleSprite::OnCreate() {

		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		PtdDraw->SetTextureResource(L"Taitoru_TEST_TX");

		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x,m_StartScale.y,0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x,m_StartPos.y,0);


		SetDrawLayer(1);
	}

	//--------------------------------------------------------------------------------------
	///	�Ղꂷ���Ɂ[���[�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	PressSprite::PressSprite(const shared_ptr<Stage>& StagePtr,
		const Vector2& StartScale, const Vector2& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	PressSprite::~PressSprite() {}
	void PressSprite::OnCreate() {

		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		PtdDraw->SetTextureResource(L"Prres_any_boten_TEST_TX");

		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0);
		SetAlphaActive(true);
		SetDrawLayer(1);
	}

	//��[��������
	//--------------------------------------------------------------------------------------
	//	class StageSelectSprite : public GameObject;
	//	�p�r: �V�[���\���n��
	//--------------------------------------------------------------------------------------
	StageSelectSprite::StageSelectSprite(const shared_ptr<Stage>& StagePtr,
		const Vector2 & StartScale,
		const Vector2 & StartPos,
		const int& Number) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Num(Number)
	{

	}
	StageSelectSprite::~StageSelectSprite() {}
	void StageSelectSprite::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0);
		auto PtrDraw = AddComponent<PCTSpriteDraw>();
		//�P�����S�@�Q==�g�t���[���@�R==������� (0=�e�X�g�\��)
		if (m_Num == 0) {
			PtrDraw->SetTextureResource(L"SELECT_TEST_TX");
		}
		/*else if (m_Num == 1) {
			PtrDraw->SetTextureResource(L"");
		}
		else if (m_Num == 2)
		{
			PtrDraw->SetTextureResource(L"");
		}
		else if (m_Num == 3) {
			PtrDraw->SetTextureResource(L"");
		}
		else {
			PtrDraw->SetTextureResource(L"");
		}*/
	}





	//--------------------------------------------------------------------------------------
	//	class Dedug : public GameObject;
	//	�p�r:�f�o�b�N
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Dedug::Dedug(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr)
	{
	}
	Dedug::~Dedug() {}

	//������
	void Dedug::OnCreate() {
	}
	void Dedug::OnUpdate() {
	
		auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeylVec.m_bPressedKeyTbl['A']) {
			auto ScenePtr = App::GetApp()->GetScene<Scene>();
			
				PostEvent(1.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
			}
		}

	
}
	
	
	
//end basecross
