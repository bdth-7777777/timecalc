#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_usage() {
    printf("Usage: time_diff -start \"HH:MM:SS.CC\" -end \"HH:MM:SS.CC\"\n");
    printf("Calculate the difference between two times provided in the format \"HH:MM:SS.CC\"\n");
    printf("Options:\n");
    printf("  -h, -help   Show this help message\n");
}

struct TimeComponents {
    int hours;
    int minutes;
    int seconds;
    int hundredths;
};

int parse_time(const char *time_str, struct TimeComponents *components) {
    return sscanf(time_str, "%d:%d:%d.%d",
                  &components->hours,
                  &components->minutes,
                  &components->seconds,
                  &components->hundredths) == 4;
}

void calculate_time_diff(struct TimeComponents *start, struct TimeComponents *end, struct TimeComponents *diff) {
    int start_in_hundredths = start->hours * 360000 + start->minutes * 6000 + start->seconds * 100 + start->hundredths;
    int end_in_hundredths = end->hours * 360000 + end->minutes * 6000 + end->seconds * 100 + end->hundredths;
    int diff_in_hundredths = end_in_hundredths - start_in_hundredths;

    if (diff_in_hundredths < 0) {
        printf("End time is before start time.\n");
        exit(EXIT_FAILURE);
    }

    diff->hours = diff_in_hundredths / 360000;
    diff_in_hundredths %= 360000;
    diff->minutes = diff_in_hundredths / 6000;
    diff_in_hundredths %= 6000;
    diff->seconds = diff_in_hundredths / 100;
    diff->hundredths = diff_in_hundredths % 100;
}

int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0)) {
        print_usage();
        return EXIT_SUCCESS;
    }

    if (argc != 5) {
        print_usage();
        return EXIT_FAILURE;
    }

    struct TimeComponents start_time, end_time, diff_time;

    if (strcmp(argv[1], "-start") == 0 && parse_time(argv[2], &start_time) &&
        strcmp(argv[3], "-end") == 0 && parse_time(argv[4], &end_time)) {
        calculate_time_diff(&start_time, &end_time, &diff_time);
        printf("%02d:%02d:%02d.%02d\n",
               diff_time.hours, diff_time.minutes, diff_time.seconds, diff_time.hundredths);
    } else {
        printf("Invalid arguments.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}