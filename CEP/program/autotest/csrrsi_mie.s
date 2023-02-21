# TAG = csrrsi_mie
	.text

	lui x31, 0x12345
    addi x31, x31, 0x678
    csrrw x30, mie, x31
    lui x31, 0xf0000
    csrrsi x31, mie, 0xf
    csrrw x31, mie, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# 12345678
	# f0000000
	# 12345670
	# 12345677
	# pout_end