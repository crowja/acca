all:
	@echo "Limited purpose Makefile. Try 'make clean' or 'make indent' ..."

indent:
	@indent $(INDENT_FLAGS) main.c
	@indent $(INDENT_FLAGS) main.h
	@indent $(INDENT_FLAGS) options.c
	@indent $(INDENT_FLAGS) options.h

clean:
	@$(RM) -f a.out *.o *~
