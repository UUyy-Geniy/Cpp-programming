#include "Loader.h"

void Loader::loadDll(const std::string& dllFileName, Operations& operations) {
	std::string fullDllPath = path + "Dinamic_" + dllFileName;

	HMODULE hModule = LoadLibraryA(fullDllPath.c_str());

	if (hModule) {
		std::string function = dllFileName.substr(0, dllFileName.find(".dll"));

		unary ufunc = (unary)GetProcAddress(hModule, "unary");

		if (!ufunc) {
			binary bfunc = (binary)GetProcAddress(hModule, "binary");
			if (!bfunc)
				throw std::exception();
			operations.addBinaryOperation(function,bfunc,4);
			std::cout << function + " was loaded";
		}
		else
			operations.addUnaryOperation(function, ufunc, 4);
		std::cout << function + " was loaded";

	}
	else {
		throw std::exception(("Failed to load DLL: " + dllFileName+"\n").c_str());
	}
	std::cout << "\n";
}
