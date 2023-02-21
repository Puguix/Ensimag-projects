# TAG = ori
	.text

	lui x31, 0x10110
    ori x31, x31, 0x191
    ori x31, x31, 0xffffffff

	# max_cycle 50
	# pout_start
	# 10110000
	# 10110191
	# ffffffff
	# pout_end