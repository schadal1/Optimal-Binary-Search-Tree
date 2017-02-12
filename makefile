all:compile
compile:schadal1_p4.c
	gcc schadal1_p4.c -o submission	
run:
	./submission input0.txt output0.txt
clean:	
	rm -f *~
