# TAG = sra
	.text

	lui x31, 0xfffff
    addi x31, x31, 0x001
    lui x30, 0
    addi x30, x30, 0x001
    sra x31, x31, x30
    lui x30, 0
    addi x30, x30, 0x01f
    sra x31, x31, x30


	# max_cycle 50
	# pout_start
	# fffff000
    # fffff001
    # fffff800
    # ffffffff
	# pout_end
