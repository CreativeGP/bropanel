#if !defined(GREATPANEL_H)

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <queue>
#include <functional>
#include <stdlib.h>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;
typedef server::connection_type::ptr connection_ptr;

class GreatPanel {

    typedef std::function<void(server* s, websocketpp::connection_hdl hdl, message_ptr msg)> on_message_fn_t;

public:
    std::thread conn_thread;
    websocketpp::connection_hdl connhdl;
    server sv;
    int wsport;
    int conn_count = 0;
    on_message_fn_t on_message;

    GreatPanel() {};
    GreatPanel(int port) : wsport(port) {};
    GreatPanel(int port, on_message_fn_t onm) : wsport(port), on_message(onm) {};

    void end();
    void run();
    void send(std::string msg, int op = 1);
};


#define GREATPANEL_H
#endif
