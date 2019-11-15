#include "writefn_data.h"
#include "utils/termcolor.h"
#include <curl/curl.h>
#include <assert.h>
#include <stdio.h>

size_t json_cb(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	assert(userdata != 0);
	size_t act = size * nmemb;
	writefn_data *data = (writefn_data *)userdata;
	
	if (!writefn_data_append(*data, ptr, act + 1)) {
		fprintf(stderr, RED("json_cb(): writefn_data_append(): out of mem(can't realloc)\n"));
		return 0;
	}
	data->ptr[data->sz - 1]='\0';
	data->sz--;
	return act;
}

CURL *bot_network_init()
{
	CURL *result = curl_easy_init();
	if (!result) {
		return NULL;
	}
	curl_easy_setopt(result, CURLOPT_WRITEFUNCTION, json_cb);
	return result;
}

void bot_network_free(CURL *c)
{
	curl_easy_cleanup(c);
}


// HTTP code

int easy_get_http_code(CURL *c)
{
	int st = 0;
	int st2 = curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &st);
	return st2 == CURLE_OK ? st : - st2;
}

/// @brief Prints HTTP code and response.
void easy_print_http_code(CURL *c, writefn_data *d = 0)
{
	int status = 0;
	curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &status);
	printf("HTTP status: %s(%d)\n",
		(status < 400) ? GREEN("OK") : RED("FAILED"), status);
	if (!d) {
		return;
	}
	printf("%s\n", d->ptr);
}

// low-level network API.

int easy_perform_commandstr(CURL *c, const char *url, writefn_data *data, 
	bool print_result = true)
{
	assert(data);
	printf("Perform command %s\n", url);
	curl_easy_setopt(c, CURLOPT_URL, url);
	curl_easy_setopt(c, CURLOPT_WRITEDATA, data);
	CURLcode result = curl_easy_perform(c);
	if (result != CURLE_OK) {
		long code = 0;
		curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &code);
		fprintf(stderr, RED("Failed to answer the user: ")  
			 "HTTP status " RED("%ld") ", curl err code: %d"
			 ", description: %s\n", code, result, curl_easy_strerror(result));
		// return result;
		return -result;
	}

	if (print_result) {
		easy_print_http_code(c);
	}
	return result;
}

int easy_perform_commandstr(CURL *c, const char *url)
{
	writefn_data d;
	writefn_data_init(d);
	int result = easy_perform_commandstr(c, url, &d);
	writefn_data_free(d);
	return result;
}

