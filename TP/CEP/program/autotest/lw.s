# TAG = lw
	.text

	lui x31, 0x01
	lui x30, 0x12345
    sw x30, 256(x31)
    lw x31, 256(x31)


	# max_cycle 50
	# pout_start
	# 00001000
	# 12345000
	# pout_end