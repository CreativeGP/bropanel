#include "greatpanel.h"

void GreatPanel::end() {
    try {        
        sv.stop_listening();
        sv.close(this->connhdl, websocketpp::close::status::normal, "exit");
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}
    
void GreatPanel::run() {
    conn_thread = std::thread(
        [&]{
            try {
                sv.set_access_channels(websocketpp::log::alevel::all);
                sv.clear_access_channels(websocketpp::log::alevel::frame_payload);

                sv.init_asio();

                sv.set_message_handler([&](websocketpp::connection_hdl hdl, message_ptr msg)
                                       {
                                           this->on_message(&sv, hdl, msg);

                                           if (msg->get_payload() == "stop-listening") {
                                               sv.stop_listening();
                                               return;
                                           }
                                       });

                sv.set_open_handler([&](websocketpp::connection_hdl hdl)
                                    {
                                        std::cout << "new connection opened." << std::endl;
                                        if (conn_count != 0) {
                                            std::cout << "over two connected!! close old one." << std::endl;
                                            sv.close(this->connhdl, websocketpp::close::status::normal, "exit");
                                            conn_count--;
                                        }
                                        this->connhdl = hdl;
                                        conn_count++;
                                    });
                    
                sv.listen(boost::asio::ip::tcp::v4(), this->wsport);
                sv.start_accept();
                sv.run();
            } catch (websocketpp::exception const & e) {
                std::cout << e.what() << std::endl;
            } catch (...) {
                std::cout << "other exception" << std::endl;
            }
        });

    system("chromium index.html");
}

void GreatPanel::send(std::string msg, int op) {
    try {
        sv.send(this->connhdl, msg, (websocketpp::frame::opcode::value) op);
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
}
