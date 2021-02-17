#include <iostream>
#include <math.h>
using std::cout;
using std::cin;
using std::endl;

int gcd(int a, int b) {
	int t;
	while (1) {
		t = a % b;
		if (t == 0)
			return b;
		a = b;
		b = t;
	}
}

int main()
{	//KEEP PRIVATE
	//Select 2 large primes 
	int largePrime_P = 10007;
	int largePrime_Q = 29881;

	//PUBLIC KEY N
	//Compute N
	int publicKey_N = largePrime_P * largePrime_Q;
	//10007 * 29881 = 299,019,167

	//Compute Totient Phi(N) = (p-1)*(q-1)
	long int phi = (largePrime_P - 1) * (largePrime_Q - 1);
	//(10007 - 1) = 10006 || (29881 - 1) = 29880 || 10006 * 29880 = 298,979,280

	//PUBLIC KEY E
	//e such that (1 < e < phi), gcd(e,phi(N)) = 1
	int publicKey_E = 7;
	int track;

	while (publicKey_E < phi) {
		track = gcd(publicKey_E, phi);
		if (track == 1)
			break;
		else
			publicKey_E++;
	}

	//KEEP PRIVATE
	//Decryption Key (private key) using inverse GCD
	//(e * d) mod phi(N) = 1 and (0 <= d <= N)
	int privateKey_D;
	int arbitraryValue = 2;

	privateKey_D = (1 + (arbitraryValue * phi)) / publicKey_E;
	// (1 + (2 * 298,979,280)) / 7 = 85,422,651


	//Publish public keys
	cout << "Key E is: " << publicKey_E << endl;
	cout << "Key N is: " << publicKey_N << endl;

	int message_P = 0;

	//LOOP TO CHECK Message_P is smaller than mod publicKey_N
	//Ask user for message to encrypt such that M(message) is smaller than modulus N
	cout << "Please enter your message: ";
	cin >> message_P;

	int userPublicKey_E = 0;
	int userPublicKey_N = 0;
	
	//Collect public keys from user
	cout << "Please enter key E: ";
	cin >> userPublicKey_E;
	cout << endl;

	cout << "Please enter key N: ";
	cin >> userPublicKey_N;
	cout << endl;

	//Compute to encrypt user plaintext.
	long int ciphertext = 1;

	//ciphertext = pow(message_P, userPublicKey_E);
	//ciphertext = fmod(ciphertext, userPublicKey_N);
	for (int i = 0; i < userPublicKey_E; ++i) {
		ciphertext = fmod((ciphertext * message_P), publicKey_N);
	}

	//Output Ciphertext
	cout << "Your ciphertext is: " << ciphertext << endl;
	cout << endl;

	int message_C = 0;

	//Collect ciphertext
	cout << "Please enter your ciphertext message: ";
	cin >> message_C;
	cout << endl;

	//Compute to decrypt user ciphertext
	long int plaintext = 1;

	//plaintext = pow(message_C, privateKey_D);
	//plaintext = fmod(plaintext, publicKey_N);
	for (int i = 0; i < privateKey_D; ++i) {
		plaintext = fmod((plaintext * message_C), publicKey_N);
	}

	//Output Plaintext
	cout << "Your plaintext is: " << plaintext << endl;
	cout << endl;



	system("pause");
	return 0;
}
