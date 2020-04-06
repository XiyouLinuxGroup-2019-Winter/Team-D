#include<stdio.h>
#define months 12
#define years 5
int main()
{
    const float rain[years][months]=
    {
        {4.3,4.3,4.3,3.0,2.0,1.2,0.2,0.2,0.4,2.4,3.5,6.6},
        {8.5,8.2,1.2,1.6,2.4,0.0,5.2,0.9,0.3,0.9,1.4,7.3},
        {9.1,8.5,6.7,4.3,2.1,0.8,0.2,0.2,1.1,2.3,6.1,8.4},
        {7.2,9.9,8.4,3.3,1.2,0.8,0.4,0.0,0.6,1.7,4.3,6.2},
        {7.6,5.6,3.8,2.8,3.8,0.2,0.0,0.0,0.0,1.3,2.6,5.2}
    };
    const float (*p1)[12]=rain;
    int y,m;
    float s,t;
    printf(" year   rainfall  (inches) \n");
    for(y=0,t=0;y<years;y++)
    {
        for(m=0,s=0;m<months;m++)
        s+=*(*(p1+y)+m);
        printf("%5d  %15.1f\n",2010+y,s);
        t+=s;
    }
    printf("\nThe yearly average is %.1f inches.\n",t/years);
    printf("MONTHLY   averages :\n");
    printf("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec\n");
    for(m=0;m<months;m++)
    {
        for(y=0,s=0;y<years;y++)
        s+=*(*(p1+y)+m);
        printf("%4.1f ",s/years);
    }
    return 0;
}
