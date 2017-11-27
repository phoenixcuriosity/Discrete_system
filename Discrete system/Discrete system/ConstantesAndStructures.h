#ifndef ConstantesAndStructures_H
#define ConstantesAndStructures_H




typedef struct screen screen;
struct screen {
	unsigned int a;
};
typedef struct fichier fichier;
struct fichier {
	const std::string log = "bin/log/log.txt";
	const std::string save = "bin/SaveAndLoad/save.txt";
	const std::string load = "bin/SaveAndLoad/load.txt";
};
typedef struct var var;
struct var {
	unsigned int a;
};



typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	fichier file;
	var variable;
};


#endif