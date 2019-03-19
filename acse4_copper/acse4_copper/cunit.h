#pragma once
#include "header.h"

class cunit {
public:
	int out_conc;
	int out_tail;
	bool conc_mark = false;
	bool tail_mark = false;
	bool source_mark = false;

	void mark(cunit* units);
};
