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
		//�����_��
		int m_RnadNum;

		//�e�G�l�~�[�ւ̑������l�����o�[�ireturn�Ŏg�p
		//�ʒu
		Vector3 m_Pos = Vector3(0,0,0);
		//�X�P�[��
		 int m_Scale = 0;
		//HP
		 int m_HP = 0;
		//�T�[�`�i���G�͈�
		 int m_Search = 0;
		//�N�[���^�C��
		 int m_CoolTime = 0;
		//�V���b�g�N�[���^�C���i�e�̌��Ԋu �g�p�ӏ��@ShotEnemy
		 int m_ShotCoolTime = 0;
		//�X�s�[�h
		 int m_Speed = 0;
		//�U����
		 int m_AttackPower = 0;
		//�ˌ��񐔁i �g�p�ӏ� TackleEnemy
		 int m_AttackTimes = 0;
		//�q�@���ˊԊu( �g�p�ӏ��@ShotEnemy
		 int m_ChildDrop = 0;
		//���G�^�q�@�̔��ˊԊu�i�g�p�ӏ� TeleportEnemy
		 int m_ChildSearch = 0;
		//���ː��i���Ŕ��˂����e�̐� 
		 int m_ShotBullet = 0;
	public:
		//�\�z�Ɣj��
		InputCSV(const shared_ptr<Stage>& StagePtr);
		virtual ~InputCSV();
		//������
		virtual void OnCreate() override;
		//�w��͈͓��Ń����_������Ԃ��֐�
		int Random(const int Min, const int Max);
#pragma region EnemysSet
		//�G�l�~�[�ւ̑���p�Z�b�^
		//�ʒu Single:�l���P�����̂Ƃ��Ɏg�p�@�@Multi
		Vector3  SinglePos(vector<wstring> Tokens);
		//�X�P�[��
		int SingleScale(vector<wstring> Tokens);
		int MultiScale(vector<wstring> Tokens, vector<wstring> Tokens2);
		//HP
		int SingleHP(vector<wstring> Tokens);
		int MultiHP(vector<wstring> Tokens, vector<wstring> Tokens2);
		//���G�͈�
		int SingleSearch(vector<wstring> Tokens);
		int MultiSearch(vector<wstring> Tokens, vector<wstring> Tokens2);
        //�N�[���^�C��
		int SingleCoolTime(vector<wstring> Tokens);
		int MultiCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2);
		//�V���b�g�N�[���^�C���i�e�̌��Ԋu �g�p�ӏ��@ShotEnemy
		int SingleShotCoolTime(vector<wstring> Tokens);
		int MultiShotCoolTime(vector<wstring> Tokens, vector<wstring> Tokens2);
		//�X�s�[�h
		int SingleSpeed(vector<wstring> Tokens);
		int MultiSpeed(vector<wstring> Tokens, vector<wstring> Tokens2);
		//�U����
		int SingleAttackPower(vector<wstring> Tokens);
		int MultiAttackPower(vector<wstring> Tokens, vector<wstring> Tokens2);
		//�ˌ��񐔁i �g�p�ӏ� TackleEnemy
		int SingleAttackTimes(vector<wstring> Tokens);
		int MultiAttackTimes(vector<wstring> Tokens, vector<wstring> Tokens2);
		//�q�@���ˊԊu( �g�p�ӏ��@ShotEnemy 
		int SingleChildDrop(vector<wstring> Tokens);
		int MultiChildDrop(vector<wstring> Tokens, vector<wstring> Tokens2);
		//���G�^�q�@�̔��ˊԊu�i�g�p�ӏ� TeleportEnemy 
		int SingleChildSearch(vector<wstring> Tokens);
		int MultiChildSearch(vector<wstring> Tokens, vector<wstring> Tokens2);
		//���ː��i���Ŕ��˂����e�̐�  
		int SingleShotBullet(vector<wstring> Tokens);
		int MultiShotBullet(vector<wstring> Tokens, vector<wstring> Tokens2);
#pragma endregion

	};

	
}