"""weasel program"""


from random import randint


def draw_accepted_char():
    """ Draw an allowed character """
    char_asc = randint(64, 90)
    if (char_asc >= 65) and (char_asc <= 90):
        return chr(char_asc)
    else:
        return " "


def random_string(size):
    """ Retruns a random string
        of accpeted characters
    """
    string = [0]*size
    i = 0
    while i < size:
        string[i] = draw_accepted_char()
        i += 1

    return ''.join(string)


def matrix_string_copies(string, number_of_copies):
    """ Returns a matrix of copies of a string"""
    i = 0
    string_copies = [0]*number_of_copies
    while i < number_of_copies:
        string_copies[i] = string
        i += 1

    return string_copies


def draw_with_probality_005():
    """ Make a draw with 5% of win"""
    draw = randint(1, 20)
    if draw == 4:
        return True
    else:
        return False


def replace_characters(string):
    """ Use another string to "replace" characters
        Place the characters on another string
        There is 5% of chance to replace
        Only accepted characters can be draw
    """
    new_string = [0]*len(string)
    i = 0
    while i < len(string):
        if draw_with_probality_005():
            new_string[i] = draw_accepted_char()
        else:
            new_string[i] = string[i]
        i += 1

    return ''.join(new_string)


def string_points(string, target):
    """ Returns the string score"""
    points = 0
    i = 0
    while i < len(string):
        if string[i] == target[i]:
            points += 1
        i += 1

    return points


def best_string_so_far(string_copies, target):
    """ Returns the best string per generation"""
    best_string = string_copies[0]
    i = 1
    while i < len(string_copies):
        if (string_points(string_copies[i], target) >
                string_points(best_string, target)):
            best_string = string_copies[i]
        i += 1

    return best_string


def it_is_correct(perfect_score, string, target):
    """ Check if the string is equal to target"""
    if string_points(string, target) == perfect_score:
        return True
    else:
        return False

TARGET = "METHINKS IT IS LIKE A WEASEL"
COPIES = 100

start = random_string(len(TARGET))
generation = 0
copies = matrix_string_copies(start, COPIES)

if it_is_correct(len(TARGET), start, TARGET) is False:

    score = 0
    best_generation_string = copies[0]

    while (score < len(TARGET) and generation < 500):
        copies = matrix_string_copies(best_generation_string, COPIES)
        new_strings = [0]*COPIES
        generation += 1
        j = 0

        while j < len(copies):
            new_strings[j] = replace_characters(copies[j])
            j += 1

        best_generation_string = best_string_so_far(new_strings, TARGET)
        score = string_points(best_generation_string, TARGET)
        print(generation, ":", best_generation_string, "-- score:", score)

# If the first string equals TARGET
else:
    print("Today I will make a mega-sena game!!!")
    print("0:", TARGET, "-- score:", len(TARGET))