#pragma once

// Standard library
#include <vector>

// Project headers
#include "ProtocolStructures.h"
#include "StatusCodes.h"
#include "json.hpp"

// Definitions
using Buffer = std::vector<unsigned char>;
using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
    static Buffer generateResponse(const std::string& json_message, ProtocolCodes message_code);

    // Serialized responses of structs
    static Buffer serializeResponse(ErrorResponse response);
    static Buffer serializeResponse(LoginResponse response);
    static Buffer serializeResponse(SignupResponse response);
};