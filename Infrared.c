void Infrared_time()//100us
{
	if(Num.time_1ms++ >= 9999)//1s
	{
		Num.time_1ms = 0;
	}
	if(Num.time_1ms % 1000 == 1)//100ms
	{
		Infrared.start_signal = 1;
		Infrared.flag_100ms =  1;
		Infrared.send_ok = 0;
		Infrared.data = 0xaa;
	}
	if(Infrared.flag_100ms == 1)//时间到发送数据
	{
		if(Infrared.start_signal == 1)
		{
			Infrared.start_signal = 2;
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//开启38k
		}
		if(Infrared.start_signal == 2)
		{
			Infrared.count1++;
			if(Infrared.count1 == 40)//发送4-5ms 38k后关闭
			{
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
			}
			if(Infrared.count1 == 50)//空闲1ms
			{
				Infrared.start_signal = 0;
				Infrared.count1 = 0;
				Infrared.send_ok = 1;//准备发送有效数据
			}
		}
		if(Infrared.send_ok == 1)
		{
			Infrared.send_ok = 0;
			Infrared.send_data = 1;
			Infrared.databit = (Infrared.data & 0x80) >> 7;
			Infrared.data <<= 1;
			Infrared.datacount++;
			if(Infrared.datacount > 8)//数据发送完成
			{
				Infrared.datacount = 0;
				Infrared.flag_100ms = 0;
				Infrared.send_data  = 0;
			}
		}
		if(Infrared.send_data == 1)//发送数据位
		{
			if(Infrared.databit==1)//发送2ms不发送1ms
			{
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//开启38k
				Infrared.databit = 2;
			}
			else if(Infrared.databit==0)//发送1ms不发送1ms
			{
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//开启38k
				Infrared.databit = 3;
			}
			if(Infrared.databit == 2)
			{
				Infrared.count2++;
				if(Infrared.count2 == 20)//停止
				{
					HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
				}
				if(Infrared.count2 == 30)//重新发送数据
				{
					Infrared.count2 = 0;
					Infrared.send_data = 0;
					Infrared.send_ok = 1;
				}
			}
			if(Infrared.databit == 3)
			{
				Infrared.count3++;
				if(Infrared.count3 == 10)//stop
				{
					HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
				}
				if(Infrared.count3 == 20)
				{
					Infrared.count3 = 0;
					Infrared.send_data = 0;
					Infrared.send_ok = 1;
				}
			}
		}	
	}	
}
