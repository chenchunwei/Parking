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
	putstr("��ʼ�������Ժ�...");
	while (1) {
		cRet = WmodeOpen();
		if (cRet != 0) {

			//putstr("\nGPRSģ����  ");
			i++;
			if (i > 0)                    //��һ�δ�ʧ�ܣ��ر�ģ��
					{
				WmodeClose();
				//delay_5();
				if (i > 1)               //�ڶ��δ�ʧ�ܣ��˳�
						{
					return 1;
				}
			}
		} else {
			break;
		}

	}
	//putstr("\n���SIM�� ");
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
	//putstr("\n����ź�ǿ��    ");
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

		printf("\n  SIM ����");
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

	putstr("���Ժ�...");

	moveto(5, 1);
	//putst("�����Զ����ã����Ժ�...");

	moveto(7, 1);
	set_ip("111.1.31.40");
	//utn_h(15,119.130.17.212);

	//moveto(9,1);putstr("�˿ں�:");

	set_port("2999");
	//putn_h(6,port);

	//cRet=WNetSeting("2","5001",ip,port);
	//putstr("\nIP���� ");printf("%d",cRet);

	//cRet=WNetInit("512","1","6","6000");
	//putstr("\n��ʱ���� ");printf("%d",cRet);

	//cRet=WNetCont("1","IP","CMNET","0,0");
	//putstr("\n��������");printf("%d",cRet);

	//moveto(15,1);putstr("\n�������");
	//key(0);
	bell(100);

}
int set_ip(uchar *s) {
	return EEROM_write(0x40, 16, s);
}
int set_port(uchar *s) {
	return EEROM_write(0x30, 7, s);

}
