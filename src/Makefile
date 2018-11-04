.PHONY: all indent stamp clean

all:
	@echo "Limited purpose Makefile. Try 'make clean' or 'make indent' ..."

indent:
	@indent $(INDENT_FLAGS) main.c
	@indent $(INDENT_FLAGS) main.h
	@indent $(INDENT_FLAGS) options.c
	@indent $(INDENT_FLAGS) options.h

stamp:
	@stamper.bash main.c
	@stamper.bash main.h
	@stamper.bash options.c
	@stamper.bash options.h

clean:
	@$(RM) -f a.out *.o *~
