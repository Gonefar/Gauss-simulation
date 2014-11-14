#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI    3.1415926
#define CUT   3
#define PRCS  0.01
#define NUM   1000000


double gauss_pdf(double x)
{
    return ( 1 / sqrt(2*PI) * exp(-x * x / 2) );
}

int init(int * sample_sect, double *pdf_sample)
{
    int i;
    int sum = 0;
    double p = 0.0;
    
    for(i = 0; i < (2 * CUT / PRCS + 1); i++)
    {
        pdf_sample[i] = gauss_pdf((double)i * PRCS - CUT);
        p += pdf_sample[i] * PRCS;
        sum += (int)(pdf_sample[i] / pdf_sample[0]);
        sample_sect[i] = sum;
        //printf("pdf value:%f, total sum:%d total probablity:%8f\n", pdf_sample[i], sum, p);
    }
    //printf("Probablity:%10f\n", p);
    return sum;
}

int find_element_section(int element, int *sample_sect, int sect_len)
{
    int i;
    for(i = 0; i < sect_len - 1; i++)
    {
        if(element == 0)
        {
            return 0;
        }
        
        if(element >= sample_sect[i] && element < sample_sect[i+1])
        {
            return i;
        }
    }

    
        
    printf("error ! the element %d is not int the section !\n", element);
    return -1;
}

int gauss(int *sample_sect, int sum)
{
    int test_num, flag, random_num, i;
    int err_sum = 0;
    int *counter = malloc(sizeof(int) * (2 * CUT / PRCS + 1));

    memset( counter, 0, sizeof(int) * (2 * CUT / PRCS + 1) );
    test_num = NUM;
    srand((int)time(0));
    
    while(test_num != 0)
    {        
        random_num = rand() % sum;
        flag = find_element_section(random_num, sample_sect, (2 * CUT / PRCS + 1));
        //printf("%d %d\n", flag, random_num);
        if( (flag * PRCS - CUT) <= -1 )
        {
            err_sum++;
        }
        
        for(i = 0; i < (2 * CUT / PRCS + 1); i++)
        {
            if(flag == i)
            {
                counter[flag]++;
            }
        }

        test_num--;
    }

    printf("receive error probablity:%8f\n", (double)err_sum/NUM);
    for(i = 0; i < (2 * CUT / PRCS + 1); i++)
    {
        //printf("%4f %10f\n", i * PRCS - 3, (double)counter[i]/NUM);
    }

    return 0;
    
}

int main()
{
    int sum = 0;
    int *sample_sect = malloc(sizeof(int) * (2 * CUT / PRCS + 1));
    double *pdf_sample = malloc(sizeof(double) * (2 * CUT / PRCS + 1));

    
    sum = init(sample_sect, pdf_sample);
    gauss(sample_sect, sum);
    

}

