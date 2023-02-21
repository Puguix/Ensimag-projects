# TAG = csrrci_mepc
	.text

	lui x31, 0x12345
    addi x31, x31, 0x678
    csrrw x30, mepc, x31
    lui x31, 0xf0000
    csrrci x31, mepc, 15
    csrrw x31, mepc, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# 12345678
	# f0000000
	# 12345678
	# 12345670
	# pout_end