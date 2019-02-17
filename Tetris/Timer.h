#pragma once
#include "Subject.h"
#include "InitPrimitiveDataType.h"
#include <thread>
namespace MyObservarPattern
{
	class Deleter
	{
	public:
		template <typename T>
		void operator()(T* value);
	};
	template<typename T>
	inline void Deleter::operator()(T * value)
	{
		value->Dispose();
	}

	class Timer
	{
	public:
		Timer() 
		{
			mSubject = new Subject<int>();
		}

		Timer(int time)
		{
			isEnd = false;
			mSubject = new Subject<int>();
			/*
			毎秒処理を行う
			*/
			mThread = std::thread([&]() ->void
			{
				auto count = 0;
				while (true)
				{
					//1秒待機
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//終了するか
					if (isEnd) break;
					//カウントアップして登録されている関数を呼び出す
					count++;
					mSubject->OnNext(count);
				}
			});
		}

		Timer(int time, int take)
		{
			isEnd = false;
			mSubject = new Subject<int>();
			/*
			毎秒処理を行う
			*/
			mThread = std::thread([&]() ->void
			{
				auto count = 0;
				while (true)
				{
					//待機
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//終了するか
					if (isEnd) break;
					//カウントアップして登録されている関数を呼び出す
					count++;
					mSubject->OnNext(count);
					//指定された回数以上実行されていたら終了
					if (count >= take) break;
				}
			});
		}

		void StartTimer(int time) 
		{
			mThread = std::thread([&]() ->void
			{
				auto count = 0;
				while (true)
				{
					//待機
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//終了するか
					if (isEnd) break;
					//カウントアップして登録されている関数を呼び出す
					count++;
					mSubject->OnNext(count);
				}
			});
		}

		void EndTimer()
		{
			isEnd = true;
			mThread.join();
		}
		/*
		関数登録
		*/
		virtual void Subscribe
		(std::function<void(int value)> next)
		{
			mSubject->Subscribe(next);
		}
		virtual void Subscribe
		(std::function<void(int value)> next,
			std::function<void()> completed)
		{
			mSubject->Subscribe(next, completed);
		}
		virtual void Subscribe
		(std::function<void(int value)> next,
			std::function<void()> completed,
			std::function<void()> error)
		{
			mSubject->Subscribe(next, completed, error);
		}
		/*
		終了処理
		*/
		void Dispose()
		{
			isEnd = true;
			mThread.join();
			mSubject->OnCompleted();
			delete this;
		};
	private:
		Subject<int>* mSubject;
		std::thread mThread;
		bool isEnd;
		~Timer() {};
	};
}
