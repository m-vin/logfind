#include <stdio.h>
#include <string.h>

int mostraRegistro(char* registro){
	printf("%s\n", registro);
	return 0;
}

void leArquivo(char* nome, char* argv){
	int linha = 1;
	FILE *fp = NULL;
	char* arquivo = nome;
	char ch = '\0';
	char padrao[255] = "";
	int i = 0;

	fp = fopen(arquivo, "r");

	printf("----------------------------------------------------\n");
	printf("registro encontrado: %s\n", arquivo);

	/* -------------------- PROCURA ARGV NO ARQUIVO */
	if (fp == NULL){
		/* o arquivo não existe */
		printf("ERRO: arquivo %s não existe...\n", arquivo);
	}
	else{
		/* o arquivo existe */
		printf("padrões encontrados:\n");
		
		/* lê o arquivo até o final */
		while ((ch = getc(fp)) != EOF){
		/* procura argv no arquivo */
			if (ch == argv[i]){
				padrao[i] = ch;
				if (strcmp(padrao, argv) == 0){
					mostraRegistro(padrao);
					for (i = 0; i < 255; i++){
						padrao[i] = '\0';
					}
					i = 0;
				}
				else {
					i++;
				}
			}
			else {
				i = 0;
			}
		}
		for (i = 0; i <= 254; i++){
			padrao[i] = 0;
		}
	}

	/* ---------- MOSTRA O CONTEUDO DO ARQUIVO */ 
	printf("\nconteudo do arquivo %s: \n\n", arquivo);
	rewind(fp);
	if (fp == NULL){
		printf("ERRO: arquivo %s não existe...\n", arquivo);
	}
	else{
		printf("%d ", linha);
		while ((ch = getc(fp)) != EOF){
			putc(ch, stdout);
			if (ch == '\n'){
				linha++;
				printf("%d ", linha);
			}
		}
	}
	printf("\n");
}

int procuraArquivos(char* caminho, char* argv){
	FILE *fp;

	char* arquivo = caminho;
	char ch;
	char nome[200];
	int i = 0;

	fp = fopen(arquivo, "r");
	
	if (fp == NULL){
		printf("ERRO: arquivo .logfind não existe...\n");
	}
	else{
		while ((ch = getc(fp)) != EOF){
			if (ch != '\n'){
				nome[i] = ch;
				i++;
			}
			else{
				leArquivo(nome, argv);
				i = 0;
			}
		}
	}
	return 0;
}

int main(int argc, char* argv[]){
	int i = 1;

	if (argc < 3){
		printf("logfind <diretorio-com-logfind> <word>\n");
	}
	else{
		while(i < argc){
			printf("logfind - %s...\n", argv[i]);
			procuraArquivos(argv[1], argv[i]);
			i++;
		}
	}
	return 0;
}
