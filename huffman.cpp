#include <iostream>
#include <vector>
#include <algorithm>
class No {
public:
	No* l;
	No* r;
	int sum;
	char c;
	No(char c, int sum) : sum{ sum }, c{ c }, l{ nullptr }, r{ nullptr } {};
	No(int sum, No* l, No* r) : sum{ sum }, c{ '\0' }, l{ l }, r{ r } {};

	static No* join(No* l, No* r) {
		int new_sum = l->sum + r->sum;
		return new No(new_sum, l, r);
	}

	static bool greater(No* l, No* r) {
		return (l->sum > r->sum);
	}
};

class HuffmanCoder {
	No* decodificador;
	std::vector<No*> nos;
	int count[256];
	const char* key;
	long long int dicionario[256];

	void construir_vector() {
		// reset counter
		for (int i{}; i < 256; i++) {
			count[i] = 0;
		}
		// obter frequencias
		int i{};
		while (key[i]) {
			count[key[i++]]++;
		}
		if (i < 3) {
			throw;
		}
		// construir vetores
		for (int i{ 1 }; i < 256; i++) {
			if (count[i]) {
				No* new_no = new No(i, count[i]);
				nos.push_back(new_no);
			}
		}
	};

	void codificar_key() {
		while (nos.size() > 1) {
			std::sort(nos.begin(), nos.end(), No::greater);
			No* no1 = nos.back(); nos.pop_back();
			No* no2 = nos.back(); nos.pop_back();
			nos.push_back(No::join(no1, no2));
		}
	};

	void save_codificacao_str(No* no, long long int storage = 1) {
		if (no->l == nullptr && no->r == nullptr) {
			dicionario[no->c] = storage;
			return;
		}
		save_codificacao_str(no->l, storage * 2);
		save_codificacao_str(no->r, storage * 2 + 1);
	}

public:

	void decodificar(const char* str, char* buffer) {
		int i{};
		int buffer_i{};
		No* aux = nos[0];

		while (str[i]) {
			if (str[i++] == '0') {
				aux = aux->l;
			}
			else {
				aux = aux->r;
			}
			if (aux->l == nullptr && aux->r == nullptr) {
				buffer[buffer_i++] = aux->c;
				aux = nos[0];
			}
		}
		buffer[buffer_i] = '\0';
	};

	void codificar(const char* str, char* buffer) {
		int i{};
		int buffer_i{};
		while (str[i]) {
			long long int code = dicionario[str[i++]];
			while (code) {
				if (code == 1)
					break;
				buffer[buffer_i++] = code % 2 + '0';
				code /= 2;
			}
		}
		buffer[buffer_i] = '\0';
	}

	HuffmanCoder(const char* str) : key{ str } {
		construir_vector();
		codificar_key();
		save_codificacao_str(nos[0]);
	};

};

int main() {
	const char* c = "abcccdddd";
	HuffmanCoder coder(c);
	char k[10];
	coder.decodificar("011101100", k);
	std::cout << k << '\n';
	char p[15];
	coder.codificar("dcab", p);
	std::cout << (char*)p << '\n';
}