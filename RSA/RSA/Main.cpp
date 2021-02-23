#include <iostream>
using std::cout;
using std::cin;
using std::endl;

const unsigned long largePrime_P = 10007;
const unsigned long largePrime_Q = 29881;
const unsigned long publicKey_E = 7;

int main()
{
	unsigned long publicKey_N, privateKey_D, phi, track;
	unsigned long message_P, message_C, userPublicKey_N, userPublicKey_E;
	unsigned long plaintext = 1;
	unsigned long ciphertext = 1;

	//PUBLIC KEY N
	//Compute N
	publicKey_N = largePrime_P * largePrime_Q; //10007 * 29881 = 299,019,167
	
	//Compute Totient Phi(N) = (p-1)*(q-1)
	phi = (largePrime_P - 1) * (largePrime_Q - 1); //(10007 - 1) = 10006 || (29881 - 1) = 29880 || 10006 * 29880 = 298,979,280

	//PRIVATE KEY D
	//Decryption Key (private key) using inverse GCD
	//(e * d) mod phi(N) = 1 and (0 <= d <= N)
	for (unsigned long i = 1; i < publicKey_N; i++)
	{
		track = (publicKey_E * i) % phi;
		if (track == 1)
		{
			privateKey_D = i;
			break;
		}
	}
	
	//Publish public keys
	cout << "Key E is: " << publicKey_E << endl;
	cout << "Key N is: " << publicKey_N << endl;


	//LOOP TO CHECK Message_P is smaller than mod publicKey_N
	//Ask user for message to encrypt such that M(message) is smaller than modulus N

	cout << "Please enter your message: ";
	cin >> message_P;

	//Collect public keys from user
	//cout << "Please enter key E: ";
	//cin >> userPublicKey_E;
	//cout << endl;

	//cout << "Please enter key N: ";
	//cin >> userPublicKey_N;
	//cout << endl;

	//Compute to encrypt user plaintext.
	for (unsigned long i = 0; i < publicKey_E; i++) {
		ciphertext = (ciphertext * message_P) % publicKey_N;
		//((1 * 23) ^ 7) % 299019167  == 115614610
	}

	//Output Ciphertext
	cout << "Your ciphertext is: " << ciphertext << endl;
	cout << endl;

	//Collect ciphertext
	//cout << "Please enter your ciphertext message: ";
	//cin >> message_C;
	//cout << endl;

	//Compute to decrypt user ciphertext
	for (unsigned long i = 0; i < privateKey_D; i++) {
		plaintext = (plaintext * ciphertext) % publicKey_N;
		//((1 * 115614610) ^ 170845303) % 299019167  == KEEP GETTING (81622366) SUPPOSED TO BE 23
	}

	//Output Plaintext
	cout << "Your plaintext is: " << plaintext << endl;
	cout << endl;

	system("pause");
	return 0;
}
