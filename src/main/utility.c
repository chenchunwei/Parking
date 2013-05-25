#include<hspos.h>
#define SUCCESS	0
/*将字符串转换成16进制数*/
void CharToHex(char *returnData, char * inputBuffer, int len) {
	int i = 0;
	int j = 0;
	unsigned char temp;
	while (i < len) {
		temp = inputBuffer[i];
		if ((temp >= 0x30) && (temp <= 0x39)) {
			temp = temp - 0x30;
			returnData[j] = temp << 4;
		} else if ((temp >= 0x41) && (temp <= 0x46)) {
			temp = temp - 0x41 + 0x0A;
			returnData[j] = temp << 4;
		} else if ((temp >= 0x61) && (temp <= 0x66)) {
			temp = temp - 0x61 + 0x0A;
			returnData[j] = temp << 4;
		} else {
			returnData[j] = 0x00;
		}
		temp = inputBuffer[i + 1];
		if ((temp >= 0x30) && (temp <= 0x39)) {
			temp = temp - 0x30;
			returnData[j] = returnData[j] | temp;
		} else if ((temp >= 0x41) && (temp <= 0x46)) {
			temp = temp - 0x41 + 0x0A;
			returnData[j] = returnData[j] | temp;
		} else if ((temp >= 0x61) && (temp <= 0x66)) {
			temp = temp - 0x61 + 0x0A;
			returnData[j] = returnData[j] | temp;
		} else {
			returnData[j] = returnData[j] | 0x00;
		}
		i = i + 2;
		j = j + 1;
	}
	return;
}

/* 从键盘接收一串全高数字字符,带回显,存放在cData */
/* 入口: renderLen为欲显示的原cData中数据的长度,maxLen为最多允许接收的数据长度,charType为0时只可接收数字,为1时可接收字母,运算符等 */
/* 出口: 返回接收字符串的长度,字符串为空时返回0(若按下数值键后再按功能键,则把功能键值存放在cData[2],若首先就按下功能键,则把该键值存放在cData[1] */
int ReadLine(uchar *cData, uchar renderLen, uchar maxLen, uchar charType) {
	uchar x1, x2, y1, y2, k, currentCursor, i2, f, end = 0;
	currentCursor = renderLen;
	x1 = getx();
	y1 = gety();
	if (renderLen != 0)
		putn_h(renderLen, cData);
	do {
		if (currentCursor != maxLen) {
			putch_h('_');
			x2 = getx();
			y2 = gety() - 1;
		} else {
			x2 = getx();
			y2 = gety();
		}
		moveto(x2, y2);
		getKey: k = key(0);
		if (charType == 0) {
			if ((currentCursor == maxLen) && (k >= 0x30) && (k <= 0x39))
				goto getKey;
			if ((k < 0x30 || k > 0x39) && k != 0x82)
				end = 1;
		}
		if (charType == 1) {
			if (k == 0x80)
				goto getKey;
			if (currentCursor == maxLen && !(k == 0x8d || k == 0x87 || k == 0x88 || k == 0x89 || k == 0x8e || k == 0x8f || k == 0x82))
				goto getKey;
			if (k == 0x8d || k == 0x87 || k == 0x88 || k == 0x89 || k == 0x8e || k == 0x8f)
				end = 1;
		}
		cData[currentCursor] = k;
		if (end) {
			f = 0;
			if (currentCursor == 0) {
				cData[0] = 0;
				cData[1] = k;
				moveto(x1, y1);
				putch_h(' ');
				moveto(x1, y1);
			} else {
				if (k == KEY_ENTER) {
					cData[currentCursor] = 0;
					if (currentCursor != maxLen)
						putch_h(' ');
					f = currentCursor;
				} else {
					cData[0] = 0;
					cData[1] = 0;
					cData[2] = k;
					moveto(x1, y1);
					for (i2 = 0; i2 <= y2 - y1; i2++)
						putch_h(' ');
				}
			}
			return currentCursor;
		}
		if (k == KEY_CLS) {
			if (currentCursor != 0) {
				putch_h(' ');
				currentCursor = currentCursor - 1;
				y2 = y2 - 1;
				moveto(x2, y2);
			}
		} else {
			putch_h(cData[currentCursor]);
			currentCursor++;
		}
	} while (1);
	return currentCursor;
}

//HEX => Int32 [Exam: 0x00,0x00,0x03,0xE8 => 1000]
int HexToInt32(uchar * hex, int *dec) {
	int index = 0;
	*dec = (hex[index] << 24) | (hex[index + 1] << 16) | (hex[index + 2] << 8) | hex[index + 3];
	return SUCCESS;
}

//Int32 => HEX [Exam: 1000 => 0x00,0x00,0x03,0xE8]
int Int32ToHex(int dec, uchar *hexBuffer) {
	hexBuffer[0] = dec >> 24;
	hexBuffer[1] = dec >> 16;
	hexBuffer[2] = dec >> 8;
	hexBuffer[3] = dec & 0xFF;
	return SUCCESS;
}

