module;

import <queue>;
import <mutex>;

export module ThreadSafeQueue;


export template<typename T> class TQueue
{
	protected:
		std::mutex muxQueue;
		std::mutex muxBlocking;
		std::condition_variable cvBlocking;
		std::queue<T> queue{};

	public:
		TQueue() = default;
		TQueue(const TQueue<T>&) = delete;
		~TQueue() { clear(); }

		const T& front()
		{
			std::scoped_lock lock(muxQueue);
			return queue.front();
		}
		const T& back()
		{
			std::scoped_lock lock(muxQueue);
			return queue.back();
		}
		T pop()
		{
			std::scoped_lock lock(muxQueue);
			if (queue.empty())
				return T(0);

			auto t = queue.front();
			queue.pop();
			return t;
		}

		void push(const T& item)
		{
			std::scoped_lock lock(muxQueue);
			queue.push(item);

			std::unique_lock<std::mutex> ul(muxBlocking);
			cvBlocking.notify_one();
		}
		bool empty()
		{
			std::scoped_lock lock(muxQueue);
			return queue.empty();
		}
		size_t count()
		{
			std::scoped_lock lock(muxQueue);
			return queue.size();
		}
		void clear()
		{
			std::scoped_lock lock(muxQueue);
			queue.clear();
		}
		void wait()
		{
			while (empty())
			{
				std::unique_lock ul(muxBlocking);
				cvBlocking.wait(ul);
			}
		}
};


