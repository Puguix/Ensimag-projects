# TAG = slt
	.text

	lui x31, 0x10110
	lui x30, 0x00111
    slt x31, x31, x30
    lui x30, 0x70000
    slt x31, x31, x30
    lui x31, 0x80000
    slt x31, x31, x30


	# max_cycle 50
	# pout_start
	# 10110000
	# 00000000
    # 00000001
    # 80000000
    # 00000001
	# pout_end