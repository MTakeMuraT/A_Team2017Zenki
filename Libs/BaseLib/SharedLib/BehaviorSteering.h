/*!
@file BehaviorRigidbody.h
@brief 行動クラス(Rigidbody関連)
@copyright Copyright (c) 2017 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	操舵行動の親クラス
	//--------------------------------------------------------------------------------------
	class SteeringBehavior : public Behavior {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトコンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit SteeringBehavior(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SteeringBehavior();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	この操舵のウェイトを得る（デフォルト1.0）
		@return	この操舵のウェイト
		*/
		//--------------------------------------------------------------------------------------
		float GetWeight() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	この操舵のウェイトを設定する
		@param[in]	f	なし
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWeight(float f);
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	SeekSteering行動クラス
	//--------------------------------------------------------------------------------------
	class SeekSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		SeekSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SeekSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetPos	追いかける位置
		@return	追いかける位置との距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const Vector3& TargetPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetKey	追いかけるオブジェクトのキー（SharedObjec）
		@return	追いかけるオブジェクトとの距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const wstring& TargetKey);
	};

	//--------------------------------------------------------------------------------------
	///	ArriveSteering行動クラス
	//--------------------------------------------------------------------------------------
	class ArriveSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		ArriveSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ArriveSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	減速値を得る（デフォルト3.0）
		@return	減速値
		*/
		//--------------------------------------------------------------------------------------
		float GetDecl() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	減速値を設定する
		@param[in]	f	減速値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDecl(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetPos	追いかける位置
		@return	追いかける位置との距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const Vector3& TargetPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetKey	追いかけるオブジェクトのキー（SharedObjec）
		@return	追いかけるオブジェクトとの距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const wstring& TargetKey);
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	PursuitSteering（追跡）行動クラス
	//--------------------------------------------------------------------------------------
	class PursuitSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit PursuitSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PursuitSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetPos	追いかける位置
		@param[in]	TargetVelocity	追いかけるオブジェクトの速度
		@param[in]	TargetRotation	追いかけるオブジェクトの回転
		@return	追いかける位置との距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const Vector3& TargetPos, const Vector3& TargetVelocity, const Vector3& TargetRotation);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@param[in]	TargetKey	追いかけるオブジェクトのキー（SharedObjec）
		@return	追いかけるオブジェクトとの距離
		*/
		//--------------------------------------------------------------------------------------
		float Execute(const wstring& TargetKey);
	};



	//--------------------------------------------------------------------------------------
	///	WanderSteering（徘徊）行動
	//--------------------------------------------------------------------------------------
	class WanderSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit WanderSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~WanderSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	徘徊の中心を得る
		@return	徘徊の中心
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetWanderTarget() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の中心を設定する
		@param[in]	target	目標の中心
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWanderTarget(const Vector3& target);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	徘徊の半径を得る
		@return	徘徊の半径
		*/
		//--------------------------------------------------------------------------------------
		float GetWanderRadius() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	徘徊の半径を設定する
		@param[in]	f	徘徊の半径
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWanderRadius(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	徘徊の円が投影されるときの距離を得る
		@return	徘徊の円が投影されるときの距離
		*/
		//--------------------------------------------------------------------------------------
		float GetWanderDistance() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	徘徊の円が投影されるときの距離を設定する
		@param[in]	f	徘徊の円が投影されるときの距離
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWanderDistance(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ランダム変異の最大値を得る
		@return	ランダム変異の最大値
		*/
		//--------------------------------------------------------------------------------------
		float GetWanderJitter() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ランダム変異の最大値を設定する
		@param[in]	f	ランダム変異の最大値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWanderJitter(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	WallAvoidanceSteering（壁回避）行動
	//--------------------------------------------------------------------------------------
	class WallAvoidanceSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit WallAvoidanceSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~WallAvoidanceSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回避する壁の配列を得る
		@return	回避する壁の配列
		*/
		//--------------------------------------------------------------------------------------
		vector<PLANE>& GetPlaneVec() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回避する壁の配列を設定する
		@param[in]	planevec	回避する壁の配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPlaneVec(const vector<PLANE>& planevec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回避する壁の配列を設定する
		@param[in]	planevec	回避する壁の配列（Plane型）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPlaneVec(const vector<Plane>& planevec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	壁と衝突しているかどうか
		*/
		//--------------------------------------------------------------------------------------
		bool Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	 ObstacleAvoidanceSteering（障害物回避）行動
	//--------------------------------------------------------------------------------------
	class ObstacleAvoidanceSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit ObstacleAvoidanceSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ObstacleAvoidanceSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	障害物の配列を得る
		@return	障害物の配列
		*/
		//--------------------------------------------------------------------------------------
		const vector<SPHERE>& GetObstacleSphereVec() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	障害物の配列を設定する
		@param[in]	spherevec	障害物の配列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetObstacleSphereVec(const vector<SPHERE>& spherevec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	道幅を得る
		@return	道幅
		*/
		//--------------------------------------------------------------------------------------
		float GetRoadWidth() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	道幅を設定する
		@param[in]	f	道幅
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetRoadWidth(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	道の高さを得る
		@return	道の高さ
		*/
		//--------------------------------------------------------------------------------------
		float GetRoadHeight() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	道の高さを設定する
		@param[in]	f	道の高さ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetRoadHeight(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 FollowPathSteering（経路追従）行動
	//--------------------------------------------------------------------------------------
	class FollowPathSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit FollowPathSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~FollowPathSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	経路をあらわすリストを設定する
		@param[in]	pathlist	経路をあらわすリスト
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetPathList(const list<Vector3>& pathlist);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	パスについた場合の減速値を得る
		@return	パスについた場合の減速値
		*/
		//--------------------------------------------------------------------------------------
		float GetDecl() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	パスについた場合の減速値を設定する
		@param[in]	f	パスについた場合の減速値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetDecl(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	パスの大きさを得る
		@return	パスの大きさ
		*/
		//--------------------------------------------------------------------------------------
		float GetWaypointSpan() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	パスの大きさを設定する
		@param[in]	f	パスの大きさ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetWaypointSpan(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ループするかどうかを得る
		@return	ループすればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool GetLooped() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ループするかどうかを得る
		@return	ループすればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsLooped() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ループするかどうかを設定する
		@param[in]	b	ループするかどうか
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetLooped(bool b);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	経路追従が終了したかどうかを得る
		@return	終了してればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsFinished() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	巡回が終了したらtrue
		*/
		//--------------------------------------------------------------------------------------
		bool Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	 AlignmentSteering（整列）行動
	//--------------------------------------------------------------------------------------
	class AlignmentSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		AlignmentSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~AlignmentSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを得る
		@return	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObjectGroup> GetGameObjectGroup() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを設定する
		@param[in]	Group	対象となるグループ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	 CohesionSteering（結合）行動
	//--------------------------------------------------------------------------------------
	class CohesionSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		CohesionSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CohesionSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを得る
		@return	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObjectGroup> GetGameObjectGroup() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを設定する
		@param[in]	Group	対象となるグループ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 SeparationSteering（分離）行動クラス
	//--------------------------------------------------------------------------------------
	class SeparationSteering : public SteeringBehavior {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Group	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		SeparationSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SeparationSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを得る
		@return	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<GameObjectGroup> GetGameObjectGroup() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	対象となるグループを設定する
		@param[in]	Group	対象となるグループ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetGameObjectGroup(const shared_ptr<GameObjectGroup>& Group);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	行動を実行する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Execute();
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};




}
//end basecross