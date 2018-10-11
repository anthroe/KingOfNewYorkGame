#include "tokens.h"

int Tokens::setWeb(int n) {
	// Ensure that the count stays positive and within maximum
	if (web + n > 13 || web + n < 0)
		return false;
	else
		web += n;

	return true;
}

int Tokens::setJinx(int n) {
	// Ensure that the count stays positive and within maximum
	if (jinx + n > 13 || jinx + n < 0)
		return false;
	else
		jinx += n;

	return true;
}

int Tokens::setSouvenir(int n) {
	// Ensure that the count stays positive and within maximum
	if (souvenir + n > 5 || souvenir + n < 0)
		return false;
	else
		souvenir += n;

	return true;
}

int Tokens::setCarapace(int n) {
	// Ensure that the count stays positive and within maximum
	if (carapace + n > 15 || carapace + n < 0)
		return false;
	else
		carapace += n;

	return true;
}