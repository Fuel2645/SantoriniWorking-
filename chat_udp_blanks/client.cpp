#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <tuple>

int main()
{
    std::shared_ptr<sf::UdpSocket> socket_ptr = std::make_shared<sf::UdpSocket>();
    // Sending a "register" message
    std::string userName;
    std::cout << "Please type in your user name: ";
    std::cin >> userName; // Not a getline

    // sf::Packet Packet;
    // Packet<<"register:"<<userName;
    std::string reg = "register:" + userName;
    // TODO: send the registration message consisting of the user name.
    if (socket_ptr->send(reg.c_str(), reg.size(),sf::IpAddress::getLocalAddress(),PORT) != sf::Socket::Done)
    {
        std::cout <<" Error registering to server " << '\n';
    }
    // register:userName

    Queue<message> q;
    // TODO: launch a receiver thread
    Receiver R(socket_ptr, q);
    std::thread tR(&Receiver::recv_loop, &R);

    tR.detach();

    std::string s = "";
    std::getline(std::cin, s); // Flushing the last end of line
    while (true)
    {
        // 1 Input from the player
        s = "";
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        // 1.1 send the new input to the server

        
        // 1.2 receive messages from the server

        // In the game client, we want to process received messages here.
        // TODO: send the message to the server

        // Packet.clear();
        //Packet<<"Message:" << s<< '\n';

        std::string message = "message: " + s;
        if(socket_ptr->send(message.c_str(),message.size(), "localhost", PORT))
        {
            std::cout << "Error sending message " << '\n';
        }



         // message:s
        std::stringstream ss;
        ss << "message:" << s;
        // 2 Simulate the game world
        // 3 Render
    }
    return 0;
}
