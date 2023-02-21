# TAG = or
	.text

	lui x31, 0x10110
	lui x30, 0x10110
    or x31, x30, x31
    lui x30, 0x00000
    addi x30, x30, 0x181
    or x31, x30, x31

	# max_cycle 50
	# pout_start
	# 10110000
	# 10110000
	# 10110181
	# pout_end