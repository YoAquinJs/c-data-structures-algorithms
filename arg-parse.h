#pragma once

#include <stdbool.h>
#include <argp.h>

typedef struct {
    bool all;
    char *category;
    char *test;
    bool print_on_fail;
} Arguments;

Arguments get_default_arguments();
struct argp argp_conf();

extern const char args_doc[];
extern const char doc[];
