#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int len_counter = 0, number_len, counter = 0, f_if_counter = 0;
    float digit1 = 0.0, digit2 = 0.0;
    int final_card_value;

    int x, y, counter1, even_num_list, odd_num_list, even_num, odd_num, total_num, a, b;
    long number, store_number_value;

    number = get_long("Number: ");

    //before we use the card number we need to create a back-up of it for further use
    store_number_value = number;

    while (number > 10)
    {
        //number will become number/10 which will get rid of 1 number
        number = number / 10;
        //counter increments after each go so we will end up with the length of the number stored in counter
        len_counter++;
    }
    //add a 1 beacause counter cant divide last number by 10 so will store 1 num less
    number_len = len_counter + 1;

    //using the back-up
    number = store_number_value;

    while (counter < 2)
    {
        //if number lenght is 13 OR 15 OR 16 we get into this if statement
        if (number_len == 13 || number_len == 15 || number_len == 16)
        {
            if (number_len == 13)
            {
                digit1 = (float)number / (float)1000000000000;
                digit1 = (int)digit1;
            }
            if (number_len == 15)
            {
                digit2 = (float)number / (float)10000000000000;
                digit2 = (int)digit2;
            }
            if (number_len == 16)
            {
                digit1 = (float)number / (float)1000000000000000;
                digit1 = (int)digit1;
                digit2 = (float)number / (float)100000000000000;
                digit2 = (int)digit2;
            }
        }
        //if number length isnt 13,15,16 than the card number is invalid and we finish the while loop
        else
        {
            printf("INVALID\n");
            //add 2 to counter so that the while loop stops
            counter = counter + 2;
            //add 1 to f_if_counter so that we dont get throught the second if process because card number is already wrong
            f_if_counter = f_if_counter + 1;
        }

        if (f_if_counter == 0)
        {
            //num_len AND first digit is 4 (same with others)
            if (number_len == 13 && digit1 == 4)
            {
                //add one to final card value because 1 will mean its VISA (same with others)
                final_card_value = final_card_value + 1;
                //add 2 to counter so that it ends the while loop (same with others)
                counter = counter + 2;
            }
            else if (number_len == 15 && (digit2 == 34 || digit2 == 37))
            {
                final_card_value = final_card_value + 2;
                counter = counter + 2;
            }
            else if (number_len == 16 && digit1 == 4)
            {
                final_card_value = final_card_value + 1;
                counter = counter + 2;
            }
            else if (number_len == 16 && (digit2 == 51 || digit2 == 52 || digit2 == 53 || digit2 == 54 || digit2 == 55))
            {
                final_card_value = final_card_value + 3;
                counter = counter + 2;
            }
            else
            {
                //if length is not 13,15,16 it will be invalid
                printf("INVALID\n");
                counter = counter + 2;
                f_if_counter = f_if_counter + 1;
            }
        }
        else
        {
            counter = counter + 2;
        }
    }
    //add 1 to counter1 so that it runs enough times
    counter1 = number_len + 1;
    while (counter1 > 0)
    {
        //if number is even there is its own code
        if (number_len % 2 == 0)
        {
            //the value in number is odd
            if (counter1 % 2 == 1)
            {
                // get last digit of number
                x = number % 10;
                //store it in even
                even_num = x;
                //add to total even
                even_num_list = even_num_list + even_num;
                // divide the number by 10 to get rid of 1 value in it
                number = number / 10;
                //decrement the counter
                counter1--;
            }
            else if (counter1 % 2 == 0)
            {
                y = number % 10;
                odd_num = y * 2;
                if (odd_num > 9)
                {
                    a = odd_num % 10;
                    b = odd_num / 10;
                    b = b % 10;
                    odd_num_list = odd_num_list + a;
                    odd_num_list = odd_num_list + b;

                    number = number / 10;
                    counter1--;
                }
                else
                {
                    odd_num_list = odd_num_list + odd_num;
                    number = number / 10;
                    counter1--;
                }
            }
        }
        else if (number_len % 2 == 1)
        {
            //even small number (we just add it )
            if (counter1 % 2 == 0)
            {
                x = number % 10;
                even_num = x;
                even_num_list = even_num_list + even_num;
                number = number / 10;
                counter1--;
            }
            else if (counter1 % 2 == 1)
            {
                y = number % 10;
                odd_num = y * 2;
                if (odd_num > 9)
                {
                    a = odd_num % 10;
                    b = odd_num / 10;
                    b = b % 10;
                    odd_num_list = odd_num_list + a;
                    odd_num_list = odd_num_list + b;
                    number = number / 10;
                    counter1--;
                }
                else
                {
                    odd_num_list = odd_num_list + odd_num;
                    number = number / 10;
                    counter1--;
                }
            }
        }
    }
    // add odd num and even num lists together for total which we % by 10 and if remainder is 0 the card is valid
    total_num = odd_num_list + even_num_list;
    if (total_num % 10 == 0)
    {
        if (final_card_value == 1)
        {
            printf("VISA\n");
        }
        else if (final_card_value == 2)
        {
            printf("AMEX\n");
        }
        else if (final_card_value == 3)
        {
            printf("MASTERCARD\n");
        }
    }
    else
    {
        if (f_if_counter == 0)
        {
            // if it said invalid once in the first if it shouldnt say it again so
            printf("INVALID\n");
        }
    }
}
