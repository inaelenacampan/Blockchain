all : Cryptographie/mainCrypto DeclarationsSecurisees/mainDeclsec BaseDeDonnees/mainList

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

BaseDeDonnees/mainList.o : BaseDeDonnees/mainList.c BaseDeDonnees/list.h DeclarationsSecurisees/declsec.h Cryptographie/crypto.h
	gcc -g -o BaseDeDonnees/mainList.o -c BaseDeDonnees/mainList.c

BaseDeDonnees/list.o : BaseDeDonnees/list.c BaseDeDonnees/list.h DeclarationsSecurisees/declsec.h Cryptographie/crypto.h
	gcc -g -o BaseDeDonnees/list.o -c BaseDeDonnees/list.c

BaseDeDonnees/hashTable.o : BaseDeDonnees/hashTable.c BaseDeDonnees/hashTable.h BaseDeDonnees/list.h DeclarationsSecurisees/declsec.h Cryptographie/crypto.h
	gcc -g -o BaseDeDonnees/hashTable.o -c BaseDeDonnees/hashTable.c

BaseDeDonnees/mainList : BaseDeDonnees/mainList.o BaseDeDonnees/hashTable.o BaseDeDonnees/list.o DeclarationsSecurisees/declsec.o Cryptographie/crypto.o
	gcc -o BaseDeDonnees/mainList BaseDeDonnees/mainList.o BaseDeDonnees/hashTable.o BaseDeDonnees/list.o DeclarationsSecurisees/declsec.o Cryptographie/crypto.o

clean : 
	rm -f *.o Cryptographie/*.o Cryptographie/mainCrypto DeclarationsSecurisees/*.o DeclarationsSecurisees/mainDeclsec BaseDeDonnees/*.o BaseDeDonnees/mainList