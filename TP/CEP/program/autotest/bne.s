# TAG = bne
	.text

	lui x31, 0x10110
	lui x30, 0x10111
    bne x31, x30, bon
    lui x31, 0x00000
bon:
    lui x31, 0x54521
    lui x31, 0xfffff
    lui x30, 0xfffff
    bne x31, x30, pas_bon
    lui x31, 0x12345
pas_bon:
    lui x31, 0

	# max_cycle 50
	# pout_start
	# 10110000
	# 54521000
    # fffff000
    # 12345000
    # 00000000
	# pout_end