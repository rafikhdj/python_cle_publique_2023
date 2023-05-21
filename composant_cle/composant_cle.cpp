#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"

#include <string>
#include <sstream>
#include <vector>

std::vector<uint8_t> hexToUint8(const std::string& hexString) {
    std::vector<uint8_t> result;

    // Iterate over the input string, two characters at a time
    for (size_t i = 0; i < hexString.length(); i += 2) {
        std::string byteString = hexString.substr(i, 2);
        uint8_t byteValue;
        std::stringstream ss;
        ss << std::hex << byteString;
        ss >> byteValue;
        result.push_back(byteValue);
    }

    return result;
}

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Cle
{
    public:
        Cle() {}
        ~Cle() {}

        void initialize(std::string number){
            
            privatekey = hexToUint8(number);
            publickey = uECC_compute_public_key(privatekey, publickey, uECC_secp256k1());
        }
        const std::string &getPrivateKey() const {
	       return privatekey;
       	}
        const std::string &getPublicKey() const {
           return publickey;
           }
    private:
        uint8_t privatekey;
        uint8_t publickey;
        
};
 
namespace py = pybind11;


PYBIND11_MODULE(cle_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Cle class
    py::class_<Cle>(greetings, "Cle")
        .def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}
