# TAG = xor
	.text

	lui x31, 0x10110
    lui x30, 0x10110
    xor x31, x31, x30
    xor x31, x31, x30

	# max_cycle 50
	# pout_start
	# 10110000
	# 00000000
	# 10110000
	# pout_end