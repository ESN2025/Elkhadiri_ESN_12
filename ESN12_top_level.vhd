library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;



entity ESN12_top_level is
    port (
        clk                 : in  std_logic;                      -- Input clock
        reset               : in  std_logic;                      -- Input reset (active high)
        opencore_scl        : inout std_logic;  -- LED output
		  opencore_sda        : inout std_logic;  -- LED output
		  boutton             : in    std_logic;
		  mode_select			 : out   std_logic;     
		  seg            : out std_logic_vector(7 downto 0);   -- LED output
		  output_av            : out std_logic_vector(31 downto 0)   -- LED output
    );
end entity ESN12_top_level;

architecture Behavioral of ESN12_top_level is



		  
		  
	  
    component ESN12_PROJET is
        port (
            clk_clk                             : in    std_logic                     := 'X'; -- clk
            opencores_i2c_0_export_0_scl_pad_io : inout std_logic                     := 'X'; -- scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io : inout std_logic                     := 'X'; -- sda_pad_io
            out_sig_readdata                    : out   std_logic_vector(31 downto 0);        -- readdata
            pio_0_s1_export                     : out   std_logic;                            -- export
            reset_reset_n                       : in    std_logic                     := 'X'; -- reset_n
            seg_export                          : out   std_logic_vector(7 downto 0);          -- export
				boutton_export                      : in    std_logic                     := 'X'  -- export
        );
    end component ESN12_PROJET;
	 
begin

    u0 : component ESN12_PROJET
        port map (
            clk_clk                             => clk,                             --                      clk.clk
            opencores_i2c_0_export_0_scl_pad_io => opencore_scl, -- opencores_i2c_0_export_0.scl_pad_io
            opencores_i2c_0_export_0_sda_pad_io => opencore_sda, --                         .sda_pad_io
            out_sig_readdata                    => output_av ,                    --                  out_sig.readdata
            pio_0_s1_export                     => mode_select,                     --                 pio_0_s1.export
            reset_reset_n                       => reset,                       --                    reset.reset_n
            seg_export                          => seg,                         --                      seg.export
				boutton_export                      => boutton
        );		  
		  

end architecture Behavioral;