#include<stdio.h>
#include<cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <crypt.h>
#include<string.h>
void cipher(string key, int key_number);
int main(int argc, string argv[])
{
    int i,j,jin_wei= 0;;
    if(argc!=2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char *word=argv[1];
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
                char *s = crypt(test, "50");
                if(strcmp(s, word) == 0)
                {
                    for(int k=0; k<i; k++)
                    {
                        printf("%c", test[k]);
                    }
                }
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

    }
    return 0;

}

//  .jPgLzVirkc
