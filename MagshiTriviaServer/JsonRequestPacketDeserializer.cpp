#include "JsonRequestPacketDeserializer.h"

json JsonRequestPacketDeserializer::retrieveJson(const Buffer& request)
{
    // Desirialize request code
    unsigned int request_code = (unsigned int)request[0];

    // Desirialize data length
    unsigned int data_length =
        (request[CODE_SIZE]) | (request[CODE_SIZE + 1] << 8) | (request[CODE_SIZE + 2] << 16) | request[CODE_SIZE + 3] << 24;

    // Parse json
    json j = json::parse(request.begin() + HEADER_SIZE, request.begin() + HEADER_SIZE + data_length);
    return j;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer request)
{
    // Get json from request
    json j = retrieveJson(request);

    // Create struct with json
    struct LoginRequest log_req;
    log_req.username = j["username"];
    log_req.password = j["password"];

    return log_req;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer request)
{
    // Get json from request
    json j = retrieveJson(request);

    // Create struct with json
    struct SignupRequest sign_req;
    sign_req.username = j["username"];
    sign_req.password = j["password"];
    sign_req.email = j["mail"];

    return sign_req;
}
