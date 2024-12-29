#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
void fetch_weather(const char *city) {
    CURL *curl;
    CURLcode res;
    char url[256];
    char response[4096] = ""; // Buffer to store the response

    // Construct the API URL with the city name
    sprintf(url, "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=46c7f1b59f8583152eaa79251410c814", city);

    curl = curl_easy_init();  // Initialize CURL session
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);  // Set the API URL
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Follow redirects
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // Set callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);  // Set the buffer to store the response

        res = curl_easy_perform(curl);  // Perform the request
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("API Response: %s\n", response);  // Print the API response (JSON format)
        }

        curl_easy_cleanup(curl);  // Cleanup CURL session
    } else {
        fprintf(stderr, "Failed to initialize CURL.\n");
    }
}


int main() {
    char city[50];
    printf("Enter city name: ");
    scanf("%49s", city);

    if (strlen(city) > 0) {
        fetch_weather(city);  // Fetch weather data for the given city
    } else {
        printf("City name cannot be empty.\n");
    }

    return 0;
}
