//
// Created by xelous on 26/11/17.
//

#include "Handler.h"

#include <iostream>
#include <thread>
#include <sstream>

#include "Helpers.h"

namespace XelM
{
	const bool Handler::SelectRoom(const RoomId& p_RoomId)
	{
		bool l_result(false);

		auto l_Found(m_Map.find(p_RoomId));
		if ( l_Found != m_Map.end() )
		{
			m_CurrentRoomPtr = l_Found->second;
			l_result = true;
		}
		return l_result;
	}

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
			const std::string& p_BodyText,
			const char& p_Direction,
			const RoomId& p_Off)
	{		
		RoomPtr l_CreatedRoom(
			Room::Create(
				p_Title,
				p_BodyText));
		
		SelectRoom(p_Off);

		if ( m_CurrentRoomPtr )
		{
			m_CurrentRoomPtr->AddDirection(
				p_Direction,
				l_CreatedRoom->Id);

			l_CreatedRoom->AddDirection(
				Helpers::OppositeDirection(p_Direction),
				m_CurrentRoomPtr->Id);
		}
		else
		{
			m_CurrentRoomPtr = l_CreatedRoom;
		}

		m_Map.emplace(
			std::make_pair(
				l_CreatedRoom->Id,
				l_CreatedRoom));

		return l_CreatedRoom->Id;
	}

	const bool Handler::EnterRoom(const RoomId& p_Room)
	{
		bool l_result(SelectRoom(p_Room));
		if ( l_result )
		{
			m_Active = true;
			m_CurrentRoomPtr->Enter();
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

		char l_direction(' ');
		std::cin >> l_direction;
		l_direction = ::tolower(l_direction);

		if ( m_CurrentRoomPtr->ExitPossible(l_direction) )
		{
			Helpers::FlowingText("Moving...\r\n");

			EnterRoom(
				m_CurrentRoomPtr->RoomInDirection(
					l_direction));
		}
	}

	const bool Handler::Active() const
	{
		return m_Active;
	}

	Handler Handler::DefaultMap()
	{
		Handler l_result;

		RoomId l_MainHall(
			l_result.AddRoom(
				"Main Hall",
				"A long dark hall stretched out before you"));

		RoomId l_AnteChamber(
			l_result.AddRoom(
				"Antechamber",
				"The antechamber is off the main hall, it smells damp and clearly hasn't seen any activity for many years...",
				'w',
				l_MainHall));

		RoomId l_Culvert(
			l_result.AddRoom(
				"Culvert",
				"Through a broken wall panel the bed rock beyond looms, damp and tight fitting",
				'n',
				l_AnteChamber));

		RoomId l_Niche(
			l_result.AddRoom(
				"Niche",
				"The niche is set back from the Antechamber, once a quite place of contemplation, not there is naught but a skeleton laying forlorn amongst the dust...",
				's',
				l_AnteChamber));

		return l_result;
	}	

}