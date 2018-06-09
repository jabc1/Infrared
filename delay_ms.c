//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
  u32 temp;		   
  SysTick->LOAD=(u32)nms*9;				//时间加载(SysTick->LOAD为24bit)
  SysTick->VAL =0x00;							//清空计数器
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
  do
  {
    temp=SysTick->CTRL;
  }while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
  SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
  SysTick->VAL =0X00;       					//清空计数器	  	    
} 
