#include<stdio.h>


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
        fprintf(stderr, "Counld'd write\n.");
        return 2;
    }

    // printf("%lu", sizeof(0xff));

    int to_seek=0;
    // while(to_seek != EOF)
    // printf("%lu\n", sizeof(0xff));
    // printf("%lu\n", sizeof(0xf));

    // for(int j=0; j<3000; j++)
    int num = 0;
    while(!feof(file))
    {
        fread(&to_seek,1,1,file);
        if(to_seek == 0xff)
        {
            printf("%x\n", to_seek);
            fread(&to_seek,1,1,file);
                if(to_seek == 0xd8)
                {
                    printf("%x\n", to_seek);
                    fread(&to_seek,1,1,file);
                        if( to_seek == 0xff)
                        {
                            printf("%x\n", to_seek);
                            fread(&to_seek,1,1,file);
                            if(to_seek >= 0xe0 &&  to_seek<= 0xef)
                            {
                               printf("%x\n", to_seek);
                               printf("%d", num);
                               break;
                            }
                        }
                }
        }
        num++;
    }
    fclose(file);
    fclose(output);
    return 0;
}
