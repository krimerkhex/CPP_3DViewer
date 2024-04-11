all: clean clean_tests uninstall dvi install tests dist

install: clean uninstall
	bash bash/install.sh
	mv 3DViewerCpp/3DViewer.app 3DViewer.app

uninstall: clean
	rm -rf 3DViewer.app

clean_tests:
	rm -rf test/*.o
	rm -rf test/s21_test
	rm -rf test/googletest-release-1.11.0

clean: clean_tests
	rm -rf build-3DViewerCpp-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	bash bash/clean.sh

tests: 
	g++ -lstdc++ -g -std=c++17 -Wall -Werror -Wextra -lgtest test/s21_test.cc 3DViewerCpp/model_pars_obj_afin.cc 3DViewerCpp/matrix_lite.h -o test/s21_test
	./test/s21_test

dist: install
	rm -rf 3DViewer.tar.gz
	tar -zcf 3DViewer.tar.gz 3DViewer.app

dvi:
	open info/dvi.html