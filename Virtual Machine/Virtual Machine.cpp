// Virtual Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	unsigned char regs[16]; // the char type is actually an 8-bit integer - exactly the size of a single byte
	char prog_mem[256];
	FILE* fp = fopen("decryptor.bin", "rb");
	if (fp == NULL)
	{
		printf("Can not open the file\n");
		exit(1);
	}
	for (int i(0); i < sizeof(prog_mem); i++)
	{
		fread(prog_mem + i, 1, 1, fp);
		if (feof(fp))
			break;
	}
	
	fclose(fp);
	FILE* fdata;
	fdata = fopen("q1_encr.txt", "rb");
	if (fdata == NULL)
	{
		printf("Cannot open file\n");
		exit(1);
	}

	// Notes: 
	// Reg1 in comments refers to least significant bits 0,1,2,3 ; 
	// Reg2 refers to most significant bits 4,5,6,7 ; 
	// bits in a byte go in such order: 7,6,5,4,3,2,1,0

	int r_pc = 0, end = 0, flag = 0;
	while (end == 0) 
	{
		char symbol = prog_mem[r_pc];
	
		switch (symbol) {
			case 0x04:
					r_pc++;
					regs[0] = prog_mem[r_pc];
					r_pc++;
				break;

			case 0x05:
					r_pc++;
					regs[prog_mem[r_pc]] = regs[prog_mem[r_pc]] * 2;
					//cout << "r_pc: " << r_pc << " regs[prog_mem[r_pc]]: " << regs[prog_mem[r_pc]] << endl;
					r_pc++;
				break;

			case 0x07: r_pc = (r_pc + prog_mem[r_pc + 1]);
				break;

			case 0x0a:
					if (flag == 1)
						r_pc = (r_pc + prog_mem[r_pc + 1]);
					else r_pc = r_pc + 2;
				break;

			case 0x0b:
					end = 1;
					cout << endl;
					cout << "The End" << endl;
				break;

			case 0x0d: 
					r_pc++;
					regs[prog_mem[r_pc] & 0xF] = (regs[prog_mem[r_pc] & 0xF] - regs[prog_mem[r_pc] / 16]);
					r_pc++;
				break;

			case 0x0e: // Reg1 = Reg1 XOR Reg2
					r_pc++;
					regs[prog_mem[r_pc] & 0xF] = (regs[prog_mem[r_pc] & 0xF] ^ regs[prog_mem[r_pc] / 16]);
					r_pc++;
				break;

			case 0x0f:
					r_pc++;
					regs[prog_mem[r_pc] & 0xF] = (regs[prog_mem[r_pc] & 0xF] | regs[prog_mem[r_pc] / 16]);
					r_pc++;
				break;

			case 0x10:
					r_pc++;
					fread(&regs[prog_mem[r_pc]], 1, 1, fdata);
					if (feof(fdata))
						flag = 1;
					else flag = 0;
					r_pc++;
				break;

			case 0x11:
					r_pc++;
					cout << regs[prog_mem[r_pc]];
					r_pc++;
				break;
		}
	}
	fclose(fdata);
	

	return 0;
}

