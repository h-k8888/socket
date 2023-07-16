#pragma once

#include <boost/asio.hpp>

	class chat_room;
	class DeviceController;

	enum ProcessorState
	{
		INITIATE = 0x10000,    // client register to server, server reset client
		CUSTOM = 0x2000,       // EMPTY, reset to COMING; !EMPTY, reset to INITIATE
		COORDINATION = 0x1000, // EMPTY
		REGISTER = 0xFFF,    // client register to server, server reset client
		EMPTY = 0,
		//CASE = 0x01,          // !EMPTY || EMPTY(COORDINATION)
		CLOSED = 0x20,        // !EMPTY
		OPENED = 0x10,        // !EMPTY
		STOP = 0x03,          // !EMPTY
		RUNNING = 0x02,       // !EMPTY
		COMING = 0x01,        // EMPTY
	};

	class DeviceServer
	{
	public:
		DeviceServer(boost::asio::io_service& io_context,
			const boost::asio::ip::tcp::endpoint& endpoint, DeviceController* controller);
		void setController(DeviceController* controller);
		void stop();

	private:
		void do_accept();

		boost::asio::ip::tcp::acceptor m_acceptor;
		chat_room* m_room;
		DeviceController* m_controller;
	};

