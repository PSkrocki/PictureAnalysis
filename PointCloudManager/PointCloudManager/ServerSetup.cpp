#include "ServerSetup.h"
#include <iostream>
#include <string>
#include <cpprest\http_listener.h>
#include <cpprest\json.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

RestManager* restManagerRef;

void handle_files_get(http_request request){
	//MOCKUP
	json::value mock;
	mock[L"1"] = json::value::string(L"file1.ply");
	mock[L"2"] = json::value::string(L"file2.ply");
	mock[L"3"] = json::value::string(L"file3.ply");
	mock[L"4"] = json::value::string(L"file4.ply");
	mock[L"5"] = json::value::string(L"file5.ply");
	request.reply(status_codes::OK, json::value(mock));
}

pplx::task<void> initFilesListener(){
	return pplx::create_task([]{
		restManagerRef->filesListener = http_listener(L"http://localhost:8080/files");
		restManagerRef->filesListener.support(methods::GET, handle_files_get);
		try{
			restManagerRef->filesListener
				.open()
				.wait();
			while (true);
		}
		catch (exception const & e){
			cout << e.what() << endl;
		}
	});
}

void handle_chosen_file_get(http_request request){
	//MOCKUP
	json::value mock;
	mock[L"chosen"] = json::value::string(L"file1.ply");
	mock[L"compression"] = json::value::string(L"75");
	mock[L"compressedFile"] = json::value::string(L"compressed.ply");
	request.reply(status_codes::OK, json::value(mock));
}

void handle_chosen_file_post(http_request request){

}

pplx::task<void> initChosenFileListener(){
	return pplx::create_task([]{
		restManagerRef->chosenFileListener = http_listener(L"http://localhost:8080/chosenfile");
		restManagerRef->chosenFileListener.support(methods::GET, handle_chosen_file_get);
		restManagerRef->chosenFileListener.support(methods::POST, handle_chosen_file_post);
		try{
			restManagerRef->chosenFileListener
				.open()
				.wait();
			while (true);
		}
		catch (exception const & e){
			cout << e.what() << endl;
		}
	});
}

void handle_selection_post(http_request request){
	
}

pplx::task<void> initSelectionListener(){
	return pplx::create_task([]{
		restManagerRef->selectionListener = http_listener(L"http://localhost:8080/selection");
		restManagerRef->selectionListener.support(methods::POST, handle_selection_post);
		try{
			restManagerRef->selectionListener
				.open()
				.wait();
			while (true);
		}
		catch (exception const & e){
			cout << e.what() << endl;
		}
	});
}

void handle_values_get(http_request request){
	//MOCKUP
	json::value mock;
	mock[L"volume"] = json::value::string(L"150");
	mock[L"error"] = json::value::string(L"0.05");
	request.reply(status_codes::OK, json::value(mock));
}

pplx::task<void> initValuesListener(){
	return pplx::create_task([]{
		restManagerRef->valuesListener = http_listener(L"http://localhost:8080/values");
		restManagerRef->valuesListener.support(methods::GET, handle_values_get);
		try{
			restManagerRef->valuesListener
				.open()
				.wait();
			while (true);
		}
		catch (exception const & e){
			cout << e.what() << endl;
		}
	});
}

void init(RestManager* restManager){
	restManagerRef = restManager;
	initFilesListener();
	initChosenFileListener();
	initSelectionListener();
	initValuesListener();
}