#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

#include "arg-parse.h"
#include "test-map.h"

const char *program_version = "dsa-ctest 1.0";
const char doc[] = "C test suite for algorithms and data structures";

int main(int argc, char **argv) {
    Arguments arguments = GetDefaultArguments();
    struct argp argp_config = ArgpConf();
    argp_parse(&argp_config, argc, argv, 0x0, NULL, &arguments);

    PRINT_ON_FAIL = arguments.print_on_fail;

    if (arguments.all) {
        RunAllTests();
    }

    if (arguments.category) {
        RunCategoryTests(arguments.category);
    }

    if (arguments.test) {
        RunSingleTest(arguments.test);
    }

    return 0;
}
