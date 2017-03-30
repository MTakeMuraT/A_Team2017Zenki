#pragma once

#include "stdafx.h"

namespace basedx11{


	template <typename T>
	class StateMachine;

	//--------------------------------------------------------------------------------------
	//	class ObjState;
	//	用途: ステート実装テンプレートクラス(抽象クラス)
	//--------------------------------------------------------------------------------------
	template <typename T>
	class ObjState{
	public:
		//--------------------------------------------------------------------------------------
		//	ObjState();
		//	用途: コンストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		ObjState(){}
		//--------------------------------------------------------------------------------------
		//	virtual ~ObjState();
		//	用途: デストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		virtual ~ObjState(){}
		//--------------------------------------------------------------------------------------
		//	virtual void Enter(
		//	const shared_ptr<T>& Obj		//ステートを保持するオブジェクト
		//	) = 0;
		//	用途: ステートに入ったときに実行される
		//	戻り値: なし（純粋仮想関数）
		//--------------------------------------------------------------------------------------
		virtual void Enter(const shared_ptr<T>& Obj) = 0;
		//--------------------------------------------------------------------------------------
		//	virtual void Execute(
		//	const shared_ptr<T>& Obj		//ステートを保持するオブジェクト
		//	) = 0;
		//	用途: Updateのときに実行される
		//	戻り値: なし（純粋仮想関数）
		//--------------------------------------------------------------------------------------
		virtual void Execute(const shared_ptr<T>& Obj) = 0;
		//--------------------------------------------------------------------------------------
		//	virtual void Exit(
		//	const shared_ptr<T>& Obj		//ステートを保持するオブジェクト
		//	) = 0;
		//	用途: ステートを出るときに実行される
		//	戻り値: なし（純粋仮想関数）
		//--------------------------------------------------------------------------------------
		virtual void Exit(const shared_ptr<T>& Obj) = 0;
	};

	//--------------------------------------------------------------------------------------
	//	template <typename T>
	//	class StateMachine;
	//	用途: ステートマシン実装テンプレートクラス(抽象クラス)
	//	＊ステートを管理する
	//--------------------------------------------------------------------------------------
	template <typename T>
	class StateMachine
	{
	private:
		//このステートマシンを持つオーナー
		weak_ptr<T> m_Owner;
		//現在のステート
		weak_ptr< ObjState<T> > m_CurrentState;
		//一つ前のステート
		weak_ptr< ObjState<T> > m_PreviousState;
	public:
		//--------------------------------------------------------------------------------------
		//	StateMachine(
		//	const shared_ptr<T>& owner	//このステートマシンを保持するオーナー
		//	);
		//	用途: コンストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		explicit StateMachine(const shared_ptr<T>& owner) :
			m_Owner(owner)
			//m_CurrentState(nullptr), m_PreviousState(nullptr)
		{}
		//--------------------------------------------------------------------------------------
		//	virtual ~StateMachine();
		//	用途: デストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		virtual ~StateMachine(){}
		//--------------------------------------------------------------------------------------
		//	用途: Setアクセッサ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		void SetCurrentState(const shared_ptr< ObjState<T> >& s){ m_CurrentState = s; }
		void SetPreviousState(const shared_ptr< ObjState<T> >& s){ m_PreviousState = s; }
		//--------------------------------------------------------------------------------------
		//	用途: Getアクセッサ
		//	戻り値: ObjState<T>*
		//--------------------------------------------------------------------------------------
		shared_ptr< ObjState<T> >  GetCurrentState() const {
			if (!m_CurrentState.expired()){
				return m_CurrentState.lock();
			}
			return nullptr; 
		}
		shared_ptr< ObjState<T> >  GetPreviousState()const {
			if (!m_pPreviousState.expired()){
				return m_pPreviousState.lock();
			}
			return nullptr;
		}
		//--------------------------------------------------------------------------------------
		//	void  Update() const
		//	用途: ステートを更新する
		//	戻り値: なし
		//	＊メンバは変更しないのでconst関数で問題ない
		//--------------------------------------------------------------------------------------
		void Update() const{
			if (!m_CurrentState.expired() && !m_Owner.expired()){
				auto Ptr = m_CurrentState.lock();
				Ptr->Execute(m_Owner.lock());
			}
		}
		//--------------------------------------------------------------------------------------
		//	void  ChangeState(
		//	const shared_ptr< ObjState<T> >& NewState	//新しいステート
		//　);
		// 用途: ステートを変更する
		// 戻り値: なし
		//--------------------------------------------------------------------------------------
		void  ChangeState(const shared_ptr< ObjState<T> >& NewState){
			//元のステートを保存
			m_PreviousState = m_CurrentState;
			if (!m_CurrentState.expired() && !m_Owner.expired()){
				//元のステートに終了を知らせる
				auto Ptr = m_CurrentState.lock();
				Ptr->Exit(m_Owner.lock());
			}
			//新しいステートをカレントに設定
			m_CurrentState = NewState;
			if (!m_CurrentState.expired() && !m_Owner.expired()){
				//元のステートに終了を知らせる
				auto Ptr = m_CurrentState.lock();
				Ptr->Enter(m_Owner.lock());
			}
		}
		//--------------------------------------------------------------------------------------
		//	void RevertToPreviousState();
		// 用途: ステートを一つ前のステートに戻す
		// 戻り値: なし
		//--------------------------------------------------------------------------------------
		void RevertToPreviousState(){
			ChangeState(m_pPreviousState);
		}
		//--------------------------------------------------------------------------------------
		//bool IsInState(
		//const ObjState<T>& st	//調べるステート
		//)const;
		//用途: カレントステートが指定したステートになってるかどうかをチェック
		//戻り値: なし
		//--------------------------------------------------------------------------------------
		bool IsInState(const shared_ptr< ObjState<T> >& st)const{
			if (m_CurrentState.expired()){
				return false;
			}
			return typeid(m_CurrentState.lock()) == typeid(st);
		}
	};

	//--------------------------------------------------------------------------------------
	//	class ObjState;
	//	用途: ステート実装テンプレートクラス(抽象クラス)
	//--------------------------------------------------------------------------------------
	template <typename T>
	class EventState{
	public:
		//--------------------------------------------------------------------------------------
		//	EventState();
		//	用途: コンストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		EventState(){}
		//--------------------------------------------------------------------------------------
		//	virtual ~EventState();
		//	用途: デストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		virtual ~EventState(){}
		//--------------------------------------------------------------------------------------
		//	virtual void Enter(
		//	const shared_ptr<T>& Obj,		//ステートを保持するオブジェクト
		//	const shared_ptr<Event>& event				//送られたイベント（追加情報はこの中に入っている）
		//	) = 0;
		//	用途: ステートに入ったときに実行される
		//	戻り値: なし（純粋仮想関数）
		//--------------------------------------------------------------------------------------
		virtual void Enter(const shared_ptr<T>& Obj, const shared_ptr<Event>& event) = 0;
	};



	//--------------------------------------------------------------------------------------
	//	template <typename T>
	//	class EventMachine;
	//	用途: イベントマシン実装テンプレートクラス(抽象クラス)
	//	＊イベントステートを管理する
	//--------------------------------------------------------------------------------------
	template <typename T>
	class EventMachine
	{
	private:
		//このステートマシンを持つオーナー
		weak_ptr<T> m_Owner;
		//イベント文字列とイベントステートの組み合わせるマップ
		map<wstring, weak_ptr< EventState<T> > >  m_EventStateMap;
	public:
		//--------------------------------------------------------------------------------------
		//	EventMachine(
		//	const shared_ptr<T>& owner	//このイベントマシンを保持するオーナー
		//	);
		//	用途: コンストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		explicit EventMachine(const shared_ptr<T>& owner) :
			m_Owner(owner)
		{}
		//--------------------------------------------------------------------------------------
		//	virtual ~EventMachine();
		//	用途: デストラクタ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		virtual ~EventMachine(){}
		//--------------------------------------------------------------------------------------
		//	用途: Addアクセッサ
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		void AddEventState(const wstring& key,const shared_ptr< EventState<T> >& s){
			auto it = m_EventStateMap.find(key);
			if (it != m_EventStateMap.end()){
				//すでにある
				throw BaseException(
					L"すでにそのイベントは登録されています。",
					key,
					L"EventMachine::AddEventState()"
					);
			}
			m_EventStateMap[key] = s;
		}
		//--------------------------------------------------------------------------------------
		//	void HandleEvent(
		//	const shared_ptr<Event>& event	//イベント
		//	);
		//	用途: イベントをイベントステートに振り分ける
		//	戻り値: なし
		//--------------------------------------------------------------------------------------
		void HandleEvent(const shared_ptr<Event>& event){
			auto it = m_EventStateMap.find(event->m_MsgStr);
			if (it != m_EventStateMap.end()){
				auto Ptr = it->second;
				if (!Ptr.expired() && !m_Owner.expired()){
					auto Ptr2 = Ptr.lock();
					Ptr2->Enter(m_Owner.lock(), event);
				}
			}
		}
	};





}
//end basedx11

