#ifndef MAGIC_UTILS_H_
#define MAGIC_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define     BUFFER_LEN              1024
#define     MAX_WORD_LEN            100

void        magic_words             (void);
void        magic_ciphers           (void);
void        two_grams               (void);

#endif /* MAGIC_UTILS_H_ */