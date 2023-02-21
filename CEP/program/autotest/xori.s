# TAG = xori
	.text

	lui x31, 0x10110
    xori x31, x31, 0x191
    xori x31, x31, 0xffffffff

	# max_cycle 50
	# pout_start
	# 10110000
	# 10110191
	# efeefe6e
	# pout_end