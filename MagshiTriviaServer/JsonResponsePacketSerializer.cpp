#include "JsonResponsePacketSerializer.h"

/**
* This method grenerate repsponse according to the protocol
* @param json_message - The json to be sent
* @param message_code - The code of the message according to the protocol
* 
* @return Buffer - the buffer that has been made (unsigned ints vector)
*/
Buffer JsonResponsePacketSerializer::generateResponse(const std::string& json_message, ProtocolCodes message_code) {
    unsigned int message_length{ json_message.length() };
    Buffer temp_buffer;
    temp_buffer.reserve(HEADER_SIZE + message_length);

    for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
        temp_buffer.insert(temp_buffer.begin(), message_length & 0xFF); // pushing back the last byte in the 
        message_length = message_length >> 8;
    }

    temp_buffer.insert(temp_buffer.begin(), (unsigned int)message_code); // inserting the message code
    temp_buffer.insert((temp_buffer.begin() + HEADER_SIZE), json_message.begin(), json_message.end()); // inserting the message
    
    return temp_buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response) {
    json j{};
    j["message"] = response.message;

    return generateResponse(j.dump(), ProtocolCodes::Error);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response) {
    json j{};
    j["status"] = response.status;

    return generateResponse(j.dump(), ProtocolCodes::Login);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response) {
    json j{};
    j["status"] = response.status;

    return generateResponse(j.dump(), ProtocolCodes::Signup);
}