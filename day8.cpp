#include <vector>
#include <string>
#include <fstream>
#include <iostream>

enum class IType {
	acc,
	jmp,
	nop
};

struct Instruction {
	IType type{};
	int argument;
	bool already_executed = false;
};

enum Status : uint32_t {
	Ok = 0x00,
	IpOutOfRange = 0x01,
	DuplicateInstruction = 0x02
};

class Program {
public:
	std::vector<Instruction> instructions;
	int ip = 0;
	int acc = 0;
	uint32_t status = Status::Ok;

	Program(std::vector<Instruction> instructions) : instructions(instructions) {
		
	}

	void exec_cur() {
		Instruction& i = instructions[ip];
		if (i.already_executed) {
			status |= Status::DuplicateInstruction; 
			return;
		}
		if (ip < 0 || ip > instructions.size()) {
			status |= Status::IpOutOfRange;
			return;
		}

		switch (i.type) {
		case IType::nop:
			++ip; break;
		case IType::jmp:
			ip += i.argument; break;
		case IType::acc:
			acc += i.argument; ++ip; break;
		}
		i.already_executed = true;
	}

	Instruction const& cur() {
		return instructions[ip];
	}

	bool has_ended() {
		return ip < 0 || ip >= instructions.size();
	}

	bool normal_termination() {
		return ip == instructions.size();
	}

	void reset() {
		for (auto& instr : instructions) {
			instr.already_executed = false;
		}
		ip = 0;
		acc = 0;
		status = 0;
	}
};

int part1(Program& program) {
	while (!program.has_ended()) {
		// Check if current instruction is duplicated
		if (program.cur().already_executed) {
			return program.acc;
		}

		program.exec_cur();
	}
}

int part2(Program& program) {
	for (int i = 0; i < program.instructions.size(); ++i) {
		// Switch instruction from nop to jmp or other way around
		if (program.instructions[i].type == IType::acc) continue;
		IType new_instruction = (program.instructions[i].type == IType::nop ? IType::jmp : IType::nop);
		program.instructions[i].type = new_instruction;
		while (!program.has_ended()) {
			program.exec_cur();
			if (program.status != Status::Ok) break;
			if (program.normal_termination()) {
				return program.acc;
			}
		}
		// Reset
		program.reset();
		program.instructions[i].type = (new_instruction == IType::nop ? IType::jmp : IType::nop);
	}
	return -1;
}

int main() {
	std::ifstream file("input/day8.txt");
	std::string itype;
	int arg = 0;
	std::vector<Instruction> instructions;
	while (file >> itype >> arg) {
		IType type;
		if (itype == "acc") type = IType::acc;
		if (itype == "jmp") type = IType::jmp;
		if (itype == "nop") type = IType::nop;
		instructions.push_back(Instruction{ .type = type, .argument = arg, .already_executed = false });
	}
	Program prog(std::move(instructions));

	std::cout << "Answer to part 1: " << part1(prog) << "\n";
	prog.reset();
	std::cout << "Answer to part 2: " << part2(prog) << "\n";
}