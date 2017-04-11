/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once


#include "resource.h"

//行動クラス用.h
#include "Behavior.h"


#include "ProjectShader.h"
#include "Scene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameStage.h"
#include "Character.h"
#include "Player.h"
#include "GameMedia.h"

//アタリ判定
#include "Collision_Sphere.h"

//オブジェクトのデータ
enum DataID {
	//NULLID = 0;
	FLOOR = 0,
	BOX = 1,
};




