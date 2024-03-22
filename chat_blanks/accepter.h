#ifndef ACCEPTER_HPP
#define ACCEPTER_HPP

#include "queue.h"
#include "list.h"
#include <SFML/Network.hpp>

class Accepter {
    private:
        Queue<std::string>& m_queue;
        List<std::shared_ptr<sf::TcpSocket>>& m_socket;

    public:
        Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s);
        void operator()();
};


#endif
