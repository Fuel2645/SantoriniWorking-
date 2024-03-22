#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <mutex>

template <typename K, typename V>
class Map
{
    public:
        unsigned short size()
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            return m_map.size();
        }

        void for_each(std::function<void(std::pair<K, V>)> f)
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            std::for_each(m_map.begin(), m_map.end(), f);
        }

        void insert(const std::pair<K, V>& p)
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            auto it = m_map.find(p.first);
            if (it == m_map.end())
            {
                m_map.insert(p);
            }
        }

        Map()=default;
        Map(const Map&) = delete;            // disable copying
        Map& operator=(const Map&) = delete; // disable assignment

    private:
        std::map<K, V> m_map;
        std::mutex m_mutex;
};

#endif
