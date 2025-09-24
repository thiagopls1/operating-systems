#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  FILE *file_pointer = NULL;
  char buffer[512];
  int file_size;

  // Abre o arquivo
  file_pointer = fopen("mbr.bin", "r");
  // Se deu erro ao abrir, retorna
  if (file_pointer == NULL) {
    printf("Erro ao abrir o arquivo: %i", errno);
    return 1;
  }
  // Vai até o fim do arquivo
  fseek(file_pointer, 0L, SEEK_END);
  // Pega o índice do ponteiro
  file_size = ftell(file_pointer);
  printf("O tamanho do arquivo é de %i bytes\n", file_size);

  // Volta pro começo do arquivo
  fseek(file_pointer, 0, SEEK_SET);
  // Lê o arquivo com o tamanho do buffer
  fread(buffer, sizeof buffer, 1, file_pointer);

  // 446 até o 509 é a partition table:
  // https://thestarman.pcministry.com/asm/mbr/PartTables.htm
  printf("Bytes das partições:\n");
  int start = 446;
  int end = 509;
  int partitions_count = (end - start + 1) / 16;
  printf("Qtd de partições selecionadas: %d\n", partitions_count);
  int indexes_to_read = 0;
  for (int i = 0; i < partitions_count; i++) {
    printf("Partição %d: ", i + 1);
    for (int j = start + indexes_to_read; j < start + indexes_to_read + 16;
         j++) {
      printf("%x ", buffer[j]);
    }
    indexes_to_read += 16;
    printf("\n");
  }
  // for (int i = start; i <= end; i++) {
  //   printf("%x ", buffer[i]);
  // }

  // Fecha o arquivo
  fclose(file_pointer);
  return 0;
}
