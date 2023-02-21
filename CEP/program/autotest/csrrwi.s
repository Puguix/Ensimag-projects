# TAG = csrrwi_mepc
	.text

    csrrwi x30, mepc, 24
    lui x31, 0
    csrrwi x31, mepc, 9

	# max_cycle 50
	# pout_start
	# 00000000
	# 00000018
	# pout_end