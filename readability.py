def count_letters(text, length):
    count = 0
    counter = 0
    while counter < length:
        # checks if the character is in the alphabet -> so a letter
        if text[counter].isalpha():
            count += 1
            counter += 1
        else:
            counter += 1
    return count


def count_words(text, length):
    count = 0
    counter = 0
    while counter < length:
        # check if the character is a space
        if text[counter].isspace():
            count += 1
            counter += 1
        else:
            counter += 1
    return count


def count_sentences(text, length):
    count = 0
    counter = 0
    while counter < length:
        # check if the character is either . or ! or ?
        # ord() -> converts the character to an ascii value so im able to check
        # whether it is a . ! ? from an ascii table
        if ord(text[counter]) == 46 or ord(text[counter]) == 33 or ord(text[counter]) == 63:
            count += 1
            counter += 1
        else:
            counter += 1
    return count


def main():
    text = input("Text: ")
    length = len(text)
    # call the functions and store their outputs
    answer_letters = count_letters(text, length)
    answer_words = count_words(text, length)
    answer_words += 1
    answer_sentences = count_sentences(text, length)
    L = answer_letters / answer_words * 100
    S = answer_sentences / answer_words * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8
    # round the index to the nearest number
    index = round(index)

    if index < 1:
        print("Before Grade 1")
    elif index == 16 or index > 16:
        print("Grade 16+")
    else:
        print(f"Grade: {index}")


main()