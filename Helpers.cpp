#include "Helpers.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>

namespace XelM
{
	
	void Helpers::Sleep(const unsigned int& p_Milliseconds)
	{
		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				p_Milliseconds));
	}

	void Helpers::FlowingText(
		const std::string& p_Text,
		const unsigned int& p_IntraCharacterDelay)
	{
		if ( !p_Text.empty() )
		{
			for (auto i(p_Text.cbegin());
				i != p_Text.cend();
				++i)
			{
				std::cout << (*i) << std::flush;		
				if ( (*i) == '\n' )
				{
					Sleep(p_IntraCharacterDelay * 4);
				}
				else
				{
					Sleep(p_IntraCharacterDelay);
				}
			}
		}
	}

	const char Helpers::OppositeDirection(const char& p_Direction)
	{
		char l_result(' ');
		switch (p_Direction)
		{
			case 'n':
			case 'N':
				l_result = 's';
				break;

			case 's':
			case 'S':
				l_result = 'n';
				break;

			case 'w':
			case 'W':
				l_result = 'e';
				break;

			case 'e':
			case 'E':
				l_result = 'w';
				break;
		}
		return l_result;
	}		

}