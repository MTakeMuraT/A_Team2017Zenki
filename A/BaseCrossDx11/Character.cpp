/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//むっくん
	//--------------------------------------------------------------------------------------
	///	タイトルのスプライト
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
		PtdDraw->SetDiffuse(Color4(1, 1, 1, 1));

		auto PtrTrans = AddComponent<Transform>();
		PtrTrans->SetScale(m_StartScale.x, m_StartScale.y, 0);
		PtrTrans->SetRotation(0, 0, 0);
		PtrTrans->SetPosition(m_StartPos.x, m_StartPos.y, 0);
		SetAlphaActive(true);
		SetDrawLayer(1);

		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//オーディオリソース登録
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
		//文字列表示
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
	//	シーン遷移のスプライトスタジオ
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

		//アニメーション関連
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(6.5f, 6.5f, 6.5f),
			Vector3(0, 0, 0),
			Vector3(0, 7.5, 0)
			);
		SetToAnimeMatrix(mat);

		//親クラスのCreate
		SS5ssae::OnCreate();
		//秒あたりのフレーム数
		SetFps(60.0f);
		//ループ無効
		SetLooped(false);


		//透明度有効化
		SetAlphaActive(true);
		//描画
		SetDrawActive(true);
		//表示レイヤー
		SetDrawLayer(2);

	}

	void SceneChangeSS::OnUpdate()
	{
		if (m_time < m_LimitTime)
		{
			m_time += App::GetApp()->GetElapsedTime();
			//アニメ―ション更新
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
	//	シーン遷移のスプライトスタジオ
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

		//アニメーション関連
		Matrix4X4 mat;
		mat.DefTransformation(
			Vector3(6.5f, 6.5f, 6.5f),
			Vector3(0, 0, 0),
			Vector3(0, 7.5, 0)
			);
		SetToAnimeMatrix(mat);

		//親クラスのCreate
		SS5ssae::OnCreate();
		//秒あたりのフレーム数
		SetFps(60.0f);
		//ループ無効
		SetLooped(false);


		//透明度有効化
		SetAlphaActive(true);
		//描画
		SetDrawActive(true);
		//表示レイヤー
		SetDrawLayer(2);

	}

	void SceneChangeSSOut::OnUpdate()
	{
		if (m_time < m_LimitTime)
		{
			m_time += App::GetApp()->GetElapsedTime();
			//アニメ―ション更新
			UpdateAnimeTime(App::GetApp()->GetElapsedTime() / 2);
		}
	}

	void SceneChangeSSOut::OnAnim()
	{
		m_ActiveFlg = true;
		ChangeAnimation(L"anime_1");
	}
	//Abe20170526

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



	////////////////////デバック、テスト系/////////////////////////////////////////////////////////

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


	//--------------------------------------------------------------------------------------
	//	class FixdBox : public GameObject;
	//	用途: エネミーテスト用
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
		//衝突判定
		auto Col = AddComponent<CollisionObb>();
		Col->SetFixed(true);
		Col->SetDrawActive(true);
		//描画設定
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_CUBE");
		Draw->SetTextureResource(m_TX_Name);

		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}
	void FixdBox::OnUpdate() {
		//プレイヤーL
		auto PtrPlayer_L = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_L", false);
		auto PtrPlayer_L_Trans = PtrPlayer_L->GetComponent<Transform>();
		Vector3 PtrPlayer_L_Pos = PtrPlayer_L_Trans->GetPosition();
		Vector3 PtrPlayer_L_Scale = PtrPlayer_L_Trans->GetScale();
		Vector3 PtrPlayer_L_ScaleHalf_Vec = Vector3(PtrPlayer_L_Scale.x / 2, PtrPlayer_L_Scale.y / 2, PtrPlayer_L_Scale.z / 2);
		//プレイヤーR
		auto PtrPlayer_R = GetStage()->GetSharedGameObject<Player>(L"GamePlayer_R", false);
		auto PtrPlayer_R_Trans = PtrPlayer_R->GetComponent<Transform>();
		Vector3 PtrPlayer_R_Pos = PtrPlayer_R_Trans->GetPosition();
		Vector3 PtrPlayer_R_Scale = PtrPlayer_R_Trans->GetScale();
		Vector3 PtrPlayer_R_ScaleHalf_Vec = Vector3(PtrPlayer_R_Scale.x / 2, PtrPlayer_R_Scale.y / 2, PtrPlayer_R_Scale.z / 2);
		//自分
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

		wstring InterposeStr(L"挟むフラグ:");
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

	//スティック入力
	void FixdBox::InputStick() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto Rig = GetComponent<Rigidbody>();
		Speed_F = 100.0f;
		Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
		Rig->SetVelocity(Vec_Vec3 * Speed_F);

	}

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


	//--------------------------------------------------------------------------------------
	//	class Enemy01 : public GameObject;
	//	用途: エネミー1　
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
		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
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
		//衝突判定
		auto Col = AddComponent<CollisionObb>();
		//unityでいうとisTrigger・・・、が動かない
		//Col->SetFixed(true);
		Col->SetDrawActive(true);
		//描画設定
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
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
			//飛ばされてたら !m_StanFlgはDamageStateで変更があった場合の対策
			if (!m_SandFlg)
			{
				GetComponent<Rigidbody>()->SetVelocity(m_Vel);
				m_StanTime += -App::GetApp()->GetElapsedTime();
				//減衰
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
			//変な判定消す、これにより挟んだ後引っかからずに移動できる
			GetComponent<CollisionObb>()->SetFixed(true);
		}
	}

	void Enemy01::Release()
	{
		if (m_SandFlg)
		{
			GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
			m_SandFlg = false;
			//飛ばす方向を取る		
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			m_Vel = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);

			m_Vel *= m_VeloPower;
			//変な判定戻す、アタリ判定が復活？する
			GetComponent<CollisionObb>()->SetFixed(false);

		}


	}

	void Enemy01::DamageState()
	{
		//挟まれてたら移動
		if (m_SandFlg)
		{
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			auto Rig = GetComponent<Rigidbody>();
			Vector3 Vec_Vec3 = Vector3(CntlVec[0].fThumbLX, 0, CntlVec[0].fThumbLY);
			Rig->SetVelocity(Vec_Vec3 * 3);
		}

		//時間いったら解除
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
			//飛ばす方向を取る		
			m_Vel = vel;

			m_Vel *= m_VeloPower;
		}

	}
	//Abe20170413

	//Abe20170519
	//--------------------------------------------------------------------------------------
	//	class PauseMenu : public GameObject;
	//	用途: ポーズ
	//--------------------------------------------------------------------------------------
	PauseMenu::PauseMenu(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{}

	void PauseMenu::OnCreate()
	{

	}

	void PauseMenu::OnUpdate()
	{

	}
	//Abe20170519


	//Abe20170418
	//--------------------------------------------------------------------------------------
	//	class NumberSprite : public GameObject;
	//	用途: 数字のスプライト
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

		//桁数える-------------------------------------
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);
		//桁数える-------------------------------------

		//数字の画像作成-------------------------
		for (int i = 0; i < 10; i++)
		{
			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//左上頂点
			vertices[0].textureCoordinate = Vector2(from, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vector2(to, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//メッシュ作成
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//数字の画像作成-------------------------

		//数字スプライト作成---------------------
		//処理用に数字取っておく
		int masternum = m_num;

		//計算結果入れておく用の箱
		vector<int> OutNums;

		//桁分ループ、数字作成
		for (int j = 0; j < m_digit; j++)
		{
			//生成した桁数加算
			m_Constdigit++;

			//上位の桁から数字入れてく
			int num = masternum / pow(10, (m_digit - 1) - j);
			OutNums.push_back(num);
			//計算用の桁の最上位の桁を排除
			masternum = masternum % (int)(pow(10, (m_digit - 1) - j));
		}

		//一個右との差
		float distance = m_scale.x / IntervalNums;

		wstring txt;
		//桁分逆からループ！(0から上位の桁入れてるので)
		//動けばいいよね、バグ起きそうとか言わない
		for (int j = 0; j < m_digit; j++) {


			//生成オブジェ
			auto NumP = GetStage()->AddGameObject<GameObject>();

			//座標設定
			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*count), m_pos.y, 0);
			TranP->SetScale(m_scale.x, m_scale.y, 1);
			TranP->SetRotation(0, 0, 0);

			//大きさ設定
			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[OutNums[(m_digit - 1) - j]]);
			NumP->SetAlphaActive(true);

			//レイヤー設定
			NumP->SetDrawLayer(m_layer);
			//メンバ変数の管理するやつに追加
			m_Numbers.push_back(NumP);

			//カウントアップ
			count++;

		}
		//数字スプライト作成---------------------
	}

	/*
	void NumberSprite::SetPositionVec2(Vector2 pos)
	{
	m_pos = pos;
	//左にずらす一番右が0
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

	//左にずらす一番右が0
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
		//マイナス弾く
		if (m_num >= 0)
		{
			m_num = num;
			//入力された桁持ってくる
			int digit = 0;
			int innum = num;
			do
			{
				innum /= 10;
				digit++;
			} while (innum > 0);

			//処理用に数字取っておく
			int masternum = m_num;
			//計算結果入れておく用の箱
			vector<int> OutNums;

			//桁分ループ、数字作成
			for (int j = 0; j < digit; j++)
			{
				//上位の桁から数字入れてく
				int num = masternum / pow(10, (digit - 1) - j);
				OutNums.push_back(num);
				//計算用の桁の最上位の桁を排除
				masternum = masternum % (int)(pow(10, (digit - 1) - j));
			}


			//入力されたほうが大きかったら
			if (digit > m_digit)
			{
				//追加する分だけループ
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
					//左側に桁追加だけ、数字は後で入れる
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
			//入力されたほうが小さい
			else if (digit < m_digit)
			{
				//添え字ように-1ずらす
				for (int i = m_digit - 1; i > digit - 1; i--)
				{
					m_Numbers[i]->SetDrawActive(false);
				}
			}

			//桁更新
			m_digit = digit;

			//数字入れ替え
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
	//	用途: タイマー
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
		//数字作成
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(m_InitTime, m_InitPos, m_InitScale, m_LayerNum);
		//初期時間入れる
		m_Time = m_InitTime;
	}

	void Timer::OnUpdate()
	{
		//止めるフラグあったら動かさない
		if (!m_TimeStopFlg)
		{
			//時間加算する
			m_Time += App::GetApp()->GetElapsedTime();
			//０秒以下なら
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

	//--------------------------------------------------------------------------------------
	//	class Player_Life : public GameObject;
	//	用途:プレイヤーのHP
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
			//HP中身作成
			auto HP = GetStage()->AddGameObject<GameObject>();

			//座標設定
			auto TranP = HP->AddComponent<Transform>();
			TranP->SetPosition(m_InitPos.x + (m_IntervalLife * i * m_InitScale.x), m_InitPos.y, 0);
			TranP->SetScale(m_InitScale.x, m_InitScale.y, 1);
			TranP->SetRotation(0, 0, 0);

			//大きさ設定
			auto DrawP = HP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"HP_TX");
			HP->SetAlphaActive(true);

			//レイヤー設定
			HP->SetDrawLayer(m_layer);
			//メンバ変数の管理するやつに追加
			m_LifeSprite.push_back(HP);

			//フレーム作成
			auto HP_Flame = GetStage()->AddGameObject<GameObject>();

			//Vector3 HP_Flame2 = HP_Flame->GetComponent<Transform>()->GetPosition();


			//m_LifeSprite.push_back(HP_Flame);

			//座標設定
			auto TranP2 = HP_Flame->AddComponent<Transform>();
			TranP2->SetPosition(m_InitPos.x + (m_IntervalLife * i * m_InitScale.x), m_InitPos.y, 0);
			TranP2->SetScale(m_InitScale.x, m_InitScale.y, 1);
			TranP2->SetRotation(0, 0, 0);

			//大きさ設定
			auto DrawP2 = HP_Flame->AddComponent<PCTSpriteDraw>();
			DrawP2->SetTextureResource(L"HP_FLAME_TX");
			HP_Flame->SetAlphaActive(true);

			//レイヤー設定
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

			//ゲームオーバー関数を呼ぶ
			dynamic_pointer_cast<GameStage>(GetStage())->GameOver();
		}

		//HP消す
		for (int i = m_LifeMax - 1; i > m_Life - 1; i--)
		{
			//直接やるけどまあライフ増やさないしおkでしょ
			m_LifeSprite[i]->SetDrawActive(false);
		}
	}
	//Abe20170418
	//Abe20170421

	//--------------------------------------------------------------------------------------
	//	スプライトの大きさ、位置を確認するオブジェクト
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

		//文字列
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
			//サイズは十字キーで操作
			//************************************
			//	操作方法
			//	十字キー：スケール [↑] +Y [↓] -Y [→] +X [←] -X
			//	スティック：座標移動
			//　A,B：減速
			//　X,Y：加速
			//************************************
			//変化速度設定
			float Speed = 1.0f;
			//２回に分けとけばそれだけ変化するのであえてやってる
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

			//サイズ------------------------------------------------
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
			//移動------------------------------------------------
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

			//表示
			wstring txt = L"Pos\nX:" + Util::FloatToWStr(m_pos.x) + L"\nY:" + Util::FloatToWStr(m_pos.y);
			txt += L"\nScale\nX:" + Util::FloatToWStr(m_scale.x) + L"\nY:" + Util::FloatToWStr(m_scale.y);
			GetComponent<StringSprite>()->SetText(txt);
		}
	}
	//Abe20170421
	//Abe20170427
	//--------------------------------------------------------------------------------------
	//	デバッグ文字表示するオブジェクト
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
	//文字設定
	void DebugTxt::SetText(wstring txt)
	{
		GetComponent<StringSprite>()->SetText(txt);
	}

	//大きさ(枠)設定
	void DebugTxt::SetScale(Vector2 sca)
	{
		m_Scale = sca;
		GetComponent<StringSprite>()->SetTextRect(Rect2D<float>(m_Pos.x, m_Pos.y, m_Pos.x + m_Scale.x, m_Pos.y + m_Scale.y));
	}
	//座標設定
	void DebugTxt::SetPos(Vector2 pos)
	{
		m_Pos = pos;
		GetComponent<StringSprite>()->SetTextRect(Rect2D<float>(m_Pos.x, m_Pos.y, m_Pos.x + m_Scale.x, m_Pos.y + m_Scale.y));
	}
	//大きさ(文字)設定
	void DebugTxt::SetScaleTxt(int scatxt)
	{
		m_ScaleTxt = scatxt;
		GetComponent<StringSprite>()->SetFont(L"", scatxt);
	}
	//レイヤー設定
	void DebugTxt::SetLayer(int num)
	{
		SetDrawLayer(num);
	}

	//色設定
	void DebugTxt::SetColor(Vector3 col)
	{
		GetComponent<StringSprite>()->SetFontColor(Color4(col.x, col.y, col.z, 1.0f));
	}
	//Abe20170427


	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChild : public GameObject;
	//	用途: ミサイルを撃つ子機　
	//--------------------------------------------------------------------------------------
	ShotEnemyChild::ShotEnemyChild(const shared_ptr<Stage>& StagePtr, const wstring& Line) :
		GameObject(StagePtr)
	{
		////トークン（カラム）の配列
		//vector<wstring> Tokens;
		////トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
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


		//モデルとトランスフォームの間の差分
		Matrix4X4 ShotEnemyChildMat;
		ShotEnemyChildMat.DefTransformation(
			Vector3(1.0, 1.0f, 1.0f),
			Vector3(0,140,0),
			Vector3(0.0f, -0.61f, 0.0f)
		);


		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0,0 ,0);
		AddComponent<Rigidbody>();
		//描画設定
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"MissileEnemyChildModl");
	//	Draw->SetTextureResource(L"Glass_TX");
		//SetDrawActive(false);
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		PtrString->SetFontColor(Color4(1.0f, 0.0f, 0.0f, 1.0f));
		//基準Pos 
		m_ReferencePoint_Vec3 = Vector3(m_Position.x - (m_Scale.x / 2) / 2, m_Position.y, m_Position.z - m_Scale.z / 2);//右
		m_ReferencePoint2_Vec3 = Vector3(m_Position.x + (m_Scale.x / 2) / 2, m_Position.y, m_Position.z - m_Scale.z / 2);//左
		m_CenterPoint_Vec3 = Vector3(m_Position.x, m_Position.y, m_Position.z - m_Scale.z / 2);
		SetDrawLayer(-20);
		auto PtrDraw = GetComponent<PNTStaticDraw>();
		PtrDraw->SetMeshToTransformMatrix(ShotEnemyChildMat);


	}
	void ShotEnemyChild::OnUpdate() {
		//Abe20170517
		if (m_ShotFlg)
		//Abe20170517
		{
			DoingSandRotation();
			ShotEnemyChildRot();
			PintNewPos();
			Direction();
			Shot();
		}
		else
		{
			Tobu();
		}
	}
	//Abe20170517
	void ShotEnemyChild::Tobu()
	{
		//座標移動
		Vector3 pos = GetComponent<Transform>()->GetPosition();
		pos += m_Velocity * App::GetApp()->GetElapsedTime();
		GetComponent<Transform>()->SetPosition(pos);

		//ちょっと遅めに落とす
		m_Velocity.y += -9.8f * App::GetApp()->GetElapsedTime();

		//床に近くなったら消す
		if (GetComponent<Transform>()->GetPosition().y <= 1.0f)
		{
			m_ShotFlg = true;
		}
	}
	//Abe20170517

	void ShotEnemyChild::OnLastUpdate() {
		//文字列表示
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\n";


		wstring  str = FPS;
		auto PtrString = GetComponent<StringSprite>();
		//PtrString->SetText(str);
	}
		//ミサイルを撃つ子機の回転 挟まれていないとき
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
			//回転する
			Trans->SetQuaternion(Qt);
			m_Angle = Qt;
			//m_Debug = Rig->GetVelocity();
		}
	}
	//挟まれているとき
	void ShotEnemyChild::DoingSandRotation() {
		if (GetShotEnemyChildSandFlg()) {
			auto Trans = GetComponent<Transform>();
			auto Rig = GetComponent<Rigidbody>();
			auto Qt = Trans->GetQuaternion();
			float ElapsedTime = App::GetApp()->GetElapsedTime();


			//コントローラの取得
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
	//弾発射場所の回転
	void ShotEnemyChild::PintNewPos() {
		auto Trans = GetComponent<Transform>();
		auto Pos = Trans->GetPosition();
		auto Scal = Trans->GetScale();
		auto ScalHalf = Scal / 2;
		float RotY = Trans->GetRotation().y;
		RotY += XM_PIDIV2;
		//距離の算出
		Vector3 m_Distance = m_Position - m_ReferencePoint_Vec3;
		Vector3 m_Distance2 = m_Position - m_ReferencePoint2_Vec3;
		Vector3 m_CenteDistancer = m_Position;
		// (中心からA地点の距離＊Sin（回転軸+場所）) ボックスを中心として回転して自分の位置を移動させることが可能
		//＋しているところの値が一緒でないと回転がおかしくなります
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
		//デバック
		m_getPos = m_NewReferencePoint_Vec3;
		m_getPos2 = m_NewReferencePoint2_Vec3;
		m_getCenter = m_NewCenterPoint_Vec3;
	}
	//撃つ
	void ShotEnemyChild::Shot() {
		auto Ela = App::GetApp()->GetElapsedTime();
		m_Time += Ela;
		//二秒間隔で発射
		if (m_Time > 2) {
			m_cout += 2;
			m_Time = 0.0;

			//Abe20170504
			//アタリ判定するオブジェクトにいれてやるやり方やってみるのでちょいと変更します
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup");
			auto obj = GetStage()->AddGameObject<ShotEnemyChildMissile>(
				Vector3(GetPos(true)),
				Vector3(0.5, 0.5, 0.5),
				Vector3(0, 0, 0),
				m_getCenter);
			ColGroup->IntoGroup(obj);
			obj = GetStage()->AddGameObject<ShotEnemyChildMissile>(
				Vector3(GetPos(false)),
				Vector3(0.5, 0.5, 0.5),
				Vector3(0, 0, 0),
				m_getCenter);
			ColGroup->IntoGroup(obj);
			//Abe20170504

		}
	}

	//向きの取得
	Vector3 ShotEnemyChild::Direction() {
		auto Trans = GetComponent<Transform>();
		Vector3 Pos = Trans->GetPosition();
		m_Direction_Vec3 = m_getCenter - Pos;
		m_Direction_Vec3.Normalize();
		return m_Direction_Vec3;
	}

	//--------------------------------------------------------------------------------------
	//	class ShotEnemyChildMissile : public GameObject;
	//	用途: ミサイルを撃つ子機（ミサイル）
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
		//描画設定
		auto Draw = AddComponent<PNTStaticDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"DEFAULT_SPHERE");
		Draw->SetTextureResource(L"Glass_TX");
		//撃つ
		m_ShotActive = true;
	}
	void ShotEnemyChildMissile::OnUpdate() {
		if (m_ShotActive) {
			ChildMissileMove();
			ObjDelete();
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

		//桁数える-------------------------------------
		int count = m_num;
		do
		{
			count /= 10;
			m_digit++;
		} while (count > 0);
		//桁数える-------------------------------------

		//数字の画像作成-------------------------
		for (int i = 0; i < 10; i++)
		{
			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float from = i / 10.0f;
			float to = from + (1.0f / 10.0f);
			//左上頂点
			vertices[0].textureCoordinate = Vector2(from, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vector2(to, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vector2(from, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vector2(to, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Color4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//メッシュ作成
			m_Mesh.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//数字の画像作成-------------------------

		//数字スプライト作成---------------------
		//処理用に数字取っておく
		int masternum = m_num;

		//計算結果入れておく用の箱
		vector<int> OutNums;

		//桁分ループ、数字作成
		for (int j = 0; j < m_digit; j++)
		{
			//生成した桁数加算
			m_Constdigit++;

			//上位の桁から数字入れてく
			int num = masternum / pow(10, (m_digit - 1) - j);
			OutNums.push_back(num);
			//計算用の桁の最上位の桁を排除
			masternum = masternum % (int)(pow(10, (m_digit - 1) - j));
		}

		//一個右との差
		float distance = m_scale.x / IntervalNums;

		wstring txt;
		//桁分逆からループ！(0から上位の桁入れてるので)
		//動けばいいよね、バグ起きそうとか言わない
		for (int j = 0; j < m_digit; j++) {


			//生成オブジェ
			auto NumP = GetStage()->AddGameObject<GameObject>();

			//座標設定
			auto TranP = NumP->AddComponent<Transform>();
			TranP->SetPosition(m_pos.x - (distance*count), m_pos.y, 5);
			TranP->SetScale(m_scale.x, m_scale.y, 3);
			TranP->SetRotation(0, 0, 0);

			//大きさ設定
			auto DrawP = NumP->AddComponent<PCTSpriteDraw>();
			DrawP->SetTextureResource(L"NUMBER_TX");
			DrawP->SetMeshResource(m_Mesh[OutNums[(m_digit - 1) - j]]);
			NumP->SetAlphaActive(true);

			//レイヤー設定
			NumP->SetDrawLayer(m_layer);
			//メンバ変数の管理するやつに追加
			m_Numbers.push_back(NumP);

			//カウントアップ
			count++;

		}
		//数字スプライト作成---------------------
	}


	void EnemyCountSprite::SetNum(int num)
	{
		//マイナス弾く
		if (m_num >= 0)
		{
			m_num = num;
			//入力された桁持ってくる
			int digit = 0;
			int innum = num;
			do
			{
				innum /= 10;
				digit++;
			} while (innum > 0);

			//処理用に数字取っておく
			int masternum = m_num;
			//計算結果入れておく用の箱
			vector<int> OutNums;

			//桁分ループ、数字作成
			for (int j = 0; j < digit; j++)
			{
				//上位の桁から数字入れてく
				int num = masternum / pow(10, (digit - 1) - j);
				OutNums.push_back(num);
				//計算用の桁の最上位の桁を排除
				masternum = masternum % (int)(pow(10, (digit - 1) - j));
			}


			//入力されたほうが大きかったら
			if (digit > m_digit)
			{
				//追加する分だけループ
				for (int j = 0; j < (digit - m_Constdigit); j++)
				{
					//左側に桁追加だけ、数字は後で入れる
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
			//入力されたほうが小さい
			else if (digit < m_digit)
			{
				//添え字ように-1ずらす
				for (int i = m_digit - 1; i > digit - 1; i--)
				{
					m_Numbers[i]->SetDrawActive(false);
				}
			}

			//桁更新
			m_digit = digit;

			//数字入れ替え
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
		//数字作成
		//Abe20170519ちょっと修正
		Vector2 pos = m_InitPos;
		//左上にずらす
		pos.x += -m_InitScale.x * 0.5f;
		pos.y += +m_InitScale.y * 0.5f;
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(0,pos, m_InitScale, m_LayerNum);
		//右下に
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
			//キャスト
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
	}



	////////////////////////////////////////////////////
	//Abe20170519MukkuMarge一つでまとめられるのでEnemyCountAのほうにまとめ
	/*

	EnemyCountB::EnemyCountB(const shared_ptr<Stage>& StagePtr, Vector2 pos, Vector2 scale, int layer) :
		GameObject(StagePtr),
		m_InitPos(pos),
		m_InitScale(scale),
		m_LayerNum(layer)
	{}

	void EnemyCountB::OnCreate()
	{
		//数字作成
		m_Numbers = GetStage()->AddGameObject<NumberSprite>(0,m_InitPos, m_InitScale, m_LayerNum);

		m_EnemyCunt = 0;


	}

	void EnemyCountB::OnUpdate()
	{
		m_EnemyCunt = 0;

		auto Group = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		//auto ShellVec = Group->GetGroupVector();

		for (auto obj : Group) {
			//キャスト
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

	//背景モデル
	BackgroundModel::BackgroundModel(const shared_ptr<Stage>& StagePtr, const Vector3& Pos, const Vector3& Scale,const int& LayerNum):
		GameObject(StagePtr),
		m_Pos(Pos),
		m_Scale(Scale),
		m_LayerNum(LayerNum)
	{}
	void BackgroundModel::OnCreate() {
		auto Trans = AddComponent<Transform>();
		Trans->SetScale(m_Scale * 1.5);

		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		//描画するメッシュを設定
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
	//	ゲームオーバー処理
	//--------------------------------------------------------------------------------------
	void GameOverS::OnCreate()
	{
		//全部の動くオブジェクトを止める
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//全部止める
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

		//状態を初期に
		m_State = 0;

		//プレイヤーのアクセサー的なの
		m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
		m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");
		//ついでにレイヤー上げとく(と表示消えるくそりぶ)
		//m_Player1->SetDrawLayer(11);
		//m_Player2->SetDrawLayer(11);

		//プレイヤーを手前に
		m_Player1->SetUpdateActive(false);
		m_Player2->SetUpdateActive(false);

		//プレイヤー管理してるやつ止める
		GetStage()->GetSharedGameObject<PlayerManager>(L"PtrPlayerManager",false)->SetUpdateActive(false);

		//移動目標設定
		m_TargetPos1 = Vector3(-2, 10, 0);
		m_TargetPos2 = Vector3(2, 10, 0);

		//暗転幕と白を作成
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
		//白版
		auto White = GetStage()->AddGameObject<GameObject>();
		auto TransW = White->AddComponent<Transform>();
		TransW->SetPosition(0, 8.2f, -3);
		TransW->SetScale(100, 100, 1);
		TransW->SetRotation(0, 0, 0);

		auto DrawW = White->AddComponent<PNTStaticDraw>();
		DrawW->SetTextureResource(L"OVERWHITE_TX");
		DrawW->SetMeshResource(L"DEFAULT_SQUARE");
		DrawW->SetDiffuse(Color4(1, 1, 1, 0));

		White->SetDrawLayer(10);
		White->SetAlphaActive(true);

		m_White = White;

	}

	void GameOverS::OnUpdate()
	{
		switch (m_State)
		{
			//プレイヤーを上に移動
		case 0:
			if (true)
			{
				//暗転
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				if (m_BlackAlpha < 1.0f)
				{
					m_Black->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				//プレイヤーを目的地に移動
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
					//状態進める
					m_State = 1;

					//カメラ移動消す
					dynamic_pointer_cast<GameStage>(GetStage())->CameraStop();
				}
			}
			break;
			//カメラを近づける
		case 1:
			if (true)
			{
				if (dynamic_pointer_cast<GameStage>(GetStage())->GameOverCamera())
				{
					//状態進める
					m_State = 2;
					//落とす速度変えて若干浮かす
					m_Grav1 = 3;
					m_Grav2 = 3;
					//浮かす
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
					pos1.y += 0.5f;
					pos2.y += 0.5f;
					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//時間初期化
					m_time = 0;
				}
			}
			break;
			//プレイヤーを横に倒す
		case 2:
			if (true)
			{
				Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
				Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();
				//ある程度まで落ちるまで落とす
				if (pos1.y >= 10)
				{
					pos1.y += m_Grav1 * App::GetApp()->GetElapsedTime();
					pos2.y += m_Grav2 * App::GetApp()->GetElapsedTime();

					m_Grav1 += -9.8f * App::GetApp()->GetElapsedTime();
					m_Grav2 += -9.8f * App::GetApp()->GetElapsedTime();

					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//回転
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
					//ちょっと待つ
					if (m_time > m_BombTime)
					{
						//爆発エフェクト
						auto obj = GetStage()->AddGameObject<BombEffect>();
						auto obj2 = GetStage()->AddGameObject<BombEffect>();
						obj->SetPosActive(m_Player1->GetComponent<Transform>()->GetPosition());
						obj2->SetPosActive(m_Player2->GetComponent<Transform>()->GetPosition());

						obj->SetLayer(8);
						obj2->SetLayer(8);

						//キャラ非表示
						m_Player1->SetDrawActive(false);
						m_Player2->SetDrawActive(false);

						//音出す
						m_CreateSe = ObjectFactory::Create<MultiAudioObject>();
						m_CreateSe->AddAudioResource(L"OverBombSE");
						m_CreateSe->Start(L"OverBombSE", 0.5f);

						//白くする
						m_BlackAlpha = 0.8f;
						m_White->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

						//状態進める
						m_State = 3;
					}
				}
			}
			break;
			//画面白いの戻してく
		case 3:
			if (true)
			{
				if (m_BlackAlpha > 0)
				{
					m_BlackAlpha += -App::GetApp()->GetElapsedTime()/2;
					//白いの戻す
					m_White->GetComponent<PNTStaticDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				}
				else
				{
					//状態進める
					m_State = 4;

					//ノイズ作成
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 0, 0);
					Trans->SetScale(1280, 720, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERNOISE_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(10);
					obj->SetAlphaActive(true);

					m_Noise = obj;

					//暗転幕
					auto obj2 = GetStage()->AddGameObject<GameObject>();
					auto Trans2 = obj2->AddComponent<Transform>();
					Trans2->SetPosition(0, 0, 0);
					Trans2->SetScale(1280, 720, 1);
					Trans2->SetRotation(0, 0, 0);

					auto Draw2 = obj2->AddComponent<PCTSpriteDraw>();
					Draw2->SetTextureResource(L"OVERBLACK_TX");
					Draw2->SetDiffuse(Color4(1, 1, 1, 0));

					obj2->SetDrawLayer(11);
					obj2->SetAlphaActive(true);

					m_BlackSprite = obj2;

					//透明度0
					m_BlackAlpha = 0;
				}
			}
			break;
			//ノイズ出す
		case 4:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				m_Noise->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));
				if (m_BlackAlpha > 0.2f && !m_NoiseSeFlg)
				{
					//２回目はいらないように
					m_NoiseSeFlg = true;

					//音鳴らす
					m_NoiseSe = ObjectFactory::Create<MultiAudioObject>();
					m_NoiseSe->AddAudioResource(L"OverNoiseSE");
					m_NoiseSe->Start(L"OverNoiseSE", 0.2f);
				}
				if (m_BlackAlpha > 2.0f)
				{
					//状態移動
					m_State = 5;

					m_BlackAlpha = 0;

					m_NoiseSe->Stop(L"OverNoiseSE");
				}
			}
			break;
			//ノイズの上に暗転
		case 5:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime() / 2;
				m_BlackSprite->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				if (m_BlackAlpha > 1.0f)
				{
					//状態移動
					m_State = 6;

					//ゲームオーバー文字作成
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, 120, 0);
					Trans->SetScale(800, 100, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERLOGO_TX");
					Draw->SetDiffuse(Color4(1, 1, 1, 0));

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_GameOverLogo = obj;

					m_BlackAlpha = 0;
				}
			}
			break;
			//ゲームオーバー文字出す
		case 6:
			if (true)
			{
				m_BlackAlpha += App::GetApp()->GetElapsedTime();
				if (m_BlackAlpha < 1.0f)
				{
					m_GameOverLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1,1,1,m_BlackAlpha));

				}
				else
				{
					//状態変更
					m_State = 7;

					//選択肢作成
					//リトライ
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-300, -120, 0);
					Trans->SetScale(300, 100, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERRETRYLOGO_TX");

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_OverRetryLogo = obj;

					//ステセレ
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(0, -120, 0);
					Trans->SetScale(300, 100, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERSTASELELOGO_TX");

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_OverStageSelectLogo = obj;

					//タイトル
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(300, -120, 0);
					Trans->SetScale(300, 100, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"OVERTITLELOGO_TX");

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_OverTitleLogo = obj;

					//カーソル作成------------------------------------
					auto CursorSprite = GetStage()->AddGameObject<GameObject>();
					//座標
					auto CTrans = CursorSprite->AddComponent<Transform>();
					CTrans->SetPosition(-300, -140, 0);
					CTrans->SetScale(120, 100, 1);
					CTrans->SetRotation(0, 0, 0);

					//描画
					auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
					CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

					//レイヤー設定
					CursorSprite->SetDrawLayer(13);

					//透明度有効化
					CursorSprite->SetAlphaActive(true);

					m_Cursor = CursorSprite;

					//音鳴らす準備
					m_SelectSe = ObjectFactory::Create<MultiAudioObject>();
					m_SelectSe->AddAudioResource(L"CURSORMOVE_SE");

				}

			}
			break;
			//選択できるように
		case 7:
			if (true)
			{		
				//コントローラ取得
				auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
				if (CntlVec[0].bConnected)
				{
					//カーソル動かす処理
					if (m_MoveFlg)
					{
						//右
						if (CntlVec[0].fThumbLX > 0.5f)
						{
							m_SelectNum++;
							if (m_SelectNum > 2)
							{
								m_SelectNum = 0;
							}
							//動けるフラグ止める
							m_MoveFlg = false;

						}
						//左
						if (CntlVec[0].fThumbLX < -0.5f)
						{
							m_SelectNum--;
							if (m_SelectNum < 0)
							{
								m_SelectNum = 2;
							}
							//動けるフラグ止める
							m_MoveFlg = false;
						}

						if (!m_MoveFlg)
						{
							//音鳴らす
							m_SelectSe->Start(L"CURSORMOVE_SE", 0.5f);

							//移動
							switch (m_SelectNum)
							{
							case 0:
								m_Cursor->GetComponent<Transform>()->SetPosition(-300, -140, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(140, 100, 1);
								break;
							case 1:
								m_Cursor->GetComponent<Transform>()->SetPosition(0, -140, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(300, 100, 1);
								break;
							case 2:
								m_Cursor->GetComponent<Transform>()->SetPosition(300, -140, 0);
								m_Cursor->GetComponent<Transform>()->SetScale(140, 100, 1);
								break;
							default:
								break;
							}
						}
					}
					//ずっと動けないように
					else
					{
						if (abs(CntlVec[0].fThumbLX) < 0.5f && abs(CntlVec[0].fThumbLY) < 0.5f)
						{
							m_MoveFlg = true;
						}
					}

					//Aボタン押されたら移動
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
					{
						//状態変更
						m_State = 8;

						//暗転幕作成
						auto obj = GetStage()->AddGameObject<GameObject>();
						auto Trans = obj->AddComponent<Transform>();
						Trans->SetPosition(0, 0, 0);
						Trans->SetScale(1280, 720, 1);
						Trans->SetRotation(0, 0, 0);

						auto Draw = obj->AddComponent<PCTSpriteDraw>();
						Draw->SetTextureResource(L"OVERBLACK_TX");
						Draw->SetDiffuse(Color4(1, 1, 1, 0));

						obj->SetDrawLayer(13);
						obj->SetAlphaActive(true);

						m_BlackLast = obj;

						//透明度0
						m_BlackAlpha = 0;


						//音鳴らす
						m_KetteiSe = ObjectFactory::Create<MultiAudioObject>();
						m_KetteiSe->AddAudioResource(L"DECIDE_SE");
						m_KetteiSe->Start(L"DECIDE_SE", 0.5f);

					}
				}
			}
			break;
			//暗転と遷移
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
						//リトライ
					case 0:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//ステセレ
					case 1:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
						}
						break;
						//タイトル
					case 2:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
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

}
	//end basecross
