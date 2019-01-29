#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include "input.h"

static void repl();
static void run_file(const char *path);
static char* read_file(const char *path);

VM vm;

int main(int argc, const char* argv[]) {
   init_vm(&vm);

   if (argc == 1) {
      repl();
   } else if (argc == 2) {
      run_file(argv[1]);
   } else {
      fprintf(stderr, "Usage: qed [path]\n");
      exit(64);
   }
   
   free_vm(&vm);
   return 0;
}

static void repl() {
   for (;;) {
      char *line = readline("> ");
      interpret(&vm, line);
      add_history(line);
      free(line);
   }
}

static void run_file(const char *path) {
   char *source = read_file(path);
   InterpretResult result = interpret(&vm, source);
   free(source);

   if (result == INTERPRET_COMPILE_ERROR) exit(65);
   if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static char* read_file(const char *path) {
   FILE *file = fopen(path, "rb");
   if (file == NULL) {
      fprintf(stderr, "Could not open file \"%s\"\n", path);
      exit(74);
   }
   
   // determine file size
   fseek(file, 0L, SEEK_END);
   size_t file_size = ftell(file);
   rewind(file);

   char *buffer = (char*)malloc(file_size + 1);
   if (buffer == NULL) {
      fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
   }

   size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
   if (bytes_read < file_size) {
      fprintf(stderr, "Could not read file \"%s\"\n", path);
   }

   buffer[bytes_read] = '\0';

   fclose(file);
   return buffer;
}