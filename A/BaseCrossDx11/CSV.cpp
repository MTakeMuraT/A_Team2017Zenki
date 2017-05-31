#include "stdafx.h"
#include "Project.h"

namespace basecross {
	InputCSV::InputCSV(const shared_ptr<Stage>& StagePtr) :
	GameObject(StagePtr)
	{}
	InputCSV::~InputCSV(){}
	void InputCSV::OnCreate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		
		auto PtrEnemyGroup = GetStage()->GetSharedObjectGroup(L"EnemyGroup");
		auto PtrCollisionGroup = GetStage()->GetSharedObjectGroup(L"CollisionGroup");
		auto PtrTereportGroup = GetStage()->GetSharedObjectGroup(L"TereportPointGroup");
		auto PtrBomGroup = GetStage()->GetSharedObjectGroup(L"BombGroup");
		// CSVフォルダの指定
		wstring CsvMediaPath = App::GetApp()->m_wstrRelativeDataPath + L"CSV\\";
		wstring CsvFileName = CsvMediaPath + L"Stage";
		CsvFileName += App::GetApp()->GetScene<Scene>()->GetCsvStageNum();
		CsvFileName += L".csv";
		//wstring CsvFileName2 = CsvMediaPath + L"Stage2.csv";
		CsvFile GameStageCsv(CsvFileName);
		//CsvFile GameStageCsv(CsvFileName2);
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
		//消す
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
					SinglePos(Tokens),BranchScale(Tokens, Tokens2), BranchHP(Tokens, Tokens2),
					BranchSearch(Tokens, Tokens2), BranchCoolTime(Tokens, Tokens2), BranchSpeed(Tokens, Tokens2),
					BranchAttackPower(Tokens, Tokens2), BranchAttackTimes(Tokens, Tokens2));
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
				auto PtrShotEnemy = GetStage()->AddGameObject<ShotEnemy>(SinglePos(Tokens),BranchScale(Tokens, Tokens2),
					BranchHP(Tokens, Tokens2), BranchSearch(Tokens, Tokens2), BranchShotCoolTime(Tokens, Tokens2),
					BranchAttackPower(Tokens, Tokens2), BranchChildDrop(Tokens,Tokens2), BranchShotBullet(Tokens,Tokens2));
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
					SinglePos(Tokens), BranchScale(Tokens,Tokens2), BranchHP(Tokens,Tokens2),
					BranchSearch(Tokens, Tokens2), BranchCoolTime(Tokens, Tokens2), BranchChildSearch(Tokens, Tokens2)
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
					SinglePos(Tokens), BranchScale(Tokens,Tokens2), BranchHP(Tokens,Tokens2),
					BranchSearch(Tokens, Tokens2), BranchSpeed(Tokens, Tokens2), BranchAttackPower(Tokens, Tokens2));
				PtrEnemyGroup->IntoGroup(PtrBombEnemy);
				PtrCollisionGroup->IntoGroup(PtrBombEnemy);
				m_Pos = Vector3(0, 0, 0); m_Scale = 0; m_HP = 0; m_Search = 0; m_Speed = 0; m_AttackPower = 0;
			}
#pragma endregion
			GetStage()->AddGameObject<BackgroundModel>(Vector3(0, 0, 0), Vector3(5, 5, 5), 1);
			GetStage()->AddGameObject<BackgroundModel>(Vector3(0, 0, 0), Vector3(7, 7, 7), 2);
	}
#pragma region EnemysSet
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
	int InputCSV::MultiScale(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Scale = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Scale;
	}
	//HP
	
	int InputCSV::MultiHP(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_HP = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_HP;
	}
	//索敵範囲
	int InputCSV::MultiSearch( vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_Search = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Search;
	}
	//クールタイム
	
	int InputCSV::MultiCoolTime( vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		 m_CoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_CoolTime;
	}
	//ショットクールタイム
	int InputCSV::MultiShotCoolTime( vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ShotCoolTime = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ShotCoolTime;
	}
	int InputCSV::MultiSpeed(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_Speed = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_Speed;
	}
	//攻撃力
	int InputCSV::MultiAttackPower(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackPower = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackPower;
	}
	//突撃回数
	int InputCSV::MultiAttackTimes(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_AttackTimes = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_AttackTimes;
	}
	//子機発射間隔
	int InputCSV::MultiChildDrop(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildDrop = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildDrop;
	}
	//索敵型子機の発射間隔  TeleportEnemyのCSV列の12に「索敵型子機」を記述
	int InputCSV::MultiChildSearch(vector<wstring> Tokens2) {
		int m_Min = (float)_wtof(Tokens2[0].c_str());
		int m_Max = (float)_wtof(Tokens2[1].c_str());
		m_ChildSearch = Random((int)m_Min, (int)m_Max);
		Tokens2.clear();
		return m_ChildSearch;
	}
	//発射数（一回で発射される弾の数  ShotEnemyのCSV列の12に「発射数」を記述
	int InputCSV::MultiShotBullet(vector<wstring> Tokens2) {
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
#pragma endregion

#pragma region EnemysSetBranch
	//スケール
	int InputCSV::BranchScale(vector<wstring> Tokens,vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[4].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
		return	MultiScale(Tokens2);
		}
		else {
		return (float)_wtof(TowValue_Str);
		}
	}
	//HP
	int InputCSV::BranchHP(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[5].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiHP(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//索敵範囲
	int InputCSV::BranchSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[6].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiSearch(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//クールタイム
	int InputCSV::BranchCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiCoolTime(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//ショットクールタイム
	int InputCSV::BranchShotCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[7].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiShotCoolTime(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//スピード
	int InputCSV::BranchSpeed(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[8].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiSpeed(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//攻撃力
	int InputCSV::BranchAttackPower(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[9].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiAttackPower(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//突撃回数
	int InputCSV::BranchAttackTimes(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[10].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiAttackTimes(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//子機発射間隔
	int InputCSV::BranchChildDrop(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[11].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiChildDrop(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//索敵型子機の発射間隔
	int InputCSV::BranchChildSearch(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiChildSearch(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}
	//発射数
	int InputCSV::BranchShotBullet(vector<wstring> Tokens, vector<wstring> Tokens2) {
		auto TowValue_Str = Tokens[12].c_str();
		Util::WStrToTokenVector(Tokens2, TowValue_Str, L':');
		if (Tokens2.size() == 2) {
			return	MultiShotBullet(Tokens2);
		}
		else {
			return (float)_wtof(TowValue_Str);
		}
	}

#pragma endregion

}