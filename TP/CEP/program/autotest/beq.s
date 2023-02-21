# TAG = beq
	.text

	lui x31, 0x10110
	lui x30, 0x10110
	beq x31, x30, saut
	lui x31, 0xfffff
saut:
	lui x31, 0x12345

	# max_cycle 50
	# pout_start
	# 10110000
	# 12345000
	# pout_end