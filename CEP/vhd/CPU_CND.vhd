library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.PKG.all;

entity CPU_CND is
    generic (
        mutant      : integer := 0
    );
    port (
        rs1         : in w32;
        alu_y       : in w32;
        IR          : in w32;
        slt         : out std_logic;
        jcond       : out std_logic
    );
end entity;

architecture RTL of CPU_CND is

    signal extension_signe  : std_logic;
    signal rs1_signe : signed (32 downto 0);
    signal alu_y_signe : signed (32 downto 0);
    signal resultat : signed (32 downto 0);
    signal z : std_logic;


begin

    extension_signe <= (not IR(12) and not IR(6)) or (IR(6) and not IR(13));
    rs1_signe <= signed (rs1(31) & rs1) when extension_signe = '1' else signed ('0' & rs1);
    alu_y_signe <= signed (alu_y(31) & alu_y) when extension_signe = '1' else signed ('0' & alu_y);
    resultat <= rs1_signe - alu_y_signe;
    z <= '1' when resultat = "000000000000000000000000000000000" else '0';
    slt <= '0' when resultat(32) = '0' else '1';
    jcond <= ((IR(12) xor z) and not IR(14)) or (IR(14) and (IR(12) xor slt));
            

end architecture;
