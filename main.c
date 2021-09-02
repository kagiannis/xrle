#include <stdio.h>
#include <stdlib.h>
#include "xrle.h"

void *read_file(const char *file, size_t *sz)
{
	FILE *f;
	void *ret = NULL;
       
	f = fopen(file, "rb");
	if(f == NULL)
		goto out;

	fseek(f, 0, SEEK_END);
	*sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	ret = malloc(*sz);
	if(ret != NULL)
		fread(ret, 1, *sz, f);

	fclose(f);

out:
	return ret;
}


int main(int argc, char *argv[])
{
	const char *file;
	char *in, *out;
	size_t insz, outsz;

	if(argc != 3 || argv[1][0] != '-')
	{
		fprintf(stderr, "Usage: xrle [-c|-d] file > out\n");
		return 1;
	}

	if(argv[1][1] != 'c' && argv[1][1] != 'd')
	{
		fprintf(stderr, "Unknown option '%s'\n", argv[1]);
		return 1;
	}

	file = argv[2];
	in = read_file(file, &insz);
	if(in == NULL)
	{
		fprintf(stderr, "An error occured\n");
		return 1;
	}

	if(argv[1][1] == 'c')
	{
		out = malloc(xrle_max_out(insz));
		if(out == NULL)
		{
			fprintf(stderr, "Unable to allocate memory\n");
			return 1;
		}

		outsz = xrle_compress(out, in, insz);
		for(size_t i = 0; i < outsz; i++)
			putc(out[i], stdout);

		fflush(stdout);
		free(out);

	}
	else
	{
		outsz = xrle_getsz(in);
		out = malloc(outsz + 8);
		if(out == NULL)
		{
			fprintf(stderr, "Unable to allocate %lu bytes of memory\n", outsz);
			return 1;
		}

		outsz = xrle_decompress(out, in, insz);
		for(size_t i = 0; i < outsz; i++)
			putc(out[i], stdout);

		fflush(stdout);
		free(out);

	}

	fprintf(stderr, "%lu --> %lu, %f%%\n", insz, outsz, ((float)outsz/(float)insz)*100.0f);
	free(in);

	return 0;
}
