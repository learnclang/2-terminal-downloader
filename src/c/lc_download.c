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

int main() {
	CURL* curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl initialization failure");
		return 128;
	}

	curl_easy_cleanup(curl);
	return 0;
}
