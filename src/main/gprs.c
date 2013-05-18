#include <hspos.h>
#define MAX_TEST_NUM 1000

int set_ip(uchar *s);
int set_port(uchar *s);
int get_ip(uchar *s) {
	return EEROM_read(0x40, 16, s);
}
int get_port(uchar *s) {
	return EEROM_read(0x30, 7, s);
}
int GPRS_Link_init(void) {
	int cRet;
//   uchar ip[32];
//   uchar port[32];
	int i = 0;
	cls();
	putstr("初始化中请稍候...");
	while (1) {
		cRet = WmodeOpen();
		if (cRet != 0) {

			//putstr("\nGPRS模块检测  ");
			i++;
			if (i > 0)                    //第一次打开失败，关闭模块
					{
				WmodeClose();
				//delay_5();
				if (i > 1)               //第二次打开失败，退出
						{
					return 1;
				}
			}
		} else {
			break;
		}

	}
	//putstr("\n检测SIM卡 ");
	for (i = 0; i < 50; i++) {

		cRet = WmodeCheckSIM();
		if (cRet == 0) {

			//putstr("ok");
			break;
		} else {

			//delay(10);
		}
	}
	if (i == 5) {
		return 2;
	}

#if 0
	//putstr("\n检测信号强度    ");
	cRet=WmodeREGStatus(rbuf);
	cRet=WmodeCheckGPRSstatus(rbuf);
	cRet=WmodeCheckSignal(rbuf);
	//putstr(rbuf);
	if(cRet==0)
	{
		//putstr("ok");
	}
	else
	{
		//putstr("error");
		bell(50);
		return 2;
	}
#endif

	cRet = WSmsSendModle(0);
	if (cRet) {

		printf("\n  SIM 错误");
		bell(100);
		key(0);
		return 0;
	} else {
		//printf("\n SET SMS ok");
	}

	//key(0);

	return 0;
}
extern void GPRS_SET1(void) {
	//int cRet;
	//uchar ip[32];
	//uchar port[32];
	cls();

	putstr("请稍候...");

	moveto(5, 1);
	//putst("正在自动配置，请稍后...");

	moveto(7, 1);
	set_ip("111.1.31.40");
	//utn_h(15,119.130.17.212);

	//moveto(9,1);putstr("端口号:");

	set_port("2999");
	//putn_h(6,port);

	//cRet=WNetSeting("2","5001",ip,port);
	//putstr("\nIP设置 ");printf("%d",cRet);

	//cRet=WNetInit("512","1","6","6000");
	//putstr("\n超时设置 ");printf("%d",cRet);

	//cRet=WNetCont("1","IP","CMNET","0,0");
	//putstr("\n网络设置");printf("%d",cRet);

	//moveto(15,1);putstr("\n设置完成");
	//key(0);
	bell(100);

}
int set_ip(uchar *s) {
	return EEROM_write(0x40, 16, s);
}
int set_port(uchar *s) {
	return EEROM_write(0x30, 7, s);

}
