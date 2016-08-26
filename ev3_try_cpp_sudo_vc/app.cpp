/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用C++サンプルプログラム
 **
 ** 注記 : sample_cpp (ライントレース/尻尾モータ/超音波センサ/リモートスタート)
 ******************************************************************************
 **/

#include "ev3api.h"
#include "app.h"
//#include "balancer.h"
//#include "TouchSensor.h"
//#include "SonarSensor.h"
//#include "ColorSensor.h"
//#include "GyroSensor.h"
//#include "Motor.h"
//#include "Clock.h"

#include	"unit/DeviceInterface.h"
#include	"unit/WrBalancer.h"

using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif


/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          40  /* 白色の光センサ値 */
#define LIGHT_BLACK           0  /* 黒色の光センサ値 */
#define SONAR_ALERT_DISTANCE 30  /* 超音波センサによる障害物検知距離[cm] */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define P_GAIN             2.5F  /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60  /* 完全停止用モータ制御PWM絶対最大値 */
//#define DEVICE_NAME     "ET0"  /* Bluetooth名 hrp2/target/ev3.h BLUETOOTH_LOCAL_NAMEで設定 */
//#define PASS_KEY        "1234" /* パスキー    hrp2/target/ev3.h BLUETOOTH_PIN_CODEで設定 */
#define CMD_START         '1'    /* リモートスタートコマンド */

static double tail_angle_stand_up = 93 ;/* 完全停止時の角度[度] (2016/06/24_変更)*/

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* 関数プロトタイプ宣言 */
static int32_t sonar_alert(void);
static void tail_control(int32_t angle);

//BBBBBBBBBBBBBBBBBBBBBBBB
///* オブジェクトへのポインタ定義 */
//TouchSensor*    touchSensor;
//SonarSensor*    sonarSensor;
//ColorSensor*    colorSensor;
//GyroSensor*     gyroSensor;
//Motor*          leftMotor;
//Motor*          rightMotor;
//Motor*          tailMotor;
//Clock*          clock;


//グローバル変数
static unsigned char	g_cBt_cmd = ' ';     // Bluetoothコマンド リモートスタート 文字
static int				g_nBt_cmd = 0;     	// Bluetoothコマンド  リモートスタート 数値
static FILE				*g_pBt = NULL;      // Bluetoothファイルハンドル
static unsigned char	g_cCourse = 'b';	// コース　b:左、m:右


CDeviceInterface*	g_pDeviceInterface;	// デバイスインターフィス
CWrBalancer*		g_pWrBalancer;		// バランスコントロール


int		g_nAvrBright		= 0;	// 平均値　輝度
float	g_fAvrMotorAngL		= 0;	// 平均値　モーター角　Ｌ
float	g_fAvrMotorAngR		= 0; 	// 平均値　モーター角　Ｒ
float	g_fAvrGyroAngler	= 0;	// 平均値　ジャイロ オフセット角速度
float	g_fAvrVolt			= 0;	// 平均値　電圧

uint8_t		g_unBright;
uint8_t		g_unBrightWht	= 0;	// 白　キャリブレーション
uint8_t		g_unBrightBlk	= 0;	// 黒　キャリブレーション
uint8_t		g_unBrightKyk	= 0;	// 境界　キャリブレーション
uint8_t		g_unBrightGry	= 0;	// 灰　キャリブレーション
uint8_t		g_unBrightGrn	= 0;	// 緑　キャリブレーション


char	g_cBuff[128];

/* メインタスク */
void main_task(intptr_t unused)
{
    int8_t nForward	= 0;	/* 前後進命令 */
    int8_t nForwardMX	= 0;	/* 前後進命令 */
    int8_t nTurn	= 0;	/* 旋回命令 */
    int8_t nPwmL	= 0;	/* 左右モータPWM出力 */
	int8_t nPwmR	= 0;	/* 左右モータPWM出力 */

//   /* 各オブジェクトを生成・初期化する */
//    touchSensor = new TouchSensor(PORT_1);
//    sonarSensor = new SonarSensor(PORT_2);
//    colorSensor = new ColorSensor(PORT_3);
//    gyroSensor  = new GyroSensor(PORT_4);
//    leftMotor   = new Motor(PORT_C);
//    rightMotor  = new Motor(PORT_B);
//    tailMotor   = new Motor(PORT_A);
//    clock       = new Clock();
	g_pDeviceInterface	= new	CDeviceInterface();	// デバイスインターフィス
	g_pWrBalancer		= new	CWrBalancer();		// バランスコントロール

    /* LCD画面表示 */
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
    ev3_lcd_draw_string("EV3way-ET sample_cpp", 0, CALIB_FONT_HEIGHT*1);

//    /* 尻尾モーターのリセット */
//    tailMotor->reset();
	g_pDeviceInterface->m_pCTailMotor->reset();
    
    /* Open Bluetooth file */
    g_pBt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(g_pBt != NULL);

    /* Bluetooth通信タスクの起動 */
    act_tsk(BT_TASK);
//    act_tsk(LOG_TASK);

    ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */

	fputs( "\n\n\n Start TAIKI\n", g_pBt ); // エコーバック
	fputs( "キー入力\n", g_pBt );

	sprintf(g_cBuff,"b:コース左,m:コース右=%c\n", g_cCourse );
	fputs( g_cBuff, g_pBt );

	sprintf(g_cBuff,"a:白　キャリブレーション=%d\n", g_unBrightWht );
	fputs( g_cBuff, g_pBt );
	sprintf(g_cBuff,"s:黒　キャリブレーション=%d\n", g_unBrightBlk );
	fputs( g_cBuff, g_pBt );
	sprintf(g_cBuff,"d:境界キャリブレーション=%d\n", g_unBrightKyk );
	fputs( g_cBuff, g_pBt );
	sprintf(g_cBuff,"f:灰　キャリブレーション=%d\n", g_unBrightGry );
	fputs( g_cBuff, g_pBt );
	sprintf(g_cBuff,"g:緑　キャリブレーション=%d\n", g_unBrightGrn );
	fputs( g_cBuff, g_pBt );

	fputs( "1-9,0:RUN\n", g_pBt );

//	int nGYRO_OFFSET	= GYRO_OFFSET;
//	float	rGYRO_OFFSET	= GYRO_OFFSET;

    /* スタート待機 */
	bool	bBreak	= false;
    while(1)
    {
        tail_control(tail_angle_stand_up); /* 完全停止用角度に制御 */

		// 尻尾角度調整
    	if (ev3_button_is_pressed(UP_BUTTON))/* 尻尾の角度調整 */
    	{
    		tail_angle_stand_up = tail_angle_stand_up + 0.1;
    	}

    	if (ev3_button_is_pressed(DOWN_BUTTON))/* 尻尾の角度調整 */
    	{
    		tail_angle_stand_up = tail_angle_stand_up - 0.1;
    	}

		switch( g_cBt_cmd ){
			// キー入力により、キャリブレーションとスタートを切り替える
			case	'1':
			case	'2':
			case	'3':
			case	'4':
			case	'5':
			case	'6':
			case	'7':
			case	'8':
			case	'9':
			case	'0':
				// 数値キーの場合は、スタート
				bBreak	= true;
				break;

			case	'b':
			case	'm':
				g_cCourse = g_cBt_cmd;	// コース　b:左、m:右
				sprintf(g_cBuff,"b:コース左,m:コース右 =%c\n", g_cCourse );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			case	'a':
				// 白キャリブレーション
				g_unBrightWht	= GetBalanceAvr(4);	// 輝度平均値を取得
				sprintf(g_cBuff,"a:白　キャリブレーション=%d\n", g_unBrightWht );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			case	's':
				// 黒キャリブレーション
				g_unBrightBlk	= GetBalanceAvr(4);	// 輝度平均値を取得
				sprintf(g_cBuff,"s:黒　キャリブレーション=%d\n", g_unBrightBlk );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			case	'd':
				// ライン境界キャリブレーション
				g_unBrightKyk	= GetBalanceAvr(4);	// 輝度平均値を取得
				sprintf(g_cBuff,"d:境界キャリブレーション=%d\n", g_unBrightKyk );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			case	'f':
				// 灰色キャリブレーション
				g_unBrightGry	= GetBalanceAvr(4);	// 輝度平均値を取得
				sprintf(g_cBuff,"f:灰　キャリブレーション=%d\n", g_unBrightGry );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			case	'g':
				// 緑キャリブレーション
				g_unBrightGrn	= GetBalanceAvr(4);	// 輝度平均値を取得
				sprintf(g_cBuff,"g:緑　キャリブレーション=%d\n", g_unBrightGrn );
				fputs( g_cBuff, g_pBt ); // エコーバック
				g_cBt_cmd	= 0;
				break;

			default:
				break;
		}

		if( bBreak )	break;

        g_pDeviceInterface->m_pCClock->sleep(10);
    }

	g_pDeviceInterface->m_pCClock->reset();	// 開始時間を現在のシステムクロックでリセットする
	sprintf(g_cBuff,"Start,%u, %u,%u,%u,%u,%u\n",
				g_pDeviceInterface->m_pCClock->now(),
				(unsigned int)g_unBrightWht,(unsigned int)g_unBrightBlk,(unsigned int)g_unBrightKyk,
				(unsigned int)g_unBrightGry,(unsigned int)g_unBrightGrn);
	fputs( g_cBuff, g_pBt ); // エコーバック

    /* 走行モーターエンコーダーリセット */
    g_pDeviceInterface->m_pCLeftMotor->reset();
    g_pDeviceInterface->m_pCRightMotor->reset();
    
    g_pDeviceInterface->m_pCGyroSensor->reset();	// ジャイロセンサーリセット
    g_pWrBalancer->Init();							// 倒立振子API初期化

    g_pDeviceInterface->m_pCLEDLight->SetColor(LED_GREEN); // スタート通知

	GetBalanceAvr(500);	// センサー平均値を取得（100ミリ秒間）
	float	rGYRO_OFFSET	= g_fAvrGyroAngler;	// ジャイロセンサー角位置

	tail_control(TAIL_ANGLE_DRIVE); /* バランス走行用角度に制御 */

    /**
    * Main loop for the self-balance control algorithm
    a*/
	//act_tsk(LOG_TASK);
	
	nForward	= g_nBt_cmd * 10;	// 前進値
	if( nForward > 90 ) nForward	= 90;	// 90以上は難しい
	nForwardMX	= nForward;

    while(1)
    {
		g_unBright	= GetBalanceAvr(4);	// 輝度平均値を取得（4ミリ秒間）　

		if( g_unBright == 0 ){
			// 輝度が0の場合転倒したと見なし、停止する
			 nForward	= 10;
		     g_pDeviceInterface->m_pCLeftMotor->setPWM(0);
        	 g_pDeviceInterface->m_pCRightMotor->setPWM(0);
			 break;
		}
    	
        if (ev3_button_is_pressed(BACK_BUTTON)) break;	// ev3のバックボタンが押された。　走行中止

 //       tail_control(TAIL_ANGLE_DRIVE); /* バランス走行用角度に制御 */

        if (sonar_alert() == 1){ /* 障害物検知 */
            nForward = nTurn = 0; /* 障害物を検知したら停止 */
        }
        else
        {
        	
 //           forward = 30; /* 前進命令 */
 //           g_unBright  = colorSensor->getBrightness();
 //           if (g_unBright >= (LIGHT_WHITE + LIGHT_BLACK)/2)
 //           {
 //               turn =  20; /* 左旋回命令 */
 //           }
 //           else
 //           {
 //               turn = -20; /* 右旋回命令 */
 //           }
 //       	
 
			nTurn = 0;
        }

        /* 倒立振子制御API に渡すパラメータを取得する */
//        g_motor_ang_l = leftMotor->getCount();
//        g_motor_ang_r = rightMotor->getCount();
//        g_gyro = gyroSensor->getAnglerVelocity();
//        g_volt = ev3_battery_voltage_mV();

		//======



//		nGYRO_OFFSET	= forward * 6;

//		if( nForward <= 0 ){
//			rGYRO_OFFSET	= GYRO_OFFSET;
//		}else{
//			rGYRO_OFFSET	= 8.5;
//		}

		//======

		// 倒立振子制御APIの呼び出し
		g_pWrBalancer->BalanceControl(	// バランサーコントロール
            (float)nForward,
            (float)nTurn,
            g_fAvrGyroAngler,
            rGYRO_OFFSET,
            g_fAvrMotorAngL,
            g_fAvrMotorAngR,
            g_fAvrVolt
		);

		nPwmL	= g_pWrBalancer->GetPwmL();	// モータPWM値取得　Ｌ
		nPwmR	= g_pWrBalancer->GetPwmR();	// モータPWM値取得　Ｒ

        g_pDeviceInterface->m_pCLeftMotor->setPWM(nPwmL);	// モーター駆動 L
        g_pDeviceInterface->m_pCRightMotor->setPWM(nPwmR);	// モーター駆動 R


        // ログ
		sprintf(g_cBuff,"Main,%lu, %d,%d, %f,%f, %f,%f, %f, %d,%d\n",
				g_pDeviceInterface->m_pCClock->now(),
				nForward, nTurn,
				g_fAvrGyroAngler,rGYRO_OFFSET,
				g_fAvrMotorAngL,g_fAvrMotorAngR,
				g_fAvrVolt,
				nPwmL, nPwmR);
		fputs( g_cBuff, g_pBt ); // エコーバック

		//if( nForwardMX > 80 ){
		//	// 高速走行時
		//	if( nPwmL > nForward || nPwmR > nForward ){
		//		nForward--;	// スピード制御
		//	}else{
		//		if( nForward < nForwardMX )	nForward--;
		//	}
		//}

 //       clock->sleep(3); /* 4msec周期起動 */	←この処理はGetBalanceAvr()に組み込んだ
    }

	// 終了処理
    g_pDeviceInterface->m_pCLeftMotor->reset();
    g_pDeviceInterface->m_pCRightMotor->reset();

    ter_tsk(BT_TASK);
    fclose(g_pBt);

	delete	g_pDeviceInterface;	// デバイス解放
	delete	g_pWrBalancer;		// バランスコントロール解放

    ext_tsk();
}

//*****************************************************************************
// 関数名 : sonar_alert
// 引数 : 無し
// 返り値 : 1(障害物あり)/0(障害物無し)
// 概要 : 超音波センサによる障害物検知
//*****************************************************************************
static int32_t sonar_alert(void)
{
    static uint32_t counter = 0;
    static int32_t alert = 0;

    int32_t distance;

    if (++counter == 40/4) /* 約40msec周期毎に障害物検知  */
    {
        /*
         * 超音波センサによる距離測定周期は、超音波の減衰特性に依存します。
         * NXTの場合は、40msec周期程度が経験上の最短測定周期です。
         * EV3の場合は、要確認
         */
        distance = g_pDeviceInterface->m_pCSonarSensor->getDistance();
        if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
        {
            alert = 1; /* 障害物を検知 */
        }
        else
        {
            alert = 0; /* 障害物無し */
        }
        counter = 0;
    }

    return alert;
}

//*****************************************************************************
// 関数名 : tail_control
// 引数 : angle (モータ目標角度[度])
// 返り値 : 無し
// 概要 : 走行体完全停止用モータの角度制御
//*****************************************************************************
static void tail_control(int32_t angle)
{
    float pwm = (float)(angle - g_pDeviceInterface->m_pCTailMotor->getCount()) * P_GAIN; /* 比例制御 */
    /* PWM出力飽和処理 */
    if (pwm > PWM_ABS_MAX)
    {
        pwm = PWM_ABS_MAX;
    }
    else if (pwm < -PWM_ABS_MAX)
    {
        pwm = -PWM_ABS_MAX;
    }

    g_pDeviceInterface->m_pCTailMotor->setPWM(pwm);
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused)
{

    while(1)
    {
        uint8_t c = fgetc(g_pBt); /* 受信 */

		if( c > 0 ){
			g_cBt_cmd	= c;
			if( '0' <= c && c <= '9' ){
				// 0 ～ 9 が押されたらスタート
				g_nBt_cmd	= c - '0';
				break;
			}
		}

        fputc(c, g_pBt); /* エコーバック */
		fputc('\n', g_pBt); /* エコーバック */
    }
}


////////////////////////////////////////////////////////////////////
// バランサー用　センサー平均値を取得
//
// 戻り値： 平均値　輝度
//
// 次のグローバル変数に設定される
//int	g_nAvrBright	平均値　輝度
//float	g_fAvrMotor_ang_l	平均値　モーター角　Ｌ
//float	g_fAvrMotor_ang_r	平均値　モーター角　Ｒ
//float	g_fAvrVolt			平均値　電圧
//float	g_fAvrGyro			平均値　ジャイロ角
////////////////////////////////////////////////////////////////////
int GetBalanceAvr(	// バランサー用　センサー平均値を取得
	int nTime		// 採取時間 ミリ秒
	)
{
	uint32_t	unNow1 = g_pDeviceInterface->m_pCClock->now();		// 経過時間取得 開始時間からの経過時間を取得する
	uint32_t	unNow2;

	int nCnt = 0;

	float fBright		= 0.0;
	float fMotorAngL	= 0.0;
	float fMotorAngR	= 0.0;
	float fGyroAngler	= 0.0;
	float fVolt			= 0.0;

	float fBrightGo			= 0.0;
	float fMotorAngLGo	= 0.0;
	float fMotorAngRGo	= 0.0;
	float fGyroAnglerGo		= 0.0;
	float fVoltGo		= 0.0;

	while (1){
		// 倒立振子制御API に渡すパラメータを取得する
		fBright		 = (float)(g_pDeviceInterface->m_pCColorSensor->getBrightness());	// 輝度
		fMotorAngL = (float)(g_pDeviceInterface->m_pCLeftMotor->getCount());
		fMotorAngR = (float)(g_pDeviceInterface->m_pCRightMotor->getCount());
		fGyroAngler  = (float)(g_pDeviceInterface->m_pCGyroSensor->getAnglerVelocity());
		fVolt		 = (float)(g_pDeviceInterface->m_pCBattery->GetmV());

		// 合算
		fBrightGo += fBright;
		fMotorAngLGo += fMotorAngL;
		fMotorAngRGo += fMotorAngR;
		fGyroAnglerGo += fGyroAngler;
		fVoltGo += fVolt;

		nCnt++;

		unNow2 = g_pDeviceInterface->m_pCClock->now();		// 経過時間取得 開始時間からの経過時間を取得する
		if (unNow2 - unNow1 < (uint32_t)nTime)	continue;

		break;
	}

	// 平均値設定
	g_nAvrBright		= fBrightGo / nCnt;
	g_fAvrMotorAngL		= fMotorAngLGo  / nCnt;
	g_fAvrMotorAngR		= fMotorAngRGo  / nCnt;
    g_fAvrGyroAngler	= fGyroAnglerGo / nCnt;
	g_fAvrVolt			= fVoltGo  / nCnt;


//	sprintf(g_cBuff,"\n GetBrightnessAvr Avr ,%d,%d,%d,%d\n",
//				clock->now(),nBrAvr,nBrg,nCnt);
//	fputs( g_cBuff, g_pBt ); // エコーバック


	return	g_nAvrBright;
}
