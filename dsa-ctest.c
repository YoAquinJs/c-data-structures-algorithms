#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "test-map.h"

void run_all_tests();
void run_category_tests(const char *category);
void run_individual_test(const char *test_name);

void usage(char name[], FILE* buff){
    const char usage_str[] =
    "Usage: %s"
    "[--all | --category CATEGORY | --single TEST_NAME]"
    "[--print-on-fail]k\n";
    fprintf(buff, usage_str, name);
}

bool print_on_fail = false;

int main(int argc, char *argv[]) {
    if (argc < 2){
        usage(argv[0], stderr);
        exit(EXIT_FAILURE);
    }

    static struct option long_options[] = {
        {"all", no_argument, NULL, 'a'},
        {"category", required_argument, NULL, 'c'},
        {"individual", required_argument, NULL, 'i'},
        {"print-on-fail", no_argument, NULL, 'p'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "ac:i:ph", long_options, NULL)) != -1) {
        switch (opt) {
            case 'a':
                run_all_tests();
                break;
            case 'c':
                run_category_tests(optarg);
                break;
            case 'i':
                run_individual_test(optarg);
                break;
            case 'p':
                print_on_fail = 1;
                break;
            case 'h':
                usage(argv[0], stdout);
                exit(EXIT_SUCCESS);
            default:
                usage(argv[0], stderr);
                exit(EXIT_FAILURE);
        }
    }
}

void run_all_tests() {
    printf("Running all tests...\n");
}

void run_category_tests(const char *category) {
    printf("Running tests for category: %s\n", category);
}

void run_individual_test(const char *test_name) {
    printf("Running individual test: %s\n", test_name);
}
