2016.09.05 M.SUDO

１．キャリブレーション取得機能を追加
　CalibrationControllerクラスに実装しました。
  
　キャリブレーションの値は次の構造体となります。　
  typedef struct{		// 補正値構造体
	int8_t	White;	// 輝度　白
	int8_t	Black;	// 輝度　黒
	int8_t	Half;	// 輝度　中間値
	float	TailAngleStandUp;	// 直立時尻尾角度
  } CALIBRAT ;

　キャリブレーション時に次のキーを押下で輝度を取得します。
　　w : 白
　　b : 黒
　　h : 中間値

２．ブルーツース系機能を追加
　UIGetクラスに実装しました。
　ログ出力はRunningController::RunningExecute()を参考にして下さい。

３．その他
　・次のクラスの使用をやめました。（ソースコードは残ってます）
　　ColorGet
　　PostureAdjustment
　　StartInstructionGet
　　理由：センサー情報やボタンやキーボード取得を同じループ内の
　　　　　色々な場所で行うと干渉し値を取得できなくなるため。
　　　　
　・各クラスのコンストラクター引数を変更したものがあります。
　　大きく見直そうかとも思ったのですが、時間がないので少しだけに留めました。

