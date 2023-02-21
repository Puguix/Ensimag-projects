# TAG = csrrwi_mtvec
	.text

    csrrwi x30, mtvec, 24
    lui x31, 0
    csrrwi x31, mtvec, 9

	# max_cycle 50
	# pout_start
	# 00000000
	# 00000018
	# pout_end