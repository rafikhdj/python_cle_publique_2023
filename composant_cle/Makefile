CPPFLAGS += `python3-config --includes` -fPIC
LIBS=`python3-config --ldflags`

COMPOSANT = composant_cle

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o uECC.o

all: test $(LIBSO)

include ../gcc.mk
include ../pybind11.mk

uECC.o: micro-ecc/uECC.c
	$(CC) -c $< -o $@

${COMPOSANT}.o: ${COMPOSANT}.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(LIBSO): ${LIBSO_OBJS}
	$(CXX) -shared -o $@ $^ $(LIBS)

test: $(LIBSO)
	echo "execution du test"
	python3 test.py

clean:
	rm -f ${LIBSO}  ${LIBSO_OBJS} uECC.o

