#include "Loader.h"

/*Loader::Loader() {
	loadDll();
}*/

/*void Loader::loadDll() {
	WIN32_FIND_DATAA find;

	HANDLE const hFind = FindFirstFileA((path + std::string("*.dll")).c_str(), &find);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::string dllFileName(find.cFileName);
			addFunction(dllFileName);
		} while (NULL != FindNextFileA(hFind, &find));

		FindClose(hFind);
	}
	else {
		;
		throw std::exception();
	}
	std::cout << "\n";
}*/

void Loader::loadDll(const std::string& dllFileName) {
	std::string fullDllPath = path + "Dinamic_" + dllFileName;

	HMODULE hModule = LoadLibraryA(fullDllPath.c_str());

	if (hModule) {
		std::string function = dllFileName.substr(0, dllFileName.find(".dll"));
		//function.erase(0, 8);

		unary ufunc = (unary)GetProcAddress(hModule, "unary");

		if (!ufunc) {
			binary bfunc = (binary)GetProcAddress(hModule, "binary");
			if (!bfunc)
				throw std::exception();

			binary_map.insert(std::pair<std::string, binary>(function, bfunc));
			std::cout << function + " was loaded\n";
		}
		else
			unary_map.insert(std::pair<std::string, unary>(function, ufunc));
		std::cout << function + " was loaded\n";

		//FreeLibrary(hModule);
	}
	else {
		throw std::exception(("Failed to load DLL: " + dllFileName).c_str());
	}
	std::cout << "\n";
}

void Loader::addFunction(const std::string& name) {
	HMODULE hm = LoadLibraryA((path + name).c_str());

	if (!hm)
		throw std::exception();

	std::string function = name.substr(0, name.find(".dll"));
	function.erase(0, 8);
	
	unary ufunc = (unary)GetProcAddress(hm, "unary");

	if (!ufunc) {
		binary bfunc = (binary)GetProcAddress(hm, "binary");
		if (!bfunc)
			throw std::exception();

		binary_map.insert(std::pair<std::string, binary>(function, bfunc));
		std::cout << function + " was loaded";
	}
	else
		unary_map.insert(std::pair<std::string, unary>(function, ufunc));
		std::cout << function + " was loaded";
}

double Loader::operation(double a, double b, const std::string& name) {
	if (Loader::unary_contains(name))
		return unary_map[name](a);
	else if (Loader::binary_contains(name))
		return binary_map[name](a, b);
}

bool Loader::binary_contains(const std::string& name) {
	return binary_map.find(name) != binary_map.end();
}

bool Loader::unary_contains(const std::string& name) {
	return unary_map.find(name) != unary_map.end();
}