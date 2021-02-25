#include <iostream>
#include <math.h>
using std::cout;
using std::cin;
using std::endl;

unsigned long gcd(unsigned long a, unsigned long b) {
	unsigned long t;
	while (1) {
		t = a % b;
		if (t == 0)
			return b;
		a = b;
		b = t;
	}
}

unsigned long main()
{	
	unsigned long largePrime_P = 10007;
	unsigned long largePrime_Q = 10009;

	//PUBLIC KEY N
	unsigned long publicKey_N = largePrime_P * largePrime_Q;

	//Compute Totient Phi(N) = (p-1)*(q-1)
	unsigned int phi = (largePrime_P - 1) * (largePrime_Q - 1);

	//PUBLIC KEY E
	unsigned long publicKey_E = 7;
	
	//KEEP PRIVATE
	//Decryption Key (private key) using inverse GCD
	unsigned long privateKey_D = 1;
	unsigned long track;

	for (unsigned long i = 1; i < publicKey_N; i++)
	{
		track = fmod((publicKey_E * i), phi);
		if (track == 1)
		{
			cout << i << endl;
			privateKey_D = i;
			cout << privateKey_D << endl;
			break;
		}
	}

	//Publish public keys
	cout << "Key E is: " << publicKey_E << endl;
	cout << "Key N is: " << publicKey_N << endl;

	unsigned long message_P = 0;

	//Ask user for message to encrypt such that M(message) is smaller than modulus N
	cout << "Please enter your message: ";
	cin >> message_P;

	unsigned long userPublicKey_E = 0;
	unsigned long userPublicKey_N = 0;
	

	//Compute to encrypt user plaintext.
	unsigned long ciphertext = 1;
	
	for (unsigned long i = 0; i < publicKey_E; ++i) {
		ciphertext = (ciphertext * message_P) % publicKey_N;
	}

	//Output Ciphertext
	cout << "Your ciphertext is: " << ciphertext << endl;
	cout << endl;

	unsigned long message_C = 0;

	//Collect ciphertext
	cout << "Please enter your ciphertext message: ";
	cin >> message_C;
	cout << endl;

	//Compute to decrypt user ciphertext
	unsigned long plaintext = 1;

	
	for (unsigned long i = 0; i < privateKey_D; ++i) {
		plaintext = (plaintext * message_C) % publicKey_N;
	}

	//Output Plaintext
	cout << "Your plaintext is: " << plaintext << endl;
	cout << endl;



	system("pause");
	return 0;
}
