//#include "stdafx.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>

using namespace boost::asio;
using namespace std;

int num_count = 0;
class server
{
    typedef server this_type;
    typedef ip::tcp::acceptor acceptor_type;
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;
    typedef ip::address address_type;
    typedef boost::shared_ptr<socket_type> sock_ptr;

private:
    io_service m_io;
    acceptor_type m_acceptor;

public:
    server() : m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 8888))
    {    accept();    }

    void run(){ m_io.run();}

    void accept()
    {
        printf("accept()\n");
        sock_ptr sock(new socket_type(m_io));
        m_acceptor.async_accept(*sock, boost::bind(&this_type::accept_handler, this, boost::asio::placeholders::error, sock));
    }

    void accept_handler(const boost::system::error_code& ec, sock_ptr sock)
    {
        if (ec)
        {    return;    }

        ++num_count;
        char b[1024];
//        char _buffer[1024];

        std::string s_tmp = to_string(num_count);
        int i =0;
        for (; i < to_string(num_count).size(); ++i) {
            b[i] = s_tmp[i];
        }
        b[i] = '\0';

        cout<<"-->> Client: ";
        cout<<sock->remote_endpoint().address() << " " << num_count << " " << endl;
        sock->async_write_some(buffer(b), boost::bind(&this_type::accept_handler, this, boost::asio::placeholders::error, sock));
//        sock->async_write_some(buffer(to_string(num_count)), boost::bind(&this_type::write_handler, this, boost::asio::placeholders::error));
//        sock->async_write_some(buffer("hello asio "), boost::bind(&this_type::write_handler, this, boost::asio::placeholders::error));
        // 发送完毕后继续监听，否则io_service将认为没有事件处理而结束运行
//        accept();
        sleep(5);

    }

    void write_handler(const boost::system::error_code&ec)
    {
        cout<<"send msg complete"<<endl;
    }
};

int main()
{
    try
    {
        cout<<"Server start."<<endl;
        server srv;
        srv.run();
    }
    catch (std::exception &e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}