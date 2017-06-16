#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//���\�[�X�̍쐬
	void GameMedia::OnCreate() {
		//�e�N�X�`���̓ǂݍ��݂̃e�N�j�b�N�@�t�@�C�����ƃe�N�X�`����z��Ŏ����Ăяo��
		//struct {
		//	wstring filename;
		//	wstring key;
		//}textureString[] = {
		//	{ L"TestTexture\\trace.png" , L"SKY_TX" },
		//};

		//App::GetApp()->RegisterTexture(textureString[0].key, DataDir + textureString[0].filename);

		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		wstring strTexture = DataDir + L"TestTexture\\trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);

		strTexture = DataDir + L"TestTexture\\sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);

		//�����̃X�v���C�g
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"Spark_TX", strTexture);
		App::GetApp()->RegisterTexture(L"TEST_AO_TX", strTexture);
		strTexture = DataDir + L"red.png";
		App::GetApp()->RegisterTexture(L"TEST_Red_TX", strTexture);

		//Abe20170602
		//�^�C�����n
		strTexture = DataDir + L"Time_Background.png";
		App::GetApp()->RegisterTexture(L"TIMEBACK_TX", strTexture);
		//Abe20170602

		//�Q�[���X�e�[�W���
		strTexture = DataDir + L"GameStage\\Background.png";
		App::GetApp()->RegisterTexture(L"Background_TX", strTexture); 
		strTexture = DataDir + L"GameStage\\Glass.png";
		App::GetApp()->RegisterTexture(L"Glass_TX", strTexture); 
		//�v���C���[�֌W
		//HP�̃t���[��
		strTexture = DataDir + L"HP_Flame.png";
		App::GetApp()->RegisterTexture(L"HP_FLAME_TX", strTexture);
		//HP�̒��g
		strTexture = DataDir + L"HP.png";
		App::GetApp()->RegisterTexture(L"HP_TX", strTexture);

		//�e�X�g�pTX
		strTexture = DataDir + L"TestTexture\\GameS.png";
		App::GetApp()->RegisterTexture(L"TEST_Game_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Serekuto.png";
		App::GetApp()->RegisterTexture(L"TEST_Serekuto_TX", strTexture);
		strTexture = DataDir + L"TestTexture\\Taitoru.png";
		App::GetApp()->RegisterTexture(L"TEST_Taitoru_TX", strTexture); 
		////�Z���N�g
		//strTexture = DataDir + L"Stage_Select_Lin\\STAGE_SELECT_TEST.png";
		//App::GetApp()->RegisterTexture(L"SELECT_TEST_TX", strTexture); 
		//�^�C�g��
		strTexture = DataDir + L"Title_Lin\\TITLE_TEST.png";
		App::GetApp()->RegisterTexture(L"Taitoru_TEST_TX", strTexture);
		strTexture = DataDir + L"Title_Lin\\Press_any_button.png";
		App::GetApp()->RegisterTexture(L"Prres_any_boten_TEST_TX", strTexture);
		strTexture = DataDir + L"kuro.png";
		App::GetApp()->RegisterTexture(L"KURO_TX", strTexture);

		//Abe20170421
		//�X�e�Z��
		//�Z���N�g�̃t���[����g
		strTexture = DataDir + L"StageSelect\\Select_Flame.png";
		App::GetApp()->RegisterTexture(L"SELECT_FLAME_TX", strTexture);		
		//Abe20170512
		//�Z���N�g�̃E�B���h�E�̃t���[��
		strTexture = DataDir + L"StageSelect\\Flame.png";
		App::GetApp()->RegisterTexture(L"SELECTCHECK_FLAME_TX", strTexture);
		//Abe20170512
		//Abe20170525
		//���g
		strTexture = DataDir + L"StageSelect\\StageSelect_WindowBack.png";
		App::GetApp()->RegisterTexture(L"SELECT_WINDOWIN_TX", strTexture);
		//���S
		//�J�[�\��
		strTexture = DataDir + L"StageSelect\\StageSelect_Logo.png";
		App::GetApp()->RegisterTexture(L"SELECT_LOGO_TX", strTexture);

		//Abe20170525
		//Abe20170526
		//���
		strTexture = DataDir + L"StageSelect\\Yazirushi.png";
		App::GetApp()->RegisterTexture(L"YAZIRUSHI_TX", strTexture);
		//easy
		strTexture = DataDir + L"StageSelect\\Easy.png";
		App::GetApp()->RegisterTexture(L"EASY_TX", strTexture);
		//normal
		strTexture = DataDir + L"StageSelect\\Normal.png";
		App::GetApp()->RegisterTexture(L"NORMAL_TX", strTexture);
		//hard
		strTexture = DataDir + L"StageSelect\\Hard.png";
		App::GetApp()->RegisterTexture(L"HARD_TX", strTexture);
		//Abe20170526
		//�J�[�\��
		strTexture = DataDir + L"StageSelect\\StageSelect_Cursor.png";
		App::GetApp()->RegisterTexture(L"SELECT_CURSOR_TX", strTexture);
		//Abe20170421

		//Abe20170505
		//�G�l�~�[
		//���G�T�[�N��
		strTexture = DataDir + L"Enemy\\SearchCircle.png";
		App::GetApp()->RegisterTexture(L"SEARCHCIRCLE_TX", strTexture);
		//Abe20170505
		//Abe20170508
		strTexture = DataDir + L"Enemy\\TereportPoint.png";
		App::GetApp()->RegisterTexture(L"TEREPORTPOINT_TX", strTexture);
		strTexture = DataDir + L"Enemy\\Bomb.png";
		App::GetApp()->RegisterTexture(L"BOMB_TX", strTexture);
		//Abe20170508
		//Abe20170512
		//strTexture = DataDir + L"EF\\Explosion.png";
		strTexture = DataDir + L"EF\\Explosion.png";
		App::GetApp()->RegisterTexture(L"BOMBEFFECT_TX", strTexture);
		//Abe20170512
		//Abe20170517
		//�~�T�C��
		strTexture = DataDir + L"Enemy\\Missile.png";
		App::GetApp()->RegisterTexture(L"MISSILE_TX", strTexture);
		//Abe20170517
		//Abe20170519
		strTexture = DataDir + L"Enemy\\Bomb.png";
		App::GetApp()->RegisterTexture(L"SHOADOW_TX", strTexture);
		//Abe20170519

		//Abe20170529
		//�Q�[���I�[�o�[---------------------------------------
		//�N��
		strTexture = DataDir + L"GameOver\\OverBlack.png";
		App::GetApp()->RegisterTexture(L"OVERBLACK_TX", strTexture);
		//�V��
		strTexture = DataDir + L"GameOver\\OverWhite.png";
		App::GetApp()->RegisterTexture(L"OVERWHITE_TX", strTexture);
		//Abe20170529

		//Abe20170602
		//�I�[�o�[�̍Ō�̍���
		strTexture = DataDir + L"GameOver\\OverLastBlack.png";
		App::GetApp()->RegisterTexture(L"OVERLASTBLACK_TX", strTexture);
		//�I�[�o�[�̍Ō�̍���
		strTexture = DataDir + L"GameOver\\GameOver_Cursor.png";
		App::GetApp()->RegisterTexture(L"OVERCURSOR_TX", strTexture);
		//Abe20170602

		//Abe20170530
		//�m�C�Y
		strTexture = DataDir + L"GameOver\\Noise1.png";
		App::GetApp()->RegisterTexture(L"OVERNOISE_TX", strTexture);
		//�Q�[���I�[�o�[���S
		strTexture = DataDir + L"GameOver\\GameOverLogo.png";
		App::GetApp()->RegisterTexture(L"OVERLOGO_TX", strTexture);

		//���g���C���S
		strTexture = DataDir + L"GameOver\\RetryLogo.png";
		App::GetApp()->RegisterTexture(L"OVERRETRYLOGO_TX", strTexture);
		//�X�e�[�W�Z���N�g���S
		strTexture = DataDir + L"GameOver\\StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"OVERSTASELELOGO_TX", strTexture);
		//�^�C�g�����S
		strTexture = DataDir + L"GameOver\\TitleLogo.png";
		App::GetApp()->RegisterTexture(L"OVERTITLELOGO_TX", strTexture);


		//������
		wstring  strMOver = App::GetApp()->m_wstrRelativeDataPath + L"GameOver\\BombSE.wav";
		App::GetApp()->RegisterWav(L"OverBombSE", strMOver);
		//�m�C�Y��
		strMOver = App::GetApp()->m_wstrRelativeDataPath + L"GameOver\\NoiseSE.wav";
		App::GetApp()->RegisterWav(L"OverNoiseSE", strMOver);

		//Abe20170530

		//�Q�[���I�[�o�[---------------------------------------
		//Abe20170529

		//Abe20170531
		//���U���g--------------------------------------
		//���U���g��
		strTexture = DataDir + L"Result\\ResultBlack.png";
		App::GetApp()->RegisterTexture(L"RESULTBLACK_TX", strTexture);
		//���U���g��
		strTexture = DataDir + L"Result\\ResultWhite.png";
		App::GetApp()->RegisterTexture(L"RESULTWHITE_TX", strTexture);
		//�~�b�V�����R���v���[�g����
		strTexture = DataDir + L"Result\\MissionComplete.png";
		App::GetApp()->RegisterTexture(L"MISSIONCOMPLETE_TX", strTexture);
		//�~
		strTexture = DataDir + L"Result\\Batu.png";
		App::GetApp()->RegisterTexture(L"BATU_TX", strTexture);
		//TotalScore���S
		strTexture = DataDir + L"Result\\TotalScore.png";
		App::GetApp()->RegisterTexture(L"TOTALSCORE_TX", strTexture);
		//�����N
		//S
		strTexture = DataDir + L"Result\\RankS.png";
		App::GetApp()->RegisterTexture(L"RANK_S_TX", strTexture);
		//A
		strTexture = DataDir + L"Result\\RankA.png";
		App::GetApp()->RegisterTexture(L"RANK_A_TX", strTexture);
		//B
		strTexture = DataDir + L"Result\\RankB.png";
		App::GetApp()->RegisterTexture(L"RANK_B_TX", strTexture);
		//C
		strTexture = DataDir + L"Result\\RankC.png";
		App::GetApp()->RegisterTexture(L"RANK_C_TX", strTexture);

		//���̃X�e�[�W�փ��S
		strTexture = DataDir + L"Result\\NextStage.png";
		App::GetApp()->RegisterTexture(L"RESULTNEXTSTAGELOGO_TX", strTexture);
		//���g���C���S
		strTexture = DataDir + L"Result\\RetryLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTRETRYLOGO_TX", strTexture);
		//�X�e�[�W�Z���N�g���S
		strTexture = DataDir + L"Result\\StageSelectLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTSTASELELOGO_TX", strTexture);
		//�^�C�g�����S
		strTexture = DataDir + L"Result\\TitleLogo.png";
		App::GetApp()->RegisterTexture(L"RESULTTITLELOGO_TX", strTexture);

		//���U���g--------------------------------------
		//Abe20170531


		//Abe20170519
		//�G�l�~�[�J�E���g�̃X���b�V��
		strTexture = DataDir + L"Enemy\\EnemyCountSlash.png";
		App::GetApp()->RegisterTexture(L"ENEMYCOUNTSLASH_TX", strTexture);
		//Abe20170519

		//Abe20170524
		//�X�e�[�W�̔ԍ�
		for (int i = 1; i <= 16; i++)
		{
			wstring txt1 = L"StageSelect\\" + Util::IntToWStr(i) + L".png";
			strTexture = DataDir + txt1;
			wstring txt2 = L"STAGEBOX_" + Util::IntToWStr(i) + L"_TX";
			App::GetApp()->RegisterTexture(txt2, strTexture);
		}
		//�X�e�Z���̔w�i
		strTexture = DataDir + L"SELECT_Background.png";
		App::GetApp()->RegisterTexture(L"STAGESELECTGROUND_TX", strTexture);
		//Abe20170524

		//Abe20170605
		//�|�[�Y
		//�|�[�Y�̎c��G��
		strTexture = DataDir + L"Pause\\Pause_EnemyS.png";
		App::GetApp()->RegisterTexture(L"PAUSE_ENEMYS_TX", strTexture);
		//�|�[�Y���S
		strTexture = DataDir + L"Pause\\PauseLogo.png";
		App::GetApp()->RegisterTexture(L"PAUSE_LOGO_TX", strTexture);
		//���g���C
		strTexture = DataDir + L"Pause\\ReTry.png";
		App::GetApp()->RegisterTexture(L"PAUSE_RETRY_TX", strTexture);
		//�Q�[���ɖ߂�
		strTexture = DataDir + L"Pause\\ToGame.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOGAME_TX", strTexture);
		//�Z���N�g��
		strTexture = DataDir + L"Pause\\ToSelect.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOSELECT_TX", strTexture);
		//�^�C�g����
		strTexture = DataDir + L"Pause\\ToTitle.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TOTITLE_TX", strTexture);
		//�N��	
		strTexture = DataDir + L"Pause\\PauseBlack.png";
		App::GetApp()->RegisterTexture(L"PAUSE_BLACK_TX", strTexture);
		//Abe20170605

		//Abe20170606
		//���U�G�t�F�N�g
		strTexture = DataDir + L"EF\\bakusan.png";
		App::GetApp()->RegisterTexture(L"BAKUSANEF_TX", strTexture);
		//Abe20170606

		//Abe20170609
		//�Ԃ���G�t�F�N�g
		strTexture = DataDir + L"EF\\spark.png";
		App::GetApp()->RegisterTexture(L"BUTUKARIEF_TX", strTexture);
		//�n�܂艉�o
		//�X�^�[�g���S
		strTexture = DataDir + L"StageStart\\Start.png";
		App::GetApp()->RegisterTexture(L"STARTSTARTLOGO_TX", strTexture);
		//�X�e�[�W���S
		strTexture = DataDir + L"StageStart\\StageLogo.png";
		App::GetApp()->RegisterTexture(L"STARTSTAGELOGO_TX", strTexture);
		//Abe20170609

		//Abe20170614
		//�^�C�g���y��
		strTexture = DataDir + L"Title_Lin\\DODAI.png";
		App::GetApp()->RegisterTexture(L"TITLEDODAI_TX", strTexture);
		//�Q�[���X�^�[�g
		strTexture = DataDir + L"Title_Lin\\Game_start.png";
		App::GetApp()->RegisterTexture(L"TITLEGAMESTART_TX", strTexture);
		//�`���[�g���A��
		strTexture = DataDir + L"Title_Lin\\Tutorial.png";
		App::GetApp()->RegisterTexture(L"TITLETUTORIAL_TX", strTexture);
		//Abe20170614

		//Abe20170615
		//�`���[�g���A���̃^�[�Q�b�g
		strTexture = DataDir + L"Tutorial\\Target.png";
		App::GetApp()->RegisterTexture(L"TUTORIALTARGET_TX", strTexture);
		//Abe20170615
		//Abe20170616
		//A�{�^��
		strTexture = DataDir + L"Tutorial\\A.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_A_TX", strTexture);
		//A�{�^�������ꂽ��
		strTexture = DataDir + L"Tutorial\\APush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_APUSH_TX", strTexture);
		//RB�{�^��
		strTexture = DataDir + L"Tutorial\\RB.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_RB_TX", strTexture);
		//RB�{�^�������ꂽ��
		strTexture = DataDir + L"Tutorial\\RBPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_RBPUSH_TX", strTexture);
		//LB�{�^��
		strTexture = DataDir + L"Tutorial\\LB.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_LB_TX", strTexture);
		//LB�{�^�������ꂽ��
		strTexture = DataDir + L"Tutorial\\LBPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_LBPUSH_TX", strTexture);
		//�X�e�B�b�N
		strTexture = DataDir + L"Tutorial\\Stick.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_STICK_TX", strTexture);
		//�X�e�B�b�N�|���ꂽ��
		strTexture = DataDir + L"Tutorial\\StickPush.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_STICKPUSH_TX", strTexture);

		//�|�b�`
		strTexture = DataDir + L"Tutorial\\Poch.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_POCH_TX", strTexture);
		//�t���[��
		strTexture = DataDir + L"Tutorial\\Frame.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_FRAME_TX", strTexture);
		//Abe20170616


		////���f���i�{�[������
		auto MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Player\\PlayerModel\\Player_animation.bmf");
		App::GetApp()->RegisterResource(L"Player_Model", MadelMesh);
		//Abe20170519
		//�ˌ��G�l�~�[
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Assault\\Assault.bmf");
		App::GetApp()->RegisterResource(L"TACKLE_MODEL", MadelMesh);
		//�e���|�[�g�G�l�~�[
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Teleport\\Teleport.bmf");
		App::GetApp()->RegisterResource(L"TELEPORT_MODEL", MadelMesh);
		//�~�T�C���G�l�~�[/�g���ĂȂ�
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Missile_Enemy\\Missile_Enemy.bmf");
		App::GetApp()->RegisterResource(L"MISSILE_MODEL", MadelMesh);
		//�h���[��
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Dorawn\\Dorawn.bmf");
		App::GetApp()->RegisterResource(L"SEARCHDRAWN_MODEL", MadelMesh);
		//�����G�l�~�[
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\BombEnemy\\Suicide_bomb.bmf");
		App::GetApp()->RegisterResource(L"BOMBENEMY_MODEL", MadelMesh);
		//���e
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\EnemyModel\\Bomb\\Bomb.bmf");
		App::GetApp()->RegisterResource(L"BOMB_MODEL", MadelMesh);
		//Abe20170519
		//�~�T�C���q�@
		MadelMesh = MeshResource::CreateBoneModelMesh(DataDir, L"Enemy\\ShotChild\\Missile_Enemy_Child.bmf");
		App::GetApp()->RegisterResource(L"MissileEnemyChildModel", MadelMesh); 
		//�~�T�C��
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Enemy\\Missile\\Missile.bmf");
		App::GetApp()->RegisterResource(L"Missile_Model", MadelMesh); 
		//�w�iMOD
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"GameStage\\Background\\Background_Effect.bmf");
		App::GetApp()->RegisterResource(L"Background_Model", MadelMesh);
		//���b
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Enemy\\Shield\\Shild_Player_Sub.bmf");
		App::GetApp()->RegisterResource(L"Shield_Model", MadelMesh);

		//Abe20170605
		//�p�[�c�Q
		//1
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts1.bmf");
		App::GetApp()->RegisterResource(L"PARTS1_MODEL", MadelMesh);
		//2
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts2.bmf");
		App::GetApp()->RegisterResource(L"PARTS2_MODEL", MadelMesh);
		//3
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts3.bmf");
		App::GetApp()->RegisterResource(L"PARTS3_MODEL", MadelMesh);
		//4
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts4.bmf");
		App::GetApp()->RegisterResource(L"PARTS4_MODEL", MadelMesh);
		//5
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts5.bmf");
		App::GetApp()->RegisterResource(L"PARTS5_MODEL", MadelMesh);
		//6
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts6.bmf");
		App::GetApp()->RegisterResource(L"PARTS6_MODEL", MadelMesh);
		//7
		MadelMesh = MeshResource::CreateStaticModelMesh(DataDir, L"Parts\\Parts7.bmf");
		App::GetApp()->RegisterResource(L"PARTS7_MODEL", MadelMesh);
		//Abe20170605

		//���؂���̂ɏd���̂ňꎞ�I�ɏ����܂� Abe20170505
		//BGM
		/*wstring strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Title\\Title_01.wav";
		App::GetApp()->RegisterWav(L"Title_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\StageSelect\\StageSelect_01.wav";
		App::GetApp()->RegisterWav(L"StageSelect_01_BGM", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\GameStage\\GameStage_01.wav";
		App::GetApp()->RegisterWav(L"GameStage_01_BGM", strMusic);*/
	
		//SE
		
		wstring  strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_01.wav";
		App::GetApp()->RegisterWav(L"Decision_01_SE", strMusic);
		
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Collision_01.wav";
		App::GetApp()->RegisterWav(L"Collision_01_SE", strMusic);
		//�e�X�gSE
		//strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decision_02.wav";
		//App::GetApp()->RegisterWav(L"Decision_02_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\PlayerDie.wav";
		App::GetApp()->RegisterWav(L"PlayerDie_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\CursorMove.wav";
		App::GetApp()->RegisterWav(L"PlayerDie_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Win.wav";
		App::GetApp()->RegisterWav(L"Win_SE", strMusic);
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Win.wav";
		App::GetApp()->RegisterWav(L"Win_SE", strMusic);
		//App::GetApp()->RegisterWav(L"CursorMove_SE", strMusic); 
		//strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\PrayerExposure.wav";
		//App::GetApp()->RegisterWav(L"PrayerDie_SE", strMusic); 
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Enemy\\Computer Launch.wav";
		App::GetApp()->RegisterWav(L"Player_Look_SE", strMusic);
		/*strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Enemy\\Enemy ArmorBreak.wav";
		App::GetApp()->RegisterWav(L"Enemy_Damage_SE", strMusic);*/
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\Player\\Shield Break.wav";
		App::GetApp()->RegisterWav(L"Enemy_Damage_SE", strMusic);

		

		//Abe20170530
		//�I����
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\CursorMove.wav";
		App::GetApp()->RegisterWav(L"CURSORMOVE_SE", strMusic);
		//���艹
		strMusic = App::GetApp()->m_wstrRelativeDataPath + L"Sound\\SE\\Decide.wav";
		App::GetApp()->RegisterWav(L"DECIDE_SE", strMusic);
		//Abe20170530
	}
	
}