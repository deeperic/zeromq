#include <iostream>
#include <thread>
#include <chrono>
#include <zmq.hpp>

int main (int argc, char *argv [])
{
    zmq::context_t ctx;

    zmq::socket_t publisher(ctx, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");

    // Give the subscribers a chance to connect, so they don't lose any messages
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //send two envelope: A and B
    //subscriber could subscribe "A", "B", or "" for all
    publisher.send(zmq::str_buffer("A"), zmq::send_flags::sndmore);
    publisher.send(zmq::str_buffer("Message in A envelope"));

    publisher.send(zmq::str_buffer("B"), zmq::send_flags::sndmore);
    publisher.send(zmq::str_buffer("Message in B envelope"));

    int c = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        //send envelope
        publisher.send(zmq::str_buffer("A"), zmq::send_flags::sndmore);

        //send message
        std::stringstream ss;
        ss << "message#: " << ++c;
        zmq::message_t message(ss.str().c_str(), ss.str().length());
        publisher.send(message, zmq::send_flags::none);

    }

    return 0;
}
