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
		//for (auto& v : LineVec) {
			//各エネミー読み込LineVec
#pragma region TackleEnemyCSV
			GameStageCsv.GetSelect(LineVec, 0, L"TackleEnemy");
			for (auto& v : LineVec) {
				//トークン（カラム）の配列
				vector<wstring> Tokens;
				//複数の値の時に使用
				vector<wstring> Tokens2;
				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, v, L',');		
				//各値がそろったのでオブジェクト作成
				auto PtrTackleEnemy = GetStage()->AddGameObject<TackleEnemy>(
					SinglePos(Tokens), MultiScale(Tokens,Tokens2), MultiHP(Tokens,Tokens2),
					MultiSearch(Tokens,Tokens2), MultiCoolTime(Tokens, Tokens2), MultiSpeed(Tokens, Tokens2), 
					MultiAttackPower(Tokens, Tokens2), MultiAttackTimes(Tokens, Tokens2));
				//グループに入れる
				PtrEnemyGroup->IntoGroup(PtrTackleEnemy);
				PtrCollisionGroup->IntoGroup(PtrTackleEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_CoolTime = 0; m_Speed = 0; m_AttackPower = 0; m_AttackTimes = 0;
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
				//スケール
				vector<wstring> Tokens2;
			
				//各値がそろったのでオブジェクト作成       位置、大きさ、HP、索敵距離、クールタイム、攻撃力、子機発射間隔、発射数
				auto PtrShotEnemy = GetStage()->AddGameObject<ShotEnemy>(SinglePos(Tokens), MultiScale(Tokens,Tokens2), 
					MultiHP(Tokens, Tokens2), MultiSearch(Tokens, Tokens2), MultiShotCoolTime(Tokens, Tokens2),
					MultiAttackPower(Tokens, Tokens2), SingleChildDrop(Tokens), SingleShotBullet(Tokens));
				PtrEnemyGroup->IntoGroup(PtrShotEnemy);
				PtrCollisionGroup->IntoGroup(PtrShotEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_ShotCoolTime = 0;  m_AttackPower = 0; m_ChildDrop = 0; m_ShotBullet = 0;
			}
			LineVec.clear();
#pragma endregion
#pragma region TeleportEnemy
			//テレポートエネミー
			GameStageCsv.GetSelect(LineVec, 0, L"TeleportEnemy");
			for (auto& v : LineVec) {
				//トークン（カラム）の配列
				vector<wstring> Tokens;
				vector<wstring> Tokens2;
				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, v, L',');
				//各値がそろったのでオブジェクト作成 

				//!!!!!!!!!!!!!!!!!!!!!後でここ変更します!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				auto A = GetStage()->AddGameObject<TereportPoint>(Vector3(3, 0.5f, 3));
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				PtrTereportGroup->IntoGroup(A);       // 位置、大きさ、HP、索敵距離、クールタイムM、索敵型子機発射S
				auto PtrTeleportEnemy = GetStage()->AddGameObject<TeleportEnemy>(
					SinglePos(Tokens), SingleScale(Tokens),SingleHP(Tokens), 
					MultiSearch(Tokens,Tokens2), MultiCoolTime(Tokens,Tokens2),SingleChildSearch(Tokens)
					);
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
				vector<wstring> Tokens2;
				//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
				Util::WStrToTokenVector(Tokens, v, L',');
				//各値がそろったのでオブジェクト作成　位置s　大きさs　HPs　索敵m　スピードm　攻撃力m
				auto PtrBombEnemy = GetStage()->AddGameObject<BombEnemy>(
					SinglePos(Tokens), SingleScale(Tokens), SingleHP(Tokens),
					MultiSearch(Tokens,Tokens2), MultiSpeed(Tokens,Tokens2), MultiAttackPower(Tokens,Tokens2));
				PtrEnemyGroup->IntoGroup(PtrBombEnemy);
				PtrCollisionGroup->IntoGroup(PtrBombEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_Speed = 0; m_AttackPower = 0;
			}
#pragma endregion

		//}
	}
	//位置
	Vector3 InputCSV::SinglePos(vector<wstring> Tokens) {
		//トークン（カラム）の配列
		//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
		//Util::WStrToTokenVector(Tokens, v, L',');
		//位置
		 m_Pos = Vector3((float)_wtof(Tokens[1].c_str()), (float)_wtof(Tokens[2].c_str()), (float)_wtof(Tokens[3].c_str()));
		 return m_Pos;
	}
	//スケール
	int InputCSV::SingleScale(vector<wstring> Tokens) {
		m_Scale = (float)_wtof(Tokens[4].c_str());
		return m_Scale;
	}
	int InputCSV::MultiScale(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[4].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Scale = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Scale;
	}
	//HP
	int InputCSV::SingleHP(vector<wstring> Tokens) {
		m_HP = (float)_wtof(Tokens[5].c_str());
		return m_HP;
	}
	int InputCSV::MultiHP(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[5].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_HP = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_HP;
	}
	//索敵範囲
	int InputCSV::SingleSearch(vector<wstring> Tokens) {
		m_Search = (float)_wtof(Tokens[6].c_str());
		return m_Search;
	}
	int InputCSV::MultiSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[6].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Search = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Search;
	}
	//クールタイム
	int InputCSV::SingleCoolTime(vector<wstring> Tokens) {
		m_CoolTime = (float)_wtof(Tokens[7].c_str());
		return m_CoolTime;
	}
	int InputCSV::MultiCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_CoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_CoolTime;
	}
	//ショットクールタイム
	int InputCSV::SingleShotCoolTime(vector<wstring> Tokens) {
		m_ShotCoolTime = (float)_wtof(Tokens[7].c_str());
		return m_ShotCoolTime;
	}
	int InputCSV::MultiShotCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ShotCoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ShotCoolTime;
	}
	//スピード
	int InputCSV::SingleSpeed(vector<wstring> Tokens) {
		m_Speed = (float)_wtof(Tokens[7].c_str());
		return m_Speed;
	}
	int InputCSV::MultiSpeed(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[8].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_Speed = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Speed;
	}
	//攻撃力
	int InputCSV::SingleAttackPower(vector<wstring> Tokens) {
		m_AttackPower = (float)_wtof(Tokens[9].c_str());
		return m_AttackPower;
	}
	int InputCSV::MultiAttackPower(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[9].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackPower = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackPower;
	}
	//突撃回数
	int InputCSV::SingleAttackTimes(vector<wstring> Tokens) {
		m_AttackTimes = (float)_wtof(Tokens[10].c_str());
		return m_AttackTimes;
	}
	int InputCSV::MultiAttackTimes(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[10].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackTimes = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackTimes;
	}
	//子機発射間隔
	int InputCSV::SingleChildDrop(vector<wstring> Tokens) {
		m_ChildDrop = (float)_wtof(Tokens[11].c_str());
		return m_ChildDrop;
	}
	int InputCSV::MultiChildDrop(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[11].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildDrop = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildDrop;
	}
	//索敵型子機の発射間隔  TeleportEnemyのCSV列の12に「索敵型子機」を記述
	int InputCSV::SingleChildSearch(vector<wstring> Tokens) {
		m_ChildSearch = (float)_wtof(Tokens[12].c_str());
		return m_ChildSearch;
	}
	int InputCSV::MultiChildSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildSearch = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildSearch;
	}
	//発射数（一回で発射される弾の数  ShotEnemyのCSV列の12に「発射数」を記述
	int InputCSV::SingleShotBullet(vector<wstring> Tokens) {
		m_ShotBullet = (float)_wtof(Tokens[12].c_str());
		return m_ShotBullet;
	}
	int InputCSV::MultiShotBullet(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ShotBullet = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ShotBullet;
	}
	//指定範囲内でランダム数を返す関数
	int InputCSV::Random(const int Min, const int Max) {
		//ランダムの値変更
		srand((unsigned)time(NULL));
		//ランダム範囲に選択
		int RandNum = rand() %(Max - Min);
		m_RnadNum = RandNum + Min;
		return m_RnadNum;
	}


}