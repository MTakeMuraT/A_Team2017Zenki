/*!
@file Rigidbody.h
@brief 物理計算コンポーネント
@copyright Copyright (c) 2017 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	操舵コンポーネントの親クラス
	//--------------------------------------------------------------------------------------
	class SteeringComponent : public Component {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトコンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit SteeringComponent(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	プロテクトデストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SteeringComponent();
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
	///	Seek（探索）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class SeekSteering : public SteeringComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit SeekSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~SeekSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を得る
		@return	目標位置
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetTargetPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	Vec	目標位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(const Vector3& Vec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	x	目標位置X
		@param[in]	y	目標位置Y
		@param[in]	z	目標位置Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	Arrive（到着）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class ArriveSteering : public SteeringComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit ArriveSteering(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ArriveSteering();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を得る
		@return	目標位置
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetTargetPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	Vec	目標位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(const Vector3& Vec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	x	目標位置X
		@param[in]	y	目標位置Y
		@param[in]	z	目標位置Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(float x, float y, float z);
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	Pursuit（追跡）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class PursuitSteering : public SteeringComponent {
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
		@brief	目標位置を得る
		@return	目標位置
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetTargetPosition() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	Vec	目標位置
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(const Vector3& Vec);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標位置を設定する
		@param[in]	x	目標位置X
		@param[in]	y	目標位置Y
		@param[in]	z	目標位置Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetPosition(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の回転を得る
		@return	目標の回転
		*/
		//--------------------------------------------------------------------------------------
		const Quaternion& GetTargetQuaternion() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の回転を設定する
		@param[in]	Qt	目標の回転
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetQuaternion(const Quaternion& Qt);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の回転ベクトルを設定する
		@param[in]	rotation	目標の回転ベクトル
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetRotation(const Vector3& rotation);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の回転ベクトルを設定する
		@param[in]	x	目標の回転ベクトルX
		@param[in]	y	目標の回転ベクトルY
		@param[in]	z	目標の回転ベクトルZ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetRotation(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の速度を得る
		@return	目標の速度
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetTargetVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の速度を設定する
		@param[in]	velocity	目標の速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetVelocity(const Vector3& velocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	目標の速度を設定する
		@param[in]	x	目標の速度X
		@param[in]	y	目標の速度Y
		@param[in]	z	目標の速度Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetTargetVelocity(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	Wander（徘徊）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class WanderSteering : public SteeringComponent {
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	WallAvoidance（壁回避）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class WallAvoidanceSteering : public SteeringComponent {
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
		@brief	壁と衝突しているかどうかを得る
		@return	壁と衝突していればtrue
		*/
		//--------------------------------------------------------------------------------------
		bool IsWallArribed() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 ObstacleAvoidance（障害物回避）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class ObstacleAvoidanceSteering : public SteeringComponent {
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 FollowPath（経路追従）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class FollowPathSteering : public SteeringComponent {
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 Alignment（整列）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class AlignmentSteering : public SteeringComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Group	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		AlignmentSteering(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<GameObjectGroup>& Group);
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};

	//--------------------------------------------------------------------------------------
	///	 Cohesion（結合）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class CohesionSteering : public SteeringComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Group	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		CohesionSteering(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<GameObjectGroup>& Group);
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};



	//--------------------------------------------------------------------------------------
	///	 Separation（分離）操舵コンポーネント
	//--------------------------------------------------------------------------------------
	class SeparationSteering : public SteeringComponent {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		@param[in]	Group	対象となるグループ
		*/
		//--------------------------------------------------------------------------------------
		SeparationSteering(const shared_ptr<GameObject>& GameObjectPtr,
			const shared_ptr<GameObjectGroup>& Group);
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
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//--------------------------------------------------------------------------------------
	///	 速度を基準とした物理位置計算コンポーネント
	//--------------------------------------------------------------------------------------
	class Rigidbody : public Component {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	GameObjectPtr	ゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		explicit Rigidbody(const shared_ptr<GameObject>& GameObjectPtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Rigidbody();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	速度を得る
		@return	速度
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	速度をを設定する
		@param[in]	Velocity	速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetVelocity(const Vector3& Velocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	速度をを設定する
		@param[in]	x	速度X
		@param[in]	y	速度Y
		@param[in]	z	速度Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetVelocity(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最高速度を得る
		@return	最高速度
		*/
		//--------------------------------------------------------------------------------------
		float GetMaxSpeed() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最高速度を設定する
		@param[in]	f	最高速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMaxSpeed(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最低速度を得る。最低速度は各方向に対して設定できる。<br />
		各方向が最低速度を下回った場合、その値は0になる
		@return	最低速度
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetMinVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最高速度を設定する
		@param[in]	Velocity	最低速度
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMinVelocity(const Vector3& Velocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最高速度を設定する
		@param[in]	x	最低速度X
		@param[in]	y	最低速度Y
		@param[in]	z	最低速度Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMinVelocity(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回転速度（ベクトル）を得る。
		@return	回転速度（ベクトル）
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetAngularVelocity() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回転速度（ベクトル）を設定する
		@param[in]	AngularVelocity	回転速度（ベクトル）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetAngularVelocity(const Vector3& AngularVelocity);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	回転速度（ベクトル）を設定する
		@param[in]	x	回転速度（ベクトル）X
		@param[in]	Y	回転速度（ベクトル）Y
		@param[in]	Z	回転速度（ベクトル）Z
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetAngularVelocity(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	質量を得る。Forceが0より大きい場合、速度はForceと質量による計算が合算される。<br />
		速度を直接操作する場合はForceは変更しないほうが良い。
		@return	質量
		*/
		//--------------------------------------------------------------------------------------
		float GetMass() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	質量を設定する
		@param[in]	f	質量
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMass(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	反発係数を得る。衝突判定により参照される。
		@return	反発係数
		*/
		//--------------------------------------------------------------------------------------
		float GetReflection() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	反発係数を設定する
		@param[in]	f	反発係数
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetReflection(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォース（力）を得る。速度計算に使用される。
		@return	フォース
		*/
		//--------------------------------------------------------------------------------------
		const Vector3& GetForce() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォース（力）を設定する
		@param[in]	Force	フォース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetForce(const Vector3& Force);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォース（力）を設定する
		@param[in]	x	フォースX
		@param[in]	y	フォースY
		@param[in]	z	フォースZ
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetForce(float x, float y, float z);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	減速フォースを得る。減速フォースは最終的に速度にブレーキを掛ける。<br />
		実際には質量で割った値（逆加速）が計算され適用される
		@return	減速フォース
		*/
		//--------------------------------------------------------------------------------------
		float GetFrictionForce() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	減速フォースを設定する。減速フォースは最終的に速度にブレーキを掛ける。<br />
		実際には質量で割った値（逆加速）が計算され適用される
		@param[in]	f	減速フォース
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetFrictionForce(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォース（力）の最大値を得る。
		@return	フォースの最大値
		*/
		//--------------------------------------------------------------------------------------
		float GetMaxForce() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	フォース（力）の最大値を設定する
		@param[in]	f	フォースの最大値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetMaxForce(float f);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	指定した時間だけ速度に従って移動する
		@param[in]	CalcTime	時間
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void UpdateFromTime(float CalcTime);
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 描画処理。デフォルトは何も行わない
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override {}
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;

	};



}
//end basecross
