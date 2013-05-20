#include <hspos.h>

void CPUCardTEest(int slot, char* cmd) {

	unsigned char rbuf[10], k, i, rlen;
	unsigned char return_buffer[100];
	unsigned int rv;
	unsigned char rt;
	while (1) {
		cls();
		printf("  Slot %d", slot);
		putstr(" card test");
		putstr("\n0.icc open ");
		putstr("\n2.icc detect");
		putstr("\n3.icc cmd ");
		putstr("\n4.icc close ");
		putstr("\n5.icc powerOpen ");
		putstr("\n[cls] exit");
		k = key(0);
		if (k == '0') {
			cls();
			putstr("\n正在打开卡 ");
			//U8 ICC_IFOpen(U8 r);
			rt = ICC_IFOpen(0);
			if (rt == 0) {
				printf("\nrt=%x ", rt);
				putstr("\nICC_IFOpen 成功\n");
			} else {
				printf("\nrt=%x ", rt);
				putstr("打开卡失败 ");
			}
			key(0);
		} else if (k == '2') {
			rt = ICC_DetectCard(slot);
			printf("\nrt v=%x", rt);
			key(0);
		} else if (k == '3') {
			cls();
			printf("\n 输入cmd: ");
			unsigned char cmd[100];
			int len = ReadLine(cmd, 100, 1);
			int cmd_len = sizeof (cmd);
			rv = ICC_IsoCommand(slot, cmd_len, cmd, &rlen, return_buffer);
			if (rv == 0x9000) {
				printf("\n");
				putstr("命令执行成功");
				for (i = 0; i < rlen; i++) {
					printf("%02X", return_buffer[i]);
				}
				printf("\nReturn: 0x%X ", rv);
			} else {

				printf("\n rv=%x ,len=%d", rv, rlen);
				printf("\n");
				putstr("else return");
				printf("\n");
				for (i = 0; i < rlen; i++) {
					printf("%02X", return_buffer[i]);
				}
				printf("\nReturn: 0x%X ", rv);
			}
			key(0);
			//if(keygo()==KEY_CLS) break;
			//}

		} else if (k == '4') {
			key(0);
		} else if (k == '5') {
			cls();
			putstr("\n ICC_PowerOpen 进行中");
			putstr("\n slot= ");
			printf("%d", slot);
			int slot2PowerOpen = slot;
			int openReturn = ICC_PowerOpen(slot2PowerOpen, 38400, 3, return_buffer);
			if (openReturn == 0) {
				putstr("\n ICC_PowerOpen 失败");
			} else {
				putstr("\n ICC_PowerOpen 成功\n");
				int maxLen = sizeof (return_buffer);
				for (i = 0; i < maxLen; i++) {
					if (return_buffer[i] == '\0') {
						putstr("\n 读取完毕 ");
						break;
					}
					printf("%02X", return_buffer[i]);
				}
			}

			key(0);
		} else if (k == KEY_CLS) {
			return;
		}
	}
}

void TestCpuCmd(void) {
	char returnValue = mif_open();
	if (returnValue != MI_OK) {
		putstr("\n inital error");
		key(0);
		return;
	}
	unsigned char sn[10], k, i, returnLen;
	unsigned char returnBuffer[100];

	//取随机数
	unsigned char PSAM_cmd_rand[5] = { 0x00, 0x84, 0x00, 0x00, 0x08 };
	unsigned char PSAM_cmd_file[64] = { 0x00, 0xa4, 0x04, 0x00, 0x07, 0x52, 0x73, 0x61, 0x20, 0x41, 0x70, 0x70, 0x00 };
	unsigned char PSAM_cmd_1[] = { 0x80, 0xc2, 0x00, 0x01, 0x01, 0x31 };
	unsigned char PSAM_cmd_3[] = { 0x80, 0x1a, 0x44, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00 }; //801A440110 00 00 00 00 00 00 00 00 30 00 FF 00 00 00 00 00
	//ucid
	unsigned char PSAM_cmd_2[16] = { 0x00, 0xb0, 0x01, 0x03, 0x0e }; //00B001030E

	while (1) {
		cls();
		putstr("\n RF CPU card test");
		putstr("\n0.card reset");
		printf("\n1.select file ");
		putstr("\n2.ucid");
		putstr("\n3.签名");
		printf("\n4.cmd 2");
		printf("\n5.Deselect card");
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
			printf("\n select file ");
			putch('\n');
			putn_hex(13, PSAM_cmd_file);
			returnValue = ISO14443A_APDU(13, PSAM_cmd_file, &returnLen, returnBuffer);
			if (returnValue == 0x9000) {
				printf("\n");
				for (i = 0; i < returnLen; i++) {
					printf("%02X", returnBuffer[i]);
				}
				printf("\nReturn: 0x%X ", returnValue);
			} else {
				printf("\nrv=%x", returnValue);
			}
			key(0);
		} else if (k == '2') {
			printf("\n ucid ");
			putch('\n');
			unsigned char inputBuffer[100];
			char len = keys(inputBuffer);
			printf("\n enter completed ");
			printf("\n len=%x",len);
			unsigned char hexBuffer[100];
			CharToHex(hexBuffer, inputBuffer, len);
			putch('\n');
			putn_hex(len/2, hexBuffer);
			key(0);
			returnValue = ISO14443A_APDU(len, hexBuffer, &returnLen, returnBuffer);
			if (returnValue == 0x9000) {
				printf("\n");
				for (i = 0; i < returnLen; i++) {
					printf("%X", returnBuffer[i]);
				}
				printf("\nReturn: 0x%X ", returnValue);
			} else {
				putstr("\n 错误码=");
				printf("%x", returnValue);
			}
			key(0);
		} else if (k == '3') {
			putstr("\n 签名 ");
			putch('\n');
			putn_hex(6, PSAM_cmd_1);
			returnValue = ISO14443A_APDU(6, PSAM_cmd_1, &returnLen, returnBuffer);
			if (returnValue == 0x9000) {
				printf("\n");
				for (i = 0; i < returnLen; i++) {
					printf("%02X", returnBuffer[i]);
				}
				printf("\nReturn: 0x%X ", returnValue);
			} else {
				printf("\nrv=%x", returnValue);
			}
			key(0);
		} else if (k == '4') {
			printf("\n select file ");
			putch('\n');
			putn_hex(21, PSAM_cmd_2);
			returnValue = ISO14443A_APDU(21, PSAM_cmd_2, &returnLen, returnBuffer);
			if (returnValue == 0x9000) {
				printf("\n");
				for (i = 0; i < returnLen; i++) {
					printf("%02X", returnBuffer[i]);
				}
				printf("\nReturn: 0x%X ", returnValue);
			} else {
				printf("\n rv=%x", returnValue);
			}
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
