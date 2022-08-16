#!/bin/bash

EXEC="magic_temple"

function init {
	total_score=10
	pad=$(printf '%.1s' "."{1..70})
	padlength=71

	make
	if [ $? -ne 0 ]; then
		echo "Makefile failed!"
		exit 1
	fi

	mkdir -p output/magic_words
	mkdir -p output/magic_cipher/caesar
	mkdir -p output/magic_cipher/vigenere
	mkdir -p output/magic_cipher/addition
	mkdir -p output/two_grams/
}

function print_result {
	printf "%s" "$1"
	printf "%*.*s" 0 $((padlength - ${#1} - ${#2} )) "$pad"
	printf "%s\n" "$2"
}

function check_task {
	start_test_id=0
	end_test_id=4
	test_score=8

	echo "............................MAGIC WORDS................................"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/magic_words/input${test_id}.txt"
            ref_file="./ref/magic_words/ref${test_id}.txt"
            output_file="./output/magic_words/output${test_id}.txt"
	
		./$EXEC < "$test_file" > "$output_file"
	
		if [ -f "$output_file" ]; then
			if diff -w "$output_file" "$ref_file" &> /dev/null; then
				let "total_score += $test_score"
				print_result "Test ${test_id}" "${test_score}/${test_score}p passed"
			else 
				print_result "Test ${test_id}" "0/${test_score}p failed"
			fi
		fi
		rm -f "$output_file"
	done

    echo " "

	echo "...........................MAGIC CIPHER................................"

    for subtask in "caesar" "vigenere" "addition"; do
        start_test_id=0
        end_test_id=4
        
        if [ $subtask == "vigenere" ]; then
            test_score=2
        else
            test_score=4
        fi

        if [ $subtask == "caesar" ]; then
            echo "..............................CAESAR..................................."
        elif [ $subtask == "vigenere" ]; then
            echo ".............................VIGENERE.................................."
        elif [ $subtask == "addition" ]; then
            echo ".............................ADDITION.................................."
        fi

        for test_id in $(seq $start_test_id $end_test_id); do
            test_file="./input/magic_cipher/${subtask}/input${test_id}.txt"
            ref_file="./ref/magic_cipher/${subtask}/ref${test_id}.txt"
            output_file="./output/magic_cipher/${subtask}/output${test_id}.txt"
        
            ./$EXEC < "$test_file" > "$output_file"
        
            if [ -f "$output_file" ]; then
                if diff -w "$output_file" "$ref_file" &> /dev/null; then
                    let "total_score += $test_score"
                    print_result "Test ${test_id}" "${test_score}/${test_score}p passed"
                else 
                    print_result "Test ${test_id}" "0/${test_score}p failed"
                fi
            fi
        done
    done

    echo " "

	start_test_id=0
	end_test_id=4
	test_score=10

	echo ".............................TWO GRAMS................................."

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/two_grams/input${test_id}.txt"
            ref_file="./ref/two_grams/ref${test_id}.txt"
            output_file="./output/two_grams/output${test_id}.txt"
	
		./$EXEC < "$test_file" > "$output_file"
	
		if [ -f "$output_file" ]; then
			if diff -w "$output_file" "$ref_file" &> /dev/null; then
				let "total_score += $test_score"
				print_result "Test ${test_id}" "${test_score}/${test_score}p passed"
			else 
				print_result "Test ${test_id}" "0/${test_score}p failed"
			fi
		fi
		rm -f "$output_file"
	done

    echo " "
}

init

check_task

print_result "Final score" "${total_score}/150"
make clean &> /dev/null