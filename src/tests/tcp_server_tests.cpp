/*
 * tcp_server_tests.cpp
 *
 *  Created on: Dec 26, 2016
 *      Author: jamil
 */




#define BOOST_TEST_MODULE first test
#include <boost/test/auto_unit_test.hpp>
#include <iostream>

#include "../utils/network/tcp/server.h"


using namespace utils::network;
using namespace utils::network::tcp;
using namespace std;

class telnetclient: public client_handler {
public:
	telnetclient(int32_t id, sockaddr_in addr):
		client_handler(id, addr) {
		cout<<"creating telnet client instance!!"<<endl;
	}

	virtual void on_connect() {
		cout<<"telnet connection request!! "<<endl;
		write("hello world!!");
	}

	virtual void on_disconnect() {
		cout<<"telnet disconnected!! "<<endl;
	}

	virtual void read(buffer_type buffer) {
		if ( nullptr == buffer ) return;
		auto c_str = reinterpret_cast<char *>(buffer.get());
		cout<<c_str<<endl;
	}

	virtual size_t write(std::string out) {
		auto len = out.length()+1;
		auto buffer = buffer_type(len);
		coctet_cpy(reinterpret_cast<uint8_t*>(buffer.get()),
				reinterpret_cast<const uint8_t*>(out.c_str()), len);
		return client_handler::write(std::move(buffer));
	};

	virtual ~telnetclient(){}
};

class telnet_connection:public server {
public:
	telnet_connection(const uint32_t port):
		server(port) {
	}

	std::shared_ptr<client_handler> create_client_handler(int client_id, sockaddr_in addr) {

		return std::make_shared<telnetclient>(client_id, addr);
	}

protected:
	void on_connect() override {
		BOOST_TEST_MESSAGE( "In on_connnect for telnet_connection " );
	}

	void on_disconnect() override {
		BOOST_TEST_MESSAGE( "In on_disconnnect for telnet_connection " );
	}
};


//bool check_exception(std::system_error const &e) { return e.what() == "example"; }

BOOST_AUTO_TEST_SUITE(tcp_server_tests)

BOOST_AUTO_TEST_CASE(tcp_server_telnet) {

	BOOST_TEST_CHECKPOINT("Starting");

	telnet_connection telnet_server(49000);
//	BOOST_CHECK_EXCEPTION(telnet_server.connect() , std::system_error, check_exception );
	telnet_server.connect();
	BOOST_CHECK_EXCEPTION( telnet_server.wait() , std::system_error, [](std::system_error const &e){
		std::cout<<e.what()<<e.code()<<e.code().message()<<std::endl;
		return e.code().value() > 0;
	});
//	BOOST_CHECK_MESSAGE( result , "Couldn't connect to outbind connection!!" );



	getchar();

	BOOST_CHECK( true );

	BOOST_TEST_CHECKPOINT("Ending");
}

BOOST_AUTO_TEST_SUITE_END()




