# ----------------------------------------------------------------------------------------------------
# --  Customer         : Enclustra GmbH
# --  Project          : Mars ZX3 Vivado Reference Design
# --  File description : Pin assignment constraints file for Mars Starter
# --  File name        : MarsZX3_Starter.xdc
# --  Authors          : Christoph Glattfelder
# ----------------------------------------------------------------------------------------------------
# --  Copyright (c) 2014 by Enclustra GmbH, Switzerland
# --  All rights reserved.
# ----------------------------------------------------------------------------------------------------

set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]

# ------------------------------------------------
# -- UART
# ------------------------------------------------

# Mars Starter specific
set_property PACKAGE_PIN H19 [get_ports UART0_TX]
set_property IOSTANDARD LVCMOS33 [get_ports UART0_TX]

set_property PACKAGE_PIN H20 [get_ports UART0_RX]
set_property IOSTANDARD LVCMOS33 [get_ports UART0_RX]

# ------------------------------------------------
# -- i2-port
# ------------------------------------------------
#set_property PACKAGE_PIN H15 [get_ports I2C0_SDA]
#set_property IOSTANDARD LVCMOS25 [get_ports I2C0_SDA]

#set_property PACKAGE_PIN R15 [get_ports I2C0_SCL]
#set_property IOSTANDARD LVCMOS25 [get_ports I2C0_SCL]

#set_property PACKAGE_PIN H17 [get_ports I2C0_INT_N]
#set_property IOSTANDARD LVCMOS25 [get_ports I2C0_INT_N]

# ------------------------------------------------
# -- led
# ------------------------------------------------
set_property PACKAGE_PIN H18 [get_ports {Led_N[0]}]
set_property IOSTANDARD LVCMOS25 [get_ports {Led_N[0]}]

set_property PACKAGE_PIN AA14 [get_ports {Led_N[1]}]
set_property IOSTANDARD LVCMOS25 [get_ports {Led_N[1]}]

set_property PACKAGE_PIN AA13 [get_ports {Led_N[2]}]
set_property IOSTANDARD LVCMOS25 [get_ports {Led_N[2]}]

set_property PACKAGE_PIN AB15 [get_ports {Led_N[3]}]
set_property IOSTANDARD LVCMOS25 [get_ports {Led_N[3]}]

## ------------------------------------------------
## -- MISC
## ------------------------------------------------

#set_property PACKAGE_PIN AB11 [get_ports Eth_Rst_N]
#set_property IOSTANDARD LVCMOS25 [get_ports Eth_Rst_N]

#set_property PACKAGE_PIN U14 [get_ports Usb_Rst_N]
#set_property IOSTANDARD LVCMOS25 [get_ports Usb_Rst_N]

## ----------------------------------------------------------------------------------
## -- system pins, set to high impedance if not used
## ----------------------------------------------------------------------------------

#set_property PACKAGE_PIN U9 [get_ports Vref0]
#set_property IOSTANDARD LVCMOS25 [get_ports Vref0]

#set_property PACKAGE_PIN T6 [get_ports Vref1]
#set_property IOSTANDARD LVCMOS25 [get_ports Vref1]

#set_property PACKAGE_PIN Y6 [get_ports CLK33]
#set_property IOSTANDARD LVCMOS25 [get_ports CLK33]

#set_property PACKAGE_PIN AA22 [get_ports DDR3_VSEL]
#set_property IOSTANDARD LVCMOS25 [get_ports DDR3_VSEL]

#set_property PACKAGE_PIN AB14 [get_ports PWR_GOOD_R]
#set_property IOSTANDARD LVCMOS25 [get_ports PWR_GOOD_R]

#set_property PACKAGE_PIN V13 [get_ports NAND_WP]
#set_property IOSTANDARD LVCMOS25 [get_ports NAND_WP]

## ----------------------------------------------------------------------------------
## -- IOs connected in parallel with MIO pins, set to high impedance if not used
## ----------------------------------------------------------------------------------

#set_property PACKAGE_PIN U12 [get_ports ETH_Link]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_Link]

#set_property PACKAGE_PIN AA12 [get_ports ETH_MDC]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_MDC]

#set_property PACKAGE_PIN AB12 [get_ports ETH_MDIO]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_MDIO]

#set_property PACKAGE_PIN Y9 [get_ports ETH_RX_CLK]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_RX_CLK]

#set_property PACKAGE_PIN Y8 [get_ports ETH_RX_CTL]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_RX_CTL]

#set_property PACKAGE_PIN U10 [get_ports {ETH_RXD[0]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_RXD[0]}]

#set_property PACKAGE_PIN Y11 [get_ports {ETH_RXD[1]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_RXD[1]}]

#set_property PACKAGE_PIN W11 [get_ports {ETH_RXD[2]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_RXD[2]}]

#set_property PACKAGE_PIN U11 [get_ports {ETH_RXD[3]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_RXD[3]}]

#set_property PACKAGE_PIN W10 [get_ports ETH_TX_CLK]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_TX_CLK]

#set_property PACKAGE_PIN V10 [get_ports ETH_TX_CTL]
#set_property IOSTANDARD LVCMOS25 [get_ports ETH_TX_CTL]

#set_property PACKAGE_PIN V8 [get_ports {ETH_TXD[0]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_TXD[0]}]

#set_property PACKAGE_PIN W8 [get_ports {ETH_TXD[1]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_TXD[1]}]

#set_property PACKAGE_PIN U6 [get_ports {ETH_TXD[2]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_TXD[2]}]

#set_property PACKAGE_PIN V9 [get_ports {ETH_TXD[3]}]
#set_property IOSTANDARD LVCMOS25 [get_ports {ETH_TXD[3]}]

#set_property PACKAGE_PIN Y18 [get_ports MIO40]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO40]

#set_property PACKAGE_PIN AA18 [get_ports MIO41]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO41]

#set_property PACKAGE_PIN AA17 [get_ports MIO42]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO42]

#set_property PACKAGE_PIN AB17 [get_ports MIO43]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO43]

#set_property PACKAGE_PIN U17 [get_ports MIO44]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO44]

#set_property PACKAGE_PIN V17 [get_ports MIO45]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO45]

##set_property PACKAGE_PIN U15 [get_ports MIO46]
##set_property IOSTANDARD LVCMOS25 [get_ports MIO46]
##
##set_property PACKAGE_PIN U16 [get_ports MIO47]
##set_property IOSTANDARD LVCMOS25 [get_ports MIO47]

#set_property PACKAGE_PIN W16 [get_ports MIO48]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO48]

#set_property PACKAGE_PIN Y16 [get_ports MIO49]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO49]

#set_property PACKAGE_PIN W17 [get_ports MIO50]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO50]

#set_property PACKAGE_PIN W18 [get_ports MIO51]
#set_property IOSTANDARD LVCMOS25 [get_ports MIO51]

## ----------------------------------------------------------------------------------------------------
## eof
## ----------------------------------------------------------------------------------------------------




