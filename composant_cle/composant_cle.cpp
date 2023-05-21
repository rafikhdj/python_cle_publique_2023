#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"
#include <string>
#include <sstream>

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
	void initialize(std::string &pk){
		privatekey = pk;
		uint8_t a = castStringToUint8(privatekey);
		uint8_t b = castStringToUint8(publickey);
        const struct uECC_Curve_t * curve = uECC_secp256k1();
		uECC_Curve curve_256k1 = uECC_secp256k1();
		uECC_make_key(&a,&b,curve_256k1);
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


PYBIND11_MODULE(cle_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Cle class
    py::class_<Cle>(greetings, "Cle")
        .def(py::init<>())
	.def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}
