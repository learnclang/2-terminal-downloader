/*Download file from a terminal

Contents:
    - Communicating via HTTP
    - Opening a file
    - Writing to a file

Usage:
    $ lc_download http://google.com

*/

#include <stdio.h>
#include <libgen.h> // For basename()
#include <curl/curl.h>


int main(int argc, char* args[]) {
    
    // Assume a single argument
    if (argc != 2) {
        printf("Please enter a URL");
        return 1;
    }

    char *url = args[1];

    // Declare a pointer to a CURL *easy* handle
    // http://curl.haxx.se/libcurl/c/curl_easy_init.html
    CURL *curl;
    
    // If there is any error, this is the variable in which it will be stored.
    // http://curl.haxx.se/libcurl/c/curl_easy_strerror.html
    CURLcode res;

    // This (file-handle) is what we'll use to write to disk
    FILE *fp;

    // Apparently, this function must be the first function call.
    // http://curl.haxx.se/libcurl/c/curl_easy_init.html
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Now that we've passed the full url, let's
        // get the last part of the URL, which will
        // become our file-name.
        char *output = basename(args[1]);
        fp = fopen(output, "wb");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
          fprintf(stderr, "Could not download file: %s\n",
                  curl_easy_strerror(res));

        // Always cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}