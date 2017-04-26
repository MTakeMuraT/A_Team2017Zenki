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
	public:
		//構築と破棄
		InputCSV(const shared_ptr<Stage>& StagePtr);
		virtual ~InputCSV();
		//初期化
		virtual void OnCreate() override;
		//操作
	};


	class TestEnemy : public GameObject {
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scale = Vector3(0, 0, 0);
		wstring TowValue_Str =L"";
		
		//デバック
		//スケール　最小値　最大値
		wstring Debug_TowValue_Scale_Str = L"";
		float Debug_Mini_Scale_F = 0.0f;
		float Debug_Mix_Scale_F = 0.0f;
		//HP　最小値　最大値
		wstring Debug_TowValue_HP_Str = L"";
		float Debug_Mini_HP_F = 0.0f;
		float Debug_Mix_HP_F = 0.0f;
		//索敵範囲
		wstring Debug_Search_Str = L"";
		float Debug_Mini_Search_F = 0.0f;
		float Debug_Mix_Search_F = 0.0f;
		//クールタイプ
		wstring Debug_CoolTime_Str = L"";
		float Debug_Mini_CoolTime_F = 0.0f;
		float Debug_Mix_CoolTime_F = 0.0f;
		//速度
		wstring Debug_Speed_Str = L"";
		float Debug_Mini_Speed_F = 0.0f;
		float Debug_Mix_Speed_F = 0.0f;
		//攻撃
		wstring Debug_Attack_Str = L"";
		float Debug_Mini_Attack_F = 0.0f;
		float Debug_Mix_Attack_F = 0.0f;
		//突撃
		wstring Debug_Assault_Str = L"";
		float Debug_Mini_Assault_F = 0.0f;
		float Debug_Mix_Assault_F = 0.0f;

	public:
		TestEnemy(const shared_ptr<Stage>& StagePtr, const wstring& line);
		virtual ~TestEnemy() {};
		virtual void OnCreate()override;
		virtual void OnLastUpdate()override;
	};
	
}