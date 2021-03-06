//ルックアップゲート攻略
#include "ExtraStageLookUp.h"

// コンストラクタ
ExtraStageLookUp::ExtraStageLookUp(
		DeviceInterface* deviceinterface,
		UIGet* guiget,
		CalibrationController*	gCalibrationController
		)
{
	m_pDeviceInterface	= deviceinterface;
	m_pUIGet			= guiget;
	m_pCalibrationController	= gCalibrationController;

	m_pRunningCalculation = new RunningCalculation();

	m_pDeviceValueGet	= new	DeviceValueGet(deviceinterface);
	m_pMotorDrive = new MotorDrive(deviceinterface);

	m_uStartTime	= 0;	// 開始時間
	m_uNowTime		= 0;	// 現在時間
	m_uElapsedTime	= 0; 	// 経過時間

	m_fTailAngleStand = 84;	// しっぽ立ち上がり
	m_fTailAngleStand2 = 80;	// しっぽ立ち上がり
	m_fTailAngleStandLow = 74;	// しっぽ立ち上がり低め
	m_fTailAngleStandFine = 87;	// しっぽ立ち上がり最終値（ガレージ）

	m_fTailAngleSlant = 60;	// しっぽリンボー

	m_nDistanceMin 	= 5;	// ソナーセンサー距離cm

	//■■■■■■■■■■■■■■■■■■■■■　＜最終調整が必要＞　■■■
	m_nFinalRunDist	= 400;	// ガレージまでの最終走行距離
	float	fTailCal	= -2;	// しっぽ初期調整

	//場合によっては、SectionDecisionData::referData() の値も変更する　「最終コーナー長さ」
	//■■■■■■■■■■■■■■■■■■■■■

	// しっぽ角度キャリブレーション
	CALIBRAT calib	= m_pCalibrationController->GetValue();
	float	fTailSabun	= calib.TailAngleStandUp - 93.0;
	fTailSabun	+= fTailCal;
	m_fTailAngleStand		+= fTailSabun;	// しっぽ立ち上がり
	m_fTailAngleStandLow	+= fTailSabun;	// しっぽ立ち上がり低め
	m_fTailAngleStandFine	+= fTailSabun;	// しっぽ立ち上がり最終値（ガレージ）
	m_fTailAngleSlant		+= fTailSabun;	// しっぽリンボー

}


//メソッド：void 競技走行する（）
void ExtraStageLookUp::ExtraRun()
{

	/*　停止部分 */
	int stopTime = m_pDeviceInterface->m_pCClock->now();
	DV dv_now;
	while(1){
		dv_now = m_pDeviceValueGet->DeviceValueGetter();
		if(m_pDeviceInterface->m_pCClock->now() - stopTime  < 1500){
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now, 0);
			m_pMotorDrive->TailMotorDrive(3);
			ev3_lcd_draw_string("EXrun section0start", 0, 70);
		}
		else if(m_pDeviceInterface->m_pCClock->now() - stopTime  < 2000){
			dv_now.GYRO_OFFSET = -10;
			dv_now = m_pRunningCalculation->RunningCalculate(dv_now, 0);
			m_pMotorDrive->TailMotorDrive(80);
			ev3_lcd_draw_string("EXrun section0 < 3500", 0, 80);
		}
		else{
			break;
		}

		m_pMotorDrive->LRMotorDrive(dv_now.Lmotor_pwm, dv_now.Rmotor_pwm);
		m_pDeviceInterface->m_pCClock->sleep(3); /* 4msec周期起動 */
	}

	ev3_lcd_draw_string("EXrun fin", 0, 90);



	//
	float	fTailAngle = m_fTailAngleStand;	// しっぽ立ち上がり

	int		nLmotor = 20;
	int		nRmotor = 20;
//	int16_t	nDistance = 9999;

	m_uStartTime	= m_pDeviceInterface->m_pCClock->now();	// 開始時間

	//ログ出力
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	sprintf(cLogBuff,"ExtraStageLookUp::ExtraRun go 1: %lu,%d,%d,sizeof(int)=%d\n", GetElapsedTime(),
			nLmotor,
			nRmotor,
			sizeof(int)
			);
	m_pUIGet->WriteLog(cLogBuff);


//BBBBBBBBBBB
// テストデータ取得
//	Spin( 'N', 3600, fTailAngle );
//
//	PauseEt( 3000, fTailAngle);	// ポーズ
//
//	// 5000mm 進む
//	MoveDist( 'N', 5000, fTailAngle, nLmotor, nRmotor );
//	PauseEt(3000, fTailAngle);	// ポーズ
//BBBBBBBBBBB

//	PauseEt(500, fTailAngle);	// ポーズ

//	// ０　しっぽを出しながら止まる
//	MoveDist( 'N', 100, fTailAngle, 5 );

	// ①　→

	//ゲートまで近づく
//	GoGate('R', fTailAngle);
	GoGate('N', fTailAngle);
	PauseEt(500, fTailAngle);	// ポーズ

	// ②　→

	//走行体をリンボー
	fTailAngle	= Limbo( 'N', fTailAngle);
	PauseEt(500, fTailAngle);	// ポーズ

	// ゲートを潜る為、230mm 進む
	MoveDist( 'N', 230, fTailAngle, 10 );
	PauseEt(500, fTailAngle);	// ポーズ

	// ③ Ｕ
	// Ｕターン　180度回転
	Spin(185, fTailAngle);
	PauseEt(500, fTailAngle);	// ポーズ

	// 戻り
	// ③　←
	// ゲートを潜る、330mm 戻る
	MoveDist( 'N', 330, fTailAngle, 10 );
	PauseEt(500, fTailAngle);	// ポーズ

	// ④　Ｕ
	// 再度Ｕターン　-180度回転
	Spin(-185, fTailAngle);
	PauseEt(500, fTailAngle);	// ポーズ

	// ④　→
	// ゲートを潜る、360mm 進む
	MoveDist( 'N', 360, fTailAngle, 20 );


	// ⑤　→
	// トレースを可能とする為に上体を起こす
	fTailAngle = StandUpTail(fTailAngle);	// しっぽを立てる

	PauseEt(2222, fTailAngle);	// ポーズ

	PauseEt(2222, fTailAngle);	// ポーズ

//
//	// トレースを確実に行う為に故意に右側にはみ出す
//	Spin(-10, fTailAngle);		// -10度回転
//	PauseEt(500, fTailAngle);	// ポーズ
//	MoveDist( 'N', 40, fTailAngle, 10 );	// 3cm進む
//	PauseEt(500, fTailAngle);	// ポーズ

	// ⑥　→
	// ガレージまで走る！！
	// 距離　m_nFinalRunDist	// ■■＜最終調整が必要＞

	// トレース走行
//	MoveDist( 'R', m_nFinalRunDist, fTailAngle, 10 );
	MoveDist( 'N', m_nFinalRunDist, fTailAngle, 10 );

	MoveDist( 'N', 50, fTailAngle,  5 );	// 急停止すると倒れる場合があるので減速走行

	// ゲートイン
	fTailAngle = StandUpTailFine(fTailAngle);	// しっぽを思い切り立てる
	PauseEt(4000, fTailAngle);	// ポーズ

	// ゲートに届かなかった場合を考慮して、微速前進とポーズを繰り返す
	// ※ゲートイン判定が出た後は、ゲートにぶつかってもお構いなしなはず
	for( int i=0 ; i< 5 ; i++ ){
		MoveDist( 'N', 30, fTailAngle,  5 );	// ゲートまで再度トライ
		PauseEt(4000, fTailAngle);	// ポーズ
	}
	MoveDist( 'N', 30, fTailAngle,  5 );	// ゲートまで再度トライ

//	Ending();

	PauseEt(5000, fTailAngle);	// ポーズ

}

// ゲートに行く
void ExtraStageLookUp::GoGate(
			char	cLRsw,			// ライントレース位置 'L':左、'R':右、'N':トレースなし
			float	fTailAngle
		)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	//------------------
	DV	dv;
	int		nForward	= 10;	// 走行速度

//	int16_t	nDistanceMin = 5;	// ソナーセンサー距離cm
	int16_t	nDistanceMin = 7;	// ソナーセンサー距離cm

	int16_t nDistance	= m_pDeviceInterface->m_pCSonarSensor->getDistance();

	for(int i=0 ; ; i++ ){
		if( i % 10 == 9 ){
			// 40ミリ秒毎にソナー検出
			nDistance	=  m_pDeviceInterface->m_pCSonarSensor->getDistance();
		}

		if( nDistance <= nDistanceMin ){
			// ゲート前に到着
			//ログ出力
			sprintf(cLogBuff,"ExtraRun GoGate %lu, nDistance=%d\n", GetElapsedTime(), nDistance);
			m_pUIGet->WriteLog(cLogBuff);
			break;
		}

		// ライントレース制御
		dv	= CalcuTraceMoterPower( cLRsw, nForward );

		// モータードライブ
		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive(dv.Lmotor_pwm, dv.Rmotor_pwm);

		//ログ出力
		sprintf(cLogBuff,"ExtraRun GoGate %lu, cLRsw=[%c], nDistance=%d,  fTailAngle=%f, nForward=%d, color=%d, Lmotor_pwm=%d, Rmotor_pwm=%d\n",
				GetElapsedTime(),
				cLRsw,
				nDistance,
				fTailAngle,
				nForward,
				dv.color,
				dv.Lmotor_pwm, dv.Rmotor_pwm
		);
		m_pUIGet->WriteLog(cLogBuff);

		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動
		if( IsKeyBreak(fTailAngle) )	break;

	}

}

//走行体をリンボー
float ExtraStageLookUp::Limbo(
		char	cLRsw,
		float	fTailAngleI
		)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	//------------------

	float	fTailAngleO	= fTailAngleI;

	// 上体を倒す。しっぽを上げる
	while(1){
		if( fTailAngleO > m_fTailAngleSlant ){
			// しっぽを徐々に上げる（一気にやると倒れてしまう）
			m_pMotorDrive->TailMotorDrive(fTailAngleO);
			m_pMotorDrive->LRMotorDrive( 0, 0 );
			fTailAngleO	-= ( 0.02 );
			//m_pDeviceInterface->m_pCClock->sleep(10); // 4msec周期起動
			m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

			if( IsKeyBreak(fTailAngleO) ){
				break;		// キーボード入力による強制ブレイク
			}
		}else{
			// 上体倒し終了
			m_pMotorDrive->TailMotorDrive(fTailAngleO);
			break;
		}
	}

	//ログ出力
	sprintf(cLogBuff,"ExtraRun Limbo %lu, fTailAngle=%f\n", GetElapsedTime(), fTailAngleO );
	m_pUIGet->WriteLog(cLogBuff);

	return	fTailAngleO;
}

// しっぽを立てる
float	ExtraStageLookUp::StandUpTail(
		float	fTailAngle
		)
{
	float	fTailAngleO	= fTailAngle;

	// 上体を起こす。しっぽを下げる
	// ※上体が倒れたままだと、
	//   ・カラーセンサーが傾きライントレースができない
	//   ・重心がしっぽに掛かり、タイヤ荷重が少なくスリップしてしまう。
	//   ・しっぽ接地抵抗が大きく走行に支障が出る可能性が高い。


	// 上体を中間まで起こす
	// いっきに起こすと前に倒れることがある
	while(1){
		if( fTailAngleO >= m_fTailAngleStandLow )	break;

		fTailAngleO	+= ( 0.4 );
		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive( 60, 60 );
//		m_pMotorDrive->LRMotorDrive( 80, 80 );

//		m_pMotorDrive->LRMotorDrive( -20, -20 );	// しっぽモーターだけではパワー不足なので、タイヤで補助
//		m_pMotorDrive->LRMotorDrive( -10, -10 );
//		m_pMotorDrive->LRMotorDrive( -7, -7 );

		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngleO) ){
			//fTailAngle	= fTailAngleS;
			break;		// キーボード入力による強制ブレイク
		}
	}

//	PauseEt(5000, fTailAngleO);	// ポーズ

	// 上体をさらに起こす
	while(1){
//		if( fTailAngleO >= m_fTailAngleStand )	break;
		if( fTailAngleO >= m_fTailAngleStand2 )	break;

//		fTailAngleO	+= ( 0.1 );
		fTailAngleO	+= ( 0.2 );
		m_pMotorDrive->TailMotorDrive(fTailAngle);
//		m_pMotorDrive->LRMotorDrive( -1, -1 );
//		m_pMotorDrive->LRMotorDrive( -3, -3 );

		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngleO) ){
			//fTailAngle	= fTailAngleS;
			break;		// キーボード入力による強制ブレイク
		}
	}

	return	fTailAngleO;

}

// しっぽを最終状態に立てる
float	ExtraStageLookUp::StandUpTailFine(
		float	fTailAngle
		)
{
	float	fTailAngleO	= fTailAngle;


	while(1){
		if( fTailAngleO >= m_fTailAngleStandFine )	break;

		fTailAngleO	+= ( 0.1 );
		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive( 0, 0 );

		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngleO) ){
			break;		// キーボード入力による強制ブレイク
		}
	}

	return	fTailAngleO;

}

// 指定距離移動
void ExtraStageLookUp::MoveDist(
		char	cLRsw,			// ライントレース位置 'L':左、'R':右、'N':トレースなし
		int		nDist,			// 移動距離　mm単位
		float	fTailAngle,
		int		nForward
		)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	//------------------

	DV	dv;

	int32_t		nLmotorCountS = m_pDeviceInterface->m_pCLeftMotor->getCount();
	int32_t		nRmotorCountS = m_pDeviceInterface->m_pCRightMotor->getCount();
	int32_t		nMotorCountS  = ( nLmotorCountS + nRmotorCountS ) / 2;
	while(1){
		int32_t		nLmotorCountN = m_pDeviceInterface->m_pCLeftMotor->getCount();
		int32_t		nRmotorCountN = m_pDeviceInterface->m_pCRightMotor->getCount();
		int32_t		nMotorCountN  = ( nLmotorCountN + nRmotorCountN ) / 2;

		int32_t		nRunCount	= nMotorCountN - nMotorCountS;
		double		dRunDist	= GetRunDistance(nRunCount);	//オフセット付き角位置から距離mmに変換

		if( dRunDist >= (double)nDist ){
			//-----ログ出力-----
			sprintf(cLogBuff,"MoveDist  %lu, nDist=%d, nRunCount=%ld, dRunDist=%f\n", GetElapsedTime(),
					nDist, nRunCount, dRunDist);
			m_pUIGet->WriteLog(cLogBuff);
			//------------------
			break;
		}

		// ライントレース制御
		dv	= CalcuTraceMoterPower( cLRsw, nForward );

		// モータードライブ
		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive( dv.Lmotor_pwm, dv.Rmotor_pwm );

		//ログ出力
		sprintf(cLogBuff,"ExtraRun MoveDist %lu, cLRsw=[%c], nDist=%d,  fTailAngle=%f, nForward=%d, color=%d, Lmotor_pwm=%d, Rmotor_pwm=%d\n",
				GetElapsedTime(),
				cLRsw,
				nDist,
				fTailAngle,
				nForward,
				dv.color,
				dv.Lmotor_pwm, dv.Rmotor_pwm
		);

		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngle) )	break;
	}
}

// スピン
void ExtraStageLookUp::Spin(
		int nAng,				// スピン角度(deg)　180,360等 　＋時計周り
		float	fTailAngle		// しっぽ角度
	)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	//------------------

	int		nLmotor =  10;
	int		nRmotor = -10;

	if(nAng < 0){
		// マイナス値
		nLmotor = -10;
		nRmotor =  10;
	}

	double	dCount360	= 740.0;	// 360度スピン時のモーターカウント 実測値
	double	dCount	= dCount360 / ( 360.0 / (double)nAng );
	int32_t nCount	= dCount;

	int32_t		nLmotorCountS = m_pDeviceInterface->m_pCLeftMotor->getCount();
//	int32_t		nRmotorCountS = m_pDeviceInterface->m_pCRightMotor->getCount();
	while(1){
		int32_t		nLmotorCountN = m_pDeviceInterface->m_pCLeftMotor->getCount();
//		int32_t		nRmotorCountN = m_pDeviceInterface->m_pCRightMotor->getCount();

		int32_t		nRunCount	= nLmotorCountN - nLmotorCountS;

		//-----ログ出力-----
		sprintf(cLogBuff,"Spin  %lu, nAng=%d, nCount=%ld, nRunCount=%ld, dCount360=%f\n", GetElapsedTime(),
				nAng, nCount, nRunCount, dCount360);
		m_pUIGet->WriteLog(cLogBuff);
		//------------------

		if(nCount >= 0){	// プラス
			if(nRunCount >= nCount )	break;
		}else{				// マイナス
			if(nRunCount <= nCount )	break;
		}

		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive( nLmotor, nRmotor );
		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngle) )	break;
	}
}

// 一時停止
void ExtraStageLookUp::PauseEt(
		int		nTime,		// 停止時間　ミリ秒
		float	fTailAngle	// しっぽ角度
		)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	sprintf(cLogBuff,"\n PauseEt  nTime=%d, fTailAngle=%f\n", nTime, fTailAngle );
	m_pUIGet->WriteLog(cLogBuff);
	//------------------

	uint32_t	uTimeStr	= m_pDeviceInterface->m_pCClock->now();
	while(1){
		m_pMotorDrive->TailMotorDrive(fTailAngle);
		m_pMotorDrive->LRMotorDrive(0,0);
		m_pDeviceInterface->m_pCClock->sleep(4); // 4msec周期起動

		if( IsKeyBreak(fTailAngle) )	break;

		if( m_pDeviceInterface->m_pCClock->now() - uTimeStr > (uint32_t)nTime )	break;
	}

}

// 経過時間取得
// m_uNowTime と m_uElapsedTimeを設定
uint32_t	ExtraStageLookUp::GetElapsedTime()
{
	m_uNowTime	= m_pDeviceInterface->m_pCClock->now();
	m_uElapsedTime	= m_uNowTime - m_uStartTime;
	return	m_uElapsedTime;
}


// オフセット付き角位置から距離(mm)に変換
double	ExtraStageLookUp::GetRunDistance(
		double	dMotorCount
		)
{
//	double	dPai		= 3.141592654;			// 円周率
//	double	dTireDia	= 80.0;					// タイヤ直径　80mm
//	double	dCircumference	= dTireDia * dPai;	// タイヤ円周
//	double	dDistance	= dMotorCount / 360.0 * dCircumference;	// 走行距離
//	return	dDistance;

	double	dMm1Dec	= 1.4263;	// 1mmあたりの角度   実走行値から算出
	double	dDistance	= dMotorCount / dMm1Dec;
	return	dDistance;

}

// キーボード入力によるブレイク指示
// 必ず　clock->sleep()の直後に呼ぶこと
bool	ExtraStageLookUp::IsKeyBreak(
		float	fTailAngle
		)
{
	//-----ログ出力-----
	char*	cLogBuff	= m_pUIGet->GetBlueT()->pcLogBuff;
	//------------------

	bool	bPause	= false;

	while(1){
		UI ui	= m_pUIGet->UIGetter();
		if( ui.btcKey == 'b' || ui.btcKey == 'B' ){
			// ブレイク

			//-----ログ出力-----
			sprintf(cLogBuff,"\n IsKeyBreak  true\n");
			m_pUIGet->WriteLog(cLogBuff);
			//------------------
			return	true;
		}
		else if(ui.btcKey == 'p' || ui.btcKey == 'P'){
			// ポーズ
			if( bPause )	return	false;

			bPause	= true;

			//-----ログ出力-----
			sprintf(cLogBuff,"\n IsKeyBreak  Pause now! please push 'p' key : fTailAngle=%f\n", fTailAngle);
			m_pUIGet->WriteLog(cLogBuff);
			//------------------

		}

		if(bPause){
			// ポーズ時
			m_pMotorDrive->TailMotorDrive(fTailAngle);
			m_pMotorDrive->LRMotorDrive(0,0);
			m_pDeviceInterface->m_pCClock->sleep(10); // 10msec周期停止
			continue;
		}

		return	false;
	}

	return	false;
}

// トレース計算する
DV	ExtraStageLookUp::CalcuTraceMoterPower(
		char	cLRsw,			// ライントレース位置 'L':左、'R':右、'N':トレースなし
		int		nForward
		)
{
	//現在のデバイス値を持ってくる
	DV	dv = m_pDeviceValueGet->DeviceValueGetter();

	if(cLRsw == 'n' || cLRsw == 'N'){
		dv.Lmotor_pwm	= nForward;
		dv.Rmotor_pwm	= nForward;
		return	dv;
	}

	//区間走行データ
	RD	rd;
	rd.KP	= 0.2;
	rd.KI	= 0.0;
	rd.KD	= 0.0;
	rd.forward	= 10;


	dv.color = dv.color * 2 - 4;	// しっぽを出した状態の輝度 BBBBBBBBBBB
	if( dv.color < 1 )	dv.color	= 1;



	//PID計算する
	double	dTurn = mPIDCalculation.PIDCalculate(rd,dv.color);

	if( cLRsw == 'l' || cLRsw == 'L'){
		// ライン左をトレース
		dTurn	=	-dTurn;
	}

	//// バランス制御値を持ってくる
	////すべての値を渡し、モータ出力値をポインタで格納してもらう
	//balance_control((float)rd.forward, (float)turn, (float)dv.gyro,(float)dv.GYRO_OFFSET, (float)dv.Lmotor_angle,
	//	(float)dv.Rmotor_angle, (float)dv.volt, (int8_t *)&dv.Lmotor_pwm, (int8_t *)&dv.Rmotor_pwm);

	double	dLpwm	= (double)nForward + (dTurn / 2.0);
	double	dRpwm	= (double)nForward - (dTurn / 2.0);

	dv.Lmotor_pwm	= (int8_t)dLpwm;
	dv.Rmotor_pwm	= (int8_t)dRpwm;

	return	dv;
}

// エンディング
void	ExtraStageLookUp::Ending()
{
	m_pDeviceInterface->m_pCSpeaker->SetVolume(50);

	for(int i=0; i<2 ; i++){
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_G6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_F6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_D6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_G6,200);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_F6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_D6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_B6,100);
	}

	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_D6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_CS6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_C6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_B6,100);
	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_G5,200);

	m_pDeviceInterface->m_pCSpeaker->PlayTone(NOTE_G6,100);

	m_pDeviceInterface->m_pCSpeaker->Stop();

}
