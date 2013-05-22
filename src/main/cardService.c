#include <hspos.h>
//初始化CPU卡 0成功 1打开MIF失败  2读取卡失败  3复位卡失败 snData 返回卡序列号
int InitializeCard(char* snData) {
	int returnLen;
	char returnValueOfMifOpen = mif_open();
	if (returnValueOfMifOpen != MI_OK)
		return 1;
	char sn[10], returnBuffer[100];
	uchar returnValue = ISO14443A_findcard(0x26, &returnLen, sn);
	if (returnValue == 0) {
		putn_hex(returnLen, sn);
		returnValue = ISO14443A_ATS(&returnLen, returnBuffer);
		if (returnValue != 0) {
			return 3;
		}
	} else {
		return 2;
	}
	return 0;
}

//初始化PSAM卡 第一步
int InitailizePsamCard(int slot) {
	unsigned char returnBuffer[100];
	int slot2PowerOpen = slot;
	int openReturn = ICC_PowerOpen(slot2PowerOpen, 38400, 3, returnBuffer);
	return openReturn;
}
//读取PSAM卡编号 返回值9000 长度6字节 第二步  返回终端机编号
int ReadPsamNo(int slot, U8 *returnlen, char* returnBuffer) {
	unsigned char inputBuffer[100];
	char command[] = { 0x00, 0xB0, 0x96, 0x00, 0x06 };
	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, returnlen, returnBuffer);
	if (returnValueOfCommand == 0)
		return 0;
	return 1;
}

//PSAM卡选择文件 选择全国密钥管理总中心ADF  第三步  返回消费密钥索引
int SelectAdfSecretFile(int slot, U8 *returnlen, char* returnBuffer) {
	unsigned char inputBuffer[100];
	char command[] = { 0x00, 0xA4, 0x00, 0x00, 0x02, 0x10, 0x01 };
	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, returnlen, returnBuffer);
	if (returnValueOfCommand == 0)
		return 0;
	return 1;
}
//CPU 读取用户卡安全识别码 80CA000009，指令执行成功后获取9字节安全识别码【 返回9000 长度9】第四步
int ReadCpuCardInfo(char* cpuSecretCode) {
	U8 returnLen;
	unsigned char returnBuffer[9];
	char command[] = { 0x80, 0xCA, 0x0, 0x00, 0x09 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnLen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(cpuSecretCode, returnBuffer, 9);
		return 0;
	}
	return 1;
}

//CPU 选择用户卡ED/EP应用    返回发卡方标识、应用序列号等信息 指令执行成功后：第2字节开始2字节为城市代码，第12字节开始8字节为应用序列号【 返回9000 长度30】 第四步
int ReadCpuCardInfo(char* city, char* appSn) {
	U8 returnLen;
	unsigned char returnBuffer[30];
	char command[] = { 0x00, 0xB0, 0x95, 0x00, 0x1E };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnLen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(city, returnBuffer + 2, 2);
		memcpy(appSn, returnBuffer + 12, 8);
		return 0;
	}
	return 1;
}

//CPU 消费初始化  返回随机数、用户卡交易序号、密钥版本、算法标识 第四步
//805001020B+01(消费密钥索引)+00000001(交易金额，转换成16进制数)+000000010001(PSAM卡终端编号)+0F(要求返还的长度)，
//指令执行成功返回：4字节电子钱包余额+2字节电子钱包交易序号+3字节透支限额+1字节密钥版本号+1字节算法标识+4字节伪随机数
int ReadCpuCardInfo(char* secretIndex, char* moneyHex, char* psamNo, char *returnlenHex, char* balance, char* no, char* overdraft, char* secretVer,
		char* algorithmVer, char* random) {
	U8 returnlen;
	char returnBuffer[100];
	char command[17] = { 0x80, 0x50, 0x01, 0x02, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//写入消费密钥索引
	memcpy(command + 5, secretIndex, 1);
	//写入交易金额，转换成16进制数
	memcpy(command + 5 + 1, moneyHex, 4);
	//写入PSAM卡终端编号
	memcpy(command + 5 + 1 + 4, psamNo, 6);
	//写入要求返还的长度
	command[16] = returnlenHex[0];
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(balance, returnBuffer, 4);
		memcpy(no, returnBuffer + 4, 2);
		memcpy(overdraft, returnBuffer + 4 + 2, 3);
		memcpy(secretVer, returnBuffer + 4 + 2 + 3, 1);
		memcpy(secretVer, returnBuffer + 4 + 2 + 3 + 1, 1);
		memcpy(secretVer, returnBuffer + 4 + 2 + 3 + 1 + 1, 4);
		return 0;
	}
	return 1;
}
//PSAM MAC1计算  返回MAC1、终端脱机交易序号 第五步
/*PSAM卡消费初始化(计算MAC1):
 * 80,70,00,00,24+47800CF7(4字节伪随机数)
 +0006(2字节电子钱包交易序号)
 +00000001(4字节交易金额)
 +06(1字节交易类型)
 +20081009140759(7字节交易日期时间)
 +01(1字节密钥版本号)+00(1字节算法标识)
 +2144000000000001(8字节应用序列号)
 +2144(2字节城市代码)
 +FF0000000000(6字节固定值)，指令执行成功后返回4字节PSAM卡终端交易序号+4字节MAC1
 */
int CalcMac1InPsam(int slot, char* random, char* no, char* moneyHex, char* oderType, char* dateTime, char* secretVer, char* algorithmVer, char* appSn,
		char* city, char* psamOderSn, char* mac1) {
	U8 returnlen;
	char returnBuffer[100];
	char command[35] = { 0x80, 0x70, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//写入随机数
	memcpy(command + 5, random, 4);
	//写入CPU卡交易序号
	memcpy(command + 5 + 4, no, 2);
	//写入交易金额
	memcpy(command + 5 + 4 + 2, moneyHex, 4);
	//写入交易类型
	memcpy(command + 5 + 4 + 2 + 4, oderType, 1);
	//写入交易时间
	memcpy(command + 5 + 4 + 2 + 4 + 1, dateTime, 7);
	//写入密钥版本号
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7, secretVer, 1);
	//写入算法标识
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1, algorithmVer, 1);
	//写入算法标识
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1 + 1, appSn, 8);
	//写入城市标识
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1 + 1 + 8, city, 2);
	//写入6字节固定值
	char* staticCmd[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00 };
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1 + 1 + 8 + 2, staticCmd, 6);

	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0) {
		memcpy(psamOderSn, returnBuffer, 4);
		memcpy(mac1, returnBuffer + 4, 4);
		return 0;
	}
	return 1;
}
/*
 *   用户卡消费:第六步
 *   80，54，01，00，0F
 +00,00,00,29(4字节PSAM卡终端交易序号)
 +20081009140759(7字节交易日期时间)
 +E82AEB3B08(4字节MAC1)，指令执行成功返回：4字节TAC+4字节MAC2
 * */
int CpuCardConsumeCommand(char* psamOderSn, char* dateTime, char* mac1, char* tac, char* mac2) {
	U8 returnlen;
	char returnBuffer[100];
	char command[17] = { 0x80, 0x54, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//写入 4字节PSAM卡终端交易序号
	memcpy(command + 5, psamOderSn, 4);
	//写入7字节交易日期时间
	memcpy(command + 5 + 4, dateTime, 7);
	//写入4字节MAC1
	memcpy(command + 5 + 4 + 7, mac1, 4);

	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(tac, returnBuffer, 4);
		memcpy(mac2, returnBuffer + 4, 4);
		return 0;
	}
	return 1;
}
/*
 *   PSAM卡消费(验证MAC2):第七步
 8072000004+AE50FB88(4字节MAC2)【当前返回值6901 长度0字节】
 * */
int CalcMac2InPsam(int slot, char* mac2) {
	U8 returnlen;
	char returnBuffer[100];
	char command[35] = { 0x80, 0x72, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };
	//写入mac2
	memcpy(command + 5, mac2, 4);

	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0) {
		return 0;
	}
	return 1;
}

/*--------------------其它CPU方法------------------------*/
//读电子钱包余额：805C000204，返回4字节16进制数转化10进制
int ReadCpuBalanceCommand(char* balance) {
	U8 returnlen;
	char returnBuffer[4];
	char command[] = { 0x80, 0x5C, 0x00, 0x02, 0x04 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(balance, returnBuffer, 4);
		return 0;
	}
	return 1;
}

// 00b0950202 获取4？？？字节城市代码，【调通 返回2字节 3140】
int ReadCpuCityCommand(char* city) {
	U8 returnlen;
	char returnBuffer[2];
	char command[] = { 0x00, 0xb0, 0x95, 0x02, 0x02 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(city, returnBuffer, 2);
		return 0;
	}
	return 1;
}

// 00b0950C08 获取16字节应用序列号，4字节城市代码+16字节应用序列号组成20位非接触式流水号  【实际调通 返回两字节 8字节】
int ReadCpuCityCommand(char* appSn) {
	U8 returnlen;
	char returnBuffer[20];
	char command[] = { 0x00, 0xb0, 0x95, 0x0C, 0x08 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(appSn, returnBuffer, 8);
		return 0;
	}
	return 1;
}

// 读取姓名：00b0960214，20位姓名长度 【调通】
int ReadCpuCityCommand(char* name) {
	U8 returnlen;
	char returnBuffer[20];
	char command[] = { 0x00, 0xb0, 0x96, 0x02, 0x14 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(name, returnBuffer, 20);
		return 0;
	}
	return 1;
}

// 读取证件号码：00b0961620，32位证件号码 【调通】
int ReadCpuUserIdCardNumberCommand(char* userIdCardNumber) {
	U8 returnlen;
	char returnBuffer[32];
	char command[] = { 0x00, 0xb0, 0x96, 0x16, 0x20 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(userIdCardNumber, returnBuffer, 32);
		return 0;
	}
	return 1;
}

// 读取接触式卡号：00b0963809，9位接触式卡号
int ReadCpuCardIdCommand(char* cardId) {
	U8 returnlen;
	char returnBuffer[9];
	char command[] = { 0x00, 0xb0, 0x96, 0x38, 0x09 };
	unsigned short returnValueOfCommand = ISO14443A_APDU(sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0x9000) {
		memcpy(cardId, returnBuffer, 9);
		return 0;
	}
	return 1;
}
