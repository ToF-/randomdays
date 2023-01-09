#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

const int MAX_DISPLAY = 30;

struct tm ymdtodate(int ymd) {
    int y = ymd / 10000;
    int rm = ymd % 10000;
    int m = rm / 100;
    int d = rm % 100;
    struct tm result = (struct tm){ 
        .tm_year = y - 1900,
        .tm_mon  = m - 1,
        .tm_mday = d };
    return result; 
}

void print_date_ymd(struct tm date) {
    char display[MAX_DISPLAY];
    strftime(display, MAX_DISPLAY, "%Y%m%d", &date);
    printf("%s", display);
}

int datetoymd(struct tm date) {
    char display[MAX_DISPLAY];
    strftime(display, MAX_DISPLAY, "%Y%m%d", &date);
    return atoi(display);
}

int main(int argc, char *argv[]) {
    time_t time_stamp_now = time(NULL);
    struct tm *date_now = localtime(&time_stamp_now);
    struct tm date_start = *date_now;
    struct tm date_end = *date_now;
    date_start.tm_year-= 2;
    date_end.tm_year+= 2;
    int start_ymd = datetoymd(date_start);
    int end_ymd   = datetoymd(date_end);
    time_t start  = mktime(&date_start);
    time_t end    = mktime(&date_end);
    char c;
    while((c = getopt(argc, argv, "s:e:h")) != -1) {
        switch(c) {
            case 'h': printf("randomkeys -s <YYYYmmdd> -e <YYYYmmdd>\n");
                      exit(0);
            case 's': start_ymd = atoi(optarg); break;
            case 'e': end_ymd = atoi(optarg); break;
        }
    }
    date_start = ymdtodate(start_ymd);
    date_end   = ymdtodate(end_ymd);
    start = mktime(&date_start);
    end = mktime(&date_end);
    assert(end > start);
    time_t range = end - start;
    srand(time(NULL));
    while(true) {
        time_t t = start + rand() % range;
        struct tm* day = localtime(&t);
        print_date_ymd(*day);
        printf("\n");
    }
}

