#include "./include/magic_utils.h"

int main(void) {
    int32_t task_number = 0;

    if (scanf("%d", &task_number) > 1) {
        return EXIT_FAILURE;
    }

    switch (task_number) {
        case 1:
            magic_words();
            break;
        case 2:
            magic_ciphers();
            break;
        case 3:
            two_grams();
            break;
        default:
            printf("Undefined task number.\n");
    }

    return 0;
}