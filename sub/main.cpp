
#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main (int argc, char *argv [])
{
    zmq::context_t ctx;

    zmq::socket_t subscriber(ctx, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");
    subscriber.set(zmq::sockopt::subscribe, "A");

    while (1) {
        // Receive all parts of the message
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result =
                zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));
        assert(result && "recv failed");
        assert(*result == 2);

        std::cout << "Received: [" << recv_msgs[0].to_string() << "] "
                  << recv_msgs[1].to_string() << std::endl;
    }

    return 0;
}