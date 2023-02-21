library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library work;
use work.PKG.all;


entity CPU_PC is
    generic(
        mutant: integer := 0
    );
    Port (
        -- Clock/Reset
        clk    : in  std_logic ;
        rst    : in  std_logic ;

        -- Interface PC to PO
        cmd    : out PO_cmd ;
        status : in  PO_status
    );
end entity;

architecture RTL of CPU_PC is
    type State_type is (
        S_Error,
        S_Init,
        S_Pre_Fetch,
        S_Fetch,
        S_Decode,
        S_LUI,
        S_ADDI,
        S_ADD,
        S_OR,
        S_AND,
        S_ORI,
        S_ANDI,
        S_XOR,
        S_XORI,
        S_SUB,
        S_SLL,
        S_SRL,
        S_SRA,
        S_SRAI,
        S_SLLI,
        S_SRLI,
        S_AUIPC,
        S_COMPARE_BRANCH,
        S_COMPARE_SET_REGISTRE,
        S_COMPARE_SET_IMM,
        S_LW,
        S_AD,
        S_STORE,
        S_PRE_LOAD,
        S_LH,
        S_LHU,
        S_LB,
        S_LBU,
        S_JAL,
        S_JALR,
        S_INTERUPT1,
        S_INTERUPT2,
        S_FIN_INTERUPT,
        S_CSRR,
        S_CSRR2
    );

    signal state_d, state_q : State_type;


begin

    FSM_synchrone : process(clk)
    begin
        if clk'event and clk='1' then
            if rst='1' then
                state_q <= S_Init;
            else
                state_q <= state_d;
            end if;
        end if;
    end process FSM_synchrone;

    FSM_comb : process (state_q, status)
    begin

        -- Valeurs par défaut de cmd à définir selon les préférences de chacun
        cmd.ALU_op            <= UNDEFINED;
        cmd.LOGICAL_op        <= UNDEFINED;
        cmd.ALU_Y_sel         <= UNDEFINED;

        cmd.SHIFTER_op        <= UNDEFINED;
        cmd.SHIFTER_Y_sel     <= UNDEFINED;

        cmd.RF_we             <= 'U';
        cmd.RF_SIZE_sel       <= UNDEFINED;
        cmd.RF_SIGN_enable    <= 'U';
        cmd.DATA_sel          <= UNDEFINED;

        cmd.PC_we             <= 'U';
        cmd.PC_sel            <= UNDEFINED;

        cmd.PC_X_sel          <= UNDEFINED;
        cmd.PC_Y_sel          <= UNDEFINED;

        cmd.TO_PC_Y_sel       <= UNDEFINED;

        cmd.AD_we             <= 'U';
        cmd.AD_Y_sel          <= UNDEFINED;

        cmd.IR_we             <= 'U';

        cmd.ADDR_sel          <= UNDEFINED;
        cmd.mem_we            <= 'U';
        cmd.mem_ce            <= 'U';

        cmd.cs.CSR_we            <= UNDEFINED;

        cmd.cs.TO_CSR_sel        <= UNDEFINED;
        cmd.cs.CSR_sel           <= UNDEFINED;
        cmd.cs.MEPC_sel          <= UNDEFINED;

        cmd.cs.MSTATUS_mie_set   <= 'U';
        cmd.cs.MSTATUS_mie_reset <= 'U';

        cmd.cs.CSR_WRITE_mode    <= UNDEFINED;

        state_d <= state_q;

        case state_q is
            when S_Error =>
                -- Etat transitoire en cas d'instruction non reconnue 
                -- Aucune action
                state_d <= S_Init;

            when S_Init =>
                -- PC <- RESET_VECTOR
                cmd.PC_we <= '1';
                cmd.PC_sel <= PC_rstvec;
                state_d <= S_Pre_Fetch;

            when S_Pre_Fetch =>
                -- mem[PC]
                cmd.mem_we   <= '0';
                cmd.mem_ce   <= '1';
                cmd.ADDR_sel <= ADDR_from_pc;
                state_d      <= S_Fetch;

            when S_Fetch =>
                --detection d'erreurs
                if status.IT = true then 
                     state_d <= S_INTERUPT1;
                -- IR <- mem_datain
                else
                    cmd.IR_we <= '1';
                    state_d <= S_Decode;
                end if;

                -- Décodage effectif des instructions,
                -- à compléter par vos soins

            when S_Decode =>
                -- On peut aussi utiliser un case, ...
                -- et ne pas le faire juste pour les branchements et auipc

                -- LUI
                if status.IR(6 downto 0) = "0110111" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_LUI;

                --addi    
                elsif status.IR(6 downto 0) = "0010011" and status.IR(14 downto 12) = "000" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_ADDI;

                --add
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_ADD;

                --and
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "111" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_AND;

                --andi
                elsif status.IR(14 downto 12) = "111" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_ANDI;

                --or
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "110" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_OR;

                --ori
                elsif status.IR(14 downto 12) = "110" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_ORI;

                --xor
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "100" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_XOR;

                --xori
                elsif status.IR(14 downto 12) = "100" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_XORI;

                --sub    
                elsif status.IR(31 downto 25) = "0100000" and status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SUB;

                --sll    
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SLL;

                --srl    
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SRL;

                --sra    
                elsif status.IR(31 downto 25) = "0100000" and status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0110011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SRA;

                --slli    
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SLLI;

                --srli    
                elsif status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SRLI;

                --srai    
                elsif status.IR(31 downto 25) = "0100000" and status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0010011" then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_SRAI;
                    
                --auipc
                elsif status.IR(6 downto 0) = "0010111" then
                    state_d <= S_AUIPC;

                --beq bne bge bgeu blt bltu    
                elsif ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "1100011" ) or ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "1100011" ) or ( status.IR(14 downto 12) = "111" and status.IR(6 downto 0) = "1100011" ) or ( status.IR(14 downto 12) = "100" and status.IR(6 downto 0) = "1100011" ) or ( status.IR(14 downto 12) = "110" and status.IR(6 downto 0) = "1100011" ) or ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "1100011" ) then
                    state_d <= S_COMPARE_BRANCH;
                
                --sltu slt
                elsif ( status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0110011" ) or ( status.IR(31 downto 25) = "0000000" and status.IR(14 downto 12) = "011" and status.IR(6 downto 0) = "0110011" ) then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_COMPARE_SET_REGISTRE;

                --slti sltiu
                elsif ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0010011" ) or ( status.IR(14 downto 12) = "011" and status.IR(6 downto 0) = "0010011" ) then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_COMPARE_SET_IMM; 

                --store ou load
                elsif ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0100011" ) or ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0100011" ) or ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0100011" ) or ( status.IR(14 downto 12) = "100" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0000011" ) then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_AD;

                --jal
                elsif ( status.IR(6 downto 0) = "1101111" ) then
                    state_d <= S_JAL;

                --jalr
                elsif ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "1100111" ) then
                    state_d <= S_JALR;

                --csrr
                elsif ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "1110011" ) or ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "1110011" ) or ( status.IR(14 downto 12) = "011" and status.IR(6 downto 0) = "1110011" ) or ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "1110011" ) or ( status.IR(14 downto 12) = "110" and status.IR(6 downto 0) = "1110011" ) or ( status.IR(14 downto 12) = "111" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                    cmd.PC_sel <= PC_from_pc;
                    cmd.PC_we <= '1';
                    state_d <= S_CSRR;

                --error
                else
                    state_d <= S_Error; -- Pour détecter les ratés du décodage
                end if;
                

---------- Instructions avec immediat de type U ----------

            when S_LUI =>
                -- rd <- ImmU + 0
                cmd.PC_X_sel <= PC_X_cst_x00;
                cmd.PC_Y_sel <= PC_Y_immU;
                cmd.RF_we <= '1';
                cmd.DATA_sel <= DATA_from_pc;
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_AUIPC =>
                -- rd <- imm + pc
                cmd.PC_X_sel <= PC_X_pc;
                cmd.PC_Y_sel <= PC_Y_immU;
                cmd.DATA_sel <= DATA_from_pc;
                cmd.RF_we <= '1';
                -- pc <- pc+4
                cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                cmd.PC_sel <= PC_from_pc;
                cmd.PC_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;

---------- Instructions arithmétiques et logiques ----------

            when S_ADDI =>
                -- rd <- rs + ImmI
                cmd.ALU_Y_sel <= ALU_Y_immI;
                cmd.ALU_op <= ALU_plus;
                cmd.DATA_sel <= DATA_from_alu;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_ADD =>
                -- rd <- rs1 + rs2
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                cmd.ALU_op <= ALU_plus;
                cmd.DATA_sel <= DATA_from_alu;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_AND =>
                -- rd <- rs1 and rs2
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                cmd.LOGICAL_op <= LOGICAL_and;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_ANDI =>
                -- rd <- rs1 and immI
                cmd.ALU_Y_sel <= ALU_Y_immI;
                cmd.LOGICAL_op <= LOGICAL_and;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_OR =>
                -- rd <- rs1 or rs2
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                cmd.LOGICAL_op <= LOGICAL_or;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_ORI =>
                -- rd <- rs1 or immI
                cmd.ALU_Y_sel <= ALU_Y_immI;
                cmd.LOGICAL_op <= LOGICAL_or;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_XOR =>
                -- rd <- rs1 xor rs2
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                cmd.LOGICAL_op <= LOGICAL_xor;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_XORI =>
                -- rd <- rs1 xor immI
                cmd.ALU_Y_sel <= ALU_Y_immI;
                cmd.LOGICAL_op <= LOGICAL_xor;
                cmd.DATA_sel <= DATA_from_logical;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SUB =>
                -- rd <- rs1 - rs2
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                cmd.ALU_op <= ALU_minus;
                cmd.DATA_sel <= DATA_from_alu;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SLL =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_ll;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_rs2;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SRL =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_rl;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_rs2;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SRA =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_ra;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_rs2;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SLLI =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_ll;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_ir_sh;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SRLI =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_rl;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_ir_sh;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_SRAI =>
                -- rd <- rs1 + rs2
                cmd.SHIFTER_op <= SHIFT_ra;
                cmd.SHIFTER_Y_sel <= SHIFTER_Y_ir_sh;
                cmd.DATA_sel <= DATA_from_shifter;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when S_COMPARE_BRANCH =>
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                -- saute si condition et continue
                if status.jcond = true then
                    cmd.TO_PC_Y_sel <= TO_PC_Y_immB;
                else 
                    cmd.TO_PC_Y_sel <= TO_PC_Y_cst_x04;
                end if;
                cmd.PC_sel <= PC_from_pc;
                cmd.PC_we <= '1';
                state_d <= S_Pre_Fetch;
                

            when S_COMPARE_SET_REGISTRE =>
                cmd.ALU_Y_sel <= ALU_Y_rf_rs2;
                --ecrit le bon truc dans le registre
                cmd.DATA_sel <= DATA_from_slt;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;
                

            when S_COMPARE_SET_IMM =>
                cmd.ALU_Y_sel <= ALU_Y_immI;
                --ecrit le bon truc dans le registre
                cmd.DATA_sel <= DATA_from_slt;
                cmd.RF_we <= '1';
                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

---------- Instructions de saut ----------

            when S_JAL =>
                --saut ou appel de fonction inconditionnel immédiat
                cmd.RF_we <= '1';
                cmd.DATA_sel <= DATA_from_pc;
                cmd.PC_X_sel <= PC_X_pc;
                cmd.PC_Y_sel <= PC_Y_cst_x04;
                cmd.PC_we <= '1';
                cmd.PC_sel <= PC_from_pc;
                cmd.TO_PC_Y_sel <= TO_PC_Y_immJ;
                -- next state
                state_d <= S_Pre_Fetch;

            when S_JALR =>
                --saut ou appel de fonction inconditionnel immédiat
                cmd.RF_we <= '1';
                cmd.DATA_sel <= DATA_from_pc;
                cmd.PC_X_sel <= PC_X_pc;
                cmd.PC_Y_sel <= PC_Y_cst_x04;
                cmd.PC_we <= '1';
                cmd.PC_sel <= PC_from_alu;
                cmd.ALU_Y_sel <= ALU_Y_immI;
                cmd.ALU_op <= ALU_plus;
                -- next state
                state_d <= S_Pre_Fetch;

---------- Instructions de chargement à partir de la mémoire ----------

            when S_AD =>
                --ecriture d’un mot dans AD
                cmd.AD_we <= '1';
                -- next state
                --load
                if ( status.IR(14 downto 12) = "100" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0000011" ) or ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0000011" ) then
                    cmd.AD_Y_sel <= AD_Y_immI;
                    state_d <= S_PRE_LOAD;
                --store
                else
                    cmd.AD_Y_sel <= AD_Y_immS;
                    state_d <= S_STORE;
                end if;

            when S_PRE_LOAD =>
                -- mem[PC]
                cmd.mem_we   <= '0';
                cmd.mem_ce   <= '1';
                cmd.ADDR_sel <= ADDR_from_ad;
                -- next state
                --lw
                if ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0000011" ) then
                    state_d <= S_LW;
                --lh
                elsif ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "0000011" ) then
                    state_d <= S_LH;                
                --lhu
                elsif ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "0000011" ) then
                    state_d <= S_LHU;
                --lb
                elsif ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0000011" ) then
                    state_d <= S_LB;
                --lbu
                else
                    state_d <= S_LBU;
                end if;
            
            when S_LW =>
                --Lecture d’un mot de la mémoire
                cmd.DATA_sel <= DATA_from_mem;
                cmd.RF_SIZE_sel <= RF_SIZE_word;
                cmd.RF_SIGN_enable <= '1';
                cmd.RF_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;
            
            when S_LH =>
                --Lecture d’un mot de la mémoire
                cmd.DATA_sel <= DATA_from_mem;
                cmd.RF_SIZE_sel <= RF_SIZE_half;
                cmd.RF_SIGN_enable <= '1';
                cmd.RF_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;
            
            when S_LHU =>
                --Lecture d’un mot de la mémoire
                cmd.DATA_sel <= DATA_from_mem;
                cmd.RF_SIZE_sel <= RF_SIZE_half;
                cmd.RF_SIGN_enable <= '0';
                cmd.RF_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;
            
            when S_LB =>
                --Lecture d’un mot de la mémoire
                cmd.DATA_sel <= DATA_from_mem;
                cmd.RF_SIZE_sel <= RF_SIZE_byte;
                cmd.RF_SIGN_enable <= '1';
                cmd.RF_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;
            
            when S_LBU =>
                --Lecture d’un mot de la mémoire
                cmd.DATA_sel <= DATA_from_mem;
                cmd.RF_SIZE_sel <= RF_SIZE_byte;
                cmd.RF_SIGN_enable <= '0';
                cmd.RF_we <= '1';
                -- next state
                state_d <= S_Pre_Fetch;

---------- Instructions de sauvegarde en mémoire ----------

            when S_STORE =>
                --ecriture d’un mot dans mem
                cmd.mem_we <= '1';
                cmd.mem_ce <= '1';
                cmd.ADDR_sel <= ADDR_from_ad;
                if ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "0100011" ) then
                    cmd.RF_SIZE_sel <= RF_SIZE_word;
                elsif ( status.IR(14 downto 12) = "000" and status.IR(6 downto 0) = "0100011" ) then
                    cmd.RF_SIZE_sel <= RF_SIZE_byte;
                else
                    cmd.RF_SIZE_sel <= RF_SIZE_half;
                end if;
                -- next state
                state_d <= S_Pre_Fetch;

---------- Instructions d'accès aux CSR ----------

            when S_INTERUPT1 =>
                -- mepc <= pc
                cmd.cs.MEPC_sel <= MEPC_from_pc;
                cmd.cs.CSR_we <= CSR_mepc;
                cmd.cs.CSR_WRITE_mode <= WRITE_mode_simple;
                -- pc <= mtvec
                cmd.PC_sel <= PC_mtvec;
                cmd.PC_we <= '1';
                --next state
                state_d <= S_INTERUPT2;

            when S_INTERUPT2 =>
                -- miepc <= '0'
                cmd.cs.MSTATUS_mie_set <= '0';
                --next state
                state_d <= S_Pre_Fetch;

            --mret
            when S_FIN_INTERUPT =>
                -- pc <= mepc
                cmd.cs.MSTATUS_mie_reset <= '1';
                cmd.PC_sel <= PC_from_mepc;
                cmd.PC_we <= '1';
                --next state
                state_d <= S_Pre_Fetch;

            when S_CSRR =>
                --rd <= csr
                cmd.RF_we <= '1';
                cmd.DATA_sel <= DATA_from_csr;
                -- ou qu'on lit?
                --mie
                if status.IR(31 downto 20) = "001100000100" then
                    cmd.cs.CSR_sel <= CSR_from_mie;
                --mstatus
                elsif status.IR(31 downto 20) = "001100000000" then
                    cmd.cs.CSR_sel <= CSR_from_mstatus;
                --mcause
                elsif status.IR(31 downto 20) = "001101000010" then
                    cmd.cs.CSR_sel <= CSR_from_mcause;
                --mip
                elsif status.IR(31 downto 20) = "001101000100" then
                    cmd.cs.CSR_sel <= CSR_from_mip;
                --mtvec
                elsif status.IR(31 downto 20) = "001100000101" then
                    cmd.cs.CSR_sel <= CSR_from_mtvec;
                --mepc
                else
                    cmd.cs.CSR_sel <= CSR_from_mepc;
                end if;
                -- next state
                state_d <= S_CSRR2;

            when S_CSRR2 =>
                --csr <= rs ou imm
                -- ou qu'on ecrit?
                --mie
                if status.IR(31 downto 20) = "001100000100" then
                    cmd.cs.CSR_we <= CSR_mie;
                --mstatus
                elsif status.IR(31 downto 20) = "001100000000" then
                    cmd.cs.CSR_we <= CSR_mstatus;
                --mtvec
                elsif status.IR(31 downto 20) = "001100000101" then
                    cmd.cs.CSR_we <= CSR_mtvec;
                --mepc
                else
                    cmd.cs.CSR_we <= CSR_mepc;
                end if;

                --csrrw
                if ( status.IR(14 downto 12) = "001" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_rs1;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_simple;
                --csrrs
                elsif ( status.IR(14 downto 12) = "010" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_rs1;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_set;
                --csrrc  
                elsif ( status.IR(14 downto 12) = "011" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_rs1;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_clear;
                --csrrwi
                elsif ( status.IR(14 downto 12) = "101" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_imm;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_simple;
                --csrrsi
                elsif ( status.IR(14 downto 12) = "110" and status.IR(6 downto 0) = "1110011" ) then
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_imm;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_set;
                --csrrci
                else
                    cmd.cs.TO_CSR_sel <= TO_CSR_from_imm;
                    cmd.cs.CSR_WRITE_mode <= WRITE_mode_clear;
                end if;

                -- lecture mem[PC]
                cmd.ADDR_sel <= ADDR_from_pc;
                cmd.mem_ce <= '1';
                cmd.mem_we <= '0';
                -- next state
                state_d <= S_Fetch;

            when others => null;
        end case;

    end process FSM_comb;

end architecture;
