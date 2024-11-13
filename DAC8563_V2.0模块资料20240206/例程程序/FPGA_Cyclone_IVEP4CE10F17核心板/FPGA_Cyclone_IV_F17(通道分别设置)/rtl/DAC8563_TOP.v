module DAC8563_TOP(
    input   wire    SYS_CLK ,
    input   wire    RST_N   ,
    output  wire    LDAC    ,
    output  wire    CLR     ,
    output  wire    SYNC    ,
    output  wire    SCLK    ,
    output  wire    MOSI 
);

/******************模块使用说明****************************************** /
 * 1、模块的最大输出电压为±10V，如果输出达不到±10V，则需要去查看升压和
 *    降压模块的输出电压是否达到了，原理图上标注的电压。
 * 2、如若供电电压达到了原理图所标注的电压输出电压任然达不到±10V的话，
 *    建议是检查一下程序使用Signal_Tap 查看波形是否输出正常。
 * 3、如果程序烧入进去出现无现象的情况请重新拔插 SYNC SCLK MOSI 三根线，
 *    后续就可以正常工作了，烧入程序也不会出问题。
 * 4、模块SCLK达到50Mhz，建议使用的时候去画一个简单的转接板使用，杜邦
 *    线还是不那么靠谱 
 ******************************************************************/

wire                DATA_SEL;
wire                CLK_100M;
wire    [15:0]      DATA_A  ;
wire    [15:0]      DATA_B  ;

assign  LDAC        = 1'b0 ;
assign  CLR         = 1'b1 ;

assign  DATA_SEL    = 1'b0 ;       // 0 -> 直流 ， 1 -> 交流

assign  DATA_A      = 16'd0 ;  // 直流输出计算公式: (DATA - 32768) * (20/65535)
assign  DATA_B      = 16'd65535 ;  // 直流输出计算公式: (DATA - 32768) * (20/65535)

pll_clk pll_clk(
    .areset              ( ~RST_N      ),
    .inclk0              ( SYS_CLK     ),
    .c0                  ( CLK_100M    )
);

DAC8563 u_DAC8563(
    .SYS_CLK             ( SYS_CLK     ),
    .RST_N               ( RST_N       ),
    .DATA_SEL            ( DATA_SEL    ),  // 0 -> 直流 ， 1 -> 交流
    .DATA_A              ( DATA_A      ),  // 通道A输出数据
		.DATA_B              ( DATA_B      ),  // 通道B输出数据
    .SYNC                ( SYNC        ),
    .SCLK                ( SCLK        ),
    .MOSI                ( MOSI        )
);

endmodule

