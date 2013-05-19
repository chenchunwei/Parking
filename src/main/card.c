#include <hspos.h>
/*int main(void)
{
    unsigned char  k;
    ICC_IFOpen(0);
    while(1)
    {
    	cls();
    	putstr("\n ic card test");
    	putstr("\n1.CPU TEST ");
    	putstr("\n2.SAM TEST");
        putstr("\n[CLS].Exit");
        k=key(0);
        if(k=='1')
        {
            CPUCardTEest(1);
        }
        else if(k=='2')
        {
            CPUCardTEest(2);
        }
        else if(k==KEY_CLS)
        {
            return 1;
        }
    }
    k=key(0);
}*/
void CPUCardTEest( slot) {

	unsigned char rbuf[10], k, i, rlen;
	unsigned char rbuf3[100];
	unsigned int rv;

	//È¡Ëæ»úÊý
	unsigned char PSAM_cmd_rand[5] = { 0x00, 0x84, 0x00, 0x00, 0x08 };
	//unsigned char PSAM_cmd_file[] = { 0x00, 0xa4, 0x00, 0x00, 0x02, 0x3f, 0x00 };
	unsigned char PSAM_cmd_file[] = { 0x00, 0xa4, 0x00, 0x00, 0x02, 0x00, 0x00 };
	unsigned char rt;
	while (1) {
		cls();
		printf("  Slot %d", slot);
		putstr(" card test");
		putstr("\n1.icc reset ");
		putstr("\n2.icc detect");
		putstr("\n3.icc cmd ");
		putstr("\n4.icc close ");
		putstr("\n[cls] exit");
		k = key(0);
		if (k == '1') {
			cls();
			rt = ICC_Reset(slot, &rlen, rbuf3);
			printf("\nrt=%x,%x", rt, rlen);
			printf("\nReset Message\n");
			if (rt > 0) {
				for (i = 0; i < rlen; i++) {
					printf("%02x", rbuf3[i]);
				}
			}
			key(0);
		} else if (k == '2') {

			rt = ICC_DetectCard(slot);
			printf("\nrt v=%x", rt);

			key(0);
		} else if (k == '3') {
			//while(1)
			//{
			cls();
#if 0
			printf("\n get random ");
			rv=ICC_IsoCommand(slot,5,PSAM_cmd_rand,&rlen,rbuf3);
			if(rv==0x9000)
			{
				printf("\n");
				for(i=0;i<rlen;i++)
				{
					printf("%02X",rbuf3[i]);
				}

				printf("\nReturn: 0x%X ",rv);

			}
			else
			{
				printf("\n rv=%x",rv);
			}
#endif

			printf("\n select file ");
			rv = ICC_IsoCommand(slot, 7, PSAM_cmd_file, &rlen, rbuf3);
			if (rv == 0x9000) {
				printf("\n");
				for (i = 0; i < rlen; i++) {
					printf("%02X", rbuf3[i]);
				}

				printf("\nReturn: 0x%X ", rv);

			} else {
				printf("\n rv=%x", rv);
			}
			key(0);
			//if(keygo()==KEY_CLS) break;
			//}

		} else if (k == '4') {
			key(0);
		} else if (k == KEY_CLS) {
			return;
		}
	}
}
