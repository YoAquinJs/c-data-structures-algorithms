#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

#include "test-map.h"

const char *program_version = "argp_example 1.0";
static char doc[] = "C test suite for algorithms and data structures";

static char args_doc[] = "";

static struct argp_option options[] = {
    {"all",             'a', NULL, 0, "Run all tests", 1},
    {"category",        'c', "CATEGORY", 0, "Run all tests in category", 1},
    {"test",            't', "TEST_NAME", 0, "Run a specific test", 1},
    {"print-on-fail",   'p', NULL, 0, "Optional flag to print test output on failure", 2},
    {0}
};

struct arguments {
    bool print_on_fail;
    bool all;
    char *category;
    char *test;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'a': // --all
            if (arguments->category || arguments->test) {
                argp_error(state, "Option --all cannot be used with --category or --test");
            }
            arguments->all = 1;
            break;
        case 'c': // --category
            if (arguments->all || arguments->test) {
                argp_error(state, "Option --category cannot be used with --all or --test");
            }
            arguments->category = arg;
            break;
        case 't': // --test
            if (arguments->all || arguments->category) {
                argp_error(state, "Option --test cannot be used with --all or --category");
            }
            arguments->test = arg;
            break;
        case 'p': // --print-on-fail
            arguments->print_on_fail = 1;
            break;
        case ARGP_KEY_END:
            if (!arguments->all && !arguments->category && !arguments->test) {
                argp_error(state, "One of --all, --category, or --test must be specified");
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char **argv) {
    struct arguments arguments;

    arguments.print_on_fail = false;
    arguments.all = 0;
    arguments.category = NULL;
    arguments.test = NULL;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    PRINT_ON_FAIL = arguments.print_on_fail;

    if (arguments.all)
        run_all_tests();

    if (arguments.category)
        run_category_tests(arguments.category);

    if (arguments.test)
        run_single_test(arguments.test);

    return 0;
}
