#include <time.h>
#include <stdio.h>
#include <libgen.h>
#include <curl/curl.h>

#define DWLD_URL "http://speedtest.ftp.otenet.gr/files/test100k.db"
//#define DWLD_URL "http://speedtest.ftp.otenet.gr/files/test1Mb.db"
//#define DWLD_URL "http://speedtest.ftp.otenet.gr/files/test100Mb.db"

#define UNUSED(var) ((void)var)

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

int xferinfo(void *ptr, double TotalToDownload, double NowDownloaded,
		double TotalToUpload, double NowUploaded)
{
	int tmp;
	int *prv_per = ptr;
	UNUSED(NowUploaded);
	UNUSED(TotalToUpload);

	if (TotalToDownload <= 0.0)
		return 0;

	tmp = (int)((NowDownloaded / TotalToDownload) * 100);

	if ((tmp != *prv_per) && !(tmp % 5)) {
		printf("* %d *\n", tmp);
		*prv_per = tmp;
	}

	return 0;
}

#if LIBCURL_VERSION_NUM < 0x072000
/* for libcurl older than 7.32.0 (CURLOPT_PROGRESSFUNCTION) */
static int older_progress(void *p,
						  double dltotal, double dlnow,
						  double ultotal, double ulnow)
{
	return xferinfo(p,
			(curl_off_t)dltotal,
			(curl_off_t)dlnow,
			(curl_off_t)ultotal,
			(curl_off_t)ulnow);
}
#endif /* LIBCURL_VERSION_NUM < 0x072000 */

int main(void)
{
	CURL *curl;
	time_t tm;
	FILE *file;
	int prv_per = 0;
	CURLcode res = CURLE_OK;

	curl = curl_easy_init();
	file = fopen(basename(DWLD_URL), "wb");
	if (!curl || !file) {
		file ? fclose(file) : curl_easy_cleanup(curl);
		perror("fopen || curl_easy_init\n");
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, DWLD_URL);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

#if LIBCURL_VERSION_NUM < 0x072000
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, xferinfo);
	/* pass the struct pointer into the progress function */
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &prv_per);
#else
	/*
	 * xferinfo was introduced in 7.32.0, no earlier libcurl versions will
	 * compile as they won't have the symbols around.
	 * If built with a newer libcurl, but running with an older libcurl:
	 * curl_easy_setopt() will fail in run-time trying to set the new
	 * callback, making the older callback get used.
	 * New libcurls will prefer the new callback and instead use that one even
	 * if both callbacks are set
	 */

	curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo);
	curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &prv_per);
#endif /* LIBCURL_VERSION_NUM < 0x072000 */

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

	curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, (curl_off_t)1024);

	tm = time(NULL);

	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
		fprintf(stderr, "%s\n", curl_easy_strerror(res));

	printf("Time taken: %ld second(s)\n", time(NULL) - tm);

	/* always cleanup */
	curl_easy_cleanup(curl);

	fflush(file);
	fclose(file);
	remove(basename(DWLD_URL));

	return (int)res;
}
