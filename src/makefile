all:
	make all-build

all-build:
	make debug-build
	make release-build

debug-build:
	make -f makefile-debug.mk     make-target

release-build:
	make -f makefile-release.mk   make-target

deploy:
	make -f makefile-release.mk   deploy-target

package:
	make -f makefile-release.mk   package-target

clean:
	make -f makefile-debug.mk     -i clean
	make -f makefile-release.mk   -i clean

depend:
	makedepend -Y -fmakefile-core.mk `ls *.[hc]xx` 1> /dev/null 2> /dev/null

