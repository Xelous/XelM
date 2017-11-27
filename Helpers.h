#ifndef HELPERS_HEADER
#define HELPERS_HEADER

#include <string>

namespace XelM
{
	
	class Helpers
	{
		public:

			static void Sleep(const unsigned int& p_Milliseconds);

			static void FlowingText(
				const std::string& p_Text,
				const unsigned int& p_InterCharacterDelay = 25);

			static const char OppositeDirection(const char& p_Direction);			

	};

}


#endif