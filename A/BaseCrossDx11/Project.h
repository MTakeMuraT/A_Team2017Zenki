/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once


#include "resource.h"

//行動クラス用.h
#include "Behavior.h"

#include "ProjectShader.h"
//シーン
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameStage.h"
//オブジェ
#include "Character.h"
//アタリ判定
#include "Collision_Sphere.h"
//オブジェ
#include "GameMedia.h"
#include "StageSelectObj.h"
#include "Enemys.h"
#include "Player.h"
//アタリ判定
#include "CollisionManager.h"

//CSV
#include "CSV.h"


//オブジェクトのデータ
enum DataID {
	//NULLID = 0;
	FLOOR = 0,
	BOX = 1,
};




