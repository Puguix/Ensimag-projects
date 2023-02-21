# TAG = bge
	.text

	lui x31, 0x10110
	lui x30, 0x10111
    bge x31, x30, pas_bon
    lui x31, 0x70000
    bge x31, x30, bon
    lui x31, 0x55555
bon:
    lui x31, 0xfffff
    lui x30, 0x0
    bge x31, x30, pas_bon
    lui x31, 0x12345
pas_bon:
    lui x31, 0

	# max_cycle 50
	# pout_start
	# 10110000
	# 70000000
    # fffff000
    # 12345000
    # 00000000
	# pout_end