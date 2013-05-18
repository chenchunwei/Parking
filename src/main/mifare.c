#include <hspos.h>

//֧���ɹ�
char PaymentSuccess = 0;
//֧��ʧ��
char PaymentFailed = 1;

int testMain(void) {
	unsigned char rbuf[32], rt;
	long kt;
	cls();
	putstr("MIFARE  test");
	//�򿪲���ʼ��������Ӧģ��
	rt = mif_open();
	if (rt != MI_OK) {
		putstr("\n initialize error");
		key(0);
		return 0;
	}
	for (;;) {
		cls();
		putstr("MIFARE  test");
		rt = testrc531();
		kt = 1000000;
		while (kt--);
		if (rt == 1) {
			if (key(0) == KEY_CLS) {
				//�رն�����Ӧģ��
				mif_close();
				return 0;
			}
		}
	}
	return 0;
}

char payment(float money) {
	unsigned char state, data[20], i, cardType[3];
	unsigned char rtbuf[30], k = 0;
	unsigned char keya[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff };

	cls();
	putstr("MIFARE ����");
	putstr("\n CLS exit");

	//��  �ܣ�Ѱ������
	state = mif_request(0, cardType);
	if (state != MI_OK) {
		state = mif_request(0, cardType);
		if (state != MI_OK) {
			putstr("\n request error ");
			putchhex(state);
			return PaymentFailed;
		}
	}
	putstr("\n request OK ");
	//���ؿ����к�
	memset(state, 0x00, sizeof (state) );
	state = mif_anticoll(0, data);
	if (state != MI_OK) {
		putstr("\n ���ؿ����к� Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n ���ؿ����к� OK");
	//�Ӷ������ѡȡһ���������кŵĿ�
	memset(state, 0x00, sizeof (state) );
	state = mif_select(data);
	if (state != MI_OK) {
		putstr("\n �Ӷ������ѡȡһ���������кŵĿ� Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n ѡ����ȷ OK");

	//������װ���дģ��RAM��
	memset(state, 0x00, sizeof (state) );
	state = mif_load_key(keya);
	if (state != MI_OK) {
		putstr("\n ����������� Error");
		putchhex(state);
		return PaymentFailed;
	}
	/*��  �ܣ���֤ĳһ��������
	��ڲ�����auth_mode��������֤ģʽ
	Sector��Ҫ��֤����������ţ�0��15��*/
	memset(state, 0x00, sizeof (state) );
	state = mif_authentication(1, 3, data);
	if (state != MI_OK)
	{
		putstr(" \n authentication Error:");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n authentication OK");
	for (i = 0; i < 16; i++) {
		rtbuf[i] = i + 0x30;
	}
    /*��������Ч�����������м�4�������� 8λ
	/*��  �ܣ�����д������
	 ����M1����һ�α���дһ���飬Ϊ16���ֽڣ�
	 ��ڲ�����blockaddr��M1�������ַ��1��63��
	 W_Data��Ҫд�������*/
	memset(state, 0x00, sizeof (state) );
	state = mif_write(12, rtbuf);
	if (state != MI_OK) {
		putstr("\n write Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n write OK");

	/*��  �ܣ���ȡ��������
	 ����M1����һ�ζ�һ��������ݣ�Ϊ16���ֽڣ�
	 ��ڲ�����blockaddr��M1�����ַ��0��63����
	 ���ڲ�����_Data����������
	 ��  �أ��ɹ��򷵻�0 */
	memset(state, 0x00, sizeof (state) );
	state = mif_read(12, data);
	if (state == MI_OK) {
		for (i = 0; i < 16; i++) {
			if (rtbuf[i] != data[i]) {
				putstr("\n read 4 block  Error");
				putchhex(state);
				return 1;
			}
		}
	} else {
		putstr("\n read 4 block  Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n �������");

	return PaymentSuccess;
}

/*
 * �洢������1024��8λ�ֳ�����1KB����
�洢���ʣ�EEPROM
��Ϊ16������������0 ~15��
ÿ��������4���飨Block����0����1����2�Ϳ�3��
ÿ������16���ֽڡ�
һ���������� 16 Byte��4 = 64 Byte
 *
 * 1�����̿�
��ַ������0��0
���ݣ�IC�����̱�־�����У���0~4���ֽ�Ϊ�����к�SN����5���ֽ�Ϊ���кŵ�У���룻��6���ֽ�Ϊ�������ֽڡ�SIZE�� ����7��8���ֽ�Ϊ�����ͺ�Tagtype��
���ԣ����ڱ����Ժ�ϵͳ�İ�ȫ�ԣ���һ����IC�����̱��֮����Ϊд��������˸ÿ鲻���ٸ���ΪӦ�����ݿ顣
����420A7E00368804004481740630373937H
       ���к�SN��420A7E00H+У����36H
       �����ֽ�SIZE��88H
       �����ͺ�Tag Type��0400H

       2�����ݿ�
ÿ����3�����ݿ飨����0ֻ��2������ÿ��16�ֽڡ�������β���еĴ�ȡ����λ��access bits������Ϊ��
��д�飺����һ������ݱ��棬���ö�/д����ֱ�Ӷ�/д������
ֵ�飺������ֵ�飬���Խ��г�ʼ��ֵ����ֵ����ֵ����ֵ�����㣬��Ӧ���õ�����ΪINC/DEC/RESTORE/TRANSFER���
ͨ�����ݿ��е����ݶ�����Ҫ���ܵ����ݣ�����Щ���ݵĶ�/д/��ֵ/��ֵ���裺���ϸÿ��ȡ������Ҫ��+ͨ����������������֤��
 3����β��
ÿ�������Ŀ�3Ϊ��β��Sector Trailer���飺
  KEY A��6B��+ Access bits��4B��+KEY B��6B��
  ���� A0A1A2A3A4A5FF078069 B0B1B2B3B4B5
  ��ԿA��A0A1A2A3A4A5H��ȱʡֵ��
  ��ԿB��B0B1B2B3B4B5H��ȱʡֵ��
  ��ȡ����λ��FF078069H ��ȱʡֵ��
Mifare 1 ����ȡ�������������Ĺ�ϵ
Access bits����ȡ����λ���������������4����ķ������������������ݿ�����ͣ���д��ֵ��
Mifare 1 ��������ʼ��ʱ������������3�ĳ�ʼ��ֵ��Ϊ
     A0A1A2A3A4A5 FF078069 B0B1B2B3B4B5
  ����ʼ����Ĵ�ȡ��������Ϊ��
   ����A�����ɶ���У������A������B��ȷ������޸ģ�
   ����B��У������A������B��ȷ��ɶ������޸ģ�
   ���ݿ���У������A������B��ȷ��ɶ������޸ġ�

   EEPROM�洢���ṹ�ṩ��Ӧ�ã�
  1K�ֽ�EEPROM��16������, 4���ݿ�/������16�ֽ�/�顣�û����Զ���ÿһ���洢����ķ���������ÿ������(ÿӦ��)ӵ�и��Զ�������Կ,֧�ִ���Կ��εĶ�Ӧ�á�
*/
