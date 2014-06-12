#include <stdio.h>
#include <string.h>
#define MAX_PATH 260

typedef unsigned long u32;

int main()
{
	FILE *pbmp = NULL, *pc = NULL;
	u32 c = 0;
	long width, height;
	long start;
	char input_filename[MAX_PATH], file_bmp[MAX_PATH], file_c[MAX_PATH];
	
	printf("输入BITMAP文件名，不含扩展名:\n");
	
	while (EOF != scanf("%s", input_filename))
	{	
		strcpy(file_bmp, input_filename);
		strcat(file_bmp, ".bmp");
		strcpy(file_c, input_filename);
		strcat(file_c, ".c");
		
		pbmp = fopen(file_bmp, "rb");
        if (pbmp == NULL)
        {
            printf("%s不存在!\n", file_bmp);
            continue;;
        }

		pc = fopen(file_c, "wt");

		
		fprintf(pc, "unsigned long bmp[] = \n{\n");
		
		fseek(pbmp, 10, SEEK_SET);
		fread(&start, 4, 1, pbmp);
		fseek(pbmp, 18, SEEK_SET);
		fread(&width, 4, 1, pbmp);
		fread(&height, 4, 1, pbmp);
		
		for(long h = height; h >= 1; h--)
		{
			fseek(pbmp, start, SEEK_SET);
			fseek(pbmp, 3 * width * h, SEEK_CUR);
			fprintf(pc, "\t");
			for(long w = 1; w <= width; w++)
			{
				fread(&c, 3, 1, pbmp);
				fprintf(pc, "0x%.6x,", c);
			}
			fprintf(pc, "\n");
		}	
		
		fseek(pc, -3, SEEK_CUR);
		fprintf(pc, "\n};\n");
		
		fclose(pc);
		fclose(pbmp);
		
		printf("%s convert successed.\n", file_c);	
	}

	return 0;
}