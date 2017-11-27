//
// Created by xelous on 26/11/17.
//

#ifndef ROOMS_ROOM_H
#define ROOMS_ROOM_H

#include <string>
#include <memory>
#include <map>

namespace XelM
{
	using Direction = char;
	using RoomId = unsigned long;
	using Exits = std::map<Direction, RoomId>;

	class Room;
	using RoomPtr = std::shared_ptr<Room>;
    class Room
    {
        public:

			const RoomId Id;
			const std::string Title;
			const std::string BodyText;

		protected:

			static RoomId s_MasterRoomId;
			static const RoomId NextRoomId();

			Room() = delete;
			Room(const std::string& p_Title,
				const std::string& p_BodyText);

			Exits m_Exits;

		public:

			static RoomPtr Create(
					const std::string& p_Title,
					const std::string p_BodyText);

			const bool ExitPossible(const Direction& p_Direction);

			void Enter();

			void PrintDirections() const;

			void AddDirection(
				const char& p_Direction,
				const RoomId& p_RoomId);

			const RoomId RoomInDirection(const Direction& p_RoomId);

    };

}
#endif //ROOMS_ROOM_H
