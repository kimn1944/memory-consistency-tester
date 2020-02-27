write_atomicity : write_atomicity.c sequential1.c sequential2_correct.c sequential2_false.c
	gcc -pthread -o write_atomicity write_atomicity.c
	gcc -pthread -o sequential1 sequential1.c
	gcc -pthread -o sequential2_correct sequential2_correct.c 
	gcc -pthread -o sequential2_false sequential2_false.c 

clean :
	rm ./write_atomicity ./sequential1 ./sequential2_correct ./sequential2_false
