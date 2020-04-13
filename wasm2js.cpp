/*

wasm2js

*/

#include <iostream>
#include <fstream>
#include "base64.hpp"

using namespace std;



string encode_wasm(string inputfilename) {

	ifstream stream(inputfilename, ios::in | ios::binary);
	vector<base64::byte> vec(
		(istreambuf_iterator<char>(stream)), 
		istreambuf_iterator<char>());
	return base64::encode(vec);
}



string wrap_js_code(string base64_wasm) {
	return "const wasm_strbuffer = atob(\""+base64_wasm+"\");\nwasm_codearray = new Uint8Array(wasm_strbuffer.length);\nfor (var i in wasm_strbuffer) wasm_codearray[i] = wasm_strbuffer.charCodeAt(i);";
}



int main(int argc, char *argv[]) {

	if (argc != 2) {
		cout << "Usage: wasm2js <wasm file>" << endl;
		return 0;
	}

	cout << wrap_js_code(encode_wasm(argv[1])) << endl;

	return 0;

}

