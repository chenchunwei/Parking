#include<hspos.h>

typedef unsigned char Uchar8; /*  8bit	*/
typedef unsigned short Uint16; /* 16bit	*/
typedef unsigned long Uint32; /* 32bit	*/
typedef unsigned long long Uint64; /* 64bit	*/

typedef signed char Schar8;
typedef signed short Sint16;
typedef signed long Sint32;
typedef signed long long Sint64;

/*	ϵͳ��Ϣ	*/
Uchar8 G_USER_VER[2] = { 0x00, 0x00 };	//	�û��汾ʶ��λ��4λ���š���λ��־λ����
#define DEBUG				0				//	���Լ���
#define	POS_PRINTER         1				//	�Ƿ��д�ӡ��
#define	PSW_TYPE			0				//	�������ͣ���һ��һ�ܡ��տ���
//	����־�궨�塿
#define	EPR_FLOWNO			0x18			//	4λASCII�ַ� ��ˮ�ߺ�
#define	FLAG_IN				0x39			//	���ϵı�־λ��ϵͳ�����о�����һ��ֵ����Ƭ����Ϊ0x00�����˲��ô�ֵ��
#define FLAG_OUT			0x00			//
#define	FLAG_GS				0x03			//	��ʧ
#define	FLAG_FOE			0x04			//	�Ǳ�ϵͳ��Ƭ
#define	FLAG_REPEAT			0x05			//	���������ظ�ʹ��
#define	FLAG_CONSUME		0x40			//	���ѽ����б�־
#define	TYPE_TEMP			0x00			//	��ʱ��
#define	TYPE_MONTH			0x06			//	�¿�
#define	TYPE_VIP			0x07			//	�����
#define	FLAG_SMALL			0x30
#define	FLAG_MIDDLE			0x31
#define	FLAG_BIG			0x32
#define	FLAG_TEZHONG		0x33
#define	FLAG_SANLUN			0x34
#define	FLAG_QITA			0x35

#define STATE_DAY   		0x55
#define STATE_NIGHT 		0x66

/*	�������		*/
#define NO_CARD				0x50			//	�޿�
#define	CR_OPEN_ER			0x51
#define	CR_CLOSE_ER			0x52
#define	REQUEST_ER          0x53
#define	ANTICOLL_ER         0x54
#define SELECT_ER           0x55
#define	DBF_ER				0x70

//	������Ա����
#define	CZY0				0x00			//	δ��½״̬��δ������ȷ����ʱ��Ĭ��״̬��
#define	CZY1				0x11			//	�շ�Ա״̬
#define	CZY2				0x12
#define	CZY3				0x13

//	������Ա��š�
#define	U_SFY				1
#define	U_JZY				8
#define	U_GLY				0

#define	U_SFY1				1
#define	U_SFY2				2
#define	U_SFY3				3
#define	U_SFY4				4
#define	U_SFY5				5
#define	U_SFY6				6
#define	U_SFY7				7

//	�����ݿ��š�
#define	DBFNO_PARK			0				//	�������ݿ�Ϊ�ڼ����ݿ�
#define	DBFNO_PARKBKP		1				//	ͣ�����ݿⱸ�����ݿ�
#define	DBFNO_CARD			2				//	�������ݿ�Ϊ�ڼ����ݿ�
#define	DBFNO_GS			3				//	�������ݿ�Ϊ�ڼ����ݿ�
#define	DBFNO_BOWEI			4				//	�û��������롢��λ�Ż���
//	�����ݿ��ֶ�������
#define	LSH					0				//	10	��ˮ��
#define	CZJ					1				//	5	������/POSID
#define	PCH					2				//	���κ�
#define	CZY					3				//	10	����Ա
#define	CLX					4				//	������
#define	TCD					5				//	ͣ����
#define	BWH					6				//	��λ��
#define	CHEPAI				7				//	���ƺ�
#define	JRSJ				8				//	20	����ʱ��
#define	LKSJ				9				//	20	�뿪ʱ��
#define	YSJE				10				//	7+2	Ӧ�ս��
#define	SCCG				11				//	�ϴ��ɹ���־
#define	BCCZY				12
#define	BCCZYMM				13
#define	BCZTW				14
//	����Լ100���ֽ�

//	��EEPROM��ַ���䡿
#define	EPR_POSID			0x10			//	POS��ID��ŵ�ַ
#define	EPR_FLOWNO			0x18			//	4λASCII�ַ�
#define	EPR_ORGNAME			0x20			//	��λ���ƴ�ŵ�ַ����һ���ֽڴ�ų��ȣ��ڶ�����ʼ���ʵ������
#define	EPR_MM				0x30			//	�ڴ�������
#define	EPR_P_STEP0			0x50			//	�Ʒ�ʱ��0��4λASCII�ַ�
#define	EPR_P_STEP1			0x58			//	�Ʒ�ʱ��1��4λASCII�ַ���Сʱ��λ
#define	EPR_P_STEP2			0x60			//	�Ʒ�ʱ��2��4λASCII�ַ���Сʱ��λ
#define	EPR_P_STEP3			0x68			//	�Ʒ�ʱ��3��4λASCII�ַ���Сʱ��λ
#define	EPR_P_STEP4			0x70			//	���ʱ�䣬4λASCII�ַ������ӵ�λ
#define	EPR_P_RATE1			0x78			//	�Ʒѱ�׼1
#define	EPR_P_RATE2			0x80			//	�Ʒѱ�׼2
#define	EPR_P_RATE3			0x88			//	�Ʒѱ�׼3
#define	EPR_P_RATE4			0x90			//	�Ʒѱ�׼4
#define	EPR_P_RATE5			0x98			//	�Ʒѱ�׼��������շ�
#define	EPR_UPSW_SFY1		0xA0			//	���� �շ�Աһ
#define	EPR_UPSW_SFY2		0xA8
#define	EPR_UPSW_SFY3		0xB0
#define	EPR_UPSW_SFY4		0xB8
#define	EPR_UPSW_SFY5		0xC0
#define	EPR_UPSW_SFY6		0xC8
#define	EPR_UPSW_JZY		0xF0			//	���� ����Ա
#define	EPR_UPSW_GLY		0xF8			//	���� ����Ա
#define	EPR_UPSW_BWH		0xG8			//	���� ����Ա
#define	EPR_SJID		0x100		//	���� ����Ա
/*	���ݿ��	*/
#define	USERNAME_W			0x0A			//	����Ա�������
#define	USERPSW_W			0x06			//	�û�������
#define	USERID_W			0x04			//	�û��Զ��忨��
#define ORGNAME_W			(20)			//	��λ���ƿ��
#define	CARDNAME_W			(8)				//	������
#define	FLOWNO_W			0x04			//	��ˮ�ſ�ȣ�ʵ�ʴ洢ΪUint16�ͣ������ֽڣ�
#define	POSID_W				0x02			//	POS����ſ��
#define	P_STEP_W			0x06			//	EPR_P_STEP��ȣ�����ʱ�ָ�ʽ hrmise��
#define	P_MONEY_W			(7)				//	���������(���ô���EEPROM�ķ���ռ䳤��)
#define	CHEPAI_W			(10)			//	���ƿ�� ��ͨ���ƿ�8(��A12345) ���⳵�����9(WJ16B1234) ���Ը۰Ŀ�9(��Z1234��)
#define FLAG_FREE           0x06            //  ��λ����
#define FLAG_BUSY           0x07            //  ��λ�г�
#define FLAG_ERROR          0x08
#define BACK_YELLOW           0x09
#define BACK_TOTXY          0x10
#define	BOWEI_W				4				//	��λ���
/*	��M1���ڴ���䡿	*/
#define CARD_PWD_TYPEA 		0X01        	//	��������
#define CARD_PWD_TYPEB 		0X02        	//	��������
#define	CARD_USER_SECTOR1	5							//	�û���Ϣ����1
#define	CARD_USER_BLK10		((CARD_USER_SECTOR1*4)+0)	//	0-7(CARDNAME_W,������) 8-15(��Ч�ڽ�ֹ)
#define	CARD_USER_BLK11		((CARD_USER_SECTOR1*4)+1)	//	0-5(�û��Զ��忨��) 6(������) 7-8(�汾) 9(�����ű�־) 10(���ѱ�־)
#define	CARD_USER_BLK12		((CARD_USER_SECTOR1*4)+2)	//	0-13(����ʱ��) 14(������)
#define	CARD_USER_SECTOR2	6							//	�û���Ϣ����2
#define	CARD_USER_BLK20		((CARD_USER_SECTOR2*4)+0)
#define	CARD_USER_BLK21		((CARD_USER_SECTOR2*4)+1)	//	���ѿ�ʼʱ��
#define	CARD_USER_BLK22		((CARD_USER_SECTOR2*4)+2)	//	���ѽ���ʱ��
//	������Ϣ�ṹ��
typedef struct {
	Uchar8 GUID[4];							//	M1������ID
	Uchar8 userID[USERID_W + 2];				//	�û��Զ��忨��
	Uchar8 bwh[CHEPAI_W + 2];				//	��λ��
	Uchar8 tcd[CHEPAI_W + 2];
	Uchar8 pch[CHEPAI_W + 2];
	Uchar8 version[2 + 2];					//	POS����汾(16λ��)
	Uchar8 card_type;						//	����	��ʱ��������������
	Uchar8 card_name[CARDNAME_W + 2];			//	�����������¿���
	Uchar8 card_time[20];
	Uchar8 flag;							//	�����ű�־
	Uchar8 consume;							//	���ѱ�־
	Uchar8 chepai[CHEPAI_W + 2];				//	����

	Uint16 r;								//	��Ӧ�ļ�¼����
	Uint16 flowNO;							//	��Ӧ����ˮ��
	Uint16 INSCUESS;							//	�����Ƿ�ɹ�
	Uchar8 czy[4];                                  //����Ա
	Uchar8 clx[10];
	Uchar8 outczy[4];
	Uchar8 outczymm[10];
	//���κ�
	Uchar8 sccg[4];                            //�ϴ��ɹ�
	Uchar8 time_in[20];						//	����ʱ���ʽ����14λ������ʱ���ʽΪ19λ��
	Uchar8 time_out[20];					//	����ʱ���ʽ����14λ������ʱ���ʽΪ19λ��
	//	Uchar8 consume_b[20];					//	���ѿ�ʼ
	//	Uchar8 consume_e[20];					//	���ѽ���
	//
	//	Uchar8 POSID_in[POSID_W+2];				//	���Ų����ֳֻ�
	//	Uchar8 operator_in[8];					//	���Ų���Ա
	//	Uchar8 POSID_out[POSID_W+2];			//	���Ų����ֳֻ�
	//	Uchar8 operator_out[8];					//	���Ų���Ա
	//
	Uchar8 step0[P_STEP_W + 2];				//	ʱ����Ϣ0
	Uchar8 step1[P_STEP_W + 2];				//	ʱ����Ϣ1
	Uchar8 step2[P_STEP_W + 2];				//	ʱ����Ϣ2
	Uchar8 step3[P_STEP_W + 2];				//	ʱ����Ϣ3
	Uchar8 rate1[P_MONEY_W + 2];				//	����1		������(����)ÿСʱ
	Uchar8 rate2[P_MONEY_W + 2];				//	����2		������(����)ÿСʱ
	Uchar8 rate3[P_MONEY_W + 2];				//	����3		������(����)���
	Uchar8 rate4[P_MONEY_W + 2];				//	����4		������(����)���
	Uchar8 rate5[P_MONEY_W + 2];				//	����4
	Uchar8 time_disp[20];			//	��ʾ�õ�ռλʱ�䣨strlen("xxxxx��xxʱxx��xx��")==19��
	Uchar8 charge_due[P_MONEY_W + 2];			//	Ӧ�շ��ã���λС������λΪԪ��������ʾ�����ڲ���ͳ�ƣ�
	Uchar8 charge_real[P_MONEY_W + 2];		//	ʵ�շ��ã���λС������λΪԪ��������ʾ�����ڲ���ͳ�ƣ�
	Uchar8 cheleixing[CARDNAME_W + 2];    //���ڳ�����

} TYPE_PARKINFO;

/*	ʱ������	*/
typedef struct {
	//	��ǰ��ṹ�������ı�����Ϊǰ׺����Ա��������������Ϣ
	Uchar8 begin[19 + 1];						//	��ʼʱ�䣨14λ����ASCII�룩
	Uchar8 end[19 + 1];						//	����ʱ�䣨14λ����ASCII�룩

	Sint32 begin_s;							//	��ʼʱ����һ���еľ���ֵ��������
	Sint32 end_s;							//	����ʱ����һ���еľ���ֵ��������

	Uint16 days;							//	ʱ����е�"��"Ȩ��λ��ֵ���ܹ���������
	Uchar8 hours;							//	ʱ����е�"��"Ȩ��λ��ֵ���ܹ���������
	Uchar8 minutes;							//	"��"Ȩ��λ��ֵ
	Uchar8 seconds;							//	"��"Ȩ��λ��ֵ
	Uchar8 time_disp[20];					//	��ʾ�õ�ʱ���ʾ

} TYPE_TIMESPAN;

//	����Ա��Ϣ��ṹ��
typedef struct {
	Uchar8 UserName[9][USERNAME_W + 1];
	Uchar8 UserPSW[9][USERPSW_W + 1];
} TYPE_USER_INFO;

/*	��ȫ�ֱ�����	*/

TYPE_USER_INFO G_USERINFO;
Uchar8 G_USERNAME[USERNAME_W + 2] = { 0 };
Uchar8 G_POSID[4];
Uchar8 lshdata;
Uchar8 G_USERTYPE[10];
Uchar8 AdminId[10];
Uchar8 AdminPassId[10];
Uchar8 posiddata[20];                  //�豸id
U16 posdata[20];
Uchar8 Index_Id;                     //���ڱ������û�������
Uchar8 G_CARD_SN[10];					//	���ڱ��浱ǰ������M1�����кţ�
Uint32 G_TOTAL;
Uint16 G_FLOWNO;
Uint16 G_Sjid;
Uchar8 G_PosId[20];
Uchar8 Cb_RETURN[20];					//	��ˮ��
Uchar8 PUBLIC_VALUE[20];
int PUBLIC_BOOLEN;
int FREE_TC;
int mm_numb = 1;
int libmitnub = 1;

//Uint16	G_RECORDNO;						//	���ڷ�����ˮ��¼

/*	������������	*/
Sint32 AllUPSW_Reset(void);
Sint32 AllUName_Reset(void);
Sint32 AllUPSW_Read(TYPE_USER_INFO *G_USERINFO);
Sint32 AllUPSW_Save(TYPE_USER_INFO *G_USERINFO);

Uchar8 Block_ProRead(Uchar8 Block_NO, Uchar8 RD_NO, Uchar8 *RD_Buffer);
Uchar8 Block_ProWrite(Uchar8 Block_NO, Uchar8 WR_NO, Uchar8 *WR_Buffer);
Uchar8 Block_Write(Uchar8 Block_NO, Uchar8 *WR_Buffer);
Uchar8 Block_Read(Uchar8 Block_NO, Uchar8 *RD_Buffer);
void BuDan(void);

Uchar8 Card_Search(void);
void Card_ChaXun(void);
void CardInfo_Disp(TYPE_PARKINFO *ParkInfo);
void CardInfo_Disp_print(TYPE_PARKINFO *ParkInfo);
int CardInfo_Disp1(TYPE_PARKINFO *ParkInfo);
Uchar8 CardReader_Open(void);
Uchar8 CardReader_Close(void);
Uchar8 CardInfo_Read(TYPE_PARKINFO *ParkInfo);
Uchar8 CardInfo_Write(TYPE_PARKINFO *ParkInfo);
void Change_Date_Style(Uchar8 c, Uchar8 *s);
void Change_Time_Style(Uchar8 c, Uchar8 *s);
void Change_DateTime_Style(Uchar8 c, Uchar8 *s);
//void	CheWei_ChaXun( void );
void CardID_Set(void);
void Consume_Begin(void);
void Consume_End(void);

int display_chepai(uchar *pmenu, uchar tt, uchar *cdata);
U8 display_menu(U8 startline, U8 totals, U8 itmes_total, U8 *pmenu[], uchar *kr);
void Door_In(void);
void Door_In_1(void);
void Door_In_2(void);
void Door_Out(void);
void Door_Out_1(void);
void Door_Out_2(void);
Sint32 Data_Upload(void);

void ErrorMsg(Uchar8 *Err);
Uint16 FlowNO_Read(void);
void FlowNO_Save(Uint16);
Uint16 Sjuid_Read(void);
void Sjuid_Save(Uint16);
void Get_DateTime(Uchar8 c, Uchar8 *tdata);
int Get_State(int s_ds, int s_ns, int s_now);
void getm1psw(uchar *sn, uchar *psw);
unsigned long get_days(int year, int month, int date);
int IN_put_CHE_PAI(Uchar8 *s);
Uchar8 JMPD_DB(TYPE_PARKINFO *ParkInfo);
Uchar8 JMPD_Flag(TYPE_PARKINFO *ParkInfo);
Uchar8 ReadLine(Uchar8 *cdata, Uchar8 n1, Uchar8 n2, Uchar8 reg);
U8 Key_PSW(U8 *kdata, U8 lgh);
Uchar8 LeapYear(Sint16 year);
Uint16 length(Uchar8 *s);

void OrgName_Set(void);			//	��λ��������
Sint32 OrgName_Read(Uchar8 *kdata);
Sint32 OrgName_Save(Uchar8 *kdata);
void PFlag2IN(TYPE_PARKINFO *ParkInfo);
void PFlag2OUT(TYPE_PARKINFO *ParkInfo);
void PInfo_Save(TYPE_PARKINFO *ParkInfo);
void BudanPInfo_Save(TYPE_PARKINFO *ParkInfo);
int PInfo_Calc(TYPE_PARKINFO *ParkInfo);
int PInfo_Calcfree(TYPE_PARKINFO *ParkInfo);
Uchar8 ProCard_HL_Auth(Uint16 wtime, Uchar8 sc, Uchar8 pwdtype, Uchar8 sectorno);
void PRate_Read(TYPE_PARKINFO *ParkInfo);
void PRate_Save(TYPE_PARKINFO *ParkInfo);
void PRate_Set(void);
void Print_Bill(TYPE_PARKINFO *ParkInfo);
Sint32 POSID_Read(Uchar8 *s);
Sint32 POSID_Save(Uchar8 *s);
void POSID_Set(void);
int S16toAscii(uchar *s, uchar *sout, int leng);
void ShouFei_ChaXun(void);
void Sys_Set(void);
void Time_Offset(TYPE_TIMESPAN *ts);
void TimeSpan_Calc(TYPE_TIMESPAN *ts);
void TJ(void);

void User_Format(void);
void UserInfo_Set(Uchar8 UserType, Uchar8 UserIndex);
Sint32 UserName_Read(Uchar8 u, Uchar8 wide, Uchar8 *udata);
Sint32 UserName_Save(Uchar8 u, Uchar8 wide, Uchar8 *udata);
Sint32 UserPSW_Read(Uchar8 u, Uchar8 wide, Uchar8 *udata);
Sint32 UserPSW_Save(Uchar8 u, Uchar8 wide, Uchar8 *udata);
void WCh_Money_Round(uchar *ss, uchar *s);
void MM_ManualClr(Uchar8 mode);
void MM_DEL(Uchar8 mode);
void MM_Set(void);
Sint32 MM_Read(Uchar8 *s);
Sint32 MM_Save(Uchar8 *s);
void FKTK(void);
extern void GPRS_Link_init(void);
extern void GPRS_SET1(void);
int GPRS_Sendrcv(TYPE_PARKINFO *s);
int GPRS_OutSendrcv(TYPE_PARKINFO *s);
int GPRS_netconnect(void);
extern void get_ip(uchar *s);
extern void get_port(uchar *s);
void BuDanMune(void);
void taodan(void);
void sendsure(void);
Uchar8 ChaZhaoBw(TYPE_PARKINFO *ParkInfo);
void sendserver(void);
void BoWei_Save(Uchar8 *bdata);
int bowei_Del();
Uchar8 BWPD(Uchar8 *bdata);
int ReSend(void);
void OutPInfo_Save(TYPE_PARKINFO *s);
int GPRS_BUDANSendrcv(TYPE_PARKINFO *s);
int GPRS_TaoDanOutSendrcv(TYPE_PARKINFO *s);
void rate_set(void);
void Jump_cb(Uchar8 *udata);
void JIAOYANGTIME(Uchar8 *udata);
void LINK_YES(void);
void LINK_NO(void);

U8 BW_State(U8 *bw);
void BWState_Ref(U8 bw[], U8 state, U8 cb_txy[]);
U8 BoWei_XuanZe(U8 *bw);
U8 BoWei_ChaXun(U8 *bw);
void CheWei_ChaXun1(void);
void alert(Uchar8 *message);

//������
int main(void) {
	while (1) {
		cls();
		putstr("cpu:1  psam:2\n");
		uchar keyOfTest = key(0);
		if (keyOfTest == '1') {
			//�����û���
			TestCpuCmd();
		} else if (keyOfTest == '2') {
			//����PSam��
			putstr("����slot:\n");
			unsigned char slot = key(1);
			if (slot == '1') {
				CPUCardTEest(1);
			} else {
				CPUCardTEest(2);
			}
		} else if (keyOfTest == KEY_CLS) {
			return 1;
		}
	}

	Uchar8 k, kr, lgh, r, rlen;
	Uchar8 tdata[2000];

	Uchar8 ndata[40], pdata[40];
	Uchar8 ss;

	AllUPSW_Read(&(G_USERINFO));
	rate_set();
	ss = GET_Chip_ID(G_PosId);
	S16toAscii(G_PosId, posiddata, 16);
	//sprintf( posiddata, "%016d", tmpdata );

	Uchar8 state = libuse("bowei.dbf", DBFNO_BOWEI);
	Uchar8 openState = libopen(DBFNO_BOWEI);
	if (openState != 0 || state != 0) {
		putstr("�򿪲�λ���ݿ�ʧ�ܣ�");
		bell(100);
		key(0);
		return 0;
	}
	memset(tdata, 0x00, sizeof (tdata));
	libset(0, 0);
	libread(tdata);
	kr = 1;									//	1�򳣹��½��0��������������
	if ((tdata[0] == ' ') | (tdata[0] == 0x00))
		kr = 0;
	if (kr == 1) {
		while (1) {
			cls();
			//GPRS_Link_init();
			//GPRS_SET1();
			//GPRS_netconnect();
			//ReSend();//�����ϴ�δ���� �ɹ�������
			moveto(1, 1);
			putstr("�ٳ����½\n");
			putstr("�ڸ����û���Ϣ\n\n\n\n");

			putstr("�豸ID:");
			putstr(posiddata);
			putn_h(18, "�汾��:v3011211\n\n");

			do {
				k = key(0); /* �ȴ�����һ���ַ�,������ */
			} while (k != 0x31 && k != 0x32 && k != 0x89 && k != KEY_ENTER);
			if (k == KEY_F2)
				return 0;
			else if (k == '1')
				break;
			else if (k == '2')
				kr = 0;
			break;
		}
	}
	if (kr == 0) {
		//putstr( "��ʼ" );
		//	memset( kdata, 0x00, sizeof(kdata) );
		//memcpy( kdata, "0011234560009000900080007000600050004000300020001004123456000500050004000300020001003123456000400040003000200010091234560003000100020003010123456000200010002", 178 );
		//memcpy( kdata, "005111111002001000102010101040103010501060108010701090110011101120113011501140117011601190118004000000002001000102010101040103010501060108010701090110011101120113011501140117011601190118", 186 );
		//BoWei_Save( kdata );
		//putstr( "���" );
		//	key(0);
		//int ccc=bowei_Del();
		GPRS_Link_init();
		//GPRS_SET1();
		GPRS_netconnect();

		//Uchar16 GET_Chip_ID(posdata);
		//	memset( tdata, 0x00, sizeof(tdata) );
		//sbuf[0]='9';
		//memcpy( &(tdata[1]),posdata,16);

		memcpy(&(tdata[0]), "9", 1);
		memcpy(&(tdata[1]), posiddata, 32);					//	ע�⣺�˴���Ϊ����������ݿ�ָ��
		cominit(B9600, 0x03, UART_ON);
		Uchar8 rt = WNetTxd(tdata, 33);
		//putstr(tdata);
		//	key(0);
		if (rt != 0) {
			ErrorMsg("���ʹ���");
			key(0);
		} else {
			memset(tdata, 0x00, sizeof (tdata));
			//rlen = 1000;
					rt = WNetRxd(tdata, &rlen, 2000);
					//memcpy(tdata , tdata, rlen);
					//sprintf( datas, "%06d", rlen);
					//putstr(tdata);
					//putstr(datas);
					//putstr(tdata);
					//  key(0);
					if (rt != 0) {
						ErrorMsg("����ʧ��");
						WNetIPClose("1", 4000);
						key(0);
					} else {
						MM_DEL(0x02);
						ll9: BoWei_Save(tdata);
						mm_numb++;
						if (mm_numb <= 2) {
							goto ll9;
						}
						ErrorMsg("���ճɹ�");
						WNetIPClose("1", 4000);
					}
				}
			}

	while (1) {
		txy: cls();
		moveto(3, 1);
		bell(20);
		putstr("��½��:");
		memset(ndata, 0x00, sizeof (ndata));
		lgh = ReadLine(ndata, 0, 3, 1);
		if (lgh == 0) {
			if (ndata[1] == KEY_F2)
				return 0;
			else
				continue;
		}
		moveto(7, 1);
		bell(20);
		putstr("��  ��:");
		memset(pdata, 0x00, sizeof (pdata));
		lgh = Key_PSW(pdata, USERPSW_W);
		if (lgh == 0) {
			if (pdata[1] == KEY_F2)
				return 0;
			else
				continue;
		}
		libopen(DBFNO_BOWEI);
		libset(6, 6);
		libread((char*) lshdata);
		for (r = 0; r < libsumf(); r++) //�������е��û������ҳ�������ƥ���
				{
			memset(tdata, 0x00, sizeof (tdata));
			libset(0, r);
			libread(tdata);
			if (memcmp(tdata, ndata, 3) == 0) {
				memset(tdata, 0x00, sizeof(tdata));
				libset(1, r);
				libread(tdata);
				if (memcmp(tdata, pdata, USERPSW_W) == 0) {
					memcpy(AdminId, ndata, 3);
					memcpy(AdminPassId, pdata, 6);
					Index_Id = r; //����ȫ�ֱ�����Ϊ������Ҳ�λ����������
					break;
				}
			}
		}
		if (r >= libsumf()) {
			ErrorMsg("��¼��\n���������");
			if (key(0) == KEY_F2)
				goto txy;
			else
				continue;
		} else {
			break;
		}
	}
	P_U8 menu[] = { "[1] ��������", "[2] ��������", "[3] ��λ��ѯ", "[4] �շѲ�ѯ", "[5] ��������", "[6] �ӵ�����", "[7] ϵͳ����" };
	if (kr == 1) {
		GPRS_Link_init();
		//GPRS_SET1();
		//GPRS_netconnect();
		libuse("park.dbf", DBFNO_PARK);
		ReSend();
		libclose(DBFNO_PARK);
		//WNetIPClose("1",1000);
		// WNetClose(1000);
	}

	cls();
	screen(1); /* �趨Ϊ������ʾ״̬ */
	Uchar8 rt = libuse("park.dbf", DBFNO_PARK);
	if (rt != 0) {
		putstr("��park.dbf���ݿ����");
		bell(100);
		key(0);
	} else {
	}

	AllUPSW_Read(&(G_USERINFO));
	for (k = 0; k < USERPSW_W; k++) {
		if ((G_USERINFO.UserPSW[U_GLY][k] < 0x30) | (G_USERINFO.UserPSW[U_GLY][k] > 0x39)) {
			PRate_Set();
			User_Format();
			break;
		}
	}

	bell(20);

	while (1) {
		cls();
		OrgName_Save("����ͣ���շ�ϵͳ");
		memset(tdata, 0x00, sizeof (tdata));
		OrgName_Read(tdata);
		lgh = strlen(tdata);
		if (lgh < 20) {
			moveto(1, (20 - lgh) / 2 + 1);
			putn_h(lgh, tdata);
		} else {
			moveto(1, 1);
			putn_h(20, tdata);
		}
		memset(G_POSID, 0x00, sizeof (G_POSID));
		POSID_Read(G_POSID);
		moveto(3, ((14 - strlen(G_POSID)) / 2));
		putstr("��ǰ�û�");
		putn_h(3, AdminId);
		//putstr( "�Ż�" );
		moveto(5, 1);

		k = display_menu(5, 7, 7, menu, &kr);

		switch (k) /* ��������İ���������Ӧ�ĺ��� */
		{
		case 0:
			Door_In_2();
			break;
		case 1:
			Door_Out_2();
			break;
		case 2:
			CheWei_ChaXun1();
			break;
		case 3:
			ShouFei_ChaXun();
			break;
		case 4:
			BuDan();
			break;
		case 5:
			taodan();
			break;
		case 6:
			Sys_Set();
			break;

		case 0xFF:
			break;
		case 0x89:
			return 0;
			break;
		default:
			;
			break;
		}
	}
	return 0;
}
void BWState_Ref(U8 bw[], U8 state, U8 cb_txy[]) {
	U8 k, s;
	U16 sumr, sumf, i;
	U8 kdata[40];
	libopen(DBFNO_BOWEI);
	sumr = libsumr();
	sumf = libsumf();
	k = sumf - 2;				//	���Ƶ��û���λ��Ϣ
	s = sumf - 1;				//	��λ״̬

	//	���ݲ�λ�Ž��и���
	if (sumr <= 2) {
		ErrorMsg("�޲�λ��Ϣ");
		key(0);
		return;
	}
	for (i = 3; i < sumr; i++) {
		libset(i, 0);
		memset(kdata, 0x00, sizeof (kdata));
		libread(kdata);

		if (memcmp(kdata, bw, BOWEI_W) == 0)       //  ����ʱ����ͬ
				{
			libset(i, s);

			if (state == FLAG_FREE) {
				libwrite("����");
			} else if (state == FLAG_BUSY) {
				libwrite(cb_txy);
			}
		}
	}
	if (i == sumr) {
		if (kdata[0] == ' ') {
			return;
		} else {
			return;
		}
	}
}
U8 BW_State(U8 *bw) {
	Uchar8 kdata[40], tdata[40];
	Sint32 last, r;                                 //  ���ݿ��п���Ϊ�գ���ʱlast����Ϊ����
	libopen(DBFNO_PARK);
	last = libsumr() - 1;
	for (r = last; r >= 0; r--) {
		memset(kdata, 0x00, sizeof (kdata));
		libset(r, BWH);
		libread(kdata);
		if (memcmp(kdata, bw, BOWEI_W) == 0)       //  ����ʱ����ͬ
				{
					memset(tdata, 0x00, sizeof(kdata));
					libset(r, LKSJ);
					libread(tdata);
					if ((tdata[0] < 0x30) || (tdata[0] > 0x39)) {
						return FLAG_BUSY;					//	��δ����
					} else {
						return FLAG_FREE;					//	��δ����
					}
				}
			}
	return FLAG_ERROR;								//	δ�ҵ���λ��
}
void Jump_cb(Uchar8 *udata) {
	Uchar8 r;
	//Uchar8 rt;
	Uchar8 tdata[20];
	//rt = libuse( "bowei.dbf", DBFNO_BOWEI );
	libopen(DBFNO_BOWEI);
	for (r = 0; r < libsumf(); r++) //�������е��û������ҳ�������ƥ���
			{
		memset(tdata, 0x00, sizeof (tdata));
		libset(0, r);
		libread(tdata);

		if (memcmp(tdata, udata, 3) == 0) {
			memset(PUBLIC_VALUE, 0x00, sizeof(PUBLIC_VALUE));
			memset(tdata, 0x00, sizeof(tdata));
			libset(1, r);
			libread(tdata);
			memcpy(PUBLIC_VALUE, tdata, 6);
		}
	}
	//return *tdata;
			}
U8 BoWei_XuanZe(U8 *bw) {
	U8 kr, lgh;
	U8 i;
	U8 kdata[40], ndata[40];
	U8 total, items;    //  �ܼ��ж�����Ҫ��ʾ  ��Ļ���ö�������ʾ
	U16 sumr, sumf;
	U8 k, s;
	U8 mtotal;

	P_U8 menu[30] = { "1                   ", "2                   ", "3                   ", "4                   ", "5                   ", "6                   ", "7                   ",
			"8                   ", "9                   ", "10                  ", "11                  ", "12                  ", "13                  ", "14                  ",
			"15                  ", "16                  ", "17                  ", "18                  ", "19                  ", "20                  ", "21                  ",
			"22                  ", "23                  ", "24                  ", "25                  ", "26                  ", "27                  ", "28                  ",
			"29                  ", "30                  ", };
	mtotal = (sizeof (menu)) / sizeof(menu[0]);
	cls();
	//moveto( 1, 1 );
	//putstr( "��ǰ�û�:" );
	//putstr( AdminId );

	libopen(DBFNO_BOWEI);
	sumr = libsumr();
	sumf = libsumf();
	k = sumf - 2;				//	���Ƶ��û���λ��Ϣ
	s = sumf - 1;				//	��λ״̬

	for (i = 2; i < libsumr(); i++) {
		if ((i - 3) <= mtotal) {
			memset(ndata, 0x00, sizeof (ndata));
			memset(ndata, ' ', 20);
			libset(i, 0);				//	��λ��
					memset(kdata, 0x00, sizeof(kdata));
					libread(kdata);
					//if( (kdata[0]==0x00)||(kdata[0]==' ') )
					//{
					//	break;
					//	}
					memcpy(&(ndata[3]), kdata, BOWEI_W);

					libset(i, s);//	��λ״̬
					memset(kdata, 0x00, sizeof(kdata));
					libread(kdata);
					memcpy(&(ndata[11]), kdata, strlen(kdata));

					memcpy(menu[i - 3], ndata, 20);
				}
			}

	if ((i - 3) > mtotal) {
		total = mtotal;
	} else {
		total = (i - 3);
	}

	moveto(3, 1);
	putstr("����λ�š�  ��״̬��");
	//		|  0002        ����  |
	if (total < 7) {
		items = total;
	} else {
		items = 7;
	}
	k = display_menu(5, total, items, menu, &kr);
	if (kr == KEY_F2) {
		return BACK_YELLOW;
	} else if (kr == KEY_ENTER) {
		memcpy(bw, &(menu[k][3]), BOWEI_W);
	} else if ((kr >= '0') & (kr <= '9')) {
		moveto(1, 1);
		putstr_x("������:", 1);
		memset(kdata, 0x00, sizeof (kdata));
		kdata[0] = kr;
		lgh = ReadLine(kdata, 1, BOWEI_W, 0);
		if (lgh == 0) {
			return 0;
		} else {
			memcpy(bw, kdata, BOWEI_W);
			return 0;
		}
	}
	return 1;
}
void CheWei_ChaXun1(void) {
	Uchar8 kdata[30];
	Uchar8 CB_JUDLE, cb_cb;
	l1: memset(kdata, 0x00, sizeof (kdata));
	CB_JUDLE = BoWei_XuanZe(kdata);
	if (CB_JUDLE == BACK_YELLOW)
		return;

	//putstr( "\nѡ��λ:" );
	//putstr( kdata );
	//key(0);

	cb_cb = BoWei_ChaXun(kdata);
	if (cb_cb == BACK_TOTXY) {
		goto l1;
	}
}
U8 BoWei_ChaXun(U8 *bw) {
	//  r   0��ˮ�� 4����ʱ�� 5�뿪ʱ��
	U8 k, kr;
	//  U8 sum;
	U8 total, items;    //  �ܼ��ж�����Ҫ��ʾ  ��Ļ���ö�������ʾ
	U8 tdata[40];
	U8 gates[40];
	U8 mdata[40];
	U8 ndata[40];
	U8 outdata[40];     //����ʱ��
	Sint32 i, j, r;
	Sint32 y;
	TYPE_PARKINFO ParkInfo;

	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
	Uint16 index[20];   //  ��ѯ���ļ�¼��
	U8 mtotal;
	P_U8 menu[30] = { "1                   ", "2                   ", "3                   ", "4                   ", "5                   ", "6                   ", "7                   ",
			"8                   ", "9                   ", "10                  ", "11                  ", "12                  ", "13                  ", "14                  ",
			"15                  ", "16                  ", "17                  ", "18                  ", "19                  ", "20                  ", "21                  ",
			"22                  ", "23                  ", "24                  ", "25                  ", "26                  ", "27                  ", "28                  ",
			"29                  ", "30                  ", };
	mtotal = (sizeof (menu)) / sizeof(menu[0]);

	libopen(DBFNO_PARK);
	i = 0;
	for (j = libsumr() - 1; j >= 0; j--) {
		libset(j, LSH);
		memset(tdata, 0x00, sizeof (tdata));
		libread(tdata);

		libset(1, CZJ);
		memset(gates, 0x00, sizeof (gates));
		libread(gates);
		if (atoi(gates) == atoi(tdata)) {
			y = j;
			goto loopbreak;
		}
	}
	loopbreak: for (r = y; r >= 0; r--) {
		libset(r, BWH);
		memset(tdata, 0x00, sizeof (tdata));
		libread(tdata);
		if (memcmp(tdata, bw, BOWEI_W) == 0) {
			if (i <= mtotal) {
				libset(r, CHEPAI);                    //  ��������
				memset(ndata, 0x00, sizeof (ndata));
				libread(ndata);
				libset(r, JRSJ);
				memset(mdata, 0x00, sizeof (mdata));
				libread(mdata);
				libset(r, LKSJ);
				memset(outdata, 0x00, sizeof (outdata));
				libread(outdata);
				//memset( &(ndata[8]), ' ', 1 );
				memcpy(&(ndata[9]), &(mdata[11]), 5);
				memcpy(&(ndata[15]), &(outdata[11]), 5);
				ndata[14] = '_';
				memcpy(menu[i], ndata, 20);
				index[i] = r;
			}
			i++;
		}
	}

	if (i > mtotal) {
		total = mtotal;
	} else {
		total = i;
	}
	c_b: cls();
	moveto(1, 1);
	putstr(bw);
	putstr("�����");
	printf("%d", total);
	putstr("����¼");
	moveto(3, 1);
	putstr("�����ơ�������ʱ�䡿");
	//		|��A12345 09-11 12:34|
	if (total < 7) {
		items = total;
	} else {
		items = 7;
	}

	k = display_menu(5, total, items, menu, &kr);
	if (k == 0xFF) {
		return BACK_TOTXY;
	} else {
		memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
		c_b1: ParkInfo.r = index[k];                  //  �������ݿ��д�����¼����Ϣ
				libset(ParkInfo.r, CHEPAI);
				libread(ParkInfo.chepai);
				libset(ParkInfo.r, BWH);
				libread(ParkInfo.bwh);
				libset(ParkInfo.r, JRSJ);
				libread(ParkInfo.time_in);
				Change_DateTime_Style(0, ParkInfo.time_in);
				libset(ParkInfo.r, LKSJ);
				libread(ParkInfo.time_out);
				Change_DateTime_Style(0, ParkInfo.time_out);
				//          libset( ParkInfo.r, ZWSJ );
				//          libread( ParkInfo->time_disp );
				libset(ParkInfo.r, YSJE);
				libread(ParkInfo.charge_due);
				PInfo_Calcfree(&ParkInfo);
				CardInfo_Disp_print(&ParkInfo);
				if (key(0) == KEY_F2) {
					goto c_b;
				} else {
					Print_Bill(&ParkInfo);
					goto c_b1;
				}
			}
		}
void JIAOYANGTIME(Uchar8 *udata) {
	cls();
	Uchar8 timedata[20];
	memset(timedata, 0x00, sizeof (timedata));
	getdate(timedata);
	int int_result6 = 0;
	int_result6 = stoi(4, &(timedata[0]));

	int int_result5 = 0;
	int_result5 = stoi(4, &(udata[0]));
	int int_result = 0;
	int_result = stoi(2, &(udata[4]));

	int int_result1 = 0;
	int_result1 = stoi(2, &(udata[6]));

	int int_result2 = 0;
	int_result2 = stoi(2, &(udata[8]));

	int int_result3 = 0;
	int_result3 = stoi(2, &(udata[10]));

	int int_result4 = 0;
	int_result4 = stoi(2, &(udata[12]));

	if (int_result5 != int_result6 || int_result > 12 || int_result1 > 32 || int_result2 > 24 || int_result3 > 60 || int_result4 > 60) {
		// memset( PUBLIC_BOOLEN, 0x00, sizeof(PUBLIC_BOOLEN) );
		//memcpy( PUBLIC_BOOLEN,"123456", 6);
		PUBLIC_BOOLEN = 1;
	}
}

int GPRS_netconnect(void) {
	int cRet;
	//uchar ip[32];
	//uchar port[32];

	//putstr("���Ժ� ");
	cRet = WNetCont("1", "IP", "CMNET", "0,0");
	if (cRet == 0) {
		//putstr("ok");
	} else {
		putstr("����ʧ��\n");
		bell(100);
		libmitnub++;
		return 4;
	}
	//putstr("\n����IP���� ");

	//get_ip(ip);

	//get_port(port);

	cRet = WNetSeting("2", "5001", "111.1.31.40", "2999");
	if (cRet == 0) {
		//putch('\n');//putstr(ip);
		//putch(' ');//putstr(port);
	} else {
		putstr("��ʱ����");
		bell(100);
		cls();
		return 2;
	}

	//putstr("\n����ͨѶ��ʱ ");
	// cRet=WNetInit("512","1","60","6000");
	cRet = WNetInit("512", "1", "60", "6000");
	if (cRet == 0) {

		//putstr("ok");
	} else {
		//putstr("error");
		bell(100);
		return 2;
	}
	// putstr("\n��������");
	cRet = WNetConnect(1000);
	//	printf("%d",cRet);
	bell(100);
	//key(0);
	return 0;
}
/*
 **	���ƣ�	��������
 **	��ڣ�
 **	���أ�
 */
void Door_In_2(void) {
	cls();
	Uchar8 rt, lgh, cb;

	Uchar8 jmbz;
	Uchar8 kdata[40];
	Uchar8 bwhdata[40];

	//Uchar8 posdata[40];
	//Uchar8 liushuihao[10];
	TYPE_PARKINFO ParkInfo;
	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));

	while (1) {
		cls();
		memset(kdata, 0x00, sizeof (kdata));
		rt = IN_put_CHE_PAI(kdata);
		if (rt != 0)
			return;
		l1:

		cls();
		// putstr( "�����벴λ��\n" );
		//moveto(10,1);
		screen(2);
		putstr("���ƺ�:\n");

		putstr(kdata);
		screen(1);
		putstr("\n\n\n\n");
		putstr("�����벴λ��");

		memset(bwhdata, 0x00, sizeof (bwhdata));
		lgh = ReadLine(bwhdata, 0, 4, 1);

		if (lgh == 0) {
			if (bwhdata[1] == KEY_F2) {

				continue;
			} else {
				goto l1;
			}
		}
		//sprintf( tmpdata, "%d", posdata);
		//putstr( posdata);
		//key(0);
		memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
		memcpy(ParkInfo.bwh, bwhdata, CHEPAI_W);
		memset(ParkInfo.chepai, 0x00, sizeof (ParkInfo.chepai));
		memcpy(ParkInfo.chepai, kdata, CHEPAI_W);
		memset(ParkInfo.czy, 0x00, sizeof (ParkInfo.czy));        //����Ա����Ϣ
		memcpy(ParkInfo.czy, AdminId, 3);
		//memcpy( ParkInfo.pch, AdminPassId, 6 );
		jmbz = JMPD_DB(&ParkInfo);
		cb = ChaZhaoBw(&ParkInfo);

		if (jmbz == FLAG_IN) {
			ErrorMsg("�˳����ظ�");
			key(0);
			goto l1;
		}
		if (cb == FLAG_IN) {
			ErrorMsg("��λ��\n�ѱ�ռ��");
			key(0);
			goto l1;
		} else if (cb == FLAG_FOE) {
			ErrorMsg("�Ƿ���λ��");
			key(0);
			goto l1;
		}
		if (jmbz == FLAG_OUT) {
			memset(ParkInfo.time_in, 0x00, sizeof (ParkInfo.time_in));
			Get_DateTime(0, ParkInfo.time_in);

			libopen(DBFNO_PARK);
			G_Sjid = Sjuid_Read();

			if (libsumr() <= 3000) {
				libapp();
			}
			if (G_Sjid >= 3000) {
				G_Sjid = 0;
				ParkInfo.r = G_Sjid;
			} else {
				G_Sjid++;
				ParkInfo.r = G_Sjid;

			}
			Sjuid_Save(G_Sjid);

			G_FLOWNO = FlowNO_Read();
			G_FLOWNO++;
			ParkInfo.flowNO = G_FLOWNO;
			FlowNO_Save(G_FLOWNO);
			PInfo_Save(&ParkInfo);
			ParkInfo.flag = FLAG_IN;

			//Print_Bill( &ParkInfo );

					ErrorMsg("���ųɹ�");
					BWState_Ref(ParkInfo.bwh, FLAG_BUSY, ParkInfo.chepai);
					//GPRS_Link_init();
					//GPRS_SET1();
					//GPRS_netconnect();
					//
					//WNetConnect(2000);
					GPRS_netconnect();
					GPRS_Sendrcv(&ParkInfo);//������
					break;
				}
			}
	cls();
}

int GPRS_Sendrcv(TYPE_PARKINFO *ParkInfo) {
	unsigned short rlen;
	int cRet;
	//int CIRCLE_TIME=1;
	//Uchar8 sbuf[20];
	Uchar8 sbuf[200];
	Uchar8 kdata[40];
	Uchar8 tdata[40];
	Uchar8 tmpdata[20];
	//uchar k;
	//uchar k1;
	Uchar8 rt;
	Uint16 r;
	memset(sbuf, 0x00, 200);
	memset(tmpdata, 0x00, sizeof (tmpdata));
	cominit(B38400, 0x03, UART_ON);
	while (1) {
		cls();
		// WNetConnect(2000);
		putstr("\n���ڷ�������...\n");
		sbuf[0] = '0';
		memcpy(&(sbuf[1]), ParkInfo->chepai, 9);

		memcpy(&(sbuf[10]), ParkInfo->bwh, 4);
		memcpy(&(sbuf[14]), ParkInfo->time_in, 14);
		memcpy(&(sbuf[28]), AdminId, 3);
		memcpy(&(sbuf[31]), AdminPassId, 6);

		memset(kdata, 0x00, sizeof (kdata));
		sprintf(kdata, "%06d", ParkInfo->flowNO);

		memcpy(&(sbuf[37]), kdata, 6);

		memcpy(&(sbuf[43]), posiddata, 32);
		memcpy(&(sbuf[75]), "1", 1);

		cRet = WNetTxd(sbuf, 76);
		if (cRet == 0) {
			memset(tdata, 0x00, sizeof (tdata));
			rt = WNetRxd(tdata, &rlen, 2000);
			if (rt == 0) {
				memcpy(tdata, &(tdata[0]), 1);

				if (tdata[0] == '1') {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "1", 1);    //����ʧ��
					libset(r, SCCG);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("���ͳɹ�\n");
					WNetIPClose("1", 1000);

					putstr("�����������\n");
					key(0);
					return 1;
				}

				else {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "2", 1);    //���ųɹ�
					libset(r, SCCG);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("����ʧ��\n");

					WNetIPClose("1", 1000);
					putstr("�����������\n");

					key(0);
					return 1;

				}
			} else {
				libopen(DBFNO_PARK);
				r = ParkInfo->r;
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, "2", 1);    //���ųɹ�
				libset(r, SCCG);//���ű�־  0˵������ʧ��
				libwrite(kdata);
				putstr("����ʧ��\n");

				WNetIPClose("1", 1000);
				putstr("�����������\n");

				key(0);
				return 1;
			}
		} else {
			libopen(DBFNO_PARK);
			r = ParkInfo->r;
			memset(kdata, 0x00, sizeof(kdata));
			memcpy(kdata, "2", 1);    //���ųɹ�
			libset(r, SCCG);//���ű�־  0˵������ʧ��
			libwrite(kdata);
			putstr("����ʧ��\n");

			WNetIPClose("1", 1000);
			putstr("�����������\n");
			key(0);
			return 1;
		}
	}
}
void Door_Out_2(void) {
	Uchar8 k, lgh;
	Uchar8 jmbz;
	Uchar8 kdata[40];
	int cccbbb;
	TYPE_PARKINFO ParkInfo;
	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
	cls();
	while (1) {
		cls();
		moveto(1, 1);
		memset(kdata, 0x00, sizeof (kdata));
		putstr("�����벴λ��:");
		lgh = ReadLine(kdata, 0, 4, 1);
		if (lgh == 0) {
			if (kdata[1] == KEY_F2) {
				return;
			} else {
				continue;
			}
		}

		memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
		memcpy(ParkInfo.bwh, kdata, 4);
		jmbz = ChaZhaoBw(&ParkInfo);    //�ж��Ƿ�Ϊ����
		if (jmbz == FLAG_IN) {
			memset(ParkInfo.time_out, 0x00, sizeof (ParkInfo.time_out));
			Get_DateTime(0, ParkInfo.time_out);
			cccbbb = PInfo_Calcfree(&ParkInfo);
			CardInfo_Disp1(&ParkInfo);

			clsn(17, 4);
			moveto(17, 1);
			putstr("[ȷ��] ����(��ӡ)");
			//putstr( "\n[����] ����(����ӡ)" );

					k = key(0);
					while (k == KEY_ENTER) {

						OutPInfo_Save(&ParkInfo);
						ParkInfo.flag = FLAG_OUT;

						if (cccbbb != 1) {
							Print_Bill(&ParkInfo);
						}

						ErrorMsg("���ųɹ�");
						BWState_Ref(ParkInfo.bwh, FLAG_FREE, ParkInfo.chepai);

						GPRS_netconnect();

						GPRS_OutSendrcv(&ParkInfo);    //������

						break;
					}
				} else {
					ErrorMsg("�˳�δ����");
					key(0);
					continue;
				}
			}
		}
int GPRS_OutSendrcv(TYPE_PARKINFO *ParkInfo) {
	int cRet;
	Uchar8 sbuf[200];
	Uint16 r;
	//int CIRCLE_TIME2=1;
	//Uchar8 tmpdata[20];
	//Uchar8 cmddata[20];
	unsigned short rlen;
	//Uchar8 tmpdata[20];
	Uchar8 rt;

	Uchar8 tdata[40];
	Uchar8 timeindata[40];

	//Uchar8 tmpdata[20];
	Uchar8 kdata[40];
	//Uchar8 tmpdata[20];
	//uchar k;
	//uchar k1;
	memset(sbuf, 0x00, 200);

	cominit(B38400, 0x03, UART_ON);
	while (1) {
		cls();
		putstr("\n���ڷ�������...\n");
		sbuf[0] = '1';
		memcpy(&(sbuf[1]), ParkInfo->chepai, 9);
		memcpy(&(sbuf[10]), ParkInfo->bwh, 4);
		memcpy(&(sbuf[14]), ParkInfo->time_out, 14);

		memcpy(&(sbuf[28]), AdminId, 3);
		memcpy(&(sbuf[31]), AdminPassId, 6);

		memset(kdata, 0x00, sizeof (kdata));
		sprintf(kdata, "%06d", ParkInfo->flowNO);

		memcpy(&(sbuf[37]), kdata, 6);
		memcpy(&(sbuf[43]), posiddata, 32);
		memcpy(&(sbuf[75]), "1", 1);
		memcpy(&(sbuf[76]), "1", 1);
		memcpy(&(sbuf[77]), ParkInfo->charge_due, 5);

		cRet = WNetTxd(sbuf, 87);
		if (cRet == 0) {
			memset(tdata, 0x00, sizeof (tdata));
			memset(timeindata, 0x00, sizeof(timeindata));

			rt = WNetRxd(tdata, &rlen, 2000);
			if (rt == 0) {
				memcpy(tdata, &(tdata[0]), 1);

				if (tdata[0] == '1') {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "1", 1);    //����ʧ��
					libset(r, BCZTW);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("���ͳɹ�\n");
					WNetIPClose("1", 1000);

					putstr("�����������\n");
					key(0);
					return 1;
				} else {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "2", 1);    //����ʧ��
					libset(r, BCZTW);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("����ʧ��\n");
					WNetIPClose("1", 1000);
					//WNetClose(1000);
					putstr("�����������\n");
					key(0);
					return 1;
				}
			} else {
				libopen(DBFNO_PARK);
				r = ParkInfo->r;
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, "2", 1);    //����ʧ��
				libset(r, BCZTW);//���ű�־  0˵������ʧ��
				libwrite(kdata);
				putstr("����ʧ��\n");
				WNetIPClose("1", 1000);
				//WNetClose(1000);
				putstr("�����������\n");
				key(0);
				return 1;
			}
		} else {
			libopen(DBFNO_PARK);
			r = ParkInfo->r;
			memset(kdata, 0x00, sizeof(kdata));
			memcpy(kdata, "2", 1);    //����ʧ��
			libset(r, BCZTW);//���ű�־  0˵������ʧ��
			libwrite(kdata);
			putstr("����ʧ��\n");
			WNetIPClose("1", 1000);
			//WNetClose(1000);
			putstr("�����������\n");
			key(0);
			return 1;
		}
	}
}

			/*
			 **	���ƣ�
			 **	��ڣ�	FLAG_IN:��ѯ��ʾ FLAG_OUT:���Ž�����ʾ
			 **	���أ�  ��ʾ��ļ��̲���
			 ��ѯ��ʾ
			 ������˳�

			 ������ʾ����ʱ�˳���
			 ȷ�ϼ����Ž��㣨��ʾ���ųɹ���
			 ������˳�


			 ����ʾֻ��ʾ��������Ϣ����������ID�ͽ���ʱ��
			 ����������Ϣ����ص���Ϣ������Ϊ

			 */
void CardInfo_Disp(TYPE_PARKINFO *ParkInfo) {
	//	Uchar8 kdata[16];
	Uchar8 cdata[40];

	screen(1);
	cls();
	//	moveto( 1, 1 );
	//	putstr( "����:" );
	//	putn_h( USERID_W, ParkInfo->userID );
	moveto(5, 1);
	putstr("���ƺ�:");
	putstr(ParkInfo->chepai);
	moveto(7, 1);
	putstr("��λ:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_in, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));
	putstr("\n�뿪:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_out, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));

	putstr("\nռλ:");
	putstr(ParkInfo->time_disp);
	putstr("\nӦ��:");
	putstr(ParkInfo->charge_due);
	putstr("Ԫ");
	if (ParkInfo->charge_due == 0) {

	}
	//moveto( 10, 5 );
	// putstr( "���Ƿ��ӡ����" );
	//moveto( 15, 4 );
	//putstr( "�������������ӡ" );
	//	moveto( 17, 4 );
	//putstr( "����F2��ȡ��" );

}
int CardInfo_Disp1(TYPE_PARKINFO *ParkInfo) {
	//	Uchar8 kdata[16];
	Uchar8 cdata[40];

	screen(1);
	cls();
	//	moveto( 1, 1 );
	//	putstr( "����:" );
	//	putn_h( USERID_W, ParkInfo->userID );
	moveto(5, 1);
	putstr("���ƺ�:");
	putstr(ParkInfo->chepai);
	moveto(7, 1);
	putstr("��λ:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_in, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));
	putstr("\n�뿪:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_out, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));

	putstr("\nռλ:");
	putstr(ParkInfo->time_disp);
	putstr("\nӦ��:");
	putstr(ParkInfo->charge_due);
	putstr("Ԫ");
	if (ParkInfo->charge_due == 0) {

		return 1;
	} else {
		return 0;
	}
	//moveto( 10, 5 );
	// putstr( "���Ƿ��ӡ����" );
	//moveto( 15, 4 );
	//putstr( "�������������ӡ" );
	//	moveto( 17, 4 );
	//putstr( "����F2��ȡ��" );

}
void CardInfo_Disp_print(TYPE_PARKINFO *ParkInfo) {
	//	Uchar8 kdata[16];
	Uchar8 cdata[40];

	screen(1);
	cls();
	//	moveto( 1, 1 );
	//	putstr( "����:" );
	//	putn_h( USERID_W, ParkInfo->userID );
	moveto(2, 1);
	putstr("���ƺ�:");
	putstr(ParkInfo->chepai);
	moveto(4, 1);
	putstr("��λ:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_in, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));
	putstr("\n�뿪:");
	memset(cdata, 0x00, sizeof (cdata));
	memcpy(cdata, ParkInfo->time_out, 14);
	Change_DateTime_Style(1, cdata);
	putn_h(14, &(cdata[2]));

	putstr("\nռλ:");
	putstr(ParkInfo->time_disp);
	putstr("\nӦ��:");
	putstr(ParkInfo->charge_due);
	putstr("Ԫ");
	moveto(14, 3);
	putstr("���Ƿ��ӡ����");
	moveto(16, 2);
	putstr("�������������ӡ");
	moveto(18, 2);
	putstr("����F2��ȡ��");

}

/*
 **	���ƣ�	��ĳһ�����Ϣ
 **	��ڣ�	������ţ����ݴ�Ż���
 **	���أ�	����״̬����
 **	˵����	������������ݿ���󣬻��������Ƿ�������Ӧ��ʾ�������ش���ֵ
 */
Uchar8 Block_Read(Uchar8 Block_NO, Uchar8 *RD_Buffer) {
	return (mif_read(Block_NO, RD_Buffer));
}

Uchar8 Block_Write(Uchar8 Block_NO, Uchar8 *WR_Buffer) {
	return (mif_write(Block_NO, WR_Buffer));
}

Uchar8 Block_ProRead(Uchar8 Block_NO, Uchar8 RD_NO, Uchar8 *RD_Buffer) {
	return 0;
}

Uchar8 Block_ProWrite(Uchar8 Block_NO, Uchar8 WR_NO, Uchar8 *WR_Buffer) {
	return 0;
}
/*
 **	���ƣ�	�����ж�_���ݱ�־λ�������汾��
 **	��ڣ�	�ޣ���ǰ����
 **	���أ�	FLAG_IN/FLAG_OUT/FLAG_FOE
 **	˵����	�˴��ϸ��жϣ�����ʱֻҪ����FLAG_IN�������š�
 */
Uchar8 JMPD_Flag(TYPE_PARKINFO *ParkInfo) {
	if (memcmp(ParkInfo->version, G_USER_VER, 2) == 0) {
		if (ParkInfo->flag == FLAG_IN)
			return FLAG_IN;
		else
			return FLAG_OUT;
	} else {
		return FLAG_FOE;
	}
}
/*
 **	���ƣ�	�����ж�_�������ݿ�����
 **	��ڣ�	����/����
 **	���أ�	FLAG_IN(���ΪIN��rָ����Ӧ��¼,��ˮ�ŷ���)/FLAG_OUT
 **	��ע��	���ݿ��ȡ��������Ŀո�ע��strlen��length��Ӧ������
 */
Uchar8 JMPD_DB(TYPE_PARKINFO *ParkInfo) {
	//	Uchar8 rt;
	Uchar8 kdata[40];
	Sint32 last, r;									//	���ݿ��п���Ϊ�գ���ʱlast����Ϊ����

	/*	���жϽ���ʱ��
	 ���ж��뿪ʱ���Ƿ�Ϊ��
	 ���жϿ���/����
	 */
	libopen(DBFNO_PARK);
	last = libsumr() - 1;

	for (r = last; r >= 0; r--) {
		memset(kdata, 0x00, sizeof (kdata));
		libset(r, CHEPAI);
		libread(kdata);
		if (memcmp(ParkInfo->chepai, kdata, strlen(ParkInfo->chepai)) == 0)									//	���ݿ��ȡ��������Ŀո������ȡkdata���ȱ�����length
				{
					memset(kdata, 0x00, sizeof(kdata));
					libset(r, LKSJ);
					libread(kdata);
					if ((kdata[0] < 0x30) | (kdata[0] > 0x39))									//	δ����
					{
						{
							ParkInfo->r = r;			//	break�󵽴�˴������ż�¼����
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, LSH);
							libread(kdata);
							ParkInfo->flowNO = atoi(kdata);
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, JRSJ);
							libread(kdata);
							Change_DateTime_Style(0, kdata);
							memcpy(ParkInfo->time_in, kdata, 14);
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, BWH);
							libread(kdata);
							memcpy(ParkInfo->bwh, kdata, 14);
							break;
						}
					}
				}
			}

	if (r < 0)
		return FLAG_OUT;							//	����δ����
	else
		return FLAG_IN;
}

/*
 **	���ƣ�	���Ÿ�������
 **	��ڣ�	ͣ�����ݣ��ϲ����Ӧ��ָ���ô洢�ļ�¼����
 **	���أ�	�ޣ�����ֻ��������ڴ��еĿɿ����ģ�M1���ĸ��ġ�У��Ƚ�������������
 */
void PInfo_Save(TYPE_PARKINFO *ParkInfo) {
	Uchar8 kdata[40];
	Uint16 r;
	//	memcpy( ParkInfo->POSID_in, G_POSID, POSID_W );
	//	memcpy( ParkInfo->operator_in, G_POSID, POSID_W );
	libopen(DBFNO_PARK);
	r = ParkInfo->r;

	memset(kdata, 0x00, sizeof (kdata));
	sprintf(kdata, "%06d", ParkInfo->flowNO);
	libset(r, LSH);
	libwrite(kdata);

	libset(1, CZJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "1", 1);    //
	libset(r, PCH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->chepai, strlen(ParkInfo->chepai));
	libset(r, CHEPAI);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->bwh, strlen(ParkInfo->bwh));
	libset(r, BWH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminId, strlen(AdminId));    //�޸ĵ�
	libset(r, CZY);
	libwrite(kdata);

	//	libset( r, CHEPAI );
	//	libwrite( ParkInfo->chepai );

	//	libset( r, YHKH );
	//	libwrite( ParkInfo->userID );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_in, strlen(ParkInfo->time_in));
	Change_DateTime_Style(1, kdata);
	libset(r, JRSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_out, strlen(ParkInfo->time_out));
	Change_DateTime_Style(1, kdata);
	libset(r, LKSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminPassId, strlen(AdminPassId));
	//Change_DateTime_Style( 1, kdata );
	libset(r, CLX);
	libwrite(kdata);

	//	libset( r, ZWSJ );
	//	libwrite( ParkInfo->time_disp );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->charge_due, strlen(ParkInfo->charge_due));
	libset(r, YSJE);
	libwrite(kdata);
	//	libset( r, SSJE );
	//	libwrite( ParkInfo->charge_real );

}
void BudanPInfo_Save(TYPE_PARKINFO *ParkInfo) {
	Uchar8 kdata[40];
	Uint16 r;

	//	memcpy( ParkInfo->POSID_in, G_POSID, POSID_W );
	//	memcpy( ParkInfo->operator_in, G_POSID, POSID_W );
	libopen(DBFNO_PARK);
	r = ParkInfo->r;
	memset(kdata, 0x00, sizeof (kdata));
	sprintf(kdata, "%06d", ParkInfo->flowNO);
	libset(r, LSH);
	libwrite(kdata);

	libset(1, CZJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "2", 1);    //
	libset(r, PCH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->chepai, strlen(ParkInfo->chepai));
	libset(r, CHEPAI);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->bwh, strlen(ParkInfo->bwh));
	libset(r, BWH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminId, strlen(AdminId));    //�޸ĵ�
	libset(r, CZY);
	libwrite(kdata);

	//	libset( r, CHEPAI );
	//	libwrite( ParkInfo->chepai );

	//	libset( r, YHKH );
	//	libwrite( ParkInfo->userID );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_in, strlen(ParkInfo->time_in));
	Change_DateTime_Style(1, kdata);
	libset(r, JRSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_out, strlen(ParkInfo->time_out));
	Change_DateTime_Style(1, kdata);
	libset(r, LKSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminPassId, strlen(AdminPassId));
	//Change_DateTime_Style( 1, kdata );
	libset(r, CLX);
	libwrite(kdata);

	//	libset( r, ZWSJ );
	//	libwrite( ParkInfo->time_disp );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->charge_due, strlen(ParkInfo->charge_due));
	libset(r, YSJE);
	libwrite(kdata);
	//	libset( r, SSJE );
	//	libwrite( ParkInfo->charge_real );

}

void taodanPInfo_Save(TYPE_PARKINFO *ParkInfo) {
	Uchar8 kdata[40];

	Uint16 r;

	//	memcpy( ParkInfo->POSID_in, G_POSID, POSID_W );
	//	memcpy( ParkInfo->operator_in, G_POSID, POSID_W );

	libopen(DBFNO_PARK);

	r = ParkInfo->r;

	memset(kdata, 0x00, sizeof (kdata));
	sprintf(kdata, "%06d", ParkInfo->flowNO);
	libset(r, LSH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "2", 1);    //�ӵ�ʧ��   ����ʧ��
	libset(r, TCD);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->chepai, strlen(ParkInfo->chepai));
	libset(r, CHEPAI);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->bwh, strlen(ParkInfo->bwh));
	libset(r, BWH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminId, strlen(AdminId));    //�޸ĵ�
	libset(r, BCCZY);
	libwrite(kdata);

	//	libset( r, CHEPAI );
	//	libwrite( ParkInfo->chepai );

	//	libset( r, YHKH );
	//	libwrite( ParkInfo->userID );

	//libset( r, CZJ );
	//libwrite( G_POSID );

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_in, strlen(ParkInfo->time_in));
	Change_DateTime_Style(1, kdata);
	libset(r, JRSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_out, strlen(ParkInfo->time_out));
	Change_DateTime_Style(1, kdata);
	libset(r, LKSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminPassId, strlen(AdminPassId));
	//Change_DateTime_Style( 1, kdata );
	libset(r, BCCZYMM);
	libwrite(kdata);

	//	libset( r, ZWSJ );
	//	libwrite( ParkInfo->time_disp );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->charge_due, strlen(ParkInfo->charge_due));
	libset(r, YSJE);
	libwrite(kdata);

	//	memset( taodandata, 0x00, sizeof(taodandata) );
	// memcpy( taodandata, "T", 1 );//�ӵ�ʧ��   ����ʧ��
	//libset( r, CZJ );//���ű�־  0˵������ʧ��

	// libwrite( taodandata );
	//	libset( r, SSJE );
	//	libwrite( ParkInfo->charge_real );

}
void OutPInfo_Save(TYPE_PARKINFO *ParkInfo) {
	Uchar8 kdata[40];
	Uint16 r;

	//	memcpy( ParkInfo->POSID_in, G_POSID, POSID_W );
	//	memcpy( ParkInfo->operator_in, G_POSID, POSID_W );

	libopen(DBFNO_PARK);

	r = ParkInfo->r;

	memset(kdata, 0x00, sizeof (kdata));
	sprintf(kdata, "%06d", ParkInfo->flowNO);
	libset(r, LSH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "1", 1);    //����ʧ��  ����ʧ��
	libset(r, TCD); //���ű�־  0˵������ʧ��
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->chepai, strlen(ParkInfo->chepai));
	libset(r, CHEPAI);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->bwh, strlen(ParkInfo->bwh));
	libset(r, BWH);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminId, strlen(AdminId)); //�޸ĵ�
	libset(r, BCCZY);
	libwrite(kdata);

	//	libset( r, CHEPAI );
	//	libwrite( ParkInfo->chepai );

	//	libset( r, YHKH );
	//	libwrite( ParkInfo->userID );

	//libset( r, CZJ );
	//libwrite( G_POSID );

	//memset( kdata, 0x00, sizeof(kdata) );
	//	memcpy( kdata, ParkInfo->time_in, strlen(ParkInfo->time_in) );
	//Change_DateTime_Style( 1, kdata );
	//libset( r, JRSJ );
	//libwrite( kdata );

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_out, strlen(ParkInfo->time_out));
	Change_DateTime_Style(1, kdata);
	libset(r, LKSJ);
	libwrite(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, AdminPassId, strlen(AdminPassId));
	//Change_DateTime_Style( 1, kdata );
	libset(r, BCCZYMM);
	libwrite(kdata);

	//	libset( r, ZWSJ );
	//	libwrite( ParkInfo->time_disp );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->charge_due, strlen(ParkInfo->charge_due));
	libset(r, YSJE);
	libwrite(kdata);
	//	libset( r, SSJE );
	//	libwrite( ParkInfo->charge_real );

}

void PFlag2OUT(TYPE_PARKINFO *ParkInfo) {
	memcpy(ParkInfo->version, G_USER_VER, 2);
	ParkInfo->flag = FLAG_OUT;
}

void PFlag2IN(TYPE_PARKINFO *ParkInfo) {
	memcpy(ParkInfo->version, G_USER_VER, 2);
	ParkInfo->flag = FLAG_IN;
}

Sint32 POSID_Read(Uchar8 *s) {
	return (EEROM_read(EPR_POSID, POSID_W, s));
}
Sint32 POSID_Save(Uchar8 *s) {
	return (EEROM_write(EPR_POSID, POSID_W, s));
}

Uint16 FlowNO_Read(void) {
	Uchar8 kdata[8];

	EEROM_read(EPR_FLOWNO, 2, kdata);
	return *((Uint16 *) kdata);
}

void FlowNO_Save(Uint16 FlowNO) {
	EEROM_write(EPR_FLOWNO, 2, (Uchar8 *) (&FlowNO));
}
Uint16 Sjuid_Read(void) {
	Uchar8 kdata[8];

	EEROM_read(EPR_SJID, 2, kdata);
	return *((Uint16 *) kdata);
}

void Sjuid_Save(Uint16 cb) {
	EEROM_write(EPR_SJID, 2, (Uchar8 *) (&cb));
}

/*
 **	���ƣ�	���ڸ�ʽ�޸�
 **	��ڣ�	c==0: �������ڸ�ʽ c==1:��չ���ڸ�ʽ
 **	���أ�	��
 */
void Change_Date_Style(Uchar8 c, Uchar8 *s) {
	Uchar8 kdata[32] = { 0 };
	if (c == 0) {
		kdata[0] = s[0];
		kdata[1] = s[1];
		kdata[2] = s[2];
		kdata[3] = s[3];
		kdata[4] = s[5];
		kdata[5] = s[6];
		kdata[6] = s[8];
		kdata[7] = s[9];
		kdata[8] = 0x00;
	} else {
		kdata[0] = s[0];
		kdata[1] = s[1];
		kdata[2] = s[2];
		kdata[3] = s[3];
		kdata[4] = '-';
		kdata[5] = s[4];
		kdata[6] = s[5];
		kdata[7] = '-';
		kdata[8] = s[6];
		kdata[9] = s[7];
		kdata[10] = 0x00;
	}
	memcpy(s, kdata, strlen(kdata));

}
/*
 **	���ƣ�	ʱ���ʽ�޸�
 **	��ڣ�	c==0:����ʱ���ʽ c==1:��չʱ���ʽ
 **	���أ�	��
 */
void Change_Time_Style(Uchar8 c, Uchar8 *s) {
	Uchar8 kdata[32] = { 0 };
	if (c == 0) {
		kdata[0] = s[0];
		kdata[1] = s[1];
		kdata[2] = s[3];
		kdata[3] = s[4];
		kdata[4] = s[6];
		kdata[5] = s[7];
		kdata[6] = 0x00;
	} else {
		kdata[0] = s[0];
		kdata[1] = s[1];
		kdata[2] = ':';
		kdata[3] = s[2];
		kdata[4] = s[3];
		kdata[5] = ':';
		kdata[6] = s[4];
		kdata[7] = s[5];
		kdata[8] = 0x00;
	}
	memcpy(s, kdata, strlen(kdata));

}
/*
 **	���ƣ�	����ʱ���ʽ�޸�
 **	��ڣ�	c==0:��������ʱ���ʽ c==1:��չ����ʱ���ʽ
 **	���أ�	��
 */
void Change_DateTime_Style(Uchar8 c, Uchar8 *s) {
	Uchar8 kdata[32] = { 0 };

	if (c == 0) {
		kdata[0] = s[0];		//	y
		kdata[1] = s[1];		//	y
		kdata[2] = s[2];		//	y
		kdata[3] = s[3];		//	y
		kdata[4] = s[5];		//	m
		kdata[5] = s[6];		//	m
		kdata[6] = s[8];		//	d
		kdata[7] = s[9];		//	d
		kdata[8] = s[11];		//	h
		kdata[9] = s[12];		//	h
		kdata[10] = s[14];		//	m
		kdata[11] = s[15];		//	m
		kdata[12] = s[17];		//	s
		kdata[13] = s[18];		//	s
		kdata[14] = 0x00;
	} else {
		kdata[0] = s[0];		//	y
		kdata[1] = s[1];		//	y
		kdata[2] = s[2];		//	y
		kdata[3] = s[3];		//	y
		kdata[4] = '-'; 		//	-
		kdata[5] = s[4];		//	m
		kdata[6] = s[5];		//	m
		kdata[7] = '-'; 		//	-
		kdata[8] = s[6];		//	d
		kdata[9] = s[7];		//	d
		kdata[10] = ' ';		//	Space
		kdata[11] = s[8];		//	h
		kdata[12] = s[9];		//	h
		kdata[13] = ':';		//	:
		kdata[14] = s[10];		//	m
		kdata[15] = s[11];		//	m
		kdata[16] = ':';		//	:
		kdata[17] = s[12];		//	s
		kdata[18] = s[13];		//	s
		kdata[19] = 0x00;
	}
	memcpy(s, kdata, strlen(kdata));
}

/*
 **	���ƣ�	ȡ��ǰ����ʱ�䣨��ʽ���裩
 **	��ڣ�	c==0:��������ʱ���ʽ c==1:��չ����ʱ���ʽ tdata:����ʱ����λ��ָ��
 **	���أ�	��
 */
void Get_DateTime(Uchar8 c, Uchar8 *tdata) {
	Uchar8 cdata[40] = { 0 };

	getdate(cdata);
	cdata[10] = ' ';
	gettime(&(cdata[11]));
	Change_DateTime_Style(0, cdata);
	if (c == 1)									//	ϵͳʱ��ļ��Ϊ"-"����Ҫ���Ϊ":"��
			{
		Change_DateTime_Style(1, cdata);
		memcpy(tdata, cdata, 19);		//	���ȷ��Ŀ��ָ���ڴ����㹻�ռ䣬����ӽ�����0x00��������ӡ�
	} else {
		memcpy(tdata, cdata, 14);
	}
}

/*
 **  ���ƣ�	�����ж�
 **  ��ڣ�	ʶ�����ָ��
 **  ���أ�	�����ַ������� �����ո����0x00��ֹ
 */
Uint16 length(Uchar8 *s) {
	Uint16 i = 0;
	while (1) {
		if (s[i] == 0x00 || s[i] == ' ') {
			break;
		} else if (i > 100) {
			i = 50;
			break;
		}
		i++;
	}
	return i;
}

void ErrorMsg(Uchar8 *Err) {
	cls();
	moveto(10, 1);
	screen(2);
	putstr(Err);
	screen(1);
	bell(100);
	delay(250);
	delay(250);
}

/*
 **	���ƣ�	�����ж�
 **	��ڣ�	��ʾ��ݵ�ASCII����
 **	���أ�	0:ƽ��	1:����
 */
Uchar8 LeapYear(Sint16 year) {
	return ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
}

/*
 **	���ƣ�	ͣ��ʱ�����
 **	��ڣ�	intime:����ʱ�䣨14λ����ʱ���ʽyyyymmddhhmmss��
 **			outtime:�뿪ʱ�䣨14λ����ʱ���ʽ��
 **			ptimedisp	ʱ��Ϊ�����ĸ�ʽ�����졢����Сʱ�����ٷ֡������룬���ļ����÷��Ӽ��㡣
 **			time_minute:ռλʱ����ָ�루*****ʱ**�֣����ٶ���λ��
 **	���أ�	ռλ���ܷ�����
 **	˵����	�˺�����ڽ��ǽ��롢�뿪ʱ�䣬���漰���ݿ������ѡ�ĸ�ʱ��Ӧ������ĺ���������
 */
int PInfo_Calc(TYPE_PARKINFO *ParkInfo) {
	Sint32 s_in, s_out, s_ds, s_ns;
	Sint32 s_out_in, s_ds_in, s_ns_in, s_out_ns, s_out_ds;
	Sint32 s_free;
	Sint32 gap_nums;
	Uchar8 i;
	Uchar8 state;
	//	Uchar8 kdata[40];
	Uchar8 rdata[40], tdata[40];
	Sint32 k[4];
	Sint32 kk, j;
	TYPE_TIMESPAN ts;
#if DEBUG
	Uchar8 xb;
	Uchar8 ll[10];
#endif

	/*	�������ʱ���	*/
	memset((Uchar8 *) (&ts), 0x00, sizeof (ts));
	memcpy(ts.begin, (ParkInfo->time_in), 14);
	memcpy(ts.end, (ParkInfo->time_out), 14);
	TimeSpan_Calc(&ts);												//	ʱ������
	memset(ParkInfo->time_disp, 0x00, sizeof (ParkInfo->time_disp));
	memcpy(ParkInfo->time_disp, ts.time_disp, strlen(ts.time_disp));												//	����ʱ���Ŀɶ�����

	//	���Ʒѡ�
	PRate_Read(ParkInfo);
	s_free = (atoi(ParkInfo->step0)) * 60;								//	���ʱ��
	memset(ParkInfo->charge_due, 0x00, sizeof (ParkInfo->charge_due));
	memset(ParkInfo->charge_real, 0x00, sizeof (ParkInfo->charge_real));
	memcpy(ParkInfo->charge_due, "0\0", 2);
	memcpy(ParkInfo->charge_real, "0\0", 2);

	/*	�����ʱ�䴦��	*/
	gap_nums = ((ts.hours * 60 + ts.minutes) * 60) + ts.seconds;
	if ((ts.days == 0) & (gap_nums <= s_free)) {
		int FREE_TCshoufei = 1;
		return FREE_TCshoufei;
	}

	/*	��ռλʱ��β������15������ȥ��	*/
	gap_nums = ((ts.minutes) * 60) + ts.seconds;
	if (gap_nums <= (15 * 60)) {
		ts.seconds = 0;
		ts.minutes = 0;
		Time_Offset(&ts);
		TimeSpan_Calc(&ts);											//	ʱ������
	}

	/*	���������շѶ�	*/
	memset(rdata, 0x00, sizeof (rdata));
	memcpy(rdata, "01", 2);
	strmul(ParkInfo->rate1, rdata, P_MONEY_W);						//	��1Сʱ�շ�

	memset(tdata, 0x00, sizeof (tdata));
	memcpy(tdata, "03", 2);
	strmul(ParkInfo->rate2, tdata, P_MONEY_W);						//	��3Сʱ�շ�

	stradd(tdata, rdata, P_MONEY_W);								//	��������շ�

	memset(tdata, 0x00, sizeof (tdata));
	itos(ts.days, tdata);
	strmul(tdata, rdata, P_MONEY_W);									//	���շ���
	memcpy(ParkInfo->charge_due, rdata, P_MONEY_W);						//	д��Ӧ��

	/*	ȡ���롢�뿪����ʼҹ�ա�ҹʼ���յľ�������	*/
	s_in = ts.begin_s;
	s_out = ts.end_s;		//	ע�⣺���������β��ȡ�ᴦ����ֵ���ܷ�ʵ��ֵ

	s_ds = stoi(2, &(ParkInfo->step1[0]));				//	ʱ
	s_ds = stoi(2, &(ParkInfo->step1[2])) + s_ds * 60;		//	ʱ+��
	s_ds = stoi(2, &(ParkInfo->step1[4])) + s_ds * 60;	//	ʱ+��+�� ��ʼʱ����һ���еľ�������
	s_ns = stoi(2, &(ParkInfo->step2[0]));				//	ʱ
	s_ns = stoi(2, &(ParkInfo->step2[2])) + s_ns * 60;
	;		//	ʱ+��
	s_ns = stoi(2, &(ParkInfo->step2[4])) + s_ns * 60;
	;		//	ʱ+��+�� ҹʼʱ����һ���еľ�������

	/*	�������ʱ���	*/
	s_out_in = s_out - s_in;			//	�뿪ʱ�������ʱ���
	if (s_out_in < 0)
		s_out_in += 24 * 60 * 60;		//	�˴���days�ѽ���������ݿ��ǽ�ȥ����s_in>s_outʱ�����ټ�

	s_ds_in = s_ds - s_in;				//	��ʼʱ�������ʱ���
	if (s_ds_in < 0)
		s_ds_in += 24 * 60 * 60;

	s_ns_in = s_ns - s_in;				//	ҹʼʱ�������ʱ���
	if (s_ns_in < 0)
		s_ns_in += 24 * 60 * 60;

	s_out_ds = s_out - s_ds;
	if (s_out_ds < 0)
		s_out_ds += 24 * 60 * 60;

	s_out_ns = s_out - s_ns;
	if (s_out_ns < 0)
		s_out_ns += 24 * 60 * 60;

	/*	��ʱ���������Ϊ����ļ�����׼����
	 ƫ�ƻ�δ����������ʱ��ȥ������
	 һ�����飬0Ϊs_in_ds��1Ϊ��ӽ���ֵ
	 */
	k[0] = 0;							//	min����
	k[1] = s_out_in;
	k[2] = s_ds_in;				//	���ds��ns���Ӧȷ��ns��ǰ�棬ҹʼ���պ���ʼҹ�գ�����������ʼ��㣨Сʱ��λ����
	k[3] = s_ns_in;

	for (i = 0; i < 4; i++)				//	����
			{
		if (k[2] < k[1]) {
			kk = k[1];
			k[1] = k[2];
			k[2] = kk;
		}
		if (k[3] < k[2]) {
			kk = k[2];
			k[2] = k[3];
			k[3] = kk;
		}
	}

	/*	�������շѼ���	*/
	kk = 0;							//	�����������������ȥ
	for (i = 0; i < 3; i++)				//	��ʼ����
			{
		j = k[i + 1] - k[i];
		state = Get_State(s_ds, s_ns, (k[i] + s_in));
		if (state == STATE_DAY) {
			kk += j;
		} else {
			//	ҹ�䲻��
		}

		if (k[i + 1] == s_out_in)
			break;
	}
	if ((kk % (60 * 60)) > 0)
		kk += (60 * 60);
	kk /= (60 * 60);

	memset(rdata, 0x00, sizeof (rdata));
	memcpy(rdata, "0\0", 2);
	if (kk == 1) {
		memset(rdata, 0x00, sizeof (rdata));
		memcpy(rdata, ParkInfo->rate1, P_MONEY_W);				//	��1Сʱ�շ�
			} else if ((kk >= 2) & (kk <= 12)) {
				memset(rdata, 0x00, sizeof(rdata));
				memcpy(rdata, "01", 2);
				strmul(ParkInfo->rate1, rdata, P_MONEY_W);			//	��1Сʱ�շ�

				if (kk > 4)
				kk = 4;//	����4Сʱ��4Сʱ��
				kk--;//	ȥ����һ��Сʱ

				memset(tdata, 0x00, sizeof(tdata));
				itos(kk, tdata);
				strmul(ParkInfo->rate2, tdata, P_MONEY_W);//

				stradd(tdata, rdata, P_MONEY_W);//	�����շ�
			} else if ((kk < 0) | (kk > 12)) {
				cls();
				moveto(1, 1);
				printf("����kk=%d", kk);
				key(0);
				key(0);
				//		return;
			}

		//moveto( 9, 1 );
		//putstr( "Ǯr " );
		//putstr( rdata );
		//key(0);

	stradd(rdata, ParkInfo->charge_due, P_MONEY_W);				//	�����������ʵ����
	memcpy(ParkInfo->charge_real, ParkInfo->charge_due, P_MONEY_W);
	return 1;
}
int PInfo_Calcfree(TYPE_PARKINFO *ParkInfo) {
	Sint32 s_in, s_out, s_ds, s_ns;
	Sint32 s_out_in, s_ds_in, s_ns_in, s_out_ns, s_out_ds;
	Sint32 s_free;

	Uchar8 i;
	Uchar8 state;
	//  Uchar8 kdata[40];
	Uchar8 rdata[40], tdata[40];
	Sint32 k[4];
	Sint32 kk, j;
	TYPE_TIMESPAN ts;
#if DEBUG
	Uchar8 xb;
	Uchar8 ll[10];
#endif

	memset((Uchar8 *) (&ts), 0x00, sizeof (ts));
	memcpy(ts.begin, (ParkInfo->time_in), 14);
	memcpy(ts.end, (ParkInfo->time_out), 14);
	TimeSpan_Calc(&ts);                                                //  ʱ������
	memset(ParkInfo->time_disp, 0x00, sizeof (ParkInfo->time_disp));
	memcpy(ParkInfo->time_disp, ts.time_disp, strlen(ts.time_disp)); //  ����ʱ���Ŀɶ�����
	//  ���Ʒѡ�

	//	���Ʒѡ�
	PRate_Read(ParkInfo);
	s_free = (atoi(ParkInfo->step0)) * 60;                              //  ���ʱ��
	memset(ParkInfo->charge_due, 0x00, sizeof (ParkInfo->charge_due));
	memset(ParkInfo->charge_real, 0x00, sizeof (ParkInfo->charge_real));
	memcpy(ParkInfo->charge_due, "0\0", 2);
	memcpy(ParkInfo->charge_real, "0\0", 2);

	/*	��ռλʱ��β������15������ȥ��	*/
	//	gap_nums = ((ts.minutes)*60)+ts.seconds;
	//	if( gap_nums<=(15*60) )
	//	{
	//		ts.seconds = 0;
	//		ts.minutes = 0;
	//		Time_Offset( &ts );
	//		TimeSpan_Calc( &ts );                                                   //  ʱ������
	//	}
	/*	���������շѶ�	*/
	memset(rdata, 0x00, sizeof (rdata));
	memcpy(rdata, "01", 2);
	strmul(ParkInfo->rate1, rdata, P_MONEY_W);                        //  ��1Сʱ�շ�
	memset(tdata, 0x00, sizeof (tdata));
	memcpy(tdata, "03", 2);
	strmul(ParkInfo->rate2, tdata, P_MONEY_W);                        //  ��3Сʱ�շ�
	stradd(tdata, rdata, P_MONEY_W);                                  //  ��������շ�
	memset(tdata, 0x00, sizeof (tdata));
	itos(ts.days, tdata);
	strmul(tdata, rdata, P_MONEY_W);                                    //  ���շ���
	memcpy(ParkInfo->charge_due, rdata, P_MONEY_W);                     //  д��Ӧ��
	/*  ȡ���롢�뿪����ʼҹ�ա�ҹʼ���յľ�������  */
	s_in = ts.begin_s;
	s_out = ts.end_s;       //  ע�⣺���������β��ȡ�ᴦ����ֵ���ܷ�ʵ��ֵ
	s_ds = stoi(2, &(ParkInfo->step1[0]));                //  ʱ
	s_ds = stoi(2, &(ParkInfo->step1[2])) + s_ds * 60;    //  ʱ+��
	s_ds = stoi(2, &(ParkInfo->step1[4])) + s_ds * 60;   //  ʱ+��+�� ��ʼʱ����һ���еľ�������
	s_ns = stoi(2, &(ParkInfo->step2[0]));                //  ʱ
	s_ns = stoi(2, &(ParkInfo->step2[2])) + s_ns * 60;
	;   //  ʱ+��
	s_ns = stoi(2, &(ParkInfo->step2[4])) + s_ns * 60;
	;   //  ʱ+��+�� ҹʼʱ����һ���еľ�������
	/*  �������ʱ���  */
	s_out_in = s_out - s_in;            //  �뿪ʱ�������ʱ���
	if (s_out_in < 0) {
		s_out_in += 24 * 60 * 60; //	�˴���days�ѽ���������ݿ��ǽ�ȥ����s_in>s_outʱ�����ټ�
	}
	s_ds_in = s_ds - s_in;              //  ��ʼʱ�������ʱ���
	if (s_ds_in < 0) {
		s_ds_in += 24 * 60 * 60;
	}
	s_ns_in = s_ns - s_in;              //  ҹʼʱ�������ʱ���
	if (s_ns_in < 0) {
		s_ns_in += 24 * 60 * 60;
	}
	s_out_ds = s_out - s_ds;
	if (s_out_ds < 0) {
		s_out_ds += 24 * 60 * 60;
	}
	s_out_ns = s_out - s_ns;
	if (s_out_ns < 0) {
		s_out_ns += 24 * 60 * 60;
	}
	/*  ��ʱ���������Ϊ����ļ�����׼����
	 ƫ�ƻ�δ����������ʱ��ȥ������
	 һ�����飬0Ϊs_in_ds��1Ϊ��ӽ���ֵ
	 */
	k[0] = 0;                           //  min����
	k[1] = s_out_in;
	k[2] = s_ds_in;              //  ���ds��ns���Ӧȷ��ns��ǰ�棬ҹʼ���պ���ʼҹ�գ�����������ʼ��㣨Сʱ��λ����
	k[3] = s_ns_in;
	for (i = 0; i < 4; i++)            //  ����
			{
		if (k[2] < k[1]) {
			kk = k[1];
			k[1] = k[2];
			k[2] = kk;
		}
		if (k[3] < k[2]) {
			kk = k[2];
			k[2] = k[3];
			k[3] = kk;
		}
	}
	/*  �������շѼ���  */
	kk = 0;                         //  �����������������ȥ
	for (i = 0; i < 3; i++)            //  ��ʼ����
			{
		j = k[i + 1] - k[i];
		state = Get_State(s_ds, s_ns, (k[i] + s_in));
		if (state == STATE_DAY) {
			kk += j;
		} else {
			//  ҹ�䲻��
		}
		if (k[i + 1] == s_out_in) {
			break;
		}
	}

	/*	�����ʱ�䴦��	*/

	if ((ts.days == 0) & (kk <= s_free)) {
		return 1;
	}

	//	15������ȥ����
	if ((kk % (60 * 60)) > (15 * 60)) {
		kk += (60 * 60);
	}
	kk /= (60 * 60);
	memset(rdata, 0x00, sizeof (rdata));
	memcpy(rdata, "0\0", 2);
	if (kk == 1) {
		memset(rdata, 0x00, sizeof (rdata));
		memcpy(rdata, ParkInfo->rate1, P_MONEY_W);                  //  ��1Сʱ�շ�
			} else if ((kk >= 2) & (kk <= 12)) {
				memset(rdata, 0x00, sizeof(rdata));
				memcpy(rdata, "01", 2);
				strmul(ParkInfo->rate1, rdata, P_MONEY_W);           //  ��1Сʱ�շ�
				if (kk > 4) {
					kk = 4;    //	����4Сʱ��4Сʱ��
				}
				kk--;                                                //  ȥ����һ��Сʱ
				memset(tdata, 0x00, sizeof(tdata));
				itos(kk, tdata);
				strmul(ParkInfo->rate2, tdata, P_MONEY_W);//
				stradd(tdata, rdata, P_MONEY_W);//  �����շ�
			} else if ((kk < 0) | (kk > 12)) {
				cls();
				moveto(1, 1);
				printf("����kk=%d", kk);
				key(0);
				key(0);
				//      return;
			}
		//moveto( 9, 1 );
		//putstr( "Ǯr " );
		//putstr( rdata );
		//key(0);
	stradd(rdata, ParkInfo->charge_due, P_MONEY_W);                //  �����������ʵ����
	memcpy(ParkInfo->charge_real, ParkInfo->charge_due, P_MONEY_W);
	return 0;
}

/*
 **	���ƣ�	ʱ������
 **	��ڣ�	ʱ��ṹ��ָ�룬Begin:��ʼʱ�䣨����ʱ���ʽyyyymmddhrmise��End:����ʱ�䣨����ʱ���ʽ��
 **	���أ�	��������������������������ʾ��ʱ��
 **	˵����
 */
void TimeSpan_Calc(TYPE_TIMESPAN *ts) {
	Uchar8 kdata[40], lgh;
	Sint32 total_gap_day, int_gap_hour, int_gap_minute, int_gap_second;
	Sint32 sumr;

	Sint32 int_b_year = stoi(4, &(ts->begin[0]));
	Sint32 int_b_month = stoi(2, &(ts->begin[4]));
	Sint32 int_b_day = stoi(2, &(ts->begin[6]));
	Sint32 int_b_hour = stoi(2, &(ts->begin[8]));
	Sint32 int_b_minute = stoi(2, &(ts->begin[10]));
	Sint32 int_b_second = stoi(2, &(ts->begin[12]));

	Sint32 int_e_year = stoi(4, &(ts->end[0]));
	Sint32 int_e_month = stoi(2, &(ts->end[4]));
	Sint32 int_e_day = stoi(2, &(ts->end[6]));
	Sint32 int_e_hour = stoi(2, &(ts->end[8]));
	Sint32 int_e_minute = stoi(2, &(ts->end[10]));
	Sint32 int_e_second = stoi(2, &(ts->end[12]));

	Sint32 s_begin = ((int_b_hour * 60 + int_b_minute) * 60) + int_b_second; //	����ʱ����һ���еľ��Է���?
	Sint32 s_end = ((int_e_hour * 60 + int_e_minute) * 60) + int_e_second; //	�뿪ʱ����һ���еľ��Է�����

#if( 1 )
	{
		if ((((ts->begin[4]) < 0x30) | ((ts->begin[4]) > 0x39)) | (((ts->begin[7]) < 0x30) | ((ts->begin[7]) > 0x39)) | (((ts->end[4]) < 0x30) | ((ts->end[4]) > 0x39))
				| (((ts->end[7]) < 0x30) | ((ts->end[7]) > 0x39))) {
			//ErrorMsg( "TIMESPAN��ڲ�����ʽ����" );
			//key(0);
			return;
		}

		if (memcmp((ts->begin), (ts->end), 19) > 0) {
			ErrorMsg("TS_ʼĩʱ�����");
			key(0);
			return;
		}
	}
#endif

	total_gap_day = get_days(int_e_year, int_e_month, int_e_day) - get_days(int_b_year, int_b_month, int_b_day);	//	ռλ����

	sumr = s_end - s_begin;
	if (sumr < 0) {
		sumr += 24 * 60 * 60;
		total_gap_day--;
	}
	int_gap_second = sumr % 60;			//	Ȩ�� ��
	int_gap_minute = sumr / 60;			//	�ܷ�����
	int_gap_hour = int_gap_minute / 60;	//	Ȩ�� ʱ
	int_gap_minute = int_gap_minute % 60;	//	Ȩ�� ��

	/*	time_disp	*/
	memset(kdata, 0x00, sizeof (kdata));
	if (total_gap_day > 0) {
		memset(kdata, 0x00, sizeof (kdata));
		itos(total_gap_day, &(kdata[0]));
		lgh = strlen(kdata);
		memcpy(&(kdata[lgh]), "��", 2);
	}
	if ((kdata[0] != 0x00) || (int_gap_hour > 0)) {
		lgh = strlen(kdata);
		itos(int_gap_hour, &(kdata[lgh]));
		lgh = strlen(kdata);
		memcpy(&(kdata[lgh]), "ʱ", 2);
	}
	if ((kdata[0] != 0x00) || ((int_gap_minute % 60) > 0)) {
		lgh = strlen(kdata);
		itos(int_gap_minute, &(kdata[lgh]));
		lgh = strlen(kdata);
		memcpy(&(kdata[lgh]), "��", 2);
	}
	lgh = strlen(kdata);
	itos(int_gap_second, &(kdata[lgh]));
	lgh = strlen(kdata);
	memcpy(&(kdata[lgh]), "��", 2);

	/*	return	*/
	lgh = strlen(kdata);
	memset(ts->time_disp, 0x00, sizeof (ts->time_disp));
	memcpy(ts->time_disp, kdata, lgh);

	ts->days = total_gap_day;
	ts->hours = int_gap_hour;
	ts->minutes = int_gap_minute;
	ts->seconds = int_gap_second;

	ts->begin_s = s_begin;				//	��ʼʱ��������賿�ľ�������
	ts->end_s = s_end;					//	����ʱ��������賿�ľ�������

}

/*
 **	���ƣ�	ʱ��ƫ��
 **	��ڣ�	ʱ��ṹ��ָ�룬Begin:��ʼʱ�䣨����ʱ���ʽyyyymmddhrmise��ƫ��ʱ�䣨��ֻΪ���ӣ�
 **	���أ�	��������������������������ʾ��ʱ��
 **	˵����
 */
void Time_Offset(TYPE_TIMESPAN *ts) {
	//	Uchar8	kdata[40], lgh;
	//	Sint32	total_gap_day, int_gap_minute, int_gap_second;

	//	Sint32	int_b_year = stoi( 4, &(ts->begin[0]) );
	//	Sint32	int_b_month = stoi( 2, &(ts->begin[4]) );
	Sint32 int_b_day = stoi(2, &(ts->begin[6]));
	Sint32 int_b_hour = stoi(2, &(ts->begin[8]));
	Sint32 int_b_minute = stoi(2, &(ts->begin[10]));
	Sint32 int_b_second = stoi(2, &(ts->begin[12]));

	//	Sint32	int_e_year = 0;
	//	Sint32	int_e_month = 0;
	Sint32 int_e_day = int_b_day;
	Sint32 int_e_hour = int_b_hour;
	Sint32 int_e_minute = int_b_minute;
	Sint32 int_e_second = int_b_second;

	Sint32 m_begin, m_end;

	int_e_second = int_e_second + ts->seconds;
	if (int_e_second >= 60) {
		int_e_second -= 60;
		int_e_minute++;
	}
	int_e_minute = int_e_minute + ts->minutes;
	if (int_e_minute >= 60) {
		int_e_minute -= 60;
		int_e_hour++;
	}
	int_e_hour = int_e_hour + ts->hours;
	if (int_e_hour >= 24) {
		int_e_hour -= 24;
		int_e_day++;
	}
	int_e_day += ts->days;

	memcpy(&(ts->end[0]), &(ts->begin[0]), 4);			//	��
	memcpy(&(ts->end[4]), &(ts->begin[4]), 2);			//	��
	sprintf(&(ts->end[6]), "%02d", int_e_day);			//	��
	sprintf(&(ts->end[8]), "%02d", int_e_hour);			//	ʱ
	sprintf(&(ts->end[10]), "%02d", int_e_minute);		//	��
	sprintf(&(ts->end[12]), "%02d", int_e_second);		//	��

	m_begin = (int_b_hour * 60 + int_b_minute);				//	����ʱ����һ���еľ��Է���?
	m_end = (int_e_hour * 60 + int_e_minute);				//	�뿪ʱ����һ���еľ��Է�����

}

/*
 **	���ƣ�
 **	��ڣ�
 **	���أ�
 */
void PRate_Read(TYPE_PARKINFO *ParkInfo) {
	memset(ParkInfo->step0, 0x00, sizeof (ParkInfo->step0));		//	��ʼҹ��
			memset(ParkInfo->step1, 0x00, sizeof(ParkInfo->step1));//	��ʼҹ��
			memset(ParkInfo->step2, 0x00, sizeof(ParkInfo->step2));//	ҹʼ����
			memset(ParkInfo->step3, 0x00, sizeof(ParkInfo->step3));//	���ʱ��
			memset(ParkInfo->rate1, 0x00, sizeof(ParkInfo->rate1));//	�����
			memset(ParkInfo->rate2, 0x00, sizeof(ParkInfo->rate2));//	ҹ����
			memset(ParkInfo->rate3, 0x00, sizeof(ParkInfo->rate3));//	������߷���
			memset(ParkInfo->rate4, 0x00, sizeof(ParkInfo->rate4));
			memset(ParkInfo->rate5, 0x00, sizeof(ParkInfo->rate5));

			EEROM_read(EPR_P_STEP0, P_STEP_W, (ParkInfo->step0));
			EEROM_read(EPR_P_STEP1, P_STEP_W, (ParkInfo->step1));
			EEROM_read(EPR_P_STEP2, P_STEP_W, (ParkInfo->step2));
			EEROM_read(EPR_P_STEP3, P_STEP_W, (ParkInfo->step3));
			EEROM_read(EPR_P_RATE1, P_MONEY_W, (ParkInfo->rate1));
			EEROM_read(EPR_P_RATE2, P_MONEY_W, (ParkInfo->rate2));
			EEROM_read(EPR_P_RATE3, P_MONEY_W, (ParkInfo->rate3));
			EEROM_read(EPR_P_RATE4, P_MONEY_W, (ParkInfo->rate4));
			EEROM_read(EPR_P_RATE5, P_MONEY_W, (ParkInfo->rate5));

		}

	/*
	 **	���ƣ�
	 **	��ڣ�
	 **	���أ�
	 */
void PRate_Save(TYPE_PARKINFO *ParkInfo) {
	EEROM_write(EPR_P_STEP0, P_STEP_W, ParkInfo->step0);
	EEROM_write(EPR_P_STEP1, P_STEP_W, ParkInfo->step1);
	EEROM_write(EPR_P_STEP2, P_STEP_W, ParkInfo->step2);
	EEROM_write(EPR_P_STEP3, P_STEP_W, ParkInfo->step3);
	EEROM_write(EPR_P_RATE1, P_MONEY_W, ParkInfo->rate1);
	EEROM_write(EPR_P_RATE2, P_MONEY_W, ParkInfo->rate2);
	EEROM_write(EPR_P_RATE3, P_MONEY_W, ParkInfo->rate3);
	EEROM_write(EPR_P_RATE4, P_MONEY_W, ParkInfo->rate4);
	EEROM_write(EPR_P_RATE5, P_MONEY_W, ParkInfo->rate5);
}
void rate_set(void) {
	TYPE_PARKINFO ParkInfo;

	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
	PRate_Read(&(ParkInfo));
	memset(ParkInfo.step1, 0x00, sizeof (ParkInfo.step1));
	memcpy(ParkInfo.step1, "0800", P_STEP_W);
	memset(ParkInfo.step2, 0x00, sizeof (ParkInfo.step2));
	memcpy(ParkInfo.step2, "2000", P_STEP_W);
	PRate_Save(&(ParkInfo));
	memcpy(ParkInfo.step0, "20", P_STEP_W);
	memcpy(ParkInfo.rate1, "3", P_MONEY_W);
	memcpy(ParkInfo.rate2, "5", P_MONEY_W);
	PRate_Save(&ParkInfo);
}
/*
 **	���ƣ�
 **	��ڣ�
 **	���أ�
 */
void PRate_Set(void) {
	//	���Ĳ˵��ṹΪ���¼�ѡ�񣬽�ʡ�пռ�
	Uchar8 k, lgh;
	Uchar8 sdata[20] = { 0 };

	//	Uchar8 sf[4] = {0}, s1[4] = {0}, s2[4] = {0}, s3[4] = {0};
	//	Uchar8 r1[4] = {0}, r2[4] = {0}, r3[4] = {0}, r4[4] = {0};

	//	Uchar8 xb, yb;

	TYPE_PARKINFO ParkInfo;

	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
	PRate_Read(&(ParkInfo));
	memset(ParkInfo.step1, 0x00, sizeof (ParkInfo.step1));
	memcpy(ParkInfo.step1, "0800", P_STEP_W);
	memset(ParkInfo.step2, 0x00, sizeof (ParkInfo.step2));
	memcpy(ParkInfo.step2, "2000", P_STEP_W);
	PRate_Save(&(ParkInfo));

	while (1) {
		cls();
		putstr_h("\n��");
		putn_h(P_STEP_W, ParkInfo.step0);
		putstr_h("�������,��������ʵ��.");
		putstr_h("\n��1Сʱ��");
		putn_h(P_MONEY_W, ParkInfo.rate1);
		putstr_h("Ԫ/ʱ.");
		putstr_h("\n�ݳ���1Сʱ");
		putn_h(P_MONEY_W, ParkInfo.rate2);
		putstr_h("Ԫ/ʱ.");
		putstr_h("\n\n[ע]:���հ����4Сʱ�շ�,ռλʱ��β������15������ȥ,�Ʒ�ʱ�޳�ҹ�����.");
		//		moveto( 19, 1 );
		//		putstr_h( "[ȷ��]����");						//	�����ʹ���Զ����г��򡱺�Ӧ��F2��

		do {
			k = key(0); /* �ȴ�����һ���ַ�,������ */
		} while (k != 0x31 && k != 0x32 && k != 0x33 && k != 0x34 && k != 0x35 && k != 0x36 && k != 0x89 && k != KEY_ENTER);
		if (k == KEY_F2)
			return;
		if (k == KEY_ENTER) //  ������ֵ
		{
			PRate_Save(&ParkInfo);
			ErrorMsg("���óɹ�");
			return;
		}
		if ((k == 0x31) | (k == 0x32)) {
			//			cls();
			//			moveto( 11, 1 );
			//			putstr_h( "ʱ���ʽʾ��:\n1245  =  12:45" );
			//			moveto( 3, 1 );
			//			putstr_h( "������:" );
			//			lgh = ksh( sdata, 0, 4, 0 );
			//			while( lgh==4 )
			//			{
			//				if( memcmp( &(sdata[2]), "60", 2 )==0 )
			//				{
			//					memcpy( &(sdata[2]), "00", 2 );
			//					stradd( "01", &(sdata[0]), 2 );
			//				}
			//				if( memcmp( &(sdata[0]), "24", 2 )==0 )
			//					memcpy( &(sdata[0]), "00", 2 );
			//
			//				memset( sb, 0x00, sizeof(sb) );
			//				memcpy( sb, &(sdata[0]), 2 );
			//				strsub( "24", &(sb[0]), 2 );
			//				if( sb[0]=='-' )
			//				{
			//#if DEBUG
			//cls();
			//moveto( 11, 1 );
			//putstr( "С��24" );
			//key(0);
			//#endif
			//					lgh=1;
			//				 	break;
			//				}
			//				memset( sb, 0x00, sizeof(sb) );
			//				memcpy( sb, &(sdata[2]), 2 );
			//				strsub( "60", &(sb[2]), 2 );
			//				if( sb[2]=='-' )
			//				{
			//#if	DEBUG
			//cls();
			//moveto( 11, 1 );
			//putstr( "С��60" );
			//key(0);
			//#endif
			//					lgh=1;
			//				 	break;
			//				}
			//				break;
			//			}
			//			if( lgh<4 )
			//			{
			//				if( lgh==0 )
			//					continue;
			//				cls();
			//				moveto( 9, 1 );
			//				putstr( "ʱ���ʽ����" );
			//				bell(50);
			//				delay(250);
			//				delay(250);
			//				continue;
			//			}
		} else {
			cls();
			moveto(3, 1);
			putstr_h("������:");
			memset(sdata, 0x00, sizeof (sdata));
			lgh = ReadLine(sdata, 0, 4, 1);

			if (lgh == 0)
				continue;
		}
		switch (k) /* ��������İ���������Ӧ�ĺ��� */
		{
		//			case '1':	memcpy( ParkInfo.step1, "0800", P_STEP_W );	break;			//	��Ҫ�����ʽУ��
		//			case '2':	memcpy( ParkInfo.step2, "0000", P_STEP_W );	break;
		case '3':
			memcpy(ParkInfo.step0, "20", P_STEP_W);
			break;
		case '4':
			memcpy(ParkInfo.rate1, "3", P_MONEY_W);
			break;
		case '5':
			memcpy(ParkInfo.rate2, "5", P_MONEY_W);
			break;
			//			case '6':   memcpy( ParkInfo.rate3, sdata, P_MONEY_W );	break;
			//			case '':   memcpy( ParkInfo.step3, sdata, P_STEP_W );	break;
		default:
			;
			break;
		}
	}
	PRate_Save(&ParkInfo);

}

/*
 **	���ƣ�	POS��������ã�ֱ���޸�EEPROM��
 */
void POSID_Set(void) {
	Uchar8 k, lgh;
	Uchar8 sdata[40];

	memset(G_POSID, 0x00, sizeof (G_POSID));
	POSID_Read(G_POSID);
	while (1) {
		cls();
		moveto(1, 1);
		putstr("�� ��ǰPOSID:");
		putstr(G_POSID);
		moveto(17, 1);
		putstr("[ȷ��] ����");
		k = key(0);

		if (k == 0x31) {
			cls();
			moveto(9, 1);
			putstr("��POSID:");
			memset(sdata, 0x00, sizeof (sdata));
			lgh = ReadLine(sdata, 0, POSID_W, 0);
			if (lgh == 0) {
				continue;
			} else {
				memset(G_POSID, 0x00, sizeof (G_POSID));
				memcpy(G_POSID, sdata, strlen(sdata));
			}
		}
		if (k == KEY_ENTER) {
			POSID_Save(G_POSID);
			ErrorMsg("�޸ĳɹ�");
			return;
		}
		if (k == KEY_F2) {
			return;
		}
	}
}

/*
 **	���ƣ�
 **	��ڣ�
 **	���أ�
 */

Uchar8 CardReader_Open(void) {
	Uchar8 rt;

	rt = mif_open();
	if (rt != MI_OK) {
		ErrorMsg("\n�������򿪴���");
		key(0);
	}
	return rt;
}

Uchar8 CardReader_Close(void) {
	Uchar8 rt;

	rt = mif_close();
	if (rt != MI_OK) {
		ErrorMsg("\n�������رմ���");
		key(0);
	}
	return rt;
}

/*
 **	���ƣ�	M1��Ѱ��
 **	���ܣ�	ֻ�����ҿ����ҵ��������������֤����ProCardAuth��ɡ�
 **	��ڣ�	��
 **	���أ�	Ѱ�������־
 */
Uchar8 Card_Search(void) {
	Uchar8 rt;
	Uchar8 CardType[3];
	rt = mif_request(0, CardType);
	if (rt != MI_OK) {
		rt = mif_request(0, CardType);
		if (rt != MI_OK)
			return REQUEST_ER;
	} else
		return MI_OK;

	return 0;

}

/*
 **	���ƣ�	����Ϣ��ȡ
 **	���ܣ�	ȷ���ҵ�������֤������������֤���룬��ȡ���ݡ�
 **	��ڣ�	���ݴ��λ��
 **	���أ�
 */
Uchar8 CardInfo_Read(TYPE_PARKINFO *ParkInfo) {
	Uchar8 rt;
	Uchar8 kdata[40];

	rt = ProCard_HL_Auth(50, 0, CARD_PWD_TYPEA, CARD_USER_SECTOR1);
	if (rt != MI_OK) {
		//		ErrorMsg( "������֤����" );
		return rt;
	}

	//	memset( kdata, 0x00, sizeof(kdata) );
	//	rt = Block_Read( CARD_USER_BLK10, kdata );
	//	memset( ParkInfo->card_name, 0x00, sizeof(ParkInfo->card_name) );
	//	memcpy( ParkInfo->card_name, kdata, 8 );
	//	memcpy( ParkInfo->card_time, &(kdata[8]), 8 );

	memset(kdata, 0x00, sizeof (kdata));
	rt = Block_Read(CARD_USER_BLK11, kdata);
	memset(ParkInfo->userID, 0x00, sizeof (ParkInfo->userID));
	memcpy(ParkInfo->userID, kdata, 6);
	ParkInfo->card_type = kdata[6];
	memset(ParkInfo->version, 0x00, sizeof (ParkInfo->version));
	memcpy(ParkInfo->version, &(kdata[7]), 2);
	ParkInfo->flag = kdata[9];
	ParkInfo->consume = kdata[10];

	memset(kdata, 0x00, sizeof (kdata));
	rt = Block_Read(CARD_USER_BLK12, kdata);
	memset(ParkInfo->time_in, 0x00, sizeof (ParkInfo->time_in));
	memcpy(ParkInfo->time_in, kdata, 14);

	return rt;

}

/*
 **	���ƣ�
 **	��ڣ�
 **	���أ�
 */
Uchar8 CardInfo_Write(TYPE_PARKINFO *ParkInfo) {
	Uchar8 rt;
	Uchar8 kdata[16];

	while (Card_Search() != MI_OK) {
		if (keygo() == KEY_F2)
			return 0xFF;
	}
	rt = ProCard_HL_Auth(50, 0, CARD_PWD_TYPEA, CARD_USER_SECTOR1);
	if (rt != MI_OK) {
		//		ErrorMsg( "������֤����" );
		return rt;
	}

	//	memset( kdata, 0x00, sizeof(kdata) );
	//	memcpy( kdata, ParkInfo->card_name, 8 );
	//	memcpy( &(kdata[8]), ParkInfo->card_time, 8 );
	//	rt = Block_Write( CARD_USER_BLK10, kdata );

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->userID, 6);
	kdata[6] = ParkInfo->card_type;
	memcpy(&(kdata[7]), ParkInfo->version, 2);
	kdata[9] = ParkInfo->flag;
	kdata[10] = ParkInfo->consume;
	rt = Block_Write(CARD_USER_BLK11, kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_in, 14);
	rt = Block_Write(CARD_USER_BLK12, kdata);

	return rt;

}

//�߼���֤����Ѱ���ȴ�
//wtime ��ʱ�ȴ�ʱ��
//SC���Ƿ���ֱ��ѡ�����кţ�=0Ҫ����ͻ��=1ֱ��ѡ���к�
//pwdtype ��������
//sectorno ������
Uchar8 ProCard_HL_Auth(Uint16 wtime, Uchar8 sc, Uchar8 pwdtype, Uchar8 sectorno) {
	Uchar8 rt;
	Uchar8 sn[5];
	Uchar8 keybuffer[6];
	//һ���Բ�����
	Uint32 stimer = 0;
	if (sc == 0) {
		memset(G_CARD_SN, 0x00, 4);
		while (1) {
			rt = mif_anticoll(0, sn);
			if (rt == MI_OK) {
				rt = mif_select(sn);
				if (rt == MI_OK) {
					memcpy(G_CARD_SN, sn, 4);
					break;
				}
			}
			stimer++;
			if (stimer > wtime) {
				return 1;
			}
		}
	} else {
		memcpy(sn, G_CARD_SN, 4);
		rt = mif_select(sn);
		if (rt != MI_OK) {
			return 2;
		}
	}
	getm1psw(sn, keybuffer);
	rt = mif_load_key(keybuffer);
	if (rt != MI_OK) {
		return 4;
	}
	rt = mif_authentication(pwdtype, sectorno, sn);
	if (rt != MI_OK) {
		return 5;
	}
	return 0;
}

/*
 **	���ƣ�	M1�������ȡ
 **	��ڣ�	�����к�ָ�룬����ָ��
 **	���أ�
 **	˵����	��һ��һ��
 */
void getm1psw(uchar *sn, uchar *psw) {
#if 0
	uchar s_snr[8], key[8];
	uchar i;
	//  uchar  key1[8]= {0xa1,0x12,0xb1,0x2b,0xc3,0xA9,0xd2,0x00};
	uchar key1[8] = {0x3D, 0x48, 0x5A, 0x3B, 0xEF, 0x01, 0x11, 0x00};
	uchar keya[8] = {0xc0, 0x31, 0x51, 0x29, 0xc0, 0xee, 0xe2, 0x00};
	uchar key2[8] = {0x13, 0x15, 0x15, 0x17, 0x17, 0x19, 0x11, 0x00};

	for(i = 0; i < 8; i++)
	{
		key[i] = keya[i];
	}
	for(i = 0; i < 8; i++)
	{
		key[i] = key1[i] + key2[i];
	}
	memcpy(s_snr, sn, 4);
	s_snr[4] = 0xaa;
	s_snr[5] = 0x05;
	s_snr[6] = key1[0];
	s_snr[7] = key2[0];
	des_code(0, s_snr, key, psw); //����
#else
	memset(psw, 0xFF, 6);
#endif

}

unsigned long get_days(int year, int month, int date) {
	int i, leap;
	long days = 0;
	for (i = 1990; i < year; i++) {
		if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {
			leap = 1;
			days += 366;
		} else {
			leap = 0;
			days += 365;
		}
	}
	year = i;
	for (i = 1; i < month; i++) {
		switch (i) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days += 31;
			break;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				days += 29;
			else
				days += 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days += 30;
			break;
		}
	}
	days += date;
	return days;
}

/*
 **	���ƣ�	�жϵ�ǰ��ʱ��
 **	��ڣ�	ʱ�����������������s_now��ǰ��s_ds��ʼ��s_nsҹʼ
 **	���أ�	ʱ��
 */
int Get_State(int s_ds, int s_ns, int s_now)		//	��һ��ֵ�п��ܻ��Ǵ���24*60�ģ���Ҫ�����ж�
{
	int s_ds_now, s_ns_now;

	if (s_now >= 24 * 60 * 60)
		s_now -= 24 * 60 * 60;
	if (s_ds >= 24 * 60 * 60)
		s_ds -= 24 * 60 * 60;
	if (s_ns >= 24 * 60 * 60)
		s_ns -= 24 * 60 * 60;

	s_ds_now = s_ds - s_now;				//	��ʼʱ�������ʱ���
	if (s_ds_now <= 0)
		s_ds_now += 24 * 60 * 60;

	s_ns_now = s_ns - s_now;				//	ҹʼʱ�������ʱ���
	if (s_ns_now <= 0)
		s_ns_now += 24 * 60 * 60;
#if DEBUG
	{
		putstr( "ʶ��״̬" );
		printf( "\ns_now=%d", s_now );
		printf( "\ns_ds=%d", s_ds );
		printf( "\ns_ns=%d", s_ns );
		printf( "\ns_ds_now=%d", s_ds_now );
		printf( "\ns_ns_now=%d", s_ns_now );
		key(0);
	}
#endif
	if (s_ds_now < s_ns_now)				//	������DAY
		return STATE_NIGHT;
	else
		return STATE_DAY;

}

/*
 **	���ƣ�	ΰ��ͣ���շѹ���ʵ�ʷ���5�ǵ�ȡ�ᣨС��5����ȥ�����ڵ���5����5�ǣ���
 **	��ڣ�	ssʵ�ʷ��ã�s����������
 **	���أ�	��
 */
void WCh_Money_Round(uchar *ss, uchar *s) {
	uchar tbuf[15], rlen, i;
	ulong lm;
	uchar bb[15];
	int m = 0;

	memset(bb, 0x00, sizeof (bb));
	bb[0] = '1';
	bb[1] = '0';
	bb[2] = '0';
	bb[3] = '0';
	bb[4] = 0x00;
	strmul(ss, bb, 9);
	lm = stoi(9, bb);
	sprintf(tbuf, "%d", lm);
	rlen = strlen(tbuf);
	if (rlen <= 2) {
		s[0] = '0';
		s[1] = 0x00;
	} else {
		for (i = 0; i < (rlen - 3); i++) {
			s[i] = tbuf[i];
		}
		s[i] = '.';
		m = memcmp(&(tbuf[i]), "5", 1);
		if (m < 0) {
			s[i + 1] = '0';
		} else {
			s[i + 1] = '5';
		}
	}
	s[i + 2] = 0x00;

}

Sint32 Data_Upload(void) {
	comm_fun();
	return 0;
}

//	�����û���������Ϊ"666666"
Sint32 AllUPSW_Reset(void) {
	Uchar8 kdata[40] = { 0 };

	memset(kdata, '6', USERPSW_W);

	UserPSW_Save(EPR_UPSW_SFY1, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_SFY2, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_SFY3, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_SFY4, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_SFY5, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_SFY6, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_JZY, USERPSW_W, kdata);
	UserPSW_Save(EPR_UPSW_GLY, USERPSW_W, kdata);

	return 0;

}

Sint32 AllUPSW_Read(TYPE_USER_INFO *G_USERINFO) {

	UserPSW_Read(EPR_UPSW_SFY1, USERPSW_W, G_USERINFO->UserPSW[1]);
	UserPSW_Read(EPR_UPSW_SFY2, USERPSW_W, G_USERINFO->UserPSW[2]);
	UserPSW_Read(EPR_UPSW_SFY3, USERPSW_W, G_USERINFO->UserPSW[3]);
	UserPSW_Read(EPR_UPSW_SFY4, USERPSW_W, G_USERINFO->UserPSW[4]);
	UserPSW_Read(EPR_UPSW_SFY5, USERPSW_W, G_USERINFO->UserPSW[5]);
	UserPSW_Read(EPR_UPSW_SFY6, USERPSW_W, G_USERINFO->UserPSW[6]);
	UserPSW_Read(EPR_UPSW_JZY, USERPSW_W, G_USERINFO->UserPSW[8]);
	UserPSW_Read(EPR_UPSW_GLY, USERPSW_W, G_USERINFO->UserPSW[0]);

	return 0;

}
Sint32 AllUPSW_Save(TYPE_USER_INFO *G_USERINFO) {

	UserPSW_Save(EPR_UPSW_SFY1, USERPSW_W, G_USERINFO->UserPSW[1]);
	UserPSW_Save(EPR_UPSW_SFY2, USERPSW_W, G_USERINFO->UserPSW[2]);
	UserPSW_Save(EPR_UPSW_SFY3, USERPSW_W, G_USERINFO->UserPSW[3]);
	UserPSW_Save(EPR_UPSW_SFY4, USERPSW_W, G_USERINFO->UserPSW[4]);
	UserPSW_Save(EPR_UPSW_SFY5, USERPSW_W, G_USERINFO->UserPSW[5]);
	UserPSW_Save(EPR_UPSW_SFY6, USERPSW_W, G_USERINFO->UserPSW[6]);
	UserPSW_Save(EPR_UPSW_JZY, USERPSW_W, G_USERINFO->UserPSW[8]);
	UserPSW_Save(EPR_UPSW_GLY, USERPSW_W, G_USERINFO->UserPSW[0]);

	return 0;

}

//	�����û�������
Sint32 AllUName_Reset(void) {

	//	UserName_Save( EPR_UNAME_SFY1, USERNAME_W, "�շ�Ա1" );
	//	UserName_Save( EPR_UNAME_SFY2, USERNAME_W, "�շ�Ա2" );
	//	UserName_Save( EPR_UNAME_SFY3, USERNAME_W, "�շ�Ա3" );
	//	UserName_Save( EPR_UNAME_SFY4, USERNAME_W, "�շ�Ա4" );
	//	UserName_Save( EPR_UNAME_SFY5, USERNAME_W, "�շ�Ա5" );
	//	UserName_Save( EPR_UNAME_SFY6, USERNAME_W, "�շ�Ա6" );
	//	UserName_Save( EPR_UNAME_JZY, USERNAME_W, "����Ա" );
	//	UserName_Save( EPR_UNAME_GLY, USERNAME_W, "����Ա" );

	memcpy(G_USERINFO.UserName[1], "�շ�Ա1", 7);
	memcpy(G_USERINFO.UserName[2], "�շ�Ա2", 7);
	memcpy(G_USERINFO.UserName[3], "�շ�Ա3", 7);
	memcpy(G_USERINFO.UserName[4], "�շ�Ա4", 7);
	memcpy(G_USERINFO.UserName[5], "�շ�Ա5", 7);
	memcpy(G_USERINFO.UserName[6], "�շ�Ա6", 7);
	memcpy(G_USERINFO.UserName[8], "����Ա", 6);
	memcpy(G_USERINFO.UserName[0], "����Ա", 6);

	return 0;

}

Sint32 UserPSW_Read(Uchar8 u, Uchar8 wide, Uchar8 *udata) {
	return (EEROM_read(u, wide, udata));
}
Sint32 UserPSW_Save(Uchar8 u, Uchar8 wide, Uchar8 *udata) {
	return (EEROM_write(u, wide, udata));
}
Sint32 UserName_Read(Uchar8 u, Uchar8 wide, Uchar8 *udata) {
	return (EEROM_read(u, wide, udata));
}
Sint32 UserName_Save(Uchar8 u, Uchar8 wide, Uchar8 *udata) {
	return (EEROM_write(u, wide, udata));
}

void UserInfo_Set(Uchar8 UserType, Uchar8 UserIndex) {
	//	ԭ���� ������ ȷ��������
	Uchar8 lgh;
	Uchar8 s[40], op[40], np[40], vnp[40];

	cls();
	bell(20);
	moveto(3, 1);
	putstr("�����뵱ǰ����:\n");
	moveto(9, 1);
	putstr("������������:\n");
	moveto(13, 1);
	putstr("ȷ��������:\n");

	while (1) {
		memset(op, 0x00, sizeof (s));
		moveto(5, 1);
		lgh = Key_PSW(op, USERPSW_W);
		if (lgh == USERPSW_W) {
			break;
		} else if (op[1] == KEY_F2)
		return;
	}
	while (1) {
		memset(np, 0x00, sizeof (s));
		moveto(11, 1);
		lgh = Key_PSW(np, USERPSW_W);
		if (lgh == USERPSW_W) {
			break;
		} else if (np[1] == KEY_F2)
		return;
	}
	while (1) {
		memset(vnp, 0x00, sizeof (s));
		moveto(15, 1);
		lgh = Key_PSW(vnp, USERPSW_W);
		if (lgh == USERPSW_W) {
			break;
		} else if (vnp[1] == KEY_F2)
		return;
	}

	if (memcmp(op, G_USERINFO.UserPSW[UserIndex], USERPSW_W) == 0) {
		if (memcmp(np, vnp, USERPSW_W) == 0) {
			memcpy(G_USERINFO.UserPSW[UserIndex], np, USERPSW_W);
			AllUPSW_Save(&G_USERINFO);
			ErrorMsg("�����޸ĳɹ�");
		} else {
			ErrorMsg("���������벻���");
		}
	} else {
		ErrorMsg("ԭ�����������");
	}

}

/*
 **	���ƣ�	�û��˵���ӡ
 **	��ڣ�	���ݿ�ļ�¼��
 **	���أ�	��
 */
void Print_Bill(TYPE_PARKINFO *ParkInfo) {
#if	POS_PRINTER
	Uchar8 kdata[100];
	Uchar8 s[40], lgh;
	Uchar8 rt;

	rt = Printer_Open();
	if (rt != 0) {
		cls();
		moveto(2, 1);
		putstr("��ӡ����:\n\n");
		switch (rt) {
		case 0x08:
			putstr("��ѹ����");
			break;
		case 0x04:
			putstr("�������");
			break;
		case 0x02:
			putstr("��ӡͷ����");
			break;
		case 0x01:
			putstr("�޴�ӡֽ");
			break;
		default:
			printf("%x", rt);
			break;
		}
		Printer_Close();
		key(0);
		return;
	}

	Printer_ClrBuf();
	Printer_PaperBack(300);
	Printer_SpaceSet(7, 30);
	Printer_Str("********************\n");			//	*��19������20
	memset(s, 0x00, sizeof (s));
	OrgName_Read(s);
	lgh = strlen(s);								//	��λ���Ƶľ��д�ӡ��Ҫ�ͳ�����ʾ��ͳһ��
	if (lgh < 20) {
		memset(kdata, 0x00, sizeof (kdata));
		memset(kdata, ' ', (20 - lgh) / 2);
		memcpy(&kdata[(20 - lgh) / 2], s, lgh + 1);
	} else {
		memcpy(kdata, s, 20);
	}
	Printer_Str(kdata);
	Printer_Str("\n********************");			//	*��19������20

	if (Printer_Buffer(0)) {
		Printer_Close();
		cls();
		putstr("��ӡ����!");
		key(0);
		return;
	}

	Printer_ClrBuf();
	Printer_SpaceSet(1, 36);
	//	Printer_Str( "\n����:" );
	//	Printer_Str( ParkInfo->userID );

	Printer_Str("\n������:");
	Printer_Str(AdminId);

	Printer_Str("\n��ˮ��");
	memset(kdata, 0x00, sizeof (kdata));
	sprintf(kdata, "%06d", ParkInfo->flowNO);
	Printer_Str(kdata);

	Printer_Str("\n���ƺ�:");
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->chepai, 16);
	//Change_DateTime_Style( 1, kdata );
	Printer_Str(kdata);

	Printer_Str("\n��λ��:");
	//Printer_Str( ParkInfo->bwh );
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->bwh, 14);
	//Change_DateTime_Style( 1, kdata );
	Printer_Str(kdata);

	Printer_Str("\n����ʱ��:");
	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, ParkInfo->time_in, 14);
	Change_DateTime_Style(1, kdata);
	Printer_Str(kdata);

	if (ParkInfo->flag == FLAG_OUT) {
		Printer_Str("\n�뿪ʱ��:");
		memset(kdata, 0x00, sizeof (kdata));
		memcpy(kdata, ParkInfo->time_out, 14);
		Change_DateTime_Style(1, kdata);
		Printer_Str(kdata);
		Printer_Str("\nռλʱ��:");
		Printer_Str(ParkInfo->time_disp);

		Printer_PaperBack(50);
		if (Printer_Buffer(0)) {
			cls();
			moveto(5, 1);
			putstr("��ӡ����!");
			key(0);
			return;
		}

		Printer_ClrBuf();
		//Printer_Font(1);
		Printer_Str("Ӧ�� RMB:");
		Printer_Str(ParkInfo->charge_due);
		Printer_Str("Ԫ");
		//		Printer_Str( "\nʵ��:" );
		//		Printer_Str( ParkInfo->charge_real );
		//		Printer_Str( "Ԫ" );
		//Printer_Font(0);

		Printer_Str("\n��������������λ�շ�����Ϊ������[2012]72�š��μ�[2012]25�ţ����ڹ�����ͣ����λ,������ɱ���ȡͣ����λ�ѣ����е�����������ٵ����·������Ρ�");
	}
	if (Printer_Buffer(500)) {
		cls();
		moveto(5, 1);
		putstr("��ӡ����!");
		key(0);
		return;
	}

	Printer_Close();
#else
	;
#endif

}

void OrgName_Set(void)			//	��λ��������
{
	Uchar8 cdata[100];
	Uchar8 k;
	Uchar8 xb, yb;

	while (1) {
		memset(cdata, 0x00, sizeof (cdata));
		OrgName_Read(cdata);

		cls();
		moveto(1, 1);
		putstr("��ǰ��λ����:\n");
		putn_h(ORGNAME_W, cdata);

		putstr("\n�µ�λ����:\n");
		xb = getx();
		yb = gety();
		keyswitchset(3);
		memset(cdata, 0x00, sizeof(cdata));
		moveto(xb, yb);
		k = keys(cdata);

		if (k == 0) {
			if ((cdata[0] == KEY_F2) || (cdata[1] == KEY_F2))
			return;
			else
			continue;
		} else {
			moveto(15, 1);
			putstr("��ȷ�ϡ�����");
			putstr("\n�� F2 ���������˳�");
			putstr("\n������������¼��");

			k = key(0);
			switch (k) {
				case KEY_ENTER:
				OrgName_Save(cdata);
				ErrorMsg("���óɹ�");
				return;
				case KEY_F2:
				return;
				default:
				break;
			}
		}
	}
}

		/*
		 **	���ƣ�	����λ���ƴ洢��EEPROM��
		 **	��ڣ�	��λ����ָ�루������λ���ƿ�ȡ����洢��ַ��
		 **	���أ�	дEEPROM���
		 */
Sint32 OrgName_Save(Uchar8 *kdata) {
	return EEROM_write(EPR_ORGNAME, ORGNAME_W, kdata);
}

/*
 **	���ƣ�	��EEPROM�ж�ȡ��λ����
 **	��ڣ�	��λ���ƴ��ָ�루������λ���ƿ�ȡ����洢��ַ��
 **	���أ�	��EEPROM���
 */
Sint32 OrgName_Read(Uchar8 *kdata) {
	return EEROM_read(EPR_ORGNAME, ORGNAME_W, kdata);
}

void Sys_Set(void) {
	Uchar8 k;
	Uchar8 lgh;
	Uchar8 s[40] = { 0 };

	AllUPSW_Read(&(G_USERINFO));

	while (1) {
		cls();
		moveto(7, 1);
		bell(20);
		putstr("����������:");
		lgh = Key_PSW(s, USERPSW_W);
		if (lgh > 0) {
			if (memcmp(s, G_USERINFO.UserPSW[U_GLY], USERPSW_W) == 0) {
				break;
			} else {
				ErrorMsg("�������!");
				continue;
			}
		} else {
			if (s[1] == KEY_F2)
				return;
		}
	}
	while (1) {
		cls();
		moveto(1, 1);
		putstr("[1] ͳ��\n");				//	�����ó̶�����
		//putstr( "[8] ��������\n" );
		putstr("[2] �ڴ����\n");
		putstr("[3] �����޸�\n");
		//putstr( "[5] �����������\n" );
		//putstr( "[6] ��λ��������\n" );
		putstr("[4] �û���Ϣ��ʽ��\n");

		do {
			k = key(0);
		} while (k != 0x31 && k != 0x32 && k != 0x33 && k != 0x34 && k != 0x35 && k != 0x36 && k != 0x37 && k != 0x38 && k != KEY_F2);
		switch (k) {
		case '1':
			TJ();
			break;
			//case '8':	PRate_Set();	break;
		case '2':
			MM_Set();
			break;
		case '3':
			UserInfo_Set(U_GLY, U_GLY);
			break;
			//case '5':	POSID_Set();	break;
			//case '6':	OrgName_Set();	break;
		case '4':
			User_Format();
			break;
			//			case '8':	FKTK();			break;
		case KEY_F2:
			return;
			break;
		default:
			break;
		}
	}

}

void User_Format(void) {
	Uchar8 kdata[10];

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "00\0", 3);
	POSID_Save(kdata);

	memset(kdata, 0x00, sizeof (kdata));
	memcpy(kdata, "��λ����\0", 9);
	OrgName_Save(kdata);
	AllUPSW_Reset();
	FlowNO_Save(0);

	ErrorMsg("��ʽ���ɹ�");

}

/*
 **	Ӧ�ø��ݲ���Աͳ��
 */
void TJ(void) {
	Uint16 total, i;
	Uchar8 kdata[30], mdata[30], ndata[30];
	Uint16 sum;
	Uchar8 k, lgh;
	Uchar8 xb, yb;

	libopen(DBFNO_PARK);
	total = libsumr();

	while (1) {
		cls();
		moveto(1, 7);
		putstr("ͳ ��");
		putstr("\n�� �����շ����");
		putstr("\n�� ��ǰδ���ų���");

		do {
			k = key(0);
		} while (k != 0x31 && k != 0x32 && k != KEY_F2);

		if (k == KEY_F2)
			break;

		while (k == '1') {
			cls();
			moveto(17, 1);
			putstr("ֱ��ȷ�ϲ�ѯ��������");
			putstr_h("���ڸ�ʽ:yyyymmdd");
			moveto(5, 1);
			putstr("����������:\n");
			memset(kdata, 0x00, sizeof (kdata));
			xb = getx();
			yb = gety();
			moveto(xb, yb);
			lgh = ReadLine(kdata, 0, 8, 1);
			if (lgh == 0)
				;
			{
				if (kdata[1] == KEY_F2)
					break;
				if (kdata[1] == KEY_ENTER) {
					memset(kdata, 0x00, sizeof (kdata));
					Get_DateTime(0, kdata);
					putn_h(8, kdata);
					lgh = 8;
				}
			}
			if (lgh == 8) {
				sum = 0;
				Change_DateTime_Style(1, kdata);
				memset(mdata, 0x00, sizeof (mdata));
				memset(mdata, '0', 1);					//	������ݿ�Ϊ�����ʼ��Ϊ0�Ǳ�Ҫ��
				memset(ndata, 0x00, sizeof (ndata));
				for (i = 0; i < total; i++) {
					libset(i, LKSJ);
					libread(ndata);
					if (memcmp(kdata, ndata, 10) == 0)				//	����ʱ���ʽ�Ƚ�
							{
						memset(ndata, 0x00, sizeof (ndata));
						libset(i, YSJE);
						libread(ndata);
						stradd(ndata, mdata, P_MONEY_W);
						sum++;
					}
				}

				moveto(9, 1);
				putstr("����");
				printf("%d", sum);
				putstr("��\n");
				putstr("����");
				putstr(mdata);
				putstr("Ԫ");
				bell(50);
				k = key(0);
				if ((k == KEY_F2) || (k == KEY_CLS))
					break;
				else
					k = '1';
			}
		}

		if (k == '2') {
			sum = 0;
			for (i = 0; i < total; i++) {
				memset(kdata, 0x00, sizeof (kdata));
				libset(i, LKSJ);
				libread(kdata);
				if ((kdata[0] < 0x30) || (kdata[0] > 0x39))
				sum++;
			}

			cls();
			moveto(9, 1);
			putstr("δ���ų�����");
			printf("%d", sum);
			putstr("̨");
			bell(50);
			key(0);
		}
	}
}

/*
 **	���ƣ�	�ڴ�����
 **	��ڣ�	0x00��ɾ������ɼ�¼��
 0x01��ɾ��δ��ɼ�¼��
 0x02��ɾ�����м�¼��
 **	���أ�	��EEPROM���
 ����Ǵ�ԭ���ݿ��о��ܶ�����¼�ṹ���ͱ�����
 */
void MM_ManualClr(Uchar8 mode) {
	Uint16 last, i;
	//	Uint16 pbr;					//	parkbkp.dbf�ļ�¼����
	Uchar8 out_time[30];
	Uchar8 dbuf[32][32];
	FS_FILE *fp0, *fp1, *fp2;
	long flen;
	Uchar8 tbuf[4500];

	if (FS_find("park.bak") != 0) {
		ErrorMsg("�����´�prak.bak");
		key(0);
		return;
	}

	libopen(DBFNO_PARK);
	last = libsumr();
	if (last == 0) {
		//		ErrorMsg( "park���ݿ������!" );
		return;
	}
	last--;

	FS_creatfile("parkbkp.dbf", 0x00);
	fp1 = FS_fopen("parkbkp.dbf", "w");

	fp0 = FS_fopen("park.bak", "w");
	FS_fseek(fp0, 0, FS_SEEK_SET);
	flen = FS_length(fp0);
	FS_fread(tbuf, flen, 1, fp0);
	FS_fwrite(tbuf, flen, 1, fp1);
	FS_fclose(fp1);
	libuse("parkbkp.dbf", DBFNO_PARKBKP);

	memset(&dbuf[0][0], 0x00, sizeof (dbuf));				//	/*�ֶ�����ͬ*/���ݿ���ÿ����¼�Ĵ�С�ǹ̶��ģ�ֻ��Ҫ��ʼ������һ�μ��ɡ�
	screen(0x01);
	cls();
	for (i = 0; i <= last; i++) {
		if ((i % 8) == 0) {
			moveto(9, 1);
			clsn(9, 2);
			putstr("������");
		} else {
			putstr(".");
		}
		libopen(DBFNO_PARK);
		memset(out_time, 0x00, sizeof (out_time));
		libset(i, LKSJ);
		libread(out_time);
		libset(i, 0);
		libreadrec(&dbuf[0][0]);

		if (((mode == 0x00) & ((out_time[0] < 0x30) | (out_time[0] > 0x39))) | /*	����δ��ɼ�¼*/
		((mode == 0x01) & ((out_time[0] >= 0x30) & (out_time[0] <= 0x39)))) /*	��������ɼ�¼*/
		{
			libopen(DBFNO_PARKBKP);
			libapp();
			libset((libsumr() - 1), 0);
			libwriterec(&dbuf[0][0]);
		}
	}

	if (FS_find("park.dbf") == 0) {
		libclose(DBFNO_PARK);
		FS_deletefile("park.dbf");
	}
	FS_creatfile("park.dbf", 0x00);
	fp2 = FS_fopen("park.dbf", "w");
	FS_fwrite(tbuf, flen, 1, fp2);
	FS_fclose(fp0);
	FS_fclose(fp2);
	libuse("park.dbf", DBFNO_PARK);
	libopen(DBFNO_PARKBKP);
	last = libsumr();
	if (last > 0) {
		for (i = 0; i < last; i++) {
			libopen(DBFNO_PARKBKP);
			libset(i, 0);
			libreadrec(&dbuf[0][0]);

			libopen(DBFNO_PARK);
			libapp();
			libset((libsumr() - 1), 0);
			libwriterec(&dbuf[0][0]);
		}
	}
	libclose(DBFNO_PARKBKP);
	FS_deletefile("parkbkp.dbf");
}
void MM_DEL(Uchar8 mode) {
	Uint16 last, i;
	//	Uint16 pbr;					//	parkbkp.dbf�ļ�¼����
	Uchar8 out_time[30];
	Uchar8 dbuf[32][32];
	FS_FILE *fp0, *fp1, *fp2;
	long flen;
	Uchar8 tbuf[4500];

	if (FS_find("BOWEI.bak") != 0) {
		ErrorMsg("�����´�BOWEI.bak");
		key(0);
		return;
	}

	libopen(DBFNO_BOWEI);
	last = libsumr();
	if (last == 0) {
		//		ErrorMsg( "park���ݿ������!" );
		return;
	}
	last--;

	FS_creatfile("parkbkp.dbf", 0x00);
	fp1 = FS_fopen("parkbkp.dbf", "w");

	fp0 = FS_fopen("BOWEI.bak", "w");
	FS_fseek(fp0, 0, FS_SEEK_SET);
	flen = FS_length(fp0);
	FS_fread(tbuf, flen, 1, fp0);
	FS_fwrite(tbuf, flen, 1, fp1);
	FS_fclose(fp1);
	libuse("parkbkp.dbf", DBFNO_PARKBKP);

	memset(&dbuf[0][0], 0x00, sizeof (dbuf));				//	/*�ֶ�����ͬ*/���ݿ���ÿ����¼�Ĵ�С�ǹ̶��ģ�ֻ��Ҫ��ʼ������һ�μ��ɡ�
	screen(0x01);
	cls();
	for (i = 0; i <= last; i++) {
		if ((i % 8) == 0) {
			moveto(9, 1);
			clsn(9, 2);
			putstr("������");
		} else {
			putstr(".");
		}
		libopen(DBFNO_BOWEI);
		memset(out_time, 0x00, sizeof (out_time));
		libset(i, LKSJ);
		libread(out_time);
		libset(i, 0);
		libreadrec(&dbuf[0][0]);

		if (((mode == 0x00) & ((out_time[0] < 0x30) | (out_time[0] > 0x39))) | /*	����δ��ɼ�¼*/
		((mode == 0x01) & ((out_time[0] >= 0x30) & (out_time[0] <= 0x39)))) /*	��������ɼ�¼*/
		{
			libopen(DBFNO_PARKBKP);
			libapp();
			libset((libsumr() - 1), 0);
			libwriterec(&dbuf[0][0]);
		}
	}

	if (FS_find("BOWEI.DBF") == 0) {
		libclose(DBFNO_BOWEI);
		FS_deletefile("BOWEI.DBF");
	}
	FS_creatfile("BOWEI.DBF", 0x00);
	fp2 = FS_fopen("BOWEI.DBF", "w");
	FS_fwrite(tbuf, flen, 1, fp2);
	FS_fclose(fp0);
	FS_fclose(fp2);
	libuse("BOWEI.DBF", DBFNO_BOWEI);
	libopen(DBFNO_BOWEI);
	last = libsumr();
	if (last > 0) {
		for (i = 0; i < last; i++) {
			libopen(DBFNO_PARKBKP);
			libset(i, 0);
			libreadrec(&dbuf[0][0]);

			libopen(DBFNO_BOWEI);
			libapp();
			libset((libsumr() - 1), 0);
			libwriterec(&dbuf[0][0]);
		}
	}

	libclose(DBFNO_PARKBKP);
	FS_deletefile("parkbkp.dbf");

}
/*
 **	���ƣ�	Memory Management�ڴ��������
 **	��ڣ�	��
 **	���أ�	��
 **	˵����	�Զ����ʹ��	�Զ����Զ����n��ǰ�����ݣ����ֶ������������ɼ�¼��������м�¼��
 */
void MM_Set(void) {
	Uchar8 k, ka;
	Uchar8 lgh, kdata[30], mdata[30];
	Uchar8 xb, yb;

#if 0
	//
	//	putstr( "�� ʱ��:" );
	//	memset( kdata, 0x00, sizeof(kdata) );
	//	sprintf( kdata, "%02d", mdata[1] );
	//	putstr( kdata );
	//	putstr( "ǰ.\n" );
	//	putstr( "�� ����:" );
	//	switch( i )
	//	{
	//		case 0x01:	putn_x( 8, "��������", 1 );	break;
	//		case 0x02:	putn_x( 8, "δ �� ��", 1 );	break;
	//		case 0x03:	putn_x( 8, " ��  �� ", 1 );	break;
	//	}
	//	putstr( "��¼" );
	//
	//
	//	memset( kdata, 0x00, sizeof(
	//
	//
	//
#endif

	while (1) {
		cls();
		moveto(1, 8);
		putstr("�ڴ����");
		putstr("\n�� �ֶ����");
		//		putstr( "\n�� �Զ��������" );
		moveto(19, 1);
		putstr("[F2] �˳�");

		do {
			k = key(0);
		} while (k != 0x31 && /*k!=0x32&&*/k != KEY_F2);
		if (k == KEY_F2)
			break;
		while (k == 0x31) {
			cls();
			moveto(1, 1);
			putstr("�� �������������¼.");
			putstr("�� ���δ���ż�¼.\n");
			putstr("�� �������ͣ����¼.");
			moveto(19, 1);
			putstr("[F2] �˳�");
			do {
				ka = key(0);
			} while (ka != 0x31 && ka != 0x32 && ka != 0x33 && ka != KEY_F2);
			if (ka == KEY_F2)
				break;
			switch (ka) {
			case 0x31:
				MM_ManualClr(0x00);
				break;
			case 0x32:
				MM_ManualClr(0x01);
				break;
			case 0x33:
				MM_ManualClr(0x02);
				break;
			default:
				continue;
				break;
			}
			ErrorMsg("����ɹ�");
		}
		memset(mdata, 0x00, sizeof (mdata));
		MM_Read(mdata);
		while (k == 0x32) {
			cls();
			moveto(1, 1);
			putstr("���Զ������");
			if (mdata[0] == 0xCC) {
				putn_x(4, "����", 1);
			} else {
				putn_x(4, "�ر�", 1);
			}
			putstr(".");
			putstr("\n���Զ����");
			xb = getx();
			yb = gety();
			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%02d", mdata[1]);
			putn_x(2, kdata, 1);
			putstr("��ǰ�����������ż�¼.");
			moveto(17, 1);
			putstr("[ȷ��] ����\n[F2] �˳�");
			do {
				ka = key(0);
			} while (ka != 0x31 && ka != 0x32 && ka != KEY_ENTER && ka != KEY_F2);
			if (ka == KEY_F2)
				break;
			switch (ka) {
			case 0x31:
				if (mdata[0] == 0xCC)
					mdata[0] = 0x00;
				else
					mdata[0] = 0xCC;
				break;
			case 0x32:
				moveto(xb, yb);
				putstr("  ");
				moveto(xb, yb);
				memset(kdata, 0x00, sizeof (kdata));
				lgh = ReadLine(kdata, 0, 2, 0);
				if (lgh == 0) {
					continue;
				} else {
					mdata[1] = stoi(2, kdata);
				}
				break;
				case KEY_ENTER:
				MM_Save(mdata);
				ErrorMsg("����ɹ�");
				break;
				default:
				break;
			}
		}
	}

}

Sint32 MM_Read(Uchar8 *s) {
	return (EEROM_read(EPR_MM, 3, s));
}
Sint32 MM_Save(Uchar8 *s) {
	return (EEROM_write(EPR_MM, 3, s));
}

//���복��
//����2 +
int IN_put_CHE_PAI(uchar *s) {
	uchar ch, cdata[100], kdata[100], chebai_f[100], chebai_s[100];
	uchar hdata[4];        //  Ĭ���׸�����ͷ����chebai_f��������
	int i, input_time = 0;
	clsn(7, 5);
	memset(chebai_f, 0x00, 100);
	memset(chebai_s, 0x00, 100);
	memset(hdata, 0x00, sizeof (hdata));
	memcpy(chebai_f, "�㴨���ʸӹ��ڻ������������³����������������������ԥ���Ʋ�", 62);
	//                      "�����ʸӹ��ڻ������������³����������������������ԥ���Ʋ���"�����ظ�˳�����й�62���ֽڣ�
	memcpy(hdata, chebai_f, 2);               //  ���ƴ�ͷ
	memcpy(chebai_s, "ABCDEFGHIJKLMNOPQRSTUVWXYZѧ", 28);
	memset(kdata, 0x00, 20);
	memset(cdata, 0x00, 20);
	memset(kdata, 0x00, 20);
	memset(cdata, 0x00, 20);
	moveto(3, 1);
	putstr("�����복�ƺ���:");
	moveto(5, 1);
	memcpy(kdata, hdata, 2);
	putstr(hdata);
	while (1) {
		c1: i = display_chepai(chebai_f, 0x31, cdata);
		if (i == 0xfe) {
			;
		} else if (i == 0xfb) {
			return 2;
		} else if (i == 0xff) {
			if (cdata[0] == KEY_CLS) {
				moveto(5, 1);
				putstr("    ");
				moveto(5, 1);
				putstr("_");
				;
			} else if (cdata[0] == KEY_F2) {
				return 1;
			}
		} else if (i == 0) {
			memcpy(kdata, hdata, 2);
			moveto(5, 1);
			putstr(hdata);
			putstr("_");
			break;
		} else {
			moveto(5, 1);
			putn_h(2, &chebai_f[i]);
			putstr("_");
			memset(kdata, 0x00, 20);
			memcpy(kdata, &chebai_f[i], 2);
			break;
		}
	}
	while (1) {
		i = display_chepai(chebai_s, 0x32, cdata);
		if (i == 0xff) {
			if (cdata[0] == KEY_CLS) {
				if (input_time == 0) {
					moveto(5, 1);
					putstr("    ");
					moveto(5, 1);
					putstr("_");
					;
					goto c1;
				}
				input_time--;
				if (input_time <= 0) {
					input_time = 0;
				}
				moveto(5, 3 + input_time);
				putstr("  ");
				moveto(5, 3 + input_time);
				putstr("_");
			} else if (cdata[0] == KEY_F2) {
				return 1;
			}
		} else if (i == 0xfb) {
			return 2;
		} else if (i == 0xfe) {
			while (1) {
				clsn(15, 6);
				moveto(19, 17);
				putstr("123");
				moveto(5, 3 + input_time);
				do {
					ch = key(0);
				} while (ch != KEY_CLS && ch != KEY_F1 && ch != KEY_F2 && ch != 0x30 && ch != 0x31 && ch != 0x32 && ch != 0x33 && ch != 0x34 && ch != 0x35 && ch != 0x36 && ch != 0x37 && ch != 0x38
						&& ch != 0x39);
				if (ch == KEY_F1) {
					break;
				} else if (ch == KEY_F2) {
					return 1;
				} else if (ch == KEY_CLS) {
					input_time--;
					if (input_time <= 0) {
						input_time = 0;
					}
					if (input_time == 0) {
						moveto(5, 1);
						putstr("    ");
						moveto(5, 1);
						putstr("_");
						;
						goto c1;
					}
					moveto(5, 3 + input_time);
					putstr("  ");
					moveto(5, 3 + input_time);
					putstr("_");
				} else {
					kdata[2 + input_time] = ch;
					putch(ch);
					putstr("_");
					input_time++;
				}
				if (input_time == 6) {
					break;
				}
			}
		} else {
			moveto(5, 3 + input_time);
			if (i < (strlen(chebai_s) - 2)) {
				memcpy(&kdata[2 + input_time], &chebai_s[i], 1);
				putn_h(1, &chebai_s[i]);
			} else {
				memcpy(&kdata[2 + input_time], &chebai_s[i], 2);
				putn_h(2, &chebai_s[i]);
			}

			putstr("_");
			input_time++;
		}
		if (input_time == 6) {
			break;
		}
	}
	memcpy(s, kdata, 10);
	return 0;
}

//������� 0x31 �����ĸ�ͺ���
int display_chepai(uchar *pmenu, uchar tt, uchar *cdata) {
	int i, input_s = 0, input_m = 0, total = 0;
	uchar k;
	int current_bar = 0, k_temp = 0;    //������λ��
	int items_ptr = 0;          //������ָ��
	int items = 0, items_y = 0, items_x = 0; //����ʾ��
	uchar temp[3] = { 0 };
	U8 y;
	int leg_p;

	leg_p = strlen(pmenu);
	if (tt != 0x31) {
		leg_p--;
	}
	moveto(10, 1);
	putstr("��F1�л������ֻ���ĸ");
	if (tt == 0x31) //����ռ2������λ2��
			{
		input_s = 2;
		input_m = 20;
		items_x = leg_p / 20; //�ܵ���������
		items_y = leg_p % 20; //�ܵ���������
	} else         //��ĸ
	{
		input_s = 1;
		input_m = 10;
		items_x = leg_p / 10; //�ܵ���������
		items_y = leg_p % 10; //�ܵ���������
	}
	if (items_y > 0) {
		items = items_x + 1;
	}
	while (1) {
		clsn(17, 4);
		moveto(17, 2);
		putstr("0 1 2 3 4 5 6 7 8 9");
		moveto(19, 1);
		if (tt == 0x31) //����ռ2������λ2��
				{
			putn_h(20, &pmenu[items_ptr]);
			y = 1 + current_bar;
		} else {
			for (i = 0; i < 10; i++) {
				putstr(" ");
				if ((items_ptr + i) < leg_p) {
					putn_h(1, &pmenu[items_ptr + i]);
				}
			}
			y = 2 + current_bar * 2;
			if (y > 20) {
				y = 2;
			}
		}
		moveto(19, y);
		total = items_ptr + current_bar;
		memset(temp, 0x00, sizeof (temp));
		if ((total == (leg_p - 1)) & (input_s == 1)) {
			memcpy(temp, &pmenu[total], 2);
		} else {
			memcpy(temp, &pmenu[total], input_s);
		}
		putstr_x(temp, 1);           //����
		drawrect(1, 121, 159, 159);
		k = key(0);
		if (k == 0x8B)   //�ҷ�
				{
			k_temp = 2;
			current_bar = current_bar + input_s;
			total = items_ptr + current_bar;
			if (total >= leg_p) {
				current_bar = 0;
			} else {
				if (current_bar >= input_m) {
					current_bar = 0;
				}
			}
		} else if (k == 0X8A)  //��
				{
			k_temp = 2;
			current_bar = current_bar - input_s;
			if (current_bar < 0) {
				i = items_ptr - (items_x * input_m);
				if (i == 0) //���һ��
						{
					current_bar = items_y - input_s;
				} else {
					current_bar = input_m - input_s;
				}
			}
		} else if (k == KEY_UP) //�Ϸ�
		{
			items_ptr = items_ptr - input_m;
			total = items_ptr + current_bar;
			if (total < 0) {
				items_ptr = items_x * input_m; //�����һ��
				current_bar = 0;
			}
		} else if (k == KEY_DOWN) //�·�
		{
			items_ptr = items_ptr + input_m;
			total = items_ptr + current_bar;
			if (total >= leg_p) {
				current_bar = 0;
				total = items_ptr + current_bar;
				if (total > leg_p) {
					items_ptr = 0;
				}
			}
		} else if (k == KEY_ENTER) //ȷ��
		{
			return items_ptr + current_bar; //��ǰ����
		} else if (k == KEY_CLS)   //�����ּ����£�����
		{
			cdata[0] = KEY_CLS;
			return 0xff;
		} else if (k == KEY_F1) {
			return 0xfe;
		} else if (k == KEY_F2) {
			cdata[0] = KEY_F2;
			return 0xff;
		} else if (k == '+') {
			return 0xfb;
		}
		//      else if(k=='.')
		//      {
		//          return 0xff;
		//      }
		else if ((k >= '1') || (k <= '9')) {
			cdata[0] = k;
			i = stoi(1, cdata);
			i = items_ptr + i * input_s;
			return i;       //ֱ�ӷ�������
		}
	}
}

//��һ��16���Ƶ����ֳ�2���� 0x12 --->0x31 0x32
//��ʮ��������ת��ΪASCII��,����ת��������鳤��
int S16toAscii(uchar *s, uchar *sout, int leng) {
	uchar temp[500];
	uchar cdata[500];
	int i = 0, j = 0, m = 0;
	memcpy(cdata, s, leng);
	for (i = 0; i < leng; i++, j++) {
		temp[j] = ((cdata[i] & 0xf0) >> 4) + 0x30;
		j++;
		temp[j] = (cdata[i] & 0x0f) + 0x30;
	}
	for (m = 0; m < j; m++) {
		if (temp[m] >= 0x3a && temp[m] <= 0x3f)
			temp[m] = temp[m] + 0x07;
	}
	memcpy(sout, temp, j);
	return j;
}

U8 Key_PSW(U8 *kdata, U8 lgh) {
	U8 i, k;
	U8 x_start, y_start;

	putstr("[");
	x_start = getx();
	y_start = gety();
	memset(kdata, ' ', lgh);
	putstr(kdata);
	putstr("]");
	moveto(x_start, y_start);
	i = 0;								//	��Ҫ���������
	while (1) {
		if (i < lgh) {
			moveto(x_start, y_start + i);
			putch_h('_');
			k = key(0);
			if (k == KEY_CLS) {
				if (i > 0) {
					kdata[i - 1] = 0x00;
					moveto(x_start, y_start + i);
					putstr(" ");
					i--;
				} else {
					i = 0;
				}
			} else if (((k >= 0x30) & (k <= 0x39)) | (k == '.')) {
				kdata[i] = k;
				moveto(x_start, y_start + i);
				putstr("*");
				i++;
			} else if (k == KEY_ENTER) {
				return i;
			} else {
				kdata[1] = k;
				return 0;
			}
		} else {
			k = key(0);
			if (k == KEY_CLS) {
				i--;
			} else if (((k >= 0x30) & (k <= 0x39)) | (k == '.')) {
				;
			} else if (k == KEY_ENTER) {
				return lgh;
			} else {
				kdata[1] = k;
				return 0;
			}
		}
	}
}

//startline  //��ʼ��
//totals     //�ܼ��ж�����
//items      ��LCD���ö�������ʾ
//pmenu      ����
//���ذ���ֵ
U8 display_menu(U8 startline, U8 totals, U8 itmes_total, U8 *pmenu[], uchar *kr) {
	int i;

	U8 current_bar = 0;		//������λ��
	U8 items_ptr = 0;			//������ָ��
	U8 items = 0;				//����ʾ��
	U8 tdata[40];
	U8 k, y;

	items = itmes_total;

	while (1) {
		clsn(startline, items * 2);
		if (totals > 0) {
			if (items > totals) {
				items = totals;
			}
			for (i = 0; i < items; i++) {
				MoveTo(1, startline + (i << 1));
				putstr_x(pmenu[items_ptr + i], 0);
			}
			y = startline + (current_bar << 1);
			clsn(y, 2);
			MoveTo(1, y);
			putstr_x(pmenu[items_ptr + current_bar], 1);			//����
		}
		drawrect(0, (startline - 1) * 8, 159, (startline + (itmes_total * 2) - 1) * 8 - 1);
		k = key(0);
		kr[0] = k;			//��������ֵ
		if (k == KEY_UP)		//�Ϸ�
		{
			if (current_bar > 0)			//��ǰ�������ǵ�һ��ʱ�������ƶ�����
					{
				current_bar--;
			} else						//���ǵ�һ��ʱ���ƶ�����ָ��
			{
				if (items_ptr > 0)			//��֤��ʾ��
						{
					items_ptr--;
				}
			}
		}

		else if (k == KEY_DOWN)	//�·�
		{
			if (current_bar < (items - 1))		//��ǰ�����������һ��ʱ�������ƶ�����
					{
				current_bar++;
			} else							//�������һ��ʱ���ƶ�����ָ��
			{
				if ((totals - items_ptr) > items) //��֤��ʾ��
						{
					items_ptr++;
				}
			}
		} else if (k == KEY_ENTER)	//ȷ��
		{
			return items_ptr + current_bar;	//��ǰ����
		} else if (k == KEY_CLS)		//�����ּ����£�����
		{
			return 0xff;
		}
		//		else if(k==KEY_F1)
		//		{
		//			return 0xff;
		//		}
		else if (k == KEY_F2) {
			return 0xff;
		} else if (k == '+') {
			return 0xff;
		} else if (k == '.') {
			return 0xff;
		} else if ((k >= '1') || (k <= '9')) {
			k = k & 0x0f;
			if (k > totals) {
				return 0;	//̫����ֱ�ӷ��ص�һ��
			}
			return k - 1;		//ֱ�ӷ�������
		}
		//	ʱ��ˢ��
		memset(tdata, 0x00, sizeof (tdata));
		Get_DateTime(1, tdata);
		moveto(19, 2);
		putn_h(16, tdata);
		Battery_display(19, 20);

	}
}

void ShouFei_ChaXun(void) {
	Uint16 total, i;
	Uchar8 mdata[30], ndata[30], txycb[30], tddata[30], mtddata[30];
	Uchar8 kdata[30];
	Uint16 sum, unb;
	Uchar8 k, lgh;
	Uchar8 xb, yb;
	libopen(DBFNO_PARK);
	total = libsumr();

	while (1) {
		cls();
		moveto(15, 1);
		putstr("���ڸ�ʽ:yyyymmdd\n");
		putstr_h("��ȷ�ϲ�ѯ�����շ�");
		moveto(5, 1);
		putstr("����������:\n");
		memset(kdata, 0x00, sizeof (kdata));
		xb = getx();
		yb = gety();
		moveto(xb, yb);
		lgh = ReadLine(kdata, 0, 8, 1);
		if (lgh == 0)
			;
		{
			if (kdata[1] == KEY_F2)
				break;
			if (kdata[1] == KEY_ENTER) {
				memset(kdata, 0x00, sizeof (kdata));
				Get_DateTime(0, kdata);
				putn_h(8, kdata);
				lgh = 8;
			}
		}
		if (lgh == 8) {
			sum = 0;
			unb = 0;
			Change_DateTime_Style(1, kdata);
			memset(mdata, 0x00, sizeof (mdata));
			memset(mtddata, 0x00, sizeof (mtddata));
			memset(mdata, '0', 1);						//	������ݿ�Ϊ�����ʼ��Ϊ0�Ǳ�Ҫ��
			memset(mtddata, '0', 1);
			memset(ndata, 0x00, sizeof (ndata));
			memset(tddata, 0x00, sizeof (tddata));
			for (i = 0; i < total; i++) {
				libset(i, LKSJ);
				libread(ndata);
				if (memcmp(kdata, ndata, 10) == 0)				//	����ʱ���ʽ�Ƚ�
						{
					memset(txycb, 0x00, sizeof (txycb));
					libset(i, TCD);
					libread(txycb);
					if (txycb[0] == '2') {
						memset(tddata, 0x00, sizeof(tddata));
						libset(i, YSJE);
						libread(tddata);
						stradd(tddata, mtddata, P_MONEY_W);
						unb++;
					} else {
						memset(ndata, 0x00, sizeof(ndata));
						libset(i, YSJE);
						libread(ndata);
						stradd(ndata, mdata, P_MONEY_W);
						sum++;
					}

				}
			}
			moveto(9, 1);
			putstr("������");
			printf("%d", sum);
			putstr("��");
			putstr("����");
			putstr(mdata);
			putstr("Ԫ\n");
			putstr("�ӵ���");
			printf("%d", unb);
			putstr("��");
			putstr("����");
			putstr(mtddata);
			putstr("Ԫ");
			bell(50);
			k = key(0);
			if ((k == KEY_F2))
				break;
			else
				k = '1';
		}
	}
}

void CheWei_ChaXun(void) {
	//	r	0��ˮ�� 4����ʱ�� 5�뿪ʱ��
	U8 k, kr;
	//	U8 sum;
	U8 total, items;	//	�ܼ��ж�����Ҫ��ʾ	��Ļ���ö�������ʾ
	U8 lgh;
	U8 kdata[40];
	U8 tdata[40];
	U8 mdata[40];
	U8 ndata[40];
	U8 outdata[40];     //����ʱ��
	Sint32 i, r;
	TYPE_PARKINFO ParkInfo;

	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));

	Uint16 index[20];	//	��ѯ���ļ�¼��
	P_U8 menu[20] = { "1                   ", "2                   ", "3                   ", "4                   ", "5                   ", "6                   ", "7                   ",
			"8                   ", "9                   ", "10                  ", "11                  ", "12                  ", "13                  ", "14                  ",
			"15                  ", "16                  ", "17                  ", "18                  ", "19                  ", "20                  ", };

	while (1) {
		cb3: cls();

		moveto(1, 1);
		memset(kdata, 0x00, sizeof (kdata));
		putstr("�����벴λ��:");
		lgh = ReadLine(kdata, 0, 4, 1);
		if (lgh == 0) {
			if (kdata[1] == KEY_F2) {
				return;
			} else {
				continue;
			}
		} else {
			libopen(DBFNO_PARK);

			i = 0;
			for (r = libsumr() - 1; r >= 0; r--) {
				libset(r, BWH);
				memset(tdata, 0x00, sizeof (tdata));
				libread(tdata);
				if (memcmp(tdata, kdata, lgh) == 0) {
					if (i <= 19) {
						libset(r, LKSJ);
						memset(outdata, 0x00, sizeof (outdata));
						libread(outdata);
						libset(r, JRSJ);
						memset(mdata, 0x00, sizeof (mdata));
						libread(mdata);
						libset(r, CHEPAI);					//	��������
						memset(ndata, 0x00, sizeof (ndata));
						libread(ndata);
						memset(&(ndata[8]), ' ', 1);
						memcpy(&(ndata[9]), &(mdata[11]), 5);
						memcpy(&(ndata[15]), &(outdata[11]), 5);
						ndata[14] = '_';
						memcpy(menu[i], ndata, 20);
						index[i] = r;
					}
					i++;
				}
			}
		}
		if (i > 19) {
			total = 19 + 1;
		} else {
			total = i;
		}
		cls();
		moveto(1, 1);
		putstr("");
		putstr(kdata);
		putstr("�����");
		printf("%d", total);
		putstr("����¼");
		moveto(3, 1);
		putstr("�����ơ�������ʱ�䡿");
		//			|��A12345 09-11 12:34|
		if (total < 8) {
			items = total;
		} else {
			items = 8;
		}
		k = display_menu(5, total, items, menu, &kr);

		if (k == 0xFF) {
			return;
		} else {
			//ParkInfo.r = index[k];      				//	�������ݿ��д�����¼����Ϣ
			memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
			ParkInfo.r = index[k];                  //  �������ݿ��д�����¼����Ϣ
					libset(ParkInfo.r, CHEPAI);
					libread(ParkInfo.chepai);
					//          libset( ParkInfo.r, BWH );
					//          libread( ParkInfo.boweihao );
					libset(ParkInfo.r, JRSJ);
					libread(ParkInfo.time_in);
					Change_DateTime_Style(0, ParkInfo.time_in);
					libset(ParkInfo.r, LKSJ);
					libread(ParkInfo.time_out);
					Change_DateTime_Style(0, ParkInfo.time_out);
					//          libset( ParkInfo.r, ZWSJ );
					//          libread( ParkInfo->time_disp );
					libset(ParkInfo.r, YSJE);
					libread(ParkInfo.charge_due);
					PInfo_Calc(&ParkInfo);
					CardInfo_Disp(&ParkInfo);

					//CardInfo_Disp( &ParkInfo );

					if (key(0) == KEY_F2)
					goto cb3;
				}
			}
		}

void BuDanMune(void) {
	cls();
	Uchar8 k;
	while (1) {
		moveto(5, 1);
		putstr("[1] ����\n");
		putstr("[2] �ӵ�\n");

		do {
			k = key(0);
		} while (k != 0x31 && k != 0x32 && k != 0x89 && k != KEY_F2);
		switch (k) {
		case 0x31:
			BuDan();
			break;
		case 0x32:
			taodan();
			break;
		case KEY_F2:
			return;
			break;
		}
	}
}

void BuDan(void) {
	cls();
	Uchar8 k;
	Uchar8 xb, yb;
	Uchar8 jmbz, cb;
	Uchar8 lgh, timelgh, rt;
	//Uchar8 jmbz;
	Uchar8 kdata[20];
	Uchar8 timedata[20];            //�����ʱ��
	Uchar8 bwhdata[20];
	TYPE_PARKINFO ParkInfo;
	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));
	while (1) {
		cls();
		memset(kdata, 0x00, sizeof (kdata));
		rt = IN_put_CHE_PAI(kdata);
		if (rt != 0)
			return;
		cls();
		//Change_DateTime_Style( 0, timedata );
		memset(ParkInfo.chepai, 0x00, sizeof (ParkInfo.chepai));
		memcpy(ParkInfo.chepai, kdata, 9);
		l2: cls();
		putstr("���ƺ�Ϊ:\n");
		putstr(kdata);
		putstr("\n\n\n\n");
		putstr("�����벴λ��");
		memset(bwhdata, 0x00, sizeof (bwhdata));
		lgh = ReadLine(bwhdata, 0, 4, 1);
		if (lgh == 0) {
			if (bwhdata[1] == KEY_F2) {

				continue;
			} else {
				goto l2;
			}
		}
		memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
		memcpy(ParkInfo.bwh, bwhdata, 4);
		jmbz = JMPD_DB(&ParkInfo);
		cb = ChaZhaoBw(&ParkInfo);
		if (jmbz == FLAG_IN) {
			ErrorMsg("�˳����ظ�");
			key(0);
			goto l2;
		}
		if (cb == FLAG_IN) {
			ErrorMsg("��λ��\n�ѱ�ռ��");
			key(0);
			goto l2;
		} else if (cb == FLAG_FOE) {
			ErrorMsg("�Ƿ���λ��");
			key(0);
			goto l2;
		}
		if (jmbz == FLAG_OUT) {
			cbtxy: cls();
			//putstr( "�밴ȷ�ϼ�������ʱ��\n");
			putstr("������ͣ���ʱ��\n");
			//putstr( "����������:\n" );
			moveto(17, 1);
			putstr_h("���ڸ�ʽ:\n");
			putstr_h("20120922080000\n");
			//moveto( 6, 1 );
			xb = getx();
			yb = gety();
			moveto(10, yb);
			memset(timedata, 0x00, sizeof (timedata));
			//if(key(0)==KEY_F2)
			//{
			//     goto l2;
			//}
			timelgh = ReadLine(timedata, 0, 14, 0);
			if (timelgh == 0)
				continue;
			if (timelgh == 14) {
				JIAOYANGTIME(timedata);

				if (PUBLIC_BOOLEN == 1) {
					ErrorMsg("��ʽ����");

					goto cbtxy;
				}
			} else {
				ErrorMsg("��ʽ����");
				goto cbtxy;
			}
			//Change_DateTime_Style( 0, timedata );

			memset(ParkInfo.time_in, 0x00, sizeof (ParkInfo.time_in));
			memcpy(ParkInfo.time_in, timedata, 14);
			//putstr(ParkInfo.time_in);
			//memset( ParkInfo.time_in, 0x00, sizeof(ParkInfo.time_in) );
			//memcpy( ParkInfo.time_in,timedata, 14);

			//Get_DateTime( 0, timedata );
			//memset( ParkInfo.time_in, 0x00, sizeof(ParkInfo.time_in) );
			//memcpy( ParkInfo.time_in, timedata, sizeof(ParkInfo.time_in) );

			//memset( ParkInfo.time_out, 0x00, sizeof(ParkInfo.time_out) );
			//Get_DateTime( 0, ParkInfo.time_out );
			//PInfo_Calc( &ParkInfo );
			clsn(17, 4);
			cls();
			moveto(5, 5);
			putstr("[�Ƿ�ȷ�ϣ�]\n");
			moveto(7, 5);
			putstr("[ȷ�ϼ�ȷ��]\n");
			moveto(9, 3);
			putstr("[F2�����ϸ�����]\n");
			//putstr( "\n[����] ����(����ӡ)" );

			k = key(0);
			if (k == KEY_F2) {
				goto cbtxy;
			}
			while (k == KEY_ENTER) {
				//memset( ParkInfo.time_out, 0x00, sizeof(ParkInfo.time_out) );
				//Get_DateTime( 0, ParkInfo.time_out );
				//memset( ParkInfo.time_in, 0x00, sizeof(ParkInfo.time_out) );
				//PInfo_Calc( &ParkInfo );
				memset(ParkInfo.czy, 0x00, sizeof (ParkInfo.czy));      //����Ա����Ϣ
						memcpy(ParkInfo.czy, AdminId, 3);
						libopen(DBFNO_PARK);
						G_Sjid = Sjuid_Read();

						if (libsumr() <= 3000) {
							libapp();
						}
						if (G_Sjid >= 3000) {
							G_Sjid = 0;
							ParkInfo.r = G_Sjid;
						} else {
							G_Sjid++;
							ParkInfo.r = G_Sjid;
						}
						Sjuid_Save(G_Sjid);

						//ParkInfo.r = libsumr();
						//	libapp();
						G_FLOWNO = FlowNO_Read();
						G_FLOWNO++;
						ParkInfo.flowNO = G_FLOWNO;
						FlowNO_Save(G_FLOWNO);

						BudanPInfo_Save(&ParkInfo);

						ParkInfo.flag = FLAG_IN;
						moveto(12, 5);
						putstr("����ɹ�");
						BWState_Ref(ParkInfo.bwh, FLAG_BUSY, ParkInfo.chepai);
						GPRS_netconnect();
						GPRS_BUDANSendrcv(&ParkInfo);//������
						break;
					}
				}
			}
		}

int GPRS_BUDANSendrcv(TYPE_PARKINFO *ParkInfo) {
	int cRet;
	unsigned short rlen;
	//int CIRCLE_TIME3=1;
	Uchar8 tdata[40];
	Uchar8 rt;
	Uchar8 sbuf[200];
	Uchar8 kdata[40];
	Uchar8 tmpdata[20];
	//uchar k;
	Uint16 r;
	memset(sbuf, 0x00, 200);
	memset(tmpdata, 0x00, sizeof (tmpdata));
	cominit(B38400, 0x03, UART_ON);
	while (1) {
		cls();
		sbuf[0] = '0';
		memcpy(&(sbuf[1]), ParkInfo->chepai, 9);
		memcpy(&(sbuf[10]), ParkInfo->bwh, 4);
		memcpy(&(sbuf[14]), ParkInfo->time_in, 14);
		memcpy(&(sbuf[28]), AdminId, 3);
		memcpy(&(sbuf[31]), AdminPassId, 6);

		memset(kdata, 0x00, sizeof (kdata));
		sprintf(kdata, "%06d", ParkInfo->flowNO);

		memcpy(&(sbuf[37]), kdata, 6);

		memcpy(&(sbuf[43]), posiddata, 32);
		memcpy(&(sbuf[75]), "2", 1);

		putstr("\n���ڷ�������...\n");

		cRet = WNetTxd(sbuf, 76);
		if (cRet == 0) {

			memset(tdata, 0x00, sizeof (tdata));
			rt = WNetRxd(tdata, &rlen, 2000);
			if (rt == 0) {
				memcpy(tdata, &(tdata[0]), 1);
				if (tdata[0] == '1') {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "1", 1);                //����ʧ��
					libset(r, SCCG);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("���ͳɹ�");
					WNetIPClose("1", 1000);

					moveto(7, 1);
					putstr("�����������");
					key(0);
					return 1;
				} else {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "2", 1);                //����ʧ��
					libset(r, SCCG);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("����ʧ��");
					WNetIPClose("1", 1000);

					putstr("�����������");
					key(0);
					return 1;
				}
			} else {
				libopen(DBFNO_PARK);
				r = ParkInfo->r;
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, "2", 1);                //����ʧ��
				libset(r, SCCG);//���ű�־  0˵������ʧ��
				libwrite(kdata);
				putstr("����ʧ��");
				WNetIPClose("1", 1000);

				putstr("�����������");
				key(0);
				return 1;
			}
		} else {
			libopen(DBFNO_PARK);
			r = ParkInfo->r;
			memset(kdata, 0x00, sizeof(kdata));
			memcpy(kdata, "2", 1);                //����ʧ��
			libset(r, SCCG);//���ű�־  0˵������ʧ��
			libwrite(kdata);
			putstr("����ʧ��");
			WNetIPClose("1", 1000);

			putstr("�����������");
			key(0);
			return 1;
		}
	}
	return 0;
}
//��������
void alert(Uchar8 *message) {
	cls();
	//putstr(&message);
}
void taodan(void) {
	cls();
	Uchar8 rt, k;
	Uchar8 jmbz;
	Uchar8 kdata[20];

	//Uchar8 exittime[20];
	TYPE_PARKINFO ParkInfo;
	memset((Uchar8 *) (&ParkInfo), 0x00, sizeof (ParkInfo));

	while (1) {
		bbbb: cls();
		memset(kdata, 0x00, sizeof (kdata));
		putstr("�����벴λ��");
		rt = ReadLine(kdata, 0, 4, 1);
		if (rt == 0) {
			if (kdata[1] == KEY_F2) {
				return;
			} else {
				continue;
			}
		}
		memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
		memcpy(ParkInfo.bwh, kdata, 4);

		jmbz = ChaZhaoBw(&ParkInfo);                //�ж��Ƿ�Ϊ����
		if (jmbz == FLAG_IN) {
			memset(ParkInfo.time_out, 0x00, sizeof (ParkInfo.time_out));
			//memcpy( ParkInfo.time_out ,ParkInfo.time_in,14);
					Get_DateTime(0, ParkInfo.time_out);
					PInfo_Calcfree(&ParkInfo);
			//CardInfo_Disp( &ParkInfo );
			//CardInfo_Disp( &ParkInfo );
					moveto(8, 1);
					putstr("[�Ƿ�����Ϊ�ӵ���]");
					moveto(10, 1);
					putstr("[��ȷ�ϼ�ȷ��]");
					moveto(12, 1);
					putstr("[��F2��ȡ��]");

					k = key(0);
					while (k == KEY_ENTER) {
						taodanPInfo_Save(&ParkInfo);
						ParkInfo.flag = FLAG_OUT;
						ErrorMsg("����ɹ�");
						BWState_Ref(ParkInfo.bwh, FLAG_FREE, ParkInfo.chepai);
						GPRS_netconnect();
						GPRS_TaoDanOutSendrcv(&ParkInfo);            //������

						return;
					}
				} else {
					ErrorMsg("�˲�λδͣ��");
					key(0);
				}
			//break;
		goto bbbb;
	}
}
int GPRS_TaoDanOutSendrcv(TYPE_PARKINFO *ParkInfo) {
	int cRet;
	Uchar8 sbuf[200];
	Uint16 r;
	Uchar8 rt;

	Uchar8 tdata[40];

	unsigned short rlen;

	Uchar8 kdata[40];
	memset(sbuf, 0x00, 200);

	cominit(B38400, 0x03, UART_ON);
	while (1) {
		cls();
		sbuf[0] = '1';
		memcpy(&(sbuf[1]), ParkInfo->chepai, 9);
		memcpy(&(sbuf[10]), ParkInfo->bwh, 4);
		memcpy(&(sbuf[14]), ParkInfo->time_out, 14);

		memcpy(&(sbuf[28]), AdminId, 3);
		memcpy(&(sbuf[31]), AdminPassId, 6);
		//memcpy( &(sbuf[45]), ParkInfo->flowNO ,6);
		memset(kdata, 0x00, sizeof (kdata));
		sprintf(kdata, "%06d", ParkInfo->flowNO);

		//sprintf( tmpdata, "%d", ParkInfo->flowNO );
		memcpy(&(sbuf[37]), kdata, 6);
		memcpy(&(sbuf[43]), posiddata, 32);
		memcpy(&(sbuf[75]), "2", 1);
		memcpy(&(sbuf[76]), "1", 1);
		memcpy(&(sbuf[77]), ParkInfo->charge_due, 5);
		putstr("���ڷ�������...\n");
		cRet = WNetTxd(sbuf, 87);
		if (cRet == 0) {
			memset(tdata, 0x00, sizeof (tdata));
			rt = WNetRxd(tdata, &rlen, 2000);

			if (rt == 0) {
				memcpy(tdata, &(tdata[0]), 1);
				if (tdata[0] == '1') {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "1", 1);            //����ʧ��
					libset(r, BCZTW);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("���ͳɹ�\n");
					WNetIPClose("1", 1000);
					//WNetClose(1000);
					putstr("�����������\n");
					key(0);
					return 1;
				} else {
					libopen(DBFNO_PARK);
					r = ParkInfo->r;
					memset(kdata, 0x00, sizeof(kdata));
					memcpy(kdata, "2", 1);            //����ʧ��
					libset(r, BCZTW);//���ű�־  0˵������ʧ��
					libwrite(kdata);
					putstr("����ʧ��\n");
					WNetIPClose("1", 1000);
					//WNetClose(1000);
					putstr("�����������\n");
					key(0);
					return 1;
				}
			} else {
				libopen(DBFNO_PARK);
				r = ParkInfo->r;
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, "2", 1);            //����ʧ��
				libset(r, BCZTW);//���ű�־  0˵������ʧ��
				libwrite(kdata);
				putstr("����ʧ��\n");
				WNetIPClose("1", 1000);
				//WNetClose(1000);
				putstr("�����������\n");
				key(0);
				return 1;
			}
		} else {
			libopen(DBFNO_PARK);
			r = ParkInfo->r;
			memset(kdata, 0x00, sizeof(kdata));
			memcpy(kdata, "2", 1);            //����ʧ��
			libset(r, BCZTW);//���ű�־  0˵������ʧ��
			libwrite(kdata);
			putstr("����ʧ��\n");
			WNetIPClose("1", 1000);
			//WNetClose(1000);
			putstr("�����������\n");
			key(0);
			return 1;
		}
	}
}

// ���ݲ�λ�Ž��в�ѯ
Uchar8 ChaZhaoBw(TYPE_PARKINFO *ParkInfo) {
	//Uchar8 rt;
	Uchar8 kdata[50];
	Sint32 last, r;									//	���ݿ��п���Ϊ�գ���ʱlast����Ϊ����

	/*	���жϽ���ʱ��
	 ���ж��뿪ʱ���Ƿ�Ϊ��
	 ���жϿ���/����
	 */
	libopen(DBFNO_PARK);
	last = libsumr() - 1;

	for (r = last; r >= 0; r--) {
		memset(kdata, 0x00, sizeof (kdata));
		libset(r, BWH);
		libread(kdata);
		//putstr(kdata);
				if (memcmp(ParkInfo->bwh, kdata, strlen(ParkInfo->bwh)) == 0)//	���ݿ��ȡ��������Ŀո������ȡkdata���ȱ�����length
				{
					memset(kdata, 0x00, sizeof(kdata));
					libset(r, LKSJ);
					libread(kdata);
					if ((kdata[0] < 0x30) | (kdata[0] > 0x39))									//	δ����
					{
						{
							ParkInfo->r = r;			//	break�󵽴�˴������ż�¼����
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, LSH);
							libread(kdata);
							ParkInfo->flowNO = atoi(kdata);
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, JRSJ);
							libread(kdata);
							Change_DateTime_Style(0, kdata);
							memcpy(ParkInfo->time_in, kdata, 14);
							memset(kdata, 0x00, sizeof(kdata));
							libset(r, CHEPAI);
							libread(kdata);
							memcpy(ParkInfo->chepai, kdata, 9);

							break;

						}
					}
				}
			}
	if (BWPD(ParkInfo->bwh) == 0)
		return FLAG_FOE;							//	�Ƿ���λ��

	if (r < 0)
		return FLAG_OUT;							//	����δ����
	else
		return FLAG_IN;
}

//	��ڣ�Լ���ķ�����ָ�����ݸ�ʽ
void BoWei_Save(Uchar8 *bdata) {
	Uchar8 kdata[2000];
	Uint16 i, r, sum, boffset;
	Uint16 sumf;	//	������

	libopen(DBFNO_BOWEI);
	boffset = 0;								//	bdataƫ��
	sum = 0;									//	��
	sumf = libsumf();							//	������

	while ((sum < sumf) & (bdata[boffset] != 0x00))		//	С��sumf����δ����������
	{
		memset(kdata, 0x00, sizeof (kdata));
		memcpy(kdata, &(bdata[boffset]), 3);
		libset(0, sum);
		libwrite(kdata);				//	�û���
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, &(bdata[boffset + 3]), 6);
				libset(1, sum);
				libwrite(kdata);//	�û�����
				memset(kdata, 0x00, sizeof(kdata));
				memcpy(kdata, &(bdata[boffset + 9]), 4);
				i = stoi(4, kdata);
				while (libsumr() < (i + 3)) {
					libapp();
				}

				libset(2, sum);
				libwrite(kdata);				//	��λ����

				memset(kdata, 0x00, sizeof(kdata));
				for (r = 0; r < (libsumr() - 3); r++) {
					if (r < i) {
						memcpy(kdata, &(bdata[boffset + 13 + r * 4]), 4);
						libset(3 + r, sum);
						libwrite(kdata);			//	��λ��
					} else {
						memset(kdata, 0x00, sizeof(kdata));
						libset(3 + r, sum);
						libwrite(kdata);			//	��λ�ſռ����
					}
				}
				boffset += (13 + i * 4);
				sum++;
			}
			//libclose( DBFNO_BOWEI );
		}

//	��ڣ���λ��
//	���ڣ�0�Ƿ���λ�� 1�Ϸ���λ��
Uchar8 BWPD(Uchar8 *bdata) {
	Uchar8 kdata[12];
	Uint16 i, r;

	libopen(DBFNO_BOWEI);
	memset(kdata, 0x00, sizeof (kdata));
	libset(2, Index_Id);        // Index_Id������ͨ�������û�����������
	libread(kdata);				//	��λ����
	i = stoi(4, kdata);

	memset(kdata, 0x00, sizeof (kdata));
	for (r = 0; r < i; r++) {
		libset(3 + r, Index_Id);
		libread(kdata);			//	��λ��
		if (memcmp(kdata, bdata, 4) == 0)
			break;
	}

	if (r < i)
		return 1;					//	�Ϸ���λ��
	else
		return 0;					//	�Ƿ���λ��
}
//����ʱ��������������ϴη���ʧ�ܵ�����
int ReSend(void) {
	cls();
	//Uchar8 cb_data[20];
	//Sint32 l;
	Uchar8 cccbbb[40];
	Uchar8 kdata[40], sdata[40]; //��ˮ��
	Uchar8 liushuidata[40]; //��ˮ��
	//Uchar8 ldata[40];//�뿪ʱ��
	//Uchar8 jdata[40];//����ʱ��
	Uchar8 cdata[40];    //���ƺ�
	int cRet;
	Uchar8 tdata[40];
	Uchar8 rt;
	unsigned short rlen;
	Uchar8 sbuf[200];
	//Uchar8 sccgbuf[10];
	Sint32 last, r;
	int nub = 0, nub1 = 0; //num ���ͳɹ�����
	Uint16 i, k;
	TYPE_PARKINFO ParkInfo;
	libopen(DBFNO_PARK);
	last = libsumr() - 1;

	//Uchar8 cbdata[40];
	putstr("�����ϴ������Ժ�...");
	for (r = last; r >= 0; r--) {
		if (nub1 >= 15 || libmitnub == 3) {
			return 1;
		}
		memset(sbuf, 0x00, sizeof (sbuf)); //��λ��
		memset(kdata, 0x00, sizeof (kdata));
		memset(sdata, 0x00, sizeof (sdata));
		libset(r, SCCG);
		libread(kdata); //��ȡ���ű�־λ
		i = stoi(1, kdata);

		libset(r, BCZTW);
		libread(sdata); //��ȡ���ű�־λ
		k = stoi(1, sdata);
		if (i == 2 && k == 0) {
			GPRS_netconnect();

			cominit(B38400, 0x03, UART_ON); //��ˮ��
			libopen(DBFNO_PARK);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LSH);
			libread(kdata);
			ParkInfo.flowNO = atoi(kdata);

			sprintf(liushuidata, "%06d", ParkInfo.flowNO);
			memset(kdata, 0x00, sizeof (kdata)); //��λ��
			libset(r, BWH);
			libread(kdata);
			memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
			memcpy(ParkInfo.bwh, kdata, 4);

			memset(kdata, 0x00, sizeof (kdata));
			libset(r, JRSJ);
			libread(kdata);
			Change_DateTime_Style(0, kdata);
			memcpy(ParkInfo.time_in, kdata, 14);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CHEPAI);
			libread(cdata);
			memcpy(ParkInfo.chepai, cdata, 9);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CLX);
			libread(cdata);
			memcpy(ParkInfo.clx, cdata, 6);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, PCH);
			libread(cdata);
			memcpy(ParkInfo.pch, cdata, 1);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CZY);
			libread(cdata);
			memcpy(ParkInfo.czy, cdata, 3);
			//Jump_cb(ParkInfo.czy);

			sbuf[0] = '0';
			memcpy(&(sbuf[1]), ParkInfo.chepai, 9);
			memcpy(&(sbuf[10]), ParkInfo.bwh, 4);
			memcpy(&(sbuf[14]), ParkInfo.time_in, 14);
			memcpy(&(sbuf[28]), ParkInfo.czy, 3);
			memcpy(&(sbuf[31]), ParkInfo.clx, 6);
			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%06d", ParkInfo.flowNO);
			memcpy(&(sbuf[37]), kdata, 6);
			memcpy(&(sbuf[43]), posiddata, 32);
			memcpy(&(sbuf[75]), ParkInfo.pch, 1);
			cRet = WNetTxd(sbuf, 76);
			if (cRet == 0) {

				memset(tdata, 0x00, sizeof (tdata));
				rt = WNetRxd(tdata, &rlen, 2000);
				if (rt == 0) {
					memcpy(tdata, &(tdata[0]), 1);
					if (tdata[0] == '1') {
						nub++;
						libopen(DBFNO_PARK);

						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "1", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					} else {
						libopen(DBFNO_PARK);
						nub1++;
						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "2", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG);//���ű�־  0˵������ʧ��
						libwrite(kdata);

					}
				}
			}
			WNetIPClose("1", 4000);
		}
		if (i == 2 && k == 1) {

			GPRS_netconnect();

			cominit(B38400, 0x03, UART_ON); //��ˮ��
			libopen(DBFNO_PARK);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LSH);
			libread(kdata);
			ParkInfo.flowNO = atoi(kdata);

			sprintf(liushuidata, "%06d", ParkInfo.flowNO);
			memset(kdata, 0x00, sizeof (kdata)); //��λ��
			libset(r, BWH);
			libread(kdata);
			memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
			memcpy(ParkInfo.bwh, kdata, 4);

			memset(kdata, 0x00, sizeof (kdata));
			libset(r, JRSJ);
			libread(kdata);
			Change_DateTime_Style(0, kdata);
			memcpy(ParkInfo.time_in, kdata, 14);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CHEPAI);
			libread(cdata);
			memcpy(ParkInfo.chepai, cdata, 9);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CLX);
			libread(cdata);
			memcpy(ParkInfo.clx, cdata, 6);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, PCH);
			libread(cdata);
			memcpy(ParkInfo.pch, cdata, 1);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CZY);
			libread(cdata);
			memcpy(ParkInfo.czy, cdata, 3);
			//Jump_cb(ParkInfo.czy);

			sbuf[0] = '0';
			memcpy(&(sbuf[1]), ParkInfo.chepai, 9);
			memcpy(&(sbuf[10]), ParkInfo.bwh, 4);
			memcpy(&(sbuf[14]), ParkInfo.time_in, 14);
			memcpy(&(sbuf[28]), ParkInfo.czy, 3);
			memcpy(&(sbuf[31]), ParkInfo.clx, 6);
			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%06d", ParkInfo.flowNO);
			memcpy(&(sbuf[37]), kdata, 6);
			memcpy(&(sbuf[43]), posiddata, 32);
			memcpy(&(sbuf[75]), ParkInfo.pch, 1);
			cRet = WNetTxd(sbuf, 76);
			if (cRet == 0) {
				memset(tdata, 0x00, sizeof (tdata));
				rt = WNetRxd(tdata, &rlen, 2000);
				if (rt == 0) {
					memcpy(tdata, &(tdata[0]), 1);
					if (tdata[0] == '1') {
						nub++;
						libopen(DBFNO_PARK);

						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "1", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					} else {
						libopen(DBFNO_PARK);
						nub1++;
						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "2", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					}
				}
			}

			WNetIPClose("1", 4000);
		}

		if (i == 1 && k == 2) {
			nub1++;
			GPRS_netconnect();

			cominit(B38400, 0x03, UART_ON); //��ˮ��
			libopen(DBFNO_PARK);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LKSJ);
			libread(kdata);
			Change_DateTime_Style(0, kdata);
			memcpy(ParkInfo.time_out, kdata, 14);

			memset(cccbbb, 0x00, sizeof (cccbbb)); //��Ǯ
			libset(r, YSJE);
			libread(cccbbb);
			memcpy(ParkInfo.charge_due, cccbbb, 10);

			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LSH);
			libread(kdata);
			ParkInfo.flowNO = atoi(kdata);

			sprintf(liushuidata, "%06d", ParkInfo.flowNO);

			memset(kdata, 0x00, sizeof (kdata)); //��λ��
			libset(r, BWH);
			libread(kdata);
			memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
			memcpy(ParkInfo.bwh, kdata, 4);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CHEPAI);
			libread(cdata);
			memcpy(ParkInfo.chepai, cdata, 9);

			memset(cdata, 0x00, sizeof (cdata)); //��Ǯ
			libset(r, YSJE);
			libread(cdata);
			memcpy(ParkInfo.charge_due, cdata, 10);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, TCD);
			libread(cdata);
			memcpy(ParkInfo.tcd, cdata, 1);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, BCCZYMM);
			libread(cdata);
			memcpy(ParkInfo.outczymm, cdata, 6);
			memset(cdata, 0x00, sizeof (cdata));
			libset(r, BCCZY);
			libread(cdata);
			memcpy(ParkInfo.outczy, cdata, 3);

			sbuf[0] = '1';
			memcpy(&(sbuf[1]), ParkInfo.chepai, 9);
			memcpy(&(sbuf[10]), ParkInfo.bwh, 4);
			memcpy(&(sbuf[14]), ParkInfo.time_out, 14);

			memcpy(&(sbuf[28]), ParkInfo.outczy, 3);
			memcpy(&(sbuf[31]), ParkInfo.outczymm, 6);

			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%06d", ParkInfo.flowNO);
			memcpy(&(sbuf[37]), kdata, 6);
			memcpy(&(sbuf[43]), posiddata, 32);
			memcpy(&(sbuf[75]), ParkInfo.tcd, 1);
			memcpy(&(sbuf[76]), "1", 1);
			memcpy(&(sbuf[77]), ParkInfo.charge_due, 5);

			moveto(1, 1);
			cRet = WNetTxd(sbuf, 87);
			if (cRet == 0) {
				memset(tdata, 0x00, sizeof (tdata));
				rt = WNetRxd(tdata, &rlen, 2000);
				if (rt == 0) {
					memcpy(tdata, &(tdata[0]), 1);
					if (tdata[0] == '1') {
						nub++;
						libopen(DBFNO_PARK);

						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "1", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, BCZTW);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					} else {
						libopen(DBFNO_PARK);
						nub1++;
						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "2", 1); //����ʧ��
						libset(r, BCZTW);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					}
				}
			}
			WNetIPClose("1", 4000);
		}

		//case 3:	ShouFei_ChaXun();	break;
		if (i == 2 && k == 2) {
			GPRS_netconnect();
			libopen(DBFNO_PARK);
			cominit(B38400, 0x03, UART_ON);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LKSJ);
			libread(kdata);
			Change_DateTime_Style(0, kdata);
			memcpy(ParkInfo.time_out, kdata, 14);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, JRSJ);
			libread(kdata);
			Change_DateTime_Style(0, kdata);
			memcpy(ParkInfo.time_in, kdata, 14);

			memset(cccbbb, 0x00, sizeof (cccbbb)); //��Ǯ
			libset(r, YSJE);
			libread(cccbbb);
			memcpy(ParkInfo.charge_due, cccbbb, 10);
			memset(kdata, 0x00, sizeof (kdata));
			libset(r, LSH);
			libread(kdata);
			ParkInfo.flowNO = atoi(kdata);
			sprintf(liushuidata, "%06d", ParkInfo.flowNO);
			memset(kdata, 0x00, sizeof (kdata)); //��λ��
			libset(r, BWH);
			libread(kdata);
			memset(ParkInfo.bwh, 0x00, sizeof (ParkInfo.bwh));
			memcpy(ParkInfo.bwh, kdata, 4);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CHEPAI);
			libread(cdata);
			memcpy(ParkInfo.chepai, cdata, 9);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, PCH);
			libread(cdata);
			memcpy(ParkInfo.pch, cdata, 1);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, TCD);
			libread(cdata);
			memcpy(ParkInfo.tcd, cdata, 1);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CZY);
			libread(cdata);
			memcpy(ParkInfo.czy, cdata, 3);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, CLX);
			libread(cdata);
			memcpy(ParkInfo.clx, cdata, 6);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, BCCZY);
			libread(cdata);
			memcpy(ParkInfo.outczy, cdata, 3);

			memset(cdata, 0x00, sizeof (cdata));
			libset(r, BCCZYMM);
			libread(cdata);
			memcpy(ParkInfo.outczymm, cdata, 6);
			cominit(B38400, 0x03, UART_ON); //��ˮ��
			sbuf[0] = '1';
			memcpy(&(sbuf[1]), ParkInfo.chepai, 9);
			memcpy(&(sbuf[10]), ParkInfo.bwh, 4);
			memcpy(&(sbuf[14]), ParkInfo.time_out, 14);

			memcpy(&(sbuf[28]), ParkInfo.outczy, 3);
			memcpy(&(sbuf[31]), ParkInfo.outczymm, 6);
			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%06d", ParkInfo.flowNO);

			memcpy(&(sbuf[37]), kdata, 6);
			memcpy(&(sbuf[43]), posiddata, 32);
			memcpy(&(sbuf[75]), ParkInfo.tcd, 1);
			memcpy(&(sbuf[76]), "1", 1);
			memcpy(&(sbuf[77]), ParkInfo.charge_due, 5);
			moveto(1, 1);

			cRet = WNetTxd(sbuf, 87);
			if (cRet == 0) {
				memset(tdata, 0x00, sizeof (tdata));
				rt = WNetRxd(tdata, &rlen, 2000);
				if (rt == 0) {
					memcpy(tdata, &(tdata[0]), 1);
					if (tdata[0] == '1') {
						nub++;
						libopen(DBFNO_PARK);

						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "1", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, BCZTW);//���ű�־  0˵������ʧ��
						libwrite(kdata);

					} else {
						libopen(DBFNO_PARK);
						nub1++;
						memset(kdata, 0x00, sizeof(kdata));
						memcpy(kdata, "2", 1); //����ʧ��
						libset(r, BCZTW);//���ű�־  0˵������ʧ��
						libwrite(kdata);
					}

				}
			}
			WNetIPClose("1", 4000);
			GPRS_netconnect();

			memset(sbuf, 0x00, sizeof (sbuf));
			//�޸Ĳ���
			cominit(B38400, 0x03, UART_ON);
			sbuf[0] = '0';
			memcpy(&(sbuf[1]), ParkInfo.chepai, 9);
			memcpy(&(sbuf[10]), ParkInfo.bwh, 4);
			memcpy(&(sbuf[14]), ParkInfo.time_in, 14);
			memcpy(&(sbuf[28]), ParkInfo.czy, 3);
			memcpy(&(sbuf[31]), ParkInfo.clx, 6);

			memset(kdata, 0x00, sizeof (kdata));
			sprintf(kdata, "%06d", ParkInfo.flowNO);

			memcpy(&(sbuf[37]), kdata, 6);

			memcpy(&(sbuf[43]), posiddata, 32);
			memcpy(&(sbuf[75]), ParkInfo.pch, 1);

			cRet = WNetTxd(sbuf, 76);
			if (cRet == 0) {
				moveto(1, 1);
				memset(tdata, 0x00, sizeof (tdata));
				rt = WNetRxd(tdata, &rlen, 2000);
				if (rt == 0) {
					memcpy(tdata, &(tdata[0]), 1);
					if (tdata[0] == '1') {
						nub++;
						libopen(DBFNO_PARK);

						memset(kdata, 0x00, sizeof (kdata));
						memcpy(kdata, "1", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG); //���ű�־  0˵������ʧ��
						libwrite(kdata);

					} else {
						libopen(DBFNO_PARK);
						nub1++;
						memset(kdata, 0x00, sizeof (kdata));
						memcpy(kdata, "2", 1); //����ʧ�� 1���ųɹ�    3�ɹ�
						libset(r, SCCG); //���ű�־  0˵������ʧ��
						libwrite(kdata);

					}
				}

			}
			WNetIPClose("1", 4000);
		}
	}
	return 1;
}

