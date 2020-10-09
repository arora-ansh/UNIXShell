run:
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc main.c
	clear
	./a.out

clear:
	rm ls
	rm a.out
	rm cat
	rm date
	rm mkdir
	rm rm
