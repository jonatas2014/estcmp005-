#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int MAX_CHAR = 90;
const int MIN_CHAR = 65;
const int MAX_GENERATION = 200;
const int AMOUNT_COPIES = 100;
const char *TARGET_ARRAY = "METHINKS IT IS LIKE A WEASEL";


/**
 * This function generate a random number between min and max-1
 * @param min: int, Lower limit of the range of possibilities
 * @param max: int, Upper limit of the range of possibilities
 * @return int in between lower limit and upper limite 
 **/
int generate_random_int(int min, int max);


/**
 * Generates a character in range (MIN_CHAR, MAX_CHAR) or space
 * @return char between initial and final or space
 **/
char generate_random_char();


/**
 * Generates an array of char with random characters
 * @param array_size: int, Represents the size of the array
 * @return char * representing the array
 **/
char *generate_random_array_char(int array_size);


/**
 * Make a copy of a char array and return a copy
 * @param array_char: char, character to copy
 * @return array char copy
 **/
char *copy_array_char(const char *array_char);


/** 
 * Create a matrix of copies of array char
 * @param array_char: const char *, represents the array to make copy
 * @param number_of_copies: int, Amout of copies 
 * @return A matrix of copies of param array
 **/
char **create_matrix_arrays_char(const char *array_char, int number_of_copies);


/**
 * Generate a random number and return that
 * @return 1, if random number between 1 and 20 or else in another case
 **/
int draw_with_probality_005();


/**
 * Use another string to "replace" characters Place the characters on another string
 * There is 5% of chance to replaceOnly accepted characters can be draw
 * @param array_char: const char *, array of char to replace somes chars
 * @return a array with replaced characters
 **/
char *replace_chars(const char *array_char);


/**
 * Calculate the poins based on count equals chars on array char and array target
 * @param array_char: char *, is a array of chars to compare with targe
 * @param array_target: const char *, is a array most to be checked
 * @return int to represents amount of equals chars 
 **/
int string_points(char *array_char, const char *array_target);


/**
 * Find string with more numbers of points
 * @param matrix_copies: char **, a array of array of char
 * @param array_target: const char *, a array of char
 * @return the array more close of target
 **/
char *best_string_so_far(char **matrix_copies, const char *array_target);


/**
 * Check two array are equals
 * @param size_target: int, represents the lenght of array target
 * @param start_random_array: char *, initial random array of char
 * @param array_target: char *, array target 
 **/
int it_is_correct(int size_target, char *start_random_array, const char *array_target);


int main() {
    srand(time(NULL)); 
    char *best_generation_array_char;
    char *random_initial_array = generate_random_array_char(strlen(TARGET_ARRAY));
    char **matrix_copies = create_matrix_arrays_char(random_initial_array, AMOUNT_COPIES);
    char **new_matrix_char;
    int score = 0;
    int generation = 0;
    int size_array;

    if (!it_is_correct(strlen(TARGET_ARRAY), random_initial_array, TARGET_ARRAY)) {
        
        best_generation_array_char = matrix_copies[0];
        while (score < strlen(TARGET_ARRAY) && generation < MAX_GENERATION) {
            
            generation ++;
            matrix_copies = create_matrix_arrays_char(best_generation_array_char, AMOUNT_COPIES);
            new_matrix_char = (char **) malloc(sizeof(char*) * AMOUNT_COPIES);

            for (int i = 0; i < AMOUNT_COPIES; i++) {
                size_array = strlen(matrix_copies[i]);
                new_matrix_char[i] = (char *) malloc (sizeof(char) * size_array);
                const char *tmp = matrix_copies[i];
                strcpy(new_matrix_char[i], replace_chars(tmp));
            }

            best_generation_array_char = best_string_so_far(new_matrix_char, TARGET_ARRAY);
            score = string_points(best_generation_array_char, TARGET_ARRAY);
            printf("%i : %s -- score: %i\n", generation, best_generation_array_char, score);
        }
    } else {
        printf("Today I will make a mega-sena game!!!\n");
        printf("0: %s --score: %li\n", TARGET_ARRAY, strlen(TARGET_ARRAY));
    }
    return (0);
}


int generate_random_int(int min, int max) {
    int random_number = min + rand() % (max - min);
    return random_number;
}


char generate_random_char() {
    char random_char = generate_random_int(MIN_CHAR-1, MAX_CHAR+1);
    if ((random_char >= MIN_CHAR) && (random_char <= MAX_CHAR))
        return random_char;
    else
        return ' ';
}


char *generate_random_array_char(int array_size) {
    char *random_array = (char*) malloc(array_size * sizeof(char));
    int i = 0;
    while (i < array_size) {
        random_array[i] = generate_random_char();
        i++;
    }
    return random_array;
}


char *copy_array_char(const char *array_char) {
    int size_array = strlen(array_char);
    char *array_copy = (char*) malloc(sizeof(char) * size_array);
    strcpy(array_copy, array_char);
    return array_copy;
}


char **create_matrix_arrays_char(const char *array_char, int number_of_copies) {
    int size_array = strlen(array_char);
    char **matrix = (char**) malloc(sizeof(char*) * number_of_copies);
    for (int i = 0; i < number_of_copies; i++) {
        matrix[i] = (char *) malloc (sizeof(char) * size_array);
        strcpy(matrix[i], array_char);
    }
    return matrix;
}


int draw_with_probality_005() {
    int draw = generate_random_int(1, 20);
    if (draw == 4)
        return 1;
    else
        return 0;
}


char *replace_chars(const char *array_char) {
    int array_size = strlen(array_char);
    char *new_array_char = (char*) malloc(sizeof(char) *array_size);
    for (int i = 0; i < array_size; i++) {
        if (draw_with_probality_005())
            new_array_char[i] = generate_random_char();
        else
            new_array_char[i] = array_char[i];
    }
    return new_array_char;
}


int string_points(char *array_char, const char *array_target) {
    int points = 0;
    for (int i = 0; array_target[i] != '\0'; i++) 
        if (array_char[i] == array_target[i])
            points ++;
    return points;
}


char *best_string_so_far(char **matrix_copies, const char *array_target) {
    int i = 0;
    int score_a;
    int score_b;
    char *best_string = matrix_copies[0];
    
    while (i < AMOUNT_COPIES) {
        score_a = string_points(matrix_copies[i], array_target);
        score_b = string_points(best_string, array_target);
        if (score_a > score_b) {
            best_string = matrix_copies[i];
        }
        i++;
    }
    return best_string;
}


int it_is_correct(int size_target, char *start_random_array, const char *array_target) {
    if(string_points(start_random_array, array_target) == size_target) 
        return 1;
    else
        return 0;
}