# minishell

This is the first group project in 42KL's core programme where needed us to recreate a bash shell in C. This really challenged us in terms of planning, work-delegation and communication, which was an enriching experience for us as programmers.

I will admit that our Minishell is not perfect (in terms of handling obscure edge cases and weird syntax errors), but we did what we can to fix whatever we could find in our limited timeframe.

For more detail on the cases we tested, we have a compilation of them in the notes directory.

# Features:
## Built-ins:
```
1. echo with -n
2. cd with relative path or absolute path
3. pwd
4. unset
5. env
6. exit
```

## Handles:
```
1. single quotes
2. double quotes
3. redirections (< > << >>)
4. pipes
5. environment variables ($PATH etc.)
6. exit code ($?)
7. signals (ctrl-c, ctrl-d, ctrl-\)
8. special cases: "'$PATH'" '"$PATH"'
```

# How we implemented it:

In terms of the workload distribution I mainly worked on the tokenizing, parsing and expansion while my teammate Lewis dealt with the execution, piping, signal handling and the built-ins.

![image](https://github.com/rsoo23/minishell/assets/81731553/f0ab9a96-32b0-4ca4-b97f-97055ab41171)
![image](https://github.com/rsoo23/minishell/assets/81731553/288a8616-7261-4eec-a515-383a9d3fdd14)

# Dependencies:
This project requires readline to work.
If you do not have readline installed, use this command to install it.
```bash
sudo apt-get install lib32readline7 lib32readline-dev
```
This is required due our implementation for getting user input.

# How to use:
1. Clone the repository
```bash
git clone https://github.com/rsoo23/minishell.git minishell
```
2. Make the executable
```bash
make
```
3. Run the executable
```bash
./minishell
```
4. Type your input
```bash
cat < input.txt << hi | wc -l | cat > output.txt
```
