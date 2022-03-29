// Copyright 2022 Daraban Albert-Timotei

/**
 * Useful structures/macros
 *
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef CHECKER_UTILS_H_
#define CHECKER_UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

#endif  // CHECKER_UTILS_H_
