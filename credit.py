def main():
    # check whether the number is of valid input
    while True:
        try:
            number = int(input("Number: "))
            if number < 0:  # IF number is negative
                print("This is a negative number")
                continue
        except ValueError:  # if number != int
            print("This is not a number! Input a number")
            continue
        else:
            break

    temp_number = number   # create a value that stores number
    len_counter = 0   # have to define it before using

    # loop will divide the number x times by 10 depending on how big the number is and
    # add 1 to counter every time division succedes which will give us number length
    while number > 10:   # loop will run if the number is bigger than 10
        number = number / 10
        len_counter += 1
    number_length = len_counter + 1   # add 1 because last num cant be divided
    number = temp_number   # get the actual number back because we used it, and /10

    # check if the number length is valid, if yes take get the first 1/2 numbers to check later
    if number_length == 13 or number_length == 15 or number_length == 16:
        if number_length == 13:
            digit1 = number / 1000000000000
            digit1 = int(digit1)
        if number_length == 15:
            digit2 = number / 10000000000000
            digit2 = int(digit2)
        if number_length == 16:
            digit1 = number / 1000000000000000
            digit1 = int(digit1)
            digit2 = number / 100000000000000
            digit2 = int(digit2)
    else:
        print("INVALID")
        return 0

    # create bool variabkles to save which card it is
    Visa = False
    MasterCard = False
    AmericanExpress = False
    # check each possibility 1 by 1, if true then assign true to card variable
    if (number_length == 13) and (digit1 == 4):
        Visa = True
    elif (number_length == 15) and (digit2 == 34 or digit2 == 37):
        AmericanExpress = True
    elif (number_length == 16) and (digit1 == 4):
        Visa = True
    elif (number_length == 16) and (digit2 == 51 or digit2 == 52 or digit2 == 53 or digit2 == 54 or digit2 == 55):
        MasterCard = True
    else:
        print("INVALID")
        return 0

    evensum = 0
    oddsum = 0
    # Luhns algorithm
    counter = number_length + 1

    while counter > 0:
        if number_length % 2 == 0:
            if counter % 2 == 1:
                last_digit = number % 10
                last_digit = int(last_digit)
                oddsum = oddsum + last_digit
                number = number / 10
                counter = counter - 1
            elif counter % 2 == 0:
                last_digit = number % 10
                last_digit = int(last_digit)
                last_num = last_digit * 2
                if last_num > 9:
                    value1 = last_num % 10
                    value1 = int(value1)

                    value2 = last_num / 10
                    value2 = value2 % 10
                    value2 = int(value2)

                    oddsum = oddsum + value1
                    oddsum = oddsum + value2

                    number = number / 10
                    counter = counter - 1
                else:
                    oddsum = oddsum + last_num
                    number = number / 10
                    counter = counter - 1

        elif number_length % 2 == 1:
            if counter % 2 == 0:
                last_digit = number % 10
                last_digit = int(last_digit)
                oddsum = oddsum + last_digit
                number = number / 10
                counter = counter - 1
            elif counter % 2 == 1:
                last_digit = number % 10
                last_digit = int(last_digit)
                last_num = last_digit * 2
                if last_num > 9:
                    value1 = last_num % 10
                    value1 = int(value1)

                    value2 = last_num / 10
                    value2 = value2 % 10
                    value2 = int(value2)

                    evensum = evensum + value1
                    evensum = evensum + value2

                    number = number / 10
                    counter = counter - 1
                else:
                    evensum = evensum + last_num
                    number = number / 10
                    counter = counter - 1

    totalsum = oddsum + evensum
    if totalsum % 10 == 0:
        if Visa == True:
            print("VISA")
        elif MasterCard == True:
            print("MASTERCARD")
        elif AmericanExpress == True:
            print("AMEX")
    else:
        print("INVALID")


main()