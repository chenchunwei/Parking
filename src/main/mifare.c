#include <hspos.h>

//支付成功
char PaymentSuccess = 0;
//支付失败
char PaymentFailed = 1;

int testMain(void) {
	unsigned char rbuf[32], rt;
	long kt;
	cls();
	putstr("MIFARE  test");
	//打开并初始化读卡感应模块
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
				//关闭读卡感应模块
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
	putstr("MIFARE 测试");
	putstr("\n CLS exit");

	//功  能：寻卡请求
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
	//返回卡序列号
	memset(state, 0x00, sizeof (state) );
	state = mif_anticoll(0, data);
	if (state != MI_OK) {
		putstr("\n 返回卡序列号 Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n 返回卡序列号 OK");
	//从多个卡中选取一个给定序列号的卡
	memset(state, 0x00, sizeof (state) );
	state = mif_select(data);
	if (state != MI_OK) {
		putstr("\n 从多个卡中选取一个给定序列号的卡 Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n 选择卡正确 OK");

	//将密码装入读写模块RAM中
	memset(state, 0x00, sizeof (state) );
	state = mif_load_key(keya);
	if (state != MI_OK) {
		putstr("\n 加载密码出错 Error");
		putchhex(state);
		return PaymentFailed;
	}
	/*功  能：验证某一扇区密码
	入口参数：auth_mode：密码验证模式
	Sector：要验证密码的扇区号（0～15）*/
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
    /*真正的有效数据区域是中间4个字世节 8位
	/*功  能：向卡中写入数据
	 对于M1卡，一次必须写一个块，为16个字节；
	 入口参数：blockaddr：M1卡棗块地址（1～63）
	 W_Data：要写入的数据*/
	memset(state, 0x00, sizeof (state) );
	state = mif_write(12, rtbuf);
	if (state != MI_OK) {
		putstr("\n write Error");
		putchhex(state);
		return PaymentFailed;
	}
	putstr("\n write OK");

	/*功  能：读取卡中数据
	 对于M1卡，一次读一个块的数据，为16个字节；
	 入口参数：blockaddr：M1卡块地址（0～63）；
	 出口参数：_Data：读出数据
	 返  回：成功则返回0 */
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
	putstr("\n 测试完成");

	return PaymentSuccess;
}

/*
 * 存储容量：1024×8位字长（即1KB），
存储介质：EEPROM
分为16个扇区（扇区0 ~15）
每个扇区有4个块（Block）块0、块1、块2和块3。
每个块有16个字节。
一个扇区共有 16 Byte×4 = 64 Byte
 *
 * 1）厂商块
地址：扇区0块0
内容：IC卡厂商标志。其中：第0~4个字节为卡序列号SN，第5个字节为序列号的校验码；第6个字节为卡容量字节“SIZE” ；第7，8个字节为卡类型号Tagtype；
特性：基于保密性和系统的安全性，这一块在IC卡厂商编程之后被置为写保护，因此该块不能再复用为应用数据块。
例：420A7E00368804004481740630373937H
       序列号SN：420A7E00H+校验码36H
       容量字节SIZE：88H
       卡类型号Tag Type：0400H

       2）数据块
每扇区3个数据块（扇区0只有2个），每块16字节。可由区尾块中的存取控制位（access bits）配置为：
读写块：用作一般的数据保存，可用读/写命令直接读/写整个块
值块：用作数值块，可以进行初始化值、加值、减值、读值的运算，相应配用的命令为INC/DEC/RESTORE/TRANSFER命令。
通常数据块中的数据都是需要保密的数据，对这些数据的读/写/加值/减值均需：符合该块存取条件的要求+通过该扇区的密码认证。
 3）区尾块
每个扇区的块3为区尾（Sector Trailer）块：
  KEY A（6B）+ Access bits（4B）+KEY B（6B）
  例： A0A1A2A3A4A5FF078069 B0B1B2B3B4B5
  密钥A：A0A1A2A3A4A5H（缺省值）
  密钥B：B0B1B2B3B4B5H（缺省值）
  存取控制位：FF078069H （缺省值）
Mifare 1 卡存取控制与数据区的关系
Access bits（存取控制位）：定义该扇区中4个块的访问条件，及定义数据块的类型（读写或值）
Mifare 1 卡出厂初始化时，所有扇区块3的初始化值均为
     A0A1A2A3A4A5 FF078069 B0B1B2B3B4B5
  卡初始化后的存取控制条件为：
   密码A永不可读，校验密码A或密码B正确后可以修改；
   密码B在校验密码A或密码B正确后可读，可修改；
   数据块在校验密码A或密码B正确后可读，可修改。

   EEPROM存储器结构提供多应用：
  1K字节EEPROM，16个扇区, 4数据块/扇区，16字节/块。用户可以定义每一个存储器块的访问条件。每个扇区(每应用)拥有各自独立的密钥,支持带密钥层次的多应用。
*/
