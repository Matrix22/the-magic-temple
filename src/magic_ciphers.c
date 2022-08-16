#include "./include/magic_utils.h"

#define LETTER_NUM 26
#define DIGITS_NUM 10
#define MAX_KEY_LEN 15

void print_code(const char * const code) {
    if (code == NULL) {
        return;
    }
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        printf("%c", code[iter]);
    }
}

void reverse_string(char * const code) {
    if (code == NULL) {
        return;
    }

    size_t code_len = strlen(code);
    size_t half_code_len = code_len / 2;

    for (size_t iter = 0; iter < half_code_len; ++iter) {
        char temp_chr = code[iter];
        code[iter] = code[code_len - iter - 1];
        code[code_len - iter - 1] = temp_chr;
    }
}

void caeser_deciphering(char * const code, int32_t code_key) {
    if (code == NULL) {
        return;
    }

    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        if ((code[iter] >= 'a') && (code[iter] <= 'z')) {
            if (code[iter] - code_key % LETTER_NUM < 'a') {
                code[iter] += 'z' - 'a' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= 'A') && (code[iter] <= 'Z')) {
            if (code[iter] - code_key % LETTER_NUM < 'A') {
                code[iter] += 'Z' - 'A' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= '0') && (code[iter] <= '9')) {
            if (code[iter] - code_key % DIGITS_NUM < '0') {
                code[iter] += '9' - '0' + 1 - code_key % DIGITS_NUM;
            } else {
                code[iter] -= code_key % DIGITS_NUM;
            }
        }
    }
}

void caeser_deciphering_numbers(char * const code, int32_t code_key) {
    if (code == NULL) {
        return;
    }
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        if ((code[iter] >= '0') && (code[iter] <= '9')) {
            if (code[iter] - code_key < '0') {
                code[iter] += '9' - '0' + 1 - code_key;
            } else {
                code[iter] -= code_key;
            }
        }
    }
}

void vigenere_deciphering(char * const code, const char * const str_key) {
    if ((code == NULL) || (str_key == NULL)) {
        return;
    }

    size_t str_key_len = strlen(str_key);
    
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        int code_key = str_key[iter % str_key_len] - 'A';

        if ((code[iter] >= 'a') && (code[iter] <= 'z')) {
            if (code[iter] - code_key % LETTER_NUM < 'a') {
                code[iter] += 'z' - 'a' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= 'A') && (code[iter] <= 'Z')) {
            if (code[iter] - code_key % LETTER_NUM < 'A') {
                code[iter] += 'Z' - 'A' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= '0') && (code[iter] <= '9')) {
            if (code[iter] - code_key % DIGITS_NUM < '0') {
                code[iter] += '9' - '0' + 1 - code_key % DIGITS_NUM;
            } else {
                code[iter] -= code_key % DIGITS_NUM;
            }
        }
    }
}

char* add_two_strings(const char * const str1, const char * const str2, size_t str1_len, size_t str2_len) {
    char* add_str = malloc(str1_len + 2);

    if (add_str == NULL) {
        return NULL;
    }

    int32_t rest = 0, current_count = 0;

    for (size_t iter = 0; iter < str1_len; ++iter) {
        if (iter < str2_len) {
            current_count = str1[iter] - '0' + str2[iter] - '0' + rest;
        } else {
            current_count = str1[iter] - '0' + rest;
        }

        add_str[iter] = current_count % DIGITS_NUM + '0';
        rest = current_count / DIGITS_NUM;
    }

    add_str[str1_len] = rest + '0';

    add_str[str1_len + 1] = '\0';

    return add_str;
}

void magic_ciphers(void) {
    char *encoded = malloc(BUFFER_LEN);

    if (encoded == NULL) {
        return;
    }

    if (scanf("%s", encoded) > 1) {
        free(encoded);
        encoded = NULL;

        return;
    }

    if (strncmp(encoded, "caesar", BUFFER_LEN) == 0) {
        int32_t code_key = 0;

        if (scanf("%d", &code_key) > 1) {
            free(encoded);
            encoded = NULL;

            return;
        }

        if (scanf("%s", encoded) > 1) {
            free(encoded);
            encoded = NULL;

            return;
        }

        caeser_deciphering(encoded, code_key);
        print_code(encoded);
        printf("\n");
        
        free(encoded);
        encoded = NULL;
    } else if (strncmp(encoded, "vigenere", BUFFER_LEN) == 0) {
        char *str_key = malloc(MAX_KEY_LEN);

        if (str_key == NULL) {
            return;
        }

        if (scanf("%s", str_key) > 1) {
            free(str_key);
            str_key = NULL;

            free(encoded);
            encoded = NULL;

            return;
        }

        if (scanf("%s", encoded) > 1) {
            free(str_key);
            str_key = NULL;

            free(encoded);
            encoded = NULL;

            return;
        }

        vigenere_deciphering(encoded, str_key);
        print_code(encoded);
        printf("\n");

        free(str_key);
        str_key = NULL;

        free(encoded);
        encoded = NULL;
    } else if (strncmp(encoded, "addition", BUFFER_LEN) == 0) {
        free(encoded);
        encoded = NULL;

        int32_t code_key = 0;

        char *str1_nums = malloc(BUFFER_LEN);
        char *str2_nums = malloc(BUFFER_LEN);

        if (scanf("%d", &code_key) > 1) {
            free(str1_nums);
            str1_nums = NULL;

            free(str2_nums);
            str2_nums = NULL;

            return;
        }

        if (scanf("%s%s", str1_nums, str2_nums) > 2) {
            free(str1_nums);
            str1_nums = NULL;

            free(str2_nums);
            str2_nums = NULL;

            return;
        }

        caeser_deciphering_numbers(str1_nums, code_key % DIGITS_NUM);
        caeser_deciphering_numbers(str2_nums, code_key % DIGITS_NUM);

        reverse_string(str1_nums);
        reverse_string(str2_nums);

        size_t str1_nums_len = strlen(str1_nums);
        size_t str2_nums_len = strlen(str2_nums);

        char *add_str = NULL;

        if (str1_nums_len > str2_nums_len) {
            add_str = add_two_strings(str1_nums, str2_nums, str1_nums_len, str2_nums_len);
        } else {
            add_str = add_two_strings(str2_nums, str1_nums, str2_nums_len, str1_nums_len);
        }

        reverse_string(add_str);

        int trailling_zero = 0;

        for (int32_t iter = 0; add_str[iter] != '\0'; ++iter) {
            if (add_str[iter] != '0') {
                break;
            } else {
                ++trailling_zero;
            }
        }

        print_code(add_str + trailling_zero);

        free(str1_nums);
        str1_nums = NULL;

        free(str2_nums);
        str2_nums = NULL;

        free(add_str);
        add_str = NULL;

        printf("\n");

    } else {
        printf("Unknown command ........ EXIT!\n");

        free(encoded);
        encoded = NULL;

        return;
    }
}