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

// { UsersStatistics: {"user1": {...}, "user2" : {...}}, "HighScoreStatistics" : {"user1" :{....}} }

Buffer JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse response) {
    json final_j{};
    json users_j{};
    json highscore_j{};

    for (auto user : response.user_statistics) {
        json current_user;
        
        current_user["average_answer_time"] = user.average_answer_time;
        current_user["games_played"] = user.games_played;
        current_user["correct_answers"] = user.correct_answers;
        current_user["total_answers"] = user.total_answers;
        current_user["score"] = user.score;

        users_j[user.username] = current_user;
    }

    for (auto user : response.high_score) {
        json current_user;

        current_user["average_answer_time"] = user.average_answer_time;
        current_user["games_played"] = user.games_played;
        current_user["correct_answers"] = user.correct_answers;
        current_user["total_answers"] = user.total_answers;
        current_user["score"] = user.score;

        highscore_j[user.username] = current_user;
    }
    
    final_j["UsersStatistics"] = users_j;
    final_j["HighScore"] = highscore_j;

    return generateResponse(final_j.dump(), ProtocolCodes::GetStatisticsRequest);
}
