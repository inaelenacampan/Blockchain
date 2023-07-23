all : Cryptographie/mainCrypto DeclarationsSecurisees/mainDeclsec

Cryptographie/mainCrypto.o : Cryptographie/mainCrypto.c Cryptographie/crypto.h
	gcc -g -o Cryptographie/mainCrypto.o -c Cryptographie/mainCrypto.c

Cryptographie/crypto.o : Cryptographie/crypto.c Cryptographie/crypto.h
	gcc -g -o Cryptographie/crypto.o -c Cryptographie/crypto.c

Cryptographie/mainCrypto : Cryptographie/mainCrypto.o Cryptographie/crypto.o
	gcc -o Cryptographie/mainCrypto Cryptographie/mainCrypto.o Cryptographie/crypto.o

DeclarationsSecurisees/mainDeclsec.o : DeclarationsSecurisees/mainDeclsec.c DeclarationsSecurisees/declsec.h Cryptographie/crypto.h
	gcc -g -o DeclarationsSecurisees/mainDeclsec.o -c DeclarationsSecurisees/mainDeclsec.c

DeclarationsSecurisees/declsec.o : DeclarationsSecurisees/declsec.c DeclarationsSecurisees/declsec.h Cryptographie/crypto.h
	gcc -g -o DeclarationsSecurisees/declsec.o -c DeclarationsSecurisees/declsec.c

DeclarationsSecurisees/mainDeclsec : DeclarationsSecurisees/mainDeclsec.o DeclarationsSecurisees/declsec.o Cryptographie/crypto.o
	gcc -o DeclarationsSecurisees/mainDeclsec DeclarationsSecurisees/mainDeclsec.o DeclarationsSecurisees/declsec.o Cryptographie/crypto.o

clean : 
	rm -f *.o Cryptographie/*.o Cryptographie/mainCrypto DeclarationsSecurisees/*.o DeclarationsSecurisees/mainDeclsec