#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    
using namespace web;                        
using namespace web::http;                 
using namespace web::http::client;          
using namespace concurrency::streams;       

class RestManager
{
public:
	RestManager();
	~RestManager();
	void sendTheRequestHTTP_client();
};

