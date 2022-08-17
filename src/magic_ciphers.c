#include "./include/magic_utils.h"

#define LETTER_NUM 26
#define DIGITS_NUM 10
#define MAX_KEY_LEN 15

/**
 * @brief Function to print a string literal
 * on the stdout
 * 
 * @param code a pointer to a string object
 */
void print_code(const char * const code) {
    if (code == NULL) {
        return;
    }
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        printf("%c", code[iter]);
    }
}

/**
 * @brief Function to reverse a string object
 * 
 * @param code a pointer to a string object
 */
void reverse_string(char * const code) {
    if (code == NULL) {
        return;
    }

    size_t code_len = strlen(code);
    size_t half_code_len = code_len / 2;

    /* Reverse ffs */
    for (size_t iter = 0; iter < half_code_len; ++iter) {
        char temp_chr = code[iter];
        code[iter] = code[code_len - iter - 1];
        code[code_len - iter - 1] = temp_chr;
    }
}

/**
 * @brief Program to decipher the caeser encription. The decoded
 * message will be found in-place in the encoded message
 * 
 * @param code[in/out] a pointer to an ecoded message
 * @param code_key the encription key
 */
void caeser_deciphering(char * const code, int32_t code_key) {
    if (code == NULL) {
        return;
    }

    /* Decipher */
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {
        if ((code[iter] >= 'a') && (code[iter] <= 'z')) {

            /* Decipher a small letter */
            if (code[iter] - code_key % LETTER_NUM < 'a') {
                code[iter] += 'z' - 'a' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= 'A') && (code[iter] <= 'Z')) {

            /* Decipher a big letter */
            if (code[iter] - code_key % LETTER_NUM < 'A') {
                code[iter] += 'Z' - 'A' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= '0') && (code[iter] <= '9')) {

            /* Decipher a digit */
            if (code[iter] - code_key % DIGITS_NUM < '0') {
                code[iter] += '9' - '0' + 1 - code_key % DIGITS_NUM;
            } else {
                code[iter] -= code_key % DIGITS_NUM;
            }
        }
    }
}

/**
 * @brief Subroutine program to decipher a string of numbers
 * encripted by caeser cipher. The string will be modified in-place
 * 
 * @param code[in/out] a pointer to a string object
 * @param code_key the caeser encription key
 */
void caeser_deciphering_numbers(char * const code, int32_t code_key) {
    if (code == NULL) {
        return;
    }

    /* Decipher */
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

/**
 * @brief Program to decipher the vigenere encription. The decoded
 * message will be found in-place in the encoded message
 * 
 * @param code[in/out] a pointer to a string object
 * @param str_key the string vigenere encription key
 */
void vigenere_deciphering(char * const code, const char * const str_key) {
    if ((code == NULL) || (str_key == NULL)) {
        return;
    }

    size_t str_key_len = strlen(str_key);
    
    /* Decipher */
    for (int32_t iter = 0; code[iter] != '\0'; ++iter) {

        /* Get the code key from string encription key */
        int code_key = str_key[iter % str_key_len] - 'A';

        if ((code[iter] >= 'a') && (code[iter] <= 'z')) {

            /* Decipher a small letter */
            if (code[iter] - code_key % LETTER_NUM < 'a') {
                code[iter] += 'z' - 'a' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= 'A') && (code[iter] <= 'Z')) {

            /* Decipher a big letter */
            if (code[iter] - code_key % LETTER_NUM < 'A') {
                code[iter] += 'Z' - 'A' + 1 - code_key % LETTER_NUM;
            } else {
                code[iter] -= code_key % LETTER_NUM;
            }
        } else if ((code[iter] >= '0') && (code[iter] <= '9')) {

            /* Decipher a number */
            if (code[iter] - code_key % DIGITS_NUM < '0') {
                code[iter] += '9' - '0' + 1 - code_key % DIGITS_NUM;
            } else {
                code[iter] -= code_key % DIGITS_NUM;
            }
        }
    }
}

/**
 * @brief Subroutine function to calculate the sum of two numbers
 * represented as string literrals. The user has to be sure that the length of the first
 * string is bigger or equal than the length of the second string object. Strings have to be
 * reversed and the answer is also reverseed.
 * 
 * @param str1 a pointer to the biggest string object
 * @param str2 a pointer to the smallest string object
 * @param str1_len length of the first string literal
 * @param str2_len length of the second string literal
 * @return char* a pointer to an allocated string object or NULL.
 */
char* add_two_strings(const char * const str1, const char * const str2, size_t str1_len, size_t str2_len) {
    /* Allocate the result string */
    char* add_str = malloc(str1_len + 2);

    if (add_str == NULL) {
        return NULL;
    }

    int32_t rest = 0, current_count = 0;

    /* Add the two strings */
    for (size_t iter = 0; iter < str1_len; ++iter) {
        if (iter < str2_len) {
            current_count = str1[iter] - '0' + str2[iter] - '0' + rest;
        } else {
            current_count = str1[iter] - '0' + rest;
        }

        add_str[iter] = current_count % DIGITS_NUM + '0';
        rest = current_count / DIGITS_NUM;
    }

    /* Add the last remaining */
    add_str[str1_len] = rest + '0';

    /* Add NULL terminator for string */
    add_str[str1_len + 1] = '\0';

    /* Return the result string */
    return add_str;
}

/**
 * @brief Function to solve "magic ciphers" task explained
 * in the readme file
 * 
 */
void magic_ciphers(void) {
    /* Allocate a string buffer */
    char *encoded = malloc(BUFFER_LEN);

    if (encoded == NULL) {
        return;
    }

    /* Read the buffer */
    if (scanf("%s", encoded) > 1) {
        free(encoded);
        encoded = NULL;

        return;
    }

    if (strncmp(encoded, "caesar", BUFFER_LEN) == 0) {

        /* The encoded buffer will solve the caeser decipher */
        int32_t code_key = 0;

        /* Read the encription key */
        if (scanf("%d", &code_key) > 1) {
            free(encoded);
            encoded = NULL;

            return;
        }

        /* Read the encoded string to decipher */
        if (scanf("%s", encoded) > 1) {
            free(encoded);
            encoded = NULL;

            return;
        }

        /* Decipher the message and print it */
        caeser_deciphering(encoded, code_key);
        print_code(encoded);
        printf("\n");
        
        free(encoded);
        encoded = NULL;
    } else if (strncmp(encoded, "vigenere", BUFFER_LEN) == 0) {

        /* The encoded buffer will solve the vigenere decipher */
        char *str_key = malloc(MAX_KEY_LEN);

        if (str_key == NULL) {
            return;
        }

        /* Read the encription string key */
        if (scanf("%s", str_key) > 1) {
            free(str_key);
            str_key = NULL;

            free(encoded);
            encoded = NULL;

            return;
        }

        /* Raed the encoded message */
        if (scanf("%s", encoded) > 1) {
            free(str_key);
            str_key = NULL;

            free(encoded);
            encoded = NULL;

            return;
        }

        /* Decipher the code and print it */
        vigenere_deciphering(encoded, str_key);
        print_code(encoded);
        printf("\n");

        free(str_key);
        str_key = NULL;

        free(encoded);
        encoded = NULL;
    } else if (strncmp(encoded, "addition", BUFFER_LEN) == 0) {

        /* The encoded buffer will solve the two string addition */
        free(encoded);
        encoded = NULL;

        int32_t code_key = 0;

        /* Allocate two strings to add */
        char *str1_nums = malloc(BUFFER_LEN);
        char *str2_nums = malloc(BUFFER_LEN);

        /* Read the caeser cihper key for numbers */
        if (scanf("%d", &code_key) > 1) {
            free(str1_nums);
            str1_nums = NULL;

            free(str2_nums);
            str2_nums = NULL;

            return;
        }

        /* Read the string literals */
        if (scanf("%s%s", str1_nums, str2_nums) > 2) {
            free(str1_nums);
            str1_nums = NULL;

            free(str2_nums);
            str2_nums = NULL;

            return;
        }

        /* Decipher the strings */
        caeser_deciphering_numbers(str1_nums, code_key % DIGITS_NUM);
        caeser_deciphering_numbers(str2_nums, code_key % DIGITS_NUM);

        /* Reverse the strings so you could add them */
        reverse_string(str1_nums);
        reverse_string(str2_nums);

        size_t str1_nums_len = strlen(str1_nums);
        size_t str2_nums_len = strlen(str2_nums);

        char *add_str = NULL;

        /* Compute the addition strings result */
        if (str1_nums_len > str2_nums_len) {
            add_str = add_two_strings(str1_nums, str2_nums, str1_nums_len, str2_nums_len);
        } else {
            add_str = add_two_strings(str2_nums, str1_nums, str2_nums_len, str1_nums_len);
        }

        /* Reverse the result string */
        reverse_string(add_str);

        int trailling_zero = 0;

        /* Calculate the trailling zeros from the beginning of number */
        for (int32_t iter = 0; add_str[iter] != '\0'; ++iter) {
            if (add_str[iter] != '0') {
                break;
            } else {
                ++trailling_zero;
            }
        }

        /* Print the result string without trailling zeros */
        print_code(add_str + trailling_zero);

        free(str1_nums);
        str1_nums = NULL;

        free(str2_nums);
        str2_nums = NULL;

        free(add_str);
        add_str = NULL;

        printf("\n");

    } else {

        /* Encoded buffer does NOT know what to solve */
        printf("Unknown command ........ EXIT!\n");

        free(encoded);
        encoded = NULL;

        return;
    }
}