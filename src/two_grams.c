#include "./include/magic_utils.h"

#define WORD_SEPARATOR " \n,.!;"

void two_grams(void) {
    char *line = malloc(BUFFER_LEN);

    if (line == NULL) {
        return;
    }

    char **words = malloc(sizeof(*words) * BUFFER_LEN);

    if (words == NULL) {
        free(line);
        line = NULL;

        return;
    }

    int32_t num_of_words = 0;

    for (int32_t iter = 0; iter < BUFFER_LEN; ++iter) {
        words[iter] = malloc(MAX_WORD_LEN);
    }

    while (fgets(line, BUFFER_LEN, stdin) != NULL) {
        char *word = NULL, *rest = NULL;

        word = __strtok_r(line, WORD_SEPARATOR, &rest);

        while (word != NULL) {
            
            snprintf(words[num_of_words++], MAX_WORD_LEN, "%s", word);
            word = __strtok_r(NULL, WORD_SEPARATOR, &rest);
        }
    }

    free(line);
    line = NULL;

    --num_of_words;

    char **n2_grams = malloc(sizeof(char *) * num_of_words);

    if (n2_grams == NULL) {
        for (int32_t iter = 0; iter < BUFFER_LEN; ++iter) {
            free(words[iter]);
            words[iter] = NULL;
        }   

        free(words);
        words = NULL;

        return;
    }

    for (int32_t iter = 0; iter < num_of_words; ++iter) {
        n2_grams[iter] = malloc(MAX_WORD_LEN);
        
        snprintf(n2_grams[iter], MAX_WORD_LEN, "%s %s", words[iter], words[iter + 1]);
    }

    for (int32_t iter = 0; iter < BUFFER_LEN; ++iter) {
        free(words[iter]);
        words[iter] = NULL;
    }

    free(words);
    words = NULL;

    int *freq_2grams = malloc(sizeof(int) * num_of_words);

    if (freq_2grams == NULL) {
        for (int32_t iter = 0; iter < num_of_words; ++iter) {
            free(n2_grams[iter]);
            n2_grams[iter] = NULL;
        }

        free(n2_grams);
        n2_grams = NULL;        
    }

    char **unique_2grams = malloc(sizeof(char *) * num_of_words);

    if (unique_2grams == NULL) {
        for (int32_t iter = 0; iter < num_of_words; ++iter) {
            free(n2_grams[iter]);
            n2_grams[iter] = NULL;
        }

        free(n2_grams);
        n2_grams = NULL;

        free(freq_2grams);
        freq_2grams = NULL;
    }

    int32_t uniq_2grams_num = 1;
    uint8_t not_found_gram = 1;

    for (int32_t iter = 0; iter < num_of_words; ++iter) {
        unique_2grams[iter] = malloc(MAX_WORD_LEN);
    }

    snprintf(unique_2grams[0], MAX_WORD_LEN, "%s", n2_grams[0]);
    freq_2grams[0] = 1;

    for (int32_t iter_i = 1; iter_i < num_of_words; ++iter_i) {
        for (int32_t iter_j = 0; iter_j < uniq_2grams_num; ++iter_j) {
            if (strncmp(unique_2grams[iter_j], n2_grams[iter_i], MAX_WORD_LEN) == 0) {
                freq_2grams[iter_j]++;
                not_found_gram = 0;
            }
        }

        if (not_found_gram == 1) {
            snprintf(unique_2grams[uniq_2grams_num], MAX_WORD_LEN, "%s", n2_grams[iter_i]);
            freq_2grams[uniq_2grams_num] = 1;
            ++uniq_2grams_num;
        } else {
            not_found_gram = 1;
        }
    }

    printf("%d\n", uniq_2grams_num);
    for (int32_t iter = 0; iter < uniq_2grams_num; ++iter) {
        printf("%s %d\n", unique_2grams[iter], freq_2grams[iter]);
    }

    for (int32_t iter = 0; iter < num_of_words; ++iter) {
        free(unique_2grams[iter]);
        unique_2grams[iter] = NULL;

        free(n2_grams[iter]);
        n2_grams[iter] = NULL;
    }

    free(unique_2grams);
    unique_2grams = NULL;

    free(n2_grams);
    n2_grams = NULL;

    free(freq_2grams);
    freq_2grams = NULL;
}