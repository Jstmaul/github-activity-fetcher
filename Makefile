build: clean
	@gcc -Wall -o github-activity main.c cli.c -lcurl

test: clean
	@./app

clean: 
	@rm -rf curl