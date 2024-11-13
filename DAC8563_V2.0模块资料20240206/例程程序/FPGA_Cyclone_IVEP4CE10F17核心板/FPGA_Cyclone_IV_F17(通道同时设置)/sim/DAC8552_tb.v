`timescale 1 ps/ 1 ps
module DAC8563_tb();

reg [15:0] DATA;
reg DATA_SEL;
reg RST_N;
reg SYS_CLK;
                                       
wire MOSI;
wire SCLK;
wire SYNC;

                        
DAC8563 DAC8563( 
	.DATA(DATA),
	.DATA_SEL(DATA_SEL),
	.MOSI(MOSI),
	.RST_N(RST_N),
	.SCLK(SCLK),
	.SYNC(SYNC),
	.SYS_CLK(SYS_CLK)
	
);
initial begin                                                  
	RST_N = 0;
 	SYS_CLK = 1;
	DATA = 16'd0;
	#100;
	RST_N = 1;
end   
                                                 
always #1 SYS_CLK = ~SYS_CLK;    

                                                
endmodule

