#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Struct para separar os valores
struct partition {
  bool is_boot;
  char start_chs_bytes[3];
  char partition_type_byte;
  char end_chs_bytes[3];
  char start_sector_bytes[4];
  char partition_size_bytes[4];
};

int main() {
  FILE *file_pointer = NULL;
  char buffer[512];
  int file_size;
  struct partition partitions[4];

  // Abre o arquivo
  file_pointer = fopen("./data/mbr.bin", "r");
  // Se deu erro ao abrir, retorna
  if (file_pointer == NULL) {
    printf("Erro ao abrir o arquivo: %i\n", errno);
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

  // 446 até o 509 é a tabela de partições
  // ref.: https://thestarman.pcministry.com/asm/mbr/PartTables.htm
  printf("Bytes das partições:\n");
  int start_index = 446;
  int end_index = 509;
  int partitions_count = (end_index - start_index + 1) / 16;
  printf("Qtd de partições selecionadas: %d\n", partitions_count);
  int indexes_to_read = 0;
  for (int i = 0; i < partitions_count; i++) {
    printf("Partição %d: ", i + 1);
    int start_point = start_index + indexes_to_read;
    for (int j = start_point; j < start_point + 16; j++) {
      // i_byte sempre será entre 0 e 15 (16 bytes)
      int i_byte = j - start_point;
      char current_buffer = buffer[j];
      printf("%hhx ", current_buffer);

      // Partição bootável
      if (j == start_point)
        partitions[i].is_boot = current_buffer == *"\x80";

      // CHS incial
      if (i_byte >= 1 && i_byte <= 3)
        partitions[i].start_chs_bytes[i_byte - 1] = current_buffer;

      // Tipo de partição
      if (i_byte == 4)
        partitions[i].partition_type_byte = current_buffer;

      // CHS final
      if (i_byte >= 5 && i_byte <= 7)
        partitions[i].end_chs_bytes[i_byte - 5] = current_buffer;

      // Setor inicial
      if (i_byte >= 8 && i_byte <= 11)
        partitions[i].start_sector_bytes[i_byte - 8] = current_buffer;

      // Tamanho da partição
      if (i_byte >= 12 && i_byte <= 15)
        partitions[i].partition_size_bytes[i_byte - 12] = current_buffer;
    }

    indexes_to_read += 16;
    printf("\n");
  }

  // Fecha o arquivo
  fclose(file_pointer);
  return 0;
}

// 11414
