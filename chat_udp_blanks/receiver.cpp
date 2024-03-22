#include "receiver.h"
#include "util.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <thread>
#include <tuple>

Receiver::Receiver(std::shared_ptr<sf::UdpSocket> s,
        Queue<message> &q):
    m_socket(s),
    m_queue(q)
{
}

void Receiver::recv_loop()
{
    char buffer[256];
    std::size_t received;
    sf::IpAddress address;
    unsigned short port;
    while(true)
    {
        std::memset(buffer, 0, 256);
        // TODO: receive a message into buffer
        if(m_socket->receive(buffer,256,received,address,port) != sf::Socket::Done)
        {
                std::cout << "Error" << '\n';
        }
        // Note that the queue of messages, now takes note of the peer
        // (address, port).
        std::cout << "Received \"" << buffer << "\"" << std::endl;
        m_queue.push(std::make_pair(std::string(buffer),
                      std::make_pair(address, port)));
    }
}

