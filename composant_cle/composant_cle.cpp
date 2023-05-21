#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"
#include <string>
#include <sstream>
#include <iomanip>

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Cle
{
    public:
        Cle(){}
	uint8_t castStringToUint8(const std::string& str) {
		
   		std::istringstream iss(str);
    		int intValue;
    		iss >> intValue;
		
    		if (intValue < 0 || intValue > 255) {}
    		return static_cast<uint8_t>(intValue);
	}
	void initialize(const std::string &pk){
	
	privatekey = pk;
        const struct uECC_Curve_t * curve = uECC_secp256k1();
        uECC_Curve curve_256k1 = uECC_secp256k1();

        uint8_t private_key[uECC_curve_private_key_size(curve)]{castStringToUint8(pk)};
        uint8_t public_key[uECC_curve_public_key_size(curve)];

        uECC_make_key(public_key, private_key, curve_256k1);

        std::stringstream ss;

        for (int i = 0; i < uECC_curve_public_key_size(curve); i++)
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(public_key[i]);

        publickey = ss.str();
	}

        const std::string &getPrivateKey() const {
	       return privatekey;
       	}
        const std::string &getPublicKey() const {
           return publickey;
           }
    private:
        std::string privatekey;
        std::string publickey;
        
};
 
namespace py = pybind11;

PYBIND11_MODULE(composant_cle, greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Cle class
    py::class_<Cle>(greetings, "Cle")
        .def(py::init<>())
        .def("initialize", &Cle::initialize, py::arg("pk"))
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}
