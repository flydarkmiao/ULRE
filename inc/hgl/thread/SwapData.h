#ifndef HGL_THREAD_SWAP_DATA_INCLUDE
#define HGL_THREAD_SWAP_DATA_INCLUDE

#include<hgl/thread/ThreadMutex.h>
#include<hgl/thread/Semaphore.h>

namespace hgl
{
    /**
     * 单向多线程数据交换模板<br>
     * 适用环境为多个线程向其投递数据，一个线程接收数据。接收方在每次处理前交换数据指针，以达到最小线程切换代价
     */
    template<typename T> class SwapData
    {
    protected:

        T data[2];

        int post_index;
        int recv_index;

        ThreadMutex lock;

    protected:

        void _Swap()
        {
            if(recv_index){recv_index=0;post_index=1;}
                      else{recv_index=1;post_index=0;}
        }

    public:

        SwapData()
        {
            recv_index=0;
            post_index=1;
        }

        virtual ~SwapData()=default;

        /**
         * 获取投递方数据访问权
         */
        T &GetPost()
        {
            lock.Lock();

            return data[post_index];
        }

        /**
         * 释放多线程投递方数据访问权
         */
        void ReleasePost()
        {
            lock.Unlock();
        }

        /**
        * 取得接收方数据访问权
        */
        T &GetReceive(){return data[recv_index];}

        /**
         * 交换双方数据
         */
        void Swap()
        {
            lock.Lock();

            this->_Swap();

            lock.Unlock();
        }

        /**
         * 尝试交换双方数据
         */
        bool TrySwap()
        {
            if(!lock.TryLock())
                return(false);

            this->_Swap();

            lock.Unlock();
            return(true);
        }

#ifndef __APPLE__
        /**
         * 尝试交换双方数据
         */
        bool WaitSwap(const double time_out)
        {
            if(!lock.WaitLock(time_out))
                return(false);

            this->_Swap();

            lock.Unlock();
            return(true);
        }
#endif//__APPLE__
    };//template<typename T> class SwapData

    /**
    * 信号自动交换数据访问模板
    */
    template<typename T> class SemSwapData:public SwapData<T>
    {
        Semaphore sem;

    public:

        using SwapData<T>::SwapData;
        ~SemSwapData()=default;

        /**
        * 释放接收信号
        * @param count 信号个数
        */
        void PostSem(int count=1)
        {
            sem.Post(count);
        }

        /**
        * 等待获取一个信号并交换前后台数据
        * @param time_out 等待时长
        */
        bool WaitSemSwap(const double time_out=5)
        {
            if(!sem.Acquire(time_out))
                return(false);

            this->Swap();
            return(true);
        }

        /**
        * 尝试获取一个信号并交换前后台数据
        */
        bool TrySemSwap()
        {
            if(!sem.TryAcquire())
                return(false);

            this->Swap();
            return(true);
        }
    };//template<typename T> class SemSwapData:public SwapData<T>

    /**
     * SwapData模板自动释放Post工具模板
     */
    template<typename T> class PostToSwapData
    {
        SwapData<T> *swap_data;
        T *post;

    public:

        PostToSwapData(SwapData<T> *sd)
        {
            swap_data=sd;

            if(swap_data)
                post=&(swap_data->GetPost());
            else
                post=nullptr;
        }

        ~PostToSwapData()
        {
            if(swap_data)
                swap_data->ReleasePost();
        }

        T *operator ->(){return post;}
    };//template<typename T> class PostToSwapData

    /**
     * SemSwapData模板自动释放Post工具模板
     */
    template<typename T> class PostToSemSwapData
    {
        SemSwapData<T> *swap_data;
        T *post;

    public:

        PostToSemSwapData(SemSwapData<T> *sd)
        {
            swap_data=sd;

            if(swap_data)
                post=&(swap_data->GetPost());
            else
                post=nullptr;
        }

        ~PostToSemSwapData()
        {
            if(swap_data)
            {
                swap_data->ReleasePost();
                swap_data->PostSem();
            }
        }

        T *operator ->(){return post;}
    };//template<typename T> class PostToSemSwapData

    /**
     * 使用范例
     *
     * using EventQueue=Queue<int>;
     * using MTEventQueue=SemSwapData<EventQueue>;
     * using MTEventPost=PostToSemSwapData<EventQueue>;
     *
     * MTEventQueue mt_event_queue;
     *
     * 新方式:
     * MTEventPost post(mt_event_queue);
     *
     * post.Push(1);
     *
     * 直接模式:
     * EventQueue &eq=mt_event_queue.GetPost();
     *
     * eq->Push(1);
     *
     * mt_event_queue.ReleasePost();
     * mt_event_queue.PostSem();
     *
     */
}//namespace hgl
#endif//HGL_THREAD_SWAP_DATA_INCLUDE
