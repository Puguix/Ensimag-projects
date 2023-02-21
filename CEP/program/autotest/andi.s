# TAG = andi
	.text

	lui x31, 0x10110
    andi x31, x31, 0x000
	lui x31, 0x10110
    addi x31, x31, 0x111
    andi x31, x31, 0xfffff803

	# max_cycle 50
	# pout_start
	# 10110000
    # 00000000
	# 10110000
	# 10110111
    # 10110001
	# pout_end