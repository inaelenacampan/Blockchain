all : Cryptographie/mainCrypto

Cryptographie/mainCrypto.o : Cryptographie/mainCrypto.c Cryptographie/crypto.h
	gcc -g -o Cryptographie/mainCrypto.o -c Cryptographie/mainCrypto.c

Cryptographie/crypto.o : Cryptographie/crypto.c Cryptographie/crypto.h
	gcc -g -o Cryptographie/crypto.o -c Cryptographie/crypto.c

Cryptographie/mainCrypto : Cryptographie/mainCrypto.o Cryptographie/crypto.o
	gcc -o Cryptographie/mainCrypto Cryptographie/mainCrypto.o Cryptographie/crypto.o

clean : 
	rm -f *.o Cryptographie/*.o Cryptographie/mainCrypto