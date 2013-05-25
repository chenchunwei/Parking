#include<hspos.h>
#define SUCCESS	0
int Payment(int slot, char* plateNumber, int money) {

	int returnState = InitailizeAppOfCPU();
	if (returnState != 0)
		return 1; //连接公共钱包应用失败

	char psamNo[6];
	returnState = ReadPsamNo(slot, psamNo);
	if (returnState != 0)
		return 2; //读取PSAM卡no失败

	char selectAdfFileReturn[40];
	returnState = SelectAdfSecretFromPsam(slot, selectAdfFileReturn);
	if (returnState != 0)
		return 3; //读取SelectAdfSecretFromPsam失败

	char secretIndex[1];
	returnState = SelectSecretIndexFromPsam(slot, &secretIndex);
	if (returnState != 0)
		return 4; //读取SelectSecretIndexFromPsam失败

	char city[2];
	char appSn[8];
	returnState = ReadCardInfoOfCPU(city, appSn);
	if (returnState != 0)
		return 5; //读取ReadCardInfoOfCPU失败

	char cpuSecretCode[9];
	returnState = ReadSecretCodeOfCPU(cpuSecretCode);
	if (returnState != 0)
		return 6; //读取ReadSecretCodeOfCPU失败

	returnState = ConfirmSecretCodeOfPSAM(slot, cpuSecretCode);
	if (returnState != 0)
		return 7; //读取ConfirmSecretCodeOfPSAM失败

	/*用户卡普通消费初始化:805001020B+01(消费密钥索引)+00000001(交易金额，转换成16进制数)+000000010001(PSAM卡终端编号)+0F(要求返还的长度)，
	 指令执行成功返回：4字节电子钱包余额+2字节电子钱包交易序号+3字节透支限额+1字节密钥版本号+1字节算法标识+4字节伪随机数*/
	char fee[] = { 0x00, 0x00, 0x00, 0x00 };
	Int32ToHex(money, fee);

	char balance[4];
	char returnNo[2];
	char returnOverdraft[3];
	char returnSecretVer[1];
	char returnAlgorithmVer[1];
	char returnRandom[4];
	returnState = InitialConsumeOfCPU(secretIndex[0], fee, psamNo, 0x0f, balance, returnNo, returnOverdraft, returnSecretVer, returnAlgorithmVer,
			returnRandom);
	if (returnState != 0)
		return 8; //读取InitialConsumeOfCPU失败

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
	char orderType[1] = { 0x06 };
	char mac1[4];
	char psamOderSn[4];
	char dateTime[7];
	char dateTimeStr[14];
	Get_DateTime(0, dateTimeStr);
	CharToHex(dateTime, dateTimeStr, 14);
	returnState = CalcMac1InPsam(slot, returnRandom, returnNo, fee, orderType, dateTime, returnSecretVer, returnAlgorithmVer, appSn, city, psamOderSn,
			mac1);
	if (returnState != 0)
		return 9; //读取CalcMac1InPsam失败

	char returnTac[4];
	char returnMac2[4];
	returnState = ConsumeCommandOfCPU(psamOderSn, dateTime, mac1, returnTac, returnMac2);
	if (returnState != 0)
		return 10; //读取ConsumeCommandOfCPU失败

	returnState = CalcMac2InPsam(slot, returnMac2);
	if (returnState != 0)
		return 11; //读取ConsumeCommandOfCPU失败

	return SUCCESS;
}


