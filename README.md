
Wasm2js
=======

General Info
------------

This tool transform .wasm file to base64 encoding wrapped into javascript code, so that it can be used in a local .html file without the need for fetch() or any client server communication.

This command prints javascript wrapping code and base64 encoded wasm code

```
wasm2js <wasm file>
```

This command saves javascript wrapping code + base64 encoded wasm code into javascript file

```
wasm2js <wasm file> > <js file>
```

Example
-------

Let's write trivial C program (example.c) just to ilustrate webassembly imports (print function) and exports (test function):

void print();

void test() {
	print();
}

We can compile that online at WasmExplorer: https://mbebenita.github.io/WasmExplorer/ and get:

(module
 (type $FUNCSIG$v (func))
 (import "env" "_Z5printv" (func $_Z5printv))
 (table 0 anyfunc)
 (memory $0 1)
 (export "memory" (memory $0))
 (export "_Z4testv" (func $_Z4testv))
 (func $_Z4testv (; 1 ;)
  (call $_Z5printv)
 )
)

And after than download .wasm compiled as explorer.wasm file.

Running wasm2js example.wasm gives javascript code:

const wasm_strbuffer = atob(AGFzbQEAAAABhICAgAABYAAAApGAgIAAAQNlbnYJX1o1cHJpbnR2AAADgoCAgAABAASEgICAAAFwAAAFg4CAgAABAAEGgYCAgAAAB5WAgIAAAgZtZW1vcnkCAAhfWjR0ZXN0dgABCoqAgIAAAYSAgIAAABAACw==);
wasm_codearray = new Uint8Array(wasm_strbuffer.length);
for (var i in wasm_strbuffer) wasm_codearray[i] = wasm_strbuffer.charCodeAt(i);

So now in wasm_codearray variable we have compiled wasm code ready to be used in WebAssembly.

Because compiled C++ code adds prefix and suffix to function names (as can be seen from webassembly source) we now have "_Z5printv" instead of "print" and "_Z4testv" instead of "test". So .html file to run it all looks like:

<!DOCTYPE HTML>
<HTML>
<script src="example.js"></script>
<body>
<h1>WASM TEST</H1>
<script>

imports = {};
imports["_Z5printv"] = () => { alert("Javascript code for C++ function print()"); } // imported function print()
WebAssembly.instantiate(wasm_codearray, {"env":imports})
	.then (obj => { obj.instance.exports._Z4testv(); }); // exported function test()

</script>
</BODY>
</HTML>



Dependencies
------------
I've used slightly modified code https://github.com/mvorbrodt/blog/blob/master/src/base64.hpp for base64 encoding/decoding.




Requirements
------------
C++14 Compiler




License
-------

Written by Sinisa Pavlovic, sipavlovic@gmail.com

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.



