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
			���b�������s��
			*/
			mThread = std::thread([&]() ->void
			{
				auto count = 0;
				while (true)
				{
					//1�b�ҋ@
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//�I�����邩
					if (isEnd) break;
					//�J�E���g�A�b�v���ēo�^����Ă���֐����Ăяo��
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
			���b�������s��
			*/
			mThread = std::thread([&]() ->void
			{
				auto count = 0;
				while (true)
				{
					//�ҋ@
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//�I�����邩
					if (isEnd) break;
					//�J�E���g�A�b�v���ēo�^����Ă���֐����Ăяo��
					count++;
					mSubject->OnNext(count);
					//�w�肳�ꂽ�񐔈ȏ���s����Ă�����I��
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
					//�ҋ@
					std::this_thread::sleep_for(std::chrono::seconds(time));
					//�I�����邩
					if (isEnd) break;
					//�J�E���g�A�b�v���ēo�^����Ă���֐����Ăяo��
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
		�֐��o�^
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
		�I������
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
