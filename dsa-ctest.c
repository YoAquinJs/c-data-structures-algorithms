#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

#include "test-map.h"
#include "arg-parse.h"

const char *program_version = "dsa-ctest 1.0";
const char doc[] = "C test suite for algorithms and data structures";

int main(int argc, char **argv) {
    Arguments arguments = get_default_arguments();
    struct argp argp_config = argp_conf();
    argp_parse(&argp_config, argc, argv, 0x0, NULL, &arguments);

    PRINT_ON_FAIL = arguments.print_on_fail;

    if (arguments.all)
        run_all_tests();

    if (arguments.category)
        run_category_tests(arguments.category);

    if (arguments.test)
        run_single_test(arguments.test);

    return 0;
}
