# TAG = csrrsi_mstatus
	.text

	lui x31, 0x12345
    addi x31, x31, 0x678
    csrrw x30, mstatus, x31
    lui x31, 0xf0000
    csrrsi x31, mstatus, 0xf
    csrrw x31, mstatus, x30

	# max_cycle 50
	# pout_start
	# 12345000
	# 12345678
	# f0000000
	# 12345678
	# 1234567f
	# pout_end