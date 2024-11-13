create_clock -name CLK_50Mhz -period 20.000 [get_ports {SYS_CLK}]
create_clock -name SCLK -period 20.000 [get_ports {SCLK}]
create_clock -name MOSI -period 20.000 [get_ports {MOSI}]
create_clock -name SYNC -period 20.000 [get_ports {SYNC}]

set_clock_uncertainty -setup -rise_from altera_reserved_tck -rise_to altera_reserved_tck 0.150
set_clock_uncertainty -hold -rise_from altera_reserved_tck -rise_to altera_reserved_tck 0.150
set_clock_uncertainty -setup -rise_from altera_reserved_tck -fall_to altera_reserved_tck 0.150
set_clock_uncertainty -hold -rise_from altera_reserved_tck -fall_to altera_reserved_tck 0.150
set_clock_uncertainty -setup -fall_from altera_reserved_tck -fall_to altera_reserved_tck 0.150
set_clock_uncertainty -hold -fall_from altera_reserved_tck -fall_to altera_reserved_tck 0.150
set_clock_uncertainty -hold -rise_from SYS_CLK -rise_to SYS_CLK 0.150
set_clock_uncertainty -setup -rise_from SYS_CLK -rise_to SYS_CLK 0.150


derive_pll_clocks
derive_clock_uncertainty

