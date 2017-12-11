#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    if(argc !=2)
    {
        fprintf(stderr, "Only accept one commend\n");
        return 2;
    }

    FILE *file = fopen(argv[1],"r");
    if(file==NULL)
    {
        fprintf(stderr, "Counld'd open %s.\n", argv[1]);
        return 2;
    }

    FILE *output = fopen("test.jpg", "w");
    if(output==NULL)
    {
        fclose(file);
        fprintf(stderr, "Counld'd write\n.");
        return 2;
    }

    // printf("%lu", sizeof(char));
    int change = 0;
    while(!feof(file))
    // for(int k=0; k<200; k++)
    {
        char* content = (char*)malloc(512);

        fread(content, 512, 1 ,file);

        if( (int)content[0] == 0xff)
        {
            if( (int)content[1] == 0xd8)
            {
                if( (int)content[2] == 0xff)
                {
                    if( (int)content[3] >= 0xe0 && (int)content[3]<= 0xef)
                    {
                        // for(int wa=0; wa<4; wa++)
                        // {
                        //     fwrite( content+wa ,sizeof(char) ,1,output);
                        // }
                        for(int j=0; j<512; j++)
                        {
                            for(int num=0; num<16; num++)
                            {
                                printf("%x", content[j]);
                            }
                            printf("\n");
                        }
                        if(change == 0)
                            change = 1;
                        else
                            break;
                    }
                }
            }
        }
        if(change == 1)
            fwrite(content, 512, 1 , output);
        // for(int j=0; j<512; j++)
        // {
        //     for(int num=0; num<16; num++)
        //     {
        //         printf("%x", content[j]);
        //     }
        //     printf("\n");
        // }
        // free(content);
        // printf("------------------------ %d ------------\n", k);
    }
    fclose(file);
    fclose(output);
    return 0;
}
