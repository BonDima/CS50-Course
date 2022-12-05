from cs50 import get_int
a = True
# while loop is needed for checking the value range, user will be promped again if number is out of range
while a:
    number = get_int("Height: ")  # get int gets rid off the typeError
    if number > 0 and number < 9:
        a = False


for i in range(number):
    for space_counter in range(number - (i + 1)):
        print(" ", end="")
    for hash_counter in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for hash_counter in range(i + 1):
        print("#", end="")
    print()
