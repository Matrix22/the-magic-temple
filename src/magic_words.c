#include "./include/magic_utils.h"

#define MAX_MATRIX_DIM 100
#define WORD_SEPARATOR " "
#define MAX_TYPE_A_LEN 5
#define TENS_NUM       10
#define DIRECTION_NUMBERS 4

uint8_t is_palindrom(char *str, int32_t str_len) {
    int32_t half_len = str_len / 2;
    
    for (int32_t iter = 1; iter < half_len; ++iter) {
        if (str[iter] != str[str_len - iter]) {
            return 0;
        }
    }

    return 1;
}

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

void magic_words(void) {
    int32_t row_dim = 0, col_dim = 0;
    int32_t path[MAX_MATRIX_DIM][MAX_MATRIX_DIM] = {0};

    int32_t last_x = 0, last_y = 0, count_steps = 1;
    
    char line[BUFFER_LEN] = "";
    char *code = NULL, *rest = NULL;

    if (scanf("%d%d\n", &row_dim, &col_dim) > 2) {
        return;
    }
    
    path[last_y][last_x] = count_steps;

    if (scanf("%[^\n]s", line) > 1) {
        return;
    }

    code = __strtok_r(line, WORD_SEPARATOR, &rest);

    while (code != NULL) {
        ++count_steps;

        if (code[0] == 'a') {
            char max_code_char = '0';
            int32_t max_code_index = 0;

            for (int32_t iter = 1; iter < MAX_TYPE_A_LEN; ++iter) {
                if (code[iter] > max_code_char) {
                    max_code_char = code[iter];
                    max_code_index = iter;
                }
            }

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
            size_t code_len = strlen(code);
            uint8_t check_palindrome = is_palindrom(code, code_len);

            int32_t check_prime = is_prime(TENS_NUM * (code[code_len - 2] - '0') + (code[code_len - 1] - '0'));

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
            int32_t circular_sum = 0;
            int32_t total_num_len = (code[1] - '0');
            int32_t modulo_num = (code[2] - '0');

            for (int32_t iter = 0; iter < modulo_num; ++iter) {
                circular_sum += (code[3 + (iter * modulo_num) % total_num_len] - '0');
            }

            circular_sum = circular_sum % DIRECTION_NUMBERS;

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
            printf("Uknown opperand ... moving to next\n");
        }

        path[last_y][last_x] = count_steps;

        code = __strtok_r(NULL, WORD_SEPARATOR, &rest);
    }

    for (int32_t iter_i = 0; iter_i < row_dim; ++iter_i) {
        for (int32_t iter_j = 0; iter_j < col_dim; ++iter_j) {
            printf("%d ", path[iter_i][iter_j]);
        }

        printf("\n");
    }
}