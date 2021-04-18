#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response) {
    Buffer buffer{ 0 };
    size_t json_data_length{ 0 };

    json json_obj;
    json_obj["message"] = response.message;

    for (auto& c : json_obj.dump()) {

    }

}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response) {
    return Buffer();
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response) {
    return Buffer();
}
