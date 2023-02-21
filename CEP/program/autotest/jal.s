# TAG = jal
	.text

	lui x31, 0x02000
    jal x30, jump
    lui x31, 0
jump:
    lui x31, 0x00001


	# max_cycle 50
	# pout_start
	# 02000000
	# 00001000
	# pout_end