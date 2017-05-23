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
		int m_StageNum = 0;
		//�X�e�[�W�̕�
		Vector2 m_StageSize = Vector2(50,50);
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

	};

}

//end basecross
