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
		//シングルだったときのリターンと複数値が入ってるときのランダムリターン
#pragma region EnemysSet
		//エネミーへの代入用セッタ
		//位置 Single:値が１つだけのときに使用　　Multi：複数の値が入ってる時のランダムリターン
		Vector3  SinglePos(vector<wstring> Tokens);
		//スケール
		int MultiScale(vector<wstring> Tokens2);
		//HP
		int MultiHP( vector<wstring> Tokens2);
		//索敵範囲
		int MultiSearch( vector<wstring> Tokens2);
        //クールタイム
		int MultiCoolTime( vector<wstring> Tokens2);
		//ショットクールタイム（弾の撃つ間隔 使用箇所　ShotEnemy
		int MultiShotCoolTime( vector<wstring> Tokens2);
		//スピード
		int MultiSpeed( vector<wstring> Tokens2);
		//攻撃力
		int MultiAttackPower( vector<wstring> Tokens2);
		//突撃回数（ 使用箇所 TackleEnemy
		int MultiAttackTimes( vector<wstring> Tokens2);
		//子機発射間隔( 使用箇所　ShotEnemy 
		int MultiChildDrop( vector<wstring> Tokens2);
		//索敵型子機の発射間隔（使用箇所 TeleportEnemy 
		int MultiChildSearch( vector<wstring> Tokens2);
		//発射数（一回で発射される弾の数  
		int MultiShotBullet(vector<wstring> Tokens2);
#pragma endregion
		//値が一つなのか二つなのかを見る関数
#pragma region EnemysSetBranch
		//スケール
		int BranchScale(vector<wstring> Tokens,vector<wstring> Tokens2);
		//HP
		int BranchHP(vector<wstring> Tokens,vector<wstring> Tokens2);
		//索敵範囲
		int  BranchSearch(vector<wstring> Tokens,vector<wstring> Tokens2);
		//クールタイム
		int BranchCoolTime(vector<wstring> Tokens,vector<wstring> Tokens2);
		//ショットクールタイム
		float BranchShotCoolTime(vector<wstring> Tokens,vector<wstring> Tokens2);
		//スピード
		int BranchSpeed(vector<wstring> Tokens,vector<wstring> Tokens2);
		//攻撃力
		int BranchAttackPower(vector<wstring> Tokens,vector<wstring> Tokens2);
		//突撃回数
		int BranchAttackTimes(vector<wstring> Tokens,vector<wstring> Tokens2);
		//子機発射間隔
		int BranchChildDrop(vector<wstring> Tokens,vector<wstring> Tokens2);
		//索敵型子機の発射間隔
		int BranchChildSearch(vector<wstring> Tokens,vector<wstring> Tokens2);
		//発射数
		int BranchShotBullet(vector<wstring> Tokens,vector<wstring> Tokens2);

#pragma endregion


	};

	
}