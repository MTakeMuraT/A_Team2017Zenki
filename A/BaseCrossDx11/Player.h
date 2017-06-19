
/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"



namespace basecross {
	

	//--------------------------------------------------------------------------------------
	///	�v���C���[�R���g���[��
	//--------------------------------------------------------------------------------------
	class PlayerControl : public GameObject
	{
	private:
		//�v���C���[��̖�
		shared_ptr<GameObject> m_Player1;
		//�v���C���[��̖�
		shared_ptr<GameObject> m_Player2;
		//��̂̋���
		float m_PlayerSDistance;
		//��̂̋��������l
		float m_PlayerSDistanceInit;
		//��̂̋����ő�
		float m_PlayerSDistanceLimit;
		//����鑬�x
		float m_DistanceSpeed;
		//���������x
		float m_KuttukuSpeed;

		//��]
		float m_rot;
		//��]���x
		float m_rotSpeed;

		//����
		Vector3 m_Kansei;

		//����
		shared_ptr<GameObject> m_BlackSprite;
		//�����̓����x
		float m_BlackAlpha;
		//�����ɂȂ邩
		bool m_BlackAlphaFlg = false;

		//�A�j���[�V�����̖��O
		//�X�V�O
		string m_NowAnimName;
		//�X�V��
		string m_ChangeAnimName;

		//�S�������Ȃ�����t���O
		bool m_DontMoveFlg = false;

		//�������Ă�t���O
		bool m_KuttukuFlg = false;
		//�������Ė߂�t���O
		bool m_KuttukuAfterFlg = false;

		//�ʒu�X�V�؂�t���O
		bool m_DontMoveFlg2 = false;
		//-----------------------
		//�p�����[�^��
		//-----------------------
		float m_Speed;


		//-----------------------
		//�֐�
		//-----------------------
		//�v���C���[�����̍��W���X�V
		void PosRotUpdate();
		//�X�e�[�W�̊O�ɍs�����Ƃ�����߂�����
		void CheckStageEnd();
		//�Ó]����
		void BlackUpdate();
		//�A�j���[�V�����X�V
		void UpdateAnimation();
		//-----------------------
		//����n
		//-----------------------
		bool m_moveFlg;
		bool m_rotFlg;
		bool m_AButtonFlg;
	public:
		PlayerControl(const shared_ptr<Stage>& StagePtr) : GameObject(StagePtr) {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//��̂̍��W��Ԃ�
		vector<Vector3> GetPlayerSPos_RETURNvectorVec3();
		//������Ԃ�
		float GetDistance() { return m_PlayerSDistance; }
		//�ʒu�X�V�I�t
		void DontMove() { m_DontMoveFlg2 = true; }
		//�����蔻��
		void SetActiveCollision(bool flg);
		
	};

	
	//--------------------------------------------------------------------------------------
	//	class SkySphere : public GameObject;
	//	�p�r: �X�J�C�{�b�N�X�̔w�i
	//--------------------------------------------------------------------------------------
	class SkySphere : public GameObject {
		Vector3 m_Scale;
		Vector3 m_Position;
	public:
		//�\�z�Ɣj��
		SkySphere(const shared_ptr<Stage>& StagePtr,
			const Vector3& Scale,
			const Vector3& Position
		);
		virtual ~SkySphere();
		//������
		virtual void OnCreate() override;
		//����
	};
	////--------------------------------------------------------------------------------------
	////	class PlayerParticle : public GameObject;
	////	�p�r:�v���C���[�p�[�e�B�N��
	////--------------------------------------------------------------------------------------
	//class  PlayerParticle :public GameObject
	//{
	//private:
	//	//�����ʒu
	//	Vector3 m_InitPos = Vector3(0,0,0);
	//	//�傫��
	//	Vector3 m_Scale = Vector3(0, 0, 0);
	//	//�쐬����Ԋu
	//	float m_CreateInterval = 0.0f;
	//	//�e�N�X�`���̖��O
	//	wstring m_TextureName;
	//	//���ŉ��o
	//	bool m_DeleteFlg = false;
	//	//���݃p�[�e�B�N�����o���Ă��邩�ǂ���
	//	bool m_NowParticleFlg = false;
	//	//���C���[
	//	int m_Layer = 0;
	//	//�����鎞��
	//	float m_DeleteTime = 1.0f;
	//	//float m_Count = 0.0f;
	//	//�p�[�e�B�N���f�[�^
	//	vector<shared_ptr<GameObject>> m_Particle;
	//	vector<int>m_DeleteIntvec;
	//	bool flg = true;
	//public:
	//	PlayerParticle(const shared_ptr<Stage>& StagePtr);
	//	~PlayerParticle() {};
	//	virtual void OnUpdate() override;
	//	//�����ʒu�A�傫���A�e�N�X�`���̖��O�A�����鎞��,�쐬�Ԋu�A���C���[�A�����鎞��
	//	void OnParticle(Vector3 InitPos, Vector3 scale, wstring TextureName, bool DeleteFlg, float CreateInterval, int Layer, float deleteTime);
	//	void CreateParticle();

	//};
	////--------------------------------------------------------------------------------------
	////	class PlayerShield : public GameObject;
	////	�p�r�V�[���h���o
	////--------------------------------------------------------------------------------------
	class PlayerShield : public GameObject
	{
	private:
		Vector3 m_Pos = Vector3(0, 0, 0);
		Vector3 m_Scele = Vector3(0, 0, 0);
		float m_Opacity = 0.0f;
		shared_ptr<GameObject> m_Player;
		float m_OpacityColor = 1.0f;
		bool m_Once = true;
		bool InitHpSaveflg = true;
		bool m_OnShield = false;
		//HP�̕ۑ�
		int m_HPSave = 0;
	public:
		PlayerShield(const shared_ptr<Stage>& StagePtr, const Vector3& Pos ,const Vector3& Scele, shared_ptr<GameObject> Player);
		~PlayerShield() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};



	
	////--------------------------------------------------------------------------------------
	////	class PlayerBoost : public GameObject;
	////	�p�r:�v���C���[�u�[�X�g
	////--------------------------------------------------------------------------------------
	class  PlayerBoost :public GameObject
	{
	 private:
		Vector3 m_InitPos = Vector3(0, 0, 0);
		Vector3 m_scale = Vector3(0, 0, 0);
		wstring m_TextureName;

		float m_DeleteTime = 0.0f;
		float m_CuntTime = 0.0f;
		int m_PlusTimeSpeed = 0;
		 public:
			 PlayerBoost(const shared_ptr<Stage>& StagePtr,const Vector3& InitPos,const Vector3& scale,const wstring& TextureName,const int& DeleteTime, const int& PlusTimeSpeed);
		 	~PlayerBoost() {};
			virtual void OnCreate() override;
		 	virtual void OnUpdate() override;
	};


	

	//--------------------------------------------------------------------------------------
	//	class PlayerHP : public GameObject;
	//	�p�r: �v���C���[HP�̏���
	//--------------------------------------------------------------------------------------
	class PlayerHP : public GameObject {
	private:
		//���G�p
		bool m_invincible_b = false;
		float InvinciblecCunt = 0.0f;
		float InvinciblecLimit = 3.0f;
		//�G�Ƃ̐ڐG
		bool m_Hit_b = false;
		//�_���[�W
		int m_Damage_int = 0;
		public:
		//�\�z�Ɣj��
		PlayerHP(const shared_ptr<Stage>& StagePtr
		);
		virtual ~PlayerHP();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//����
		bool GetInvincible() {
			return m_invincible_b;
		}
		void SetInvincible(bool Hit_flg) {
			m_invincible_b = Hit_flg;
		}
		bool GetHit() {
			return m_Hit_b;
		}
		void SetHit(bool Hit) {
			m_Hit_b = Hit;
		}
		int  GetDamage_int() {
			return m_Damage_int;
		}
		void SetDamage_int(int Damage) {
			m_Damage_int = Damage;
		}
	};
	
	//--------------------------------------------------------------------------------------
	//	Player�u�[�X�gSP �X�v���C�g�X�^�W�I
	//--------------------------------------------------------------------------------------
	class PlayerBoostSP : public SS5ssae
	{
	private:
		Vector3 m_Pos;
		Vector3 m_Scale;
		Vector3 m_Rotation;
	public:
		PlayerBoostSP(const shared_ptr<Stage>& StagePtr, Vector3 pos, Vector3 scale, wstring txtdire, wstring txtname, Vector3 Rotation);
		~PlayerBoostSP() {};
		void OnCreate() override;
		void OnUpdate() override;
	};
	
}
//end basecross
