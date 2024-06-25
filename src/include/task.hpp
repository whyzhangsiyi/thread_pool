

#include <functional>
#include <memory>
#include <initializer_list>
#include <future>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include<vector>
#include<any>
namespace ziggy
{

    template<typename Derived>
    class task_
    {
    private:
        /* data */

    protected:
        task_(/* args */); // 子类可访问

    public:
        virtual void operator()()=0;
        ~task_();
    };

    task_::task_(/* args */)
    {
    }

    task_::~task_()
    {
    }

    template <typename Ret, typename... Args>
    class task : public task_
    {

    private:
        // class Result
        // {
        // private:
        //     Ret ret_;

        // public:
        //     Ret get()
        //     {
        //         return ret_;
        //     }
        //     void setRet(Ret ret)
        //     {

        //         ret_ = ret;
        //     }
        //     Result(/* args */){}
        //     ~Result(){}
        // };

    private:
        std::function<Ret(Args...)> cb_;
        std::mutex mt_;
        std::condition_variable cv_;
        bool isReturn_;
        Ret ret_;

    public:
        void operator()(Args... args)
        {

            std::unique_lock<std::mutex> lk(mt_);
            isReturn_ = false;
            ret_ = cb_(args...);
            isReturn_ = true;
            cv_.notify_all();
        }

        Ret wait_get()
        {

            std::unique_lock<std::mutex> lk(mt_);
            cv_.wait(lk, [this]()
                     { return isReturn_; });
            return ret_;
        }

        bool try_get(Ret &ret)
        {

            if (isReturn_)
            {
                ret = ret_;
                return true;
            }
            return false;
        }

        task(std::function<Ret(Args...)>);
        ~task();
    };

    template <typename Ret, typename... Args>
    task<Ret, Args...>::task(std::function<Ret(Args...)> cb)
    {
        cb_ = cb;
    }

    template <typename Ret, typename... Args>
    task<Ret, Args...>::~task()
    {
    }

} // namespace ziggy
