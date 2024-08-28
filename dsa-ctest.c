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
    "usage: %s"
    "[--all | --category CATEGORY | --test TEST_NAME]"
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
        {"test", required_argument, NULL, 'i'},
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
    printf("running all tests...\n");

    for (int i=0; i < TEST_COUNT; i++){
        printf("\n");
        if (!run_test(TESTS[i]))
            exit(EXIT_FAILURE);
    }
}

void run_category_tests(const char *category_name) {
    Category category = get_category(category_name);
    if (category == invalid){
        printf("invalid category\n");
        exit(EXIT_FAILURE);
    }

    printf("running all tests in '%s'...\n", category_name);
    Test* category_tests = get_category_tests(category);
    for (int i=0; i < TESTS_BY_CATEGORY_COUNT[category]; i++){
        printf("\n");
        if (!run_test(category_tests[i]))
            exit(EXIT_FAILURE);
    }
}

void run_individual_test(const char *test_name) {
    Test test = get_test(test_name);
    if (test == invalid){
        printf("invalid test\n");
        exit(EXIT_FAILURE);
    }

    printf("running test...\n\n");
    if (!run_test(test))
        exit(EXIT_FAILURE);
}
