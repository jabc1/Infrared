#include "stdio.h"
#define T	1000000//us
main()
{
	int temp = 0,i;
	float use_t = 0;
	printf("please input HZ?\r\n");
	scanf("%d",&temp);
	//printf("temp=%d",temp);
	if(temp > 1000)
	{
		temp = temp / 1000;
	}
	use_t = (float)(T / (float)temp);
	printf("input HZ = %dKHz\r\n",temp);
	printf("use_t=%fus\tT=%fus\r\n",use_t,use_t/2);
	i = (int)(use_t/2);
	printf("htimx.Init.Prescaler=72-1\r\n");
	printf("htimx.Init.Prescaler=%d-1\r\n",i);
}






