/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class TestLin : public GameObject;
	//	用途: シーン表示テスト系統
	//--------------------------------------------------------------------------------------
	//構築と破棄
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

	//初期化
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

	//むっくん
	//--------------------------------------------------------------------------------------
	///	タイトルのスプライト
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
	///	ぷれすえにーきーのスプライト
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

	//ゆーすけくん
	//--------------------------------------------------------------------------------------
	//	class StageSelectSprite : public GameObject;
	//	用途: シーン表示系統
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
		//１＝ロゴ　２==枠フレーム　３==操作説明 (0=テスト表示)
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
	//	用途:デバック
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Dedug::Dedug(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr)
	{
	}
	Dedug::~Dedug() {}

	//初期化
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
