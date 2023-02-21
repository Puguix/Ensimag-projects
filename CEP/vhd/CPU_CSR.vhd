library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.PKG.all;

entity CPU_CSR is
    generic (
        INTERRUPT_VECTOR : waddr   := w32_zero;
        mutant           : integer := 0
    );
    port (
        clk         : in  std_logic;
        rst         : in  std_logic;

        -- Interface de et vers la PO
        cmd         : in  PO_cs_cmd;
        it          : out std_logic;
        pc          : in  w32;
        rs1         : in  w32;
        imm         : in  W32;
        csr         : out w32;
        mtvec       : out w32;
        mepc        : out w32;

        -- Interface de et vers les IP d'interruption
        irq         : in  std_logic;
        meip        : in  std_logic;
        mtip        : in  std_logic;
        mie         : out w32;
        mip         : out w32;
        mcause      : in  w32
    );
end entity;

architecture RTL of CPU_CSR is
    -- Fonction retournant la valeur à écrire dans un csr en fonction
    -- du « mode » d'écriture, qui dépend de l'instruction
    function CSR_write (CSR        : w32;
                         CSR_reg    : w32;
                         WRITE_mode : CSR_WRITE_mode_type)
        return w32 is
        variable res : w32;
    begin
        case WRITE_mode is
            when WRITE_mode_simple =>
                res := CSR;
            when WRITE_mode_set =>
                res := CSR_reg or CSR;
            when WRITE_mode_clear =>
                res := CSR_reg and (not CSR);
            when others => null;
        end case;
        return res;
    end CSR_write;

    -- signaux
    signal mcause_in : w32;
    signal mcause_out : w32;
    signal mip_in : w32;
    signal mip_out : w32;
    signal mie_in : w32;
    signal mie_out : w32;
    signal mstatus_waiting : w32;
    signal mstatus_in : w32;
    signal mstatus_out : w32;
    signal mtvec_in : w32;
    signal mtvec_out : w32;
    signal mepc_in : w32;
    signal mepc_out : w32;
    signal TO_CSR : w32;

begin
    --mettre a jour les registres aux signaux de la clock
    gpr_flip_flops : process (clk)
    begin
        if clk'event and clk='1' then
            if rst ='1' then
                mcause_out   <= w32_zero;
                mip_out   <= w32_zero;
                mie_out   <= w32_zero;
                mstatus_out   <= w32_zero;
                mtvec_out  <= w32_zero;
                mepc_out  <= w32_zero;
            else
                mcause_out    <= mcause_in;
                mip_out    <= mip_in;
                mie_out <= mie_in;
                mstatus_out    <= mstatus_in;
                mtvec_out    <= mtvec_in;
                mepc_out   <= mepc_in;
            end if;
        end if;
    end process gpr_flip_flops;

    TO_CSR <= rs1 when cmd.TO_CSR_sel = TO_CSR_from_rs1 else imm;

    mstatus_waiting <= TO_CSR(31 downto 4) & '1' & TO_CSR(2 downto 0) when cmd.MSTATUS_mie_set = '1' else
            TO_CSR(31 downto 4) & '0' & TO_CSR(2 downto 0) when cmd.MSTATUS_mie_reset = '1' else
            TO_CSR;

    -- Calcul des entrées des registres
    gpr_input_selection : process (all)
    begin
        
        -- Les registres prennent leur valeur par défaut
        mcause_in  <= irq & mcause(30 downto 0);
        mip_in(7)  <= mtip;
        mip_in(11)  <= meip;
        mie_in  <= mie_out;
        mstatus_in <= mstatus_out;
        mtvec_in <= mtvec_out;
        mepc_in <= mepc_out;
        
        
        -- Mise a jour des registres
        case cmd.CSR_we is
            when CSR_mie =>
                mie_in <= CSR_write( TO_CSR(31 downto 4) & mie(3) & TO_CSR(2 downto 0), mie_out, cmd.CSR_WRITE_mode);
            when CSR_mstatus =>
                mstatus_in <= CSR_write( mstatus_waiting, mstatus_out, cmd.CSR_WRITE_mode);
            when CSR_mtvec =>
                mtvec_in <= CSR_write( TO_CSR, mtvec_out, cmd.CSR_WRITE_mode)(31 downto 2) & "00";
            when CSR_mepc =>
                if cmd.MEPC_sel = MEPC_from_pc then 
                    mepc_in <=  CSR_write( pc, mepc_out, cmd.CSR_WRITE_mode);
                else 
                    mepc_in <=  CSR_write( TO_CSR, mepc_out, cmd.CSR_WRITE_mode)(31 downto 2) & "00";
                end if;
            when others => null;
        end case;

        -- multiplexeurs
        case cmd.CSR_sel is
            when CSR_from_mcause =>
                csr <= mcause_out;
            when CSR_from_mip =>
                csr <= mip_out;
            when CSR_from_mie =>
                csr <= mie_out;
            when CSR_from_mstatus =>
                csr <= mstatus_out;
            when CSR_from_mtvec =>
                csr <= mtvec_out;
            when others =>
                csr <= mepc_out;
        end case;

        mip <= mip_out;
        mie <= mie_out;
        mtvec <= mtvec_out;
        mepc <= mepc_out;
        it <= irq and mstatus_out(3);

    end process gpr_input_selection;    

end architecture;
