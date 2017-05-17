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
		auto PtrTereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto PtrBomGroup = GetStage()->GetSharedObjectGroup(L"BombGroup");
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
//各エネミー読み込み
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
#pragma region ShotEnemy
		//ショットエネミー
		GameStageCsv.GetSelect(LineVec, 0, L"ShotEnemy");
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
			int m_Scale = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//HP 値の分割処理
			TowValue_Str = Tokens[5].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_HP = Random((int)m_Min, (int)m_Max);
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
			int m_ShotCoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//攻撃力
			TowValue_Str = Tokens[9].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_AttackPower = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//子機発射
			TowValue_Str = Tokens[11].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_ChildDrop = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//弾発射数
			int m_ShotBullet = (float)_wtof(Tokens[1].c_str());
			//各値がそろったのでオブジェクト作成                       位置、大きさ、HP、索敵距離、クールタイム、攻撃力、子機発射間隔、発射数
			auto PtrShotEnemy = GetStage()->AddGameObject<ShotEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_ShotCoolTime, m_AttackPower, m_ChildDrop , m_ShotBullet);
			PtrEnemyGroup->IntoGroup(PtrShotEnemy);
			PtrCollisionGroup->IntoGroup(PtrShotEnemy);
			m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_ShotCoolTime = 0;  m_AttackPower = 0; m_ChildDrop = 0; m_ShotBullet = 0;
		}
		LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
		//テレポートポイント
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, v, L',');

			//位置
			Vector3 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
		}
		LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
		//テレポートエネミー
		GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
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
			//クールタイム
			TowValue_Str = Tokens[7].c_str();
			Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
			m_Min = (float)_wtof(Tokens2[0].c_str());
			m_Max = (float)_wtof(Tokens2[1].c_str());
			int m_CoolTime = Random((int)m_Min, (int)m_Max);
			Tokens2.clear();
			//子機発射
			int m_ChildSearch = (float)_wtof(Tokens[12].c_str());
			//各値がそろったのでオブジェクト作成 
			auto A = GetStage()->AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3));
			PtrTereportGroup->IntoGroup(A);                     // 位置、大きさ、HP、索敵距離、クールタイム、発射数
		//	m_Pos.y = 1.0f;
			auto PtrTeleportEnemy = GetStage()->AddGameObject<TeleportEnemy>(m_Pos, m_Scale, m_HP, m_Search, m_CoolTime, m_ChildSearch);
			PtrEnemyGroup->IntoGroup(PtrTeleportEnemy);
			PtrCollisionGroup->IntoGroup(PtrTeleportEnemy);
			
			m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0;  m_ChildSearch = 0;
		}
		LineVec.clear();
#pragma endregion
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


}