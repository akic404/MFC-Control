module DAC8563_TOP(
	input		wire	SYS_CLK	,
	input		wire	RST_N		,
	output	wire	SYNC		,
	output	wire	SCLK		,
	output	wire	MOSI	  
);


/* 				模块使用说明 		*/
/* 模块的最大输出电压为±10V，如果输出达不到±10V，则需要去查看升压和降压模块的输出电压是否达到了，原理图上标注的电压 			 
	 如若供电电压达到了原理图所标注的电压输出电压任然达不到±10V的话，建议是检查一下程序使用Signal_Tap 查看波形是否输出正常 */
/* 如果程序烧入进去出现无现象的情况请重新拔插 SYNC SCLK MOSI 三根线，后续就可以正常工作了，烧入程序也不会出问题				 */
/* 模块SCLK达到50Mhz，建议使用的时候去画一个简单的转接板使用，杜邦线还是不那么靠谱 */

wire					DATA_SEL;
wire	[15:0]	DATA;
wire					CLK_100M;

assign DATA_SEL = 1'b0;
assign DATA     = 16'd65535;

pll_clk pll_clk(
	.areset (~RST_N		),
	.inclk0 (SYS_CLK	),
	.c0			(CLK_100M	)
);

DAC8563 u_DAC8563(
	.SYS_CLK	(SYS_CLK	),
	.RST_N		(RST_N		),
	.DATA_SEL	(DATA_SEL	),	// 0 -> 直流 ， 1 -> 交流
	.DATA			(DATA			), // 数据输入
	.SYNC			(SYNC			),
	.SCLK			(SCLK			),
	.MOSI	  	(MOSI			)
);

endmodule

