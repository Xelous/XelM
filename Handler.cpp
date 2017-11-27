//
// Created by xelous on 26/11/17.
//

#include "Handler.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

namespace XelM
{
	Handler::Handler()
		:
		m_Map(),
		m_CurrentRoomPtr(nullptr),
		m_CurrentRoomId(0),
		m_Active(false)
	{
	}

	RoomId Handler::AddRoom(
			const std::string& p_Title,
			const std::string& p_BodyText)
	{
		RoomPtr l_CreatedRoom(
				Room::Create(
						p_Title,
						p_BodyText));
		m_Map.emplace(
				std::make_pair(
						l_CreatedRoom->Id,
						l_CreatedRoom));
	}

	const bool Handler::EnterRoom(const RoomId& p_Room)
	{
		bool l_result(false);
		auto l_Found(m_Map.find(p_Room));
		if ( l_Found != m_Map.end() )
		{
			m_Active = true;

			m_CurrentRoomId = p_Room;
			m_CurrentRoomPtr = l_Found->second;

			m_CurrentRoomPtr->Enter();

			l_result = true;
		}
		return l_result;
	}

	void Handler::HandleUserInput()
	{
		std::cout << "Which way would you like to move? ";
		if ( m_CurrentRoomPtr )
		{
			m_CurrentRoomPtr->PrintDirections();
		}
		char l_direction;
		std::cin >> l_direction;
	}

	const bool Handler::Active() const
	{
		return m_Active;
	}

	Handler Handler::DefaultMap()
	{
		Handler l_result;

		l_result.AddRoom("Main Hall", "A long dark hall stretched out before you");
		l_result.AddRoom("Antechamber", "The antechamber is off the main hall, it smells damp and clearly hasn't seen any activity for many years...");

		return l_result;
	}

	void Handler::SimpleSleep(const unsigned int& p_Milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(p_Milliseconds));
	}

}