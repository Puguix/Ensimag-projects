# TAG = csrrwi_mie
	.text

    csrrwi x30, mie, 24
    lui x31, 0
    csrrwi x31, mie, 9

	# max_cycle 50
	# pout_start
	# 00000000
	# 00000010
	# pout_end