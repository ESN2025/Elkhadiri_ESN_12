library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity counter_avalon_interface is
    Port (
        clk        : in std_logic;
        reset      : in std_logic;
        av_address : in std_logic_vector(2 downto 0);
        av_read    : in std_logic;
        av_write   : in std_logic;
        av_readdata: out std_logic_vector(15 downto 0);
		  output_av: out std_logic_vector(31 downto 0);
        av_writedata: in std_logic_vector(15 downto 0)
    );
end counter_avalon_interface;

architecture Behavioral of counter_avalon_interface is
    signal counter: std_logic_vector(11 downto 0); 
    signal digits: std_logic_vector(31 downto 0); 
begin
    process(clk, reset)
    begin
        if reset = '1' then
            counter <= (others => '0');
        elsif rising_edge(clk) then
            if av_write = '1' then
                
                counter <= av_writedata(11 downto 0);
            end if;
        end if;
    end process;

   
    process(counter)
    begin
       
        case counter(3 downto 0) is
            when "0000" => digits(6 downto 0) <= "1000000"; 
            when "0001" => digits(6 downto 0) <= "1111001"; 
            when "0010" => digits(6 downto 0) <= "0100100"; 
            when "0011" => digits(6 downto 0) <= "0110000"; 
            when "0100" => digits(6 downto 0) <= "0011001"; 
            when "0101" => digits(6 downto 0) <= "0010010"; 
            when "0110" => digits(6 downto 0) <= "0000010"; 
            when "0111" => digits(6 downto 0) <= "1111000"; 
            when "1000" => digits(6 downto 0) <= "0000000"; 
            when "1001" => digits(6 downto 0) <= "0010000"; 
            when others => digits(6 downto 0) <= "1111111"; 
        end case;

        
        case counter(7 downto 4) is
            when "0000" => digits(13 downto 7) <= "1000000"; 
            when "0001" => digits(13 downto 7) <= "1111001"; 
            when "0010" => digits(13 downto 7) <= "0100100"; 
            when "0011" => digits(13 downto 7) <= "0110000"; 
            when "0100" => digits(13 downto 7) <= "0011001"; 
            when "0101" => digits(13 downto 7) <= "0010010"; 
            when "0110" => digits(13 downto 7) <= "0000010"; 
            when "0111" => digits(13 downto 7) <= "1111000"; 
            when "1000" => digits(13 downto 7) <= "0000000"; 
            when "1001" => digits(13 downto 7) <= "0010000"; 
            when others => digits(13 downto 7) <= "0000000"; 
        end case;

        
        case counter(11 downto 8) is
            when "0000" => digits(20 downto 14) <= "1000000"; 
            when "0001" => digits(20 downto 14) <= "1111001"; 
            when "0010" => digits(20 downto 14) <= "0100100"; 
            when "0011" => digits(20 downto 14) <= "0110000"; 
            when "0100" => digits(20 downto 14) <= "0011001"; 
            when "0101" => digits(20 downto 14) <= "0010010"; 
            when "0110" => digits(20 downto 14) <= "0000010"; 
            when "0111" => digits(20 downto 14) <= "1111000"; 
            when "1000" => digits(20 downto 14) <= "0000000"; 
            when "1001" => digits(20 downto 14) <= "0010000"; 
            when others => digits(20 downto 14) <= "0000000"; 
        end case;
    end process;

    
    digits(31 downto 21) <= (others => '0');
    output_av <= digits;   
end Behavioral;

