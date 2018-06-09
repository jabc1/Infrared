void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint16_t temp;
	uint8_t  Tim=0,Ok=0,Data,Num=0,result;
	if(GPIO_Pin==GPIO_PIN_15)
	{
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15))
			{
				 Tim=re_hw();//获得此次高电平时间
				 printf("Tim=%d\r\n",Tim);
				 if(Tim>=65) break;//不是有用的信号
				 if(Tim>=30 && Tim<55)//4ms-5ms  39
				 {
					Ok=1;//收到起始信号
				 }
				 else if(Tim >= 15 && Tim<29)//1.2ms - 1.8ms  19-25
				 {
					Data=1;//收到数据 1
				 }
				 else if(Tim>=5 && Tim < 15)//200us - 1ms  9-13
				 {
					Data=0;//收到数据 0
				 }

				 if(Ok==1)
				 {
					result<<=1;
					result+=Data;
					if(Num>=8)
					{
						Num = 0;
						printf("result=0x%04x\r\n",result);
						break;
					}
				 }
				 Num++;
			}
		}
	}
}
uint16_t re_hw()
{
	uint16_t temp=0;
	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15))
	{
		temp++;
		delay_us1(100);
		if(temp >= 65)
			return temp;
	}
	return temp;
}
void delay_us(uint32_t nus)
{
 uint32_t temp;
 SysTick->LOAD = 9*nus;
 SysTick->VAL=0X00;//清空计数器
 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
 do
 {
  temp=SysTick->CTRL;//读取当前倒计数值
 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
     SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}

