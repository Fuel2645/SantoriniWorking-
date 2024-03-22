#include "queue.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

int main()
{
    // Add bcast udp
    // 1. create a UDP socket
    // 2. send a broadcast message
    // 3. set the socket to non blocking
    // 4. wait 100 ms
    // 5. receive a message
    // 6. if received worked, we can connect
    // 7. else
    // 7.1 create a thread that runs the server
    // 7.2 wait a bit
    // 7.3 mark localhost as the address of the server
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    sf::Socket::Status status = socket->connect("152.105.66.61", PORT);
    if (status != sf::Socket::Done) 
    {
        std::cerr << "Error connecting\n";
        return 1;
    }
    std::cout << "Connected\n";
    Queue<std::string> queue;

    // Launch a receiver thread to receive messages from the server.
    Receiver receiver(socket, queue);
    std::thread recv_thread(&Receiver::recv_loop, &receiver);

    std::string s = "";
    while (1)
    {
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;

        // Send messages to the server
        if (socket->send(s.c_str(), s.size() + 1) != sf::Socket::Done)
        {
            std::cerr << "Error sending\n"; 
            return 1;
        }
        
    }
    recv_thread.join();
    return 0;
}
