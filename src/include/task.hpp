

#include <functional>
#include <memory>
#include <initializer_list>
#include <future>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <vector>
#include <any>
namespace ziggy
{

    class anytask
    {

    private:
        class task_
        {
        public:
            // virtual void operator()() = 0;
            task_() {}
            virtual ~task_() {}
        };

        template <typename Ret, typename... Args>
        class task : public task_
        {
        private:
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

            task(std::function<Ret(Args...)> cb)
            {
                cb_ = cb;
            }
            ~task() {}
        };

    private:
        std::unique_ptr<task_> task_ptr;

        template <typename Ret, typename... Args>
        anytask(std::function<Ret(Args...)> cb) {

            task_ptr=std::make_unique<task<Ret, Args...>>(cb);
        }



        
    };

} // namespace ziggy