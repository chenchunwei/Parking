#include<hspos.h>
#define SUCCESS	0
int Payment(int slot, char* plateNumber, int money) {

	int returnState = InitailizeAppOfCPU();
	if (returnState != 0)
		return 1; //���ӹ���Ǯ��Ӧ��ʧ��

	char psamNo[6];
	returnState = ReadPsamNo(slot, psamNo);
	if (returnState != 0)
		return 2; //��ȡPSAM��noʧ��

	char selectAdfFileReturn[40];
	returnState = SelectAdfSecretFromPsam(slot, selectAdfFileReturn);
	if (returnState != 0)
		return 3; //��ȡSelectAdfSecretFromPsamʧ��

	char secretIndex[1];
	returnState = SelectSecretIndexFromPsam(slot, &secretIndex);
	if (returnState != 0)
		return 4; //��ȡSelectSecretIndexFromPsamʧ��

	char city[2];
	char appSn[8];
	returnState = ReadCardInfoOfCPU(city, appSn);
	if (returnState != 0)
		return 5; //��ȡReadCardInfoOfCPUʧ��

	char cpuSecretCode[9];
	returnState = ReadSecretCodeOfCPU(cpuSecretCode);
	if (returnState != 0)
		return 6; //��ȡReadSecretCodeOfCPUʧ��

	returnState = ConfirmSecretCodeOfPSAM(slot, cpuSecretCode);
	if (returnState != 0)
		return 7; //��ȡConfirmSecretCodeOfPSAMʧ��

	/*�û�����ͨ���ѳ�ʼ��:805001020B+01(������Կ����)+00000001(���׽�ת����16������)+000000010001(PSAM���ն˱��)+0F(Ҫ�󷵻��ĳ���)��
	 ָ��ִ�гɹ����أ�4�ֽڵ���Ǯ�����+2�ֽڵ���Ǯ���������+3�ֽ�͸֧�޶�+1�ֽ���Կ�汾��+1�ֽ��㷨��ʶ+4�ֽ�α�����*/
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
		return 8; //��ȡInitialConsumeOfCPUʧ��

	//PSAM MAC1����  ����MAC1���ն��ѻ�������� ���岽
	/*PSAM�����ѳ�ʼ��(����MAC1):
	 * 80,70,00,00,24+47800CF7(4�ֽ�α�����)
	 +0006(2�ֽڵ���Ǯ���������)
	 +00000001(4�ֽڽ��׽��)
	 +06(1�ֽڽ�������)
	 +20081009140759(7�ֽڽ�������ʱ��)
	 +01(1�ֽ���Կ�汾��)+00(1�ֽ��㷨��ʶ)
	 +2144000000000001(8�ֽ�Ӧ�����к�)
	 +2144(2�ֽڳ��д���)
	 +FF0000000000(6�ֽڹ̶�ֵ)��ָ��ִ�гɹ��󷵻�4�ֽ�PSAM���ն˽������+4�ֽ�MAC1
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
		return 9; //��ȡCalcMac1InPsamʧ��

	char returnTac[4];
	char returnMac2[4];
	returnState = ConsumeCommandOfCPU(psamOderSn, dateTime, mac1, returnTac, returnMac2);
	if (returnState != 0)
		return 10; //��ȡConsumeCommandOfCPUʧ��

	returnState = CalcMac2InPsam(slot, returnMac2);
	if (returnState != 0)
		return 11; //��ȡConsumeCommandOfCPUʧ��

	return SUCCESS;
}


