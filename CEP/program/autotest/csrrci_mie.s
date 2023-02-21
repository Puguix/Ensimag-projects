# TAG = csrrci_mie
	.text

	lui x31, 0x12345
    addi x31, x31, 0x671
    csrrw x30, mie, x31
    lui x31, 0xf0000
    csrrci x31, mie, 15
    csrrw x31, mie, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# 12345671
	# f0000000
	# 12345671
	# 12345670
	# pout_end