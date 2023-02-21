# TAG = and
	.text

	lui x31, 0x00111
    lui x30, 0x10011
    and x31, x30, x31
    and x31, x30, x30

	# max_cycle 50
	# pout_start
	# 00111000
    # 00011000
    # 10011000
	# pout_end