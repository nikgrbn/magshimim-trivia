#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& login_manager, RequestHandlerFactory* handler_factory)
	: IRequestHandler(), _login_manager(login_manager), _handler_factory(handler_factory) {
}

LoginRequestHandler::~LoginRequestHandler()
{ }

bool LoginRequestHandler::IsRequestRelevant(RequestInfo info) {
	return (info.id == ProtocolCodes::Signup || info.id == ProtocolCodes::Login);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info) {
	RequestResult response = { Buffer(), nullptr };

	if (info.buffer[0] == (unsigned char)ProtocolCodes::Signup) {
		response = signup(info);
	} else if (info.buffer[0] == (unsigned char)ProtocolCodes::Login) {
		response = login(info);
	}

	return response;
}

RequestResult LoginRequestHandler::login(RequestInfo request) {
	RequestResult response;
	LoginResponse login_response;

	try {
		LoginRequest deserialized_request = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
		this->_login_manager.login(deserialized_request.username, deserialized_request.password);
		login_response.status = ResponseStatus::LoginSuccess;
		response.newHandler = this->_handler_factory->createLoginRequestHandler();
	} catch (std::exception& e) {
		login_response.status = ResponseStatus::LoginError;
		response.newHandler = this->_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(login_response);
	return response;
}

RequestResult LoginRequestHandler::signup(RequestInfo request) {
	SignupResponse signup_response;
	RequestResult response;

	try {
		SignupRequest deserialized_request = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
		this->_login_manager.signup(deserialized_request.username, deserialized_request.password, deserialized_request.email);
		
		signup_response.status = ResponseStatus::SignupSuccess;
		response.newHandler = this->_handler_factory->createLoginRequestHandler();
	} catch (std::exception& e) {
		signup_response.status = ResponseStatus::SignupError;
		response.newHandler = this->_handler_factory->createLoginRequestHandler();
	}

	response.buffer = JsonResponsePacketSerializer::serializeResponse(signup_response);
	return response;
}
