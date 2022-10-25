# Lab1 report

## Spike model and co-sim

### Spike model (with risc-v pk) execution correctness
![](./images/spike-dhrystone.png)
![](./images/spike-pk.png)
### GreenRio core RTL execution correctness
The verification environment is located at **./verilog/dv**.
1. Convert the orignal elf file into hex file to facilitate magic memory to read it.
2. Instanse GreenRIos and magic memory in hehe_tb.sv, connecting them and giving rst and clk signal to motivate them.
3. Use HTIF to detect whether the program executes successfully.
![](./images/vcs-simulation.png)

### Spike model + GreenRio RTL co-simulation system
1. Use spike to print the log
![](./images/spike-log.png)
2. Use DPI to embed probe into core and print executing log, which is stored in **./verilog/dv/greenrio_log.txt**.
![](./images/hehe-log.png)
### Open EDA flow
1. SKY130A synthesis
    **./backend_log/RUN_1** records the GreenRio synthesis flow under <u>sky130_fd_sc_hd__ff_100C_1v65.lib</u> corner.  
    