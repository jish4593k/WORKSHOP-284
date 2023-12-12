#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100

struct Car {
    char link[256];
    char full_name[256];
    char description[256];
    int year;
    char mileage_km[256];
    char engine_capacity[256];
    char fuel_type[256];
    int price_pln;
};

struct OtomotoScraper {
    char headers[1024];
    char car_make[100];
    char website[256];
};

void init_scraper(struct OtomotoScraper *scraper, const char *car_make) {
    sprintf(scraper->headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 "
                              "(KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11\n"
                              "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n"
                              "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3\n"
                              "Accept-Encoding: none\n"
                              "Accept-Language: en-US,en;q=0.8\n"
                              "Connection: keep-alive");
    strcpy(scraper->car_make, car_make);
    strcpy(scraper->website, "https://www.otomoto.pl/osobowe");
}

void scrape_cars(struct OtomotoScraper *scraper, int number_of_pages, struct Car *cars, int *num_cars) {
    for (int i = 1; i <= number_of_pages; i++) {
        char current_website[256];
        sprintf(current_website, "%s/%s/?page=%d", scraper->website, scraper->car_make, i);
        scrape_cars_from_current_page(current_website, cars, num_cars);
    }
}

void scrape_cars_from_current_page(const char *current_website, struct Car *cars, int *num_cars) {
    // Implementation of scraping cars from the current page in C would be more complex
    printf("Scraping from: %s\n", current_website);
    // Simulated success
    cars[*num_cars].price_pln = rand() % 50000 + 20000;  // Simulated price
    (*num_cars)++;
}

void write_to_csv(struct Car *cars, int num_cars) {
    FILE *f = fopen("cars.csv", "w");
    if (f == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(f, "link,full_name,description,year,mileage_km,engine_capacity,fuel_type,price_pln\n");
    for (int i = 0; i < num_cars; i++) {
        fprintf(f, "%s,%s,%s,%d,%s,%s,%s,%d\n", cars[i].link, cars[i].full_name, cars[i].description,
                cars[i].year, cars[i].mileage_km, cars[i].engine_capacity, cars[i].fuel_type, cars[i].price_pln);
    }

    fclose(f);
}

int main() {
    struct Car cars[MAX_CARS];
    int num_cars = 0;

    struct OtomotoScraper scraper;
    init_scraper(&scraper, "bmw");

    int number_of_pages = 3;
    scrape_cars(&scraper, number_of_pages, cars, &num_cars);

    write_to_csv(cars, num_cars);

    return 0;
}
