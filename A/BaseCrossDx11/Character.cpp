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
		//�I�[�f�B�I���\�[�X�o�^
		auto pMultiSoundEffect = AddComponent<MultiSoundEffect>();
		pMultiSoundEffect->AddAudioResource(L"Decision_01_SE");
	}
	void PressSprite::OnUpdate() {
		auto PtdDraw = AddComponent<PCTSpriteDraw>();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();


		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_A) {
			Max = 0.5f;
			auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			pMultiSoundEffect->Start(L"Decision_01_SE", 0, 1.0f);
		}
		if (CntlVec[0].wPressedButtons &XINPUT_GAMEPAD_B)
		{
			Max = 2.0f;
			auto pMultiSoundEffect = GetComponent<MultiSoundEffect>();
			pMultiSoundEffect->Start(L"Decision_01_SE", 0, 1.0f);
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
		//PtrString->SetText(str);
	}

	//--------------------------------------------------------------------------------------
	//	�V�[���J�ڂ̃X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	SceneChangeSS::SceneChangeSS(const shared_ptr<Stage>& StagePtr) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + L"SS\\FadeIn\\", L"scene_shange.ssae", L"anime_1",true)
	{
	}

	void SceneChangeSS::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(5, 5, 5);
		Trans->SetRotation(0, 0, 0);

		//�A�j���[�V�����֘A
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(6.5f, 6.5f, 6.5f),
			Vector3(0, 0, 0),
			Vector3(0, 7.5, 0)
			);
		SetToAnimeMatrix(mat);

		//�e�N���X��Create
		SS5ssae::OnCreate();
		//�b������̃t���[����
		SetFps(60.0f);
		//���[�v����
		SetLooped(false);


		//�����x�L����
		SetAlphaActive(true);
		//�`��
		SetDrawActive(true);
		//�\�����C���[
		SetDrawLayer(7);

	}

	void SceneChangeSS::OnUpdate()
	{
		if (m_time < m_LimitTime)
		{
			m_time += App::GetApp()->GetElapsedTime();
			//�A�j���\�V�����X�V
			UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 2);
		}
	}

	void SceneChangeSS::OnAnim()
	{
		m_ActiveFlg = true;
		ChangeAnimation(L"anime_1");
	}

	//Abe20170526
	//--------------------------------------------------------------------------------------
	//	�V�[���J�ڂ̃X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	SceneChangeSSOut::SceneChangeSSOut(const shared_ptr<Stage>& StagePtr) :
		SS5ssae(StagePtr, App::GetApp()->m_wstrDataPath + L"SS\\FadeOut\\", L"scene_shange.ssae", L"anime_1", true)
	{
	}

	void SceneChangeSSOut::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(5, 5, 5);
		Trans->SetRotation(0, 0, 0);

		//�A�j���[�V�����֘A
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(6.5f, 6.5f, 6.5f),
			Vector3(0, 0, 0),
			Vector3(0, 7.5, 0)
			);
		SetToAnimeMatrix(mat);

		//�e�N���X��Create
		SS5ssae::OnCreate();
		//�b������̃t���[����
		SetFps(60.0f);
		//���[�v����
		SetLooped(false);


		//�����x�L����
		SetAlphaActive(true);
		//�`��
		SetDrawActive(true);
		//�\�����C���[
		SetDrawLayer(2);

	}

	void SceneChangeSSOut::OnUpdate()
	{
		if (m_time < m_LimitTime)
		{
			m_time += App::GetApp()->GetElapsedTime();
			//�A�j���\�V�����X�V
			UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 2);
		}
	}

	void SceneChangeSSOut::OnAnim()
	{
		m_ActiveFlg = true;
		ChangeAnimation(L"anime_1");
	}
	//Abe20170526

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

	Enemy01::Enemy01(const shared_ptr<Stage>& StagePtr, const wstring& line):
		GameObject(StagePtr)
	{
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> Tokens;
		//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		Util::WStrToTokenVector(Tokens, line, L',');
		m_Scale = Vector3(
			(float)_wtof(Tokens[4].c_str()),
			(float)_wtof(Tokens[4].c_str()),
			(float)_wtof(Tokens[4].c_str())
		);
		m_InitPos = Vector3(
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str()),
			(float)_wtof(Tokens[3].c_str())
		);

	}


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

			//�Ȃ񂩃o�O���Ă�̂ŏ�����
			OutNums.clear();

			//�������[�v�A�����쐬
			for (int j = 0; j < digit; j++)
			{
				//��ʂ̌����琔������Ă�
				int powpow = pow(10, (digit - 1) - j);
				int numm = masternum / powpow;
				OutNums.push_back(numm);
				//�v�Z�p�̌��̍ŏ�ʂ̌���r��
				masternum = masternum % (int)(pow(10, (digit - 1) - j));
			}


			//���͂��ꂽ�ق����傫��������
			if (digit > m_digit)
			{
				//�ǉ����镪�������[�v
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
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
				//�����Ɍ��ǉ������A�����͌�œ����
				m_Constdigit = digit;

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

	//Abe20170531
	//�ړ�
	void NumberSprite::MoveNums(Vector3 inpos)
	{
		for (auto obj : m_Numbers)
		{
			Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
			pos += inpos;
			obj->GetComponent<Transform>()->SetPosition(pos);
		}
	}

	//���C���[�ݒ�
	void NumberSprite::SetLayer(int num)
	{
		for (auto obj : m_Numbers)
		{
			obj->SetDrawLayer(num);
		}
	}
	//Abe20170531


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

		//�^�C���̔w�i
		auto obj = GetStage()->AddGameObject<GameObject>();
		auto Trans = obj->AddComponent<Transform>();
		Trans->SetPosition(0, 300,0);
		Trans->SetScale(300,150,1);
		Trans->SetRotation(0, 0, 0);

		auto Draw = obj->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"TIMEBACK_TX");

		obj->SetDrawLayer(m_LayerNum - 1);
		obj->SetAlphaActive(true);
	}

	void Timer::OnUpdate()
	{
		//�~�߂�t���O�������瓮�����Ȃ�
		if (!m_TimeStopFlg)
		{
			//���ԉ��Z����
			m_Time += App::GetApp()->GetElapsedTime();
			//�O�b�ȉ��Ȃ�
			if (m_Time >= 999)
			{
				m_FinishFlg = true;
				m_Time = 999;
			}
			

			m_Numbers->SetNum((int)m_Time);
		}
	}

	void Timer::SetTimer(bool flg)
	{
		m_TimeStopFlg = flg;
	}

	//Abe20170531
	//���W�ړ�
	void Timer::MovePos(Vector3 inpos)
	{
		m_Numbers->MoveNums(inpos);
	}

	//���C���[�ݒ�
	void Timer::SetLayer(int num)
	{
		m_Numbers->SetLayer(num);
	}
	//Abe20170531

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

			//Vector3 HP_Flame2 = HP_Flame->GetComponent<Transform>()->GetPosition();


			//m_LifeSprite.push_back(HP_Flame);

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

			m_AllSpriteS.push_back(HP);
			m_AllSpriteS.push_back(HP_Flame);
		}
		m_DieFlg = true;
	}


	void Player_Life::OnUpdate()
	{

		for (int i = m_LifeMax - 1; i > m_Life - 1; i--)
		{

			if (dmg == true)
			{
				for (auto obj : m_AllSpriteS)
				{
					Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
					/////////////
					if (pos.y >= 250) {
						pos.y += -30;
						/////////////
						obj->GetComponent<Transform>()->SetPosition(pos);
					}
					dmg = false;
				}
			}

			if (dmg == false)
			{
				for (auto obj : m_AllSpriteS)
				{
					Vector3 pos = obj->GetComponent<Transform>()->GetPosition();

					////////
					if (pos.y < 300) {
						pos.y += +1;
						/////////////
						obj->GetComponent<Transform>()->SetPosition(pos);
					}
					//pos.y = 300;
					///////
					obj->GetComponent<Transform>()->SetPosition(pos);

				}
			}

		}

	}


	void Player_Life::LifeDown(int num)
	{
		dmg = true;

		m_Life += -num;
		if (m_Life <= 0)
		{
			m_Life = 0;
			m_DieFlg = false;

			//�Q�[���I�[�o�[�֐����Ă�
			dynamic_pointer_cast<GameStage>(GetStage())->GameOver();
		}
		else
		{
			//����łȂ���΃J�������o
			dynamic_pointer_cast<GameStage>(GetStage())->DamageCameraOn();

		}
		//HP����
		for (int i = m_LifeMax - 1; i > m_Life - 1; i--)
		{
			//���ڂ�邯�ǂ܂����C�t���₳�Ȃ�����k�ł���
			m_LifeSprite[i]->SetDrawActive(false);
		}
	}
	//Abe20170418
	//Abe20170421


	//Abe20170531
	//���C�t�X�v���C�g�ړ�
	void Player_Life::MoveSprtieS(Vector3 inpos)
	{
		//���͂��ꂽ���ړ�
		for (auto obj : m_AllSpriteS)
		{
			Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
			pos += inpos;
			obj->GetComponent<Transform>()->SetPosition(pos);
		}
	}
	//���C���[�ύX
	void Player_Life::SetLayer(int num)
	{
		//���C���[�ύX
		for (auto obj : m_AllSpriteS)
		{
			obj->SetDrawLayer(num);
		}

	}
	//Abe20170531

	//--------------------------------------------------------------------------------------
	//	�X�v���C�g�̑傫���A�ʒu���m�F����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	SpritePosScaleChecker::SpritePosScaleChecker(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer, wstring txtname) :
		GameObject(StagePtr),
		m_pos(pos),
		m_scale(scale),
		m_layer(layer),
		m_texturename(txtname)
	{}

	void SpritePosScaleChecker::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_pos);
		Trans->SetScale(m_scale);
		Trans->SetRotation(0, 0, 0);

		auto Draw = AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(m_texturename);

		SetDrawLayer(m_layer);

		SetAlphaActive(true);

		//������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetFont(L"", 40);
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}

	void SpritePosScaleChecker::OnUpdate()
	{
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�T�C�Y�͏\���L�[�ő���
			//************************************
			//	������@
			//	�\���L�[�F�X�P�[�� [��] +Y [��] -Y [��] +X [��] -X
			//	�X�e�B�b�N�F���W�ړ�
			//�@A,B�F����
			//�@X,Y�F����
			//************************************
			//�ω����x�ݒ�
			float Speed = 1.0f;
			//�Q��ɕ����Ƃ��΂��ꂾ���ω�����̂ł����Ă���Ă�
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_A)
			{
				Speed *= 0.5f;
			}
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_B)
			{
				Speed *= 0.5f;
			}

			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_X)
			{
				Speed *= 2.0f;
			}
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_Y)
			{
				Speed *= 2.0f;
			}

			//�T�C�Y------------------------------------------------
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				m_scale += Vector3(0, -1, 0) * Speed;
				GetComponent<Transform>()->SetScale(m_scale);
			}
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				m_scale += Vector3(0, 1, 0) * Speed;
				GetComponent<Transform>()->SetScale(m_scale);
			}
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				m_scale += Vector3(-1, 0, 0) * Speed;
				GetComponent<Transform>()->SetScale(m_scale);
			}
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				m_scale += Vector3(1, 0, 0) * Speed;
				GetComponent<Transform>()->SetScale(m_scale);
			}
			//�ړ�------------------------------------------------
			if (CntlVec[0].fThumbLX > 0.5f)
			{
				m_pos += Vector3(1, 0, 0) * Speed;
				GetComponent<Transform>()->SetPosition(m_pos);
			}
			if (CntlVec[0].fThumbLX < -0.5f)
			{
				m_pos += Vector3(-1, 0, 0) * Speed;
				GetComponent<Transform>()->SetPosition(m_pos);
			}

			if (CntlVec[0].fThumbLY > 0.5f)
			{
				m_pos += Vector3(0, 1, 0) * Speed;
				GetComponent<Transform>()->SetPosition(m_pos);
			}
			if (CntlVec[0].fThumbLY < -0.5f)
			{
				m_pos += Vector3(0, -1, 0) * Speed;
				GetComponent<Transform>()->SetPosition(m_pos);
			}

			//�\��
			wstring txt = L"Pos\nX:" + Util::FloatToWStr(m_pos.x) + L"\nY:" + Util::FloatToWStr(m_pos.y);
			txt += L"\nScale\nX:" + Util::FloatToWStr(m_scale.x) + L"\nY:" + Util::FloatToWStr(m_scale.y);
			GetComponent<StringSprite>()->SetText(txt);
		}
	}
	//Abe20170421
	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	�f�o�b�O�����\������I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	DebugTxt::DebugTxt(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void DebugTxt::OnCreate()
	{
		auto sts = AddComponent<StringSprite>();
		sts->SetText(L"");
		sts->SetFont(L"", 20);
		sts->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		m_Pos = Vector2(16.0f, 16.0f);
		m_Scale = Vector2(624.0f, 624.0f);
		m_ScaleTxt = 20;
		SetDrawLayer(10);
	}
	//�����ݒ�
	void DebugTxt::SetText(wstring txt)
	{
		GetComponent<StringSprite>()->SetText(txt);
	}

	//�傫��(�g)�ݒ�
	void DebugTxt::SetScale(Vector2 sca)
	{
		m_Scale = sca;
		GetComponent<StringSprite>()->SetTextRect(Rect2D<float>(m_Pos.x, m_Pos.y, m_Pos.x + m_Scale.x, m_Pos.y + m_Scale.y));
	}
	//���W�ݒ�
	void DebugTxt::SetPos(Vector2 pos)
	{
		m_Pos = pos;
		GetComponent<StringSprite>()->SetTextRect(Rect2D<float>(m_Pos.x, m_Pos.y, m_Pos.x + m_Scale.x, m_Pos.y + m_Scale.y));
	}
	//�傫��(����)�ݒ�
	void DebugTxt::SetScaleTxt(int scatxt)
	{
		m_ScaleTxt = scatxt;
		GetComponent<StringSprite>()->SetFont(L"", scatxt);
	}
	//���C���[�ݒ�
	void DebugTxt::SetLayer(int num)
	{
		SetDrawLayer(num);
	}

	//�F�ݒ�
	void DebugTxt::SetColor(Vector3 col)
	{
		GetComponent<StringSprite>()->SetFontColor(Color4(col.x, col.y, col.z, 1.0f));
	}
	//Abe20170427


	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChild : public GameObject;
	//	�p�r: �~�T�C�������q�@�@
	//--------------------------------------------------------------------------------------
	ShotEnemyChild::ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const wstring& Line) :
		GameObject(StagePtr)
	{
		////�g�[�N���i�J�����j�̔z��
		//vector<wstring> Tokens;
		////�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
		//Util::WStrToTokenVector(Tokens, Line, L',');

	}
	ShotEnemyChild::ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const float& ShotInterval) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_ShotInterval(ShotInterval)
	{}
	void ShotEnemyChild::OnCreate() {
		SetDrawLayer(10);


		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 ShotEnemyChildMat;
		ShotEnemyChildMat.DefTransformation(
			Vector3(0.2f, 0.2f, 0.2f),
			Vector3(0,140,0),
			Vector3(0.0f, -0.61f, 0.0f)
		);


		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0,0 ,0);
		AddComponent<Rigidbody>();
		//�`��ݒ�
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//���b�V���ݒ�
		Draw->SetMeshResource(L"MissileEnemyChildModel");
	//	Draw->SetTextureResource(L"Glass_TX");
		//SetDrawActive(false);
		//�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFontColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
		//�Pos 
		m_ReferencePoint_Vec3 = Vector3(m_Position.x - (m_Scale.x / 2) / 2, m_Position.y, m_Position.z - m_Scale.z / 2);//�E
		m_ReferencePoint2_Vec3 = Vector3(m_Position.x + (m_Scale.x / 2) / 2, m_Position.y, m_Position.z - m_Scale.z / 2);//��
		m_CenterPoint_Vec3 = Vector3(m_Position.x, m_Position.y, m_Position.z - m_Scale.z / 2);
		SetDrawLayer(-20);
		Draw->SetMeshToTransformMatrix(ShotEnemyChildMat);

		//Abe20170609
		//�A�j���[�V�����ǉ�
		Draw->AddAnimation(L"Shot", 0, 60, true, 60);
		//�A�j���[�V�����ݒ�
		Draw->ChangeCurrentAnimation(L"Shot");
		//Abe20170609

	}
	void ShotEnemyChild::OnUpdate() {
		//Abe20170517
		if (m_ShotFlg)
		//Abe20170517
		{
			//Abe20170614
			//���Ԃ������������
			m_DeleteTime += App::GetApp()->GetElapsedTime();
			if (m_DeleteTime > 5.0f)
			{
				m_ShotFlg = false;
				m_DeleteTime = 0;
				SetUpdateActive(false);
				SetDrawActive(false);
				
				bool flg = false;
				for (auto obj : GetStage()->GetSharedObjectGroup(L"BakusanEFGroup")->GetGroupVector())
				{
					auto ptr = dynamic_pointer_cast<BakusanEF>(obj.lock());
					if (ptr)
					{
						ptr->SetPosScaActive(GetComponent<Transform>()->GetPosition(), Vector3(2, 2, 2));
						flg = true;
						break;
					}
				}
				if (!flg)
				{
					auto obj = GetStage()->AddGameObject<BakusanEF>();
					obj->SetPosScaActive(GetComponent<Transform>()->GetPosition(), Vector3(2, 2, 2));
				}
			}
			//Abe20170614

			DoingSandRotation();
			ShotEnemyChildRot();
			PintNewPos();
			Direction();
			Shot();

			//�A�j���[�V�����X�V
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			GetComponent<PNTBoneModelDraw>()->UpdateAnimation(ElapsedTime);

		}
		else
		{
			Tobu();
		}
	}
	//Abe20170517
	void ShotEnemyChild::Tobu()
	{
		//���W�ړ�
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		pos += m_Velocity * App::GetApp()->GetElapsedTime();
		GetComponent<Transform>()->SetPosition(pos);

		//������ƒx�߂ɗ��Ƃ�
		m_Velocity.y += -9.8f * App::GetApp()->GetElapsedTime();

		//���ɋ߂��Ȃ��������
		if (GetComponent<Transform>()->GetPosition().y <= 1.0f)
		{
			m_ShotFlg = true;
		}
		m_DeleteTime = 0;

	}
	//Abe20170517

	void ShotEnemyChild::OnLastUpdate() {
		//������\��
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\n";


		wstring  str = FPS;
		auto PtrString = GetComponent<StringSprite>();
		//PtrString->SetText(str);
	}
		//�~�T�C�������q�@�̉�] ���܂�Ă��Ȃ��Ƃ�
	void ShotEnemyChild::ShotEnemyChildRot() {
		if (GetShotEnemyChildSandFlg() == false ) {
			auto Trans = GetComponent<Transform>();
			auto Qt = Trans->GetQuaternion();
			auto Rig = GetComponent<Rigidbody>();
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			m_T_Angle += -ElapsedTime * 0.5f;
			Quaternion SpinQt(Vector3(0, 1, 0), ElapsedTime * 0.5f);
			if (abs(m_T_Angle) >= XM_2PI) {
				m_T_Angle = 0;
			}
			Qt *= SpinQt;
			//��]����
			Trans->SetQuaternion(Qt);
			m_Angle = Qt;
			//m_Debug = Rig->GetVelocity();
		}
	}
	//���܂�Ă���Ƃ�
	void ShotEnemyChild::DoingSandRotation() {
		if (GetShotEnemyChildSandFlg()) {
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			auto Qt = Trans->GetQuaternion();
			float ElapsedTime = App::GetApp()->GetElapsedTime();


			//�R���g���[���̎擾
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				Quaternion SpanQt(Vector3(0, 1, 0), -ElapsedTime * 2.0f);
				Qt *= SpanQt;
				Trans->SetQuaternion(Qt);
			}
			else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				Quaternion SpanQt(Vector3(0, 1, 0), ElapsedTime * 2.0f);
				Qt *= SpanQt;
				Trans->SetQuaternion(Qt);
			}
			m_DefaultRot_F = false;
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				SetShotEnemyChildSandFlg(false);
			}
		}
	}
	//�e���ˏꏊ�̉�]
	void ShotEnemyChild::PintNewPos() {
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		auto Scal = Trans->GetScale();
		auto ScalHalf = Scal / 2;
		float RotY = Trans->GetRotation().y;
		RotY += XM_PIDIV2;
		//�����̎Z�o
		Vector3 m_Distance = m_Position - m_ReferencePoint_Vec3;
		Vector3 m_Distance2 = m_Position - m_ReferencePoint2_Vec3;
		Vector3 m_CenteDistancer = m_Position;
		// (���S����A�n�_�̋�����Sin�i��]��+�ꏊ�j) �{�b�N�X�𒆐S�Ƃ��ĉ�]���Ď����̈ʒu���ړ������邱�Ƃ��\
		//�{���Ă���Ƃ���̒l���ꏏ�łȂ��Ɖ�]�����������Ȃ�܂�
		Vector3 NewAngle = Vector3(m_Distance.Length() *sin(RotY + 1.0), m_Position.y + 1.0, m_Distance.Length()* cos(RotY + (1.0)));
		Vector3 New2Angle = Vector3(m_Distance2.Length()*sin(RotY + (-1.0)), m_Position.y + 1.0, m_Distance2.Length() *  cos(RotY + (-1.0)));
		Vector3 NewCenter = Vector3(m_CenteDistancer.Length() * sin(RotY), m_Position.y, m_CenteDistancer.Length() * cos(RotY));
		NewAngle.Normalize();
		New2Angle.Normalize();
		NewCenter.Normalize();
		Pos.y = 0.0f;
		NewAngle += Pos;
		New2Angle += Pos;
		m_NewReferencePoint_Vec3 = NewAngle;
		m_NewReferencePoint2_Vec3 = New2Angle;
		m_NewCenterPoint_Vec3 = NewCenter;
		//�f�o�b�N
		m_getPos = m_NewReferencePoint_Vec3;
		m_getPos2 = m_NewReferencePoint2_Vec3;
		m_getCenter = m_NewCenterPoint_Vec3;
	}
	//����
	void ShotEnemyChild::Shot() {
		auto Ela = App::GetApp()->GetElapsedTime();
		m_Time += Ela;
		//��b�Ԋu�Ŕ���
		if (m_Time > 2) {
			m_cout += 2;
			m_Time = 0.0;

			//Abe20170504
			//�A�^�����肷��I�u�W�F�N�g�ɂ���Ă���������Ă݂�̂ł��傢�ƕύX���܂�
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup");
			/*
			auto obj = GetStage()->AddGameObject<ShotEnemyChildMissile>(
				Vector3(GetPos(true)),
				Vector3(0.8, 0.8, 0.8),
				Vector3(0, 0, 0),
				m_getCenter);
			ColGroup->IntoGroup(obj);
			obj = GetStage()->AddGameObject<ShotEnemyChildMissile>(
				Vector3(GetPos(false)),
				Vector3(0.8, 0.8, 0.8),
				Vector3(0, 0, 0),
				m_getCenter);
			ColGroup->IntoGroup(obj);
			*/

			//Abe20170614
			auto obj = GetStage()->AddGameObject<Missile>();
			m_getCenter.y = 0;
			obj->SetMissileActive(GetPos(true), Vector3(0.8f, 0.8f, 0.8f), m_getCenter * 10, false, 1);
			
			ColGroup->IntoGroup(obj);
			auto obj2 = GetStage()->AddGameObject<Missile>();
			obj->SetMissileActive(GetPos(false), Vector3(0.8f, 0.8f, 0.8f), m_getCenter * 10, false, 1);
			ColGroup->IntoGroup(obj2);
			//Abe20170614

			//Abe20170504

		}
	}

	//�����̎擾
	Vector3 ShotEnemyChild::Direction() {
		auto Trans = GetComponent<Transform>();
		Vector3 Pos = Trans->GetPosition();
		m_Direction_Vec3 = m_getCenter - Pos;
		m_Direction_Vec3.Normalize();
		return m_Direction_Vec3;
	}

	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChildMissile : public GameObject;
	//	�p�r: �~�T�C�������q�@�i�~�T�C���j
	//--------------------------------------------------------------------------------------
	ShotEnemyChildMissile::ShotEnemyChildMissile(const shared_ptr<Stage>& StagePtr, const Vector3& Position, const Vector3& Scale, const Vector3& Rotation, const Vector3& Direction) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Direction(Direction)
	{
	}
	void ShotEnemyChildMissile::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(m_Rotation);
		AddComponent<Rigidbody>();
		//�`��ݒ�
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//���b�V���ݒ�
		//Draw->SetMeshResource(L"DEFAULT_SPHERE");
		//Draw->SetTextureResource(L"Glass_TX");
		Draw->SetMeshResource(L"Missile_Model");
		//����
		m_ShotActive = true;
		//���f���ƃg�����X�t�H�[���̊Ԃ̍���
		Matrix4X4 ShotEnemyChildMat;
		ShotEnemyChildMat.DefTransformation(
			Vector3(0.8f, 0.8f, 0.8f),
			Vector3(0, -90*3.14159265f/180, 0),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		Draw->SetMeshToTransformMatrix(ShotEnemyChildMat);

		//�p�x�ݒ�
		float angle = atan2(m_Direction.z, m_Direction.x) * -1;
		Vector3 rot = GetComponent<Transform>()->GetRotation();
		rot.y = angle;
		GetComponent<Transform>()->SetRotation(rot);
	}
	void ShotEnemyChildMissile::OnUpdate() {
		if (m_ShotActive) {
			//ChildMissileMove();
			//ObjDelete();
		}
	}
	void ShotEnemyChildMissile::ChildMissileMove() {
		m_Speed = 10;
		auto Rig = GetComponent<Rigidbody>();
		m_Direction.y = 0.0f;
		Rig->SetVelocity(m_Direction * m_Speed);

	}
	void ShotEnemyChildMissile::ObjDelete() {

		auto Ela = App::GetApp()->GetElapsedTime();
		m_DeleteTime += Ela;
		if (m_DeleteTime > 10) {
			SetDrawActive(false);
			SetUpdateActive(false);
		}

	}

	/////////////////////////////////////////////

	/*
	EnemyCountSprite::EnemyCountSprite(const shared_ptr<Stage>& StagePtr, int num, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_num(num),
		m_pos(pos),
		m_scale(scale),
		m_layer(layer)
	{
	}
	void EnemyCountSprite::OnCreate() {

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
			TranP->SetPosition(m_pos.x - (distance*count), m_pos.y, 5);
			TranP->SetScale(m_scale.x, m_scale.y, 3);
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


	void EnemyCountSprite::SetNum(int num)
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

	void EnemyCountSprite::SetNumDraw(bool flg)
	{
		for (auto v : m_Numbers)
		{
			v->SetDrawActive(flg);
		}

	}*/



	////////////////////////////////////////////////////

	EnemyCountA::EnemyCountA(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_LayerNum(layer)
	{}

	void EnemyCountA::OnCreate()
	{
		//�����쐬
		//Abe20170519������ƏC��
		Vector2 pos = m_InitPos;
		//����ɂ��炷
		pos.x += -m_InitScale.x * 0.5f;
		pos.y += +m_InitScale.y * 0.5f;
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(0,pos, m_InitScale, m_LayerNum);
		//�E����
		pos.x += +m_InitScale.x * 1;
		pos.y += -m_InitScale.y * 1;

		m_MaxNumber = GetStage()->AddGameObject<NumberSprite>(0, pos, m_InitScale, m_LayerNum);

		m_EnemyCunt = 0;
		m_EnemyMaxCount = 0;

		auto ptr = GetStage()->AddGameObject<GameObject>();

		auto Trans = ptr->AddComponent<Transform>();
		Trans->SetPosition(m_InitPos.x, m_InitPos.y, 0);
		Trans->SetRotation(0, 0, 0);
		Trans->SetScale(m_InitScale.x,m_InitScale.y,1);

		auto Draw = ptr->AddComponent<PCTSpriteDraw>();
		Draw->SetTextureResource(L"ENEMYCOUNTSLASH_TX");
		ptr->SetAlphaActive(true);
		ptr->SetDrawLayer(3);
	}

	void EnemyCountA::OnUpdate()
	{
		m_EnemyCunt = 0;

		auto Group = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		//	auto ShellVec = Group->GetGroupVector();

		for (auto obj : Group) {
			//�L���X�g
			//auto ptr = dynamic_pointer_cast<TackleEnemy>(obj.lock());
			auto ptr1 = dynamic_pointer_cast<TackleEnemy>(obj.lock());
			if (ptr1)
			{
				if (ptr1->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);
				}
			}

			auto ptr2 = dynamic_pointer_cast<BombEnemy>(obj.lock());
			if (ptr2)
			{
				if (ptr2->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);
				}
			}

			auto ptr3 = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
			if (ptr3)
			{
				if (ptr3->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);
				}
			}

			auto ptr4 = dynamic_pointer_cast<ShotEnemy>(obj.lock());
			if (ptr4)
			{
				if (ptr4->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);
				}
			}
		}
		if (m_EnemyMaxCount == 0)
		{
			m_EnemyMaxCount = m_EnemyCunt;
			m_MaxNumber->SetNum((int)m_EnemyMaxCount);
		}

		m_Numbers->SetNum((int)m_EnemyCunt);

		if (m_EnemyCunt == 0)
		{
			dynamic_pointer_cast<GameStage>(GetStage())->Result();
		}
	}



	////////////////////////////////////////////////////
	//Abe20170519MukkuMarge��ł܂Ƃ߂���̂�EnemyCountA�̂ق��ɂ܂Ƃ�
	/*

	EnemyCountB::EnemyCountB(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_LayerNum(layer)
	{}

	void EnemyCountB::OnCreate()
	{
		//�����쐬
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(0,m_InitPos, m_InitScale, m_LayerNum);

		m_EnemyCunt = 0;


	}

	void EnemyCountB::OnUpdate()
	{
		m_EnemyCunt = 0;

		auto Group = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		//auto ShellVec = Group->GetGroupVector();

		for (auto obj : Group) {
			//�L���X�g
			//auto ptr = dynamic_pointer_cast<TackleEnemy>(obj.lock());
			auto ptr1 = dynamic_pointer_cast<TackleEnemy>(obj.lock());
			if (ptr1)
			{
				if (ptr1->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);

				}
			}

			auto ptr2 = dynamic_pointer_cast<BombEnemy>(obj.lock());
			if (ptr2)
			{
				if (ptr2->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);

				}
			}

			auto ptr3 = dynamic_pointer_cast<TeleportEnemy>(obj.lock());
			if (ptr3)
			{
				if (ptr3->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);

				}
			}

			auto ptr4 = dynamic_pointer_cast<ShotEnemy>(obj.lock());
			if (ptr4)
			{
				if (ptr4->GetDrawActive())
				{
					m_EnemyCunt++;
					//m_Numbers->SetNum((int)m_EnemyCunt);

				}
			}

		}
		if (m_MaxCount == 0)
		{
			m_MaxCount = m_EnemyCunt;
			m_Numbers->SetNum((int)m_MaxCount);
		}
	}*/

	//�w�i���f��
	BackgroundModel::BackgroundModel(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scale,const int& LayerNum):
		GameObject(StagePtr),
		m_Pos(Pos),
		m_Scale(Scale),
		m_LayerNum(LayerNum)
	{}
	void BackgroundModel::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetScale(m_Scale * 1.5);

		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"Background_Model");
		
		if (m_LayerNum == 1) {
			Trans->SetPosition(m_Pos);
			Trans->SetRotation(0, 50, 0);
			SetDrawLayer(3);
			SetAlphaActive(true);
		}
		else {
			Trans->SetPosition(m_Pos);
			Trans->SetRotation(0, 0, 0);
			SetDrawLayer(2);
			SetAlphaActive(true);
		}
	}
	void BackgroundModel::OnUpdate() {
		if (m_LayerNum == 1) {
			Rot += 0.01f;
			auto Trans = GetComponent<Transform>();
			Trans->SetRotation(0, Rot, 0);
		}
		else {
			Rot += -0.01f;
			auto Trans = GetComponent<Transform>();
			Trans->SetRotation(0, Rot, 0);
		}
		
	}
	//Abe20170529
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[����
	//--------------------------------------------------------------------------------------
	void GameOverS::OnCreate()
	{
		//�S���̓����I�u�W�F�N�g���~�߂�
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//�A�^������~�߂�
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(false);
		}
		//�S���~�߂�
		for (auto obj : ColGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : EnemyGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : BombGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : SearchChildGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : UgokuGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}

		//��Ԃ�������
		m_State = 0;

		//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");
		//���łɃ��C���[�グ�Ƃ�(�ƕ\�������邭�����)
		//m_Player1->SetDrawLayer(11);
		//m_Player2->SetDrawLayer(11);

		//�v���C���[����O��
		m_Player1->SetUpdateActive(false);
		m_Player2->SetUpdateActive(false);

		//�v���C���[�Ǘ����Ă��~�߂�
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl",false)->SetUpdateActive(false);

		//�ړ��ڕW�ݒ�
		m_TargetPos1 = Vector3(-2, 10, 0);
		m_TargetPos2 = Vector3(2, 10, 0);

		//�Ó]���Ɣ����쐬
		auto Black = GetStage()->AddGameObject<GameObject>();
		auto TransB = Black->AddComponent<Transform>();
		TransB->SetPosition(0, 8, -3);
		TransB->SetScale(100, 100, 1);
		TransB->SetRotation(90 * 3.14159265f / 180, 0, 0);

		auto DrawB = Black->AddComponent<PNTStaticDraw>();
		DrawB->SetTextureResource(L"OVERBLACK_TX");
		DrawB->SetMeshResource(L"DEFAULT_SQUARE");
		DrawB->SetDiffuse(Color4(1, 1, 1, 0));

		Black->SetDrawLayer(9);
		Black->SetAlphaActive(true);
		m_Black = Black;
		//����
		auto White = GetStage()->AddGameObject<GameObject>();
		auto TransW = White->AddComponent<Transform>();
		TransW->SetPosition(0, 8.2f, -3);
		TransW->SetScale(100, 100, 1);
		TransW->SetRotation(0, 0, 0);

		auto DrawW = White->AddComponent<PNTStaticDraw>();
		DrawW->SetTextureResource(L"OVERWHITE_TX");
		DrawW->SetMeshResource(L"DEFAULT_SQUARE");
		DrawW->SetDiffuse(Color4(1, 1, 1, 0));

		White->SetDrawLayer(11);
		White->SetAlphaActive(true);

		m_White = White;
		/*m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"Loss_BGM");*/
	}

	void GameOverS::OnUpdate()
	{
		switch (m_State)
		{
			//�v���C���[����Ɉړ�
		case 0:
			if (true)
			{
				//�Ó]
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				if (m_BlackAlpha < 1.0f)
				{
					m_Black->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				//�v���C���[��ړI�n�Ɉړ�
				Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();
				Vector3 pdir1 = m_TargetPos1 - ppos1;
				Vector3 pdir2 = m_TargetPos2 - ppos2;
				pdir1 /= 10;
				pdir2 /= 10;
				ppos1 += pdir1;
				ppos2 += pdir2;

				m_Player1->GetComponent<Transform>()->SetPosition(ppos1);
				m_Player2->GetComponent<Transform>()->SetPosition(ppos2);

				bool flg1 = false;
				bool flg2 = false;

				if (abs(m_TargetPos1.x - ppos1.x) + abs(m_TargetPos1.y - ppos1.y) + abs(m_TargetPos1.z - ppos1.z) < 0.1f)
				{
					flg1 = true;
				}
				if (abs(m_TargetPos2.x - ppos2.x) + abs(m_TargetPos2.y - ppos2.y) + abs(m_TargetPos2.z - ppos2.z) < 0.1f)
				{
					flg2 = true;
				}

				if (flg1 && flg2)
				{
					//��Ԑi�߂�
					m_State = 1;

					//�J�����ړ�����
					dynamic_pointer_cast<GameStage>(GetStage())->CameraStop();
				}
			}
			break;
			//�J�������߂Â���
		case 1:
			if (true)
			{
				if (dynamic_pointer_cast<GameStage>(GetStage())->GameOverCamera())
				{
					//��Ԑi�߂�
					m_State = 2;
					//���Ƃ����x�ς��Ď኱������
					m_Grav1 = 3;
					m_Grav2 = 3;
					//������
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
					pos1.y += 0.5f;
					pos2.y += 0.5f;
					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//���ԏ�����
					m_time = 0;
				}
			}
			break;
			//�v���C���[�����ɓ|��
		case 2:
			if (true)
			{
				Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
				//������x�܂ŗ�����܂ŗ��Ƃ�
				if (pos1.y >= 10)
				{
					pos1.y += m_Grav1 * App::GetApp()->GetElapsedTime();
					pos2.y += m_Grav2 * App::GetApp()->GetElapsedTime();

					m_Grav1 += -9.8f * App::GetApp()->GetElapsedTime();
					m_Grav2 += -9.8f * App::GetApp()->GetElapsedTime();

					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//��]
					Vector3 rot1 = m_Player1->GetComponent<Transform>()->GetRotation();
					Vector3 rot2 = m_Player2->GetComponent<Transform>()->GetRotation();

					rot1 += Vector3(-0.5f,0.3f,-0.5f);
					rot2 += Vector3(0.5f, 0.6f, 0.3f);

					m_Player1->GetComponent<Transform>()->SetRotation(rot1);
					m_Player2->GetComponent<Transform>()->SetRotation(rot2);
				}
				else
				{
					m_time += App::GetApp()->GetElapsedTime();
					//������Ƒ҂�
					if (m_time > m_BombTime)
					{
						//�����G�t�F�N�g
						auto obj = GetStage()->AddGameObject<BombEffect>();
						auto obj2 = GetStage()->AddGameObject<BombEffect>();
						obj->SetPosActive(m_Player1->GetComponent<Transform>()->GetPosition());
						obj2->SetPosActive(m_Player2->GetComponent<Transform>()->GetPosition());

						obj->SetLayer(10);
						obj2->SetLayer(10);

						//�L������\��
						m_Player1->SetDrawActive(false);
						m_Player2->SetDrawActive(false);

						//���o��
						m_CreateSe = ObjectFactory::Create<MultiAudioObject>();
						m_CreateSe->AddAudioResource(L"OverBombSE");
						m_CreateSe->Start(L"OverBombSE", 0.5f);

						//��������
						m_BlackAlpha = 0.8f;
						m_White->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

						//��Ԑi�߂�
						m_State = 3;
					}
				}
			}
			break;
			//��ʔ����̖߂��Ă�
		case 3:
			if (true)
			{
				if (m_BlackAlpha > 0)
				{
					m_BlackAlpha += -App::GetApp()->GetElapsedTime()/2;
					//�����̖߂�
					m_White->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				else
				{
					//��Ԑi�߂�
					m_State = 4;

					//�m�C�Y�쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1280, 720, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERNOISE_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_Noise = obj;

					//�Ó]��
					auto obj2 = GetStage()->AddGameObject<GameObject>();
					auto Trans2 = obj2->AddComponent<Transform>();
					Trans2->SetPosition(0, 0, 0);
					Trans2->SetScale(1280, 720, 1);
					Trans2->SetRotation(0, 0, 0);

					auto Draw2 = obj2->AddComponent<PCTSpriteDraw>();
					Draw2->SetTextureResource(L"OVERLASTBLACK_TX");
					Draw2->SetDiffuse(Color4(1, 1, 1, 0));

					obj2->SetDrawLayer(13);
					obj2->SetAlphaActive(true);

					m_BlackSprite = obj2;

					//�����x0
					m_BlackAlpha = 0;
				}
			}
			break;
			//�m�C�Y�o��
		case 4:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				m_Noise->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				if (m_BlackAlpha > 0.2f && !m_NoiseSeFlg)
				{
					//�Q��ڂ͂���Ȃ��悤��
					m_NoiseSeFlg = true;

					//���炷
					m_NoiseSe = ObjectFactory::Create<MultiAudioObject>();
					m_NoiseSe->AddAudioResource(L"OverNoiseSE");
					m_NoiseSe->Start(L"OverNoiseSE", 0.2f);
				}
				if (m_BlackAlpha > 2.0f)
				{
					//��Ԉړ�
					m_State = 5;

					m_BlackAlpha = 0;

					m_NoiseSe->Stop(L"OverNoiseSE");
				}
			}
			break;
			//�m�C�Y�̏�ɈÓ]
		case 5:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime() / 2;
				m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				if (m_BlackAlpha > 1.0f)
				{
					//��Ԉړ�
					m_State = 6;

					//�Q�[���I�[�o�[�����쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 30, 0);
					Trans->SetScale(800, 400, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERLOGO_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(14);
					obj->SetAlphaActive(true);

					m_GameOverLogo = obj;

					m_BlackAlpha = 0;
				}
			}
			break;
			//�Q�[���I�[�o�[�����o��
		case 6:
			if (true)
			{
				if (OnBgmflg == false) {
					//m_AudioObjectPtr->Start(L"Loss_BGM", XAUDIO2_LOOP_INFINITE, 0.5f);
					OnBgmflg = true;
				}
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				if (m_BlackAlpha < 1.0f)
				{
					m_GameOverLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1,1,1,m_BlackAlpha));

				}
				else
				{
					//��ԕύX
					m_State = 7;

					//�I�����쐬
					//���g���C
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-300, -200, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERRETRYLOGO_TX");

					obj->SetDrawLayer(14);
					obj->SetAlphaActive(true);

					m_OverRetryLogo = obj;

					//�X�e�Z��
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, -200, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERSTASELELOGO_TX");

					obj->SetDrawLayer(14);
					obj->SetAlphaActive(true);

					m_OverStageSelectLogo = obj;

					//�^�C�g��
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(300, -200, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERTITLELOGO_TX");

					obj->SetDrawLayer(14);
					obj->SetAlphaActive(true);

					m_OverTitleLogo = obj;

					//�J�[�\���쐬------------------------------------
					auto CursorSprite = GetStage()->AddGameObject<GameObject>();
					//���W
					auto CTrans = CursorSprite->AddComponent<Transform>();
					CTrans->SetPosition(-300, -240, 0);
					CTrans->SetScale(180, 20, 1);
					CTrans->SetRotation(0, 0, 0);

					//�`��
					auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
					CDraw->SetTextureResource(L"OVERCURSOR_TX");

					//���C���[�ݒ�
					CursorSprite->SetDrawLayer(15);

					//�����x�L����
					CursorSprite->SetAlphaActive(true);

					m_Cursor = CursorSprite;

					//���炷����
					m_SelectSe = ObjectFactory::Create<MultiAudioObject>();
					m_SelectSe->AddAudioResource(L"CURSORMOVE_SE");

				}

			}
			break;
			//�I���ł���悤��
		case 7:
			if (true)
			{		
				//�R���g���[���擾
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{
					//�J�[�\������������
					if (m_MoveFlg)
					{
						//�E
						if (CntlVec[0].fThumbLX > 0.5f)
						{
							m_SelectNum++;
							if (m_SelectNum > 2)
							{
								m_SelectNum = 0;
							}
							//������t���O�~�߂�
							m_MoveFlg = false;

						}
						//��
						if (CntlVec[0].fThumbLX < -0.5f)
						{
							m_SelectNum--;
							if (m_SelectNum < 0)
							{
								m_SelectNum = 2;
							}
							//������t���O�~�߂�
							m_MoveFlg = false;
						}

						if (!m_MoveFlg)
						{
							//���炷
							m_SelectSe->Start(L"CURSORMOVE_SE", 0.5f);

							//�ړ�
							switch (m_SelectNum)
							{
							case 0:
								m_Cursor->GetComponent<Transform>()->SetPosition(-300, -240, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(180, 20, 1);
								break;
							case 1:
								m_Cursor->GetComponent<Transform>()->SetPosition(0, -240, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(250, 20, 1);
								break;
							case 2:
								m_Cursor->GetComponent<Transform>()->SetPosition(310, -240, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(180, 20, 1);
								break;
							default:
								break;
							}
						}
					}
					//�����Ɠ����Ȃ��悤��
					else
					{
						if (abs(CntlVec[0].fThumbLX) < 0.5f && abs(CntlVec[0].fThumbLX) > -0.5f)
						{
							m_MoveFlg = true;
						}
					}

					//A�{�^�������ꂽ��ړ�
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						//��ԕύX
						m_State = 8;

						//�Ó]���쐬
						auto obj = GetStage()->AddGameObject<GameObject>();
						auto Trans = obj->AddComponent<Transform>();
						Trans->SetPosition(0, 0, 0);
						Trans->SetScale(1280, 720, 1);
						Trans->SetRotation(0, 0, 0);

						auto Draw = obj->AddComponent<PCTSpriteDraw>();
						Draw->SetTextureResource(L"OVERBLACK_TX");
						Draw->SetDiffuse(Color4(1, 1, 1, 0));

						obj->SetDrawLayer(15);
						obj->SetAlphaActive(true);

						m_BlackLast = obj;

						//�����x0
						m_BlackAlpha = 0;


						//���炷
						m_KetteiSe = ObjectFactory::Create<MultiAudioObject>();
						m_KetteiSe->AddAudioResource(L"DECIDE_SE");
						m_KetteiSe->Start(L"DECIDE_SE", 0.5f);

					}
				}
			}
			break;
			//�Ó]�ƑJ��
		case 8:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				if (m_BlackAlpha < 1.5f)
				{
					m_BlackLast->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				else
				{
					switch (m_SelectNum)
					{
						//���g���C
					case 0:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//	m_AudioObjectPtr->Stop(L"Loss_BGM");
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//�X�e�Z��
					case 1:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//	m_AudioObjectPtr->Stop(L"Loss_BGM");
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
						}
						break;
						//�^�C�g��
					case 2:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//	m_AudioObjectPtr->Stop(L"Loss_BGM");
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
						}
						break;
					}

				}
			}
			break;
		default:
			break;
		}
	}

	//Abe20170529
	//Abe20170531
	//--------------------------------------------------------------------------------------
	//	���U���g����
	//--------------------------------------------------------------------------------------
	void ResultS::OnCreate()
	{
		if (!m_TutorialFlg)
		{
			//�S���̓����I�u�W�F�N�g���~�߂�
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
			auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
			auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
			auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
			//�A�^������~�߂�
			auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
			if (colmanptr)
			{
				colmanptr->SetUpdateActive(false);
			}
			//�S���~�߂�
			for (auto obj : ColGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}
			for (auto obj : EnemyGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}
			for (auto obj : BombGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}
			for (auto obj : SearchChildGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}
			for (auto obj : UgokuGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}

			//��Ԃ�������
			m_State = 0;

			//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
			m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
			m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");
			//���łɃ��C���[�グ�Ƃ�(�ƕ\�������邭�����)
			//m_Player1->SetDrawLayer(11);
			//m_Player2->SetDrawLayer(11);

			//�v���C���[����O��
			m_Player1->SetUpdateActive(false);
			m_Player2->SetUpdateActive(false);

			//�v���C���[�Ǘ����Ă��~�߂�
			GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

			//�v���C���[�̖ڕW���W�A���S���W���擾
			m_centerPos = (m_Player1->GetComponent<Transform>()->GetPosition() + m_Player2->GetComponent<Transform>()->GetPosition()) / 2;
			m_Player1TargetPos = m_centerPos;
			m_Player1TargetPos.x += -2;
			m_Player2TargetPos = m_centerPos;
			m_Player2TargetPos.x += 2;
		}
		//�`���[�g���A���̎�
		else
		{
			//��Ԃ�������
			m_State = 0;

			//�v���C���[�̃A�N�Z�T�[�I�Ȃ�
			m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
			m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

			//�v���C���[�̖ڕW���W�A���S���W���擾
			m_centerPos = (m_Player1->GetComponent<Transform>()->GetPosition() + m_Player2->GetComponent<Transform>()->GetPosition()) / 2;
			m_Player1TargetPos = m_centerPos;
			m_Player1TargetPos.x += -2;
			m_Player2TargetPos = m_centerPos;
			m_Player2TargetPos.x += 2;

		}
		//Abe20170601
		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(15);
		//�F�ԂɕύX
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);
		//Abe20170601
	
	}
	
	void ResultS::OnUpdate()
	{
		if (!m_TutorialFlg)
		{
			//�R���g���[��
			auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			switch (m_State)
			{
				//���΂炭�҂�
			case 0:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_1WaitTime)
					{
						//��ԕύX
						m_State = 1;

						//���ԏ�����
						m_time = 0;

						//�J������~
						dynamic_pointer_cast<GameStage>(GetStage())->CameraStop();
					}
				}
				break;
				//�J�������߂Â���{�L�������߂Â���
			case 1:
				if (true)
				{
					//�J���������Ă�t���O
					bool flg1 = false;
					//�J�������ړ����ĖڕW�n�_�ɋ߂�������
					if (dynamic_pointer_cast<GameStage>(GetStage())->ResultCamera(m_centerPos))
					{
						flg1 = true;
					}

					//�v���C���[��ړI�n�Ɉړ�
					Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();
					Vector3 pdir1 = m_Player1TargetPos - ppos1;
					Vector3 pdir2 = m_Player2TargetPos - ppos2;
					pdir1 /= 10;
					pdir2 /= 10;
					ppos1 += pdir1;
					ppos2 += pdir2;

					bool flg2 = false;
					bool flg3 = false;

					//�߂���Δ���p�̃t���O��true�ɂ��A������΋߂Â���
					if (abs(m_Player1TargetPos.x - ppos1.x) + abs(m_Player1TargetPos.y - ppos1.y) + abs(m_Player1TargetPos.z - ppos1.z) < 0.1f)
					{
						flg2 = true;
					}
					else
					{
						m_Player1->GetComponent<Transform>()->SetPosition(ppos1);
					}
					if (abs(m_Player2TargetPos.x - ppos2.x) + abs(m_Player2TargetPos.y - ppos2.y) + abs(m_Player2TargetPos.z - ppos2.z) < 0.1f)
					{
						flg3 = true;
					}
					else
					{
						m_Player2->GetComponent<Transform>()->SetPosition(ppos2);
					}


					if (flg1 && flg2 && flg3)
					{
						//��ԕύX
						m_State = 2;
					}
				}
				break;
				//�L��������O�Ɍ�������
			case 2:
				if (true)
				{
					//��]
					Vector3 rot1 = m_Player1->GetComponent<Transform>()->GetRotation();
					Vector3 rot2 = m_Player2->GetComponent<Transform>()->GetRotation();
					rot1.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
					rot2.y += -180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();

					//�Ȃ񂩕ςȂƂ��ňႤ������]���邩�炻��~�߂�
					rot1 = Vector3(0, rot1.y, 0);
					rot2 = Vector3(0, rot2.y, 0);
					//��̎�O��1.6���炢
					if (rot1.y >= 1.4f && rot1.y <= 1.8f)
					{
						//��]�Œ�
						rot1.y = 90 * 3.14159265f / 180;
						rot2.y = 90 * 3.14159265f / 180;

						//��ԕύX
						m_State = 3;
						//���˂�͐ݒ�
						float m_HopPower = 10;

						//���˂�t���O�I��
						m_HopFlg = true;

					}
					m_Player1->GetComponent<Transform>()->SetRotation(rot1);
					m_Player2->GetComponent<Transform>()->SetRotation(rot2);

				}
				break;
				//���˂�
			case 3:
				if (true)
				{
					//��ԕύX
					m_State = 4;

					//�~�b�V�����R���v���[�g�����쐬
					//�Ó]���쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-2000, 0, 0);
					Trans->SetScale(1500, 600, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"MISSIONCOMPLETE_TX");

					obj->SetDrawLayer(11);
					obj->SetAlphaActive(true);

					m_MissCompLogo = obj;

				}
				break;
				//�~�b�V�����R���v���[�g����������o��
			case 4:
				if (true)
				{
					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();

					//���S�܂ŗ�����
					if (pos.x > 0 || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 41;
					}

					//���W�ړ�
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//��������X�L�b�v�@�\�ǉ��X�L�b�v�@�\�S�ʂ̎�����20170627Abe
			case 41:
				if (true)
				{
					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();

					//�Ó]���쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1280, 720, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTBLACK_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(10);
					obj->SetAlphaActive(true);

					m_Black = obj;

					m_BlackAlpha = 0;

					
					//���W�Œ�
					pos.x = 0;

					//��ԕύX
					m_State = 5;

					//���W�ړ�
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);

				}
				break;
				//������ƈÂ�����
			case 5:
				if (true)
				{
					if (m_BlackAlpha < 0.5f)
					{
						m_BlackAlpha += App::GetApp()->GetElapsedTime();
					}
					else
					{
						//��ԕύX
						m_State = 51;
					}

					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						//�����x�Œ�
						m_BlackAlpha = 0.5f;
						//��ԕύX
						m_State = 51;
					}
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				}
				break;
			case 51:
				if (true)
				{
					//�����x�Œ�
					m_BlackAlpha = 0.5f;
					//�����x�ݒ�
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

					m_State = 6;
				}
				break;
				//�~�b�V�����R���v���[�g���������ď�Ɉړ�
			case 6:
				if (true)
				{
					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					if (pos.y < 200)
					{
						pos.y += 600 * App::GetApp()->GetElapsedTime();
					}

					//�傫�������Ă���
					Vector3 sca = m_MissCompLogo->GetComponent<Transform>()->GetScale();
					if (sca.x > 1200)
					{
						sca.x *= 0.95f;
						sca.y *= 0.95f;
					}
					else
					{
						sca.x = 1200;
						sca.y = 420;
					}

					if (pos.y > 200 && sca.x <= 1200)
					{
						m_State = 61;
					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 61;
					}

					//���W�Ƒ傫���X�V
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
			case 61:
				if (true)
				{

					//��ԕύX
					m_State = 7;

					//�^�C�}�[�����Ă���
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HP�X�v���C�g�����Ă���
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					//���C���[�ς���
					timeptr->SetLayer(11);
					hpptr->SetLayer(11);

					//const�Ő錾���Ă��X�V����Ȃ�unk�Ȃ̂�
					//HP�X�v���C�g��Time�̖ړI���W���Đݒ�
					m_HpTargetPos = Vector3(30, -250, 0);
					m_TimeTargetPos = Vector3(-400, -400, 0);


					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					//�傫�������Ă���
					Vector3 sca = m_MissCompLogo->GetComponent<Transform>()->GetScale();

					pos.y = 200;
					sca.x = 1200;
					sca.y = 420;

					//���W�Ƒ傫���X�V
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//HP�X�v���C�g�ƃ^�C�������Ă���
			case 7:
				if (true)
				{
					//�^�C�}�[�����Ă���
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HP�X�v���C�g�����Ă���
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					m_HpPos += Vector3(0.3f, -2.5f, 0) * 3;
					m_TimePos += Vector3(-4, -4, 0) * 3;

					//����t���O
					bool flg1 = false;
					bool flg2 = false;

					if (m_HpTargetPos.x < m_HpPos.x && m_HpTargetPos.y > m_HpPos.y)
					{
						flg1 = true;
					}
					else
					{
						hpptr->MoveSprtieS(Vector3(0.3f, -2.5f, 0) * 3);
					}

					if (m_TimeTargetPos.x > m_TimePos.x && m_TimeTargetPos.y > m_TimePos.y)
					{
						flg2 = true;
					}
					else
					{
						timeptr->MovePos(Vector3(-4, -4, 0) * 3);
					}

					if (flg1 && flg2)
					{
						//��ԕύX
						m_State = 8;
					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 71;
					}

					//�f�o�b�O-----------------------
					//wstring txt = Util::FloatToWStr(m_TimePos.x) + L":"
					//	+ Util::FloatToWStr(m_TimePos.y) + L":";
					//txt += L"\n";
					//txt += Util::FloatToWStr(m_TimeTargetPos.x) + L":"
					//	+ Util::FloatToWStr(m_TimeTargetPos.y) + L":";
					//m_Debugtxt->SetText(txt);
					//�f�o�b�O-----------------------

				}
				break;
			case 71:
				if (true)
				{
					//�^�C�}�[�����Ă���
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HP�X�v���C�g�����Ă���
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					//�ړ��ʌv�Z
					float HpPosMoveX = m_HpTargetPos.x - m_HpPos.x;
					float HpPosMoveY = m_HpTargetPos.y - m_HpPos.y;

					float TimePosMoveX = m_TimeTargetPos.x - m_TimePos.x;
					float TimePosMoveY = m_TimeTargetPos.y - m_TimePos.y;

					//�ړ�
					hpptr->MoveSprtieS(Vector3(HpPosMoveX, HpPosMoveY, 0));
					timeptr->MovePos(Vector3(TimePosMoveX, TimePosMoveY, 0));

					m_State = 8;
				}
				break;
				//���ڏo��
			case 8:
				if (true)
				{
					//HP�̂ق��́~�쐬
					auto batu = GetStage()->AddGameObject<GameObject>();
					auto Transba = batu->AddComponent<Transform>();
					Transba->SetPosition(-5, 50, 0);
					Transba->SetScale(100, 100, 1);
					Transba->SetRotation(0, 0, 0);

					auto Drawba = batu->AddComponent<PCTSpriteDraw>();
					Drawba->SetTextureResource(L"BATU_TX");

					batu->SetDrawLayer(11);
					batu->SetAlphaActive(true);

					//HP�̔{���X�R�A
					auto numhp = GetStage()->AddGameObject<NumberSprite>(500, Vector2(260, 50), Vector2(100, 100), 11);

					//HP�̃X�R�A
					auto numhpscore = GetStage()->AddGameObject<NumberSprite>(0, Vector2(560, 50), Vector2(100, 100), 11);
					m_HpScore = numhpscore;

					//TIME�̃X�R�A
					auto numtimescore = GetStage()->AddGameObject<NumberSprite>(0, Vector2(560, -100), Vector2(100, 100), 11);
					m_TimeScore = numtimescore;

					//��ԕύX
					m_State = 9;

					//�����n
					m_HpAmount = 0;
					m_TimeAmount = 0;

					//�X�R�A�ő�l�ݒ�
					//HP�̒l��[�l*500]
					m_HpScoreTotal = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false)->GetLife() * 500;
					m_TimeScoreTotal = GetStage()->GetSharedGameObject<Timer>(L"Timer", false)->GetTime();
					//Time�̒l�ݒ�B30�b�܂ł͖�������5000
					if (m_TimeScoreTotal <= 30)
					{
						m_TimeScoreTotal = 5000;
					}
					//���Ƃ�200�b�܂�1�b25�_�ŉ��_
					else if (m_TimeScoreTotal <= 200)
					{
						m_TimeScoreTotal = (200 - m_TimeScoreTotal) * 25;
					}
					else
					{
						m_TimeScoreTotal = 0;
					}

					//�g�[�^���X�R�A�v�Z
					m_TotalAmount = 0;
					m_TotalScore = m_HpScoreTotal + m_TimeScoreTotal;
				}
				break;
				//�X�R�A���Z
			case 9:
				if (true)
				{
					//HP�X�R�A���Z
					m_HpAmount += m_HpScoreTotal / 60;
					//TIME�X�R�A���Z
					m_TimeAmount += m_TimeScoreTotal / 60;

					//�ő�l���������̃t���O
					bool flg1 = false;
					bool flg2 = false;
					//HP�̃X�R�A�z���Ă���
					if (m_HpAmount >= m_HpScoreTotal)
					{
						m_HpAmount = m_HpScoreTotal;
						flg1 = true;
					}
					//ITME�̃X�R�A�z���Ă���
					if (m_TimeAmount >= m_TimeScoreTotal)
					{
						m_TimeAmount = m_TimeScoreTotal;
						flg2 = true;
					}
					//HP�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_HpScore)->SetNum(m_HpAmount);
					//TIME�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_TimeScore)->SetNum(m_TimeAmount);


					//HP��TIME�̃X�R�A���ݒ�l�ɓ͂�����
					if (flg1 && flg2)
					{
						m_State = 91;
					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 91;
					}

				}
				break;
			case 91:
				if (true)
				{
					//�X�R�A�ύX
					m_HpAmount = m_HpScoreTotal;
					m_TimeAmount = m_TimeScoreTotal;

					//HP�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_HpScore)->SetNum(m_HpAmount);
					//TIME�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_TimeScore)->SetNum(m_TimeAmount);

					//��ԍX�V
					m_State = 10;

					//Total�X�R�A
					auto numTo = GetStage()->AddGameObject<NumberSprite>(500, Vector2(450, -250), Vector2(100, 100), 11);
					m_TotalScoreSp = numTo;

					//TotalScore���S�쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-200, -250, 0);
					Trans->SetScale(600, 100, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"TOTALSCORE_TX");

					obj->SetDrawLayer(11);
					obj->SetAlphaActive(true);

				}
				break;
				//�g�[�^���X�R�A���Z
			case 10:
				if (true)
				{
					//Total�X�R�A���Z
					m_TotalAmount += m_TotalScore / 60;

					if (m_TotalAmount >= m_TotalScore)
					{
						m_TotalAmount = m_TotalScore;
						//��ԕύX
						m_State = 101;

					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 101;
					}

					//Total�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_TotalScoreSp)->SetNum(m_TotalAmount);

				}
				break;
			case 101:
				if (true)
				{
					//�X�R�A�ύX
					m_TotalAmount = m_TotalScore;

					//�����N�쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1000, 1000, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetDiffuse(Color4(1, 1, 1, 0));
					if (m_TotalScore >= 7000)
					{
						Draw->SetTextureResource(L"RANK_S_TX");
					}
					else if (m_TotalScore >= 5000)
					{
						Draw->SetTextureResource(L"RANK_A_TX");
					}
					else if (m_TotalScore >= 3000)
					{
						Draw->SetTextureResource(L"RANK_B_TX");
					}
					else
					{
						Draw->SetTextureResource(L"RANK_C_TX");
					}

					obj->SetDrawLayer(14);
					obj->SetAlphaActive(true);

					m_RankSp = obj;

					//�����x���Z�b�g
					m_RankAlpha = 0;

					//Total�X�R�A�X�V
					dynamic_pointer_cast<NumberSprite>(m_TotalScoreSp)->SetNum(m_TotalAmount);

					//��ԍX�V
					m_State = 11;
				}
				break;
				//�����N�\��
			case 11:
				if (true)
				{
					//���̉����Ă�
					m_RankAlpha += App::GetApp()->GetElapsedTime();

					//�����N�̑傫��
					Vector3 sca = m_RankSp->GetComponent<Transform>()->GetScale();
					if (m_TotalScore >= 7000)
					{
						sca *= 0.98f;
					}
					else if (m_TotalScore >= 5000)
					{
						sca *= 0.96f;
					}
					else if (m_TotalScore >= 3000)
					{
						sca *= 0.94f;
					}
					else
					{
						sca *= 0.90f;
					}

					//������x�������Ȃ�����
					if (sca.x < 300)
					{
						m_State = 111;
					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 111;
					}

					//�����x�X�V
					m_RankSp->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_RankAlpha));
					//�傫���X�V
					m_RankSp->GetComponent<Transform>()->SetScale(sca);
				}
				break;
			case 111:
				if (true)
				{

					//�����N�̑傫��
					Vector3 sca = m_RankSp->GetComponent<Transform>()->GetScale();

					//�傫���Œ�
					sca.x = 300;
					sca.y = 300;
					sca.z = 1;
					//��ԕύX
					m_State = 12;

					//���ԃ��Z�b�g
					m_time = 0;

					//�����摜�o��
					auto obj2 = GetStage()->AddGameObject<GameObject>();
					auto Trans2 = obj2->AddComponent<Transform>();
					Trans2->SetPosition(0, 0, 0);
					Trans2->SetScale(1280, 720, 1);
					Trans2->SetRotation(0, 0, 0);

					auto Draw2 = obj2->AddComponent<PCTSpriteDraw>();
					Draw2->SetTextureResource(L"RESULTWHITE_TX");
					Draw2->SetDiffuse(Color4(1, 1, 1, 1));

					obj2->SetDrawLayer(13);
					obj2->SetAlphaActive(true);

					m_White12 = obj2;

					//�����x�ݒ�
					m_BlackAlpha = 1;
					m_RankAlpha = 1;


					//Abe20170622
					//���_�V�[���ɓo�^
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					ScenePtr->SetStageScore(m_TotalScore);
					//Abe20170622

					//�����x�X�V
					m_RankSp->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_RankAlpha));
					//�傫���X�V
					m_RankSp->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//���΂炭�҂�
			case 12:
				if (true)
				{
					m_BlackAlpha += -App::GetApp()->GetElapsedTime() * 2;
					if (m_BlackAlpha < 0)
					{
						m_BlackAlpha = 0;
					}
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_Wait12Time)
					{
						m_State = 121;
						m_time = 0;
					}

					//�X�L�b�v
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 121;
					}


					m_White12->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				break;
			case 121:
				if (true)
				{
					//��ԕύX
					m_State = 13;

					//���������N�̉��ɏo��
					//�Ó]���쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1280, 720, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTBLACK_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(13);
					obj->SetAlphaActive(true);

					m_Black = obj;

					m_BlackAlpha = 0;

					m_Black12 = obj;

					m_White12->SetDrawActive(false);

					m_White12->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				}
				break;
				//�����������ɂ��ă����N����Ɉړ�
			case 13:
				if (true)
				{
					//�Ö�
					if (m_BlackAlpha < 0.6f)
					{
						m_BlackAlpha += App::GetApp()->GetElapsedTime() * 2;
						m_Black12->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					}
					else
					{
						m_BlackAlpha = 0.6f;
						m_Black12->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
					}

					//�ړ�
					Vector3 pos = m_RankSp->GetComponent<Transform>()->GetPosition();
					pos.y += 300 * App::GetApp()->GetElapsedTime();
					if (pos.y > 150)
					{
						//�����Œ�
						pos.y = 150;

						//��Ԉړ�
						m_State = 14;
					}
					m_RankSp->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//�I�����o��
			case 14:
				if (true)
				{
					//��ԕύX
					m_State = 15;

					//�I�����쐬
					//���̃X�e�[�W��
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-400, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTNEXTSTAGELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//���g���C
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-150, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTRETRYLOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//�X�e�Z��
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(150, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTSTASELELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//�^�C�g��
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(450, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTTITLELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//�J�[�\���쐬------------------------------------
					auto CursorSprite = GetStage()->AddGameObject<GameObject>();
					//���W
					auto CTrans = CursorSprite->AddComponent<Transform>();
					CTrans->SetPosition(-400, -160, 0);
					CTrans->SetScale(180, 50, 1);
					CTrans->SetRotation(0, 0, 0);

					//�`��
					auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
					CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

					//���C���[�ݒ�
					CursorSprite->SetDrawLayer(16);

					//�����x�L����
					CursorSprite->SetAlphaActive(true);

					m_Cursor = CursorSprite;

					//���炷����
					m_SelectSe = ObjectFactory::Create<MultiAudioObject>();
					m_SelectSe->AddAudioResource(L"CURSORMOVE_SE");

				}
				break;
				//�I��
			case 15:
				if (true)
				{
					//�R���g���[���擾
					if (CntlVec[0].bConnected)
					{
						//�J�[�\������������
						if (m_MoveFlg)
						{
							//�E
							if (CntlVec[0].fThumbLX > 0.5f)
							{
								m_SelectNum++;
								if (m_SelectNum > 3)
								{
									m_SelectNum = 0;
								}
								//������t���O�~�߂�
								m_MoveFlg = false;

							}
							//��
							if (CntlVec[0].fThumbLX < -0.5f)
							{
								m_SelectNum--;
								if (m_SelectNum < 0)
								{
									m_SelectNum = 3;
								}
								//������t���O�~�߂�
								m_MoveFlg = false;
							}

							if (!m_MoveFlg)
							{
								//���炷
								m_SelectSe->Start(L"CURSORMOVE_SE", 0.5f);

								//�ړ�
								switch (m_SelectNum)
								{
								case 0:
									m_Cursor->GetComponent<Transform>()->SetPosition(-400, -160, 0);
									m_Cursor->GetComponent<Transform>()->SetScale(180, 50, 1);
									break;
								case 1:
									m_Cursor->GetComponent<Transform>()->SetPosition(-150, -160, 0);
									m_Cursor->GetComponent<Transform>()->SetScale(180, 50, 1);
									break;
								case 2:
									m_Cursor->GetComponent<Transform>()->SetPosition(150, -160, 0);
									m_Cursor->GetComponent<Transform>()->SetScale(220, 50, 1);
									break;
								case 3:
									m_Cursor->GetComponent<Transform>()->SetPosition(450, -160, 0);
									m_Cursor->GetComponent<Transform>()->SetScale(180, 50, 1);
									break;
								default:
									break;
								}
							}
						}
						//�����Ɠ����Ȃ��悤��
						else
						{
							if (abs(CntlVec[0].fThumbLX) < 0.5f && abs(CntlVec[0].fThumbLX) > -0.5f)
							{
								m_MoveFlg = true;
							}
						}

						//A�{�^�������ꂽ��ړ�
						if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
						{
							//��ԕύX
							m_State = 16;

							//���炷
							m_KetteiSe = ObjectFactory::Create<MultiAudioObject>();
							m_KetteiSe->AddAudioResource(L"DECIDE_SE");
							m_KetteiSe->Start(L"DECIDE_SE", 0.5f);

							//�؂�ւ����o
							auto ob = GetStage()->AddGameObject<SceneChangeSS>();
							ob->OnAnim();
							ob->SetLayer(17);
						}
					}
				}
				break;
				//�J��
			case 16:
				if (true)
				{
					switch (m_SelectNum)
					{
						//���̃X�e�[�W��
					case 0:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							int num = ScenePtr->GetStageNum();
							num++;
							//�X�e�[�W�ԍ����Ƃɑ傫���ς���
							if (num <= 4)
							{
								ScenePtr->SetStageNumAndStageSize(num, Vector2(25, 25));
							}
							else if (num > 4 && num <= 12)
							{
								ScenePtr->SetStageNumAndStageSize(num, Vector2(50, 50));
							}
							else if (num > 12)
							{
								ScenePtr->SetStageNumAndStageSize(num, Vector2(75, 75));
							}
							//CSV�ɐݒ�
							ScenePtr->SetCsvStageNum(Util::IntToWStr(num));
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//���g���C
					case 1:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//�X�e�Z��
					case 2:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
						}
						break;
						//�^�C�g��
					case 3:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
						}
						break;
					}

					//��ԕύX
					m_State = 17;
				}
				break;
				//�ҋ@
			case 17:
				break;
			}
		}



		//�`���[�g���A���p
#pragma region �`���[�g���A���p
		if (m_TutorialFlg)
		{
			switch (m_State)
			{
				//���΂炭�҂�
			case 0:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_1WaitTime)
					{
						//��ԕύX
						m_State = 1;

						//���ԏ�����
						m_time = 0;

						//�J������~
						dynamic_pointer_cast<TutorialScene>(GetStage())->CameraStop();

						GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->DontMove();
					}
				}
				break;
				//�J�������߂Â���{�L�������߂Â���
			case 1:
				if (true)
				{
					//�J���������Ă�t���O
					bool flg1 = false;
					//�J�������ړ����ĖڕW�n�_�ɋ߂�������
					if (dynamic_pointer_cast<TutorialScene>(GetStage())->ResultCamera(m_centerPos))
					{
						flg1 = true;
					}

					//�v���C���[��ړI�n�Ɉړ�
					Vector3 ppos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 ppos2 = m_Player2->GetComponent<Transform>()->GetPosition();
					Vector3 pdir1 = m_Player1TargetPos - ppos1;
					Vector3 pdir2 = m_Player2TargetPos - ppos2;
					pdir1 /= 10;
					pdir2 /= 10;
					ppos1 += pdir1;
					ppos2 += pdir2;

					bool flg2 = false;
					bool flg3 = false;

					//�߂���Δ���p�̃t���O��true�ɂ��A������΋߂Â���
					if (abs(m_Player1TargetPos.x - ppos1.x) + abs(m_Player1TargetPos.y - ppos1.y) + abs(m_Player1TargetPos.z - ppos1.z) < 0.1f)
					{
						flg2 = true;
					}
					else
					{
						m_Player1->GetComponent<Transform>()->SetPosition(ppos1);
					}
					if (abs(m_Player2TargetPos.x - ppos2.x) + abs(m_Player2TargetPos.y - ppos2.y) + abs(m_Player2TargetPos.z - ppos2.z) < 0.1f)
					{
						flg3 = true;
					}
					else
					{
						m_Player2->GetComponent<Transform>()->SetPosition(ppos2);
					}


					if (flg1 && flg2 && flg3)
					{
						//��ԕύX
						m_State = 2;
					}
				}
				break;
				//�L��������O�Ɍ�������
			case 2:
				if (true)
				{
					//��]
					Vector3 rot1 = m_Player1->GetComponent<Transform>()->GetRotation();
					Vector3 rot2 = m_Player2->GetComponent<Transform>()->GetRotation();
					rot1.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
					rot2.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();

					//�Ȃ񂩕ςȂƂ��ňႤ������]���邩�炻��~�߂�
					rot1 = Vector3(0, rot1.y, 0);
					rot2 = Vector3(0, rot2.y, 0);
					//��̎�O��1.6���炢
					if (rot1.y >= 1.4f && rot1.y <= 1.8f)
					{
						//��]�Œ�
						rot1.y = 90 * 3.14159265f / 180;
						rot2.y = 90 * 3.14159265f / 180;

						//��ԕύX
						m_State = 3;
						//���˂�͐ݒ�
						float m_HopPower = 10;

						//���˂�t���O�I��
						m_HopFlg = true;

					}
					m_Player1->GetComponent<Transform>()->SetRotation(rot1);
					m_Player2->GetComponent<Transform>()->SetRotation(rot2);

				}
				break;
				//���˂�
			case 3:
				if (true)
				{
					//��ԕύX
					m_State = 4;

					//�~�b�V�����R���v���[�g�����쐬
					//�Ó]���쐬
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-2000, 0, 0);
					Trans->SetScale(1500, 600, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"MISSIONCOMPLETE_TX");

					obj->SetDrawLayer(11);
					obj->SetAlphaActive(true);

					m_MissCompLogo = obj;

				}
				break;
				//�~�b�V�����R���v���[�g����������o��
			case 4:
				if (true)
				{
					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();

					//���S�܂ŗ�����
					if (pos.x > 0)
					{
						//�Ó]���쐬
						auto obj = GetStage()->AddGameObject<GameObject>();
						auto Trans = obj->AddComponent<Transform>();
						Trans->SetPosition(0, 0, 0);
						Trans->SetScale(1280, 720, 1);
						Trans->SetRotation(0, 0, 0);

						auto Draw = obj->AddComponent<PCTSpriteDraw>();
						Draw->SetTextureResource(L"RESULTBLACK_TX");
						Draw->SetDiffuse(Color4(1, 1, 1, 0));

						obj->SetDrawLayer(10);
						obj->SetAlphaActive(true);

						m_Black = obj;

						m_BlackAlpha = 0;

						//���W�Œ�
						pos.x = 0;

						//��ԕύX
						m_State = 5;
					}

					//���W�ړ�
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//������ƈÂ�����
			case 5:
				if (true)
				{
					if (m_BlackAlpha < 0.5f)
					{
						m_BlackAlpha += App::GetApp()->GetElapsedTime();
					}
					else
					{
						//�����x�Œ�
						m_BlackAlpha = 0.5f;
						//��ԕύX
						m_State = 6;
					}
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				}
				break;
				//�~�b�V�����R���v���[�g���������ď�Ɉړ�
			case 6:
				if (true)
				{
					//�~�b�V�����R���v���[�g�̍��W�����Ă���
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					if (pos.y < 200)
					{
						pos.y += 600 * App::GetApp()->GetElapsedTime();
					}

					//�傫�������Ă���
					Vector3 sca = m_MissCompLogo->GetComponent<Transform>()->GetScale();
					if (sca.x > 1200)
					{
						sca.x *= 0.95f;
						sca.y *= 0.95f;
					}

					if (pos.y > 200 && sca.x <= 1200)
					{
						//��ԕύX
						m_State = 7;
						m_time = 0;
					}

					//���W�Ƒ傫���X�V
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//���΂炭�҂�
			case 7:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > 2.0f)
					{
						m_State = 8;
						//�؂�ւ����o
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(17);
					}
				}
				break;
				//�X�e�Z���Ɉړ�
			case 8:
				if (true)
				{
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					App::GetApp()->GetScene<Scene>()->SetBgmflg(false);
					PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");

				}
				break;
			}
		}
#pragma endregion

		if (!m_TutorialFlg)
		{
			//���˂�t���O�������Ă���҂��҂��
			if (m_HopFlg)
			{
				if (m_HopTime > m_1WaitTime)
				{
					//�L�����̍��W�����Ă���
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//�ʒu������
					pos1.y += m_HopPower * App::GetApp()->GetElapsedTime();
					pos2.y += m_HopPower *App::GetApp()->GetElapsedTime();
					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//���˂�͂�����������
					m_HopPower += -9.8f * App::GetApp()->GetElapsedTime() * 3;
					//������x��������������������˂�͂�������
					if (pos1.y < 1.0f)
					{
						//���˂�͉�����
						m_HopPower = 10;
						//�v�Z�p�ҋ@���Ԃ����Z�b�g
						m_HopTime = 0;

						pos1.y = 1.1f;
						pos2.y = 1.1f;
						m_Player1->GetComponent<Transform>()->SetPosition(pos1);
						m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					}
				}
				else
				{
					m_HopTime += App::GetApp()->GetElapsedTime();
				}
			}
		}
	}
	//Abe20170531
	
	//Abe20170605
	//--------------------------------------------------------------------------------------
	//	�|�[�Y
	//--------------------------------------------------------------------------------------
	void PauseMenu::OnCreate()
	{
		//-----����------
		//�Q�[���ɖ߂�
		auto togame = GetStage()->AddGameObject<GameObject>();
		auto TransTG = togame->AddComponent<Transform>();
		TransTG->SetPosition(-350, 100, 0);
		TransTG->SetScale(400, 150, 1);
		TransTG->SetRotation(0, 0, 0);

		auto DrawTG = togame->AddComponent<PCTSpriteDraw>();
		DrawTG->SetTextureResource(L"PAUSE_TOGAME_TX");

		togame->SetAlphaActive(true);
		togame->SetDrawLayer(7);
		togame->SetDrawActive(false);

		m_ToGame = togame;
		//���g���C
		auto retry = GetStage()->AddGameObject<GameObject>();
		auto TransRT = retry->AddComponent<Transform>();
		TransRT->SetPosition(-450, 0, 0);
		TransRT->SetScale(400, 150, 1);
		TransRT->SetRotation(0, 0, 0);

		auto DrawRT = retry->AddComponent<PCTSpriteDraw>();
		DrawRT->SetTextureResource(L"PAUSE_RETRY_TX");

		retry->SetAlphaActive(true);
		retry->SetDrawLayer(7);
		retry->SetDrawActive(false);

		m_ToRetry = retry;
		//�X�e�Z��
		auto stesele = GetStage()->AddGameObject<GameObject>();
		auto TransSS = stesele->AddComponent<Transform>();
		TransSS->SetPosition(-450, -100, 0);
		TransSS->SetScale(400, 150, 1);
		TransSS->SetRotation(0, 0, 0);

		auto DrawSS = stesele->AddComponent<PCTSpriteDraw>();
		DrawSS->SetTextureResource(L"PAUSE_TOSELECT_TX");

		stesele->SetAlphaActive(true);
		stesele->SetDrawLayer(7);
		stesele->SetDrawActive(false);

		m_ToSteSele = stesele;
		//�^�C�g��
		auto title = GetStage()->AddGameObject<GameObject>();
		auto TransTI = title->AddComponent<Transform>();
		TransTI->SetPosition(-450, -200, 0);
		TransTI->SetScale(400, 150, 1);
		TransTI->SetRotation(0, 0, 0);

		auto DrawTI = title->AddComponent<PCTSpriteDraw>();
		DrawTI->SetTextureResource(L"PAUSE_TOTITLE_TX");

		title->SetAlphaActive(true);
		title->SetDrawLayer(7);
		title->SetDrawActive(false);

		m_ToTitle = title;
		//�G�l�~�[�̐�
		auto enemys = GetStage()->AddGameObject<GameObject>();
		auto TransEN = enemys->AddComponent<Transform>();
		TransEN->SetPosition(250, -50, 0);
		TransEN->SetScale(780, 500, 1);
		TransEN->SetRotation(0, 0, 0);

		auto DrawEN = enemys->AddComponent<PCTSpriteDraw>();
		DrawEN->SetTextureResource(L"PAUSE_ENEMYS_TX");

		enemys->SetAlphaActive(true);
		enemys->SetDrawLayer(7);
		enemys->SetDrawActive(false);

		m_EnemyS = enemys;

		//����
		auto num1 = GetStage()->AddGameObject<NumberSprite>(0, Vector2(220, 90), Vector2(100, 100), 8);
		num1->SetLayer(8);
		num1->SetNumDraw(false);
		m_TackleSp = num1;
		
		auto num2 = GetStage()->AddGameObject<NumberSprite>(0, Vector2(520, 90), Vector2(100, 100), 8);
		num2->SetLayer(8);
		num2->SetNumDraw(false);
		m_ShotSp = num2;

		auto num3 = GetStage()->AddGameObject<NumberSprite>(0, Vector2(220, -160), Vector2(100, 100), 8);
		num3->SetLayer(8);
		num3->SetNumDraw(false);
		m_TerepoSp = num3;

		auto num4 = GetStage()->AddGameObject<NumberSprite>(0, Vector2(520, -160), Vector2(100, 100), 8);
		num4->SetLayer(8);
		num4->SetNumDraw(false);
		m_BombSp = num4;

		//�|�[�Y���S
		auto pauselogo = GetStage()->AddGameObject<GameObject>();
		auto TransPL = pauselogo->AddComponent<Transform>();
		TransPL->SetPosition(0, 280, 0);
		TransPL->SetScale(800, 280, 1);
		TransPL->SetRotation(0, 0, 0);

		auto DrawPL = pauselogo->AddComponent<PCTSpriteDraw>();
		DrawPL->SetTextureResource(L"PAUSE_LOGO_TX");

		pauselogo->SetAlphaActive(true);
		pauselogo->SetDrawLayer(7);
		pauselogo->SetDrawActive(false);

		m_PauseLogo = pauselogo;
		//�Ó]
		auto black = GetStage()->AddGameObject<GameObject>();
		auto TransB = black->AddComponent<Transform>();
		TransB->SetPosition(0, 0, 0);
		TransB->SetScale(1280, 720, 1);
		TransB->SetRotation(0, 0, 0);

		auto DrawB = black->AddComponent<PCTSpriteDraw>();
		DrawB->SetTextureResource(L"PAUSE_BLACK_TX");
		DrawB->SetDiffuse(Color4(1, 1, 1, 0.5f));

		black->SetAlphaActive(true);
		black->SetDrawLayer(6);
		black->SetDrawActive(false);

		m_Black = black;

		//�N���o�O�C���p
		m_StartPushFlg = true;

		//�A�b�v�f�[�g��~
		SetUpdateActive(false);
	}

	void PauseMenu::OnUpdate()
	{
		//�R���g���[���擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�J�[�\������������
			if (m_MoveFlg)
			{
				//��
				if (CntlVec[0].fThumbLY < -0.5f)
				{
					m_SelectNum++;
					if (m_SelectNum > 3)
					{
						m_SelectNum = 0;
					}
					//������t���O�~�߂�
					m_MoveFlg = false;

				}
				//��
				if (CntlVec[0].fThumbLY > 0.5f)
				{
					m_SelectNum--;
					if (m_SelectNum < 0)
					{
						m_SelectNum = 3;
					}
					//������t���O�~�߂�
					m_MoveFlg = false;
				}

				if (!m_MoveFlg)
				{
					//�ړ�
					switch (m_SelectNum)
					{
						//�Q�[���ɖ߂�
					case 0:
						m_ToGame->GetComponent<Transform>()->SetPosition(-350, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//���g���C
					case 1:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-350, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//�X�e�Z��
					case 2:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-350, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//�^�C�g��
					case 3:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-350, -200, 0);
						break;
					}
				}

			}
			//�����Ɠ����Ȃ��悤��
			else
			{
				if (abs(CntlVec[0].fThumbLY) < 0.5f && abs(CntlVec[0].fThumbLY) > -0.5f)
				{
					m_MoveFlg = true;
				}
			}

			//�{�^�������ꂽ��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				switch (m_SelectNum)
				{
					//�߂�
				case 0:
					Close();
					break;
					//���g���C
				case 1:
					if (true)
					{
						//�؂�ւ����o
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(10);

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
					}
					break;
					//�X�e�Z��
				case 2:
					if (true)
					{
						//�؂�ւ����o
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(10);

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
					}
					break;
					//�^�C�g��
				case 3:
					if (true)
					{				
						//�؂�ւ����o
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(10);

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
					}
					break;
				}
			}

		}
	}

	void PauseMenu::Open()
	{
		//�|�[�Y�I�u�W�F�\��
		m_PauseLogo->SetDrawActive(true);
		m_ToGame->SetDrawActive(true);
		m_ToRetry->SetDrawActive(true);
		m_ToSteSele->SetDrawActive(true);
		m_ToTitle->SetDrawActive(true);
		m_EnemyS->SetDrawActive(true);
		m_Black->SetDrawActive(true);
		dynamic_pointer_cast<NumberSprite>(m_TackleSp)->SetNumDraw(true);
		dynamic_pointer_cast<NumberSprite>(m_ShotSp)->SetNumDraw(true);
		dynamic_pointer_cast<NumberSprite>(m_TerepoSp)->SetNumDraw(true);
		dynamic_pointer_cast<NumberSprite>(m_BombSp)->SetNumDraw(true);

		//�A�b�v�f�[�g�N��
		SetUpdateActive(true);

		//�S���̓����I�u�W�F�N�g���~�߂�
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//�A�^������~�߂�
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(false);
		}
		//�v���C���[���~�߂�
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(false);
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(false);

		//�v���C���[�Ǘ����Ă��~�߂�
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

		//�S���~�߂�
		for (auto obj : ColGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				if (ptr->GetDrawActive())
				{
					ptr->SetUpdateActive(false);
				}
			}
		}
		for (auto obj : EnemyGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				if (ptr->GetDrawActive())
				{
					ptr->SetUpdateActive(false);
				}
			}
		}
		for (auto obj : BombGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : SearchChildGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				if (ptr->GetDrawActive())
				{
					ptr->SetUpdateActive(false);
				}
			}
		}
		for (auto obj : UgokuGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				if (ptr->GetDrawActive())
				{
					ptr->SetUpdateActive(false);
				}
			}
		}

		//�G�̐��擾
		//�܂�������
		m_TackleCount = 0;
		m_ShotCount = 0;
		m_TereportCount = 0;
		m_BombCount = 0;
		
		//Vector4 EnemyCount = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager",false)->GetEnemyCount();
		Vector4 EnemyCountS;
		for (auto obj : GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector())
		{

			if (dynamic_pointer_cast<TackleEnemy>(obj.lock()))
			{
				if (dynamic_pointer_cast<GameObject>(obj.lock())->GetDrawActive())
				{
					EnemyCountS.x++;
				}
			}
			if (dynamic_pointer_cast<ShotEnemy>(obj.lock()))
			{
				if (dynamic_pointer_cast<GameObject>(obj.lock())->GetDrawActive())
				{
					EnemyCountS.y++;
				}
			}
			if (dynamic_pointer_cast<TeleportEnemy>(obj.lock()))
			{
				if (dynamic_pointer_cast<GameObject>(obj.lock())->GetDrawActive())
				{
					EnemyCountS.z++;
				}
			}
			if (dynamic_pointer_cast<BombEnemy>(obj.lock()))
			{
				if (dynamic_pointer_cast<GameObject>(obj.lock())->GetDrawActive())
				{
					EnemyCountS.w++;
				}
			}

		}

		m_TackleCount = EnemyCountS.x;
		m_ShotCount = EnemyCountS.y;
		m_TereportCount = EnemyCountS.z;
		m_BombCount = EnemyCountS.w;

		//����(������)�ݒ�
		dynamic_pointer_cast<NumberSprite>(m_TackleSp)->SetNum(m_TackleCount);
		dynamic_pointer_cast<NumberSprite>(m_ShotSp)->SetNum(m_ShotCount);
		dynamic_pointer_cast<NumberSprite>(m_TerepoSp)->SetNum(m_TereportCount);
		dynamic_pointer_cast<NumberSprite>(m_BombSp)->SetNum(m_BombCount);

	}

	void PauseMenu::Close()
	{
		//�|�[�Y�I�u�W�F��\��
		m_PauseLogo->SetDrawActive(false);
		m_ToGame->SetDrawActive(false);
		m_ToRetry->SetDrawActive(false);
		m_ToSteSele->SetDrawActive(false);
		m_ToTitle->SetDrawActive(false);
		m_EnemyS->SetDrawActive(false);
		m_Black->SetDrawActive(false);
		dynamic_pointer_cast<NumberSprite>(m_TackleSp)->SetNumDraw(false);
		dynamic_pointer_cast<NumberSprite>(m_ShotSp)->SetNumDraw(false);
		dynamic_pointer_cast<NumberSprite>(m_TerepoSp)->SetNumDraw(false);
		dynamic_pointer_cast<NumberSprite>(m_BombSp)->SetNumDraw(false);

		//�A�b�v�f�[�g��~
		SetUpdateActive(false);

		//�ʒu�X�V
		m_ToGame->GetComponent<Transform>()->SetPosition(-350, 100, 0);
		m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
		m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
		m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
		//�I��ԍ����Z�b�g
		m_SelectNum = 0;

		//�S���̓����I�u�W�F�N�g�𓮂���
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//�A�^�����蓮����
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(true);
		}

		//�v���C���[�𓮂���
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(true);
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(true);

		//�v���C���[�Ǘ����Ă�������
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(true);

		//�S��������
		for (auto obj : ColGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(true);
			}
		}
		for (auto obj : EnemyGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(true);
			}
		}
		for (auto obj : BombGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(false);
			}
		}
		for (auto obj : SearchChildGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(true);
			}
		}
		for (auto obj : UgokuGroup)
		{
			auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
			if (ptr)
			{
				ptr->SetUpdateActive(true);
			}
		}

	}
	//Abe20170605

	//Abe20170609
	//************************************
	//�@�v���C���[ABUTTON�b���ĂԂ��������̃G�t�F�N�g
	//	�������܁[�[�[�[�[�[��
	//************************************

	void ButukariEf::OnCreate()
	{
		auto Trans = AddComponent<Transform>();
		Trans->SetPosition(0, 0, 0);
		Trans->SetScale(3, 3, 3);
		Trans->SetRotation(45 * 3.14159265f / 180, 0, 0);

		auto Draw = AddComponent<PCTStaticDraw>();
		//Draw->SetMeshResource(L"DEFAULT_SQUARE");
		Draw->SetTextureResource(L"BUTUKARIEF_TX");

		//��������
		SetAlphaActive(true);
		SetDrawActive(false);

		SetDrawLayer(5);
		//�摜����

		//�X�v���C�g�̐����Z�b�g
		m_SpriteNum = -1;
		//3x3
		//�܂���
		Vector2 TexSize = Vector2(3, 3);

		//�摜�쐬-------------------------
		for (int i = 0; i < TexSize.x * TexSize.y; i++)
		{
			m_SpriteNum++;
			//���_�z��
			vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV�l�̕ύX
			float fromX = (i % (int)(TexSize.x)) / TexSize.x;
			float toX = fromX + (1.0f / TexSize.x);
			float fromY = (int)(i / TexSize.x) / TexSize.y;
			float toY = fromY + (1.0f / TexSize.y);
			//���㒸�_
			vertices[0].textureCoordinate = Vector2(fromX, fromY);
			//�E�㒸�_
			vertices[1].textureCoordinate = Vector2(toX, fromY);
			//�������_
			vertices[2].textureCoordinate = Vector2(fromX, toY);
			//�E�����_
			vertices[3].textureCoordinate = Vector2(toX, toY);
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
			m_SpriteS.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//�摜�쐬-------------------------
		Draw->SetMeshResource(m_SpriteS[0]);

	}
	void ButukariEf::OnUpdate()
	{
		//�摜�J��
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_IntervalTime)
		{
			m_time = 0;
			GetComponent<PCTStaticDraw>()->SetMeshResource(m_SpriteS[m_NowSpriteNum++]);

			//������������葽��������
			if (m_NowSpriteNum > m_SpriteNum)
			{
				m_NowSpriteNum = 0;
				SetUpdateActive(false);
				SetDrawActive(false);

				//���ƈʒu����
				GetComponent<Transform>()->SetPosition(0, -10, 0);

			}
		}
	}

	void ButukariEf::SetPosScaActive(Vector3 pos , Vector3 sca)
	{
		SetDrawActive(true);
		SetUpdateActive(true);

		Vector3 pos2 = pos;
		Vector3 ransca = sca * 10;
		pos2 += Vector3((rand() % (int)(ransca.x * 2) - ransca.x) / 10, (rand() % (int)(ransca.y * 2) - ransca.y) / 10, (rand() % (int)(ransca.z * 2) - ransca.z) / 10);
		Vector3 scale = sca * 10;

		GetComponent<Transform>()->SetPosition(pos2);
		GetComponent<Transform>()->SetScale(scale);

	}

	//************************************
	//�@�n�܂鉉�o
	//************************************
	void StartState::OnCreate()
	{
		//�X�^�[�g���S�쐬
		auto stlogo = GetStage()->AddGameObject<GameObject>();
		auto TransSt = stlogo->AddComponent<Transform>();
		TransSt->SetPosition(0,0,0);
		TransSt->SetRotation(0, 0, 0);
		TransSt->SetScale(30, 16, 1);

		auto DrawSt = stlogo->AddComponent<PCTSpriteDraw>();
		DrawSt->SetTextureResource(L"STARTSTARTLOGO_TX");
		DrawSt->SetDiffuse(Color4(1, 1, 1, 0));
		stlogo->SetDrawLayer(6);
		stlogo->SetAlphaActive(true);

		m_StartLogo = stlogo;

		//�X�e�[�W���S�쐬
		auto stalogo = GetStage()->AddGameObject<GameObject>();
		auto TransSta = stalogo->AddComponent<Transform>();
		TransSta->SetPosition(-800, 200, 0);
		TransSta->SetRotation(0, 0, 0);
		TransSta->SetScale(700, 300, 1);

		auto DrawSta = stalogo->AddComponent<PCTSpriteDraw>();
		DrawSta->SetTextureResource(L"STARTSTAGELOGO_TX");

		stalogo->SetDrawLayer(6);
		stalogo->SetAlphaActive(true);

		m_StageLogo = stalogo;

		//�����쐬
		auto nump = GetStage()->AddGameObject<NumberSprite>(0,Vector2(-600,200),Vector2(100,100) , 7);
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		nump->SetNum(ScenePtr->GetStageNum());
		m_NumSp = nump;
	}

	void StartState::OnUpdate()
	{
		//�����N��
		if (m_Init)
		{
			//Abe20170620
			//�u�[�X�g�؂�
			GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
			GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
			//Abe20170620


			m_Init = false;
			//�S���̓����I�u�W�F�N�g���~�߂�
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
			auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
			auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
			auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
			//�A�^������~�߂�
			auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
			if (colmanptr)
			{
				colmanptr->SetUpdateActive(false);
			}
			//�v���C���[���~�߂�
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(false);
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(false);

			//�v���C���[�Ǘ����Ă��~�߂�
			GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

			//�S���~�߂�
			for (auto obj : ColGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					if (ptr->GetDrawActive())
					{
						ptr->SetUpdateActive(false);
					}
				}
			}
			for (auto obj : EnemyGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					if (ptr->GetDrawActive())
					{
						ptr->SetUpdateActive(false);
					}
				}
			}
			for (auto obj : BombGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					ptr->SetUpdateActive(false);
				}
			}
			for (auto obj : SearchChildGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					if (ptr->GetDrawActive())
					{
						ptr->SetUpdateActive(false);
					}
				}
			}
			for (auto obj : UgokuGroup)
			{
				auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
				if (ptr)
				{
					if (ptr->GetDrawActive())
					{
						ptr->SetUpdateActive(false);
					}
				}
			}

			return;
		}

		//����
		switch (m_State)
		{
			//�E����X�e�[�W�Ɣԍ�����
			case 0:
				if (true)
				{
					//���S
					Vector3 pos = m_StageLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();
					m_StageLogo->GetComponent<Transform>()->SetPosition(pos);

					//����
					m_NumSp->MoveNums(Vector3(1000 * App::GetApp()->GetElapsedTime(), 0, 0));

					if (pos.x > 0)
					{
						m_State = 1;
						m_time = 0;
					}
				}
				break;
				//������Ƒ҂�
			case 1:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > 1.0f)
					{
						m_State = 2;
					}
				}
				break;
				//���S�ɃX�^�[�g���S�o���ē����ɂ��Ă�
			case 2:
				if (true)
				{
					//���̉�
					m_Alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_StartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));
					
					m_StageLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1 - m_Alpha));

					//������
					Vector3 sca = m_StartLogo->GetComponent<Transform>()->GetScale();
					sca *= 1.05f;
					m_StartLogo->GetComponent<Transform>()->SetScale(sca);

					//�����ǂ�����΂�
					m_NumSp->MoveNums(Vector3(0, 2000, 0) * App::GetApp()->GetElapsedTime());
					if (sca.x > 2000)
					{
						m_State = 3;
						m_StageLogo->SetDrawActive(false);
						m_StartLogo->SetDrawActive(false);
						m_NumSp->SetNumDraw(false);
					}
				}
				break;
				//�I��
			case 3:
				if (true)
				{
					m_State = 4;
					//�S���̓����I�u�W�F�N�g�𓮂���
					auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
					auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
					auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
					auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
					auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
					//�A�^�����蓮����
					auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
					if (colmanptr)
					{
						colmanptr->SetUpdateActive(true);
					}

					//�v���C���[�𓮂���
					GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(true);
					GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(true);

					//�v���C���[�Ǘ����Ă�������
					GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", true)->SetUpdateActive(true);

					//�S��������
					for (auto obj : ColGroup)
					{
						auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
						if (ptr)
						{
							if (ptr->GetDrawActive())
							{
								ptr->SetUpdateActive(true);
							}
						}
					}
					for (auto obj : EnemyGroup)
					{
						auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
						if (ptr)
						{
							if (ptr->GetDrawActive())
							{
								ptr->SetUpdateActive(true);
							}
						}
					}
					for (auto obj : BombGroup)
					{
						auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
						if (ptr)
						{
							ptr->SetUpdateActive(false);
						}
					}
					for (auto obj : SearchChildGroup)
					{
						auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
						if (ptr)
						{
							if (ptr->GetDrawActive())
							{
								ptr->SetUpdateActive(true);
							}
						}
					}
					for (auto obj : UgokuGroup)
					{
						auto ptr = dynamic_pointer_cast<GameObject>(obj.lock());
						if (ptr)
						{
							if (ptr->GetDrawActive())
							{
								ptr->SetUpdateActive(true);
							}
						}
					}

				}

				SetUpdateActive(false);
				break;
		}

	}
	//Abe20170609


	//Abe20170620
	//**************************************************************************************
	//	����
	//�@����Ƀv���C���[�����ăP�c�ɕ��˂���
	//**************************************************************************************
	void KetsuHunsya::OnCreate()
	{
		//�ꉞ������
		m_states = "Stop";

		//�p�����[�^----
		//������
		m_Amount = 2;
		//�������o
		m_intervaltime = 0.05f;
		//�v�Z�p
		m_time = 0;
		//�X�s�[�h
		m_Speed = 3;
		//�傫��
		m_Size = 0.5f;
		//--------------

		//�X�N�G�A
		m_SquareS.clear();
		//�ړ����x
		m_Velocity.clear();

		//�ꉞ
		AddComponent<Transform>();

		////�f�o�b�O��������
		//m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		//m_Debugtxt->SetLayer(10);
		////�F���ɕύX
		//m_Debugtxt->SetColor(Vector3(0, 0, 0));
		////�傫���ύX
		//m_Debugtxt->SetScaleTxt(40);

	}

	void KetsuHunsya::OnUpdate()
	{
		//�ړ�
		UpdateSquareS();

		
		//�~�߂���
		if (m_states == "Stop")
		{

		}
		else
		{
			//���Ԍv��
			m_time += App::GetApp()->GetElapsedTime();

			//�������邩
			bool CreFlg = false;
			//������
			float CreAmount = 0;
			//�T�C�Y
			float size = m_Size;
			//�X�s�[�h
			float speed = m_Speed;
			//�ʏ�
			if (m_states == "Normal")
			{
				if (m_time > m_intervaltime)
				{
					//���ԃ��Z�b�g
					m_time = 0;
					//��������t���O�I��
					CreFlg = true;
					//�������ݒ�
					CreAmount = m_Amount;
					
				}
			}

			//�u�[�X�g
			if (m_states == "Boost")
			{
				//���Ԕ���
				if (m_time > m_intervaltime * 0.2f)
				{
					//���ԃ��Z�b�g
					m_time = 0;
					//��������t���O�I��
					CreFlg = true;
					//�������ݒ�
					CreAmount = m_Amount * 2;
					size *= 2.0f;
					speed *= 3.0f;
				}
			}

			//����
			if (CreFlg)
			{
				Vector3 pos = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetPosition();
				//���傢��
				pos.y += 0.3f;
				for (int i = 0; i < CreAmount; i)
				{
					int count = 0;
					for (auto obj : m_SquareS)
					{
						if (!obj->GetDrawActive())
						{
							i++;

							//���x�ݒ�
							float angle = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetRotation().y;
							if (angle == 0 || angle == 90 || angle == 180 || angle == 270)
							{
								angle += 1 * 3.14159265f / 180;
							}
							//�P�c�ɏo���̂Ŋp�x���]���Ȃ��Ƃ����ǌ�����t�ɂȂ��Ă�̂ł��̂܂܎g��
							//�Ǝv�������ǂȂ񂾂���
							angle += 180 * 3.14159265f / 180;
							angle *= -1;
							Vector3 vel = Vector3(cos(angle), 0, sin(angle)) * speed;

							//���傢�����_����
							//�u������ -1.0�`-1.0
							Vector3 randvec3 = Vector3((rand() % 20) - 10, (rand() % 10) - 5, (rand() % 20) - 10) / 10;
							//���₷
							if (m_states == "Boost")
							{
								randvec3 = Vector3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5) / 10;
							}
							vel += randvec3 * speed;

							m_Velocity[count] = vel;

							//�o���đ傫���ƈʒu�ݒ�
							m_SquareS[count]->SetDrawActive(true);
							Vector3 pos2 = Vector3(cos(angle) + ((rand() % 100) - 50) / 100, 0, sin(angle) + ((rand() % 100) - 50) / 100);
							m_SquareS[count]->GetComponent<Transform>()->SetPosition(pos + pos2);
							m_SquareS[count]->GetComponent<Transform>()->SetScale(size, size, size);

							continue;
						}
						count++;
					}


					//���x�ݒ�
					float angle = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetRotation().y;
					if (angle == 0 || angle == 90 || angle == 180 || angle == 270)
					{
						angle += 1 * 3.14159265f / 180;
					}
					//�P�c�ɏo���̂Ŋp�x���]���Ȃ��Ƃ����ǌ�����t�ɂȂ��Ă�̂ł��̂܂܎g��
					//�Ǝv�������ǂȂ񂾂���
					angle += 180 * 3.14159265f / 180;
					angle *= -1;
					Vector3 vel = Vector3(cos(angle), 0, sin(angle)) * speed;

					//���傢�����_����
					//�u������ -1.0�`-1.0
					Vector3 randvec3 = Vector3((rand() % 20) - 10, (rand() % 10) - 5, (rand() % 20) - 10) / 10;
					vel += randvec3 * speed;

					m_Velocity.push_back(vel);


					//����
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Vector3 pos2 = Vector3(cos(angle) + ((rand() % 100) - 50) / 100, 0, sin(angle) + ((rand() % 100) - 50) / 100);
					Trans->SetPosition(pos + pos2);
					Trans->SetScale(size, size, size);
					Trans->SetRotation(30 * 3.14159265f / 180, 0, 0);

					auto Draw = obj->AddComponent<PNTStaticDraw>();
					Draw->SetTextureResource(L"BOOST_TX");
					Draw->SetMeshResource(L"DEFAULT_SQUARE");

					obj->SetDrawLayer(5);
					obj->SetAlphaActive(true);

					m_SquareS.push_back(obj);

					i++;

				}
			}
		}
	}

	void KetsuHunsya::UpdateSquareS()
	{
		for (int i = 0; i < m_SquareS.size(); i++)
		{
			if (m_SquareS[i]->GetDrawActive())
			{
				//�ʒu�ړ�
				Vector3 pos = m_SquareS[i]->GetComponent<Transform>()->GetPosition();
				pos += m_Velocity[i] * App::GetApp()->GetElapsedTime();
				m_SquareS[i]->GetComponent<Transform>()->SetPosition(pos);

				//�傫���ύX
				Vector3 sca = m_SquareS[i]->GetComponent<Transform>()->GetScale();
				sca *= 0.93f;
				m_SquareS[i]->GetComponent<Transform>()->SetScale(sca);
				if (sca.x < 0.2f)
				{
					m_SquareS[i]->SetDrawActive(false);
					m_Velocity[i] = Vector3(0, 0, 0);
				}
			}
		}
	}

	void KetsuHunsya::Stop()
	{
		m_states = "Stop";
	}

	void KetsuHunsya::Normal()
	{
		m_states = "Normal";
	}

	void KetsuHunsya::Boost()
	{
		m_states = "Boost";
	}

	//Abe20170620


	//Abe20170622
	//**************************************************************************************
	//	�X�R�A�o��
	//	�Ƃ肠�����J�����Ƃ��ɓǂށA�ۑ��͂��Ȃ��߂�ǂ�
	//�Ƃ肠�������C���[��10����ݒ�
	//**************************************************************************************
	void ScoreDisplay::OnCreate()
	{
		int layer = 10;

		//�����쐬x5
		for (int i = 0; i < 5; i++)
		{
			auto numSp = GetStage()->AddGameObject<NumberSprite>(0, Vector2(430,110 + (i*-75)), Vector2(50,50), layer+1);
			m_NumSps.push_back(numSp);
		}

		//�����N�쐬
		for (int i = 0; i < 5; i++)
		{
			auto objRank = GetStage()->AddGameObject<GameObject>();
			auto objTransRank = objRank->AddComponent<Transform>();
			objTransRank->SetPosition(520, 110 + (i*-75),0);
			objTransRank->SetScale(50, 50, 1);
			objTransRank->SetRotation(0, 0, 0);

			auto objDrawRannk = objRank->AddComponent<PCTSpriteDraw>();
			objDrawRannk->SetTextureResource(L"RANK_S_TX");

			objRank->SetDrawLayer(layer + 1);
			objRank->SetAlphaActive(true);

			m_RankSps.push_back(objRank);
		}

		//���_�쐬
		for (int i = 0; i < 5; i++)
		{
			auto objYoko = GetStage()->AddGameObject<GameObject>();
			auto objTransYoko = objYoko->AddComponent<Transform>();
			objTransYoko->SetPosition(400, 110 + (i*-75), 0);
			objTransYoko->SetScale(300, 150, 1);
			objTransYoko->SetRotation(0, 0, 0);

			auto objDrawYoko = objYoko->AddComponent<PCTSpriteDraw>();
			objDrawYoko->SetTextureResource(L"SCORE_BAR_TX");

			objYoko->SetDrawLayer(layer + 1);
			objYoko->SetAlphaActive(true);

			m_Yokosen.push_back(objYoko);
		}

		//�f�o�b�O��������
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//�F���ɕύX
		m_Debugtxt->SetColor(Vector3(1, 1, 1));
		//�傫���ύX
		m_Debugtxt->SetScaleTxt(40);

		//�����A�߂�ǂ�����֐��Ă�
		Delete();
		
	}

	//�\��(�����̓X�e�[�W�ԍ�)
	void ScoreDisplay::Disp(int stagenum)
	{
		auto SceneP = App::GetApp()->GetScene<Scene>();

		/* �f�o�b�O�\���p
		//�z��
		int arr[5] = { 0 };

		wstring txt;
		for (int i = 0; i < 5; i++)
		{
			arr[i] = SceneP->GetStageScore(stagenum,i);
			txt += Util::IntToWStr(arr[i]) + L"\n";
		}

		m_Debugtxt->SetText(txt);
		*/

		//�\��

		//�����ύX�ƕ\�����f
		for (int i = 0; i < 5; i++)
		{
			int innum = SceneP->GetStageScore(stagenum, i);

			//�X�R�A�ɓ����Ă鐔����0����Ȃ���Γ���ĕ\��
			if (innum != 0)
			{
				auto numP = dynamic_pointer_cast<NumberSprite>(m_NumSps[i]);
				//�����X�V
				numP->SetNum(innum);
				//�\��
				numP->SetNumDraw(true);

				//���ƃ����N���v�Z���ďo��
				//************************
				//TotalMax:10000
				//S:10000 ~7000
				//A:7000 ~5000
				//B:5000 ~3000
				//C:3000 ~0
				//************************* 
				//�܂��\��
				m_RankSps[i]->SetDrawActive(true);

				if (innum >= 7000)
				{
					m_RankSps[i]->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"RANK_S_TX");
				}
				else if (7000 > innum && innum >= 5000)
				{
					m_RankSps[i]->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"RANK_A_TX");
				}
				else if (5000 > innum && innum >= 3000)
				{
					m_RankSps[i]->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"RANK_B_TX");
				}
				else
				{
					m_RankSps[i]->GetComponent<PCTSpriteDraw>()->SetTextureResource(L"RANK_C_TX");
				}

			}
			//0�����Ă�Ή����o��
			else
			{
				m_Yokosen[i]->SetDrawActive(true);
			}
		}
	}

	//����
	void ScoreDisplay::Delete()
	{
		//���낢��\������
		//����
		for (auto obj : m_NumSps)
		{
			dynamic_pointer_cast<NumberSprite>(obj)->SetNumDraw(false);
		}
		//�����N
		for (auto obj : m_RankSps)
		{
			obj->SetDrawActive(false);
		}
		//����
		for (auto obj : m_Yokosen)
		{
			obj->SetDrawActive(false);
		}
	}

	//Abe20170622


}
	//end basecross
