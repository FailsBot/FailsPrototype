/// @file bot_network.h Contains networking functions declarations which 
///       used for communicating with Telegram Bot API
#ifndef TGBOTLIB_BOT_NETWORK_H_
#define TGBOTLIB_BOT_NETWORK_H_
// #include <curl/curl.h>
// struct CURL;
struct writefn_data;
typedef void CURL;

struct bot_mime_field {
	const char *name;
	const char *filename;
	const writefn_data *data;
};

// Init-deinit API.

CURL *bot_network_init();
void bot_network_free(CURL *c);

// low-level HTTP API.


int easy_get_http_code(CURL *c);
void easy_print_http_code(CURL *c, writefn_data *d = 0);


int easy_perform_commandstr(CURL *c, const char *url, writefn_data *data,
	bool print_result = true);

int easy_perform_commandstr(CURL *c, const char *url);

int easy_perform_mime_query(CURL *curl, const char *url,
	const bot_mime_field *fields, size_t count, writefn_data &result);

#endif
