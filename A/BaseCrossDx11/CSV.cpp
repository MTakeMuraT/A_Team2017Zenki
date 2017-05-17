#include "stdafx.h"
#include "Project.h"

namespace basecross {
	InputCSV::InputCSV(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{}
	InputCSV::~InputCSV(){}
	void InputCSV::OnCreate() {
		auto PtrEnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		auto PtrCollisionGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup");
		// CSVフォルダの指定
		wstring CsvMediaPath = App::GetApp()->m_wstrRelativeDataPath + L"CSV\\";
		wstring CsvFileName = CsvMediaPath + L"Stage1.csv";
		CsvFile GameStageCsv(CsvFileName);
		// ファイルの確認
		if (!GameStageCsv.ReadCsv())
		{
			// ファイルが存在しなかった場合
			throw BaseException(
				L"CSVファイルがありません",
				L"",
				L"選択された場所にアクセスできません"
			);
		}
		//最初の名前分数を入れる
		vector<wstring> LineVec;
#pragma region TackleEnemyCSV
		GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');

			//位置
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//スケール
			vector<wstring> Tokens2;
			auto TowValue_Str = Tokens[4].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Scale	 = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//HP 値の分割処理
			TowValue_Str = Tokens[5].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_HP = Random((int)m_Min,(int)m_Max);
			Tokens2.clear();
			//サーチ
			TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//クールタイム
			TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_CoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//スピード
			TowValue_Str = Tokens[8].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Speed = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//攻撃力
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//突撃回数
			TowValue_Str = Tokens[10].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackTimes = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//各値がそろったのでオブジェクト作成
			auto PtrTackleEnemy = GetStage()->AddGameObject<TackleEnemy>(m_Pos, m_Scale,m_HP,m_Search, m_CoolTime, m_Speed, m_AttackPower,m_AttackTimes);
			PtrEnemyGroup->IntoGroup(PtrTackleEnemy);
			PtrCollisionGroup->IntoGroup(PtrTackleEnemy);
			m_Pos = Vector3(0,0,0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0; m_Speed = 0; m_AttackPower = 0; m_AttackTimes = 0;
		}
		//初期化
		LineVec.clear();
#pragma endregion

		//ショットエネミー
		GameStageCsv.GetSelect(LineVec, 0, L"ShotEnemy");
		for (auto& v : LineVec) {
	//		GetStage()->AddGameObject<Enemy02>(v);
		}
		LineVec.clear();
		//テレポートエネミー
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
		for (auto& v : LineVec) {
			//GetStage()->AddGameObject<Enemy02>(v);
		}
		LineVec.clear();
#pragma region BombEnemyCSV
		//自爆エネミー
		GameStageCsv.GetSelect(LineVec, 0, L"BombEnemy");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');

			//位置
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
			//スケール
			vector<wstring> Tokens2;
			int m_Scale = (float)_wtof(Tokens[4].c_str());
			//HP 値の分割処理
			int m_HP = (float)_wtof(Tokens[5].c_str());
			//サーチ
			auto TowValue_Str = Tokens[6].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			int m_Min = (float)_wtof(Tokens2[0].c_str());
			int m_Max = (float)_wtof(Tokens2[1].c_str());
			 int m_Search = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//自爆時間
			/*TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_BomTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();*/
			//スピード
			TowValue_Str = Tokens[8].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_Speed = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//攻撃力
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			

			//各値がそろったのでオブジェクト作成
			auto PtrBombEnemy = GetStage()->AddGameObject<BombEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_Speed, m_AttackPower);
			PtrEnemyGroup->IntoGroup(PtrBombEnemy);
			PtrCollisionGroup->IntoGroup(PtrBombEnemy);
			m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_Speed = 0; m_AttackPower = 0;
		}
#pragma endregion



/*

		//トークン（カラム）の配列
		vector<wstring> Tokens;
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		Util::WStrToTokenVector(Tokens, LineVec[i], L',');
		for (size_t j = 0; j < Tokens.size(); j++) {
			//XとZの位置を計算
			float XPos = (float)((int)j - 19);
			float ZPos = (float)(19 - (int)i);
			if (Tokens[j] == L"TackleEnemy") {
					
				//ゲームオブジェクトの生成
				//GetStage()->AddGameObject<Enemy01>(Vector3(),Vector3());
			}
			else if (Tokens[j] == L"ShotEnemy") {
				m_InputFlg_B = true;
				//AddGameObject<Enemy2>(Vector3(XPos, 0.25f, ZPos));

			}
			else if (Tokens[j] == L"TeleportEnemy") {
				m_InputFlg_C = true;
				//AddGameObject<Enemy3>(Vector3(XPos, 0.25f, ZPos));
			}
			else if (Tokens[j] == L"BombEnemy") {
				m_InputFlg_D = true;
			}
		}
*/

	}
	
	int InputCSV::Random(const int Min, const int Max) {
		//ランダムの値変更
		srand((unsigned)time(NULL));
		//ランダム範囲に選択
		int RandNum = rand() %(Max - Min);
		m_RnadNum = RandNum + Min;
		return m_RnadNum;
	}


	TestEnemy::TestEnemy(const shared_ptr<Stage>& PtrStage, const wstring& line):
	GameObject(PtrStage)
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
		m_Pos = Vector3(
			(float)_wtof(Tokens[1].c_str()),
			(float)_wtof(Tokens[2].c_str()),
			(float)_wtof(Tokens[3].c_str())
		);
		//スケール
		TowValue_Str = Tokens[4].c_str();
		vector<wstring> Tokens2;
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		float Mini = (float)_wtof(Tokens2[0].c_str());
		float Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_TowValue_Scale_Str = TowValue_Str;
		Debug_Mini_Scale_F = Mini;
		Debug_Mix_Scale_F = Mix;
		//////////////////////////////////////////////////////////HP
		//値が二つwstringで入っているものの分解処理
		TowValue_Str = Tokens[5].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_TowValue_HP_Str = TowValue_Str;
		Debug_Mini_HP_F = Mini;
		Debug_Mix_HP_F = Mix;
		//////////////////////////////////////////////////////////索敵範囲
		//値が二つwstringで入っているものの分解処理
		TowValue_Str = Tokens[6].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_Search_Str = TowValue_Str;
		Debug_Mini_Search_F = Mini;
		Debug_Mix_Search_F = Mix;
		//////////////////////////////////////////////////////////クールタイム
		TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_CoolTime_Str = TowValue_Str;
		Debug_Mini_CoolTime_F = Mini;
		Debug_Mix_CoolTime_F = Mix;
		//////////////////////////////////////////////////////////速度
		TowValue_Str = Tokens[8].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_Speed_Str = TowValue_Str;
		Debug_Mini_Speed_F = Mini;
		Debug_Mix_Speed_F = Mix;
		//////////////////////////////////////////////////////////攻撃力
		TowValue_Str = Tokens[9].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_Attack_Str = TowValue_Str;
		Debug_Mini_Attack_F = Mini;
		Debug_Mix_Attack_F = Mix;
		//////////////////////////////////////////////////////////突撃回数
		TowValue_Str = Tokens[10].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		Mini = (float)_wtof(Tokens2[0].c_str());
		Mix = (float)_wtof(Tokens2[1].c_str());
		Tokens2.clear();
		//デバック////////////////////////////////////////////////
		Debug_Assault_Str = TowValue_Str;
		Debug_Mini_Assault_F = Mini;
		Debug_Mix_Assault_F = Mix;
		//////////////////////////////////////////////////////////
	}
	void TestEnemy::OnCreate() {
		auto Trans = GetComponent<Transform>();
		Trans->SetScale(m_Scale);
		Trans->SetRotation(0, 0, 0);
		Trans->SetPosition(m_Pos);
		//文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}
	void TestEnemy::OnLastUpdate() {
		wstring PosStr(L"\nPosition:\t");
		
			auto Obj = GetComponent<Transform>()->GetPosition();
			PosStr += L"X=" + Util::FloatToWStr(Obj.x, 6, Util::FloatModify::Fixed) + L",\t";
			PosStr += L"Y=" + Util::FloatToWStr(Obj.y, 6, Util::FloatModify::Fixed) + L",\t";
			PosStr += L"Z=" + Util::FloatToWStr(Obj.z, 6, Util::FloatModify::Fixed) + L"\n";
			
			wstring ScalePtr(L"スケール;\t");
			ScalePtr += Debug_TowValue_Scale_Str;
			ScalePtr += L"\n";
			wstring HPMiniScale(L"最小値:\t");
			HPMiniScale += Util::FloatToWStr(Debug_Mini_Scale_F);
			wstring ScaleMaxStr(L"\t最大値\t");
			ScaleMaxStr += Util::FloatToWStr(Debug_Mix_Scale_F);
			ScaleMaxStr += L"\n";

			wstring HPStr(L"HP:\t");
			HPStr += Debug_TowValue_HP_Str;
			HPStr += L"\n";
			wstring HPMiniStr(L"最小値:\t");
			HPMiniStr += Util::FloatToWStr(Debug_Mini_HP_F);
			wstring HPMaxStr(L"\t最大値\t");
			HPMaxStr += Util::FloatToWStr(Debug_Mix_HP_F);
			HPMaxStr += L"\n";
				
			wstring SearchStr(L"索敵:\t");
			SearchStr += Debug_Search_Str;
			SearchStr += L"\n";
			wstring SearchMiniStr(L"最小値:\t");
			SearchMiniStr += Util::FloatToWStr(Debug_Mini_Search_F);
			wstring SearchMaxStr(L"\t最大値\t");
			SearchMaxStr += Util::FloatToWStr(Debug_Mix_Search_F);
			SearchMaxStr += L"\n";

			wstring CoolTimeStr(L"クールタイム:\t");
			CoolTimeStr += Debug_CoolTime_Str;
			CoolTimeStr += L"\n";
			wstring CoolTimeMiniStr(L"最小値:\t");
			CoolTimeMiniStr += Util::FloatToWStr(Debug_Mini_CoolTime_F);
			wstring CoolTimeMaxStr(L"\t最大値\t");
			CoolTimeMaxStr += Util::FloatToWStr(Debug_Mix_CoolTime_F);
			CoolTimeMaxStr += L"\n";

			wstring SpeedStr(L"速度:\t");
			SpeedStr += Debug_Speed_Str;
			SpeedStr += L"\n";
			wstring SpeedMiniStr(L"最小値:\t");
			SpeedMiniStr += Util::FloatToWStr(Debug_Mini_Speed_F);
			wstring SpeedMaxStr(L"\t最大値\t");
			SpeedMaxStr += Util::FloatToWStr(Debug_Mix_Speed_F);
			SpeedMaxStr += L"\n";

			wstring AttackStr(L"攻撃力:\t");
			AttackStr += Debug_Attack_Str;
			AttackStr += L"\n";
			wstring AttackMiniStr(L"最小値:\t");
			AttackMiniStr += Util::FloatToWStr(Debug_Mini_Attack_F);
			wstring AttackMaxStr(L"\t最大値\t");
			AttackMaxStr += Util::FloatToWStr(Debug_Mix_Attack_F);
			AttackMaxStr += L"\n";

			wstring Debug_AssaultStr(L"突撃回数:\t");
			Debug_AssaultStr += Debug_Assault_Str;
			Debug_AssaultStr += L"\n";
			wstring AssaultMiniStr(L"最小値:\t");
			AssaultMiniStr += Util::FloatToWStr(Debug_Mini_Assault_F);
			wstring AssaultMaxStr(L"\t最大値\t");
			AssaultMaxStr += Util::FloatToWStr(Debug_Mix_Assault_F);
			AssaultMaxStr += L"\n";

		wstring  str = PosStr + ScalePtr + HPMiniScale + ScaleMaxStr + HPStr + HPMiniStr + HPMaxStr + SearchStr + SearchMiniStr + SearchMaxStr
						+ CoolTimeStr + CoolTimeMiniStr + CoolTimeMaxStr + SpeedStr + SpeedMiniStr + SpeedMaxStr + AttackStr + AttackMiniStr + AttackMaxStr
						+ Debug_AssaultStr + AssaultMiniStr + AssaultMaxStr;
						
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}
}