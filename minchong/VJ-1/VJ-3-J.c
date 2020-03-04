#include<stdio.h>
#include<algorithm>
int sum1[16000001],sum2[16000001]
int main()
{
    int m,n,num1[4010],num2[4010],num3[4010],num4[4010],i,q=0;
    int min,max,mid,ans=0,add,h;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    scanf("%d %d %d %d",&num1[i],&num2[i],&num3[i],&num4[i]); 
    for(m=0;m<n;m++)
    for(i=0;i<n;i++)
    {
        sum1[q]=num1[m]+num2[i];
        sum2[q]=num3[m]+num4[i];
        q++;
    }
    std::sort(sum2,sum2+q);
    for(i=0;i<q;i++)
    {
        min=0,max=q-1;
        while(min<=max)
        {
            mid=(min+max)/2;
            add=sum1[i]+sum2[mid];
            if(add==0)
            {
                ans++;
                for(h=mid+1;h<q;h++)
                {
                if(sum1[i]+sum2[h]!=0)
                break;
                else
                ans++;
                }
                for(h=mid-1;h>=0;h--)
                {
                    if(sum1[i]+sum2[h]!=0)
                    break;
                    else
                    ans++;
                }
                break;
            }
            if(add<0)
            min=mid+1;
            else
            max=mid-1;
        }
    }
    printf("%d\n",ans);
}
