# the-magic-temple
A mini program with different tasks to solve basically string problems, chiphers and very simple "2-grams"

## Table of Contents

1. [Getting Started](#start-description)
2. [Building](#build-description)
3. [Testing](#test-description)

<a name="start-description"></a>
## Getting Started

The current project is basically some examples to use string literals, nothing fancy. The project is devided in thre main partsȘ
* **magic words** - the source code can be found at [magic_words.c](/src/magic_words.c).
* **magic ciphers** - the source code can be found at [magic_ciphers.c](/src/magic_ciphers.c).
* **two grams** - the source code can be found at [two_grams.c](/src/two_grams.c).

### **Magic Words**

Entering the magic temple, the first magic room is a matrix of **NxM** dimension, your task is to traverse the matrix to get in the next room, however the **right** path is encoded and you must
to decode it. On the temple's walls are written some codes and you see that thise codes have a small pattern:

* Some codes start with letter **a** and have the following form **aQ1Q2Q3Q4**, where Q_i is a digit.
    * Q1 - represents moving to the right from current position
    * Q2 - represents moving up from current position
    * Q3 - represents moving to the left from the current position
    * Q4 - represents moving down from current position.

    The maximum number from those 4 will dictate the **next** moving step.

* Some codes start with letter **b** and have the following form **bQ1Q2...Qn**, where Q_i is a digit. Now let's consider MOV_1 = number(**Q1Q2...Qn**), MOV_2 = number(**Qn-1,Qn**).
    * If MOV_1 is palindrome and MOV_2 is prime : moving to left
    * If MOV_1 is palindrome and MOV_2 is not prime : moving to right
    * If MOV_1 is not palindrome and MOV_2 is prime : moving up
    * If MOV_1 is not palindrome and MOV_2 is not prime : moving down

* Some codes start with letter **c** and have the following form **cNKQ1Q2...Qn**, where Q_i is a digit. Now let's consider SUM = Q0 + QK + Q2K + ... + QK-1K (numbers are selected circulary from K to K) and N is the number of Q's.
    * If SUM % 4 = 0 : moving to left
    * If SUM % 4 = 1 : moving up
    * If SUM % 4 = 2 : moving right
    * If SUM % 4 = 3 : moving down

After all the codes are processed you must print your way on the **magic temple** wall for the next person that will step in the magic temple.

### **Magic Ciphers**

After you pass the first room you enter the second room, but this tim eyou hear a strange voice, however the words are very strange. Because you are a good programmer you know that the words are encripted and understand that the encriptions are caeser, vigenere and sometimes you have to add those decoded messages. If you find all the right messages the strange voice will open the door for the next room.

**Check** the [input](/build/input/magic_ciphers/) folder data to show how the voice speaks to you.

### **Two Grams**

After you pass and the second room in the third room you see on the floor not encoded text and the voice tells you if you help it to find the set of all **two grams** and to print their frequency in the text you are free to leave the magic temple with the biggest ever prize **(its mom)**.

**Check** the [input](/build/input/two_grams/) folder data to show how the text is represented to you.

<a name="build-description"></a>
## Building

In order to build the project make sure that you are on a LINUX machine or **WSL**, the enter the build folder and to run the *Makefile**:

```BASH
    cd build
    make
```

After that you will get the executable **magic_temple** run it and select the room that you want to break.

```BASH
    ./magic_temple
    1
    ...the input data...
```

<a name="test-description"></a>
## Testing

If you want to check some input files and references files you have to check the **input** and **ref** folder from the **build** folder.
In order to check if the program creates the right output you shall execute:

```BASH
    ./temple_run.sh
```

After that you will get an output message to see what task failed and what task passed.

I encourage you to look on the input and reference folders to see how the input data is represented and how the output is printed.