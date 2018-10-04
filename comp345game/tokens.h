#pragma once
#ifndef TOKENS_H
#define TOKENS_H

class Tokens {
	private:
		int web = 13;
		int jinx = 13;
		int souvenir = 5;
		int carapace = 15;

	public:
		Tokens(){};
		int getWeb() { return web; };
		int getJinx() { return jinx; };
		int getSouvenir() { return souvenir; };
		int getCarapace() { return carapace; };

		// The mutators change the value of the variables by n
		int setWeb(int n);
		int setJinx(int n);
		int setSouvenir(int n);
		int setCarapace(int n);
};

#endif