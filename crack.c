#include<stdio.h>
#include<cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <crypt.h>

void cipher(string key, int key_number);
int main(void)
{
    int i,j,jin_wei,o= 0;;
    // if(argc!=2)
    // {
    //     printf("Usage: ./crack hash\n");
    //     return 1;
    // }
    string word="rfid";

    for(i=1; i<5; i++)
    {
        char test[i];

//        initial
        for(int test_number=0; test_number<i;  test_number++)
        {
            test[test_number] = 'a';
        }


        while(1)
        {

            for(j=0; j<26; j++)
            {
                test[0] = 'a'+j;
                o = 0;
                while(o<i)
                {
                    if(test[o] != word[o])
                    {
                        break;
                    }
                    o++;
                }
                if(o == i && word[o]=='\0')
                    printf("%s", test);
            }

            test[0] = 'a'+j;
            jin_wei=0;
            for(; jin_wei<i-1; jin_wei++)
            {
                if(test[jin_wei]>'z')
                {
                    test[jin_wei]='a';
                    test[jin_wei+1]+=1;
                }
            }
            if(test[i-1]>'z')
            {
                break;
            }


        }

        printf("i=%d\n", i);
    }
    return 0;

}

//  .jPgLzVirkc
