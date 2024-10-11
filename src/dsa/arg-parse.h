#pragma once

#include <argp.h>
#include <stdbool.h>

typedef struct {
    bool all;
    char *category;
    char *test;
    bool print_on_fail;
} Arguments;

Arguments GetDefaultArguments();
struct argp ArgpConf();

extern const char args_doc[];
extern const char doc[];
