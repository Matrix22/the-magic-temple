CFLAGS += -c -g -Wall -Wextra -Wpedantic \
                  -Wformat=2 -Wno-unused-parameter \
                  -Wshadow -Wwrite-strings -Wstrict-prototypes \
                  -Wold-style-definition -Wredundant-decls \
                  -Wnested-externs -Wmissing-include-dirs \
                  -Wjump-misses-init -Wlogical-op -O2

PATH_TO_FILES += ../src
PATH_TO_HEADER_FILES += $(PATH_TO_FILES)/include

FILES += $(PATH_TO_FILES)/magic_words.c $(PATH_TO_FILES)/magic_ciphers.c \
		 $(PATH_TO_FILES)/two_grams.c $(PATH_TO_FILES)/magic_temple.c

.PHONY: build clean

build: magic_temple
	@rm -rf *.o

magic_temple: magic_obj_files
	@gcc *.o -o magic_temple

magic_obj_files:
	@gcc $(CFLAGS) $(FILES)

clean:
	@find . -type f -name "*.o" -exec rm -rf {} \;
	@rm -rf output magic_temple