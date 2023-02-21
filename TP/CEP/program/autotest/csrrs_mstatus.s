# TAG = csrrs_mstatus
	.text

	lui x31, 0x12345
    csrrw x30, mstatus, x31
    lui x31, 0xf0000
    csrrs x31, mstatus, x31
    csrrw x31, mstatus, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# f0000000
	# 12345000
	# f2345000
	# pout_end