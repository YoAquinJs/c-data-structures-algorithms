#include <stdlib.h>
#include <argp.h>

#include "arg-parse.h"

const char args_doc[] = "must always select one of --all, --category and --test";

static struct argp_option options[] = {
    {"all",             'a', NULL,          0, "Run all tests", 1},
    {"category",        'c', "CATEGORY",    0, "Run all tests in category", 1},
    {"test",            't', "TEST_NAME",   0, "Run a specific test", 1},
    {"print-on-fail",   'p', NULL,          0, "Optional flag to print test output on failure", 2},
    {0}
};

Arguments get_default_arguments(){
    Arguments args;
    args.print_on_fail = false;
    args.category = NULL;
    args.test = NULL;
    args.print_on_fail = false;
    return args;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    Arguments *args = state->input;

    switch (key) {
        case 'a': // --all
            if (args->category || args->test) {
                argp_error(state, "Option --all cannot be used with --category or --test");
            }
            args->all = 1;
            break;
        case 'c': // --category
            if (args->all || args->test) {
                argp_error(state, "Option --category cannot be used with --all or --test");
            }
            args->category = arg;
            break;
        case 't': // --test
            if (args->all || args->category) {
                argp_error(state, "Option --test cannot be used with --all or --category");
            }
            args->test = arg;
            break;
        case 'p': // --print-on-fail
            args->print_on_fail = 1;
            break;
        case ARGP_KEY_END:
            if (!args->all && !args->category && !args->test) {
                argp_error(state, "One of --all, --category, or --test must be specified");
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct argp argp_conf(){
    struct argp argp;
    argp.options = options;
    argp.parser = parse_opt;
    argp.args_doc = args_doc;
    argp.doc = doc;
    argp.children = NULL;
    argp.help_filter = NULL;
    argp.argp_domain = NULL;

    return argp;
}
