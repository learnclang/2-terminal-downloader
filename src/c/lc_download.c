/*Download file from a terminal

Contents:
    - Communicating via HTTP
    - Opening a file
    - Writing to a file

Usage:
    $ lc_download.py http://google.com

*/

#include <stdio.h>
#include "curl/curl.h"

int main(int argc, const char* args[]) {
	if (argc != 2) {
		fprintf(stderr, "Please provide exactly one URL to print to standard output\n");
		return 1;
	}

	CURL* curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl initialization failure\n");
		return 128;
	}

	CURLcode res = CURLE_OK;
	if ((res = curl_easy_setopt(curl, CURLOPT_URL, args[1])) != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 3;
	}
	if ((res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L) != CURLE_OK)) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 3;
	}

	if ((res = curl_easy_perform(curl)) != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 4;
	}

	curl_easy_cleanup(curl);
	return 0;
}
