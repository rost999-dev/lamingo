# lamingo

🦩 LAMINGO

LAMINGO is a lightweight command-line interface (CLI) wrapper for working with local AI models via Ollama.

It adds pipelines (via ;), variables, and ready-to-use commands for AI interaction to a standard shell. With LAMINGO, you can ask an AI to write code, save it to a file, read that file, and execute it—all in a single line without restarting the program or manually copying text.

Ollama is an optional dependency. Without it, LAMINGO functions as a standard shell wrapper.

🛠️ How to Compile

You need a C compiler (e.g., gcc or clang).

```bash
gcc lamingo.c -o lamingo
```

(On Windows, you can use mingw or tcc)

🚀 How to Run

Run the compiled executable. To execute a script, pass the filename as an argument:

```bash
./lamingo
```

or

```bash
./lamingo script.lam
```

❓ How to View Help

Inside the program, type help and press Enter:

```text
lamingo]}>> help
```

It will display a list of all available commands, their arguments, and descriptions.

🦁 What is this thing

LAMINGO is a mini automation language on top of Ollama.

Instead of typing long commands in the terminal, you write them on a single line separated by ;.

Example pipeline:

```text
tell;llama3;write a shell script to clean the folder;clean.sh;
read_file;clean.sh;
sh;$readed_text
```

What happens here:

1. tell asks llama3 to write a script and saves the response to clean.sh.
2. read_file reads clean.sh and stores the text in the $readed_text variable.
3. sh takes the text from $readed_text and executes it in the system.

Key Features:

· Command pipelines using ;.
· Variables: $default (default model) and $readed_text (file contents).
· Model management (install, delete, list).
· Persistent chat history (start_chat, chat).

---

(Author: rost999-dev. License: MIT)
