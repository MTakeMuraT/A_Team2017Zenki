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
		SetDrawLayer(7);

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

			//なんかバグってるので初期化
			OutNums.clear();

			//桁分ループ、数字作成
			for (int j = 0; j < digit; j++)
			{
				//上位の桁から数字入れてく
				int powpow = pow(10, (digit - 1) - j);
				int numm = masternum / powpow;
				OutNums.push_back(numm);
				//計算用の桁の最上位の桁を排除
				masternum = masternum % (int)(pow(10, (digit - 1) - j));
			}


			//入力されたほうが大きかったら
			if (digit > m_digit)
			{
				//追加する分だけループ
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
				//左側に桁追加だけ、数字は後で入れる
				m_Constdigit = digit;

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

	//Abe20170531
	//移動
	void NumberSprite::MoveNums(Vector3 inpos)
	{
		for (auto obj : m_Numbers)
		{
			Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
			pos += inpos;
			obj->GetComponent<Transform>()->SetPosition(pos);
		}
	}

	//レイヤー設定
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

		//タイムの背景
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

	//Abe20170531
	//座標移動
	void Timer::MovePos(Vector3 inpos)
	{
		m_Numbers->MoveNums(inpos);
	}

	//レイヤー設定
	void Timer::SetLayer(int num)
	{
		m_Numbers->SetLayer(num);
	}
	//Abe20170531

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
		else
		{
			//死んでなけらばカメラ演出
			dynamic_pointer_cast<GameStage>(GetStage())->DamageCameraOn();

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


	//Abe20170531
	//ライフスプライト移動
	void Player_Life::MoveSprtieS(Vector3 inpos)
	{
		//入力された分移動
		for (auto obj : m_AllSpriteS)
		{
			Vector3 pos = obj->GetComponent<Transform>()->GetPosition();
			pos += inpos;
			obj->GetComponent<Transform>()->SetPosition(pos);
		}
	}
	//レイヤー変更
	void Player_Life::SetLayer(int num)
	{
		//レイヤー変更
		for (auto obj : m_AllSpriteS)
		{
			obj->SetDrawLayer(num);
		}

	}
	//Abe20170531

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
			Vector3(0.2f, 0.2f, 0.2f),
			Vector3(0,140,0),
			Vector3(0.0f, -0.61f, 0.0f)
		);


		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(m_Position);
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0,0 ,0);
		AddComponent<Rigidbody>();
		//描画設定
		auto Draw = AddComponent<PNTBoneModelDraw>();
		//メッシュ設定
		Draw->SetMeshResource(L"MissileEnemyChildModel");
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
		Draw->SetMeshToTransformMatrix(ShotEnemyChildMat);

		//Abe20170609
		//アニメーション追加
		Draw->AddAnimation(L"Shot", 0, 60, true, 60);
		//アニメーション設定
		Draw->ChangeCurrentAnimation(L"Shot");
		//Abe20170609

	}
	void ShotEnemyChild::OnUpdate() {
		//Abe20170517
		if (m_ShotFlg)
		//Abe20170517
		{
			//Abe20170614
			//時間たったら消える
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

			//アニメーション更新
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
		m_DeleteTime = 0;

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
		auto Draw = AddComponent<PNTStaticModelDraw>();
		//メッシュ設定
		//Draw->SetMeshResource(L"DEFAULT_SPHERE");
		//Draw->SetTextureResource(L"Glass_TX");
		Draw->SetMeshResource(L"Missile_Model");
		//撃つ
		m_ShotActive = true;
		//モデルとトランスフォームの間の差分
		Matrix4X4 ShotEnemyChildMat;
		ShotEnemyChildMat.DefTransformation(
			Vector3(0.8f, 0.8f, 0.8f),
			Vector3(0, -90*3.14159265f/180, 0),
			Vector3(0.0f, 0.0f, 0.0f)
			);

		Draw->SetMeshToTransformMatrix(ShotEnemyChildMat);

		//角度設定
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

		if (m_EnemyCunt == 0)
		{
			dynamic_pointer_cast<GameStage>(GetStage())->Result();
		}
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
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//アタリ判定止める
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(false);
		}
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
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl",false)->SetUpdateActive(false);

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

						obj->SetLayer(10);
						obj2->SetLayer(10);

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

					obj->SetDrawLayer(12);
					obj->SetAlphaActive(true);

					m_Noise = obj;

					//暗転幕
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
			//ゲームオーバー文字出す
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
					//状態変更
					m_State = 7;

					//選択肢作成
					//リトライ
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

					//ステセレ
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

					//タイトル
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

					//カーソル作成------------------------------------
					auto CursorSprite = GetStage()->AddGameObject<GameObject>();
					//座標
					auto CTrans = CursorSprite->AddComponent<Transform>();
					CTrans->SetPosition(-300, -240, 0);
					CTrans->SetScale(180, 20, 1);
					CTrans->SetRotation(0, 0, 0);

					//描画
					auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
					CDraw->SetTextureResource(L"OVERCURSOR_TX");

					//レイヤー設定
					CursorSprite->SetDrawLayer(15);

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
					//ずっと動けないように
					else
					{
						if (abs(CntlVec[0].fThumbLX) < 0.5f && abs(CntlVec[0].fThumbLX) > -0.5f)
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

						obj->SetDrawLayer(15);
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
						//	m_AudioObjectPtr->Stop(L"Loss_BGM");
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//ステセレ
					case 1:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
						//	m_AudioObjectPtr->Stop(L"Loss_BGM");
							PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
						}
						break;
						//タイトル
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
	//	リザルト処理
	//--------------------------------------------------------------------------------------
	void ResultS::OnCreate()
	{
		if (!m_TutorialFlg)
		{
			//全部の動くオブジェクトを止める
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
			auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
			auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
			auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
			//アタリ判定止める
			auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
			if (colmanptr)
			{
				colmanptr->SetUpdateActive(false);
			}
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
			GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

			//プレイヤーの目標座標、中心座標を取得
			m_centerPos = (m_Player1->GetComponent<Transform>()->GetPosition() + m_Player2->GetComponent<Transform>()->GetPosition()) / 2;
			m_Player1TargetPos = m_centerPos;
			m_Player1TargetPos.x += -2;
			m_Player2TargetPos = m_centerPos;
			m_Player2TargetPos.x += 2;
		}
		//チュートリアルの時
		else
		{
			//状態を初期に
			m_State = 0;

			//プレイヤーのアクセサー的なの
			m_Player1 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L");
			m_Player2 = GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R");

			//プレイヤーの目標座標、中心座標を取得
			m_centerPos = (m_Player1->GetComponent<Transform>()->GetPosition() + m_Player2->GetComponent<Transform>()->GetPosition()) / 2;
			m_Player1TargetPos = m_centerPos;
			m_Player1TargetPos.x += -2;
			m_Player2TargetPos = m_centerPos;
			m_Player2TargetPos.x += 2;

		}
		//Abe20170601
		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(15);
		//色赤に変更
		m_Debugtxt->SetColor(Vector3(1, 0, 0));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);
		//Abe20170601
	
	}
	
	void ResultS::OnUpdate()
	{
		if (!m_TutorialFlg)
		{
			//コントローラ
			auto KeylVec = App::GetApp()->GetInputDevice().GetKeyState();
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			switch (m_State)
			{
				//しばらく待つ
			case 0:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_1WaitTime)
					{
						//状態変更
						m_State = 1;

						//時間初期化
						m_time = 0;

						//カメラ停止
						dynamic_pointer_cast<GameStage>(GetStage())->CameraStop();
					}
				}
				break;
				//カメラを近づける＋キャラを近づける
			case 1:
				if (true)
				{
					//カメラ動いてるフラグ
					bool flg1 = false;
					//カメラを移動して目標地点に近いか判定
					if (dynamic_pointer_cast<GameStage>(GetStage())->ResultCamera(m_centerPos))
					{
						flg1 = true;
					}

					//プレイヤーを目的地に移動
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

					//近ければ判定用のフラグをtrueにし、遠ければ近づける
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
						//状態変更
						m_State = 2;
					}
				}
				break;
				//キャラを手前に向かせる
			case 2:
				if (true)
				{
					//回転
					Vector3 rot1 = m_Player1->GetComponent<Transform>()->GetRotation();
					Vector3 rot2 = m_Player2->GetComponent<Transform>()->GetRotation();
					rot1.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
					rot2.y += -180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();

					//なんか変なとこで違う軸が回転するからそれ止める
					rot1 = Vector3(0, rot1.y, 0);
					rot2 = Vector3(0, rot2.y, 0);
					//大体手前が1.6くらい
					if (rot1.y >= 1.4f && rot1.y <= 1.8f)
					{
						//回転固定
						rot1.y = 90 * 3.14159265f / 180;
						rot2.y = 90 * 3.14159265f / 180;

						//状態変更
						m_State = 3;
						//跳ねる力設定
						float m_HopPower = 10;

						//跳ねるフラグオン
						m_HopFlg = true;

					}
					m_Player1->GetComponent<Transform>()->SetRotation(rot1);
					m_Player2->GetComponent<Transform>()->SetRotation(rot2);

				}
				break;
				//跳ねる
			case 3:
				if (true)
				{
					//状態変更
					m_State = 4;

					//ミッションコンプリート文字作成
					//暗転幕作成
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
				//ミッションコンプリート文字左から出す
			case 4:
				if (true)
				{
					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();

					//中心まで来たら
					if (pos.x > 0 || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 41;
					}

					//座標移動
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//ここからスキップ機能追加スキップ機能全般の実装は20170627Abe
			case 41:
				if (true)
				{
					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();

					//暗転幕作成
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

					
					//座標固定
					pos.x = 0;

					//状態変更
					m_State = 5;

					//座標移動
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);

				}
				break;
				//ちょっと暗くする
			case 5:
				if (true)
				{
					if (m_BlackAlpha < 0.5f)
					{
						m_BlackAlpha += App::GetApp()->GetElapsedTime();
					}
					else
					{
						//状態変更
						m_State = 51;
					}

					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						//透明度固定
						m_BlackAlpha = 0.5f;
						//状態変更
						m_State = 51;
					}
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				}
				break;
			case 51:
				if (true)
				{
					//透明度固定
					m_BlackAlpha = 0.5f;
					//透明度設定
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

					m_State = 6;
				}
				break;
				//ミッションコンプリート小さくして上に移動
			case 6:
				if (true)
				{
					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					if (pos.y < 200)
					{
						pos.y += 600 * App::GetApp()->GetElapsedTime();
					}

					//大きさ持ってくる
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

					//スキップ
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 61;
					}

					//座標と大きさ更新
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
			case 61:
				if (true)
				{

					//状態変更
					m_State = 7;

					//タイマー持ってくる
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HPスプライト持ってくる
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					//レイヤー変える
					timeptr->SetLayer(11);
					hpptr->SetLayer(11);

					//constで宣言しても更新されないunkなので
					//HPスプライトとTimeの目的座標を再設定
					m_HpTargetPos = Vector3(30, -250, 0);
					m_TimeTargetPos = Vector3(-400, -400, 0);


					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					//大きさ持ってくる
					Vector3 sca = m_MissCompLogo->GetComponent<Transform>()->GetScale();

					pos.y = 200;
					sca.x = 1200;
					sca.y = 420;

					//座標と大きさ更新
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//HPスプライトとタイム持ってくる
			case 7:
				if (true)
				{
					//タイマー持ってくる
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HPスプライト持ってくる
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					m_HpPos += Vector3(0.3f, -2.5f, 0) * 3;
					m_TimePos += Vector3(-4, -4, 0) * 3;

					//判定フラグ
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
						//状態変更
						m_State = 8;
					}

					//スキップ
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 71;
					}

					//デバッグ-----------------------
					//wstring txt = Util::FloatToWStr(m_TimePos.x) + L":"
					//	+ Util::FloatToWStr(m_TimePos.y) + L":";
					//txt += L"\n";
					//txt += Util::FloatToWStr(m_TimeTargetPos.x) + L":"
					//	+ Util::FloatToWStr(m_TimeTargetPos.y) + L":";
					//m_Debugtxt->SetText(txt);
					//デバッグ-----------------------

				}
				break;
			case 71:
				if (true)
				{
					//タイマー持ってくる
					auto timeptr = GetStage()->GetSharedGameObject<Timer>(L"Timer", false);
					//HPスプライト持ってくる
					auto hpptr = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false);

					//移動量計算
					float HpPosMoveX = m_HpTargetPos.x - m_HpPos.x;
					float HpPosMoveY = m_HpTargetPos.y - m_HpPos.y;

					float TimePosMoveX = m_TimeTargetPos.x - m_TimePos.x;
					float TimePosMoveY = m_TimeTargetPos.y - m_TimePos.y;

					//移動
					hpptr->MoveSprtieS(Vector3(HpPosMoveX, HpPosMoveY, 0));
					timeptr->MovePos(Vector3(TimePosMoveX, TimePosMoveY, 0));

					m_State = 8;
				}
				break;
				//項目出す
			case 8:
				if (true)
				{
					//HPのほうの×作成
					auto batu = GetStage()->AddGameObject<GameObject>();
					auto Transba = batu->AddComponent<Transform>();
					Transba->SetPosition(-5, 50, 0);
					Transba->SetScale(100, 100, 1);
					Transba->SetRotation(0, 0, 0);

					auto Drawba = batu->AddComponent<PCTSpriteDraw>();
					Drawba->SetTextureResource(L"BATU_TX");

					batu->SetDrawLayer(11);
					batu->SetAlphaActive(true);

					//HPの倍率スコア
					auto numhp = GetStage()->AddGameObject<NumberSprite>(500, Vector2(260, 50), Vector2(100, 100), 11);

					//HPのスコア
					auto numhpscore = GetStage()->AddGameObject<NumberSprite>(0, Vector2(560, 50), Vector2(100, 100), 11);
					m_HpScore = numhpscore;

					//TIMEのスコア
					auto numtimescore = GetStage()->AddGameObject<NumberSprite>(0, Vector2(560, -100), Vector2(100, 100), 11);
					m_TimeScore = numtimescore;

					//状態変更
					m_State = 9;

					//数字系
					m_HpAmount = 0;
					m_TimeAmount = 0;

					//スコア最大値設定
					//HPの値は[値*500]
					m_HpScoreTotal = GetStage()->GetSharedGameObject<Player_Life>(L"Life", false)->GetLife() * 500;
					m_TimeScoreTotal = GetStage()->GetSharedGameObject<Timer>(L"Timer", false)->GetTime();
					//Timeの値設定。30秒までは無条件で5000
					if (m_TimeScoreTotal <= 30)
					{
						m_TimeScoreTotal = 5000;
					}
					//あとは200秒まで1秒25点で加点
					else if (m_TimeScoreTotal <= 200)
					{
						m_TimeScoreTotal = (200 - m_TimeScoreTotal) * 25;
					}
					else
					{
						m_TimeScoreTotal = 0;
					}

					//トータルスコア計算
					m_TotalAmount = 0;
					m_TotalScore = m_HpScoreTotal + m_TimeScoreTotal;
				}
				break;
				//スコア加算
			case 9:
				if (true)
				{
					//HPスコア加算
					m_HpAmount += m_HpScoreTotal / 60;
					//TIMEスコア加算
					m_TimeAmount += m_TimeScoreTotal / 60;

					//最大値いったかのフラグ
					bool flg1 = false;
					bool flg2 = false;
					//HPのスコア越してたら
					if (m_HpAmount >= m_HpScoreTotal)
					{
						m_HpAmount = m_HpScoreTotal;
						flg1 = true;
					}
					//ITMEのスコア越してたら
					if (m_TimeAmount >= m_TimeScoreTotal)
					{
						m_TimeAmount = m_TimeScoreTotal;
						flg2 = true;
					}
					//HPスコア更新
					dynamic_pointer_cast<NumberSprite>(m_HpScore)->SetNum(m_HpAmount);
					//TIMEスコア更新
					dynamic_pointer_cast<NumberSprite>(m_TimeScore)->SetNum(m_TimeAmount);


					//HPとTIMEのスコアが設定値に届いたら
					if (flg1 && flg2)
					{
						m_State = 91;
					}

					//スキップ
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 91;
					}

				}
				break;
			case 91:
				if (true)
				{
					//スコア変更
					m_HpAmount = m_HpScoreTotal;
					m_TimeAmount = m_TimeScoreTotal;

					//HPスコア更新
					dynamic_pointer_cast<NumberSprite>(m_HpScore)->SetNum(m_HpAmount);
					//TIMEスコア更新
					dynamic_pointer_cast<NumberSprite>(m_TimeScore)->SetNum(m_TimeAmount);

					//状態更新
					m_State = 10;

					//Totalスコア
					auto numTo = GetStage()->AddGameObject<NumberSprite>(500, Vector2(450, -250), Vector2(100, 100), 11);
					m_TotalScoreSp = numTo;

					//TotalScoreロゴ作成
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
				//トータルスコア加算
			case 10:
				if (true)
				{
					//Totalスコア加算
					m_TotalAmount += m_TotalScore / 60;

					if (m_TotalAmount >= m_TotalScore)
					{
						m_TotalAmount = m_TotalScore;
						//状態変更
						m_State = 101;

					}

					//スキップ
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 101;
					}

					//Totalスコア更新
					dynamic_pointer_cast<NumberSprite>(m_TotalScoreSp)->SetNum(m_TotalAmount);

				}
				break;
			case 101:
				if (true)
				{
					//スコア変更
					m_TotalAmount = m_TotalScore;

					//ランク作成
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

					//透明度リセット
					m_RankAlpha = 0;

					//Totalスコア更新
					dynamic_pointer_cast<NumberSprite>(m_TotalScoreSp)->SetNum(m_TotalAmount);

					//状態更新
					m_State = 11;
				}
				break;
				//ランク表示
			case 11:
				if (true)
				{
					//実体化してく
					m_RankAlpha += App::GetApp()->GetElapsedTime();

					//ランクの大きさ
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

					//ある程度小さくなったら
					if (sca.x < 300)
					{
						m_State = 111;
					}

					//スキップ
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || KeylVec.m_bPressedKeyTbl['B'])
					{
						m_State = 111;
					}

					//透明度更新
					m_RankSp->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_RankAlpha));
					//大きさ更新
					m_RankSp->GetComponent<Transform>()->SetScale(sca);
				}
				break;
			case 111:
				if (true)
				{

					//ランクの大きさ
					Vector3 sca = m_RankSp->GetComponent<Transform>()->GetScale();

					//大きさ固定
					sca.x = 300;
					sca.y = 300;
					sca.z = 1;
					//状態変更
					m_State = 12;

					//時間リセット
					m_time = 0;

					//白い画像出す
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

					//透明度設定
					m_BlackAlpha = 1;
					m_RankAlpha = 1;


					//Abe20170622
					//得点シーンに登録
					auto ScenePtr = App::GetApp()->GetScene<Scene>();
					ScenePtr->SetStageScore(m_TotalScore);
					//Abe20170622

					//透明度更新
					m_RankSp->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_RankAlpha));
					//大きさ更新
					m_RankSp->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//しばらく待つ
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

					//スキップ
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
					//状態変更
					m_State = 13;

					//黒幕ランクの下に出す
					//暗転幕作成
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
				//黒幕半透明にしてランクを上に移動
			case 13:
				if (true)
				{
					//暗幕
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

					//移動
					Vector3 pos = m_RankSp->GetComponent<Transform>()->GetPosition();
					pos.y += 300 * App::GetApp()->GetElapsedTime();
					if (pos.y > 150)
					{
						//高さ固定
						pos.y = 150;

						//状態移動
						m_State = 14;
					}
					m_RankSp->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//選択肢出す
			case 14:
				if (true)
				{
					//状態変更
					m_State = 15;

					//選択肢作成
					//次のステージへ
					auto obj = GetStage()->AddGameObject<GameObject>();
					auto Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-400, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					auto Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTNEXTSTAGELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//リトライ
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(-150, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTRETRYLOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//ステセレ
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(150, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTSTASELELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//タイトル
					obj = GetStage()->AddGameObject<GameObject>();
					Trans = obj->AddComponent<Transform>();
					Trans->SetPosition(450, -120, 0);
					Trans->SetScale(300, 150, 1);
					Trans->SetRotation(0, 0, 0);

					Draw = obj->AddComponent<PCTSpriteDraw>();
					Draw->SetTextureResource(L"RESULTTITLELOGO_TX");

					obj->SetDrawLayer(15);
					obj->SetAlphaActive(true);

					//カーソル作成------------------------------------
					auto CursorSprite = GetStage()->AddGameObject<GameObject>();
					//座標
					auto CTrans = CursorSprite->AddComponent<Transform>();
					CTrans->SetPosition(-400, -160, 0);
					CTrans->SetScale(180, 50, 1);
					CTrans->SetRotation(0, 0, 0);

					//描画
					auto CDraw = CursorSprite->AddComponent<PCTSpriteDraw>();
					CDraw->SetTextureResource(L"SELECT_CURSOR_TX");

					//レイヤー設定
					CursorSprite->SetDrawLayer(16);

					//透明度有効化
					CursorSprite->SetAlphaActive(true);

					m_Cursor = CursorSprite;

					//音鳴らす準備
					m_SelectSe = ObjectFactory::Create<MultiAudioObject>();
					m_SelectSe->AddAudioResource(L"CURSORMOVE_SE");

				}
				break;
				//選択
			case 15:
				if (true)
				{
					//コントローラ取得
					if (CntlVec[0].bConnected)
					{
						//カーソル動かす処理
						if (m_MoveFlg)
						{
							//右
							if (CntlVec[0].fThumbLX > 0.5f)
							{
								m_SelectNum++;
								if (m_SelectNum > 3)
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
									m_SelectNum = 3;
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
						//ずっと動けないように
						else
						{
							if (abs(CntlVec[0].fThumbLX) < 0.5f && abs(CntlVec[0].fThumbLX) > -0.5f)
							{
								m_MoveFlg = true;
							}
						}

						//Aボタン押されたら移動
						if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
						{
							//状態変更
							m_State = 16;

							//音鳴らす
							m_KetteiSe = ObjectFactory::Create<MultiAudioObject>();
							m_KetteiSe->AddAudioResource(L"DECIDE_SE");
							m_KetteiSe->Start(L"DECIDE_SE", 0.5f);

							//切り替え演出
							auto ob = GetStage()->AddGameObject<SceneChangeSS>();
							ob->OnAnim();
							ob->SetLayer(17);
						}
					}
				}
				break;
				//遷移
			case 16:
				if (true)
				{
					switch (m_SelectNum)
					{
						//次のステージへ
					case 0:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							int num = ScenePtr->GetStageNum();
							num++;
							//ステージ番号ごとに大きさ変える
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
							//CSVに設定
							ScenePtr->SetCsvStageNum(Util::IntToWStr(num));
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//リトライ
					case 1:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
						}
						break;
						//ステセレ
					case 2:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
						}
						break;
						//タイトル
					case 3:
						if (true)
						{
							auto ScenePtr = App::GetApp()->GetScene<Scene>();
							PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleScene");
						}
						break;
					}

					//状態変更
					m_State = 17;
				}
				break;
				//待機
			case 17:
				break;
			}
		}



		//チュートリアル用
#pragma region チュートリアル用
		if (m_TutorialFlg)
		{
			switch (m_State)
			{
				//しばらく待つ
			case 0:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > m_1WaitTime)
					{
						//状態変更
						m_State = 1;

						//時間初期化
						m_time = 0;

						//カメラ停止
						dynamic_pointer_cast<TutorialScene>(GetStage())->CameraStop();

						GetStage()->GetSharedGameObject<TutorialPlayerS>(L"TutorialPlayerS", false)->DontMove();
					}
				}
				break;
				//カメラを近づける＋キャラを近づける
			case 1:
				if (true)
				{
					//カメラ動いてるフラグ
					bool flg1 = false;
					//カメラを移動して目標地点に近いか判定
					if (dynamic_pointer_cast<TutorialScene>(GetStage())->ResultCamera(m_centerPos))
					{
						flg1 = true;
					}

					//プレイヤーを目的地に移動
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

					//近ければ判定用のフラグをtrueにし、遠ければ近づける
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
						//状態変更
						m_State = 2;
					}
				}
				break;
				//キャラを手前に向かせる
			case 2:
				if (true)
				{
					//回転
					Vector3 rot1 = m_Player1->GetComponent<Transform>()->GetRotation();
					Vector3 rot2 = m_Player2->GetComponent<Transform>()->GetRotation();
					rot1.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();
					rot2.y += 180 * 3.14159265f / 180 * App::GetApp()->GetElapsedTime();

					//なんか変なとこで違う軸が回転するからそれ止める
					rot1 = Vector3(0, rot1.y, 0);
					rot2 = Vector3(0, rot2.y, 0);
					//大体手前が1.6くらい
					if (rot1.y >= 1.4f && rot1.y <= 1.8f)
					{
						//回転固定
						rot1.y = 90 * 3.14159265f / 180;
						rot2.y = 90 * 3.14159265f / 180;

						//状態変更
						m_State = 3;
						//跳ねる力設定
						float m_HopPower = 10;

						//跳ねるフラグオン
						m_HopFlg = true;

					}
					m_Player1->GetComponent<Transform>()->SetRotation(rot1);
					m_Player2->GetComponent<Transform>()->SetRotation(rot2);

				}
				break;
				//跳ねる
			case 3:
				if (true)
				{
					//状態変更
					m_State = 4;

					//ミッションコンプリート文字作成
					//暗転幕作成
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
				//ミッションコンプリート文字左から出す
			case 4:
				if (true)
				{
					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();

					//中心まで来たら
					if (pos.x > 0)
					{
						//暗転幕作成
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

						//座標固定
						pos.x = 0;

						//状態変更
						m_State = 5;
					}

					//座標移動
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
				}
				break;
				//ちょっと暗くする
			case 5:
				if (true)
				{
					if (m_BlackAlpha < 0.5f)
					{
						m_BlackAlpha += App::GetApp()->GetElapsedTime();
					}
					else
					{
						//透明度固定
						m_BlackAlpha = 0.5f;
						//状態変更
						m_State = 6;
					}
					m_Black->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_BlackAlpha));

				}
				break;
				//ミッションコンプリート小さくして上に移動
			case 6:
				if (true)
				{
					//ミッションコンプリートの座標持ってくる
					Vector3 pos = m_MissCompLogo->GetComponent<Transform>()->GetPosition();
					if (pos.y < 200)
					{
						pos.y += 600 * App::GetApp()->GetElapsedTime();
					}

					//大きさ持ってくる
					Vector3 sca = m_MissCompLogo->GetComponent<Transform>()->GetScale();
					if (sca.x > 1200)
					{
						sca.x *= 0.95f;
						sca.y *= 0.95f;
					}

					if (pos.y > 200 && sca.x <= 1200)
					{
						//状態変更
						m_State = 7;
						m_time = 0;
					}

					//座標と大きさ更新
					m_MissCompLogo->GetComponent<Transform>()->SetPosition(pos);
					m_MissCompLogo->GetComponent<Transform>()->SetScale(sca);

				}
				break;
				//しばらく待つ
			case 7:
				if (true)
				{
					m_time += App::GetApp()->GetElapsedTime();
					if (m_time > 2.0f)
					{
						m_State = 8;
						//切り替え演出
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(17);
					}
				}
				break;
				//ステセレに移動
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
			//跳ねるフラグが立ってたらぴょんぴょん
			if (m_HopFlg)
			{
				if (m_HopTime > m_1WaitTime)
				{
					//キャラの座標持ってくる
					Vector3 pos1 = m_Player1->GetComponent<Transform>()->GetPosition();
					Vector3 pos2 = m_Player2->GetComponent<Transform>()->GetPosition();

					//位置動かす
					pos1.y += m_HopPower * App::GetApp()->GetElapsedTime();
					pos2.y += m_HopPower *App::GetApp()->GetElapsedTime();
					m_Player1->GetComponent<Transform>()->SetPosition(pos1);
					m_Player2->GetComponent<Transform>()->SetPosition(pos2);

					//跳ねる力を減衰させる
					m_HopPower += -9.8f * App::GetApp()->GetElapsedTime() * 3;
					//ある程度下がったらもっかい跳ねる力を加える
					if (pos1.y < 1.0f)
					{
						//跳ねる力加える
						m_HopPower = 10;
						//計算用待機時間をリセット
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
	//	ポーズ
	//--------------------------------------------------------------------------------------
	void PauseMenu::OnCreate()
	{
		//-----生成------
		//ゲームに戻る
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
		//リトライ
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
		//ステセレ
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
		//タイトル
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
		//エネミーの数
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

		//数字
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

		//ポーズロゴ
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
		//暗転
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

		//起動バグ修正用
		m_StartPushFlg = true;

		//アップデート停止
		SetUpdateActive(false);
	}

	void PauseMenu::OnUpdate()
	{
		//コントローラ取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//カーソル動かす処理
			if (m_MoveFlg)
			{
				//下
				if (CntlVec[0].fThumbLY < -0.5f)
				{
					m_SelectNum++;
					if (m_SelectNum > 3)
					{
						m_SelectNum = 0;
					}
					//動けるフラグ止める
					m_MoveFlg = false;

				}
				//上
				if (CntlVec[0].fThumbLY > 0.5f)
				{
					m_SelectNum--;
					if (m_SelectNum < 0)
					{
						m_SelectNum = 3;
					}
					//動けるフラグ止める
					m_MoveFlg = false;
				}

				if (!m_MoveFlg)
				{
					//移動
					switch (m_SelectNum)
					{
						//ゲームに戻る
					case 0:
						m_ToGame->GetComponent<Transform>()->SetPosition(-350, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//リトライ
					case 1:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-350, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//ステセレ
					case 2:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-350, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
						break;
						//タイトル
					case 3:
						m_ToGame->GetComponent<Transform>()->SetPosition(-450, 100, 0);
						m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
						m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
						m_ToTitle->GetComponent<Transform>()->SetPosition(-350, -200, 0);
						break;
					}
				}

			}
			//ずっと動けないように
			else
			{
				if (abs(CntlVec[0].fThumbLY) < 0.5f && abs(CntlVec[0].fThumbLY) > -0.5f)
				{
					m_MoveFlg = true;
				}
			}

			//ボタン押されたら
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				switch (m_SelectNum)
				{
					//戻る
				case 0:
					Close();
					break;
					//リトライ
				case 1:
					if (true)
					{
						//切り替え演出
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(10);

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
					}
					break;
					//ステセレ
				case 2:
					if (true)
					{
						//切り替え演出
						auto ob = GetStage()->AddGameObject<SceneChangeSS>();
						ob->OnAnim();
						ob->SetLayer(10);

						auto ScenePtr = App::GetApp()->GetScene<Scene>();
						PostEvent(2.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelectScene");
					}
					break;
					//タイトル
				case 3:
					if (true)
					{				
						//切り替え演出
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
		//ポーズオブジェ表示
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

		//アップデート起動
		SetUpdateActive(true);

		//全部の動くオブジェクトを止める
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//アタリ判定止める
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(false);
		}
		//プレイヤーを止める
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(false);
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(false);

		//プレイヤー管理してるやつ止める
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

		//全部止める
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

		//敵の数取得
		//まず初期化
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

		//数字(見た目)設定
		dynamic_pointer_cast<NumberSprite>(m_TackleSp)->SetNum(m_TackleCount);
		dynamic_pointer_cast<NumberSprite>(m_ShotSp)->SetNum(m_ShotCount);
		dynamic_pointer_cast<NumberSprite>(m_TerepoSp)->SetNum(m_TereportCount);
		dynamic_pointer_cast<NumberSprite>(m_BombSp)->SetNum(m_BombCount);

	}

	void PauseMenu::Close()
	{
		//ポーズオブジェ非表示
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

		//アップデート停止
		SetUpdateActive(false);

		//位置更新
		m_ToGame->GetComponent<Transform>()->SetPosition(-350, 100, 0);
		m_ToRetry->GetComponent<Transform>()->SetPosition(-450, 0, 0);
		m_ToSteSele->GetComponent<Transform>()->SetPosition(-450, -100, 0);
		m_ToTitle->GetComponent<Transform>()->SetPosition(-450, -200, 0);
		//選択番号リセット
		m_SelectNum = 0;

		//全部の動くオブジェクトを動かす
		auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
		auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
		auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
		auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
		auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
		//アタリ判定動かす
		auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
		if (colmanptr)
		{
			colmanptr->SetUpdateActive(true);
		}

		//プレイヤーを動かす
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(true);
		GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(true);

		//プレイヤー管理してるやつ動かす
		GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(true);

		//全部動かす
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
	//　プレイヤーABUTTON話してぶつかった時のエフェクト
	//	分割ざまーーーーーーす
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

		//透明処理
		SetAlphaActive(true);
		SetDrawActive(false);

		SetDrawLayer(5);
		//画像分割

		//スプライトの数リセット
		m_SpriteNum = -1;
		//3x3
		//ます数
		Vector2 TexSize = Vector2(3, 3);

		//画像作成-------------------------
		for (int i = 0; i < TexSize.x * TexSize.y; i++)
		{
			m_SpriteNum++;
			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//UV値の変更
			float fromX = (i % (int)(TexSize.x)) / TexSize.x;
			float toX = fromX + (1.0f / TexSize.x);
			float fromY = (int)(i / TexSize.x) / TexSize.y;
			float toY = fromY + (1.0f / TexSize.y);
			//左上頂点
			vertices[0].textureCoordinate = Vector2(fromX, fromY);
			//右上頂点
			vertices[1].textureCoordinate = Vector2(toX, fromY);
			//左下頂点
			vertices[2].textureCoordinate = Vector2(fromX, toY);
			//右下頂点
			vertices[3].textureCoordinate = Vector2(toX, toY);
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
			m_SpriteS.push_back(MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true));
		}
		//画像作成-------------------------
		Draw->SetMeshResource(m_SpriteS[0]);

	}
	void ButukariEf::OnUpdate()
	{
		//画像遷移
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > m_IntervalTime)
		{
			m_time = 0;
			GetComponent<PCTStaticDraw>()->SetMeshResource(m_SpriteS[m_NowSpriteNum++]);

			//もし分割数より多かったら
			if (m_NowSpriteNum > m_SpriteNum)
			{
				m_NowSpriteNum = 0;
				SetUpdateActive(false);
				SetDrawActive(false);

				//あと位置調整
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
	//　始まる演出
	//************************************
	void StartState::OnCreate()
	{
		//スタートロゴ作成
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

		//ステージロゴ作成
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

		//数字作成
		auto nump = GetStage()->AddGameObject<NumberSprite>(0,Vector2(-600,200),Vector2(100,100) , 7);
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		nump->SetNum(ScenePtr->GetStageNum());
		m_NumSp = nump;
	}

	void StartState::OnUpdate()
	{
		//初期起動
		if (m_Init)
		{
			//Abe20170620
			//ブースト切る
			GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_R", false)->Stop();
			GetStage()->GetSharedGameObject<KetsuHunsya>(L"Ketu_L", false)->Stop();
			//Abe20170620


			m_Init = false;
			//全部の動くオブジェクトを止める
			auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
			auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
			auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
			auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
			auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
			//アタリ判定止める
			auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
			if (colmanptr)
			{
				colmanptr->SetUpdateActive(false);
			}
			//プレイヤーを止める
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(false);
			GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(false);

			//プレイヤー管理してるやつ止める
			GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", false)->SetUpdateActive(false);

			//全部止める
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

		//動く
		switch (m_State)
		{
			//右からステージと番号来る
			case 0:
				if (true)
				{
					//ロゴ
					Vector3 pos = m_StageLogo->GetComponent<Transform>()->GetPosition();
					pos.x += 1000 * App::GetApp()->GetElapsedTime();
					m_StageLogo->GetComponent<Transform>()->SetPosition(pos);

					//数字
					m_NumSp->MoveNums(Vector3(1000 * App::GetApp()->GetElapsedTime(), 0, 0));

					if (pos.x > 0)
					{
						m_State = 1;
						m_time = 0;
					}
				}
				break;
				//ちょっと待つ
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
				//中心にスタートロゴ出して透明にしてく
			case 2:
				if (true)
				{
					//実体化
					m_Alpha += 1.0f * App::GetApp()->GetElapsedTime();
					m_StartLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, m_Alpha));
					
					m_StageLogo->GetComponent<PCTSpriteDraw>()->SetDiffuse(Color4(1, 1, 1, 1 - m_Alpha));

					//小さく
					Vector3 sca = m_StartLogo->GetComponent<Transform>()->GetScale();
					sca *= 1.05f;
					m_StartLogo->GetComponent<Transform>()->SetScale(sca);

					//文字どっか飛ばす
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
				//終了
			case 3:
				if (true)
				{
					m_State = 4;
					//全部の動くオブジェクトを動かす
					auto ColGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup")->GetGroupVector();
					auto EnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup")->GetGroupVector();
					auto BombGroup = GetStage()->GetSharedObjectGroup(L"BombGroup")->GetGroupVector();
					auto SearchChildGroup = GetStage()->GetSharedObjectGroup(L"SearchChildGroup")->GetGroupVector();
					auto UgokuGroup = GetStage()->GetSharedObjectGroup(L"UgokuGroup")->GetGroupVector();
					//アタリ判定動かす
					auto colmanptr = GetStage()->GetSharedGameObject<CollisionManager>(L"CollisionManager", false);
					if (colmanptr)
					{
						colmanptr->SetUpdateActive(true);
					}

					//プレイヤーを動かす
					GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_L")->SetUpdateActive(true);
					GetStage()->GetSharedGameObject<GameObject>(L"GamePlayer_R")->SetUpdateActive(true);

					//プレイヤー管理してるやつ動かす
					GetStage()->GetSharedGameObject<PlayerControl>(L"PlayerControl", true)->SetUpdateActive(true);

					//全部動かす
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
	//	噴射
	//　勝手にプレイヤーを見てケツに噴射する
	//**************************************************************************************
	void KetsuHunsya::OnCreate()
	{
		//一応初期化
		m_states = "Stop";

		//パラメータ----
		//生成量
		m_Amount = 2;
		//生成感覚
		m_intervaltime = 0.05f;
		//計算用
		m_time = 0;
		//スピード
		m_Speed = 3;
		//大きさ
		m_Size = 0.5f;
		//--------------

		//スクエア
		m_SquareS.clear();
		//移動速度
		m_Velocity.clear();

		//一応
		AddComponent<Transform>();

		////デバッグ文字生成
		//m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		//m_Debugtxt->SetLayer(10);
		////色黒に変更
		//m_Debugtxt->SetColor(Vector3(0, 0, 0));
		////大きさ変更
		//m_Debugtxt->SetScaleTxt(40);

	}

	void KetsuHunsya::OnUpdate()
	{
		//移動
		UpdateSquareS();

		
		//止める状態
		if (m_states == "Stop")
		{

		}
		else
		{
			//時間計測
			m_time += App::GetApp()->GetElapsedTime();

			//生成するか
			bool CreFlg = false;
			//生成量
			float CreAmount = 0;
			//サイズ
			float size = m_Size;
			//スピード
			float speed = m_Speed;
			//通常
			if (m_states == "Normal")
			{
				if (m_time > m_intervaltime)
				{
					//時間リセット
					m_time = 0;
					//生成するフラグオン
					CreFlg = true;
					//生成数設定
					CreAmount = m_Amount;
					
				}
			}

			//ブースト
			if (m_states == "Boost")
			{
				//時間半分
				if (m_time > m_intervaltime * 0.2f)
				{
					//時間リセット
					m_time = 0;
					//生成するフラグオン
					CreFlg = true;
					//生成数設定
					CreAmount = m_Amount * 2;
					size *= 2.0f;
					speed *= 3.0f;
				}
			}

			//生成
			if (CreFlg)
			{
				Vector3 pos = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetPosition();
				//ちょい上
				pos.y += 0.3f;
				for (int i = 0; i < CreAmount; i)
				{
					int count = 0;
					for (auto obj : m_SquareS)
					{
						if (!obj->GetDrawActive())
						{
							i++;

							//速度設定
							float angle = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetRotation().y;
							if (angle == 0 || angle == 90 || angle == 180 || angle == 270)
							{
								angle += 1 * 3.14159265f / 180;
							}
							//ケツに出すので角度反転しないとだけど元から逆になってるのでそのまま使う
							//と思ったけどなんだこれ
							angle += 180 * 3.14159265f / 180;
							angle *= -1;
							Vector3 vel = Vector3(cos(angle), 0, sin(angle)) * speed;

							//ちょいランダムに
							//ブレ幅は -1.0～-1.0
							Vector3 randvec3 = Vector3((rand() % 20) - 10, (rand() % 10) - 5, (rand() % 20) - 10) / 10;
							//増やす
							if (m_states == "Boost")
							{
								randvec3 = Vector3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5) / 10;
							}
							vel += randvec3 * speed;

							m_Velocity[count] = vel;

							//出して大きさと位置設定
							m_SquareS[count]->SetDrawActive(true);
							Vector3 pos2 = Vector3(cos(angle) + ((rand() % 100) - 50) / 100, 0, sin(angle) + ((rand() % 100) - 50) / 100);
							m_SquareS[count]->GetComponent<Transform>()->SetPosition(pos + pos2);
							m_SquareS[count]->GetComponent<Transform>()->SetScale(size, size, size);

							continue;
						}
						count++;
					}


					//速度設定
					float angle = GetStage()->GetSharedGameObject<GameObject>(m_SharedName, false)->GetComponent<Transform>()->GetRotation().y;
					if (angle == 0 || angle == 90 || angle == 180 || angle == 270)
					{
						angle += 1 * 3.14159265f / 180;
					}
					//ケツに出すので角度反転しないとだけど元から逆になってるのでそのまま使う
					//と思ったけどなんだこれ
					angle += 180 * 3.14159265f / 180;
					angle *= -1;
					Vector3 vel = Vector3(cos(angle), 0, sin(angle)) * speed;

					//ちょいランダムに
					//ブレ幅は -1.0～-1.0
					Vector3 randvec3 = Vector3((rand() % 20) - 10, (rand() % 10) - 5, (rand() % 20) - 10) / 10;
					vel += randvec3 * speed;

					m_Velocity.push_back(vel);


					//生成
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
				//位置移動
				Vector3 pos = m_SquareS[i]->GetComponent<Transform>()->GetPosition();
				pos += m_Velocity[i] * App::GetApp()->GetElapsedTime();
				m_SquareS[i]->GetComponent<Transform>()->SetPosition(pos);

				//大きさ変更
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
	//	スコア出す
	//	とりあえず開いたときに読む、保存はしないめんどい
	//とりあえずレイヤーは10から設定
	//**************************************************************************************
	void ScoreDisplay::OnCreate()
	{
		int layer = 10;

		//数字作成x5
		for (int i = 0; i < 5; i++)
		{
			auto numSp = GetStage()->AddGameObject<NumberSprite>(0, Vector2(430,110 + (i*-75)), Vector2(50,50), layer+1);
			m_NumSps.push_back(numSp);
		}

		//ランク作成
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

		//横棒作成
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

		//デバッグ文字生成
		m_Debugtxt = GetStage()->AddGameObject<DebugTxt>();
		m_Debugtxt->SetLayer(10);
		//色黒に変更
		m_Debugtxt->SetColor(Vector3(1, 1, 1));
		//大きさ変更
		m_Debugtxt->SetScaleTxt(40);

		//消す、めんどいから関数呼ぶ
		Delete();
		
	}

	//表示(引数はステージ番号)
	void ScoreDisplay::Disp(int stagenum)
	{
		auto SceneP = App::GetApp()->GetScene<Scene>();

		/* デバッグ表示用
		//配列
		int arr[5] = { 0 };

		wstring txt;
		for (int i = 0; i < 5; i++)
		{
			arr[i] = SceneP->GetStageScore(stagenum,i);
			txt += Util::IntToWStr(arr[i]) + L"\n";
		}

		m_Debugtxt->SetText(txt);
		*/

		//表示

		//数字変更と表示判断
		for (int i = 0; i < 5; i++)
		{
			int innum = SceneP->GetStageScore(stagenum, i);

			//スコアに入ってる数字が0じゃなければ入れて表示
			if (innum != 0)
			{
				auto numP = dynamic_pointer_cast<NumberSprite>(m_NumSps[i]);
				//数字更新
				numP->SetNum(innum);
				//表示
				numP->SetNumDraw(true);

				//あとランクも計算して出す
				//************************
				//TotalMax:10000
				//S:10000 ~7000
				//A:7000 ~5000
				//B:5000 ~3000
				//C:3000 ~0
				//************************* 
				//まず表示
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
			//0入ってれば横線出す
			else
			{
				m_Yokosen[i]->SetDrawActive(true);
			}
		}
	}

	//消し
	void ScoreDisplay::Delete()
	{
		//いろいろ表示消す
		//数字
		for (auto obj : m_NumSps)
		{
			dynamic_pointer_cast<NumberSprite>(obj)->SetNumDraw(false);
		}
		//ランク
		for (auto obj : m_RankSps)
		{
			obj->SetDrawActive(false);
		}
		//横線
		for (auto obj : m_Yokosen)
		{
			obj->SetDrawActive(false);
		}
	}

	//Abe20170622


}
	//end basecross
