# include "lecture.h"
# define TAILLE_MAX 1000

int main(int argc, char *argv[])
{
	/*
	 * modes:
	 *	0 : bin
	 *	1 : 94c
	 */
	char *mode = "94c";
	if (argc == 2)
		mode = argv[1]; //atoi()

	size_t count = 0;
	printf("load: %s, %zu\n", mode, count++);
	s_network *container = load_RDN_from_path("../saved_RDN_LBIW.txt");
	printf("read: %s, %zu\n", mode, count++);
	read_RDN(container, mode);
	//save();
	/*
	double inputs[2] = {0 ,1};
	eval(inputs);
	size_t pos = find(network);
	printf("%lf\n", network[pos] -> val);
	*/
	return 0;
}
