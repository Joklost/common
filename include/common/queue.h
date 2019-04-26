#ifndef COMMON_QUEUE_H
#define COMMON_QUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace common {

    template<class T, class Allocator = std::allocator<T>>
    class DoubleEndedQueue : public std::deque<T, Allocator> {
    public:
        DoubleEndedQueue() : std::deque<T, Allocator>(Allocator()) {}

        /**
         * Pop the first element and return a copy.
         * @return Copy of the first element.
         */
        T fpop() {
            T front = T{this->front()};
            this->pop_front();
            return front;
        };

        /**
         * Pop the last element and return a copy.
         * @return Copy of the last element.
         */
        T bpop() {
            T back = T(this->back());
            this->pop_back();
            return back;
        }
    };

    template<
            class T,
            class Container = std::vector<T>,
            class Compare = std::less<typename Container::value_type>
    >
    class PriorityQueue : public std::priority_queue<T, Container, Compare> {
    public:
        PriorityQueue() : std::priority_queue<T, Container, Compare>(Compare(), Container()) {}

        explicit PriorityQueue(const Compare &compare) : std::priority_queue<T, Container, Compare>(compare,
                                                                                                    Container()) {}

        /**
         * Returns a reference to the internal container.
         * When modifying the internal container, be very careful
         * not to modify the values used in the comparison function.
         * @return Reference to the internal container.
         */
        Container &get_container() {
            return this->c;
        }

        /**
         * Returns a const reference to the internal container.
         * @return Const reference to the internal container.
         */
        const Container &get_container() const {
            return this->c;
        }

        /**
         * Pop the first element and return a copy.
         * @return Copy of the first element.
         */
        T fpop() {
            T front = T{this->top()};
            this->pop();
            return front;
        };
    };

    template<typename T>
    class Queue {
    public:
        T pop();

        void pop(T &item);

        void push(const T &item);

        void push(T &&item);

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
    };

    template<typename T>
    T Queue<T>::pop() {
        std::unique_lock<std::mutex> mlock(mutex_);

        while (queue_.empty()) {
            cond_.wait(mlock);
        }

        auto item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    template<typename T>
    void Queue<T>::pop(T &item) {
        std::unique_lock<std::mutex> mlock(mutex_);

        while (queue_.empty()) {
            cond_.wait(mlock);
        }

        item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    template<typename T>
    void Queue<T>::push(const T &item) {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_.notify_one();
    }

    template<typename T>
    void Queue<T>::push(T &&item) {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_.notify_one();
    }

}

#endif /* COMMON_QUEUE_H */
