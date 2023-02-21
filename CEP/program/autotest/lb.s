# TAG = lb
	.text

	lui x31, 0x01
	lui x30, 0x12345
	addi x30, x30, 0x678
    sb x30, 256(x31)
    lb x31, 256(x31)


	# max_cycle 50
	# pout_start
	# 00001000
	# 00000078
	# pout_end
