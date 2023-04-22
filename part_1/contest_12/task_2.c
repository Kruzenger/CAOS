#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct Request {
  char query_name[4096];
  char script_path[4096];
  char script_name[4096];
  char host[4096];
  char query_string[4096];
};

int CountCharInBuffer(char* buffer, char symbol) {
  int counter = 0;
  for (int i = 0; i < strlen(buffer); ++i) {
    if (buffer[i] == symbol) {
      ++counter;
    }
  }

  return counter;
}

char* ConstructListPart(char* target, char* value) {
  char* part =
      (char*)malloc(sizeof(char) * (strlen(target) + strlen(value) + 2));
  snprintf(part, strlen(target) + strlen(value) + 2, "%s=%s", target, value);
  return part;
}

void ProcessQuery(struct Request* request) {
  char** list = (char**)malloc(sizeof(char*) * 5);
  list[0] = ConstructListPart("HTTP_HOST", request->host);
  list[1] = ConstructListPart("REQUEST_METHOD", request->query_name);
  list[2] = ConstructListPart("QUERY_STRING", request->query_string);
  list[3] = ConstructListPart("SCRIPT_NAME", request->script_name);
  list[4] = NULL;

  int file = open(request->script_path, O_RDONLY);
  if (file == -1) {
    printf("HTTP/1.1 404 ERROR\n\n");
    return;
  }

  struct stat status;
  fstat(file, &status);
  if (!(status.st_mode & S_IXUSR)) {
    printf("HTTP/1.1 403 ERROR\n\n");
    return;
  }

  printf("HTTP/1.1 200 OK\n");
  fflush(stdout);
  execve(request->script_path, NULL, list);
}

int main() {
  char input[8192];
  memset(input, '\0', 8192);
  size_t i = 0;
  while ((scanf("%c", input + i)) != EOF) {
    ++i;
  }

  struct Request request;

  size_t start_pos = 0;

  char* end_part_symbol;
  end_part_symbol = strchr(input + start_pos, ' ');
  memcpy(request.query_name, input + start_pos,
         end_part_symbol - (input + start_pos));

  request.query_name[end_part_symbol - (input + start_pos)] = '\0';
  start_pos = end_part_symbol - input + 1;

  request.script_path[0] = '.';
  request.script_path[1] = '/';
  end_part_symbol = strchr(input + start_pos, '?');
  if (end_part_symbol == NULL) {
    end_part_symbol = strchr(input + start_pos, ' ');
  }
  memcpy(request.script_path + 2, input + start_pos,
         end_part_symbol - (input + start_pos));

  if (request.script_path[1] == request.script_path[2]) {
    memcpy(request.script_path + 1, request.script_path + 2,
           end_part_symbol - (input + start_pos));
    request.script_path[end_part_symbol - (input + start_pos) + 1] = '\0';
  } else {
    request.script_path[end_part_symbol - (input + start_pos) + 2] = '\0';
  }
  start_pos = end_part_symbol - input + 1;

  memcpy(request.script_name, request.script_path,
         strlen(request.script_path) + 1);

  int argc = CountCharInBuffer(input, '=');
  request.query_string[0] = '\0';

  if (argc > 0) {
    end_part_symbol = strchr(input + start_pos, ' ');
    memcpy(request.query_string, input + start_pos,
           end_part_symbol - (input + start_pos));
    request.query_string[end_part_symbol - (input + start_pos)] = '\0';
  }

  end_part_symbol = strstr(input + start_pos, "Host:");
  start_pos = (end_part_symbol - input) + 6;
  end_part_symbol = strchr(input + start_pos, '\n');
  memcpy(request.host, input + start_pos,
         end_part_symbol - (input + start_pos));
  request.host[end_part_symbol - (input + start_pos)] = '\0';

  ProcessQuery(&request);

  return 0;
}