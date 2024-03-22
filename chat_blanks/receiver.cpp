#include "receiver.h"
#include "util.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <thread>

Receiver::Receiver(std::shared_ptr<sf::TcpSocket> s,
        Queue<std::string> &q):
    m_socket(s),
    m_queue(q)
{
}

void Receiver::recv_loop()
{
    char buffer[256];
    {
        std::stringstream ss;
        ss << m_socket->getRemoteAddress() << ":" << m_socket->getRemotePort() << std::endl;
        std::cout << ss.str();
    }
    while(1)
    {
        std::memset(buffer, 0, 256);
        std::size_t received;
        //receive a message here
        if (m_socket->receive(buffer, 256, received) != sf::Socket::Done)
        {
            // error...
            std::cout << "ERROR" << std::endl;
            return;
        } 
        else 
        {
            //output
            std::stringstream ss;
            ss << "Received: \"" << buffer << "\", " << received << " bytes." << std::endl;
            std::cout << ss.str();
        }
        m_queue.push(std::string(buffer));
    }
}

