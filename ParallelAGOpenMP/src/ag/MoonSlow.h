/*
 * MoonSlow.h
 *
 *  Created on: Oct 7, 2016
 *      Author: reginaldo
 */

#ifndef AG_MOONSLOW_H_
#define AG_MOONSLOW_H_

class Population;
class Chromosome;

class MoonSlow {
private:
	Population *p;
	Population *selected;
	int functionID;

	static bool compare(Chromosome *, Chromosome *);

public:
	MoonSlow(const int);
	virtual ~MoonSlow();

	void initializePopulation();
	void calculateFitness(Population *);
	Population *parentSelection(Population *);
	Population *crossover(Population *);
	void mutation(Population *);
	Population *survivorSelection(Population *, Population *);
	Population *run();
};

#endif /* AG_MOONSLOW_H_ */
