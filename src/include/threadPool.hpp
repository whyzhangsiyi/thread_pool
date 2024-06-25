#include <queue>

#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include "task.hpp"

namespace ziggy
{

    class threadPool
    {

        using ThreadFunc = std::function<void(void *)>;
        using unique_lock = std::unique_lock<std::mutex>;
        using Task=std::shared_ptr<task_>;

    private:
        enum class SCHEMA
        {

            FIXED,
            CACHED

        };

    private:
        std::mutex mt_;
        std::condition_variable cv_;

        std::queue<Task> taskQue_; // 对任务队列实现线程安全      //几乎必须使用std::shared_ptr<task>
        std::queue<std::thread> threadQue_;
        uint32_t maxTaskQueueSize_;
        uint32_t maxThreadQueueSize_; // 当模式为cached时有效
        SCHEMA schema_;

    private:
        // 线程函数,用于调度task队列力里的任务,消费者
        void
        threadFunc()
        {

            while ((true))
            {
                Task tk;

                {
                    unique_lock uk(mt_); // 线程安全的取出任务
                    cv_.wait(uk, [this]()
                             { return !taskQue_.empty(); });

                    tk = taskQue_.front();
                    taskQue_.pop();
                }

                // 调度代码

                (*tk)();
            }
        }

    public:
        threadPool(/* args */);
        ~threadPool();

        void start(){


        }

        void setMaxTaskQueueSize(uint32_t size)
        {
            maxTaskQueueSize_ = size;
        }

        void setMaxThreadQueueSize(uint32_t size)
        {
            maxThreadQueueSize_ = size;
        }

        void setThreadPoolSchema(SCHEMA modle){

            schema_=modle;

        }

        void submitTask(Task tk)
        { // 添加任务,生产者

            unique_lock uk(mt_);
            cv_.wait(uk, [this]()
                     { return taskQue_.size() < maxTaskQueueSize_; });
            taskQue_.emplace(std::move(tk));
        }

        
    };

    threadPool::threadPool(/* args */)
    {
    }

    threadPool::~threadPool()
    {
    }

}
