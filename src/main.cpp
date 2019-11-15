#include "tgbotlib/bot_network.h"

int main()
{
	auto bot_handle = bot_network_init();
	bot_network_free(bot_handle);
	return 0;
}
