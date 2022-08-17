#include "./include/magic_utils.h"

#define MAX_MATRIX_DIM 100
#define WORD_SEPARATOR " "
#define MAX_TYPE_A_LEN 5
#define TENS_NUM       10
#define DIRECTION_NUMBERS 4

/**
 * @brief Function to check if a string is palindrome
 * 
 * @param str a pointer to a string object
 * @param str_len the length of the string object
 * @return uint8_t 1 if string is palindrom, 0 otherwise
 */
uint8_t is_palindrom(char *str, int32_t str_len) {
    if (NULL == str) {
        return 0;
    }

    int32_t half_len = str_len / 2;
    
    for (int32_t iter = 1; iter < half_len; ++iter) {
        if (str[iter] != str[str_len - iter]) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Function to check if an integer number
 * is prime or not.
 * 
 * @param check_num number to check 
 * @return uint8_t 1 if number is prime, 0 otherwise
 */
uint8_t is_prime(int32_t check_num) {
    if (check_num < 2) {
        return 0;
    } else if (check_num == 2) {
        return 1;
    }

    for (int32_t iter = 2; (iter * iter) <= check_num; ++iter) {
        if (check_num % iter == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Function to solve "magic words" task explained
 * in the readme file
 * 
 */
void magic_words(void) {
    
    /* Initialize dimensions and the path matrix */
    int32_t row_dim = 0, col_dim = 0;
    int32_t path[MAX_MATRIX_DIM][MAX_MATRIX_DIM] = {0};

    int32_t last_x = 0, last_y = 0, count_steps = 1;
    
    /* Initialize string buffers */
    char line[BUFFER_LEN] = "";
    char *code = NULL, *rest = NULL;

    if (scanf("%d%d\n", &row_dim, &col_dim) > 2) {
        return;
    }
    
    path[last_y][last_x] = count_steps;

    if (scanf("%[^\n]s", line) > 1) {
        return;
    }

    /* Extract first word from line */
    code = __strtok_r(line, WORD_SEPARATOR, &rest);

    /* Traverse every word from line */
    while (code != NULL) {
        ++count_steps;

        if (code[0] == 'a') {

            /* Processing code is first type */
            char max_code_char = '0';
            int32_t max_code_index = 0;

            /* Find the maximum number from code */
            for (int32_t iter = 1; iter < MAX_TYPE_A_LEN; ++iter) {
                if (code[iter] > max_code_char) {
                    max_code_char = code[iter];
                    max_code_index = iter;
                }
            }

            /* Compute the moving path */
            if (max_code_index == 1) {
                ++last_x;
            } else if (max_code_index == 2) {
                --last_y;
            } else if (max_code_index == 3) {
                --last_x;
            } else {
                ++last_y;
            }
        } else if (code[0] == 'b') {

            /* Processing code is the second type */
            size_t code_len = strlen(code);
            uint8_t check_palindrome = is_palindrom(code, code_len);
            int32_t check_prime = is_prime(TENS_NUM * (code[code_len - 2] - '0') + (code[code_len - 1] - '0'));

            /* Compute the moving path */
            if ((check_palindrome != 0) && (check_prime != 0)) {
                --last_x;
            } else if (check_palindrome != 0) {
                ++last_x;
            } else if (check_prime != 0) {
                --last_y;
            } else {
                ++last_y;
            }
        } else if (code[0] == 'c') {

            /* Processing code is the third type */
            int32_t circular_sum = 0;
            int32_t total_num_len = (code[1] - '0');
            int32_t modulo_num = (code[2] - '0');

            /* Compute the circular sum */
            for (int32_t iter = 0; iter < modulo_num; ++iter) {
                circular_sum += (code[3 + (iter * modulo_num) % total_num_len] - '0');
            }

            circular_sum = circular_sum % DIRECTION_NUMBERS;

            /* Compute the moving path */
            if (circular_sum == 0) {
                --last_x;
            } else if (circular_sum == 1) {
                --last_y;
            } else if (circular_sum == 2) {
                ++last_x;
            } else {
                ++last_y;
            }
        } else {

            /* Code type unknown */
            printf("Uknown opperand ... moving to next\n");
        }

        /* Update path matrix */
        path[last_y][last_x] = count_steps;

        /* Extract the next word */
        code = __strtok_r(NULL, WORD_SEPARATOR, &rest);
    }

    /* Print the resulting matrix after all operations */
    for (int32_t iter_i = 0; iter_i < row_dim; ++iter_i) {
        for (int32_t iter_j = 0; iter_j < col_dim; ++iter_j) {
            printf("%d ", path[iter_i][iter_j]);
        }

        printf("\n");
    }
}