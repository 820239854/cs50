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
    // printf("%s", word);
    for(i=1; i<5; i++)
    {
        char test[i+1];
        test[i] ='\0';
//        initial
        for(int test_number=0; test_number<i;  test_number++)
        {
            test[test_number] = 'A';
        }


        while(1)
        {

            for(j=0; j<52; j++)
            {
                if(j>25)
                {
                    test[0] = 'a'+j-26;
                }
                else
                {
                    test[0] = 'A'+j;
                }

                // for(int k=0; k<i; k++)
                // {
                //     printf("%c", test[k]);
                // }
                // printf("\n");

                char *s = crypt(test, "50");
                if(strcmp(s, word) == 0)
                {
                    // printf("%s\n",s);
                    for(int k=0; k<i; k++)
                    {
                        printf("%c", test[k]);
                    }
                    printf("\n");
                    return 0;
                }
                // if(strcmp(test, word) == 0)
                // {
                //     printf("hi");
                //     for(int k=0; k<i; k++)
                //     {
                //         printf("%c", test[k]);
                //     }
                //     return 0;
                // }
            }

            test[0] = 'a'+j-26;
            jin_wei=0;
            for(; jin_wei<i-1; jin_wei++)
            {
                if(test[jin_wei]>'z')
                {
                    test[jin_wei]='A';
                    if(test[jin_wei+1] =='Z')
                    {
                        test[jin_wei+1] = 'a';
                    }
                    else
                    {
                        test[jin_wei+1]+=1;
                    }
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
