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
{	//KEEP PRIVATE
	//Select 2 large primes 
	unsigned long largePrime_P = 10007;
	//unsigned long largePrime_P = 13;
	unsigned long largePrime_Q = 29881;
	//unsigned long largePrime_Q = 11;

	//PUBLIC KEY N
	//Compute N
	unsigned long publicKey_N = largePrime_P * largePrime_Q;
	//10007 * 29881 = 299,019,167

	//Compute Totient Phi(N) = (p-1)*(q-1)
	unsigned int phi = (largePrime_P - 1) * (largePrime_Q - 1);
	//(10007 - 1) = 10006 || (29881 - 1) = 29880 || 10006 * 29880 = 298,979,280

	//PUBLIC KEY E
	//e such that (1 < e < phi), gcd(e,phi(N)) = 1
	unsigned long publicKey_E = 7;
	
	//KEEP PRIVATE
	//Decryption Key (private key) using inverse GCD
	//(e * d) mod phi(N) = 1 and (0 <= d <= N)
	double privateKey_D;
	unsigned long track;

	privateKey_D = (1 + (2 * phi)) / publicKey_E;
	/*for (unsigned long i = 1; i < publicKey_N; i++)
	{
		track = fmod((publicKey_E * i), phi);
		if (track == 1)
		{
			cout << i << endl;
			privateKey_D = i;
			break;
		}
	}*/
	
	//privateKey_D = fmod((publicKey_E * privateKey_D), phi);
	// (7 * 170845303) % 298,979,280


	//Publish public keys
	cout << "Key E is: " << publicKey_E << endl;
	cout << "Key N is: " << publicKey_N << endl;

	unsigned long message_P = 0;

	//LOOP TO CHECK Message_P is smaller than mod publicKey_N
	//Ask user for message to encrypt such that M(message) is smaller than modulus N
	cout << "Please enter your message: ";
	cin >> message_P;

	unsigned long userPublicKey_E = 0;
	unsigned long userPublicKey_N = 0;
	
	//Collect public keys from user
	cout << "Please enter key E: ";
	cin >> userPublicKey_E;
	cout << endl;

	cout << "Please enter key N: ";
	cin >> userPublicKey_N;
	cout << endl;

	//Compute to encrypt user plaintext.
	unsigned long ciphertext = 1;// pow(message_P, userPublicKey_E);
	//23 * 7
	//ciphertext = fmod(ciphertext, userPublicKey_N);
	//161 % 299,019,167
	for (unsigned long i = 0; i < userPublicKey_E; ++i) {
		ciphertext = fmod((ciphertext * message_P), publicKey_N);
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
	unsigned long plaintext = 1;// pow(message_C, privateKey_D);

	//plaintext = pow(message_C, privateKey_D);
	// 115614610 ^ 170845303
	//plaintext = fmod(plaintext, publicKey_N);
	for (unsigned long i = 0; i < privateKey_D; ++i) {
		plaintext = fmod((plaintext * message_C), publicKey_N);
	}

	//Output Plaintext
	cout << "Your plaintext is: " << plaintext << endl;
	cout << endl;



	system("pause");
	return 0;
}
