#pragma once
#include"stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Dedug : public GameObject;
	//	用途: ステージシーン　
	//--------------------------------------------------------------------------------------
	class InputCSV : public GameObject {

		//CSVファイルそのA
		CsvFile m_InputCSV;
		//ランダム
		int m_RnadNum;

		//各エネミーへの代入する値メンバー（returnで使用
		//位置
		Vector3 m_Pos = Vector3(0,0,0);
		//スケール
		 int m_Scale = 0;
		//HP
		 int m_HP = 0;
		//サーチ（索敵範囲
		 int m_Search = 0;
		//クールタイム
		 int m_CoolTime = 0;
		//ショットクールタイム（弾の撃つ間隔 使用箇所　ShotEnemy
		 int m_ShotCoolTime = 0;
		//スピード
		 int m_Speed = 0;
		//攻撃力
		 int m_AttackPower = 0;
		//突撃回数（ 使用箇所 TackleEnemy
		 int m_AttackTimes = 0;
		//子機発射間隔( 使用箇所　ShotEnemy
		 int m_ChildDrop = 0;
		//索敵型子機の発射間隔（使用箇所 TeleportEnemy
		 int m_ChildSearch = 0;
		//発射数（一回で発射される弾の数 
		 int m_ShotBullet = 0;
	public:
		//構築と破棄
		InputCSV(const shared_ptr<Stage>& StagePtr);
		virtual ~InputCSV();
		//初期化
		virtual void OnCreate() override;
		//指定範囲内でランダム数を返す関数
		int Random(const int Min, const int Max);
#pragma region EnemysSet
		//エネミーへの代入用セッタ
		//位置 Single:値が１つだけのときに使用　　Multi
		Vector3  SinglePos(vector<wstring> Tokens);
		//スケール
		int SingleScale(vector<wstring> Tokens);
		int MultiScale(vector<wstring> Tokens, vector<wstring> Tokens2);
		//HP
		int SingleHP(vector<wstring> Tokens);
		int MultiHP(vector<wstring> Tokens, vector<wstring> Tokens2);
		//索敵範囲
		int SingleSearch(vector<wstring> Tokens);
		int MultiSearch(vector<wstring> Tokens, vector<wstring> Tokens2);
        //クールタイム
		int SingleCoolTime(vector<wstring> Tokens);
		int MultiCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2);
		//ショットクールタイム（弾の撃つ間隔 使用箇所　ShotEnemy
		int SingleShotCoolTime(vector<wstring> Tokens);
		int MultiShotCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2);
		//スピード
		int SingleSpeed(vector<wstring> Tokens);
		int MultiSpeed(vector<wstring> Tokens, vector<wstring> Tokens2);
		//攻撃力
		int SingleAttackPower(vector<wstring> Tokens);
		int MultiAttackPower(vector<wstring> Tokens, vector<wstring> Tokens2);
		//突撃回数（ 使用箇所 TackleEnemy
		int SingleAttackTimes(vector<wstring> Tokens);
		int MultiAttackTimes(vector<wstring> Tokens, vector<wstring> Tokens2);
		//子機発射間隔( 使用箇所　ShotEnemy 
		int SingleChildDrop(vector<wstring> Tokens);
		int MultiChildDrop(vector<wstring> Tokens, vector<wstring> Tokens2);
		//索敵型子機の発射間隔（使用箇所 TeleportEnemy 
		int SingleChildSearch(vector<wstring> Tokens);
		int MultiChildSearch(vector<wstring> Tokens, vector<wstring> Tokens2);
		//発射数（一回で発射される弾の数  
		int SingleShotBullet(vector<wstring> Tokens);
		int MultiShotBullet(vector<wstring> Tokens, vector<wstring> Tokens2);
#pragma endregion

	};

	
}