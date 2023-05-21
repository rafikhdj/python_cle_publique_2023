#include <pybind11/pybind11.h>
#include "micro-ecc/uECC.h"

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
            
            privatekey = number;
            publickey = uECC_compute_public_key(privateKey, publicKey, uECC_secp256k1());
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
    py::class_<Cle>(greetings, "Cle", py::dynamic_attr())
        .def(py::init<const std::string &>())
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey)
}
