#include "map.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <tuple>

int main()
{
    Queue<message> queue;
    std::shared_ptr<sf::UdpSocket> socket_ptr = std::make_shared<sf::UdpSocket>();
    // TODO: we need to bind our socket to a port

    if(socket_ptr->bind(PORT)!= sf::Socket::Done)
    {
        std::cout << "Error Binding" << '\n';
    }

    Receiver receiver{socket_ptr, queue};
    // TODO: we need to start a receiver thread.
    std::thread RecThread(&Receiver::recv_loop, &receiver);


    // This is tricky:
    // We want to identify the clients by their nicknames?   [[[pp]]]
    // Alternatively we could identify the clients with their port numbers.
    // The reason is that all clients are running on the same machine.
    // They will all have a different port number but the same address.
    Map<std::string, peer> peers; // list of clients
    // std::vector<unsigned short> peers;
    while(true)
    {
        std::cout << "Server main thread: peers listing\n";
        std::cout << "*********************************\n";
        peers.for_each([](message m) {
                std::cout << m.first <<
                " " << m.second.first <<
                " " << m.second.second << std::endl; });
        std::cout << "*********************************\n";
        message m = queue.pop(); 
        // m = (string, (ipAddress, port))
        // if m.first is a register message
        //   then we should add the (userName, m.second) to peers
        // else
        //   distribute the message to the peers
        std::cout << "Server main read: \"" << 
        m.first << "\" " << peers.size() << std::endl;
        
        std::string s = m.first;
        std::string delimiter = ":";
        size_t pos = s.find(delimiter);
        std::string command = s.substr(0, pos); // command is either
        
        // "register" or "message"
        // "register:myUserName"
        // "message:Here is my message"
        s.erase(0, pos + delimiter.length()); // getting rid of register:
        // s should be the userName/message
        if (command == "register")
        {
            std::cout << "Adding new peer: " << command << " " << s << std::endl;
            // TODO insert the peer in the map


            peer newPeer;
            peers.insert(std::make_pair(s, m.second));

            // Can only do one register for one user name
        }
        else if(command == "message")
        {
            // We need to send the message to everyone in peers.
            // We need to do it in a thread safe way.
            std::cout << "Sending message: " << s << std::endl;
            auto send = [&] (std::pair<std::string, peer> p)
                // p == (string, (IpAddress, port))
            {
                // TODO send to one peer
                socket_ptr->send(s.c_str(), s.size(), p.second.first, p.second.second);

            };
            // TODO: we send to every peer
            peers.for_each(send);
        }
        else
        {

        }
    }
    return 0;
}
