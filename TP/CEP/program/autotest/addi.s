# TAG = addi
	.text

	lui x31, 0x12345
	addi x31, x31, 0x0
	addi x31, x31, 0x1
	addi x31, x31, 0xffffffff
	addi x31, x31, 0x400

	# max_cycle 50
	# pout_start
	# 12345000
	# 12345000
	# 12345001
	# 12345000
	# 12345400
	# pout_end
