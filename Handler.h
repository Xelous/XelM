//
// Created by xelous on 26/11/17.
//

#ifndef ROOMS_HANDLER_H
#define ROOMS_HANDLER_H


#include <map>
#include "Room.h"

namespace XelM
{
	using RoomMap = std::map<RoomId, RoomPtr>;

	class Handler
	{
		private:

			RoomMap m_Map;
			RoomPtr m_CurrentRoomPtr;
			RoomId	m_CurrentRoomId;
			bool m_Active;

		public:

			Handler();

			RoomId AddRoom(
					const std::string& p_Title,
					const std::string& p_BodyText);

			const bool EnterRoom(const RoomId& p_Room);

			void HandleUserInput();

			const bool Active() const;

			static Handler DefaultMap();

			static void SimpleSleep(const unsigned int& p_Milliseconds);

	};

}

#endif //ROOMS_HANDLER_H
