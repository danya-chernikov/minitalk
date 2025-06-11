#include <signal.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	psignal(1, "kekeke");

	char *sig_name = strsignal(15);
	printf("%s\n", sig_name);

	sig_name = strsignal(9);
	printf("%s\n", sig_name);

	return 0;
}
