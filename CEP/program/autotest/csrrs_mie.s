# TAG = csrrs_mie
	.text

	lui x31, 0x12345
    csrrw x30, mie, x31
    lui x31, 0xf0000
    csrrs x31, mie, x31
    csrrw x31, mie, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# f0000000
	# 12345000
	# f2345000
	# pout_end