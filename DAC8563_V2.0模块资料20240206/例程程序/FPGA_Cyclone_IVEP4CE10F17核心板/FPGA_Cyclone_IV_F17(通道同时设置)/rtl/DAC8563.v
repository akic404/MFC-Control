module DAC8563(
    input   wire                SYS_CLK ,
    input   wire                RST_N ,
    input   wire                DATA_SEL ,      // 0 -> 直流 ， 1 -> 交流
    input   wire [15:0]         DATA ,          // 数据输入
    output  wire                SYNC ,
    output  wire                SCLK ,
    output  wire                MOSI
);

localparam  delay_500ms         = (50_000_000 / 2) - 1;

localparam  FRE_SYS_CLK         = 50_000_000 ;

localparam  delay_80ns          = (FRE_SYS_CLK / 12_500_000)  - 1; //延时80ns
localparam  sclk_cnt            = ((FRE_SYS_CLK / FRE_SYS_CLK) * 24) - 1;

//寄存器配置参考数据手册第37页
localparam  C2_C1_C0_0          = 3'b000;       // 写入寄存器
localparam  C2_C1_C0_1          = 3'b001;       // 软件LDAC更新寄存器
localparam  C2_C1_C0_2          = 3'b010;       // 写入寄存器，并更新所有DAC寄存器
localparam  C2_C1_C0_3          = 3'b011;       // 写入寄存器n，并更新寄存器n
localparam  C2_C1_C0_4          = 3'b100;       // 设置DAC通电或断电模式
localparam  C2_C1_C0_5          = 3'b101;       // 软件复位
localparam  C2_C1_C0_6          = 3'b110;       // 设置LDAC寄存器
localparam  C2_C1_C0_7          = 3'b111;       // 使用或禁用內部引用

localparam  A2_A1_A0_0          = 3'b000;       // DAC A寄存器
localparam  A2_A1_A0_1          = 3'b001;       // DAC B寄存器
localparam  A2_A1_A0_2          = 3'b010;       // 增益设置
localparam  A2_A1_A0_3          = 3'b011;       // 保持
localparam  A2_A1_A0_4          = 3'b100;       // 保持
localparam  A2_A1_A0_5          = 3'b101;       // 保持
localparam  A2_A1_A0_6          = 3'b110;       // 保持
localparam  A2_A1_A0_7          = 3'b111;       // DAC A 和 DAC B

reg     [7 :0]                  ROM_ADDR  ;

reg     [4 :0]                  cycle_cnt ;     // sclk周期计数器
reg     [3 :0]                  delay_cnt ;     // 延时计数器

reg     [3 :0]                  STATE     ;     // 状态计数器
 
reg     [23:0]                  DAC_DATA  ;     // 需要发送的数据
reg     [23:0]                  SEND_DATA ;     // 数据发送缓冲级

wire                            spi_sclk  ;

wire    [15:0]                  DC_DATA   ;
wire    [15:0]                  SIN_DATA  ;


reg     [0 :0]                  spi_mosi  ;
reg     [0 :0]                  spi_sync  ;

reg                             update    ;     // 数据更新标志位
reg                             delay_per ;

reg     [25:0]                  DELAY_CNT ; 

rom_sin u_rom_sin(
    .address                    ( ROM_ADDR                  ),
    .clock                      ( SYS_CLK                   ),
    .q                          ( SIN_DATA                  )
);

assign DC_DATA  = DATA;

always@(posedge SYS_CLK or negedge RST_N) begin
    if(!RST_N) begin
        cycle_cnt   <= 5'd0 ;
        delay_cnt   <= 4'd0 ;
        spi_sync    <= 1'b1 ;
        DAC_DATA    <= 24'd0;
				DELAY_CNT   <= 26'd0;
        ROM_ADDR    <= 8'd0 ;
        delay_per   <= 1'b0 ;
        update      <= 1'b0 ;
        STATE       <= 4'd0 ;
    end 
		else begin
        case(STATE)
            4'd0: begin //复位状态
                cycle_cnt   <= 5'd0 ;
                delay_cnt   <= 4'd0 ;
                spi_sync    <= 1'b1 ;
                DAC_DATA    <= 24'd0;
                ROM_ADDR    <= 8'd0 ;
                delay_per   <= 1'b0 ;
                update      <= 1'b0 ;
								if(DELAY_CNT >= delay_500ms)begin
								  DELAY_CNT <= 26'd0;
								  STATE     <= 4'd1 ;
								end
						    else begin
								  DELAY_CNT <= DELAY_CNT + 1'b1;
						      STATE     <= 4'd0 ;
				        end		
            end
            4'd1: begin //DAC_A 和 DAC_B 上电
                DAC_DATA    <= 24'h200003 ;
                STATE       <= 4'd2 ;
            end
            4'd2: begin
                delay_per   <= 1'b0 ;
                spi_sync    <= 1'b0 ;
                update      <= 1'b1 ;
                STATE       <= 4'd3 ;
            end
            4'd3: begin
                update      <= 1'b0 ;
                delay_per   <= 1'b1 ;
                if(cycle_cnt >= sclk_cnt)begin
                    cycle_cnt   <= 5'd0 ;
                    STATE       <= 4'd4 ;
                end else begin
                    cycle_cnt   <= cycle_cnt + 1'b1 ;
                    STATE       <= 4'd3 ;
                end
            end
            4'd4: begin
                spi_sync    <= 1'b1 ;
                delay_per   <= 1'b0 ;
                DAC_DATA    <= 24'h300003;  //LDAC引脚不使用
                if(delay_cnt >= delay_80ns)begin
                    delay_cnt   <= 4'd0 ;
                    update      <= 1'b1 ;
                    STATE       <= 4'd5 ;
                end else begin
                    delay_cnt   <= delay_cnt + 1'b1 ;
                    update      <= 1'b0 ;
                    STATE       <= 4'd4 ;
                end
            end
            4'd5: begin
                spi_sync    <= 1'b0 ;
                delay_per   <= 1'b0 ;
                update      <= 1'b0 ;
                STATE       <= 4'd6 ;
            end
            4'd6: begin
                delay_per   <= 1'b1 ;
                if(cycle_cnt >= sclk_cnt)begin
                    cycle_cnt   <= 5'd0 ;
                    STATE       <= 4'd7 ;
                end else begin
                    cycle_cnt   <= cycle_cnt + 1'b1 ;
                    STATE       <= 4'd6 ;
                end
            end
            4'd7: begin
                delay_per   <= 1'b0 ;
                spi_sync    <= 1'b1 ;
                DAC_DATA    <= 24'h380001 ;     //LDAC通道增益设置为2
                if(delay_cnt >= delay_80ns)begin
                    delay_cnt   <= 4'd0 ;
                    update      <= 1'b1 ;
                    STATE       <= 4'd8 ;
                end else begin
                    delay_cnt   <= delay_cnt + 1'b1 ;
                    update      <= 1'b0 ;
                    STATE       <= 4'd7 ;
                end
            end
            4'd8: begin
                delay_per   <= 1'b0 ;
                spi_sync    <= 1'b0 ;
                update      <= 1'b0 ;
                STATE       <= 4'd9 ;
            end
            4'd9: begin
                delay_per   <= 1'b1 ;
                if(cycle_cnt >= sclk_cnt)begin
                    cycle_cnt   <= 5'd0 ;
                    STATE       <= 4'd10 ;
                end else begin
                    cycle_cnt   <= cycle_cnt + 1'b1 ;
                    STATE       <= 4'd9 ;
                end
            end
            4'd10:begin
                spi_sync        <= 1'b1 ;
                delay_per       <= 1'b0 ;
                if(DATA_SEL) begin
                    DAC_DATA    <= {2'b00,C2_C1_C0_3,A2_A1_A0_7,SIN_DATA} ;     //发送数据
                end
                else begin
                    DAC_DATA    <= {2'b00,C2_C1_C0_3,A2_A1_A0_7,DC_DATA} ;      //发送数据
                end
                if(delay_cnt >= delay_80ns) begin
                    delay_cnt   <= 4'd0 ;
                    update      <= 1'b1 ;
                    STATE       <= 4'd11 ;
                end else begin
                    delay_cnt   <= delay_cnt + 1'b1 ;
                    update      <= 1'b0 ;
                    STATE       <= 4'd10 ;
                end
            end
            4'd11:begin
                spi_sync    <= 1'b0 ;
                delay_per   <= 1'b0 ;
                update      <= 1'b0 ;
                STATE       <= 4'd12 ;
            end
            4'd12: begin
                delay_per   <= 1'b1;
                if(cycle_cnt >= sclk_cnt)begin
                    cycle_cnt   <= 5'd0 ;
                    ROM_ADDR    <= ROM_ADDR + 1'b1 ;
                    STATE       <= 4'd10 ;
                end
                else begin
                    cycle_cnt   <= cycle_cnt + 1'b1 ;
                    STATE       <= 4'd12 ;
                end
            end
            default: STATE <= 4'd0 ;
        endcase
    end
end



//SCLK上升沿发送数据
always@(posedge SCLK or negedge RST_N or posedge update)
begin
    if(!RST_N)begin
        spi_mosi     <= 1'b0 ;
        SEND_DATA    <= 24'd0 ;
    end else if(update)begin
        SEND_DATA    <= DAC_DATA ;
    end else begin
        spi_mosi     <= SEND_DATA[23] ;
        SEND_DATA    <= SEND_DATA << 1 ;
    end
end

assign  spi_sclk    = SYS_CLK & (~SYNC) & delay_per;
assign  SCLK        = spi_sclk;
assign  MOSI        = spi_mosi;
assign  SYNC        = spi_sync;


endmodule

