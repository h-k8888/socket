#include "DeviceServer.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>

#include <vector>
#include <utility>
#include <boost/system/system_error.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/ref.hpp>

//#include "DeviceMessage.h"
//#include "DeviceController.h"
using namespace std;
	//----------------------------------------------------------------------

	//----------------------------------------------------------------------
	
	static std::string DATA_COMMA(",");
//	class Participant
//	{
//	public:
//		virtual ~Participant() {}
//
//		virtual void deliver(const DeviceMessage& msg) = 0;
//
//		bool withType(int type)
//		{
//			return (m_p_type & type) == type;
//		}
//
//		void setType(int type)
//		{
//			m_p_type = type;
//		}
//
//		bool atCode(int code)
//		{
//			return (m_code & code) == code;
//		}
//
//		void setIndex(int index)
//		{
//			m_index = index;
//		}
//
//		int getIndex()
//		{
//			return m_index;
//		}
//
//		void setCode(int code)
//		{
//			m_code = code;
//		}
//
//		bool isState(int state)
//		{
//			return (m_state & state) == state;
//		}
//
//		void setState(int state)
//		{
//			m_state = state;
//		}
//
//	private:
//		int m_p_type = 0;
//		int m_index = 0;
//		int m_code = 0;
//		int m_state = 0;
//	};
//	typedef std::shared_ptr<Participant> Participant_ptr;
//
//	class chat_room
//	{
//	public:
//		chat_room()
//			: m_controller(nullptr)
//		{
//
//		}
//
//		void join(Participant_ptr participant)
//		{
//			m_participants.insert(participant);
//		}
//
//		void leave(Participant_ptr participant)
//		{
//			m_participants.erase(participant);
//		}
//
//		void receive(Participant_ptr participant, const DeviceMessage& msg)
//		{
//			if (m_controller != nullptr)
//			{
//				std::lock_guard<std::mutex> guard(m_states_mutex);
//				std::string body(msg.body(), msg.body_length());
//				std::size_t pos = body.find(DATA_COMMA);//��һ��","
//				int code = 0, type = 0,lidar_index = -1;
//				int coming_index = -1;
//				std::size_t last = std::string::npos;
//				if (pos != std::string::npos)
//				{
//					last = pos + 1;
//					type = std::stoi(body.substr(0, pos));
//				}
//				else
//				{
//					type = std::stoi(body);
//				}
//
//				if ((type & ProcessorState::INITIATE) == ProcessorState::INITIATE)
//				{
//					if (pos != std::string::npos)
//					{
//						pos = body.find(DATA_COMMA, last);//�ڶ���","
//						if (pos != std::string::npos)
//						{
//							code = std::stoi(body.substr(last, pos - last));
//							last = pos + 1;
//
//						}
//						else
//						{
//							code = std::stoi(body.substr(last));
//						}
//						if (code != 0)
//						{
//							participant->setCode(code);
//							if (m_code_state.find(code) == m_code_state.end())
//							{
//								m_code_state.insert({ code, ProcessorState::EMPTY });
//							}
//							auto csvi = m_code_sta_tt.find(code);
//							if (csvi == m_code_sta_tt.end())
//							{
//								std::vector<int> _sta_tt;
//								_sta_tt.push_back(0);
//								m_code_sta_tt.insert({ code, _sta_tt });
//							}
//							else
//							{
//								csvi->second.push_back(0);
//							}
//						}
//
//						// index//
//						pos = body.find(DATA_COMMA, last);////������","   ��ȡindex
//						if (pos != std::string::npos)
//						{
//							lidar_index = std::stoi(body.substr(last, pos - last));
//							last = pos + 1;
//
//						}
//						cout << "lidar_index Register : " << lidar_index  << endl;
//						participant->setIndex(lidar_index);
//
//						int data_type = 0;
//						while (pos != std::string::npos)
//						{
//							pos = body.find(DATA_COMMA, last);
//							if (pos != std::string::npos)
//							{
//								data_type |= std::stoi(body.substr(last, pos));
//								last = pos + 1;
//							}
//							else
//							{
//								data_type |= std::stoi(body.substr(last));
//							}
//						}
//						if (data_type != 0)
//						{
//							participant->setType(data_type);
//						}
//
//					}
//				}
//				else // process code state
//				{
//					int _tt = -1;
//					auto csi = m_code_state.begin();
//					for (; csi != m_code_state.end(); csi++)
//					{
//						if (participant->atCode(csi->first))
//						{
//							code = csi->first;
//							_tt = csi->second;
//							break;
//						}
//					}
//					int temp_tt = -1;
//					if (csi == m_code_state.end())
//					{
//						std::cout << "participant no code!!!" << std::endl;
//						return;
//					}
//
//					if (type == 1)//������
//					{
//						coming_index = participant->getIndex();// std::stoi(body.substr(pos, pos + 1));
//						cout << "coming_index : " << coming_index << endl;
//					}
//
//					std::vector<double> position;
//					while (pos != std::string::npos)
//					{
//						last = pos + 1;
//						pos = body.find(DATA_COMMA, last);
//						if (pos != std::string::npos)
//						{
//							position.push_back(std::stod(body.substr(last, pos - last)));
//						}
//						else
//						{
//							position.push_back(std::stod(body.substr(last)));
//						}
//					}
//					auto csvi = m_code_sta_tt.begin();
//					for (; csvi != m_code_sta_tt.end(); csvi++)
//					{
//						if (participant->atCode(csvi->first))
//						{
//							break;
//						}
//					}
//					if (csvi != m_code_sta_tt.end())
//					{
//						temp_tt = _tt;
//					}
//					else
//					{
//						return;
//					}
//					csvi->second[participant->getIndex()] = type;
//					temp_tt = check_status(csvi->second, _tt);
//					bool needResponse = (temp_tt != _tt);// = process(participant, type, position);
//					if (needResponse || type == 2)
//					{
//						csi->second = temp_tt;
//						std::string client_data;
//						client_data.append(std::to_string(type));
//						if ((type == 1) && (coming_index != -1))//������
//						{
//							client_data.append(",");
//							client_data.append(std::to_string(coming_index));
//						}
//						std::cout << "server sendmsg : " << client_data << std::endl;
//						DeviceMessage msg;
//						msg.body_length(client_data.length());
//						std::memcpy(msg.body(), client_data.c_str(), msg.body_length());
//						msg.encode_header();
//						deliver(msg);
//					}
//					auto iter = m_code_sta_tt.begin();
//					if (needResponse || (position.size() > 0))
//					{
//						execute(code, csi->second, position);//���ƴ�С���ȷ�ָ��
//					}
//				}
//			}
//			else
//			{
//				deliver(msg);
//			}
//		}
//
//		void deliver(const DeviceMessage& msg)
//		{
//			for (auto participant : m_participants)
//				participant->deliver(msg);
//		}
//
//		void setController(DeviceController* controller)
//		{
//			m_controller = controller;
//		}
//
//	private:
//
//		void execute(int code, int state, std::vector<double>& pos)
//		{
//			if (m_controller != nullptr)
//			{
//				cout << "code  state" <<  code<< " " << state <<"pos size" << pos.size()<< endl;
//				//m_controller->doAction(code, state);
//				m_controller->doAction(state, code, pos);
//			}
//		}
//
//		int check_status(std::vector<int> vec, int current_status)
//		{
//			int status = current_status;
//			switch (current_status) {
//				case 0:
//				{
//					vector<int>::iterator result_1 = find(vec.begin(), vec.end(), 1); //����1,����
//					if (result_1 != vec.end()) //�ҵ�
//						status = 1;
//				}
//				break;
//				case 1:
//				{
//					//int cnt = count(vec.begin(), vec.end(), 2); //����0������
//					//if (cnt == vec.size()) //�����뿪�����뿪
//					vector<int>::iterator result_2 = find(vec.begin(), vec.end(), 2); //����2��ͣ��
//					if (result_2 != vec.end()) //����һ��ͣ����ͣ�ȣ���������ͣ����
//						status = 2;
//					////5����ͣ���ȣ�Ĭ�Ͻ��복�����׶Σ�����ʻ���⡣
//					vector<int>::iterator result_5 = find(vec.begin(), vec.end(), 3); //����3��������
//					if (result_5 != vec.end()) //�ҵ���һ���ҵ�����������
//						status = 3;
//				}
//				break;
//				case 2:
//				{
//					vector<int>::iterator result_3 = find(vec.begin(), vec.end(), 3); //����3��������
//					if (result_3 != vec.end()) //�ҵ���һ���ҵ�����������
//						status = 3;
//				}
//				break;
//				case 3:
//				{
//					int cnt = count(vec.begin(), vec.end(), 0); //����0������
//					if (cnt == vec.size()) //�����뿪�����뿪
//						status = 0;
//					//////ͣ��-����-ͣ��20230425
//					vector<int>::iterator result_5 = find(vec.begin(), vec.end(), 2); //����3��������
//					if (result_5 != vec.end()) //�ҵ���һ���ҵ�����������
//						status = 2;
//					//////ͣ��-����-ͣ��20230425
//				}
//			}
//			return status;
//		}
//
//		std::set<Participant_ptr> m_participants;
//		//std::map<int, std::vector<Participant_ptr>> m_codes;
//		std::map<int, int> m_code_state;
//		std::map<int, std::vector<int>> m_code_sta_tt;
//		//std::map<Participant_ptr, int> m_states;
//		//enum { max_recent_msgs = 100 };
//		//DeviceMessage_queue recent_msgs_; // disable.
//		DeviceController* m_controller;
//		//std::vector<int> sta_tt;
//		//int train_tt = 0;
//		std::mutex m_states_mutex;
//	};
//
//	class chat_session
//		: public Participant,
//		public std::enable_shared_from_this<chat_session>
//	{
//	public:
//		chat_session(boost::asio::ip::tcp::socket socket, chat_room& room)
//			: socket_(std::move(socket)),
//			room_(room)
//		{
//			std::cout <<  " session @ " << socket_.local_endpoint().address().to_string() << std::endl;//getTimestampMicroseconds() <<
//		}
//
//		void start()
//		{
//				room_.join(shared_from_this());
//				do_read_header();
//		}
//
//		void deliver(const DeviceMessage& msg)
//		{
//			bool write_in_progress = !write_msgs_.empty();
//			write_msgs_.push_back(msg);
//			if (!write_in_progress)
//			{
//				do_write();
//			}
//		}
//
//	private:
//		void do_read_header()
//		{
//			auto self(shared_from_this());
//			boost::asio::async_read(socket_,
//				boost::asio::buffer(read_msg_.data(), DeviceMessage::header_length),
//				[this, self](boost::system::error_code ec, std::size_t /*length*/)
//			{
//				if (!ec && read_msg_.decode_header())
//				{
//					std::cout  << " session do_read_header" << std::endl;//<< getTimestampMicroseconds()
//					do_read_body();
//				}
//				else
//				{
//					room_.leave(shared_from_this());
//				}
//			});
//		}
//
//		void do_read_body()
//		{
//			auto self(shared_from_this());
//			boost::asio::async_read(socket_,
//				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//				[this, self](boost::system::error_code ec, std::size_t /*length*/)
//			{
//				if (!ec)
//				{
//					room_.receive(shared_from_this(), read_msg_);//room_.deliver(read_msg_);
//					do_read_header();
//				}
//				else
//				{
//					room_.leave(shared_from_this());
//				}
//			});
//		}
//
//		void do_write()
//		{
//			auto self(shared_from_this());
//			boost::asio::async_write(socket_,
//				boost::asio::buffer(write_msgs_.front().data(),
//					write_msgs_.front().length()),
//				[this, self](boost::system::error_code ec, std::size_t /*length*/)
//			{
//				if (!ec)
//				{
//					write_msgs_.pop_front();
//					if (!write_msgs_.empty())
//					{
//						std::cout << " session do_write" << std::endl;
//						do_write();
//					}
//				}
//				else
//				{
//					std::cout <<  ec.message() << std::endl;
//					room_.leave(shared_from_this());
//				}
//			});
//		}
//
//		boost::asio::ip::tcp::socket socket_;
//		chat_room& room_;
//		DeviceMessage read_msg_;
//		DeviceMessage_queue write_msgs_;
//	};

	DeviceServer::DeviceServer(boost::asio::io_service& io_context,
		const boost::asio::ip::tcp::endpoint& endpoint, DeviceController* controller)
		: m_acceptor(io_context, endpoint)
		, m_room(nullptr)
		, m_controller(controller)
	{
//		m_room = new chat_room();
//		m_room->setController(controller);
		std::cout << "DeviceServer Start" << std::endl;
		std::cout <<  "DeviceServer @ " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;//getTimestampMicroseconds() <<
		do_accept();
	}

	void DeviceServer::stop()
	{
		m_acceptor.close();
	}

	void DeviceServer::do_accept()
	{
//        m_acceptor = boost::make_shared<boost::asio::ip::tcp::acceptor>(boost::ref(_ios), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 10086));//10086为端口号

m_acceptor.async_accept();
//        m_acceptor.async_accept()
		m_acceptor.async_accept(
			[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
		{
			if (!ec)
			{
				std::make_shared<chat_session>(std::move(socket), *m_room)->start();
			}

			do_accept();
		});
	}
