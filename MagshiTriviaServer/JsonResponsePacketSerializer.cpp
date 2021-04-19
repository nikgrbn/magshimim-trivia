#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response) {

}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response) {
    return Buffer();
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response) {
    return Buffer();
}
