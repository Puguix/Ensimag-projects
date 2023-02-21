# TAG = jalr
	.text

	lui x31, 1
    jalr x30, 24(x31)
    lui x31, 8
    lui x31, 12
    lui x31, 16
    lui x31, 20
    lui x31, 24 # jump1 ici


	# max_cycle 50
	# pout_start
	# 00001000
	# 00018000
	# pout_end