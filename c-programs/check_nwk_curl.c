#include <stdio.h>
#include <libgen.h>
#include <curl/curl.h>

size_t wrfn(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return size * nmemb;
}

int main(void)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "curl_easy_init failed\n");
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wrfn);
	curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");

	res = curl_easy_perform(curl);
	if (res == CURLE_OK) {
	        printf("Network is alive\n");
                goto finish;
        }

        switch (res) {
                case CURLE_COULDNT_CONNECT:
                case CURLE_COULDNT_RESOLVE_HOST:
                case CURLE_COULDNT_RESOLVE_PROXY:
                        printf("Network is dead\n");
                        break;

                default:
                        fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(res));
                        break;
        }

finish:
        /* always cleanup */
        curl_easy_cleanup(curl);

        return (int)res;
}
