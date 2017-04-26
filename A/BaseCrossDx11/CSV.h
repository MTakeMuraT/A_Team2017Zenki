#pragma once
#include"stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Dedug : public GameObject;
	//	�p�r: �X�e�[�W�V�[���@
	//--------------------------------------------------------------------------------------
	class InputCSV : public GameObject {

		//CSV�t�@�C������A
		CsvFile m_InputCSV;
	public:
		//�\�z�Ɣj��
		InputCSV(const shared_ptr<Stage>& StagePtr);
		virtual ~InputCSV();
		//������
		virtual void OnCreate() override;
		//����
	};


	class TestEnemy : public GameObject {
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scale = Vector3(0, 0, 0);
		wstring TowValue_Str =L"";
		
		//�f�o�b�N
		//�X�P�[���@�ŏ��l�@�ő�l
		wstring Debug_TowValue_Scale_Str = L"";
		float Debug_Mini_Scale_F = 0.0f;
		float Debug_Mix_Scale_F = 0.0f;
		//HP�@�ŏ��l�@�ő�l
		wstring Debug_TowValue_HP_Str = L"";
		float Debug_Mini_HP_F = 0.0f;
		float Debug_Mix_HP_F = 0.0f;
		//���G�͈�
		wstring Debug_Search_Str = L"";
		float Debug_Mini_Search_F = 0.0f;
		float Debug_Mix_Search_F = 0.0f;
		//�N�[���^�C�v
		wstring Debug_CoolTime_Str = L"";
		float Debug_Mini_CoolTime_F = 0.0f;
		float Debug_Mix_CoolTime_F = 0.0f;
		//���x
		wstring Debug_Speed_Str = L"";
		float Debug_Mini_Speed_F = 0.0f;
		float Debug_Mix_Speed_F = 0.0f;
		//�U��
		wstring Debug_Attack_Str = L"";
		float Debug_Mini_Attack_F = 0.0f;
		float Debug_Mix_Attack_F = 0.0f;
		//�ˌ�
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