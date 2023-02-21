# TAG = add
	.text

	lui x31, 0
    lui x30, 0x1
    addi x30, x30, 0x001
    add x31, x30, x31
    lui x30, 0xfffff
    add x31, x30, x31

	# max_cycle 50
	# pout_start
	# 00000000
    # 00001001
    # 00000001
	# pout_end
