# TAG = sltiu
	.text

	lui x31, 0xfffff
    sltiu x31, x31, 0x000
    sltiu x31, x31, 0x700


	# max_cycle 50
	# pout_start
	# fffff000
	# 00000000
    # 00000001
	# pout_end