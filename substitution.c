#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //argv will store the key
    int key_len, counter = 0, count1 = 0, count2 = 0;
    char num1, num2;

    if (argc == 2)
    {
        //store the key length in a variabkle
        key_len = strlen(argv[1]);
        if (key_len == 26)
        {
            while (counter < key_len + 1)
            {
                //if integer value of keys[1] is bigger than 64 and same smaller than 123
                ///this is done to ensure that the number values are between the start of the uppercase and end of lowercase
                while (counter < key_len)
                {
                    if (isalpha(argv[1][counter]))
                    {
                        counter++;
                    }
                    else if ((int)argv[1][counter] > 47 || (int)argv[1][counter] < 58)
                    {
                        printf("Key must only contain alphabetic characters.\n");
                        return 1;
                    }
                    else
                    {
                        printf("Key must only contain alphabetic characters.\n");
                        return 1;
                    }
                }
                //just a bunch of definitions, didnt use all of them but scared to ruin the code if i get rid of some XDDD
                int equal_counter = 0;
                counter = 0;
                count1 = 0;
                count2 = 1;
                int x_main = 0;
                string key = argv[1];
                while (counter < 26)
                {
                    if (equal_counter > 1)
                    {
                        printf("Key must not contain repeated characters. \n");
                        return 1;
                    }
                    else
                    {
                        //find the num and store it somewhere (x)
                        //do while the x != counter, when it does add 1 to count
                        if (key[count1] != key[count2])
                        {
                            x_main = count1;
                            if (key[x_main] == key[count2])
                            {
                                count2++;
                            }
                            else
                            {
                                count2++;
                            }
                        }
                        else if (key[count1] != toupper(key[count2]))
                        {
                            if (key[x_main] == toupper(key[count2]))
                            {
                                equal_counter = equal_counter + 2;
                            }
                            else
                            {
                                count2++;
                            }
                        }
                        else
                        {
                            //add a CAPS part that will check if its caps same letter here
                            equal_counter++;
                            count2++;
                        }
                    }
                    //if amt of times that equal bigger happend is more than 1 than its there are repeateed letters
                    if (equal_counter > 1)
                    {
                        printf("Key must not contain repeated characters. \n");
                        return 1;
                    }
                    if (count2 > 25)
                    {
                        count2 = 0;
                        count1 = count1 + 1;
                        counter++;
                        equal_counter = 0;
                    }
                }
                //if number of times that equal happened is less than or = 1, then we can keep going with our code
                if (equal_counter < 1)
                {
                    //usript = user-input
                    string usript = get_string("plaintext: ");
                    int usriptlen = strlen(usript);
                    count1 = 0;
                    count2 = 0;
                    int somevalue = 0;
                    int somevalue_u;
                    int somevalue_l;
                    int nomber = 0;
                    string nomber_s;
                    char user_input[usriptlen];
                    for (counter = 0; counter < 1; counter++)
                    {
                        while (count1 <= usriptlen)
                        {
                            //checks if its in the alphabet
                            if (isalpha(usript[count1]))
                            {
                                //if yes then we store a integer value of (count1) number of letter as an integer
                                somevalue = (int)usript[count1];
                                //if its uppercase
                                if (isupper(usript[count1]))
                                {
                                    //add 1 to somevalue_uPPER
                                    somevalue_u = 1;
                                }
                                else
                                {
                                    //if not uppercase addd 1 to somevalue_lOWER
                                    somevalue_l = 1;
                                }
                                //----------------------------------
                                if (somevalue_u == 1)
                                {
                                    //if its upper then we get rid of 65 as thats where cap A starts in ASCII
                                    somevalue = somevalue - 65;
                                    //now we use the somevalue number to understand which number it should be in out key and we make it upper and then place in array
                                    user_input[count1] = toupper(key[somevalue]);
                                    //add 1 to count
                                    count1++;
                                    //empty the some value for next round
                                    somevalue = 0;
                                    //empty the some value for next round
                                    somevalue_u = 0;
                                }
                                //the exactly same thing as on top of you
                                else if (somevalue_l == 1)
                                {
                                    somevalue = somevalue - 97;
                                    user_input[count1] = tolower(key[somevalue]);
                                    count1++;
                                    somevalue = 0;
                                    somevalue_l = 0;
                                }
                            }
                            else
                            {
                                user_input[count1] = usript[count1];
                                nomber = 0;
                                count1++;
                            }
                        }
                        if (count1 > usriptlen - 1)
                        {
                            printf("ciphertext: %s", user_input);
                            printf("\n");
                            return 0;
                        }
                    }
                }
            }
        }
        else
        {
            printf("Key must contain 26 characters. \n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }
}