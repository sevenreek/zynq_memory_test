connect -url tcp:127.0.0.1:3121
source C:/Development/VHDL/zynq_memory_test/zynqexample.sdk/System_wrapper_hw_platform_0/ps7_init.tcl
targets -set -filter {jtag_cable_name =~ "Platform Cable USB 00000acb5d4001" && level==0} -index 1
fpga -file C:/Development/VHDL/zynq_memory_test/zynqexample.sdk/System_wrapper_hw_platform_0/System_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Platform Cable USB 00000acb5d4001"} -index 0
loadhw -hw C:/Development/VHDL/zynq_memory_test/zynqexample.sdk/System_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Platform Cable USB 00000acb5d4001"} -index 0
stop
ps7_init
configparams force-mem-access 0
bpadd -addr &main
