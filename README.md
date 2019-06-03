# VirtualMachine
Virtual machine, which decrypts an encrypted quote. Project done for Architecture of Computers and Computer Networks course in 2nd year of university.

The task of the project was:

"Using programming language of your choice make a virtual machine that: 
• has 16 registers R0-R15 (8 bits wide); 
• has PC (program counter) register that points to the currently executed instruction. 
After execution it has to increase by 2. 
In case of jump instructions, jump bytes (displacement address) is added to PC, 
thus virtual machine performs jump to different address; 
• has 8 bit addressing mode: it addresses program memory at byte level; 
• has 256 byte program memory; 
• has flag register for holding 1 bit of data – EOF mark for IN command.

The task includes two files: 
• decryptor.bin, which contains binary program for execution; 
• q1_encr.txt – encrypted file that machine reads byte by byte when it executes IN command. 

Task is considered as completed when machine reads input and by executing given program performs input decryption 
and outputs English text – a sentence of known scientist. 
