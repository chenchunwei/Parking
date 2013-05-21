#include <hspos.h>

void CPUCardTEest(int slot, char* cmd) {
	unsigned char k, i, returnLen,returnValue;
	unsigned char returnBuffer[100];
	unsigned short returnValueOfCommand;
	while (1) {
		cls();
		printf("  Slot %d", slot);
		putstr(" card test");
		putstr("\n0.icc powerOpen ");
		putstr("\n1.icc detect");
		putstr("\n2.icc cmd ");
		putstr("\n3.icc close ");
		putstr("\n[cls] exit");
		k = key(0);
		if (k == '0') {
			cls();
			putstr("\n ICC_PowerOpen 进行中");
			putstr("\n slot= ");
			printf("%d", slot);
			int slot2PowerOpen = slot;
			int openReturn = ICC_PowerOpen(slot2PowerOpen, 38400, 3, returnBuffer);
			if (openReturn == 0) {
				putstr("\n ICC_PowerOpen 失败");
			} else {
				putstr("\n ICC_PowerOpen 成功\n");
				int maxLen = sizeof (returnBuffer);
				for (i = 0; i < maxLen; i++) {
					if (returnBuffer[i] == '\0') {
						putstr("\n 读取完毕 ");
						break;
					}
					printf("%02X", returnBuffer[i]);
				}
			}
			key(0);
		} else if (k == '1') {
			returnValue = ICC_DetectCard(slot);
			printf("\nrt v=%x", returnValue);
			key(0);
		} else if (k == '2') {
			cls();
			putstr("\n输入指令：\n");
			unsigned char inputBuffer[100];
			char len = keys(inputBuffer);
			unsigned char hexBuffer[100];
			CharToHex(hexBuffer, inputBuffer, len);
			returnValueOfCommand = ICC_IsoCommand(slot, len / 2, hexBuffer, &returnLen, returnBuffer);
			printf("\nreturnLen=%d", returnLen);
			if (returnLen > 0) {
				putstr("\n");
				for (i = 0; i < returnLen; i++) {
					printf("%X", returnBuffer[i]);
				}
			}
			putstr("\n指令长度： ");
			printf("%d ;Return: 0x %X  ", len / 2, returnValueOfCommand);
			key(0);
			key(0);
		} else if (k == '3') {
			ICC_IFClose();
		} else if (k == KEY_CLS) {
			return;
		}
	}
}

void TestCpuCmd() {
	char returnValueOfMifOpen = mif_open();
	if (returnValueOfMifOpen != MI_OK) {
		putstr("\n 打开Mif失败");
		key(0);
		return;
	}
	unsigned char sn[10], k, i, returnLen;
	unsigned char returnBuffer[100];
	unsigned short returnValue;
	while (1) {
		cls();
		putstr("\n RF CPU card test");
		putstr("\n0.card reset");
		printf("\n1.command ");
		k = key(0);
		cls();
		if (k == '0') {
			returnValue = InitializeCard(sn);
			switch (returnValue) {
			case 0:
				putstr("\n 读取卡成功！");
				break;
			case 1:
				putstr("\n 读取卡片失败，请将卡片放置到机器底部读卡区！");
				break;
			case 2:
				putstr("\n 复位卡片失败");
				break;
			}
			key(0);
		} else if (k == '1') {
			putstr("\n 输入指令： ");
			putch('\n');
			unsigned char inputBuffer[100];
			char len = keys(inputBuffer);
			unsigned char hexBuffer[100];
			CharToHex(hexBuffer, inputBuffer, len);
			returnValue = ISO14443A_APDU(len / 2, hexBuffer, &returnLen, returnBuffer);
			printf("\n returnLen=%d \n", returnLen);
			for (i = 0; i < returnLen; i++) {
				printf("%X", returnBuffer[i]);
			}
			printf("\n Return: 0x%X ", returnValue);
			key(0);
		} else if (k == KEY_CLS) {
			return;
		}
	}
}
//0 成功  1 读取卡失败  2 复位卡失败 snData 返回卡序列号
int InitializeCard(char* snData) {
	int returnLen;
	char sn[10], returnBuffer[100];
	uchar returnValue = ISO14443A_findcard(0x26, &returnLen, sn);
	if (returnValue == 0) {
		putn_hex(returnLen, sn);
		returnValue = ISO14443A_ATS(&returnLen, returnBuffer);
		if (returnValue != 0) {
			return 2;
		}
	} else {
		return 1;
	}
	return 0;
}
