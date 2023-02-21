# TAG = slti
	.text

	lui x31, 0xfffff
    slti x31, x31, 0x000
    slti x31, x31, 0xffffffff


	# max_cycle 50
	# pout_start
	# fffff000
	# 00000001
    # 00000000
	# pout_end