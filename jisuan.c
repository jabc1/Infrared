#include "stdio.h"
#define T	1000000//us
main()
{
	int temp = 0;
	float use_t = 0;
	printf("please input HZ?\r\n");
	scanf("%d",&temp);
	//printf("temp=%d",temp);
	use_t = (float)(T / (float)temp);
	printf("use_t=%fus\tT=%fus\r\n",use_t,use_t/2);
}







