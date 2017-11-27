//
// Created by xelous on 26/11/17.
//

#include "Room.h"

#include <iostream>
#include <sstream>

#include "Helpers.h"

namespace XelM
{

	RoomId Room::s_MasterRoomId(0);

	const RoomId Room::NextRoomId()
	{
		++s_MasterRoomId;
		return s_MasterRoomId;
	}

	Room::Room(const std::string& p_Title,
			   const std::string& p_BodyText)
			:
			Id(NextRoomId()),
			Title(p_Title),
			BodyText(p_BodyText),
			m_Exits()
	{
	}

	RoomPtr Room::Create(
			const std::string& p_Title,
			const std::string p_BodyText)
	{
		return RoomPtr(new Room(p_Title, p_BodyText));
	}

	const bool Room::ExitPossible(const Direction& p_Direction)
	{
		auto l_exists(m_Exits.find(p_Direction));
		return l_exists != m_Exits.end();
	}

	void Room::Enter()
	{
		std::ostringstream l_oss;
		l_oss << "You Enter the '" << Title << "'...\r\n";
		Helpers::FlowingText(l_oss.str());
		Helpers::FlowingText(BodyText);
		std::cout << std::endl;
	}

	void Room::PrintDirections() const
	{
		std::ostringstream l_oss;
		if ( !m_Exits.empty() )
		{
			int l_count(0);
			int l_Max(m_Exits.size()-1);
			l_oss << "[";
			for (auto i(m_Exits.begin());
					i != m_Exits.end();
					++i, ++l_count)
			{
				l_oss << i->first;
				if ( l_count < l_Max )
				{
					l_oss << ", ";
				}
			}
			l_oss << "] ";
		}
		std::cout << l_oss.str();
	}

	void Room::AddDirection(
		const char& p_Direction,
		const RoomId& p_RoomId)
	{
		if ( !ExitPossible(p_Direction) )
		{
			m_Exits.emplace(
				std::make_pair(
					p_Direction,
					p_RoomId));
		}
		else
		{
			std::cout << "Error adding duplicate direction" << std::endl;
		}
	}

	const RoomId Room::RoomInDirection(const Direction& p_Direction)
	{
		RoomId l_result(0);
		auto l_Found(m_Exits.find(p_Direction));
		if ( l_Found != m_Exits.end() )
		{
			l_result = l_Found->second;
		}
		return l_result;
	}

}