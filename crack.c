#include<stdio.h>
#include<cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <crypt.h>

void cipher(string key, int key_number);
int main(void)
{
    int i,j,k,jin_wei= 0;;
    // if(argc!=2)
    // {
    //     printf("Usage: ./crack hash\n");
    //     return 1;
    // }

    for(i=1; i<4; i++)
    {
        char test[i];

//        initial
        for(int test_number=0; test_number<i;  test_number++)
        {
            test[test_number] = 'a';
        }


        while(1)
        {
            jin_wei=0;
            for(j=0; j<26; j++)
            {
                test[0] = 'a'+j;
                for(k=0; k<i; k++)
                {
                    printf("%c", test[k]);

                }
                printf("\n");
            }

            test[0] = 'a'+j;

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
