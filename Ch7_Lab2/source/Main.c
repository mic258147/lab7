#include <stdlib.h>
#include<stdio.h>

struct clientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
};
int main()
{
	errno_t err1;
	errno_t err2;
	errno_t err3;
	FILE *pRead, *pWrite;
	FILE *cfPtr;
	int cnt = 0;
	struct clientData client = { 0,"","",0.0 };
	
	err1 = fopen_s(&pRead, "C://Users/User/Desktop/c_code/credit.txt", "r");
	if (err1 != 0)
	{
		return 0;
	}
	err2 = fopen_s(&pWrite, "C://Users/User/Desktop/c_code/credit_bin.txt", "wb");
	if (err2 != 0)
	{
		fclose(pRead);
		return 0;
	}
	while (!feof(pRead))
	{
		
		fscanf_s(pRead, "%d", &client.acctNum, sizeof(int));
		fscanf_s(pRead, "%s", &client.lastName, 10*sizeof(char));
		fscanf_s(pRead, "%s", &client.firstName, 10*sizeof(char));
		fscanf_s(pRead, "%lf", &client.balance, sizeof(float));
		fwrite(&client, sizeof(struct clientData), 1, pWrite);
		printf("%-6d%-16s%-11s%10.2f\n", client.acctNum,
			client.lastName, client.firstName, client.balance);
	}
	fclose(pRead);
	fclose(pWrite);
	printf("已讀取文字檔的ASCII資料，並轉存成二進位資料檔案\n\n");
	system("pause");
	printf("\n讀取二進位資料檔案，並格式化輸出如下: \n");
	err3 = fopen_s(&cfPtr, "C://Users/User/Desktop/c_code/credit_bin.txt", "rb");
	if (err3 != 0)
	{
		printf("File could not be opened.\n");
	}
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");
		cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		while (cnt > 0)
		{
			printf("%-6d%-16s%-11s%10.2f\n", client.acctNum,
				client.lastName, client.firstName, client.balance);
			cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		}
		fclose(cfPtr);	
	}
	system("pause");
	return 0;
}