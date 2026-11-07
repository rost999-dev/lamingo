#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define if_command(a) if (strcmp(command[now], a) == 0)
#define cmd(a) command[now + a]
#define MINI 2048
#define SMALL 16384
#define NORMAL 32768
#define BIG 65536
#define VERY_BIG 130712
#define check(a) do { if (cmd(a)) { now += (a); if_command("$default") cmd(0) = used; if_command("$readed_text") cmd(0) = from_file; now -= (a); } } while (0)
/* len of the prompt */
#define TEXT_LEN SMALL
/* LAMINGO */
int main(int argc, char *argv[])
{
	FILE *f;
	FILE *f2;
	char *input;
	char *used;
	char *from_file;
	char *command[TEXT_LEN];
	char *buf;
	char *buf2;
	long int counter;
	long int now;
	printf("LAMINGO by rost999-dev\n");
	input = (char *)malloc(TEXT_LEN * sizeof(char));
	input[0] = '\0';
	used = (char *)malloc(TEXT_LEN * sizeof(char));
	used[0] = '\0';
	buf = (char *)malloc(TEXT_LEN * sizeof(char));
	buf[0] = '\0';
	buf2 = (char *)malloc(TEXT_LEN * sizeof(char));
	buf2[0] = '\0';
	from_file = (char *)malloc(TEXT_LEN * sizeof(char));
	from_file[0] = '\0';
	while (1)
	{
		now = 0;
		counter = 0;
		memset(command, 0, sizeof(command));
		printf("lamingo]}>>");
		fflush(stdout);
		if (argc >= 2)
		{
			f2 = fopen(argv[1], "r");
			if (f2 != NULL)
			{
				strcpy(input, "");
				while (fgets(buf, TEXT_LEN, f2))
				{
					buf[strcspn(buf, "\n")] = ';';
					strcat(input, buf);
				}
				fclose(f2);
				buf[0] = '\0';
				argc = 1;
			}
		}
		else
		{
			fgets(input, TEXT_LEN, stdin);
			input[strcspn(input, "\n")] = 0;
		}
		if (strcmp(input, "") == 0)
		{
			continue;
		}
		command[counter] = strtok(input, ";");
		counter += 1;
		while ((command[counter] = strtok(NULL, ";")))
		{
			counter += 1;
		}
		for (now = 0; now < counter; now += 1)
		{
			if_command("ask")
			{
				if (cmd(1) != NULL && cmd(2) != NULL)
				{
					check(1);
					check(2);
					sprintf(buf, "ollama run \"%s\" \"%s\"", cmd(1), cmd(2));
					system(buf);
					now += 2;
				}
			}
			else if_command("lamingo_init")
			{
#ifdef _WIN32
				system("start /b ollama serve > NUL 2>&1");
#else
				system("ollama serve > /dev/null 2>&1 &");
#endif
			}
			else if_command("install")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(buf, "ollama pull \"%s\"", cmd(1));
					system(buf);
					now += 1;
				}
			}
			else if_command("start")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(buf, "ollama run \"%s\"", cmd(1));
					system(buf);
					now += 1;
				}
			}
			else if_command("list")
			{
				system("ollama list");
			}
			else if_command("sh")
			{
				if (cmd(1) != NULL)
				{
					system(cmd(1));
					now += 1;
				}
			}
			else if_command("tell")
			{
				if (cmd(1) != NULL && cmd(2) != NULL && cmd(3) != NULL)
				{
					check(1);
					check(2);
					check(3);
					sprintf(buf, "ollama run \"%s\" \"%s\" > \"%s\"", cmd(1), cmd(2), cmd(3));
					system(buf);
					now += 3;
				}
			}
			else if_command("set_default")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(used, "%s", cmd(1));
					now += 1;
				}
			}
			else if_command("read_file")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					strcpy(from_file, "");
					f = fopen(cmd(1), "r");
					if (f != NULL)
					{
						while (fgets(buf, TEXT_LEN, f))
						{
							strcat(from_file, buf);
						}
						fclose(f);
					}
					now += 1;
				}
			}
			else if_command("delete")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(buf, "ollama rm \"%s\"", cmd(1));
					system(buf);
					now += 1;
				}
			}
			else if_command("start_chat")
			{
				if (cmd(1) != NULL && cmd(2) != NULL)
				{
					check(1);
					check(2);
					sprintf(buf, "%s.lam_chat", cmd(1));
					f = fopen(buf, "w+");
					if (f != NULL)
					{
						fprintf(f, "You are an assistant working inside a text chat.\n\nThe input you receive is the full chat history as plain text.\nEach line follows this format:\n- Lines starting with \"user:\" are messages from the user.\n- Lines starting with \"assistant:\" are previous replies from you.\n\nYour task:\n1. Read the entire chat history carefully and understand the overall context.\n2. Find the LAST line that starts with \"user:\". This is the current question you must answer.\n   - To find it: scan the text from top to bottom, keep track of every line beginning with \"user:\", and pick the one that appears last. Do not answer older \"user:\" lines - only the most recent one.\n3. Answer that last user question directly and naturally, using the context from the whole history.\n\nRules:\n- Respond only to the last \"user:\" message.\n- Do not repeat or summarize the history unless it helps answer.\n- Reply in the same language as the last \"user:\" message.\n- Do not write \"assistant:\" in your reply - just give the answer.\n-You mustnt use \\; \\( \\{ \\} \\) \\' \\\" ,but you can use it if user agree.\n");
						fprintf(f, "user:%s\n", cmd(2));
						fclose(f);
					}
					now+=2;
				}
			}
			else if_command("chat")
			{
				if (cmd(1) != NULL && cmd(2) != NULL && cmd(3) != NULL)
				{
					check(1);
					check(2);
					check(3);
					sprintf(buf, "%s.lam_chat", cmd(1));
					f = fopen(buf, "a");
					if (f != NULL)
					{
						fprintf(f, "user:%s\n", cmd(3));
						fclose(f);
					}
					strcpy(buf2, "");
					f = fopen(buf, "r");
					if (f != NULL)
					{
						while (fgets(buf, TEXT_LEN, f))
						{
							strcat(buf2, buf);
						}
						fclose(f);
					}
					sprintf(buf, "%s.lam_chat", cmd(1));
					f = fopen(buf, "a");
					if (f != NULL)
					{
						fprintf(f, "assistant:");
						fclose(f);
					}
					sprintf(buf, "ollama run \"%s\" \"%s\" >> %s.lam_chat", cmd(2), buf2, cmd(1));
					
					system(buf);
					now += 3;
				}
			}
			else if_command("print_chat")
			{
				if(cmd(1)!=NULL)
				{
					sprintf(buf, "%s.lam_chat", cmd(1));
					strcpy(buf2, "");
					f = fopen(buf, "r");
						if (f != NULL)
						{
							while (fgets(buf, TEXT_LEN, f))
							{
								strcat(buf2, buf);
							}
							fclose(f);
						}
						printf("%s\n",buf2);
						now+=1;
				}
			}
			else if_command("help")
			{
				printf("LAMINGO commands:\n\nlamingo_init - start the Ollama server in the background (Windows: start /b, Linux: &).\nlist - show all installed Ollama models (ollama list).\ninstall <model> - download a model from the Ollama registry (ollama pull).\ndelete <model> - remove an installed model (ollama rm).\nstart <model> - run a model in interactive mode (ollama run).\nask <model> <prompt> - send a one-time prompt to the model and print the answer.\ntell <model> <prompt> <file> - send a prompt to the model and save the answer to a file.\nset_default <value> - set the $default variable, used in later commands via check().\nread_file <file> - read a file into the $readed_text variable.\nsh <command> - execute an arbitrary shell command.\nstart_chat <name> <first_message> - create a new chat file <name>.lam_chat with the system prompt and the first user message.\nchat <name> <model> <message> - append the user message to the chat, call the model with the full history, and write the answer after 'assistant:'.\nprint_chat <name> - print the full contents of the chat file <name>.lam_chat.\nprint <text> - print text in console\nread - get input and save it in $readed_text\nload <model> <file> - load file in model and ask him(WARNING:can not work on windows beacouse ollama devs have released stdin bug,please use read_file )\nexit - exit the program\nis_running - show you a running models\nshow <model> - show full info about model\nstop <model> - stop running model\nrename <model> <name> - copy and rename model\n\nVariables:\n$default - set by set_default, substituted when passed as an argument and check() is called.\n$readed_text - set by read_file, substituted the same way.\n\nNotes:\n- Commands are separated by ';' (semicolon), so a single line can contain a whole pipeline.\n- A script file passed as argv[1] is read line by line; each newline becomes ';'.\n- Chat messages use 'user:' and 'assistant:' prefixes to mark who said what.\n");
			}
			else if_command("print"){
				if(cmd(1)!=NULL){
					check(1);
					printf("%s\n",cmd(1));
					now+=1;
				}
			}
			else if_command("read"){
				fgets(from_file,TEXT_LEN,stdin);
				from_file[strcspn(from_file,"\n")]=0;
			}
			else if_command("load")
			{
				if (cmd(1) != NULL && cmd(2) != NULL)
				{
					check(1);
					check(2);
					sprintf(buf, "ollama run \"%s\" < \"%s\"", cmd(1), cmd(2));
					system(buf);
					now += 2;
				}
			}
			else if_command("exit")
			{
				free(from_file);
				free(used);
				free(buf);
				free(input);
				free(buf2);
				exit(0);
			}
			else if_command("is_running")
			{
				system("ollama ps");
			}
			else if_command("stop")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(buf, "ollama stop \"%s\"", cmd(1));
					system(buf);
					now += 1;
				}
			}
			else if_command("show")
			{
				if (cmd(1) != NULL)
				{
					check(1);
					sprintf(buf, "ollama show \"%s\"", cmd(1));
					system(buf);
					now += 1;
				}
			}
			else if_command("rename")
			{
				if (cmd(1) != NULL && cmd(2) != NULL)
				{
					check(1);
					check(2);
					sprintf(buf, "ollama cp \"%s\" \"%s\"", cmd(1), cmd(2));
					system(buf);
					now += 2;
				}
			}
			else
			{
				printf("unknown command!!\n");
			}
		}
	}
	return 0;
}
