//
// Created by hk on 7/16/23.
//
//#include <hl/version_check/boost_impl.h>
//#include <hl/net_driver.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>

//客户端
class client
{
public:
    client(boost::asio::io_service& io_service,
           const std::string& server, const std::string& path)
            : resolver_(io_service),
              socket_(io_service)
    {
        boost::asio::ip::tcp::resolver::query query(server, "8888");//10086为端口号
        resolver_.async_resolve(query,
                                boost::bind(&client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::iterator));
    }

private:
    char _buffer[1024];

    void handle_resolve(const boost::system::error_code& err,
                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    {
        if (!err)
        {
            // Attempt a connection to each endpoint in the list until we
            // successfully establish a connection.
            boost::asio::async_connect(socket_, endpoint_iterator,
                                       boost::bind(&client::handle_connect, this,
                                                   boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_connect(const boost::system::error_code& err)
    {
        if (!err)
        {
            boost::asio::async_read(socket_, boost::asio::buffer(_buffer, 1024),
                                    boost::bind(&client::handle_read, this, _1, _2));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_read(const boost::system::error_code& err, size_t s)
    {
        if (!err)
        {
            std::cout  << " client recv:"  << _buffer << "\n";

            boost::asio::async_write(socket_, boost::asio::buffer("2", 1), boost::bind(&client::handle_write, this, _1, _2));

        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_write(const boost::system::error_code& err, size_t s)
    {
        if (!err)
        {
            memset(_buffer, '\0', 1024);
            boost::asio::async_read(socket_, boost::asio::buffer(_buffer, 1),
                                    boost::bind(&client::handle_read, this, _1, _2));

        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }


    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf request_;
    boost::asio::streambuf response_;
};


int main()
{

    boost::asio::io_service io_service;                //开启客户端
    client c(io_service, "127.0.0.1", "");
    io_service.run();

}

