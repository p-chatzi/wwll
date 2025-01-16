default: run

# -Wall -Werror me permettent de voir les warnings et de les traiter comme des erreurs
# Eviter des problemes plus tard a cause de warning que j'aurais pu regler.
# -O0 pour ne pas optimiser le code, pour faciliter le debug
run: clean build
	g++ src/*.cpp -o out/magi -Wall -Werror -O0
	./out/magi

build:
	mkdir out

clean:
	rm -rf out