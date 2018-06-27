#include "stdio.h"
unsigned char buff[7]={0x07,0x06,0x05,0x04,5,6,7};
typedef struct{
	unsigned int add;
	unsigned char type;
	unsigned char H;
	unsigned char L;
}_Test;

main()
{
	_Test * update;
	update = (_Test *)(&buff);

	printf("%d\n",update->add);
	printf("%d\n",update->type);
	printf("%d\n",update->H);
	printf("%d\n",update->L);
}
