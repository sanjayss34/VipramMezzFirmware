--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2014 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--    Generated from core with identifier:                                    --
--    xilinx.com:ip:gig_eth_pcs_pma:11.5                                      --
--                                                                            --
--    The Ethernet 1000BASE-X PCS/PMA or SGMII LogiCORE(TM) provides the      --
--    functionality to implement one of two different specifications:         --
--    firstly the IEEE 802.3 1000BASE-X specification; secondly the           --
--    Serial-GMII (SGMII) specification which is closely based on             --
--    1000BASE-X.  The core provides a choice of physical interface           --
--    options: a Ten-Bit-Interface (TBI) for connection to an external        --
--    SERDES; high speed serial functionality using the device specific       --
--    transceivers in Virtex-7, Kintex-7, Artix-7, Virtex-4, Virtex-5,        --
--    Virtex-6 and Spartan-6; SGMII standard only - LVDS using SelectIO in    --
--    Virtex-6 devices -2 speed grade and faster.  All options provide up     --
--    to 1 gigabit per second total bandwidth.  When perfoming the SGMII      --
--    standard, the core can carry Ethernet traffic up to 1 gigabit per       --
--    second total bandwidth; this is inclusive of 10Mbps, 100Mbps and        --
--    1Gbps Ethernet speeds.  The core is designed to interface to the        --
--    LogiCORE Tri-Mode Ethernet MAC from Xilinx to provide a complete        --
--    solution.                                                               --
--------------------------------------------------------------------------------

-- The following code must appear in the VHDL architecture header:

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT gig_eth_pcs_pma_v11_5
  PORT (
    reset : IN STD_LOGIC;
    signal_detect : IN STD_LOGIC;
    mgt_rx_reset : OUT STD_LOGIC;
    mgt_tx_reset : OUT STD_LOGIC;
    userclk : IN STD_LOGIC;
    userclk2 : IN STD_LOGIC;
    dcm_locked : IN STD_LOGIC;
    rxbufstatus : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    rxchariscomma : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    rxcharisk : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    rxclkcorcnt : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    rxdata : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    rxdisperr : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    rxnotintable : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    rxrundisp : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    txbuferr : IN STD_LOGIC;
    powerdown : OUT STD_LOGIC;
    txchardispmode : OUT STD_LOGIC;
    txchardispval : OUT STD_LOGIC;
    txcharisk : OUT STD_LOGIC;
    txdata : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    enablealign : OUT STD_LOGIC;
    gmii_txd : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    gmii_tx_en : IN STD_LOGIC;
    gmii_tx_er : IN STD_LOGIC;
    gmii_rxd : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    gmii_rx_dv : OUT STD_LOGIC;
    gmii_rx_er : OUT STD_LOGIC;
    gmii_isolate : OUT STD_LOGIC;
    configuration_vector : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    status_vector : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : gig_eth_pcs_pma_v11_5
  PORT MAP (
    reset => reset,
    signal_detect => signal_detect,
    mgt_rx_reset => mgt_rx_reset,
    mgt_tx_reset => mgt_tx_reset,
    userclk => userclk,
    userclk2 => userclk2,
    dcm_locked => dcm_locked,
    rxbufstatus => rxbufstatus,
    rxchariscomma => rxchariscomma,
    rxcharisk => rxcharisk,
    rxclkcorcnt => rxclkcorcnt,
    rxdata => rxdata,
    rxdisperr => rxdisperr,
    rxnotintable => rxnotintable,
    rxrundisp => rxrundisp,
    txbuferr => txbuferr,
    powerdown => powerdown,
    txchardispmode => txchardispmode,
    txchardispval => txchardispval,
    txcharisk => txcharisk,
    txdata => txdata,
    enablealign => enablealign,
    gmii_txd => gmii_txd,
    gmii_tx_en => gmii_tx_en,
    gmii_tx_er => gmii_tx_er,
    gmii_rxd => gmii_rxd,
    gmii_rx_dv => gmii_rx_dv,
    gmii_rx_er => gmii_rx_er,
    gmii_isolate => gmii_isolate,
    configuration_vector => configuration_vector,
    status_vector => status_vector
  );
-- INST_TAG_END ------ End INSTANTIATION Template ------------

-- You must compile the wrapper file gig_eth_pcs_pma_v11_5.vhd when simulating
-- the core, gig_eth_pcs_pma_v11_5. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

