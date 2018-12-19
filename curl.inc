
#ifdef USE_CURL
    #include <curl/curl.h>

    typedef int (*JADE_PROGRESS_CALLBACK)(void*,double,double,double,double);
    typedef int (*JADE_WRITE_CALLBACK)(void*,long,long,void*);

    void downloadFile(CSTRING url, CSTRING downloadFileName, void *progress_callback);
    void downloadPage(CSTRING url, CSTRING buffer, void *write_callback);




    int jade_curl_progress_callback(void* clientp, double dltotal, double dlnow, double ultotal, double ulnow ) {
        printf("Downloaded %d of %d bytes\r",(int)dlnow,(int)dltotal);
        return 0; 
    }

    int jade_curl_write_data_callback (void* content, long size, long nmemb, void* stream) {
        ((std::string*)stream)->append((char*)content, size * nmemb);
        return size * nmemb;
    }

    std::string downloadPage(CSTRING url,JADE_WRITE_CALLBACK write_callback = jade_curl_write_data_callback) {
        void* handle;
        int success;
        std::string buffer$;

        handle = curl_easy_init();    
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION,1);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer$);

    
            success = curl_easy_perform(handle);

        curl_easy_cleanup(handle);     

        return buffer$; 
    }
    void downloadFile(CSTRING url, CSTRING downloadFileName, JADE_PROGRESS_CALLBACK progress_callback=jade_curl_progress_callback)  {
        void* handle;
        int success;
        FILE *fp;

        handle = curl_easy_init();    
        if ((fp = fopen(downloadFileName.c_str(), "wb+"))) {
            curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION,1);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(handle, CURLOPT_NOPROGRESS,0);
            curl_easy_setopt(handle, CURLOPT_PROGRESSDATA,downloadFileName.c_str());
            curl_easy_setopt(handle, CURLOPT_PROGRESSFUNCTION,progress_callback);
        
            success = curl_easy_perform(handle);
            fclose(fp);
        }
        curl_easy_cleanup(handle);
        printf("\n\nDownload of '%s' Complete.\n\n", downloadFileName.c_str());
    }

#endif
