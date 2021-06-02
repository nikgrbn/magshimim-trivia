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

class JsonRequestPacketDeserializer
{
public:
	static json retrieveJson(const Buffer& request);

	// Desirialize requests to structs
	static LoginRequest deserializeLoginRequest(Buffer request);
	static SignupRequest deserializeSignupRequest(Buffer request);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer request);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer request);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer request);
};