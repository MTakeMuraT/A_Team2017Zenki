/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//�ނ�����
	//--------------------------------------------------------------------------------------
	///	�^�C�g���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	TitleSprite::TitleSprite(const shared_ptr<Stage>& StagePtr, const Vector2& StartScale, const Vector2& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	TitleSprite::~TitleSprite() {}
	void TitleSprite::OnCreate() {

		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		PtdDraw->SetTextureResource(L"Taitoru_TEST_TX");

		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0);


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
		PtdDraw->SetDiffuse(Color4(1, 1, 1, 1));

		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0);
		SetAlphaActive(true);
		SetDrawLayer(1);

		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}
	void PressSprite::OnUpdate() {
		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//m_alpha += 0.05f;


		/*if (m_alpha > 2) {
		lighton = false;
		}
		else if (m_alpha < 0) {
		lighton = true;
		}*/

		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
			Max = 0.5f;
		}

		if (m_alpha > Max) {
			lighton = false;
		}
		else if (m_alpha < 0) {
			lighton = true;
		}






		if (lighton == true) {
			m_alpha += 0.05;
		}
		else if (lighton == false) {
			m_alpha += -0.05;
		}



		PtdDraw->SetDiffuse(Color4(1, 1, 1, m_alpha));
	}
	void PressSprite::OnLastUpdate() {
		//������\��
		wstring alphaStr(L"Alpha: ");
		alphaStr += Util::FloatToWStr(m_alpha);
		alphaStr += L"\n";

		wstring flg(L"lighton ;\t");
		if (lighton == true) {
			flg += L"true";
		}
		else {
			flg += L"false";
		}
		flg += L"\n";

		wstring str = alphaStr + flg;

		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
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

	DimSprite::DimSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vector2& StartScale, const Vector2& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)
	{
	}

	DimSprite::~DimSprite()
	{
	}
	void DimSprite::OnCreate()
	{
		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0);
		SetAlphaActive(true);
		SetDrawLayer(1);
		auto PtrDraw = AddComponent<PCTSpriteDraw>();
		PtrDraw->SetTextureResource(L"KURO_TX");
		PtrDraw->SetDiffuse(Color4(1, 1, 1, 0));

	}

	void DimSprite::OnUpdate()
	{
		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A)
		{
			dimon = true;
		}

		if (dimon == true)
		{
			dim += 0.05;
		}

		if (dimon == false)
		{
			dim += 0;
		}


		PtdDraw->SetDiffuse(Color4(1, 1, 1, dim));

	}



	////////////////////�f�o�b�N�A�e�X�g�n/////////////////////////////////////////////////////////

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


	//--------------------------------------------------------------------------------------
	//	class FixdBox : public GameObject;
	//	�p�r: �G�l�~�[�e�X�g�p
	//--------------------------------------------------------------------------------------
	FixdBox::FixdBox(const shared_ptr<Stage>& StagePtr, const Vector3& Scale, const Vector3& Rotation, const Vector3& Position, const wstring& TXName) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_TX_Name(TXName)
	{
	}
	void FixdBox::OnCreate() {
		auto Trans = GetComponent<Transform>();

		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);
		Trans->SetPosition(m_Position);

		//Rigidbody
		auto Rigid = AddComponent<Rigidbody>();
		//�Փ˔���
		auto Col = AddComponent<CollisionObb>();
		Col->SetFixed(true);
		Col->SetDrawActive(true);
		//�`��ݒ�
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(m_TX_Name);

		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}
	void FixdBox::OnUpdate() {
		//�v���C���[L
		auto PtrPlayer_L = GetStage()->GetSharedGameObject<Player>(L"GamePlayer", false);
		auto PtrPlayer_L_Trans = PtrPlayer_L->GetComponent<Transform>();
		Vector3 PtrPlayer_L_Pos = PtrPlayer_L_Trans->GetPosition();
		Vector3 PtrPlayer_L_Scale = PtrPlayer_L_Trans->GetScale();
		Vector3 PtrPlayer_L_ScaleHalf_Vec = Vector3(PtrPlayer_L_Scale.x / 2, PtrPlayer_L_Scale.y / 2, PtrPlayer_L_Scale.z / 2);
		//�v���C���[R
		auto PtrPlayer_R = GetStage()->GetSharedGameObject<Player_Second>(L"GamePlayer_R", false);
		auto PtrPlayer_R_Trans = PtrPlayer_R->GetComponent<Transform>();
		Vector3 PtrPlayer_R_Pos = PtrPlayer_R_Trans->GetPosition();
		Vector3 PtrPlayer_R_Scale = PtrPlayer_R_Trans->GetScale();
		Vector3 PtrPlayer_R_ScaleHalf_Vec = Vector3(PtrPlayer_R_Scale.x / 2, PtrPlayer_R_Scale.y / 2, PtrPlayer_R_Scale.z / 2);
		//����
		auto Trans = GetComponent<Transform>();
		Vector3 Pos = Trans->GetPosition();
		Vector3 MyScale = Trans->GetScale();
		Vector3 ScaleHalf = Vector3(MyScale.x / 2, MyScale.y / 2, MyScale.z / 2);

		//
		Vector3 TestScale = Vector3(MyScale.x + 0.5f, MyScale.y, MyScale.z + 0.5f);
		Vector3 TestPos_p = Vector3((Pos.x + (TestScale.x / 2)), Pos.y, (Pos.z + (TestScale.z / 2)));
		Vector3 TestPos_m = Vector3((Pos.x - (TestScale.x / 2)), Pos.y, (Pos.z - (TestScale.z / 2)));
		if (PtrPlayer_L_Pos.x  < TestPos_p.x  && PtrPlayer_L_Pos.x > TestPos_m.x&&
			PtrPlayer_L_Pos.z < TestPos_p.z  && PtrPlayer_L_Pos.z > TestPos_m.z &&
			PtrPlayer_R_Pos.x  < TestPos_p.x  && PtrPlayer_R_Pos.x > TestPos_m.x&&
			PtrPlayer_R_Pos.z < TestPos_p.z  && PtrPlayer_R_Pos.z > TestPos_m.z) {
			Inserted = true;
		}
		else {
			Inserted = false;
		}

		if (Inserted) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].wButtons &XINPUT_GAMEPAD_A) {
				InputStick();
			}
		}
		else {
			auto Rig = GetComponent<Rigidbody>();
			Rig->SetVelocity(0, 0, 0);
		}


	}
	void FixdBox::OnLastUpdate() {

		wstring LogName(L"Enemy");
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\n";

		auto ScaleS = GetComponent<Transform>()->GetScale();
		wstring ScaleStr(L"Position:\t");
		ScaleStr += L"X=" + Util::FloatToWStr(ScaleS.x, 6, Util::FloatModify::Fixed) + L",\t";
		ScaleStr += L"Y=" + Util::FloatToWStr(ScaleS.y, 6, Util::FloatModify::Fixed) + L",\t";
		ScaleStr += L"Z=" + Util::FloatToWStr(ScaleS.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring InterposeStr(L"���ރt���O:");
		if (Inserted) {
			InterposeStr += L"true";
		}
		else {
			InterposeStr += L"false";
		}
		InterposeStr += L"\n";

		wstring str = LogName + FPS + ScaleStr + InterposeStr;
		auto PtrString = GetComponent<StringSprite>();
		//PtrString->SetText(str);
	}

	//�X�e�B�b�N����
	void FixdBox::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}

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


	//--------------------------------------------------------------------------------------
	//	class Enemy01 : public GameObject;
	//	�p�r: �G�l�~�[1�@
	//--------------------------------------------------------------------------------------
	//Abe20170412
	Enemy01::Enemy01(const shared_ptr<Stage>& StagePtr, Vector3 Pos, Vector3 Scale) :
		GameObject(StagePtr),
		m_InitPos(Pos),
		m_Scale(Scale)
	{}

	void Enemy01::OnCreate()
	{
		auto Trans = GetComponent<Transform>();

		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);
		Trans->SetPosition(m_InitPos);

		//Rigidbody
		auto Rigid = AddComponent<Rigidbody>();
		//�Փ˔���
		auto Col = AddComponent<CollisionObb>();
		//unity�ł�����isTrigger�E�E�E�A�������Ȃ�
		//Col->SetFixed(true);
		Col->SetDrawActive(true);
		//�`��ݒ�
		auto Draw = AddComponent<PNTStaticDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(L"SKY_TX");

		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}

	void Enemy01::OnUpdate()
	{
		if (m_StanFlg)
		{
			DamageState();
			//��΂���Ă��� !m_StanFlg��DamageState�ŕύX���������ꍇ�̑΍�
			if (!m_SandFlg)
			{
				GetComponent<Rigidbody>()->SetVelocity(m_Vel);
				m_StanTime += -App::GetApp()->GetElapsedTime();
				//����
				m_Vel *= 0.9f;
				if (!m_StanFlg)
				{
					GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
					m_Vel = Vector3(0, 0, 0);
				}
			}
		}

	}

	void Enemy01::Damage(float Time)
	{
		if (!m_SandFlg)
		{
			m_StanFlg = true;
			m_SandFlg = true;
			m_StanTime = Time * 2;
			//�ςȔ�������A����ɂ�苲�񂾌���������炸�Ɉړ��ł���
			GetComponent<CollisionObb>()->SetFixed(true);
		}
	}

	void Enemy01::Release()
	{
		if (m_SandFlg)
		{
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
			m_SandFlg = false;
			//��΂����������		
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			m_Vel = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);

			m_Vel *= m_VeloPower;
			//�ςȔ���߂��A�A�^�����肪�����H����
			GetComponent<CollisionObb>()->SetFixed(false);

		}


	}

	void Enemy01::DamageState()
	{
		//���܂�Ă���ړ�
		if (m_SandFlg)
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Rig = GetComponent<Rigidbody>();
			Vector3 Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
			Rig->SetVelocity(Vec_Vec3 * 3);
		}

		//���Ԃ����������
		if (m_StanTime < 0)
		{
			m_StanTime = 0;
			m_StanFlg = false;
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
		}
		else
		{
			m_StanTime += -App::GetApp()->GetElapsedTime();

		}
		GetComponent<StringSprite>()->SetText(Util::FloatToWStr(m_StanTime));

	}
	//Abe20170412
	//Abe20170413

	void Enemy01::OnCollision(vector<shared_ptr<GameObject>>& OtherVec)
	{
		if (m_StanFlg)
		{
			for (auto obj : OtherVec)
			{
				auto Enemy01Ptr = dynamic_pointer_cast<Enemy01>(obj);
				if (Enemy01Ptr)
				{
					Enemy01Ptr->Damage(m_StanTime / 2);
					Enemy01Ptr->Release(m_Vel);
				}
			}
		}
	}

	void Enemy01::Release(Vector3 vel)
	{
		if (m_SandFlg)
		{
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
			m_SandFlg = false;
			//��΂����������		
			m_Vel = vel;

			m_Vel *= m_VeloPower;
		}

	}
	//Abe20170413


	//Abe20170418
	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	�p�r: �����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	NumberSprite::NumberSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_num(num),
		m_pos(pos),
		m_scale(scale),
		m_layer(layer)
	{}

	void NumberSprite::OnCreate()
	{

		//��������-------------------------------------
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);
		//��������-------------------------------------

		//�����̉摜�쐬-------------------------
		for (int i = 0; i < 10; i++)
		{
			//���_�z��
			vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV�l�̕ύX
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//���㒸�_
			vertices[0].textureCoordinate = Vector2(from, 0);
			//�E�㒸�_
			vertices[1].textureCoordinate = Vector2(to, 0);
			//�������_
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//�E�����_
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//���_�̌^��ς����V�������_���쐬
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//���b�V���쐬
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//�����̉摜�쐬-------------------------

		//�����X�v���C�g�쐬---------------------
		//�����p�ɐ�������Ă���
		int masternum = m_num;

		//�v�Z���ʓ���Ă����p�̔�
		vector<int> OutNums;

		//�������[�v�A�����쐬
		for (int j = 0; j < m_digit; j++)
		{
			//���������������Z
			m_Constdigit++;

			//��ʂ̌����琔������Ă�
			int num = masternum / pow(10, (m_digit - 1) - j);
			OutNums.push_back(num);
			//�v�Z�p�̌��̍ŏ�ʂ̌���r��
			masternum = masternum % (int)(pow(10, (m_digit - 1) - j));
		}

		//��E�Ƃ̍�
		float distance = m_scale.x / IntervalNums;

		wstring txt;
		//�����t���烋�[�v�I(0�����ʂ̌�����Ă�̂�)
		//�����΂�����ˁA�o�O�N�������Ƃ�����Ȃ�
		for (int j = 0; j < m_digit; j++) {


			//�����I�u�W�F
			auto NumP = GetStage()->AddGameObject<GameObject>();

			//���W�ݒ�
			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*count), m_pos.y, 0);
			TranP->SetScale(m_scale.x, m_scale.y, 1);
			TranP->SetRotation(0, 0, 0);

			//�傫���ݒ�
			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[OutNums[(m_digit - 1) - j]]);
			NumP->SetAlphaActive(true);

			//���C���[�ݒ�
			NumP->SetDrawLayer(m_layer);
			//�����o�ϐ��̊Ǘ������ɒǉ�
			m_Numbers.push_back(NumP);

			//�J�E���g�A�b�v
			count++;

		}
		//�����X�v���C�g�쐬---------------------
	}

	/*
	void NumberSprite::SetPositionVec2(Vector2 pos)
	{
	m_pos = pos;
	//���ɂ��炷��ԉE��0
	float distance = m_scale.x / 1.8f;
	int j = 0;
	for (auto v : m_Numbers)
	{
	v->GetComponent<Transform>()->SetPosition(m_pos.x - (distance*j), m_pos.y - (distance*j), 0);
	j++;
	}
	}

	void NumberSprite::SetScaleVec2(Vector2 scale)
	{
	m_scale = scale;
	for (auto v : m_Numbers)
	{
	v->GetComponent<Transform>()->SetScale(scale.x, scale.y, 0);
	}

	//���ɂ��炷��ԉE��0
	float distance = m_scale.x / 1.8f;
	int j = 0;
	for (auto v : m_Numbers)
	{
	v->GetComponent<Transform>()->SetPosition(m_pos.x - (distance*j), m_pos.y - (distance*j), 0);
	j++;
	}
	}
	*/

	void NumberSprite::SetNum(int num)
	{
		//�}�C�i�X�e��
		if (m_num >= 0)
		{
			m_num = num;
			//���͂��ꂽ�������Ă���
			int digit = 0;
			int innum = num;
			do
			{
				innum /= 10;
				digit++;
			} while (innum > 0);

			//�����p�ɐ�������Ă���
			int masternum = m_num;
			//�v�Z���ʓ���Ă����p�̔�
			vector<int> OutNums;

			//�������[�v�A�����쐬
			for (int j = 0; j < digit; j++)
			{
				//��ʂ̌����琔������Ă�
				int num = masternum / pow(10, (digit - 1) - j);
				OutNums.push_back(num);
				//�v�Z�p�̌��̍ŏ�ʂ̌���r��
				masternum = masternum % (int)(pow(10, (digit - 1) - j));
			}


			//���͂��ꂽ�ق����傫��������
			if (digit > m_digit)
			{
				//�ǉ����镪�������[�v
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
					//�����Ɍ��ǉ������A�����͌�œ����
					m_Constdigit++;

					auto NumP = GetStage()->AddGameObject<GameObject>();

					float distance = m_scale.x / 1.8f;

					auto TranP = NumP->AddComponent<Transform>();
					TranP->SetPosition(m_pos.x - (distance*(m_digit + j)), m_pos.y, 0);
					TranP->SetScale(m_scale.x, m_scale.y, 1);
					TranP->SetRotation(0, 0, 0);

					auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
					DrawP->SetTextureResource(L"NUMBER_TX");
					DrawP->SetMeshResource(m_Mesh[0]);
					NumP->SetAlphaActive(true);

					NumP->SetDrawLayer(m_layer);
					m_Numbers.push_back(NumP);
				}

				for (int i = 0; i < m_Constdigit; i++)
				{
					m_Numbers[i]->SetDrawActive(true);
				}

			}
			//���͂��ꂽ�ق���������
			else if (digit < m_digit)
			{
				//�Y�����悤��-1���炷
				for (int i = m_digit - 1; i > digit - 1; i--)
				{
					m_Numbers[i]->SetDrawActive(false);
				}
			}

			//���X�V
			m_digit = digit;

			//��������ւ�
			masternum = m_num;
			for (int i = 0; i < m_digit; i++)
			{
				m_Numbers[i]->GetComponent<PCTSpriteDraw>()->SetMeshResource(m_Mesh[OutNums[(m_digit - 1) - i]]);
			}

		}
	}

	void NumberSprite::SetNumDraw(bool flg)
	{
		for (auto v : m_Numbers)
		{
			v->SetDrawActive(flg);
		}

	}

	//--------------------------------------------------------------------------------------
	//	class Timer : public GameObject;
	//	�p�r: �^�C�}�[
	//--------------------------------------------------------------------------------------

	Timer::Timer(const shared_ptr<Stage>& StagePtr, int Time, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitTime(Time),
		m_InitPos(pos),
		m_InitScale(scale),
		m_LayerNum(layer)
	{}

	void Timer::OnCreate()
	{
		//�����쐬
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(m_InitTime, m_InitPos, m_InitScale, m_LayerNum);
		//�������ԓ����
		m_Time = m_InitTime;
	}

	void Timer::OnUpdate()
	{
		//�~�߂�t���O�������瓮�����Ȃ�
		if (!m_TimeStopFlg)
		{
			//���Ԍ��炷
			m_Time += -App::GetApp()->GetElapsedTime();
			//�O�b�ȉ��Ȃ�
			if (m_Time <= 0)
			{
				m_FinishFlg = true;
				m_Time = 0;
			}

			m_Numbers->SetNum((int)m_Time);
		}
	}

	void Timer::SetTimer(bool flg)
	{
		m_TimeStopFlg = flg;
	}

	//--------------------------------------------------------------------------------------
	//	class Player_Life : public GameObject;
	//	�p�r:�v���C���[��HP
	//--------------------------------------------------------------------------------------
	Player_Life::Player_Life(const shared_ptr<Stage>& StagePtr, int LifeNum, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_Life(LifeNum),
		m_LifeMax(LifeNum),
		m_InitPos(pos),
		m_InitScale(scale),
		m_layer(layer)
	{}

	void Player_Life::OnCreate()
	{
		for (int i = 0; i < m_Life; i++)
		{
			//HP���g�쐬
			auto HP = GetStage()->AddGameObject<GameObject>();

			//���W�ݒ�
			auto TranP = HP->AddComponent<Transform>();
			TranP->SetPosition(m_InitPos.x + (m_IntervalLife * i * m_InitScale.x), m_InitPos.y, 0);
			TranP->SetScale(m_InitScale.x, m_InitScale.y, 1);
			TranP->SetRotation(0, 0, 0);

			//�傫���ݒ�
			auto DrawP = HP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"HP_TX");
			HP->SetAlphaActive(true);

			//���C���[�ݒ�
			HP->SetDrawLayer(m_layer);
			//�����o�ϐ��̊Ǘ������ɒǉ�
			m_LifeSprite.push_back(HP);

			//�t���[���쐬
			auto HP_Flame = GetStage()->AddGameObject<GameObject>();
			//���W�ݒ�
			auto TranP2 = HP_Flame->AddComponent<Transform>();
			TranP2->SetPosition(m_InitPos.x + (m_IntervalLife * i * m_InitScale.x), m_InitPos.y, 0);
			TranP2->SetScale(m_InitScale.x, m_InitScale.y, 1);
			TranP2->SetRotation(0, 0, 0);

			//�傫���ݒ�
			auto DrawP2 = HP_Flame->AddComponent<PCTSpriteDraw>();
			DrawP2->SetTextureResource(L"HP_FLAME_TX");
			HP_Flame->SetAlphaActive(true);

			//���C���[�ݒ�
			HP_Flame->SetDrawLayer(m_layer);

		}
	}

	void Player_Life::LifeDown(int num)
	{

		m_Life += -num;
		if (m_Life <= 0)
		{
			m_Life = 0;
		}

		//HP����
		for (int i = m_LifeMax - 1; i > m_Life - 1; i--)
		{
			//���ڂ�邯�ǂ܂����C�t���₳�Ȃ�����k�ł���
			m_LifeSprite[i]->SetDrawActive(false);
		}
	}
	//Abe20170418

}
	
	
	
//end basecross
