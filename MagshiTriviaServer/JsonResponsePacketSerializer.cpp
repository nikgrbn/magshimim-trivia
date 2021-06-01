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
    Buffer temp_buffer; // buffer to return
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

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse response) {
    json j{};
    j["status"] = response.status;

    return generateResponse(j.dump(), ProtocolCodes::LogoutRequest);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response) {
    json j{};
    std::string rooms_string{};

    for (auto r : response.rooms) {
        if (!rooms_string.empty())
            rooms_string += ',';
        rooms_string += r.name;
    }

    j["Rooms"] = rooms_string;

    return generateResponse(j.dump(), ProtocolCodes::LogoutRequest);
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response) {
    json j{};
    std::string users_string{};

    for (auto r : response.players) {
        if (!users_string.empty())
            users_string += ',';
        users_string += r;
    }

    j["Rooms"] = users_string;

    return generateResponse(j.dump(), ProtocolCodes::LogoutRequest);
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response) {
    json j{};
    j["status"] = response.status;

    return generateResponse(j.dump(), ProtocolCodes::JoinRoomRequest);
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response) {
    json j{};
    j["status"] = response.status;

    return generateResponse(j.dump(), ProtocolCodes::CreateRoomRequest);
}
