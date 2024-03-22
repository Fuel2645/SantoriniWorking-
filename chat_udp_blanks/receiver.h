#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "queue.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <tuple>

class Receiver {
    public:
        Receiver(std::shared_ptr<sf::UdpSocket> s, Queue<message>& queue);
        void recv_loop();
    private:
        std::shared_ptr<sf::UdpSocket> m_socket;
        Queue<message> &m_queue;
};
#endif
