#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <functional>
#include <list>
#include <mutex>

template <typename T>
class List
{
    public:
        void for_each(std::function<void(T)> f)
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            std::for_each(m_list.begin(), m_list.end(), f);
        }

        void push(const T& item)
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            m_list.push_back(item);
        }

        List()=default;
        List(const List&) = delete;            // disable copying
        List& operator=(const List&) = delete; // disable assignment

    private:
        std::list<T> m_list;
        std::mutex m_mutex;
};

#endif
