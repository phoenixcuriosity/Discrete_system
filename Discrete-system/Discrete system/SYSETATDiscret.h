#ifndef SYSETATDiscret_H
#define SYSETATDiscret_H

#include "LIB.h"
#include "Matrice.h"
#include "FCTDiscret.h"
#include "Signal.h"


class SYSETATDiscret{
public:
	SYSETATDiscret();
	SYSETATDiscret(const SYSETATDiscret&);
	~SYSETATDiscret();

	friend std::ostream& operator<<(std::ostream&, const SYSETATDiscret&);

	void SETA(const Matrice&);
	void SETB(const Matrice&);
	void SETC(const Matrice&);
	void SETD(const Matrice&);
	void SETdeltaT(double);
	void SETeditSizeA(unsigned int, unsigned int);
	void SETeditSizeB(unsigned int, unsigned int);
	void SETeditSizeC(unsigned int, unsigned int);
	void SETeditSizeD(unsigned int, unsigned int);
	void SETthisCoefA(unsigned int, unsigned int, double);
	void SETthisCoefB(unsigned int, unsigned int, double);
	void SETthisCoefC(unsigned int, unsigned int, double);
	void SETthisCoefD(unsigned int, unsigned int, double);
	Matrice GETA()const;
	Matrice GETB()const;
	Matrice GETC()const;
	Matrice GETD()const;
	double GETdeltaT()const;
	

	void calculABCD(const FCTDiscret&);
	void simulation();

	std::string printOn(bool on = true)const;


private:
	Matrice _A, _B, _C, _D;
	double _deltaT;
};

#endif // !SYSETATDiscret_H
