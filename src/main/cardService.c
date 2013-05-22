#include <hspos.h>
//��ʼ��CPU�� 0�ɹ� 1��MIFʧ��  2��ȡ��ʧ��  3��λ��ʧ�� snData ���ؿ����к�
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

//��ʼ��PSAM�� ��һ��
int InitailizePsamCard(int slot) {
	unsigned char returnBuffer[100];
	int slot2PowerOpen = slot;
	int openReturn = ICC_PowerOpen(slot2PowerOpen, 38400, 3, returnBuffer);
	return openReturn;
}
//��ȡPSAM����� ����ֵ9000 ����6�ֽ� �ڶ���  �����ն˻����
int ReadPsamNo(int slot, U8 *returnlen, char* returnBuffer) {
	unsigned char inputBuffer[100];
	char command[] = { 0x00, 0xB0, 0x96, 0x00, 0x06 };
	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, returnlen, returnBuffer);
	if (returnValueOfCommand == 0)
		return 0;
	return 1;
}

//PSAM��ѡ���ļ� ѡ��ȫ����Կ����������ADF  ������  ����������Կ����
int SelectAdfSecretFile(int slot, U8 *returnlen, char* returnBuffer) {
	unsigned char inputBuffer[100];
	char command[] = { 0x00, 0xA4, 0x00, 0x00, 0x02, 0x10, 0x01 };
	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, returnlen, returnBuffer);
	if (returnValueOfCommand == 0)
		return 0;
	return 1;
}
//CPU ��ȡ�û�����ȫʶ���� 80CA000009��ָ��ִ�гɹ����ȡ9�ֽڰ�ȫʶ���롾 ����9000 ����9�����Ĳ�
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

//CPU ѡ���û���ED/EPӦ��    ���ط�������ʶ��Ӧ�����кŵ���Ϣ ָ��ִ�гɹ��󣺵�2�ֽڿ�ʼ2�ֽ�Ϊ���д��룬��12�ֽڿ�ʼ8�ֽ�ΪӦ�����кš� ����9000 ����30�� ���Ĳ�
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

//CPU ���ѳ�ʼ��  ������������û���������š���Կ�汾���㷨��ʶ ���Ĳ�
//805001020B+01(������Կ����)+00000001(���׽�ת����16������)+000000010001(PSAM���ն˱��)+0F(Ҫ�󷵻��ĳ���)��
//ָ��ִ�гɹ����أ�4�ֽڵ���Ǯ�����+2�ֽڵ���Ǯ���������+3�ֽ�͸֧�޶�+1�ֽ���Կ�汾��+1�ֽ��㷨��ʶ+4�ֽ�α�����
int ReadCpuCardInfo(char* secretIndex, char* moneyHex, char* psamNo, char *returnlenHex, char* balance, char* no, char* overdraft, char* secretVer,
		char* algorithmVer, char* random) {
	U8 returnlen;
	char returnBuffer[100];
	char command[17] = { 0x80, 0x50, 0x01, 0x02, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//д��������Կ����
	memcpy(command + 5, secretIndex, 1);
	//д�뽻�׽�ת����16������
	memcpy(command + 5 + 1, moneyHex, 4);
	//д��PSAM���ն˱��
	memcpy(command + 5 + 1 + 4, psamNo, 6);
	//д��Ҫ�󷵻��ĳ���
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
int CalcMac1InPsam(int slot, char* random, char* no, char* moneyHex, char* oderType, char* dateTime, char* secretVer, char* algorithmVer, char* appSn,
		char* city, char* psamOderSn, char* mac1) {
	U8 returnlen;
	char returnBuffer[100];
	char command[35] = { 0x80, 0x70, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//д�������
	memcpy(command + 5, random, 4);
	//д��CPU���������
	memcpy(command + 5 + 4, no, 2);
	//д�뽻�׽��
	memcpy(command + 5 + 4 + 2, moneyHex, 4);
	//д�뽻������
	memcpy(command + 5 + 4 + 2 + 4, oderType, 1);
	//д�뽻��ʱ��
	memcpy(command + 5 + 4 + 2 + 4 + 1, dateTime, 7);
	//д����Կ�汾��
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7, secretVer, 1);
	//д���㷨��ʶ
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1, algorithmVer, 1);
	//д���㷨��ʶ
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1 + 1, appSn, 8);
	//д����б�ʶ
	memcpy(command + 5 + 4 + 2 + 4 + 1 + 7 + 1 + 1 + 8, city, 2);
	//д��6�ֽڹ̶�ֵ
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
 *   �û�������:������
 *   80��54��01��00��0F
 +00,00,00,29(4�ֽ�PSAM���ն˽������)
 +20081009140759(7�ֽڽ�������ʱ��)
 +E82AEB3B08(4�ֽ�MAC1)��ָ��ִ�гɹ����أ�4�ֽ�TAC+4�ֽ�MAC2
 * */
int CpuCardConsumeCommand(char* psamOderSn, char* dateTime, char* mac1, char* tac, char* mac2) {
	U8 returnlen;
	char returnBuffer[100];
	char command[17] = { 0x80, 0x54, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//д�� 4�ֽ�PSAM���ն˽������
	memcpy(command + 5, psamOderSn, 4);
	//д��7�ֽڽ�������ʱ��
	memcpy(command + 5 + 4, dateTime, 7);
	//д��4�ֽ�MAC1
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
 *   PSAM������(��֤MAC2):���߲�
 8072000004+AE50FB88(4�ֽ�MAC2)����ǰ����ֵ6901 ����0�ֽڡ�
 * */
int CalcMac2InPsam(int slot, char* mac2) {
	U8 returnlen;
	char returnBuffer[100];
	char command[35] = { 0x80, 0x72, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };
	//д��mac2
	memcpy(command + 5, mac2, 4);

	unsigned short returnValueOfCommand = ICC_IsoCommand(slot, sizeof (command), command, &returnlen, returnBuffer);
	if (returnValueOfCommand == 0) {
		return 0;
	}
	return 1;
}

/*--------------------����CPU����------------------------*/
//������Ǯ����805C000204������4�ֽ�16������ת��10����
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

// 00b0950202 ��ȡ4�������ֽڳ��д��룬����ͨ ����2�ֽ� 3140��
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

// 00b0950C08 ��ȡ16�ֽ�Ӧ�����кţ�4�ֽڳ��д���+16�ֽ�Ӧ�����к����20λ�ǽӴ�ʽ��ˮ��  ��ʵ�ʵ�ͨ �������ֽ� 8�ֽڡ�
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

// ��ȡ������00b0960214��20λ�������� ����ͨ��
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

// ��ȡ֤�����룺00b0961620��32λ֤������ ����ͨ��
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

// ��ȡ�Ӵ�ʽ���ţ�00b0963809��9λ�Ӵ�ʽ����
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
