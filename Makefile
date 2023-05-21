
all: component1 component2 component3

component1:
	cd hello && ${MAKE}

component2:
	cd voiture && ${MAKE}

component3:
	cd composant_cle && ${MAKE}

