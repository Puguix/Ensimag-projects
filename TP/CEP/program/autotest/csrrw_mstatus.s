# TAG = csrrw_mstatus
	.text

	lui x31, 0x12345
    csrrw x30, mstatus, x31
    lui x31, 0
    csrrw x31, mstatus, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# 00000000
	# 12345000
	# pout_end