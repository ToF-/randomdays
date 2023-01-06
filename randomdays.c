#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

const int MAX_DISPLAY = 30;

void ymd(int ymd, int *y, int *m, int *d) {

    *y = ymd / 10000;
    int rm = ymd % 10000;
    *m = rm / 100;
    *d = rm % 100;
}

int main(int argc, char *argv[]) {
    time_t time_stamp_now = time(NULL);
    struct tm *date_now = localtime(&time_stamp_now);
    struct tm date_start = *date_now;
    struct tm date_end = *date_now;
    date_start.tm_year-= 2;
    date_end.tm_year+= 2;
    char display[MAX_DISPLAY];
    strftime(display, MAX_DISPLAY, "%Y%m%d", &date_start);
    int start_ymd = atoi(display);
    strftime(display, MAX_DISPLAY, "%Y%m%d", &date_end);
    int end_ymd = atoi(display);

    time_t start = mktime(&date_start);
    time_t end   = mktime(&date_end);
    char c;
    while((c = getopt(argc, argv, "s:e:h")) != -1) {
        switch(c) {
            case 'h': printf("randomkeys -s : start <YYYYmmdd>\n\t   -e : end <YYYYmmdd>\n\t");
                      exit(0);
            case 's': start_ymd = atoi(optarg); break;
            case 'e': end_ymd = atoi(optarg); break;
        }
    }
    int start_year;
    int start_month;
    int start_day;
    ymd(start_ymd, &start_year, &start_month, &start_day);
    int end_year;
    int end_month;
    int end_day;
    ymd(end_ymd, &end_year, &end_month, &end_day);
    date_start = (struct tm) { .tm_year = start_year-1900, .tm_mon = start_month, .tm_mday = start_day };
    strftime(display, MAX_DISPLAY, "%Y%m%d", &date_start);
    printf("%s\n", display);
    date_end = (struct tm) { .tm_year = end_year-1900, .tm_mon = end_month, .tm_mday = end_day };
    start = mktime(&date_start);
    end = mktime(&date_end);
    assert(end > start);
    time_t range = end - start;
    srand(time(NULL));
    while(true) {
        time_t t = start + rand() % range;
        struct tm* day = localtime(&t);
        strftime(display, MAX_DISPLAY, "%Y%m%d", day);
        printf("%s\n", display);
    }
}

