/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	class GameMedia;

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//���\�[�X���ŏ��ɌĂԂ��ߍ쐬
		shared_ptr<GameMedia> m_GameMedia;

		//Abe20170515
		//�X�e�[�W�ԍ�
		int m_StageNum = 1;
		//�X�e�[�W�̕�
		Vector2 m_StageSize = Vector2(50,50);
		//Abe20170515
		//�X�e�[�WCSV�ԍ�
		wstring m_CsvStageNum;

		//Abe20170515
		//int m_stagescorearr[16][5] = { 0 };
		//Abe20170515

	public:

		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;

		virtual void OnEvent(const shared_ptr<Event>& event) override;
		
		//Abe20170515
		//�X�e�[�W�ԍ��ƃX�e�[�W�T�C�Y��ݒ�
		void SetStageNumAndStageSize(int stagenum, Vector2 stagesize);
		//�X�e�[�W�T�C�Y�A�N�Z�T�[
		Vector2 GetStageSize() { return m_StageSize; }
		//�X�e�[�W�ԍ��A�N�Z�T�[
		int GetStageNum() { return m_StageNum; }
		//Abe20170515
		//CSV�̃X�e�[�W�i���o�[�A�N�Z�T
		void SetCsvStageNum(wstring StageNumCSV) { m_CsvStageNum = StageNumCSV; }
		wstring GetCsvStageNum() { return m_CsvStageNum; }


		//Abe20170622
		//�X�R�A�o�^
		void SetStageScore(int score);

		//�X�R�A�擾
		int GetStageScore(int stage, int num);
		//Abe20170622

	};
}

//end basecross
