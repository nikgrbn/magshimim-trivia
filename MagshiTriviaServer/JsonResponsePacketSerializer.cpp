#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::generateResponse(const std::string& json_message, ProtocolCodes message_code) {
    unsigned int message_length{ json_message.length() };
    Buffer temp_buffer;
    temp_buffer.reserve(HEADER_SIZE + message_length);

    temp_buffer.push_back((unsigned int)message_code); // inserting the code
    std::memcpy(temp_buffer.data(), &message_length, sizeof(unsigned int));

    temp_buffer.insert(temp_buffer.begin() + HEADER_SIZE, json_message.begin(), json_message.end()); // inserting the message
    return temp_buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response) {
    json j{};
    j["message"] = response.message;

    return generateResponse(j.dump(), ProtocolCodes::Error);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response) {
    return Buffer();
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response) {
    return Buffer();
}