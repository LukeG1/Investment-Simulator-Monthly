// #include <iostream>
// #include <thread>
// #include <vector>
// #include <queue>
// #include <functional>
// #include <mutex>
// #include <condition_variable>
// #include <optional>
// #include <atomic>

// // ========== Thread-Safe Queue ==========
// template <typename T>
// class ThreadSafeQueue
// {
// public:
//     void push(T value)
//     {
//         std::unique_lock<std::mutex> lock(mtx_);
//         queue_.push(std::move(value));
//         cv_.notify_one();
//     }

//     std::optional<T> pop()
//     {
//         std::unique_lock<std::mutex> lock(mtx_);
//         cv_.wait(lock, [&]
//                  { return !queue_.empty(); });
//         T val = std::move(queue_.front());
//         queue_.pop();
//         return val;
//     }

// private:
//     std::queue<T> queue_;
//     std::mutex mtx_;
//     std::condition_variable cv_;
// };

// // ========== Thread Pool ==========
// class ThreadPool
// {
// public:
//     ThreadPool(size_t num_threads) : stop_(false)
//     {
//         for (size_t i = 0; i < num_threads; ++i)
//         {
//             workers_.emplace_back([this]
//                                   {
//                 while (true) {
//                     std::function<void()> task;

//                     {   // scope for lock
//                         std::unique_lock<std::mutex> lock(this->queue_mutex_);
//                         this->condition_.wait(lock, [this] {
//                             return this->stop_ || !this->tasks_.empty();
//                         });
//                         if (this->stop_ && this->tasks_.empty())
//                             return;
//                         task = std::move(this->tasks_.front());
//                         this->tasks_.pop();
//                     }

//                     task();  // Run task
//                 } });
//         }
//     }

//     // Add task to pool
//     void enqueue(std::function<void()> task)
//     {
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);
//             tasks_.push(std::move(task));
//         }
//         condition_.notify_one();
//     }

//     // Shutdown
//     ~ThreadPool()
//     {
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);
//             stop_ = true;
//         }
//         condition_.notify_all();
//         for (std::thread &worker : workers_)
//             worker.join();
//     }

// private:
//     std::vector<std::thread> workers_;
//     std::queue<std::function<void()>> tasks_;

//     std::mutex queue_mutex_;
//     std::condition_variable condition_;
//     bool stop_;
// };

// // ========== Simulated Work Function ==========
// int some_function(int i, int j)
// {
//     return i * j;
// }

// // ========== Collector Function ==========
// void collector_func(ThreadSafeQueue<std::optional<int>> &result_queue,
//                     std::vector<int> &final_results)
// {
//     while (true)
//     {
//         auto item = result_queue.pop();
//         if (!item.has_value())
//             break; // Sentinel
//         final_results.push_back(item.value());
//     }
// }

// // ========== Main ==========
// int main()
// {
//     int n = 20; // number of 'i'
//     int k = 5;  // number of 'j' per 'i'

//     // Results
//     ThreadSafeQueue<std::optional<int>> result_queue;
//     std::vector<int> final_results;

//     // Collector thread
//     std::thread collector(collector_func, std::ref(result_queue), std::ref(final_results));

//     // Thread pool with hardware concurrency or fallback
//     size_t num_threads = std::thread::hardware_concurrency();
//     if (num_threads == 0)
//         num_threads = 4;
//     ThreadPool pool(num_threads);

//     // Enqueue one task per `i`
//     for (int i = 0; i < n; ++i)
//     {
//         pool.enqueue([i, k, &result_queue]()
//                      {
//             for (int j = 0; j < k; ++j) {
//                 int result = some_function(i, j);
//                 result_queue.push(result);
//             } });
//     }

//     // Shutdown collector
//     pool.enqueue([&result_queue]()
//                  {
//                      result_queue.push(std::nullopt); // Sentinel
//                  });

//     collector.join();

//     // Output
//     std::cout << "Collected results:\n";
//     for (int val : final_results)
//     {
//         std::cout << val << " ";
//     }
//     std::cout << "\n";

//     return 0;
// }

#include "simulation.h"

int main()
{
    for (auto _ = 0; _ < 1; _++)
        simulate_lifetime();
    return 0;
}